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
#include "cPlayer.h"
#include "framework/world_structure/cWorldMap.h"
#include "iEngine.h"
#include "implementation/content/cObjectsContent.h"

namespace Forradia {

class cEngine : public iEngine {
 public:
  // ---- Ctor ----
  // Give needed references to this engine to all sub components

  cEngine()
      : GameLoopImplemented(*this), ModelGraphics(*this),
        FpsCounterImplemented(*this), CustomCursorImplemented(*this),
        ImageGraphics(*this), FullscreenControllerImplemented(*this),
        Player(*this),
        iEngine(&KeyboardHandlerImplemented, &CustomCursorImplemented,
                &FpsCounterImplemented, &FullscreenControllerImplemented,
                &GameLoopImplemented) {}

  // Loads content and initializes all engine components
  // Runs game loop until user exists program
  // Cleans up SDL

  inline void Run(cScenesCollection ScenesCollection_, int StartScene_,
                  UPtr<cWorldMap> WorldMap_,
                  UMap<int, SPtr<cObject>> StartingInventory_,
                  cObjectsContent ObjectsContent_) {
    using std::move;

    InitializeGL();

    WorldMap = move(WorldMap_);
    ObjectsContent = ObjectsContent_;

    // Player          .CurrentMapArea = 0;
    Player.WorldMapCoord = {1, 1, 0};
    Player.Position = GetCurrentMapArea().PlayerSpawnPosition;
    Player.GetModule<cModuleInventory>().Objects = StartingInventory_;
    SceneManager.Initialize(move(ScenesCollection_), StartScene_);
    ModelLoader.LoadModels();
    ImageLoader.LoadImages();
    TextGraphics.Initialize();
    CustomCursor.Initialize();

    GameLoop.Run();

    SDL_Quit();
  }

  // ---- Drawing operations ----

  inline void DrawImage(std::string ImageName, float X, float Y, float Width,
                        float Height) const override {
    ImageGraphics.DrawImage(ImageName, X, Y, Width, Height);
  }

  inline void DrawImage(int ImageNameHash, float X, float Y, float Width,
                        float Height) const override {
    ImageGraphics.DrawImage(ImageNameHash, X, Y, Width, Height);
  }

  inline void FillRectangle(SDL_Color Color, float X, float Y, float Width,
                            float Height) const override {
    PaintGraphics.FillRectangle(Color, X, Y, Width, Height);
  }

  inline void DrawRectangle(SDL_Color Color, float X, float Y, float Width,
                            float Height) const override {
    PaintGraphics.DrawRectangle(Color, X, Y, Width, Height);
  }

  inline void DrawLine(SDL_Color Color, float X0, float Y0, float X1,
                       float Y1) const override {
    PaintGraphics.DrawLine(Color, X0, Y0, X1, Y1);
  }

  inline void DrawString(std::string Message, SDL_Color Color, float X, float Y,
                         bool CenterAlign = false) const override {
    TextGraphics.DrawString(Message, Color, X, Y, CenterAlign);
  }

  inline void DrawModel(std::string ModelName, float X, float Y, float Z,
                        float Rotation = 0.0f,
                        float SpecificScaling = 1.0f) const override {
    ModelGraphics.DrawModel(ModelName, X, Y, Z, Rotation, SpecificScaling);
  }

  inline void DrawModel(int ModelNameHash, float X, float Y, float Z,
                        float Rotation = 0.0f,
                        float SpecificScaling = 1.0f) const override {
    ModelGraphics.DrawModel(ModelNameHash, X, Y, Z, Rotation, SpecificScaling);
  }

  // ---- Helper functions ----

  inline cMapArea& GetCurrentMapArea() const override {
    // return *WorldMap->MapAreas.at(Player.CurrentMapArea);
    return *WorldMap->MapAreas[Player.WorldMapCoord.X][Player.WorldMapCoord.Y]
                              [Player.WorldMapCoord.Z];
  }

  // ---- Public members ----

  cPlayer Player;
  UPtr<cWorldMap> WorldMap;
  cObjectsContent ObjectsContent;

  cKeyboardHandler KeyboardHandlerImplemented;
  cCustomCursor CustomCursorImplemented;
  cFpsCounter FpsCounterImplemented;
  cFullscreenController FullscreenControllerImplemented;
  cGameLoop GameLoopImplemented;

  float TileSize = 0.5f;

 private:
  // Initializes SDL video module
  // Specifices GL version
  // Creates game window with GL support
  // Enables alpha blending for all following render operations

  inline void InitializeGL() {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                        SDL_GL_CONTEXT_PROFILE_CORE);

    Window = F_WindowPtr(
        SDL_CreateWindow(Title.c_str(), SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED, DefaultWindowSize.Width,
                         DefaultWindowSize.Height,
                         SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN |
                             SDL_WINDOW_FULLSCREEN_DESKTOP),
        cSDL_Deleter());

    FullscreenController.ToggleFullscreen();
    SDL_SetWindowResizable(Window.get(), SDL_TRUE);
    FullscreenController.ToggleFullscreen();

    SDL_GL_CreateContext(Window.get());
    SDL_GL_SetSwapInterval(1);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  }

  // ---- Private members ----

  cImageGraphics ImageGraphics;
  cPaintGraphics PaintGraphics;
  cModelGraphics ModelGraphics;

  const std::string Title = "Forradia";
  const cSize DefaultWindowSize = {800, 600};
};

}  // namespace Forradia
