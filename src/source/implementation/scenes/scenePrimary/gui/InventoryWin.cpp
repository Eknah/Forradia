// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "InventoryWin.h"
#include "Engine.h"
#include "CraftSkillsModule.h"

namespace Forradia
{
    void InventoryWin::RenderEx()
    {
        using namespace Palette;

        auto& player = e.GetPlayer();

        auto canvasSize = utils.GetCanvasSize();
        auto aspectRatio = CFloat(canvasSize.w) / canvasSize.h;
        auto boundsInterior = GetInnerBounds();

        e.FillRect(Wheat, boundsInterior);

        auto slotSize = boundsInterior.w / numSlotCols - margin;
        auto numSlotRows = boundsInterior.h / ((slotSize + margin) * aspectRatio);

        auto i = 0;

        for (auto y = 0; y < numSlotRows; y++)
        {
            auto ypos = boundsInterior.y + y * (slotSize * aspectRatio + margin);

            for (auto x = 0; x < numSlotCols; x++)
            {
                auto xpos = boundsInterior.x + x * (slotSize + margin);

                if (player.GetModule<InventoryModule>().inventory.objects.count(i) > 0)
                {
                    if (player.GetModule<CraftSkillsModule>().objectBeingUsed == e.GetPlayer().GetModule<InventoryModule>().inventory.objects.at(i))
                        e.DrawImage("ObjectSelected", xpos, ypos, slotSize, slotSize * aspectRatio);
                    else
                        e.DrawImage("ObjectBackgroundShadow", xpos, ypos, slotSize, slotSize * aspectRatio);

                    e.DrawImage(player.GetModule<InventoryModule>().inventory.objects.at(i)->objectType, xpos, ypos, slotSize, slotSize * aspectRatio);
                }

                i++;
            }
        }
    }

    void InventoryWin::MouseDownEx(Uint8 mouseButton)
    {
        if (mouseButton != SDL_BUTTON_RIGHT) return;

        auto& player = e.GetPlayer();

        player.GetModule<CraftSkillsModule>().objectBeingUsed = nullptr;

        auto canvasSize = utils.GetCanvasSize();
        auto aspectRatio = CFloat(canvasSize.w) / canvasSize.h;
        auto boundsInterior = GetInnerBounds();

        auto slotSize = boundsInterior.w / numSlotCols - margin;
        auto numSlotRows = boundsInterior.h / ((slotSize + margin) * aspectRatio);
        auto i = 0;

        auto mousePosRel = utils.GetMousePosF();

        for (auto y = 0; y < numSlotRows; y++)
        {
            auto ypos = boundsInterior.y + y * (slotSize * aspectRatio + margin);

            for (auto x = 0; x < numSlotCols; x++)
            {
                auto xpos = boundsInterior.x + x * (slotSize + margin);

                if (player.GetModule<InventoryModule>().inventory.objects.count(i) > 0)
                {
                    if (mousePosRel.x >= xpos && mousePosRel.y >= ypos && mousePosRel.x < xpos + slotSize && mousePosRel.y < ypos + slotSize * aspectRatio)
                    {
                        player.GetModule<CraftSkillsModule>().objectBeingUsed = player.GetModule<InventoryModule>().inventory.objects.at(i);
                        return;
                    }
                }

                i++;
            }
        }
    }
}