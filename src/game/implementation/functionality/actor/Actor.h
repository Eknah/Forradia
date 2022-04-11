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
  explicit Actor(const IEngine &_e) : e(_e),
    actorId(currentActorId++) {}

  Actor(const IEngine &_e, float x, float y, std::string _modelName);

  Actor(const IEngine &_e, std::string _modelName) :
      e(_e), modelName(_modelName),
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

  int actorId = -1;
  std::string modelName;

  virtual ~Actor() {}  // Just to make class polymorphic

 protected:

 private:

  const IEngine &e;

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
  modules.insert({Type.hash_code(), MakeUPtr<T>(e, this)});
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
