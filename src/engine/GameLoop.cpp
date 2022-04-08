// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "GameLoop.h"

namespace Forradia {

void cGameLoop::Run() {
    bool quit = false;
    SDL_Event event;

    SDL_SetEventFilter((SDL_EventFilter)EventFilter, &engine);

    while (!quit) {
      ResetForNewFrame();

      while (SDL_PollEvent(&event) != 0) {
        switch (event.type) {
        case SDL_QUIT: {
          quit = true;

          break;
        }

        case SDL_KEYDOWN: {
          engine.keyboardHandler.DoKeyDown(event.key.keysym.sym);

          engine.fullscreenController.UpdateFullscreenToggling();

          break;
        }

        case SDL_KEYUP: {
          engine.keyboardHandler.DoKeyUp(event.key.keysym.sym);

          break;
        }

        case SDL_MOUSEBUTTONDOWN: {
          engine.sceneManager.GetCurrentScene()->DoMouseDown(
              event.button.button);

          if (event.button.button == SDL_BUTTON_LEFT) {
            engine.mouseHandler.leftButtonDown = true;
              engine.mouseHandler.SetLeftButtonBeenFired();
          } else if (event.button.button == SDL_BUTTON_RIGHT) {
            engine.mouseHandler.rightButtonDown = true;
              engine.mouseHandler.SetRightButtonBeenFired();
          }

          break;
        }

        case SDL_MOUSEBUTTONUP: {
          engine.sceneManager.GetCurrentScene()->DoMouseUp(event.button.button);

          if (event.button.button == SDL_BUTTON_LEFT)
            engine.mouseHandler.leftButtonDown = false;
          else if (event.button.button == SDL_BUTTON_RIGHT)
            engine.mouseHandler.rightButtonDown = false;

          break;
        }

        case SDL_MOUSEWHEEL: {
          *engine.mouseHandler.wheelAmount = static_cast<float>(event.wheel.y);

          break;
        }
        }
      }

      Update();
      Render();
    }
  }

void cGameLoop::ResetForNewFrame() {
      engine.keyboardHandler.ResetForNewFrame();
      engine.mouseHandler.ResetForNewFrame();
      engine.customCursor.ResetForNewFrame();
  }

void cGameLoop::Update() {
    engine.sceneManager.GetCurrentScene()->Update();
    engine.fpsCounter.Update();
  }

void cGameLoop::Render() {
    glClear(GL_COLOR_BUFFER_BIT);

    engine.sceneManager.GetCurrentScene()->Render();
    engine.fpsCounter.Render();
    engine.customCursor.Render();

    SDL_GL_SwapWindow(engine.window.get());
  }

int cGameLoop::EventFilter(void *pthis, const SDL_Event *event) {
    auto do_handle_event = event->type == SDL_WINDOWEVENT &&
                           event->window.event == SDL_WINDOWEVENT_SIZE_CHANGED;

    if (!do_handle_event)
      return 1;

    iEngine *engine = reinterpret_cast<iEngine *>(pthis);

    engine->gameLoop.Update();
    engine->gameLoop.Render();

    return 1;
  }

}  // namespace Forradia
