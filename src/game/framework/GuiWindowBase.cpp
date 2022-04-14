// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "GuiWindowBase.h"
#include "../engine/Engine.h"

namespace Forradia
{

    void GuiWindowBase::Render()
    {
        if (!visible) return;

        e.FillRect(palette.mediumBlue, bounds.x, bounds.y, bounds.w, bounds.h);
        e.DrawRect(palette.black, bounds.x, bounds.y, bounds.w, bounds.h);
        e.DrawString(title, palette.black, bounds.x + margin, bounds.y + margin);
        e.DrawLine(palette.black, bounds.x, bounds.y + topBarHeight, bounds.x + bounds.w, bounds.y + topBarHeight);

        RenderDerived();
    }

    void GuiWindowBase::Update()
    {
        if (!isBeingMoved) return;

        auto mousePosF = utils.GetMousePosF();
        auto deltaMouseX = mousePosF.x - startMoveMousePos.x;
        auto deltaMouseY = mousePosF.y - startMoveMousePos.y;

        bounds.x = startMovePos.x + deltaMouseX;
        bounds.y = startMovePos.y + deltaMouseY;
    }

    RectF GuiWindowBase::GetInteriorBounds()
    {
        auto x = bounds.x + margin;
        auto y = bounds.y + topBarHeight + margin;
        auto width = bounds.w - 2 * margin;
        auto height = bounds.h - topBarHeight - 2 * margin;

        return { x, y, width, height };
    }

    bool GuiWindowBase::DoMouseDown(Uint8 button)
    {
        if (!visible) return false;

        auto mousePosF = utils.GetMousePosF();
        auto titleBarBounds = GetTopBarBounds();

        if (titleBarBounds.Contains(mousePosF))
        {
            isBeingMoved = true;
            startMovePos = { bounds.x, bounds.y };
            startMoveMousePos = { mousePosF.x, mousePosF.y };
        }

        DoMouseDownDerived(button);

        if (bounds.Contains(mousePosF)) return true;

        return false;
    }

    RectF GuiWindowBase::GetTopBarBounds()
    {
        return { bounds.x, bounds.y, bounds.w, topBarHeight };
    }

    void GuiWindowBase::DoMouseUp()
    {
        isBeingMoved = false;
    }

}  // namespace Forradia
