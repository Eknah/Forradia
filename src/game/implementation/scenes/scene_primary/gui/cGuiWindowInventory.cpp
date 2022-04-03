// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "cGuiWindowInventory.h"
#include "../engine/cEngine.h"

namespace Forradia {

void cGuiWindowInventory::RenderDerived() {
  auto CanvasSize = Utilities.GetCanvasSize();
  auto AspectRatio = static_cast<float>(CanvasSize.width) / CanvasSize.height;
  auto BoundsInterior = GetInteriorBounds();

  Engine.FillRectangle(Palette.wheat, BoundsInterior.x, BoundsInterior.y,
                       BoundsInterior.width, BoundsInterior.height);

  auto SlotSize = BoundsInterior.width / NumSlotCols - Margin;
  auto NumSlotRows =
      BoundsInterior.height / ((SlotSize + Margin) * AspectRatio);
  auto I = 0;


  for (auto Y = 0; Y < NumSlotRows; Y++) {
    for (auto X = 0; X < NumSlotCols; X++) {
      auto XPos = BoundsInterior.x + X * (SlotSize + Margin);
      auto YPos = BoundsInterior.y + Y * (SlotSize * AspectRatio + Margin);

      if (Engine.GetPlayer().GetModule<cModuleInventory>()
              .Inventory.objects.count(I) > 0) {
        if (Engine.GetPlayer().GetModule<cModuleObjectUsage>()
                .ObjectBeingUsed ==
            Engine.GetPlayer().GetModule<cModuleInventory>().Inventory.objects.at(I))
          Engine.DrawImage("ObjectSelected", XPos, YPos, SlotSize,
                           SlotSize * AspectRatio);
        else
          Engine.DrawImage("ObjectBackgroundShadow", XPos, YPos, SlotSize,
                           SlotSize * AspectRatio);

        Engine.DrawImage(Engine.GetPlayer().GetModule<cModuleInventory>()
                             .Inventory.objects.at(I)
                             ->ObjectType,
                         XPos, YPos, SlotSize, SlotSize * AspectRatio);
      }

      I++;
    }
  }
}

void cGuiWindowInventory::DoMouseDownDerived(Uint8 MouseButton) {
  if (MouseButton != SDL_BUTTON_RIGHT)
    return;

  Engine.GetPlayer().GetModule<cModuleObjectUsage>().ObjectBeingUsed = nullptr;

  auto CanvasSize = Utilities.GetCanvasSize();
  auto AspectRatio = static_cast<float>(CanvasSize.width) / CanvasSize.height;
  auto BoundsInterior = GetInteriorBounds();

  auto SlotSize = BoundsInterior.width / NumSlotCols - Margin;
  auto NumSlotRows =
      BoundsInterior.height / ((SlotSize + Margin) * AspectRatio);
  auto I = 0;

  auto MousePosition = Utilities.GetMousePositionI();
  auto MouseXRel = static_cast<float>(MousePosition.x) / CanvasSize.width;
  auto MouseYRel = static_cast<float>(MousePosition.y) / CanvasSize.height;

  for (auto Y = 0; Y < NumSlotRows; Y++) {
    for (auto X = 0; X < NumSlotCols; X++) {
      auto XPos = BoundsInterior.x + X * (SlotSize + Margin);
      auto YPos = BoundsInterior.y + Y * (SlotSize * AspectRatio + Margin);

      if (Engine.GetPlayer().GetModule<cModuleInventory>()
              .Inventory.objects.count(I) > 0) {
        if (MouseXRel >= XPos && MouseYRel >= YPos &&
            MouseXRel < XPos + SlotSize &&
            MouseYRel < YPos + SlotSize * AspectRatio) {
          Engine.GetPlayer().GetModule<cModuleObjectUsage>().ObjectBeingUsed =
              Engine.GetPlayer().GetModule<cModuleInventory>().Inventory
                  .objects.at(I);
          return;
        }
      }

      I++;
    }
  }
}

}  // namespace Forradia
