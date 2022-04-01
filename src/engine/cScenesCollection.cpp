// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "cScenesCollection.h"

namespace Forradia {

void cScenesCollection::Add(std::string sceneName, SPtr<cSceneBase> scene) {
    Scenes.insert({GetId(sceneName), std::move(scene)});
  }

void cScenesCollection::AddMany(std::vector<std::tuple<std::string, SPtr<cSceneBase>>> scenes) {
    for (auto& entry : scenes) {
        auto name = std::get<0>(entry);
        auto scene = std::get<1>(entry);

        Scenes.insert({GetId(name), scene});
    }
}

}  // namespace Forradia
