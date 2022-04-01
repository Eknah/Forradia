// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include <GL/glew.h>
#include <SDL2/SDL_pixels.h>
#include <vector>
#include "../engine/cPoint2F.h"

namespace Forradia {

class cPaintGraphics {
 public:
  // ---- Drawing operations ----

  void FillRectangle(SDL_Color Color, float X, float Y, float Width,
                            float Height) const;

  void DrawRectangle(SDL_Color Color, float X, float Y, float Width,
                            float Height) const;

  void DrawLine(SDL_Color Color, float X0, float Y0, float X1,
                       float Y1) const;

 private:
  // ---- Drawing operations generalization ----

  void RenderShape(GLenum GeometryType,
                          const std::vector<cPoint2F> &Vertices,
                          SDL_Color Color) const;
};

}  // namespace Forradia
