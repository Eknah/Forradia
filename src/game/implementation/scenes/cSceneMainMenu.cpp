// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "cSceneMainMenu.h"
#include "../engine/cEngine.h"
#include "CommonExternal.h"

namespace Forradia {

void cSceneMainMenu::Update() {
  if (Engine.KeyboardHandler.KeysBeingPressed.size() > 0)
    Engine.SceneManager.SwitchToScene("ScenePrimary");
}

void cSceneMainMenu::Render() {
  Engine.DrawImage("SceneGameStartBackground", 0, 0, 1, 1);

  auto CanvasSize = Utilities.GetCanvasSize();

  glBindTexture(GL_TEXTURE_2D,
                Engine.ImageLoader.Images[GetId("SceneForradiaLogo")]);

  int Width, Height;
  int MipLevel = 0;

  glGetTexLevelParameteriv(GL_TEXTURE_2D, MipLevel, GL_TEXTURE_WIDTH, &Width);
  glGetTexLevelParameteriv(GL_TEXTURE_2D, MipLevel, GL_TEXTURE_HEIGHT, &Height);

  auto ImageWidth = (float)Width / CanvasSize.Width / 2.0f;
  auto ImageHeight = (float)Height / CanvasSize.Height / 2.0f;

  Engine.DrawImage("SceneForradiaLogo", 0.5f - ImageWidth / 2.0f,
                   0.15f - ImageHeight / 2.0f, ImageWidth, ImageHeight);
}

void cSceneMainMenu::DoMouseDown(Uint8 mouseButton) {
  Engine.SceneManager.SwitchToScene("ScenePrimary");
}

}  // namespace Forradia
