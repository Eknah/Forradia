// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include <string>
#include <utility>
#include "../engine/Aliases.h"
#include "framework/cSceneBase.h"

namespace Forradia {

class cScenesCollection {
 public:
  // Collection operations
  inline void Add(std::string sceneName, UPtr<cSceneBase> scene) {
    Scenes.insert({GetId(sceneName), std::move(scene)});
  }

//  inline cScenesCollection& operator=(const cScenesCollection &Other) {
//      Scenes = Other.Scenes;

//      return *this;
//  }

  // Collection structure
  UMap<int, UPtr<cSceneBase>> Scenes;
};

}  // namespace Forradia
