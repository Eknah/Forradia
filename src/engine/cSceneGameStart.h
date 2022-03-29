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
  inline void Update() override {
    if (Engine.KeyboardHandler.KeysBeenFired->size() > 0)
      Engine.SceneManager.SwitchToScene(SwitchToSceneName);

    if (Engine.MouseHandler.GetLeftButtonBeenFired()
            || Engine.MouseHandler.GetRightButtonBeenFired())
        Engine.SceneManager.SwitchToScene(SwitchToSceneName);
  }

  inline void Render() override {
    Engine.DrawImage(ImageNameBackground, 0, 0, 1, 1);

    auto LogoSizeF = Engine.GetImageSizeF(ImageNameLogo);

    Engine.DrawImage(ImageNameLogo, 0.5f - LogoSizeF.Width / 2.0f,
                     0.25f - LogoSizeF.Height / 2.0f,
                     LogoSizeF.Width,
                     LogoSizeF.Height);
    Engine.DrawString(Text, {255, 255, 255, 255}, 0.5f, 0.5f, true);
  }
  void DoMouseDown(Uint8 mouseButton) override {};
  void DoMouseUp(Uint8 mouseButton) override {}

 private:
  cUtilities Utilities;

  std::string SwitchToSceneName;
  std::string ImageNameBackground;
  std::string ImageNameLogo;
  std::string Text;
};

}  // namespace Forradia
