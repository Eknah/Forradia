// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include <GL/glew.h>
#include <SDL2/SDL_pixels.h>
#include <vector>
#include "../engine/Point2F.h"

namespace Forradia {

class cPaintGraphics {
 public:
  // ---- Drawing operations ----

  void FillRectangle(SDL_Color color, float x, float y, float width,
                            float Height) const;

  void DrawRectangle(SDL_Color color, float x, float y, float width,
                            float height) const;

  void DrawLine(SDL_Color color, float x0, float y0, float x1,
                       float y1) const;

 private:
  // ---- Drawing operations generalization ----

  void RenderShape(GLenum geometryType,
                          const std::vector<cPoint2F> &vertices,
                          SDL_Color color) const;
};

}  // namespace Forradia
