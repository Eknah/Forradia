#pragma once
#include "../hidden/CEngine.h"
#include "../hidden/CUtilities.h"
#include "CGuiMinimap.h"
#include "framework/CGuiWindowBase.h"

namespace Forradia
{

class CGui
{

public:

    CGui(CEngine& engine) : Engine(engine), GuiMinimap(engine) {}

    void Initialize();
    void Update();
    void Render();
    bool DoMouseDown(Uint8 mouseButton);
    void DoMouseUp();

    UMap<std::string, UPtr<CGuiWindowBase>> Windows;

private:

    CEngine& Engine;

    CGuiMinimap GuiMinimap;
    std::vector<std::string> TextBoxText = { "You have entered the world of Forradia" };
    const float TextBoxMargin = 0.005f;

    CUtilities Utilities;

    const float ButtonWidth = 0.15f;
    const float ButtonHeight = 0.03f;
    const float TextBoxWidth = 3 * ButtonWidth;
    const float TextBoxHeight = 0.15f;

    CRectF BoundsButtonInventory = { 0.5f - ButtonWidth / 2, 1.0f - ButtonHeight, ButtonWidth, ButtonHeight };
    CRectF BoundsButtonCharacter = { 0.5f - ButtonWidth / 2 - ButtonWidth, 1.0f - ButtonHeight, ButtonWidth, ButtonHeight };
    CRectF BoundsButtonSystem = { 0.5f - ButtonWidth / 2 + ButtonWidth, 1.0f - ButtonHeight, ButtonWidth, ButtonHeight };
    CRectF BoundsTextBox = { 0.5f - TextBoxWidth / 2, 1.0f - ButtonHeight - TextBoxHeight, TextBoxWidth, TextBoxHeight };

};

}