// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include <SDL2/SDL.h>
#include <string>
#include "../engine/cMapArea.h"
#include "Typedefs.h"
#include "cImageLoader.h"
#include "cModelLoader.h"
#include "cMouseHandler.h"
#include "cTextGraphics.h"
#include "cVector3.h"
#include "implementation/content/cObjectsContent.h"
#include "iCustomCursor.h"
#include "iFpsCounter.h"
#include "iFullscreenController.h"
#include "iGameLoop.h"
#include "iKeyboardHandler.h"
#include "iSceneManager.h"
#include "cPlayer.h"
#include "cPlanetWorldMap.h"

namespace Forradia {

class F_MapArea;

class iEngine {
 public:
  iEngine(iKeyboardHandler* _keyboardHandler, iCustomCursor* _customCursor,
          iFpsCounter* _fpsCounter,
          iFullscreenController* _fullscreenController, iGameLoop* _gameLoop,
          iSceneManager* _sceneManager)
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
                                 float y, bool centerAlign = false) const = 0;

  virtual void DrawModel(std::string modelName, float x, float y,
                                float z, float rotation = 0.0f,
                                float specificScaling = 1.0f,
                         float Opacity = 1.0f) const = 0;
  virtual void DrawModel(int modelNameHash, float x, float y, float z,
                                float rotation = 0.0f,
                                float specificScaling = 1.0f,
                         float opacity = 1.0f) const = 0;

  virtual cSizeF GetImageSizeF(std::string imageName) const = 0;

  virtual cMapArea& GetCurrentMapArea() const = 0;

  cPlayer &GetPlayer() const;

  WindowPtr window;

  iKeyboardHandler &keyboardHandler;
  iCustomCursor &customCursor;
  iFpsCounter &fpsCounter;
  iFullscreenController &fullscreenController;
  iGameLoop &gameLoop;
  iSceneManager &sceneManager;

  cMouseHandler mouseHandler;
  cImageLoader imageLoader;
  cModelLoader modelLoader;
  cTextGraphics textGraphics;
  cObjectsContent objectsContent;

  UPtr<cPlanetWorldMap> world;

  UPtr<cPlayer*> playerPtrPtr;
};

}  // namespace Forradia
