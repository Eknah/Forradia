#include "Pch.h"
#include "CGuiWindowBase.h"
#include "../Hidden/CEngine.h"
namespace Forradia
{
	void CGuiWindowBase::Render()
	{
		if (!Visible) return;
		Engine.FillRectangle(Palette.MediumBlue, Bounds.X, Bounds.Y, Bounds.Width, Bounds.Height);
		Engine.DrawRectangle(Palette.Black, Bounds.X, Bounds.Y, Bounds.Width, Bounds.Height);
		Engine.DrawString(Title, Palette.Black, Bounds.X + Margin, Bounds.Y + Margin);
		Engine.DrawLine(Palette.Black, Bounds.X, Bounds.Y + TitleBarHeight, Bounds.X + Bounds.Width, Bounds.Y + TitleBarHeight);
		RenderDerived();
	}
	void CGuiWindowBase::Update()
	{
		if (!IsBeingMoved) return;
		auto mouse_pos_f = Utilities.GetMousePositionF();
		auto delta_mouse_x = mouse_pos_f.X - StartMoveMousePosition.x;
		auto delta_mouse_y = mouse_pos_f.Y - StartMoveMousePosition.y;
		Bounds.X = StartMovePosition.x + delta_mouse_x;
		Bounds.Y = StartMovePosition.y + delta_mouse_y;
	}
	CRectF CGuiWindowBase::GetInteriorRect()
	{
		auto x = Bounds.X + Margin;
		auto y = Bounds.Y + TitleBarHeight + Margin;
		auto width = Bounds.Width - 2 * Margin;
		auto height = Bounds.Height - TitleBarHeight - 2 * Margin;
		return { x, y, width, height };
	}
	bool CGuiWindowBase::DoMouseDown(Uint8 mouseButton)
	{
		if (!Visible) return False;
		auto mouse_pos_f = Utilities.GetMousePositionF();
		auto title_bar_rect = GetTitleBarRect();
		if (title_bar_rect.ContainsPoint(mouse_pos_f))
		{
			IsBeingMoved = True;
			StartMovePosition = { Bounds.X, Bounds.Y };
			StartMoveMousePosition = { mouse_pos_f.X, mouse_pos_f.Y };
		}
		DoMouseDownDerived(mouseButton);
		if (Bounds.ContainsPoint(mouse_pos_f))
			return True;
		return False;
	}
	CRectF CGuiWindowBase::GetTitleBarRect()
	{
		return { Bounds.X, Bounds.Y, Bounds.Width, TitleBarHeight};
	}
	void CGuiWindowBase::DoMouseUp()
	{
		IsBeingMoved = False;
	}
}
