// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "CommonExternal.h"
#include "iCustomCursor.h"
#include "iEngine.h"

namespace Forradia {

class cCustomCursor : public iCustomCursor {
 public:
  cCustomCursor(iEngine &engine) : iCustomCursor(engine) {}

  inline void Initialize() override { SDL_ShowCursor(0); }

  inline void ResetForNewFrame() override {
    CursorType = eCursorTypes::Default;
  }

  inline void Render() override {
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
};

}  // namespace Forradia
