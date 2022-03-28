// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "../engine/Aliases.h"
#include "../engine/cPoint2F.h"
#include "../engine/cPoint3.h"
#include "../engine/iModule.h"
#include "CommonExternal.h"

namespace Forradia {

class iEngine;

class cActor {
 public:
  explicit cActor(iEngine &Engine_) : Engine(Engine_) {}

  void ResetForNewFrame();
  void Update();

  template <class T> inline T &GetModule() {
    return static_cast<T &>(*Modules.at(typeid(T).hash_code()));
  }

  cPoint3 WorldMapCoord = {1, 1, 0};
  cPoint2F Position = {50.0f, 50.0f};

 protected:
  template <class T> inline void AddModule() {
    auto &Type = typeid(T);
    Modules.insert({Type.hash_code(), MakeUPtr<T>(Engine, *this)});
  }

 private:
  iEngine &Engine;

  UMap<size_t, UPtr<iModule>> Modules;
};

}  // namespace Forradia
