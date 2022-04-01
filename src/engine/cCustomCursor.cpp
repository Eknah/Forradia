// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "cCustomCursor.h"

namespace Forradia {

void cCustomCursor::Initialize() {
    SDL_ShowCursor(0);
}

void cCustomCursor::ResetForNewFrame() {
  CursorType = eCursorTypes::Default;
}

void cCustomCursor::Render() {
    auto mouse_pos_f = Utilities.GetMousePositionF();
    auto cursor_size_f = Utilities.ConvertToFloat(CursorSize);

    switch (CursorType) {
    case eCursorTypes::Default: {
      Engine.DrawImage("CursorDefault", mouse_pos_f.X, mouse_pos_f.Y,
                       cursor_size_f.Width, cursor_size_f.Height);
      break;
    }
    case eCursorTypes::Hovering: {
      Engine.DrawImage("CursorHoveringClickable", mouse_pos_f.X, mouse_pos_f.Y,
                       cursor_size_f.Width, cursor_size_f.Height);
      break;
    }
    }
  }

}  // namespace Forradia
