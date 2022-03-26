
#pragma once
#include "CommonExternal.h"
#include "F_Utilities.h"
#include "F_IEngine.h"
#include "F_ECursorTypes.h"

namespace Forradia
{

class F_CustomCursor
{

public:

    F_CustomCursor(F_IEngine& engine) : Engine(engine) {}

    inline void Initialize()
    {
        SDL_ShowCursor(0);
    }

    inline void ResetForNewFrame()
    {
        CursorType = F_ECursorTypes::Default;
    }

    inline void Render()
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

    F_ECursorTypes CursorType = F_ECursorTypes::Default;

private:

    F_IEngine& Engine;
    F_Utilities Utilities;

    int CursorSize = 20;
};

}
