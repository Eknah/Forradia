// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "cGameLoop.h"

namespace Forradia {

void cGameLoop::Run() {
    bool quit = false;
    SDL_Event event;

    SDL_SetEventFilter((SDL_EventFilter)EventFilter, &Engine);

    while (!quit) {
      ResetForNewFrame();

      while (SDL_PollEvent(&event) != 0) {
        switch (event.type) {
        case SDL_QUIT: {
          quit = true;

          break;
        }

        case SDL_KEYDOWN: {
          Engine.KeyboardHandler.DoKeyDown(event.key.keysym.sym);

          Engine.FullscreenController.UpdateFullscreenToggling();

          break;
        }

        case SDL_KEYUP: {
          Engine.KeyboardHandler.DoKeyUp(event.key.keysym.sym);

          break;
        }

        case SDL_MOUSEBUTTONDOWN: {
          Engine.SceneManager.GetCurrentScene()->DoMouseDown(
              event.button.button);

          if (event.button.button == SDL_BUTTON_LEFT) {
            Engine.MouseHandler.LeftButtonDown = true;
              Engine.MouseHandler.SetLeftButtonBeenFired();
          } else if (event.button.button == SDL_BUTTON_RIGHT) {
            Engine.MouseHandler.RightButtonDown = true;
              Engine.MouseHandler.SetRightButtonBeenFired();
          }

          break;
        }

        case SDL_MOUSEBUTTONUP: {
          Engine.SceneManager.GetCurrentScene()->DoMouseUp(event.button.button);

          if (event.button.button == SDL_BUTTON_LEFT)
            Engine.MouseHandler.LeftButtonDown = false;
          else if (event.button.button == SDL_BUTTON_RIGHT)
            Engine.MouseHandler.RightButtonDown = false;

          break;
        }

        case SDL_MOUSEWHEEL: {
          *Engine.MouseHandler.WheelAmount = static_cast<float>(event.wheel.y);

          break;
        }
        }
      }

      Update();
      Render();
    }
  }

void cGameLoop::ResetForNewFrame() {
      Engine.KeyboardHandler.ResetForNewFrame();
      Engine.MouseHandler.ResetForNewFrame();
      Engine.CustomCursor.ResetForNewFrame();
  }

void cGameLoop::Update() {
    Engine.SceneManager.GetCurrentScene()->Update();
    Engine.FpsCounter.Update();
  }

void cGameLoop::Render() {
    glClear(GL_COLOR_BUFFER_BIT);

    Engine.SceneManager.GetCurrentScene()->Render();
    Engine.FpsCounter.Render();
    Engine.CustomCursor.Render();

    SDL_GL_SwapWindow(Engine.Window.get());
  }

int cGameLoop::EventFilter(void *pthis, const SDL_Event *event) {
    auto do_handle_event = event->type == SDL_WINDOWEVENT &&
                           event->window.event == SDL_WINDOWEVENT_SIZE_CHANGED;

    if (!do_handle_event)
      return 1;

    iEngine *Engine = reinterpret_cast<iEngine *>(pthis);

    Engine->GameLoop.Update();
    Engine->GameLoop.Render();

    return 1;
  }

}  // namespace Forradia
