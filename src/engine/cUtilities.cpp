// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "cUtilities.h"

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
    auto mouse_position = GetMousePositionI();
    auto canvas_size = GetCanvasSize();
    auto mouse_x_f = static_cast<float>(mouse_position.X) / canvas_size.Width;
    auto mouse_y_f = static_cast<float>(mouse_position.Y) / canvas_size.Height;

    return {mouse_x_f, mouse_y_f};
  }

cSizeF cUtilities::ConvertToFloat(int value) {
    auto canvas_size = GetCanvasSize();
    auto result_width = static_cast<float>(value) / canvas_size.Width;
    auto result_height = static_cast<float>(value) / canvas_size.Height;

    return {result_width, result_height};
  }

}  // namespace Forradia
