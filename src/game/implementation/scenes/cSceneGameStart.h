// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "../engine/cUtilities.h"
#include "CommonExternal.h"
#include "framework/cSceneBase.h"

namespace Forradia {

class cSceneGameStart : public cSceneBase {
 public:
  using cSceneBase::cSceneBase;

  void Enter() override {}
  void Update() override;
  void Render() override;
  void DoMouseDown(Uint8 mouseButton) override {};
  void DoMouseUp(Uint8 mouseButton) override {}

 private:
  cUtilities Utilities;
};

}  // namespace Forradia
