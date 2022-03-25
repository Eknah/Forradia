#pragma once
#include "CommonExternal.h"
#include "CUtilities.h"
#include "IEngine.h"
#include "ECursorTypes.h"
namespace Forradia
{

class CCustomCursor
{

public:
    CCustomCursor(IEngine& engine) : Engine(engine) {}

    inline void ResetForNewFrame()
    {
        CursorType = ECursorTypes::Default;
    }
    inline void Render()
    {
        auto mouse_pos_f = Utilities.GetMousePositionF();
        auto cursor_size_f = Utilities.ConvertToFloat(CursorSize);

        switch (CursorType)
        {
        case ECursorTypes::Default:
        {
            Engine.DrawImage("CursorDefault", mouse_pos_f.X, mouse_pos_f.Y, cursor_size_f.Width, cursor_size_f.Height);
            break;
        }
        case ECursorTypes::Hovering:
        {
            Engine.DrawImage("CursorHoveringClickable", mouse_pos_f.X, mouse_pos_f.Y, cursor_size_f.Width, cursor_size_f.Height);
            break;
        }
        }

    }

    ECursorTypes CursorType = ECursorTypes::Default;

private:
    IEngine& Engine;
    CUtilities Utilities;

    int CursorSize = 20;
};

}
