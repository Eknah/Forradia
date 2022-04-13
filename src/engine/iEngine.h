// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include <SDL2/SDL.h>
#include <string>
#include "../engine/MapArea.h"
#include "Typedefs.h"
#include "ImageLoader.h"
#include "ModelLoader.h"
#include "MouseHandler.h"
#include "TextGraphics.h"
#include "Vector3.h"
#include "implementation/content/ObjectsBehaviour.h"
#include "ICustomCursor.h"
#include "IFpsCounter.h"
#include "IFullscreenController.h"
#include "IGameLoop.h"
#include "IKeyboardHandler.h"
#include "ISceneManager.h"
#include "Player.h"
#include "PlanetWorldMap.h"

namespace Forradia {

class IEngine {
 public:
  IEngine(IKeyboardHandler* _keyboardHandler, ICustomCursor* _customCursor,
          IFpsCounter* _fpsCounter,
          IFullscreenController* _fullscreenController, IGameLoop* _gameLoop,
          ISceneManager* _sceneManager)
      : keyboardHandler(*_keyboardHandler), customCursor(*_customCursor),
        fpsCounter(*_fpsCounter), fullscreenController(*_fullscreenController),
        gameLoop(*_gameLoop), sceneManager(*_sceneManager) {}

  virtual void DrawImage(std::string imageName, float x, float y,
                                float width, float height) const = 0;
  virtual void DrawImage(int imageNameHash, float x, float y,
                                float width, float height) const = 0;

  virtual void FillRectangle(SDL_Color color, float x, float y,
                                    float width, float height) const = 0;
  virtual void DrawRectangle(SDL_Color color, float X, float Y,
                                    float width, float height) const = 0;
  virtual void DrawLine(SDL_Color color, float x0, float y0, float x1,
                               float y1) const = 0;

  virtual void DrawString(std::string message, SDL_Color color, float x,
                                 float y, bool centerAlign = false, float specificScaling = 1.0f) const = 0;

  virtual void DrawModel(std::string modelName, float x, float y,
                                float z, float rotation = 0.0f,
                                float specificScaling = 1.0f,
                         float Opacity = 1.0f) const = 0;
  virtual void DrawModel(int modelNameHash, float x, float y, float z,
                                float rotation = 0.0f,
                                float specificScaling = 1.0f,
                         float opacity = 1.0f) const = 0;

  virtual SizeF GetImageSizeF(std::string imageName) const = 0;

  virtual MapArea& GetCurrMapArea() const = 0;

  Player &GetPlayer() const;

  WindowPtr window;

  IKeyboardHandler &keyboardHandler;
  ICustomCursor &customCursor;
  IFpsCounter &fpsCounter;
  IFullscreenController &fullscreenController;
  IGameLoop &gameLoop;
  ISceneManager &sceneManager;

  MouseHandler mouseHandler;
  ImageLoader imageLoader;
  ModelLoader modelLoader;
  TextGraphics textGraphics;
  ObjectsBehaviour objectsContent;

  UPtr<PlanetWorldMap> world;

  UPtr<Player*> playerPtrPtr;

  //char *text = nullptr;
  std::string text;
  char *composition;
  Sint32 cursor = 0;
  Sint32 selection_len = 0;
};

}  // namespace Forradia
