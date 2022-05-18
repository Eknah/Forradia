// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "CraftSkillsModule.h".h"
#include "IEngine.h"

namespace Forradia
{
    std::vector<CraftRecipe> CraftSkillsModule::GetPossibleRecipes(Point2 tile)
    {

        std::vector<CraftRecipe> result;

        if (tile.x < 0 || tile.y < 0 || tile.x >= e.GetCurrMapArea().size || tile.y >= e.GetCurrMapArea().size) return result;

        auto& hoveredTile = e.GetCurrMapArea().tiles[tile.x][tile.y];

        for (auto& object : hoveredTile.objects)
        {
            if (object->objectType == GetId("ObjectTree1"))
            {
                CraftRecipe recipe;
                recipe.toolObjectType = GetId("ObjectWoodaxe");
                recipe.rawMatObjectType = GetId("ObjectTree1");
                recipe.resultObjectType = GetId("ObjectFelledTree");
                recipe.description = "Chop down tree";

                result.push_back(recipe);
            }
            if (object->objectType == GetId("ObjectTree2"))
            {
                CraftRecipe recipe;
                recipe.toolObjectType = GetId("ObjectWoodaxe");
                recipe.rawMatObjectType = GetId("ObjectTree2");
                recipe.resultObjectType = GetId("ObjectFelledTree");
                recipe.description = "Chop down tree";

                result.push_back(recipe);
            }
            if (object->objectType == GetId("ObjectRipeAppleTree"))
            {
                CraftRecipe recipe;
                recipe.toolObjectType = GetId("ObjectWoodaxe");
                recipe.rawMatObjectType = GetId("ObjectRipeAppleTree");
                recipe.resultObjectType = GetId("ObjectFelledTree");
                recipe.description = "Chop down tree";

                result.push_back(recipe);
            }
        }

        return result;
    }

    void CraftSkillsModule::TryPerformRecipe(CraftRecipe recipe)
    {
        auto& hoveredTile = e.GetCurrMapArea().tiles[recipe.craftTile.x][recipe.craftTile.y];

        for (auto& object : hoveredTile.objects)
        {
            if (object->objectType == recipe.rawMatObjectType)
            {
                object->objectType = recipe.resultObjectType;
                return;
            }
        }
    }
}
