// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "Point2.h"
#include "Point2F.h"
#include "Size.h"
#include "SizeF.h"
#include <GL/glew.h>
#include <SDL2/SDL.h>

namespace Forradia {

class Utilities {
 public:
  Size GetCanvasSize() const;
  Point2 GetMousePositionI();
  Point2F GetMousePositionF();
  SizeF ConvertToFloat(int value);
};

}  // namespace Forradia
