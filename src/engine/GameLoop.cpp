// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "GameLoop.h"

namespace Forradia {

void GameLoop::Run() {
    bool quit = false;
    SDL_Event event;

    SDL_SetEventFilter((SDL_EventFilter)EventFilter, &e);

    while (!quit) {
      ResetForNewFrame();

      while (SDL_PollEvent(&event) != 0) {
        switch (event.type) {
        case SDL_QUIT: {
          quit = true;

          break;
        }

        case SDL_KEYDOWN: {
          e.keyboardHandler.DoKeyDown(event.key.keysym.sym);

          e.fullscreenController.UpdateFullscreenToggling();

          break;
        }

        case SDL_KEYUP: {
          e.keyboardHandler.DoKeyUp(event.key.keysym.sym);

          break;
        }

        case SDL_MOUSEBUTTONDOWN: {
          e.sceneManager.GetCurrentScene()->DoMouseDown(
              event.button.button);

          if (event.button.button == SDL_BUTTON_LEFT) {
            e.mouseHandler.leftButtonDown = true;
              e.mouseHandler.SetLeftButtonBeenFired();
          } else if (event.button.button == SDL_BUTTON_RIGHT) {
            e.mouseHandler.rightButtonDown = true;
              e.mouseHandler.SetRightButtonBeenFired();
          }

          break;
        }

        case SDL_MOUSEBUTTONUP: {
          e.sceneManager.GetCurrentScene()->DoMouseUp(event.button.button);

          if (event.button.button == SDL_BUTTON_LEFT)
            e.mouseHandler.leftButtonDown = false;
          else if (event.button.button == SDL_BUTTON_RIGHT)
            e.mouseHandler.rightButtonDown = false;

          break;
        }

        case SDL_MOUSEWHEEL: {
          *e.mouseHandler.wheelAmount = static_cast<float>(event.wheel.y);

          break;
        }
        }
      }

      Update();
      Render();
    }
  }

void GameLoop::ResetForNewFrame() {
      e.keyboardHandler.ResetForNewFrame();
      e.mouseHandler.ResetForNewFrame();
      e.customCursor.ResetForNewFrame();
  }

void GameLoop::Update() {
    e.sceneManager.GetCurrentScene()->Update();
    e.fpsCounter.Update();
  }

void GameLoop::Render() {
    glClear(GL_COLOR_BUFFER_BIT);

    e.sceneManager.GetCurrentScene()->Render();
    e.fpsCounter.Render();
    e.customCursor.Render();

    SDL_GL_SwapWindow(e.window.get());
  }

int GameLoop::EventFilter(void *pthis, const SDL_Event *event) {
    auto do_handle_event = event->type == SDL_WINDOWEVENT &&
                           event->window.event == SDL_WINDOWEVENT_SIZE_CHANGED;

    if (!do_handle_event)
      return 1;

    IEngine *e = reinterpret_cast<IEngine *>(pthis);

    e->gameLoop.Update();
    e->gameLoop.Render();

    return 1;
  }

}  // namespace Forradia
