// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include <string>
#include <memory>
#include "../engine/Aliases.h"
#include "../engine/SDL_Deleter.h"
#include "../engine/Utilities.h"

namespace Forradia {

class cTextGraphics {
 public:
  void Initialize();

  // --- Drawing operations ---

  void DrawString(std::string text, SDL_Color color, float x, float y,
                         bool centerAlign = false) const;

 private:
  const std::string defaultFontPath = "/Resources/Fonts/PixeloidSans.ttf";
  const int defaultFontSize = 20;
  const float scaling = 0.8f;

  std::unique_ptr<TTF_Font, cSDL_Deleter> defaultFont;
  cUtilities utilities;
};

}  // namespace Forradia
