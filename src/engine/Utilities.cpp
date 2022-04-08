// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "Utilities.h"

namespace Forradia {

cSize cUtilities::GetCanvasSize() const {
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    auto canvas_width = viewport[2];
    auto canvas_height = viewport[3];

    return {canvas_width, canvas_height};
  }

cPoint2 cUtilities::GetMousePositionI() {
    auto x = 0;
    auto y = 0;
    SDL_GetMouseState(&x, &y);

    return {x, y};
  }

cPoint2F cUtilities::GetMousePositionF() {
    auto mousePosition = GetMousePositionI();
    auto canvas_size = GetCanvasSize();
    auto mousexF = static_cast<float>(mousePosition.x) / canvas_size.width;
    auto mouseyF = static_cast<float>(mousePosition.y) / canvas_size.height;

    return {mousexF, mouseyF};
  }

cSizeF cUtilities::ConvertToFloat(int value) {
    auto canvasSize = GetCanvasSize();
    auto resultWidth = static_cast<float>(value) / canvasSize.width;
    auto resultHeight = static_cast<float>(value) / canvasSize.height;

    return {resultWidth, resultHeight};
  }

}  // namespace Forradia
