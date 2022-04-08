// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once

namespace Forradia {

class IEngine;
class Actor;

class IModule {
 public:
  IModule(const IEngine &_engine, Actor *_parentActor)
      : engine(_engine), parentActor(_parentActor) {}

  virtual void ResetForNewFrame() = 0;
  virtual void Update() = 0;

  Actor &GetParentActor();

 protected:
  const IEngine &engine;

 private:
  Actor *parentActor;
};

}  // namespace Forradia
