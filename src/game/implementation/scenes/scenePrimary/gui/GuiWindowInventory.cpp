// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "GuiWindowInventory.h"
#include "../engine/Engine.h"

namespace Forradia {

void cGuiWindowInventory::RenderDerived() {
  auto canvasSize = utilities.GetCanvasSize();
  auto aspectRatio = static_cast<float>(canvasSize.width) / canvasSize.height;
  auto boundsInterior = GetInteriorBounds();

  engine.FillRectangle(palette.wheat, boundsInterior.x, boundsInterior.y,
                       boundsInterior.width, boundsInterior.height);

  auto slotSize = boundsInterior.width / numSlotCols - margin;
  auto numSlotRows =
      boundsInterior.height / ((slotSize + margin) * aspectRatio);
  auto i = 0;


  for (auto y = 0; y < numSlotRows; y++) {
    for (auto x = 0; x < numSlotCols; x++) {
      auto xpos = boundsInterior.x + x * (slotSize + margin);
      auto ypos = boundsInterior.y + y * (slotSize * aspectRatio + margin);

      if (engine.GetPlayer().GetModule<cModuleInventory>()
              .inventory.objects.count(i) > 0) {
        if (engine.GetPlayer().GetModule<cModuleObjectUsage>()
                .objectBeingUsed ==
            engine.GetPlayer().GetModule<cModuleInventory>().inventory.objects.at(i))
          engine.DrawImage("ObjectSelected", xpos, ypos, slotSize,
                           slotSize * aspectRatio);
        else
          engine.DrawImage("ObjectBackgroundShadow", xpos, ypos, slotSize,
                           slotSize * aspectRatio);

        engine.DrawImage(engine.GetPlayer().GetModule<cModuleInventory>()
                             .inventory.objects.at(i)
                             ->objectType,
                         xpos, ypos, slotSize, slotSize * aspectRatio);
      }

      i++;
    }
  }
}

void cGuiWindowInventory::DoMouseDownDerived(Uint8 mouseButton) {
  if (mouseButton != SDL_BUTTON_RIGHT)
    return;

  engine.GetPlayer().GetModule<cModuleObjectUsage>().objectBeingUsed = nullptr;

  auto canvasSize = utilities.GetCanvasSize();
  auto aspectRatio = static_cast<float>(canvasSize.width) / canvasSize.height;
  auto boundsInterior = GetInteriorBounds();

  auto slotSize = boundsInterior.width / numSlotCols - margin;
  auto numSlotRows =
      boundsInterior.height / ((slotSize + margin) * aspectRatio);
  auto i = 0;

  auto mousePosition = utilities.GetMousePositionI();
  auto mouseXRel = static_cast<float>(mousePosition.x) / canvasSize.width;
  auto mouseYRel = static_cast<float>(mousePosition.y) / canvasSize.height;

  for (auto y = 0; y < numSlotRows; y++) {
    for (auto x = 0; x < numSlotCols; x++) {
      auto xpos = boundsInterior.x + x * (slotSize + margin);
      auto ypos = boundsInterior.y + y * (slotSize * aspectRatio + margin);

      if (engine.GetPlayer().GetModule<cModuleInventory>()
              .inventory.objects.count(i) > 0) {
        if (mouseXRel >= xpos && mouseYRel >= ypos &&
            mouseXRel < xpos + slotSize &&
            mouseYRel < ypos + slotSize * aspectRatio) {
          engine.GetPlayer().GetModule<cModuleObjectUsage>().objectBeingUsed =
              engine.GetPlayer().GetModule<cModuleInventory>().inventory
                  .objects.at(i);
          return;
        }
      }

      i++;
    }
  }
}

}  // namespace Forradia
