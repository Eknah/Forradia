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
      : GameLoopImplemented(*this), ModelGraphics(*this),
        FpsCounterImplemented(*this), CustomCursorImplemented(*this),
        ImageGraphics(*this), FullscreenControllerImplemented(*this),
        SceneManagerImplemented(*this),
        iEngine(&KeyboardHandlerImplemented, &CustomCursorImplemented,
                &FpsCounterImplemented, &FullscreenControllerImplemented,
                &GameLoopImplemented, &SceneManagerImplemented) {}

  // Loads content and initializes all engine components
  // Runs game loop until user exists program
  // Cleans up SDL

  void Run(cScenesCollection ScenesCollection_, int StartScene_,
                  UPtr<cWorldMap> World_,
                  cInventory StartingInventory_,
                  cObjectsContent ObjectsContent_);

  // ---- Drawing operations ----

  void DrawImage(std::string ImageName, float X, float Y, float Width,
                        float Height) const override;

  void DrawImage(int ImageNameHash, float X, float Y, float Width,
                        float Height) const override;

  void FillRectangle(SDL_Color Color, float X, float Y, float Width,
                            float Height) const override;

  void DrawRectangle(SDL_Color Color, float X, float Y, float Width,
                            float Height) const override;

  void DrawLine(SDL_Color Color, float X0, float Y0, float X1,
                       float Y1) const override;

  void DrawString(std::string Message, SDL_Color Color, float X, float Y,
                         bool CenterAlign = false) const override;

  void DrawModel(std::string ModelName, float X, float Y, float Z,
                        float Rotation = 0.0f,
                        float SpecificScaling = 1.0f) const override;

  void DrawModel(int ModelNameHash, float X, float Y, float Z,
                        float Rotation = 0.0f,
                        float SpecificScaling = 1.0f) const override;

  // ---- Helper functions ----

  cSizeF GetImageSizeF(std::string ImageName) const;

  cMapArea& GetCurrentMapArea() const override;

  // ---- Public members ----

  cKeyboardHandler KeyboardHandlerImplemented;
  cCustomCursor CustomCursorImplemented;
  cFpsCounter FpsCounterImplemented;
  cFullscreenController FullscreenControllerImplemented;
  cGameLoop GameLoopImplemented;
  cSceneManager SceneManagerImplemented;

  float TileSize = 0.5f;

 private:
  // Initializes SDL video module
  // Specifices GL version
  // Creates game window with GL support
  // Enables alpha blending for all following render operations

  void InitializeGL();

  // ---- Private members ----

  cImageGraphics ImageGraphics;
  cPaintGraphics PaintGraphics;
  cModelGraphics ModelGraphics;

  const std::string Title = "Forradia";
  const cSize DefaultWindowSize = {800, 600};
};

}  // namespace Forradia
