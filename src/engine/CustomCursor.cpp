// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "CustomCursor.h"

namespace Forradia
{

    void CustomCursor::Initialize()
    {
        SDL_ShowCursor(0);
    }

    void CustomCursor::ResetForNewFrame()
    {
        cursorType = CursorTypes::Default;
    }

    void CustomCursor::Render()
    {
        auto mousePosF = utils.GetMousePosF();
        auto cursorSizeF = utils.ConvertToFloat(cursorSize);

        switch (cursorType)
        {
        case CursorTypes::Default:
        {
            e.DrawImage("CursorDefault", mousePosF.x, mousePosF.y,
                cursorSizeF.width, cursorSizeF.height);
            break;
        }
        case CursorTypes::Hovering:
        {
            e.DrawImage("CursorHoveringClickable", mousePosF.x, mousePosF.y,
                cursorSizeF.width, cursorSizeF.height);
            break;
        }
        }
    }

}  // namespace Forradia
