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
    cSceneGameStart(const cEngine &_engine,
                    std::string _imageNameBackground,
                    std::string _imageNameLogo,
                    std::string _text,
                    std::string _switchToSceneName) :
                    cSceneBase(_engine),
                    switchToSceneName(_switchToSceneName),
                    imageNameBackground(_imageNameBackground),
                    imageNameLogo(_imageNameLogo), text(_text) {}

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
