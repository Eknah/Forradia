// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once

namespace Forradia {

class iEngine;
class cActor;

class iModule {
 public:
  iModule(const iEngine &_engine, cActor *_parentActor)
      : engine(_engine), parentActor(_parentActor) {}

  virtual void ResetForNewFrame() = 0;
  virtual void Update() = 0;

  cActor &GetParentActor();

 protected:
  const iEngine &engine;

 private:
  cActor *parentActor;
};

}  // namespace Forradia
