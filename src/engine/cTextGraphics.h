// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include <string>
#include <memory>
#include "../engine/Aliases.h"
#include "../engine/cSDL_Deleter.h"
#include "../engine/cUtilities.h"

namespace Forradia {

class cTextGraphics {
 public:
  void Initialize();

  // --- Drawing operations ---

  void DrawString(std::string Text, SDL_Color Color, float X, float Y,
                         bool CenterAlign = false) const;

 private:
  const std::string DefaultFontPath = "/Resources/Fonts/PixeloidSans.ttf";
  const int DefaultFontSize = 20;
  const float Scaling = 0.8f;

  std::unique_ptr<TTF_Font, cSDL_Deleter> DefaultFont;
  cUtilities Utilities;
};

}  // namespace Forradia
