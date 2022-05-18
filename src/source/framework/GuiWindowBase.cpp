// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "GuiWindowBase.h"
#include "Engine.h"

namespace Forradia
{
    void GuiWindowBase::Render()
    {
        using namespace Palette;

        if (!visible) return;

        e.FillRect(MediumBlue, bounds.x, bounds.y, bounds.w, bounds.h);
        e.DrawRect(Black, bounds.x, bounds.y, bounds.w, bounds.h);
        e.DrawString(title, Black, bounds.x + margin, bounds.y + margin);
        e.DrawLine(Black, bounds.x, bounds.y + topBarHeight, bounds.x + bounds.w, bounds.y + topBarHeight);

        RenderEx();
    }

    void GuiWindowBase::Update()
    {
        if (!beingMoved) return;

        auto mousePosF = utils.GetMousePosF();
        auto deltaMouseX = mousePosF.x - startMoveMousePos.x;
        auto deltaMouseY = mousePosF.y - startMoveMousePos.y;

        bounds.x = startMovePos.x + deltaMouseX;
        bounds.y = startMovePos.y + deltaMouseY;
    }

    RectF GuiWindowBase::GetInnerBounds()
    {
        auto x = bounds.x + margin;
        auto y = bounds.y + topBarHeight + margin;
        auto w = bounds.w - 2 * margin;
        auto h = bounds.h - topBarHeight - 2 * margin;

        return { x, y, w, h };
    }

    bool GuiWindowBase::MouseDown(Uint8 button)
    {
        if (!visible) return false;

        auto mousePosF = utils.GetMousePosF();
        auto titleBarBounds = GetTopBarBounds();

        if (titleBarBounds.Contains(mousePosF))
        {
            beingMoved = true;
            startMovePos = { bounds.x, bounds.y };
            startMoveMousePos = { mousePosF.x, mousePosF.y };
        }

        MouseDownEx(button);

        if (bounds.Contains(mousePosF)) return true;

        return false;
    }

    RectF GuiWindowBase::GetTopBarBounds()
    {
        return { bounds.x, bounds.y, bounds.w, topBarHeight };
    }

    void GuiWindowBase::MouseUp()
    {
        beingMoved = false;
    }
}