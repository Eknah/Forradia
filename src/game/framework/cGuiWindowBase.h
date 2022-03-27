
#pragma once
#include "../engine/cUtilities.h"
#include "../engine/cEngine.h"
#include "../engine/cRectF.h"

namespace Forradia
{

class cGuiWindowBase
{

public:

    cGuiWindowBase(cEngine& engine, std::string title, cRectF bounds) : Engine(engine), Title(title), Bounds(bounds) {}

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
    cRectF GetInteriorRect();

    // To implement in child
    virtual void DoMouseDownDerived(Uint8 mouseButton) = 0;
    virtual void RenderDerived() = 0;

    // Basic data
    const float Margin = 0.008f;

    cEngine& Engine;

private:

    // Internal helpers
    cRectF GetTitleBarRect();

    // Composition
    cPalette Palette;
    cUtilities Utilities;

    // Basic data
    std::string Title;
    const float TitleBarHeight = 0.04f;

    // Dimensions
    cRectF Bounds;

    // Window movement
    bool IsBeingMoved = false;
    SDL_FPoint StartMovePosition = { -1, -1 };
    SDL_FPoint StartMoveMousePosition = { -1, -1 };

};

}
