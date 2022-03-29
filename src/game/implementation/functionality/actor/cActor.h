// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include <string>
#include "../engine/Aliases.h"
#include "../engine/cPoint2F.h"
#include "../engine/cPoint3.h"
#include "../engine/iModule.h"

namespace Forradia {

class iEngine;

class cActor {
 public:
  explicit cActor(const iEngine &Engine_) : Engine(Engine_) {
        ActorId = CurrentActorId++;
    }

  cActor(const iEngine &Engine_, float X, float Y, std::string ModelName_) :
      Engine(Engine_), Position({X, Y}), ModelName(ModelName_) {
      ActorId = CurrentActorId++;
  }

  cActor(const iEngine &Engine_, std::string ModelName_) :
      Engine(Engine_), ModelName(ModelName_) {
      ActorId = CurrentActorId++;
  }

  void ResetForNewFrame() const;
  void Update() const;

  template <class T> inline T &GetModule() const {
    return static_cast<T &>(*Modules.at(typeid(T).hash_code()));
  }

  int GetAnimatedModelId() const;

  cPoint3 WorldMapCoord = {1, 1, 0};
  cPoint2F Position = {50.0f, 50.0f};
  float PositionZ = 0.0f;
  std::string ModelName;
  UPtr<float> FacingAngle = MakeUPtr<float>(0.0f);
  int ActorId = -1;

  virtual ~cActor() {}  // Just to make class polymorphic

 protected:
  template <class T> inline void AddModule() {
    auto &Type = typeid(T);
    Modules.insert({Type.hash_code(), MakeUPtr<T>(Engine, this)});
  }

 private:
  template <class T> inline bool HasModule() const {
    return Modules.count(typeid(T).hash_code()) > 0;
  }

  const iEngine &Engine;

  inline static int CurrentActorId = 0;

  UMap<size_t, UPtr<iModule>> Modules;
};

}  // namespace Forradia
