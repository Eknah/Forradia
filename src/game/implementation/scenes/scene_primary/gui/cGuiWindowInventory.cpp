
#include "cGuiWindowInventory.h"
#include "../engine/cEngine.h"

namespace Forradia
{

void cGuiWindowInventory::RenderDerived()
{
    auto CanvasSize = Utilities.GetCanvasSize();
    auto AspectRatio = float(CanvasSize.Width) / CanvasSize.Height;
    auto BoundsInterior = GetInteriorBounds();

    Engine.FillRectangle(Palette.Wheat, BoundsInterior.X, BoundsInterior.Y, BoundsInterior.Width, BoundsInterior.Height);

    auto SlotSize = BoundsInterior.Width / NumSlotCols - Margin;
    auto NumSlotRows = BoundsInterior.Height / ((SlotSize + Margin) * AspectRatio);
    auto I = 0;

    auto MousePosition = Utilities.GetMousePositionI();
    auto MouseXRel = (double)MousePosition.X / CanvasSize.Width;
    auto MouseYRel = (double)MousePosition.Y / CanvasSize.Height;

    for (auto Y = 0; Y < NumSlotRows; Y++)
    {
        for (auto X = 0; X < NumSlotCols; X++)
        {
            auto XPos = BoundsInterior.X + X * (SlotSize + Margin);
            auto YPos = BoundsInterior.Y + Y * (SlotSize * AspectRatio + Margin);

            if (Engine.Player.GetModule<cModuleInventory>().Objects.count(I) > 0)
            {
                if (Engine.Player.GetModule<cModuleObjectUsage>().ObjectBeingUsed == Engine.Player.GetModule<cModuleInventory>().Objects.at(I))
                    Engine.DrawImage("ObjectSelected", XPos, YPos, SlotSize, SlotSize * AspectRatio);
                else
                    Engine.DrawImage("ObjectBackgroundShadow", XPos, YPos, SlotSize, SlotSize * AspectRatio);

                Engine.DrawImage(Engine.Player.GetModule<cModuleInventory>().Objects.at(I)->ObjectType, XPos, YPos, SlotSize, SlotSize * AspectRatio);
            }

            I++;
        }
    }
}

void cGuiWindowInventory::DoMouseDownDerived(Uint8 MouseButton)
{
    if (MouseButton != SDL_BUTTON_RIGHT) return;
    Engine.Player.GetModule<cModuleObjectUsage>().ObjectBeingUsed = nullptr;

    auto CanvasSize = Utilities.GetCanvasSize();
    auto AspectRatio = double(CanvasSize.Width) / CanvasSize.Height;
    auto BoundsInterior = GetInteriorBounds();

    auto SlotSize = BoundsInterior.Width / NumSlotCols - Margin;
    auto NumSlotRows = BoundsInterior.Height / ((SlotSize + Margin) * AspectRatio);
    auto I = 0;

    auto MousePosition = Utilities.GetMousePositionI();
    auto MouseXRel = (double)MousePosition.X / CanvasSize.Width;
    auto MouseYRel = (double)MousePosition.Y / CanvasSize.Height;

    for (auto Y = 0; Y < NumSlotRows; Y++)
    {
        for (auto X = 0; X < NumSlotCols; X++)
        {
            auto XPos = BoundsInterior.X + X * (SlotSize + Margin);
            auto YPos = BoundsInterior.Y + Y * (SlotSize * AspectRatio + Margin);

            if (Engine.Player.GetModule<cModuleInventory>().Objects.count(I) > 0)
            {
                if (MouseXRel >= XPos && MouseYRel >= YPos && MouseXRel < XPos + SlotSize && MouseYRel < YPos + SlotSize * AspectRatio)
                {
                    Engine.Player.GetModule<cModuleObjectUsage>().ObjectBeingUsed = Engine.Player.GetModule<cModuleInventory>().Objects.at(I);
                    return;
                }


            }

            I++;
        }
    }
}

}
