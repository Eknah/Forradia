#include "CommonExternal.h"
#include "F_GuiWindowBase.h"
#include "../core/F_Engine.h"

namespace Forradia
{

void F_GuiWindowBase::Render()
{
    if (!Visible) return;

    Engine.FillRectangle(Palette.MediumBlue, Bounds.X, Bounds.Y, Bounds.Width, Bounds.Height);
    Engine.DrawRectangle(Palette.Black, Bounds.X, Bounds.Y, Bounds.Width, Bounds.Height);
    Engine.DrawString(Title, Palette.Black, Bounds.X + Margin, Bounds.Y + Margin);
    Engine.DrawLine(Palette.Black, Bounds.X, Bounds.Y + TitleBarHeight, Bounds.X + Bounds.Width, Bounds.Y + TitleBarHeight);

    RenderDerived();
}

void F_GuiWindowBase::Update()
{
    if (!IsBeingMoved) return;

    auto mouse_pos_f = Utilities.GetMousePositionF();
    auto delta_mouse_x = mouse_pos_f.X - StartMoveMousePosition.x;
    auto delta_mouse_y = mouse_pos_f.Y - StartMoveMousePosition.y;

    Bounds.X = StartMovePosition.x + delta_mouse_x;
    Bounds.Y = StartMovePosition.y + delta_mouse_y;
}

F_RectF F_GuiWindowBase::GetInteriorRect()
{
    auto x = Bounds.X + Margin;
    auto y = Bounds.Y + TitleBarHeight + Margin;
    auto width = Bounds.Width - 2 * Margin;
    auto height = Bounds.Height - TitleBarHeight - 2 * Margin;

    return { x, y, width, height };
}

bool F_GuiWindowBase::DoMouseDown(Uint8 mouseButton)
{
    if (!Visible) return false;

    auto mouse_pos_f = Utilities.GetMousePositionF();
    auto title_bar_rect = GetTitleBarRect();

    if (title_bar_rect.ContainsPoint(mouse_pos_f))
    {
        IsBeingMoved = true;
        StartMovePosition = { Bounds.X, Bounds.Y };
        StartMoveMousePosition = { mouse_pos_f.X, mouse_pos_f.Y };
    }

    DoMouseDownDerived(mouseButton);

    if (Bounds.ContainsPoint(mouse_pos_f)) return true;

    return false;
}

F_RectF F_GuiWindowBase::GetTitleBarRect()
{
    return { Bounds.X, Bounds.Y, Bounds.Width, TitleBarHeight};
}

void F_GuiWindowBase::DoMouseUp()
{
    IsBeingMoved = false;
}

}
