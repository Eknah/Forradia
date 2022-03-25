#pragma once
#include "../Hidden/CUtilities.h"
namespace Forradia
{

class CGuiWindowBase
{

public:

    CGuiWindowBase(CEngine& engine, String title, CRectF bounds) : Engine(engine), Title(title), Bounds(bounds) {}

    void Render();
    void Update();
    bool DoMouseDown(Uint8 mouseButton);
    void DoMouseUp();

    bool Visible = false;

protected:
    CRectF GetInteriorRect();
    virtual void DoMouseDownDerived(Uint8 mouseButton) = 0;
    virtual void RenderDerived() = 0;

    CEngine& Engine;

    const float Margin = 0.008;

private:

    CRectF GetTitleBarRect();

    CPalette Palette;

    String Title;

    CRectF Bounds;
    bool IsBeingMoved = false;
    CUtilities Utilities;
    SDL_FPoint StartMovePosition = { -1, -1 };
    SDL_FPoint StartMoveMousePosition = { -1, -1 };

    const float TitleBarHeight = 0.04f;

};

}
