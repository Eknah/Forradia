#include "CommonExternal.h"
#include "CGameLoop.h"
#include "../hidden/CEngine.h"

namespace Forradia
{

/**
 * @brief Loops all game loop processes until user quits game.
 *
 * Before loop:
 * Initializes game loop variables.
 * Sets event filter to enable game update and rendering during window resize.
 *
 * In loop:
 * Resets all engine components that need to be reset for each frame.
 * Poll events and handle them.
 * Update game.
 * Render game.
 *
 */
void CGameLoop::Run()
{
    bool quit = false;
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

/**
 * @brief Update currently displayed scene and fps counter.
 */
void CGameLoop::Update()
{
    Engine.SceneManager.GetCurrentScene()->Update();
    Engine.FpsCounter.Update();
}

/**
 * @brief Render currently displayed scene and general engine components.
 */
void CGameLoop::Render()
{
    glClear(GL_COLOR_BUFFER_BIT);

    Engine.SceneManager.GetCurrentScene()->Render();
    Engine.FpsCounter.Render();
    Engine.CustomCursor.Render();

    SDL_GL_SwapWindow(Engine.Window.get());
}

/**
 * @brief Enables game updating and rendering during window resize.
 * @param Pointer to the Engine-object.
 * @param Pointer to triggering event information.
 * @return See detailed description.
 *
 * From the SDL documentation:
 * If the filter function returns 1 when called, then the event will be added to the internal queue.
 * If it returns 0, then the event will be dropped from the queue, but the internal state will still be updated.
 * This allows selective filtering of dynamically arriving events.
 */
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

    SDL_GL_SwapWindow(Engine->Window.get());

    return 1;
}

}