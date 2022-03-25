#pragma once
#include "../Hidden/CUtilities.h"
#include "../Hidden/CEngine.h"
#include "../Hidden/CRectF.h"

namespace Forradia
{

class CGuiWindowBase
{

public:

    CGuiWindowBase(CEngine& engine, std::string title, CRectF bounds) : Engine(engine), Title(title), Bounds(bounds) {}

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
    CRectF GetInteriorRect();

    // To implement in child
    virtual void DoMouseDownDerived(Uint8 mouseButton) = 0;
    virtual void RenderDerived() = 0;

    // Basic data
    const float Margin = 0.008;

    CEngine& Engine;

private:

    // Internal helpers
    CRectF GetTitleBarRect();

    // Composition
    CPalette Palette;
    CUtilities Utilities;

    // Basic data
    std::string Title;
    const float TitleBarHeight = 0.04f;

    // Dimensions
    CRectF Bounds;

    // Window movement
    bool IsBeingMoved = false;
    SDL_FPoint StartMovePosition = { -1, -1 };
    SDL_FPoint StartMoveMousePosition = { -1, -1 };

};

}
