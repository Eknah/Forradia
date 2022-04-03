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
          Engine.keyboardHandler.DoKeyDown(event.key.keysym.sym);

          Engine.fullscreenController.UpdateFullscreenToggling();

          break;
        }

        case SDL_KEYUP: {
          Engine.keyboardHandler.DoKeyUp(event.key.keysym.sym);

          break;
        }

        case SDL_MOUSEBUTTONDOWN: {
          Engine.sceneManager.GetCurrentScene()->DoMouseDown(
              event.button.button);

          if (event.button.button == SDL_BUTTON_LEFT) {
            Engine.mouseHandler.leftButtonDown = true;
              Engine.mouseHandler.SetLeftButtonBeenFired();
          } else if (event.button.button == SDL_BUTTON_RIGHT) {
            Engine.mouseHandler.rightButtonDown = true;
              Engine.mouseHandler.SetRightButtonBeenFired();
          }

          break;
        }

        case SDL_MOUSEBUTTONUP: {
          Engine.sceneManager.GetCurrentScene()->DoMouseUp(event.button.button);

          if (event.button.button == SDL_BUTTON_LEFT)
            Engine.mouseHandler.leftButtonDown = false;
          else if (event.button.button == SDL_BUTTON_RIGHT)
            Engine.mouseHandler.rightButtonDown = false;

          break;
        }

        case SDL_MOUSEWHEEL: {
          *Engine.mouseHandler.wheelAmount = static_cast<float>(event.wheel.y);

          break;
        }
        }
      }

      Update();
      Render();
    }
  }

void cGameLoop::ResetForNewFrame() {
      Engine.keyboardHandler.ResetForNewFrame();
      Engine.mouseHandler.ResetForNewFrame();
      Engine.customCursor.ResetForNewFrame();
  }

void cGameLoop::Update() {
    Engine.sceneManager.GetCurrentScene()->Update();
    Engine.fpsCounter.Update();
  }

void cGameLoop::Render() {
    glClear(GL_COLOR_BUFFER_BIT);

    Engine.sceneManager.GetCurrentScene()->Render();
    Engine.fpsCounter.Render();
    Engine.customCursor.Render();

    SDL_GL_SwapWindow(Engine.window.get());
  }

int cGameLoop::EventFilter(void *pthis, const SDL_Event *event) {
    auto do_handle_event = event->type == SDL_WINDOWEVENT &&
                           event->window.event == SDL_WINDOWEVENT_SIZE_CHANGED;

    if (!do_handle_event)
      return 1;

    iEngine *Engine = reinterpret_cast<iEngine *>(pthis);

    Engine->gameLoop.Update();
    Engine->gameLoop.Render();

    return 1;
  }

}  // namespace Forradia
