// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "cGuiWindowInventory.h"
#include "../engine/Engine.h"

namespace Forradia {

void cGuiWindowInventory::RenderDerived() {
  auto CanvasSize = utilities.GetCanvasSize();
  auto AspectRatio = static_cast<float>(CanvasSize.width) / CanvasSize.height;
  auto BoundsInterior = GetInteriorBounds();

  engine.FillRectangle(palette.wheat, BoundsInterior.x, BoundsInterior.y,
                       BoundsInterior.width, BoundsInterior.height);

  auto SlotSize = BoundsInterior.width / numSlotCols - margin;
  auto NumSlotRows =
      BoundsInterior.height / ((SlotSize + margin) * AspectRatio);
  auto I = 0;


  for (auto Y = 0; Y < NumSlotRows; Y++) {
    for (auto X = 0; X < numSlotCols; X++) {
      auto XPos = BoundsInterior.x + X * (SlotSize + margin);
      auto YPos = BoundsInterior.y + Y * (SlotSize * AspectRatio + margin);

      if (engine.GetPlayer().GetModule<cModuleInventory>()
              .inventory.objects.count(I) > 0) {
        if (engine.GetPlayer().GetModule<cModuleObjectUsage>()
                .objectBeingUsed ==
            engine.GetPlayer().GetModule<cModuleInventory>().inventory.objects.at(I))
          engine.DrawImage("ObjectSelected", XPos, YPos, SlotSize,
                           SlotSize * AspectRatio);
        else
          engine.DrawImage("ObjectBackgroundShadow", XPos, YPos, SlotSize,
                           SlotSize * AspectRatio);

        engine.DrawImage(engine.GetPlayer().GetModule<cModuleInventory>()
                             .inventory.objects.at(I)
                             ->objectType,
                         XPos, YPos, SlotSize, SlotSize * AspectRatio);
      }

      I++;
    }
  }
}

void cGuiWindowInventory::DoMouseDownDerived(Uint8 MouseButton) {
  if (MouseButton != SDL_BUTTON_RIGHT)
    return;

  engine.GetPlayer().GetModule<cModuleObjectUsage>().objectBeingUsed = nullptr;

  auto CanvasSize = utilities.GetCanvasSize();
  auto AspectRatio = static_cast<float>(CanvasSize.width) / CanvasSize.height;
  auto BoundsInterior = GetInteriorBounds();

  auto SlotSize = BoundsInterior.width / numSlotCols - margin;
  auto NumSlotRows =
      BoundsInterior.height / ((SlotSize + margin) * AspectRatio);
  auto I = 0;

  auto MousePosition = utilities.GetMousePositionI();
  auto MouseXRel = static_cast<float>(MousePosition.x) / CanvasSize.width;
  auto MouseYRel = static_cast<float>(MousePosition.y) / CanvasSize.height;

  for (auto Y = 0; Y < NumSlotRows; Y++) {
    for (auto X = 0; X < numSlotCols; X++) {
      auto XPos = BoundsInterior.x + X * (SlotSize + margin);
      auto YPos = BoundsInterior.y + Y * (SlotSize * AspectRatio + margin);

      if (engine.GetPlayer().GetModule<cModuleInventory>()
              .inventory.objects.count(I) > 0) {
        if (MouseXRel >= XPos && MouseYRel >= YPos &&
            MouseXRel < XPos + SlotSize &&
            MouseYRel < YPos + SlotSize * AspectRatio) {
          engine.GetPlayer().GetModule<cModuleObjectUsage>().objectBeingUsed =
              engine.GetPlayer().GetModule<cModuleInventory>().inventory
                  .objects.at(I);
          return;
        }
      }

      I++;
    }
  }
}

}  // namespace Forradia
