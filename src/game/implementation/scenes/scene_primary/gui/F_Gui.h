#pragma once
#include "../core/F_Engine.h"
#include "../core/F_Utilities.h"
#include "F_GuiMinimap.h"
#include "framework/F_GuiWindowBase.h"

namespace Forradia
{

class F_Gui
{

public:

    F_Gui(F_Engine& engine) : Engine(engine), GuiMinimap(engine) {}

    void Initialize();
    void Update();
    void Render();
    bool DoMouseDown(Uint8 mouseButton);
    void DoMouseUp();

    UMap<std::string, UPtr<F_GuiWindowBase>> Windows;

private:

    F_Engine& Engine;

    F_GuiMinimap GuiMinimap;
    std::vector<std::string> TextBoxText = { "You have entered the world of Forradia" };
    const float TextBoxMargin = 0.005f;

    F_Utilities Utilities;

    const float ButtonWidth = 0.15f;
    const float ButtonHeight = 0.03f;
    const float TextBoxWidth = 3 * ButtonWidth;
    const float TextBoxHeight = 0.15f;

    F_RectF BoundsButtonInventory = { 0.5f - ButtonWidth / 2, 1.0f - ButtonHeight, ButtonWidth, ButtonHeight };
    F_RectF BoundsButtonCharacter = { 0.5f - ButtonWidth / 2 - ButtonWidth, 1.0f - ButtonHeight, ButtonWidth, ButtonHeight };
    F_RectF BoundsButtonSystem = { 0.5f - ButtonWidth / 2 + ButtonWidth, 1.0f - ButtonHeight, ButtonWidth, ButtonHeight };
    F_RectF BoundsTextBox = { 0.5f - TextBoxWidth / 2, 1.0f - ButtonHeight - TextBoxHeight, TextBoxWidth, TextBoxHeight };

};

}
