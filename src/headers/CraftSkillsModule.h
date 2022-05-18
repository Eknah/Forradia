// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once

#include "IModule.h"
#include "Aliases.h"
#include "CraftRecipe.h"
#include "Point2.h"

namespace Forradia
{

    class Object;

    class CraftSkillsModule : public IModule
    {

        // Functions

    public:
        using IModule::IModule;

        void ResetForNewFrame() override {};
        void Update() override {};
        std::vector<CraftRecipe> GetPossibleRecipes(Point2 tile);
        void TryPerformRecipe(CraftRecipe recipe);


    public:
      SPtr<Object> objectBeingUsed = nullptr;

    };

}