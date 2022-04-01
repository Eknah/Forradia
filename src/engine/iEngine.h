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
#include "cWorldMap.h"

namespace Forradia {

class F_MapArea;

class iEngine {
 public:
  iEngine(iKeyboardHandler* KeyboardHandler_, iCustomCursor* CustomCursor_,
          iFpsCounter* FpsCounter_,
          iFullscreenController* FullscreenController_, iGameLoop* GameLoop_,
          iSceneManager* SceneManager_)
      : KeyboardHandler(*KeyboardHandler_), CustomCursor(*CustomCursor_),
        FpsCounter(*FpsCounter_), FullscreenController(*FullscreenController_),
        GameLoop(*GameLoop_), SceneManager(*SceneManager_) {}

  virtual inline void DrawImage(std::string imageName, float x, float y,
                                float width, float height) const = 0;
  virtual inline void DrawImage(int imageNameHash, float x, float y,
                                float width, float height) const = 0;

  virtual inline void FillRectangle(SDL_Color color, float x, float y,
                                    float width, float height) const = 0;
  virtual inline void DrawRectangle(SDL_Color color, float X, float Y,
                                    float width, float height) const = 0;
  virtual inline void DrawLine(SDL_Color color, float x0, float y0, float x1,
                               float y1) const = 0;

  virtual inline void DrawString(std::string message, SDL_Color color, float x,
                                 float y, bool centerAlign = false) const = 0;

  virtual inline void DrawModel(std::string modelName, float x, float y,
                                float z, float rotation = 0.0f,
                                float specificScaling = 1.0f) const = 0;
  virtual inline void DrawModel(int modelNameHash, float x, float y, float z,
                                float rotation = 0.0f,
                                float specificScaling = 1.0f) const = 0;

  virtual inline cSizeF GetImageSizeF(std::string ImageName) const = 0;

  virtual inline cMapArea& GetCurrentMapArea() const = 0;

  cPlayer &GetPlayer() const {
      return **PlayerPtrPtr;
  }

  F_WindowPtr Window;

  iKeyboardHandler &KeyboardHandler;
  iCustomCursor &CustomCursor;
  iFpsCounter &FpsCounter;
  iFullscreenController &FullscreenController;
  iGameLoop &GameLoop;
  iSceneManager &SceneManager;

  cMouseHandler MouseHandler;
  cImageLoader ImageLoader;
  cModelLoader ModelLoader;
  cTextGraphics TextGraphics;
  cObjectsContent ObjectsContent;

  UPtr<cWorldMap> World;

  UPtr<cPlayer*> PlayerPtrPtr;
};

}  // namespace Forradia
