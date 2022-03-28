// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once

namespace Forradia {

class iEngine;
class cActor;

class iModule {
 public:
  iModule(const iEngine &Engine_, cActor *ParentActor_)
      : Engine(Engine_), ParentActor(ParentActor_) {}

  virtual void ResetForNewFrame() = 0;
  virtual void Update() = 0;

  inline cActor &GetParentActor() {
      return *ParentActor;
  }

 protected:
  const iEngine &Engine;

 private:
  cActor *ParentActor;
};

}  // namespace Forradia
