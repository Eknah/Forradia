
#include "F_GuiWindowInventory.h"
#include "../engine/F_Engine.h"

namespace Forradia
{

void F_GuiWindowInventory::RenderDerived()
{
    auto canvas_size = Utilities.GetCanvasSize();
    auto aspect_ratio = float(canvas_size.Width) / canvas_size.Height;
    auto rect_interior = GetInteriorRect();

    Engine.FillRectangle(Palette.Wheat, rect_interior.X, rect_interior.Y, rect_interior.Width, rect_interior.Height);

    auto slot_size = rect_interior.Width / NumSlotCols - Margin;
    auto num_slow_rows = rect_interior.Height / ((slot_size + Margin) * aspect_ratio);
    auto i = 0;

    auto mouse_position = Utilities.GetMousePositionI();
    auto mouse_x_rel = (double)mouse_position.X / canvas_size.Width;
    auto mouse_y_rel = (double)mouse_position.Y / canvas_size.Height;

    for (auto Y = 0; Y < num_slow_rows; Y++)
    {
        for (auto X = 0; X < NumSlotCols; X++)
        {
            auto x_pos = rect_interior.X + X * (slot_size + Margin);
            auto y_pos = rect_interior.Y + Y * (slot_size * aspect_ratio + Margin);

            if (Engine.Player.GetModule<F_ModuleInventory>().Objects.count(i) > 0)
            {
                if (Engine.Player.GetModule<F_ModuleObjectUsage>().ObjectBeingUsed == Engine.Player.GetModule<F_ModuleInventory>().Objects.at(i))
                    Engine.DrawImage("ObjectSelected", x_pos, y_pos, slot_size, slot_size * aspect_ratio);
                else
                    Engine.DrawImage("ObjectBackgroundShadow", x_pos, y_pos, slot_size, slot_size * aspect_ratio);

                Engine.DrawImage(Engine.Player.GetModule<F_ModuleInventory>().Objects.at(i)->ObjectType, x_pos, y_pos, slot_size, slot_size * aspect_ratio);
            }

            i++;
        }
    }
}

void F_GuiWindowInventory::DoMouseDownDerived(Uint8 mouseButton)
{
    if (mouseButton != SDL_BUTTON_RIGHT) return;
    Engine.Player.GetModule<F_ModuleObjectUsage>().ObjectBeingUsed = nullptr;

    auto canvas_size = Utilities.GetCanvasSize();
    auto aspect_ratio = double(canvas_size.Width) / canvas_size.Height;
    auto rect_interior = GetInteriorRect();

    auto slot_size = rect_interior.Width / NumSlotCols - Margin;
    auto num_slow_rows = rect_interior.Height / ((slot_size + Margin) * aspect_ratio);
    auto i = 0;

    auto mouse_position = Utilities.GetMousePositionI();
    auto mouse_x_rel = (double)mouse_position.X / canvas_size.Width;
    auto mouse_y_rel = (double)mouse_position.Y / canvas_size.Height;

    for (auto Y = 0; Y < num_slow_rows; Y++)
    {
        for (auto X = 0; X < NumSlotCols; X++)
        {
            auto x_pos = rect_interior.X + X * (slot_size + Margin);
            auto y_pos = rect_interior.Y + Y * (slot_size * aspect_ratio + Margin);

            if (Engine.Player.GetModule<F_ModuleInventory>().Objects.count(i) > 0)
            {
                if (mouse_x_rel >= x_pos && mouse_y_rel >= y_pos && mouse_x_rel < x_pos + slot_size && mouse_y_rel < y_pos + slot_size * aspect_ratio)
                {
                Engine.Player.GetModule<F_ModuleObjectUsage>().ObjectBeingUsed = Engine.Player.GetModule<F_ModuleInventory>().Objects.at(i);
                return;
                }


            }

            i++;
        }
    }
}

}
