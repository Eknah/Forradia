// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include <string>
#include "../engine/Aliases.h"
#include "../engine/Point2F.h"
#include "../engine/Point3.h"
#include "../engine/IModule.h"

namespace Forradia {

class IEngine;

class Actor {
 public:
  explicit Actor(const IEngine &_engine) : engine(_engine),
    actorId(currentActorId++) {}

  Actor(const IEngine &_engine, float x, float y, std::string _modelName);

  Actor(const IEngine &_engine, std::string _modelName) :
      engine(_engine), modelName(_modelName),
      actorId(currentActorId++) {}

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
  int actorId = -1;
  std::string modelName;

  virtual ~Actor() {}  // Just to make class polymorphic

 protected:

 private:

  const IEngine &engine;

  inline static int currentActorId = 0;

  UMap<size_t, UPtr<IModule>> modules;
};

template <class T>
T &Actor::GetModule() const {
  return static_cast<T &>(*modules.at(typeid(T).hash_code()));
}

template <class T>
void Actor::AddModule() {
  auto &Type = typeid(T);
  modules.insert({Type.hash_code(), MakeUPtr<T>(engine, this)});
}

template <class T>
bool Actor::HasModule() const {
  return modules.count(typeid(T).hash_code()) > 0;
}

template <class T>
void Actor::AddIfNotExists() {
    if (!HasModule<T>()) {
        AddModule<T>();
    }
}


}  // namespace Forradia
