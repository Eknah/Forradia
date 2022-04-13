// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include <string>
#include "../engine/Aliases.h"
#include "../engine/IEngine.h"

namespace Forradia {

class ImageGraphics {
 public:
  explicit ImageGraphics(IEngine &_e) : e(_e) {}

  // ---- Drawing operations ----

  void DrawImage(std::string ImageName, float X, float Y, float Width,
                        float Height) const;

  void DrawImage(int ImageNameId, float X, float Y, float Width,
                        float Height) const;

  SizeF GetImageSizeF(std::string ImageName) const;

 private:
  IEngine &e;
  Utilities utils;
};

}  // namespace Forradia
