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
                    std::string SwitchToSceneName_,
                    std::string ImageNameBackground_,
                    std::string ImageNameLogo_,
                    std::string Text_) :
                    cSceneBase(Engine_),
                    SwitchToSceneName(SwitchToSceneName_),
                    ImageNameBackground(ImageNameBackground_),
                    ImageNameLogo(ImageNameLogo_), Text(Text_) {}

  void Enter() override {}

  void Update() override;

  void Render() override;

  void DoMouseDown(Uint8 mouseButton) override {};
  void DoMouseUp(Uint8 mouseButton) override {}

 private:
  std::string SwitchToSceneName;
  std::string ImageNameBackground;
  std::string ImageNameLogo;
  std::string Text;
};

}  // namespace Forradia
