// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "InventoryWindow.h"
#include "../engine/Engine.h"

namespace Forradia
{

    void InventoryWindow::RenderDerived()
    {
        auto canvasSize = utils.GetCanvasSize();
        auto aspectRatio = static_cast<float>(canvasSize.w) / canvasSize.h;
        auto boundsInterior = GetInteriorBounds();

        e.FillRect(palette.wheat, boundsInterior.x, boundsInterior.y,
            boundsInterior.w, boundsInterior.h);

        auto slotSize = boundsInterior.w / numSlotCols - margin;
        auto numSlotRows =
            boundsInterior.h / ((slotSize + margin) * aspectRatio);
        auto i = 0;


        for (auto y = 0; y < numSlotRows; y++)
        {
            for (auto x = 0; x < numSlotCols; x++)
            {
                auto xpos = boundsInterior.x + x * (slotSize + margin);
                auto ypos = boundsInterior.y + y * (slotSize * aspectRatio + margin);

                if (e.GetPlayer().GetModule<InventoryModule>()
                    .inventory.objects.count(i) > 0)
                {
                    if (e.GetPlayer().GetModule<ObjectUsageModule>()
                        .objectBeingUsed ==
                        e.GetPlayer().GetModule<InventoryModule>().inventory.objects.at(i))
                        e.DrawImage("ObjectSelected", xpos, ypos, slotSize,
                            slotSize * aspectRatio);
                    else
                        e.DrawImage("ObjectBackgroundShadow", xpos, ypos, slotSize,
                            slotSize * aspectRatio);

                    e.DrawImage(e.GetPlayer().GetModule<InventoryModule>()
                        .inventory.objects.at(i)
                        ->objectType,
                        xpos, ypos, slotSize, slotSize * aspectRatio);
                }

                i++;
            }
        }
    }

    void InventoryWindow::DoMouseDownDerived(Uint8 mouseButton)
    {
        if (mouseButton != SDL_BUTTON_RIGHT)
            return;

        e.GetPlayer().GetModule<ObjectUsageModule>().objectBeingUsed = nullptr;

        auto canvasSize = utils.GetCanvasSize();
        auto aspectRatio = static_cast<float>(canvasSize.w) / canvasSize.h;
        auto boundsInterior = GetInteriorBounds();

        auto slotSize = boundsInterior.w / numSlotCols - margin;
        auto numSlotRows =
            boundsInterior.h / ((slotSize + margin) * aspectRatio);
        auto i = 0;

        auto mousePosition = utils.GetMousePosI();
        auto mouseXRel = static_cast<float>(mousePosition.x) / canvasSize.w;
        auto mouseYRel = static_cast<float>(mousePosition.y) / canvasSize.h;

        for (auto y = 0; y < numSlotRows; y++)
        {
            for (auto x = 0; x < numSlotCols; x++)
            {
                auto xpos = boundsInterior.x + x * (slotSize + margin);
                auto ypos = boundsInterior.y + y * (slotSize * aspectRatio + margin);

                if (e.GetPlayer().GetModule<InventoryModule>()
                    .inventory.objects.count(i) > 0)
                {
                    if (mouseXRel >= xpos && mouseYRel >= ypos &&
                        mouseXRel < xpos + slotSize &&
                        mouseYRel < ypos + slotSize * aspectRatio)
                    {
                        e.GetPlayer().GetModule<ObjectUsageModule>().objectBeingUsed =
                            e.GetPlayer().GetModule<InventoryModule>().inventory
                            .objects.at(i);
                        return;
                    }
                }

                i++;
            }
        }
    }

}  // namespace Forradia
