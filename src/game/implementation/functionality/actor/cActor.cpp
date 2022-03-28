// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "cActor.h"

namespace Forradia {

void cActor::ResetForNewFrame() const {
  for (auto &[Key, Module] : Modules)
    Module->ResetForNewFrame();
}

void cActor::Update() const {
  for (auto &[Key, Module] : Modules)
    Module->Update();
}

}  // namespace Forradia
