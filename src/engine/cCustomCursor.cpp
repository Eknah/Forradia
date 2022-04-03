// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "cCustomCursor.h"

namespace Forradia {

void cCustomCursor::Initialize() {
    SDL_ShowCursor(0);
}

void cCustomCursor::ResetForNewFrame() {
  cursorType = eCursorTypes::Default;
}

void cCustomCursor::Render() {
    auto mouse_pos_f = utilities.GetMousePositionF();
    auto cursor_size_f = utilities.ConvertToFloat(cursorSize);

    switch (cursorType) {
    case eCursorTypes::Default: {
      engine.DrawImage("CursorDefault", mouse_pos_f.x, mouse_pos_f.y,
                       cursor_size_f.width, cursor_size_f.height);
      break;
    }
    case eCursorTypes::Hovering: {
      engine.DrawImage("CursorHoveringClickable", mouse_pos_f.x, mouse_pos_f.y,
                       cursor_size_f.width, cursor_size_f.height);
      break;
    }
    }
  }

}  // namespace Forradia
