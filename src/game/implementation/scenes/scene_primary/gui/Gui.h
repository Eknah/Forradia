// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include <string>
#include <vector>
#include "../engine/Engine.h"
#include "../engine/Utilities.h"
#include "GuiMinimap.h"
#include "framework/GuiWindowBase.h"

namespace Forradia {

class cGui {
 public:
  explicit cGui(const cEngine &_engine) :
        engine(_engine), guiMinimap(_engine) {}

  void Initialize();
  void Update();
  void Render();
  bool DoMouseDown(Uint8 mouseButton);
  void DoMouseUp();

  UMap<std::string, UPtr<cGuiWindowBase>> windows;

 private:
  const cEngine &engine;

  cGuiMinimap guiMinimap;

  std::vector<std::string> textBoxText = {"You have entered Forradia"};

  const float textBoxMargin = 0.005f;

  cUtilities utilities;

  const float buttonWidth = 0.15f;
  const float buttonHeight = 0.03f;
  const float textBoxWidth = 3 * buttonWidth;
  const float textBoxHeight = 0.15f;

  const int buttonMallSize = 100;

  cRectF boundsButtonInventory = {0.5f - buttonWidth / 2, 1.0f - buttonHeight,
                                  buttonWidth, buttonHeight};
  cRectF boundsButtonCharacter = {0.5f - buttonWidth / 2 - buttonWidth,
                                  1.0f - buttonHeight, buttonWidth,
                                  buttonHeight};
  cRectF boundsButtonSystem = {0.5f - buttonWidth / 2 + buttonWidth,
                               1.0f - buttonHeight, buttonWidth, buttonHeight};
  cRectF boundsTextBox = {0.5f - textBoxWidth / 2,
                          1.0f - buttonHeight - textBoxHeight, textBoxWidth,
                          textBoxHeight};
};

}  // namespace Forradia
