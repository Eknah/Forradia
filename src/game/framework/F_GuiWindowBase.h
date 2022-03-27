
#pragma once
#include "../core/F_Utilities.h"
#include "../core/F_Engine.h"
#include "../core/F_RectF.h"

namespace Forradia
{

class F_GuiWindowBase
{

public:

    F_GuiWindowBase(F_Engine& engine, std::string title, F_RectF bounds) : Engine(engine), Title(title), Bounds(bounds) {}

    // Looped operations
    void Render();
    void Update();

    // Fired by events
    bool DoMouseDown(Uint8 mouseButton);
    void DoMouseUp();

    // Basic data
    bool Visible = false;

protected:

    // Internal helpers
    F_RectF GetInteriorRect();

    // To implement in child
    virtual void DoMouseDownDerived(Uint8 mouseButton) = 0;
    virtual void RenderDerived() = 0;

    // Basic data
    const float Margin = 0.008f;

    F_Engine& Engine;

private:

    // Internal helpers
    F_RectF GetTitleBarRect();

    // Composition
    F_Palette Palette;
    F_Utilities Utilities;

    // Basic data
    std::string Title;
    const float TitleBarHeight = 0.04f;

    // Dimensions
    F_RectF Bounds;

    // Window movement
    bool IsBeingMoved = false;
    SDL_FPoint StartMovePosition = { -1, -1 };
    SDL_FPoint StartMoveMousePosition = { -1, -1 };

};

}
