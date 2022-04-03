// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include <string>
#include "cUtilities.h"
#include "framework/cSceneBase.h"
#include "cEngine.h"

namespace Forradia {

class cSceneGameStart : public cSceneBase {
 public:
    cSceneGameStart(const cEngine &Engine_,
                    std::string ImageNameBackground_,
                    std::string ImageNameLogo_,
                    std::string Text_,
                    std::string SwitchToSceneName_) :
                    cSceneBase(Engine_),
                    switchToSceneName(SwitchToSceneName_),
                    imageNameBackground(ImageNameBackground_),
                    imageNameLogo(ImageNameLogo_), text(Text_) {}

  void Enter() override {}
  void Update() override;
  void Render() override;
  void DoMouseDown(Uint8 mouseButton) override {};
  void DoMouseUp(Uint8 mouseButton) override {}

 private:
  std::string switchToSceneName;
  std::string imageNameBackground;
  std::string imageNameLogo;
  std::string text;
};

}  // namespace Forradia
