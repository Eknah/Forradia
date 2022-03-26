
#pragma once
#include "../core/F_IGameLoop.h"
#include "../core/F_IEngine.h"

namespace Forradia
{

class F_GameLoop : public F_IGameLoop
{

public:

    F_GameLoop(F_IEngine& engine) : F_IGameLoop(engine) {}

    // Before loop:
    // Initializes game loop variables
    // Sets event filter to enable game update and rendering during window resize
    //
    // In loop:
    // Resets all engine components that need to be reset for each frame
    // Poll events and handle them
    // Update game
    // Render game

    inline void Run() override
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

                    Engine.FullscreenController.UpdateFullscreenToggling();

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

private:

    // ---- Looped functions ----

    // Update currently displayed scene and fps counter.

    inline void Update()
    {
        Engine.SceneManager.GetCurrentScene()->Update();
        Engine.FpsCounter.Update();
    }

    // Render currently displayed scene and general engine components.

    inline void Render()
    {
        glClear(GL_COLOR_BUFFER_BIT);

        Engine.SceneManager.GetCurrentScene()->Render();
        Engine.FpsCounter.Render();
        Engine.CustomCursor.Render();

        SDL_GL_SwapWindow(Engine.Window.get());
    }

    // Enables game updating and rendering during window resize.

    inline static int EventFilter(void* pthis, const SDL_Event* event)
    {
        auto do_handle_event = event->type == SDL_WINDOWEVENT && event->window.event == SDL_WINDOWEVENT_SIZE_CHANGED;

        if (!do_handle_event) return 1;

        F_IEngine* Engine = (F_IEngine*)pthis;

        Engine->GameLoop.Update();
        Engine->GameLoop.Render();

        return 1;
    }

};

}