// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include <string>
#include "../engine/Aliases.h"
#include "../engine/iEngine.h"

namespace Forradia {

class cImageGraphics {
 public:
  explicit cImageGraphics(iEngine &engine) : Engine(engine) {}

  // ---- Drawing operations ----

  void DrawImage(std::string ImageName, float X, float Y, float Width,
                        float Height) const;

  void DrawImage(int ImageNameId, float X, float Y, float Width,
                        float Height) const;

  cSizeF GetImageSizeF(std::string ImageName) const;

 private:
  iEngine &Engine;
  cUtilities Utilities;
};

}  // namespace Forradia
