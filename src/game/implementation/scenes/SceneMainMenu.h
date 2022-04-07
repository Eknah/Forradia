// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "../engine/Utilities.h"
#include "../engine/Palette.h"
#include "framework/SceneBase.h"

namespace Forradia {

class cSceneMainMenu : public cSceneBase {
 public:
  using cSceneBase::cSceneBase;

  void Enter() override;
  void Update() override;
  void Render() override;
  void DoMouseDown(Uint8 mouseButton) override {};
  void DoMouseUp(Uint8 mouseButton) override {}

 private:
  cUtilities utilities;
  cPalette palette;
};

}  // namespace Forradia
