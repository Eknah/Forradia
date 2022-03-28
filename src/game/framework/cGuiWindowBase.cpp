// Copyright (C) 2022  Andreas Åkerberg

#include "CommonExternal.h"
#include "cGuiWindowBase.h"
#include "../engine/cEngine.h"

namespace Forradia
{

void cGuiWindowBase::Render()
{
    if (!Visible) return;

    Engine.FillRectangle(Palette.MediumBlue, Bounds.X, Bounds.Y, Bounds.Width, Bounds.Height);
    Engine.DrawRectangle(Palette.Black, Bounds.X, Bounds.Y, Bounds.Width, Bounds.Height);
    Engine.DrawString(Title, Palette.Black, Bounds.X + Margin, Bounds.Y + Margin);
    Engine.DrawLine(Palette.Black, Bounds.X, Bounds.Y + TitleBarHeight, Bounds.X + Bounds.Width, Bounds.Y + TitleBarHeight);

    RenderDerived();
}

void cGuiWindowBase::Update()
{
    if (!IsBeingMoved) return;

    auto MousePosF = Utilities.GetMousePositionF();
    auto DeltaMouseX = MousePosF.X - StartMoveMousePosition.x;
    auto DeltaMouseY = MousePosF.Y - StartMoveMousePosition.y;

    Bounds.X = StartMovePosition.x + DeltaMouseX;
    Bounds.Y = StartMovePosition.y + DeltaMouseY;
}

cRectF cGuiWindowBase::GetInteriorBounds()
{
    auto X = Bounds.X + Margin;
    auto Y = Bounds.Y + TitleBarHeight + Margin;
    auto Width = Bounds.Width - 2 * Margin;
    auto Height = Bounds.Height - TitleBarHeight - 2 * Margin;

    return { X, Y, Width, Height };
}

bool cGuiWindowBase::DoMouseDown(Uint8 MouseButton)
{
    if (!Visible) return false;

    auto MousePosF = Utilities.GetMousePositionF();
    auto TitleBarBounds = GetTitleBarBounds();

    if (TitleBarBounds.ContainsPoint(MousePosF))
    {
        IsBeingMoved = true;
        StartMovePosition = { Bounds.X, Bounds.Y };
        StartMoveMousePosition = { MousePosF.X, MousePosF.Y };
    }

    DoMouseDownDerived(MouseButton);

    if (Bounds.ContainsPoint(MousePosF)) return true;

    return false;
}

cRectF cGuiWindowBase::GetTitleBarBounds()
{
    return { Bounds.X, Bounds.Y, Bounds.Width, TitleBarHeight};
}

void cGuiWindowBase::DoMouseUp()
{
    IsBeingMoved = false;
}

}
