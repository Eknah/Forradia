// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "RightClickMenu.h"
#include "Engine.h"
#include "Palette.h"

namespace Forradia
{

    void RightClickMenu::Render()
    {
        if (!visible) return;

        using namespace Palette;

        auto y = lineHeight;


        e.FillRect(MediumBlueSemiTrans, mouseClickPos.x, mouseClickPos.y, width, lineHeight);
        e.DrawString("Crafting actions", Wheat, mouseClickPos.x, mouseClickPos.y);
        e.DrawLine(Wheat, mouseClickPos.x, mouseClickPos.y + lineHeight, mouseClickPos.x + width, mouseClickPos.y + lineHeight);

        if (recipes.size() == 0)
        {
            e.FillRect(MediumBlueSemiTrans, mouseClickPos.x, mouseClickPos.y + lineHeight, width, lineHeight);
            e.DrawString("None", Wheat, mouseClickPos.x, mouseClickPos.y + lineHeight);
        }
        else
        {

            for (auto& recipe : recipes)
            {

                auto rect = RectF {mouseClickPos.x, mouseClickPos.y + y, width, lineHeight};

                if (rect.Contains(utils.GetMousePosF()))
                {
                    e.FillRect(LightMediumBlueSemiTrans, mouseClickPos.x, mouseClickPos.y + y, width, lineHeight);
                    e.cursor.type = CursorTypes::Hovering;
                }
                else
                {
                    e.FillRect(MediumBlueSemiTrans, mouseClickPos.x, mouseClickPos.y + y, width, lineHeight);
                }

                e.DrawString(recipe.description, Wheat, mouseClickPos.x, mouseClickPos.y + y);

                y += lineHeight;
            }
        }

    }

    void RightClickMenu::MouseDown(Uint8 mouseButton)
    {
        if (mouseButton == SDL_BUTTON_LEFT)
        {
            if (!visible) return;

            visible = false;

            auto y = lineHeight;

            for (auto& recipe : recipes)
            {
                auto rect = RectF {mouseClickPos.x, mouseClickPos.y + y, width, lineHeight};

                if (rect.Contains(utils.GetMousePosF()))
                {
                    e.GetPlayer().GetModule<CraftSkillsModule>().TryPerformRecipe(recipe);
                }

                y += lineHeight;
            }
        }
    }

    void RightClickMenu::MouseUp(Uint8 mouseButton)
    {
        if (mouseButton == SDL_BUTTON_RIGHT && e.mouseHandler.rightClickDeltaPos < 0.0002f)
        {
            visible = true;
            mouseClickPos = utils.GetMousePosF();
            auto hoveredTile = camera.GetHoveredTile();
            recipes = e.GetPlayer().GetModule<CraftSkillsModule>().GetPossibleRecipes(hoveredTile);
            for (auto& recipe : recipes)
            {
                recipe.craftTile = hoveredTile;
            }
        }
    }

}