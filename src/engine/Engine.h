// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once

#include <utility>
#include <string>
#include "CustomCursor.h"
#include "FpsCounter.h"
#include "FullscreenController.h"
#include "GameLoop.h"
#include "ImageGraphics.h"
#include "KeyboardHandler.h"
#include "Model3D.h"
#include "ModelGraphics.h"
#include "PaintGraphics.h"
#include "SceneManager.h"
#include "IEngine.h"

namespace Forradia {

class Engine : public IEngine {
 public:
  // ---- Ctor ----
  // Give needed references to this engine to all sub components

  Engine()
      : gameLoopImplemented(*this), modelGraphics(*this),
        fpsCounterImplemented(*this), customCursorImplemented(*this),
        imageGraphics(*this), fullscreenControllerImplemented(*this),
        sceneManagerImplemented(*this),
        IEngine(&keyboardHandlerImplemented, &customCursorImplemented,
                &fpsCounterImplemented, &fullscreenControllerImplemented,
                &gameLoopImplemented, &sceneManagerImplemented) {}

  // Loads content and initializes all engine components
  // Runs game loop until user exists program
  // Cleans up SDL

  void Run(ScenesCollection scenesCollection_, int startScene_,
                  UPtr<PlanetWorldMap> world_,
                  Inventory startingInventory_,
                  ObjectsContent objectsContent_);

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
                        float specificScaling = 1.0f, float Opacity = 1.0f) const override;

  void DrawModel(int ModelNameHash, float x, float y, float z,
                        float rotation = 0.0f,
                        float specificScaling = 1.0f, float Opacity = 1.0f) const override;

  // ---- Helper functions ----

  SizeF GetImageSizeF(std::string imageName) const override;

  MapArea& GetCurrentMapArea() const override;

  // ---- Public members ----

  KeyboardHandler keyboardHandlerImplemented;
  CustomCursor customCursorImplemented;
  FpsCounter fpsCounterImplemented;
  FullscreenController fullscreenControllerImplemented;
  GameLoop gameLoopImplemented;
  SceneManager sceneManagerImplemented;

  float tileSize = 0.5f;
  float fov = 60.0f;

 private:
  // Initializes SDL video module
  // Specifices GL version
  // Creates game window with GL support
  // Enables alpha blending for all following render operations

  void InitializeGL();

  // ---- Private members ----

  ImageGraphics imageGraphics;
  PaintGraphics paintGraphics;
  ModelGraphics modelGraphics;

  const std::string title = "Forradia";
  const Size defaultWindowSize = {800, 600};
};

}  // namespace Forradia
