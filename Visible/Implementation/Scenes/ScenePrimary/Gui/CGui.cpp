#include "Common.h"
#include "CGui.h"
#include "../Hidden/CEngine.h"
#include "CGuiWindowInventory.h"
namespace Forradia
{
void CGui::InitializeEngine()
{
    Windows.clear();
    Windows.insert({ "Inventory", std::make_unique<CGuiWindowInventory>(Engine, "Inventory", CRectF {0.1f, 0.1f, 0.2f, 0.7f}) });
}
void CGui::Update()
{
    auto mouse_position_f = Utilities.GetMousePositionF();
    if (BoundsButtonInventory.ContainsPoint(mouse_position_f))
        Engine.CustomCursor.CursorType = ECursorTypes::Hovering;
    if (BoundsButtonCharacter.ContainsPoint(mouse_position_f))
        Engine.CustomCursor.CursorType = ECursorTypes::Hovering;
    if (BoundsButtonSystem.ContainsPoint(mouse_position_f))
        Engine.CustomCursor.CursorType = ECursorTypes::Hovering;
    for (auto& [key, window] : Windows)
        window->Update();
}
void CGui::Render()
{
    GuiMinimap.Render();

    auto mouse_position_f = Utilities.GetMousePositionF();
    if (BoundsButtonInventory.ContainsPoint(mouse_position_f))
        Engine.FillRectangle({ 100,200,255,100 }, BoundsButtonInventory.X, BoundsButtonInventory.Y, BoundsButtonInventory.Width, BoundsButtonInventory.Height);
    else
        Engine.FillRectangle({ 0,150,255,100 }, BoundsButtonInventory.X, BoundsButtonInventory.Y, BoundsButtonInventory.Width, BoundsButtonInventory.Height);
    Engine.DrawRectangle({ 255,255,255,100 }, BoundsButtonInventory.X, BoundsButtonInventory.Y, BoundsButtonInventory.Width, BoundsButtonInventory.Height);
    Engine.DrawString("Inventory [F2]", { 255,255,255,255 }, BoundsButtonInventory.X + BoundsButtonInventory.Width / 2, BoundsButtonInventory.Y + BoundsButtonInventory.Height / 2, true);
    if (BoundsButtonCharacter.ContainsPoint(mouse_position_f))
        Engine.FillRectangle({ 100,200,255,100 }, BoundsButtonCharacter.X, BoundsButtonCharacter.Y, BoundsButtonCharacter.Width, BoundsButtonCharacter.Height);
    else
        Engine.FillRectangle({ 0,150,255,100 }, BoundsButtonCharacter.X, BoundsButtonCharacter.Y, BoundsButtonCharacter.Width, BoundsButtonCharacter.Height);
    Engine.DrawRectangle({ 255,255,255,100 }, BoundsButtonCharacter.X, BoundsButtonCharacter.Y, BoundsButtonCharacter.Width, BoundsButtonCharacter.Height);
    Engine.DrawString("Character [F1]", { 255,255,255,255 }, BoundsButtonCharacter.X + BoundsButtonCharacter.Width / 2, BoundsButtonCharacter.Y + BoundsButtonCharacter.Height / 2, true);
    if (BoundsButtonSystem.ContainsPoint(mouse_position_f))
        Engine.FillRectangle({ 100,200,255,100 }, BoundsButtonSystem.X, BoundsButtonSystem.Y, BoundsButtonSystem.Width, BoundsButtonSystem.Height);
    else
        Engine.FillRectangle({ 0,150,255,100 }, BoundsButtonSystem.X, BoundsButtonSystem.Y, BoundsButtonSystem.Width, BoundsButtonSystem.Height);
    Engine.DrawRectangle({ 255,255,255,100 }, BoundsButtonSystem.X, BoundsButtonSystem.Y, BoundsButtonSystem.Width, BoundsButtonSystem.Height);
    Engine.DrawString("System [F3]", { 255,255,255,255 }, BoundsButtonSystem.X + BoundsButtonSystem.Width / 2, BoundsButtonSystem.Y + BoundsButtonSystem.Height / 2, true);
    Engine.FillRectangle({ 0,150,255,100 }, BoundsTextBox.X, BoundsTextBox.Y, BoundsTextBox.Width, BoundsTextBox.Height);
    Engine.DrawRectangle({ 255,255,255,100 }, BoundsTextBox.X, BoundsTextBox.Y, BoundsTextBox.Width, BoundsTextBox.Height);
    auto textbox_text_x = BoundsTextBox.X + TextBoxMargin;
    auto textbox_text_y = BoundsTextBox.Y + TextBoxMargin;
    Engine.DrawString(TextBoxText.at(0), {255, 255, 255, 255}, textbox_text_x, textbox_text_y);
    for (auto& [key, window] : Windows)
        window->Render();
}
bool CGui::DoMouseDown(Uint8 mouseButton)
{
    for (auto& [key, window] : Windows)
    {
        auto clicked_in_window = window->DoMouseDown(mouseButton);
        if (clicked_in_window) return True;
    }
    auto mouse_position_f = Utilities.GetMousePositionF();
    if (BoundsButtonInventory.ContainsPoint(mouse_position_f))
    {
        Windows.at("Inventory")->Visible = !Windows.at("Inventory")->Visible;
        return True;
    }
    return False;
}
void CGui::DoMouseUp()
{
    for (auto& [key, window] : Windows)
        window->DoMouseUp();
}
}
