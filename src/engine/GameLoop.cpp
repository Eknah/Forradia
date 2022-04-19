// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "GameLoop.h"

namespace Forradia
{

    void GameLoop::Run()
    {

        SDL_Event event;

        SDL_SetEventFilter((SDL_EventFilter)EventFilter, &e);

        while (!quit)
        {
            ResetForNewFrame();

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
                    e.keyboardHandler.KeyDown(event.key.keysym.sym);

                    e.fullscreenController.UpdateFullscreenToggling();

                    if (event.key.keysym.sym == SDLK_RETURN)
                    {
                        if (SDL_IsTextInputActive())
                        {
                            SDL_StopTextInput();
                        }
                        else
                        {
                            SDL_StartTextInput();
                            e.text.clear();
                            e.cursor = 0;
                        }
                    }

                    if (SDL_IsTextInputActive())
                    {
                        if (event.key.keysym.sym == SDLK_LEFT)
                        {
                            e.cursor = std::max(0, e.cursor - 1);
                        }
                        else if (event.key.keysym.sym == SDLK_RIGHT)
                        {
                            e.cursor =
                                std::min(static_cast<int>(e.text.size()), e.cursor + 1);
                        }
                        else if (event.key.keysym.sym == SDLK_BACKSPACE)
                        {
                            if (e.cursor > 0)
                            {
                                e.text.erase(e.cursor - 1, 1);
                                e.cursor = std::max(0, e.cursor - 1);
                            }
                        }
                        else if (event.key.keysym.sym == SDLK_DELETE)
                        {
                            if (e.cursor < e.text.size())
                            {
                                e.text.erase(e.cursor, 1);
                            }
                        }
                    }

                    e.sceneManager.GetCurrentScene()->KeyDown(event.key.keysym.sym);

                    break;
                }

                case SDL_KEYUP:
                {
                    e.keyboardHandler.KeyUp(event.key.keysym.sym);
                    e.sceneManager.GetCurrentScene()->KeyUp(event.key.keysym.sym);

                    break;
                }

                case SDL_MOUSEBUTTONDOWN:
                {
                    e.sceneManager.GetCurrentScene()->MouseDown(
                        event.button.button);

                    if (event.button.button == SDL_BUTTON_LEFT)
                    {
                        e.mouseHandler.leftButtonDown = true;
                        e.mouseHandler.SetLeftButtonBeenFired();
                    }
                    else if (event.button.button == SDL_BUTTON_RIGHT)
                    {
                        e.mouseHandler.rightButtonDown = true;
                        e.mouseHandler.SetRightButtonBeenFired();
                    }

                    break;
                }
                case SDL_TEXTINPUT:
                {
                    e.text.append(event.text.text);
                    e.cursor++;
                    break;
                }
                case SDL_TEXTEDITING:
                {
                    e.composition = event.edit.text;
                    e.cursor = event.edit.start;
                    e.selection_len = event.edit.length;
                    break;
                }

                case SDL_MOUSEBUTTONUP:
                {
                    e.sceneManager.GetCurrentScene()->MouseUp(event.button.button);

                    if (event.button.button == SDL_BUTTON_LEFT)
                        e.mouseHandler.leftButtonDown = false;
                    else if (event.button.button == SDL_BUTTON_RIGHT)
                        e.mouseHandler.rightButtonDown = false;

                    break;
                }

                case SDL_MOUSEWHEEL:
                {
                    *e.mouseHandler.wheelAmount = static_cast<float>(event.wheel.y);

                    break;
                }
                }
            }

            Update();
            Render();
        }
    }

    void GameLoop::ResetForNewFrame()
    {
        e.keyboardHandler.ResetForNewFrame();
        e.mouseHandler.ResetForNewFrame();
        e.customCursor.ResetForNewFrame();
    }

    void GameLoop::Update()
    {
        e.sceneManager.GetCurrentScene()->Update();
        e.fpsCounter.Update();
    }

    void GameLoop::Render()
    {
        glClear(GL_COLOR_BUFFER_BIT);

        e.sceneManager.GetCurrentScene()->Render();
        e.fpsCounter.Render();
        e.customCursor.Render();

        SDL_GL_SwapWindow(e.window.get());
    }

    int GameLoop::EventFilter(void* pthis, const SDL_Event* event)
    {
        auto do_handle_event = event->type == SDL_WINDOWEVENT &&
            event->window.event == SDL_WINDOWEVENT_SIZE_CHANGED;

        if (!do_handle_event)
            return 1;

        IEngine* e = reinterpret_cast<IEngine*>(pthis);

        e->gameLoop.Update();
        e->gameLoop.Render();

        return 1;
    }

}  // namespace Forradia
