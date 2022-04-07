// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "../engine/iEngine.h"
#include "../engine/iGameLoop.h"

namespace Forradia {

class cGameLoop : public iGameLoop {
 public:
  explicit cGameLoop(iEngine &engine) : iGameLoop(engine) {}

  // Before loop:
  // Initializes game loop variables
  // Sets event filter to enable game update and rendering during window resize
  //
  // In loop:
  // Resets all engine components that need to be reset for each frame
  // Poll events and handle them
  // Update game
  // Render game

  void Run() override;

  void ResetForNewFrame() override;

 private:
  // ---- Looped functions ----

  // Update currently displayed scene and fps counter.

  void Update() override;

  // Render currently displayed scene and general engine components.

  void Render() override;

  // Enables game updating and rendering during window resize.

  static int EventFilter(void *pthis, const SDL_Event *event);
};

}  // namespace Forradia
