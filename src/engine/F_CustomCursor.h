
#pragma once
#include "CommonExternal.h"
#include "F_IEngine.h"
#include "F_ICustomCursor.h"

namespace Forradia
{

class F_CustomCursor : public F_ICustomCursor
{

public:

    F_CustomCursor(F_IEngine& engine) : F_ICustomCursor(engine) {}

    inline void Initialize() override
    {
        SDL_ShowCursor(0);
    }

    inline void ResetForNewFrame() override
    {
        CursorType = F_ECursorTypes::Default;
    }

    inline void Render() override
    {
        auto mouse_pos_f = Utilities.GetMousePositionF();
        auto cursor_size_f = Utilities.ConvertToFloat(CursorSize);

        switch (CursorType)
        {

        case F_ECursorTypes::Default:
        {
            Engine.DrawImage("CursorDefault", mouse_pos_f.X, mouse_pos_f.Y, cursor_size_f.Width, cursor_size_f.Height);
            break;
        }
        case F_ECursorTypes::Hovering:
        {
            Engine.DrawImage("CursorHoveringClickable", mouse_pos_f.X, mouse_pos_f.Y, cursor_size_f.Width, cursor_size_f.Height);
            break;
        }

        }

    }

};

}
