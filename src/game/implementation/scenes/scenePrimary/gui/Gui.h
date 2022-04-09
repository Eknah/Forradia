// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include <string>
#include <vector>
#include "../engine/Engine.h"
#include "../engine/Utilities.h"
#include "GuiMinimap.h"
#include "framework/GuiWindowBase.h"
#include "Console.h"

namespace Forradia {

class Gui {
 public:
  explicit Gui(const Engine &_e) :
        e(_e), guiMinimap(_e), console(_e) {}

  void Initialize();
  void Update();
  void Render();
  bool DoMouseDown(Uint8 mouseButton);
  void DoMouseUp();

  UMap<std::string, UPtr<GuiWindowBase>> windows;
  Console console;

 private:
  const Engine &e;

  GuiMinimap guiMinimap;

  const float textBoxMargin = 0.005f;

  Utilities utilities;

  const float buttonWidth = 0.15f;
  const float buttonHeight = 0.03f;

  const int buttonMallSize = 100;

  RectF boundsButtonInventory = {0.5f - buttonWidth / 2, 1.0f - buttonHeight,
                                  buttonWidth, buttonHeight};
  RectF boundsButtonCharacter = {0.5f - buttonWidth / 2 - buttonWidth,
                                  1.0f - buttonHeight, buttonWidth,
                                  buttonHeight};
  RectF boundsButtonSystem = {0.5f - buttonWidth / 2 + buttonWidth,
                               1.0f - buttonHeight, buttonWidth, buttonHeight};

};

}  // namespace Forradia
