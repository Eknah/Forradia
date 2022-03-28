// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include <string>
#include <vector>
#include "../engine/cEngine.h"
#include "../engine/cUtilities.h"
#include "cGuiMinimap.h"
#include "framework/cGuiWindowBase.h"

namespace Forradia {

class cGui {
 public:
  explicit cGui(const cEngine &Engine_) :
        Engine(Engine_), GuiMinimap(Engine_) {}

  void Initialize();
  void Update();
  void Render();
  bool DoMouseDown(Uint8 MouseButton);
  void DoMouseUp();

  UMap<std::string, UPtr<cGuiWindowBase>> Windows;

 private:
  const cEngine &Engine;

  cGuiMinimap GuiMinimap;

  std::vector<std::string> TextBoxText = {"You have entered the world"};

  const float TextBoxMargin = 0.005f;

  cUtilities Utilities;

  const float ButtonWidth = 0.15f;
  const float ButtonHeight = 0.03f;
  const float TextBoxWidth = 3 * ButtonWidth;
  const float TextBoxHeight = 0.15f;

  cRectF BoundsButtonInventory = {0.5f - ButtonWidth / 2, 1.0f - ButtonHeight,
                                  ButtonWidth, ButtonHeight};
  cRectF BoundsButtonCharacter = {0.5f - ButtonWidth / 2 - ButtonWidth,
                                  1.0f - ButtonHeight, ButtonWidth,
                                  ButtonHeight};
  cRectF BoundsButtonSystem = {0.5f - ButtonWidth / 2 + ButtonWidth,
                               1.0f - ButtonHeight, ButtonWidth, ButtonHeight};
  cRectF BoundsTextBox = {0.5f - TextBoxWidth / 2,
                          1.0f - ButtonHeight - TextBoxHeight, TextBoxWidth,
                          TextBoxHeight};
};

}  // namespace Forradia
