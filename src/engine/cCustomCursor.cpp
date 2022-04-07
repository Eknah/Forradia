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
    auto mousePosF = utilities.GetMousePositionF();
    auto cursorSizeF = utilities.ConvertToFloat(cursorSize);

    switch (cursorType) {
    case eCursorTypes::Default: {
      engine.DrawImage("CursorDefault", mousePosF.x, mousePosF.y,
                       cursorSizeF.width, cursorSizeF.height);
      break;
    }
    case eCursorTypes::Hovering: {
      engine.DrawImage("CursorHoveringClickable", mousePosF.x, mousePosF.y,
                       cursorSizeF.width, cursorSizeF.height);
      break;
    }
    }
  }

}  // namespace Forradia
