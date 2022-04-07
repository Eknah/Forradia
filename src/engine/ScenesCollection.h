// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include <string>
#include <utility>
#include <vector>
#include <tuple>
#include "../engine/Aliases.h"
#include "framework/SceneBase.h"

namespace Forradia {

class cScenesCollection {
 public:
  // Collection operations
  void Add(std::string sceneName, SPtr<cSceneBase> scene);
  void AddMany(std::vector<std::tuple<std::string, SPtr<cSceneBase>>> _scenes);

  // Collection structure
  UMap<int, SPtr<cSceneBase>> scenes;
};

}  // namespace Forradia
