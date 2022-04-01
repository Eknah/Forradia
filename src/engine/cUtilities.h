// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "cPoint2.h"
#include "cPoint2F.h"
#include "cSize.h"
#include "cSizeF.h"
#include <GL/glew.h>
#include <SDL2/SDL.h>

namespace Forradia {

class cUtilities {
 public:
  cSize GetCanvasSize() const;

  cPoint2 GetMousePositionI();

  cPoint2F GetMousePositionF();

  cSizeF ConvertToFloat(int value);
};

}  // namespace Forradia
