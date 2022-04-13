// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include <string>
#include <utility>
#include <vector>
#include <tuple>
#include "../engine/Aliases.h"
#include "framework/SceneBase.h"

namespace Forradia
{

    class ScenesCollection
    {
    public:
        // Collection operations
        void Add(std::string sceneName, SPtr<SceneBase> scene);
        void AddMany(std::vector<std::tuple<std::string, SPtr<SceneBase>>> _scenes);

        // Collection structure
        UMap<int, SPtr<SceneBase>> scenes;
    };

}  // namespace Forradia
