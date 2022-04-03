// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once

#include <utility>
#include <string>
#include "cCustomCursor.h"
#include "cFpsCounter.h"
#include "cFullscreenController.h"
#include "cGameLoop.h"
#include "cImageGraphics.h"
#include "cKeyboardHandler.h"
#include "cModel3D.h"
#include "cModelGraphics.h"
#include "cPaintGraphics.h"
#include "cSceneManager.h"
#include "iEngine.h"

namespace Forradia {

class cEngine : public iEngine {
 public:
  // ---- Ctor ----
  // Give needed references to this engine to all sub components

  cEngine()
      : gameLoopImplemented(*this), modelGraphics(*this),
        fpsCounterImplemented(*this), customCursorImplemented(*this),
        imageGraphics(*this), fullscreenControllerImplemented(*this),
        sceneManagerImplemented(*this),
        iEngine(&keyboardHandlerImplemented, &customCursorImplemented,
                &fpsCounterImplemented, &fullscreenControllerImplemented,
                &gameLoopImplemented, &sceneManagerImplemented) {}

  // Loads content and initializes all engine components
  // Runs game loop until user exists program
  // Cleans up SDL

  void Run(cScenesCollection scenesCollection_, int startScene_,
                  UPtr<cPlanetWorldMap> world_,
                  cInventory startingInventory_,
                  cObjectsContent objectsContent_);

  // ---- Drawing operations ----

  void DrawImage(std::string imageName, float x, float y, float width,
                        float height) const override;

  void DrawImage(int imageNameHash, float x, float y, float width,
                        float height) const override;

  void FillRectangle(SDL_Color color, float x, float y, float width,
                            float height) const override;

  void DrawRectangle(SDL_Color color, float x, float y, float width,
                            float height) const override;

  void DrawLine(SDL_Color color, float x0, float y0, float x1,
                       float y1) const override;

  void DrawString(std::string message, SDL_Color color, float x, float y,
                         bool centerAlign = false) const override;

  void DrawModel(std::string modelName, float x, float y, float z,
                        float rotation = 0.0f,
                        float specificScaling = 1.0f) const override;

  void DrawModel(int ModelNameHash, float x, float y, float z,
                        float rotation = 0.0f,
                        float specificScaling = 1.0f) const override;

  // ---- Helper functions ----

  cSizeF GetImageSizeF(std::string imageName) const override;

  cMapArea& GetCurrentMapArea() const override;

  // ---- Public members ----

  cKeyboardHandler keyboardHandlerImplemented;
  cCustomCursor customCursorImplemented;
  cFpsCounter fpsCounterImplemented;
  cFullscreenController fullscreenControllerImplemented;
  cGameLoop gameLoopImplemented;
  cSceneManager sceneManagerImplemented;

  float tileSize = 0.5f;

 private:
  // Initializes SDL video module
  // Specifices GL version
  // Creates game window with GL support
  // Enables alpha blending for all following render operations

  void InitializeGL();

  // ---- Private members ----

  cImageGraphics imageGraphics;
  cPaintGraphics paintGraphics;
  cModelGraphics modelGraphics;

  const std::string title = "Forradia";
  const cSize defaultWindowSize = {800, 600};
};

}  // namespace Forradia
