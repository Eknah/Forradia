#include "Common.h"
#include "CGameLoop.h"
#include "../Hidden/CEngine.h"
namespace Forradia
{
void CGameLoop::Run()
{
    bool quit = False;
    SDL_Event event;
    SDL_SetEventFilter((SDL_EventFilter)EventFilter, &Engine);
    while (!quit)
    {
        Engine.KeyboardHandler.ResetForNewFrame();
        Engine.MouseHandler.ResetForNewFrame();
        Engine.CustomCursor.ResetForNewFrame();
        while (SDL_PollEvent(&event) != 0)
        {
            switch (event.type)
            {
            case SDL_QUIT:
            {
                quit = true;
                break;
            }
            case SDL_KEYDOWN:
            {
                Engine.KeyboardHandler.DoKeyDown(event.key.keysym.sym);
                if (event.key.keysym.sym == SDLK_RETURN && Engine.KeyboardHandler.KeysBeingPressed.count(SDLK_LALT) > 0)
                    Engine.FullscreenController.ToggleFullscreen();
                break;
            }
            case SDL_KEYUP:
            {
                Engine.KeyboardHandler.DoKeyUp(event.key.keysym.sym);
                break;
            }
            case SDL_MOUSEBUTTONDOWN:
            {
                Engine.SceneManager.GetCurrentScene()->DoMouseDown(event.button.button);
                if (event.button.button == SDL_BUTTON_LEFT)
                    Engine.MouseHandler.LeftButtonDown = true;
                else if (event.button.button == SDL_BUTTON_RIGHT)
                    Engine.MouseHandler.RightButtonDown = true;
                break;
            }
            case SDL_MOUSEBUTTONUP:
            {
                Engine.SceneManager.GetCurrentScene()->DoMouseUp(event.button.button);
                if (event.button.button == SDL_BUTTON_LEFT)
                    Engine.MouseHandler.LeftButtonDown = false;
                else if (event.button.button == SDL_BUTTON_RIGHT)
                    Engine.MouseHandler.RightButtonDown = false;
                break;
            }
            case SDL_MOUSEWHEEL:
            {
                Engine.MouseHandler.WheelAmount = event.wheel.y;
                break;
            }
            }
        }
        Update();
        Render();
    }
}
void CGameLoop::Update()
{
    Engine.SceneManager.GetCurrentScene()->Update();
    Engine.FpsCounter.Update();
}
void CGameLoop::Render()
{
    glClear(GL_COLOR_BUFFER_BIT);
    Engine.SceneManager.GetCurrentScene()->Render();
    Engine.FpsCounter.Render();
    Engine.CustomCursor.Render();
    SDL_GL_SwapWindow(Engine.GWindow);

}
int CGameLoop::EventFilter(void* pthis, const SDL_Event* event)
{
    auto do_handle_event = event->type == SDL_WINDOWEVENT && event->window.event == SDL_WINDOWEVENT_SIZE_CHANGED;
    if (!do_handle_event) return 1;
    CEngine* Engine = (CEngine*)pthis;
    Engine->GameLoop.Update();
    glClear(GL_COLOR_BUFFER_BIT);
    Engine->SceneManager.GetCurrentScene()->Render();
    Engine->FpsCounter.Render();
    Engine->CustomCursor.Render();
    SDL_GL_SwapWindow(Engine->GWindow);
    return 1;
}
}
