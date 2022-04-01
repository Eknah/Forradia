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
  explicit cActor(const iEngine &Engine_) : Engine(Engine_),
    ActorId(CurrentActorId++) {}

  cActor(const iEngine &Engine_, float X, float Y, std::string ModelName_);

  cActor(const iEngine &Engine_, std::string ModelName_) :
      Engine(Engine_), ModelName(ModelName_),
      ActorId(CurrentActorId++) {}

  void ResetForNewFrame() const;
  void Update() const;

  template <class T>
  T &GetModule() const;

  int GetAnimatedModelId() const;

  template <class T>
  void AddModule();

  template <class T>
  bool HasModule() const;

  template <class T>
  void AddIfNotExists();


//  cPoint3 WorldMapCoord = {1, 1, 0};
//  cPoint2F Position = {50.0f, 50.0f};
//  float PositionZ = 0.0f;
//  std::string ModelName;
//  UPtr<float> FacingAngle = MakeUPtr<float>(0.0f);
  int ActorId = -1;
  std::string ModelName;

  virtual ~cActor() {}  // Just to make class polymorphic

 protected:

 private:

  const iEngine &Engine;

  inline static int CurrentActorId = 0;

  UMap<size_t, UPtr<iModule>> Modules;
};

template <class T>
T &cActor::GetModule() const {
  return static_cast<T &>(*Modules.at(typeid(T).hash_code()));
}

template <class T>
void cActor::AddModule() {
  auto &Type = typeid(T);
  Modules.insert({Type.hash_code(), MakeUPtr<T>(Engine, this)});
}

template <class T>
bool cActor::HasModule() const {
  return Modules.count(typeid(T).hash_code()) > 0;
}

template <class T>
void cActor::AddIfNotExists() {
    if (!HasModule<T>()) {
        AddModule<T>();
    }
}


}  // namespace Forradia
