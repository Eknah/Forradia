// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "ScenesCollection.h"

namespace Forradia
{

    void ScenesCollection::Add(std::string sceneName, SPtr<SceneBase> scene)
    {
        scenes.insert({ GetId(sceneName), std::move(scene) });
    }

    void ScenesCollection::AddMany(std::vector<std::tuple<std::string, SPtr<SceneBase>>> scenes_)
    {
        for (auto& entry : scenes_)
        {
            auto name = std::get<0>(entry);
            auto scene = std::get<1>(entry);

            scenes.insert({ GetId(name), scene });
        }
    }

}