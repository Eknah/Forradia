// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "../engine/Engine.h"
#include "../engine/Utilities.h"

namespace Forradia {

class Console {
 public:
  explicit Console(const Engine &_e) : e(_e) {}

  void Render();
  void Print(std::string message);
  void ToggleInput();
  void AttemptWriteCharacter(char c);

 private:
  const Engine &e;

  const float textBoxWidth = 3 * 0.15f;
  const float textBoxHeight = 0.15f;
  const float textBoxMargin = 0.005f;

  std::string inputText;

  bool inputActive = false;

  RectF boundsTextBox = {0.5f - textBoxWidth / 2,
                          1.0f - 0.03f - textBoxHeight, textBoxWidth,
                          textBoxHeight};

  std::vector<std::string> textBoxText = {};

  Utilities utilities;
};

}  // namespace Forradia
