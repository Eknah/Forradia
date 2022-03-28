// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "../engine/Aliases.h"
#include "framework/cSceneBase.h"

namespace Forradia {

class cScenesCollection {
 public:
  // Collection operations
  inline void Add(std::string sceneName, UPtr<cSceneBase> scene) {
    Scenes.insert({GetId(sceneName), std::move(scene)});
  }

  // Collection structure
  UMap<int, UPtr<cSceneBase>> Scenes;
};

}  // namespace Forradia
