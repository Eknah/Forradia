
#include "CommonExternal.h"
#include "cSceneGameStart.h"
#include "../engine/cEngine.h"

namespace Forradia
{

void cSceneGameStart::Update()
{
    if (Engine.KeyboardHandler.KeysBeingPressed.size() > 0)
        Engine.SceneManager.SwitchToScene("SceneMainMenu");
}

void cSceneGameStart::Render()
{
    Engine.DrawImage("SceneGameStartBackground", 0, 0, 1, 1);

    auto CanvasSize = Utilities.GetCanvasSize();

    glBindTexture(GL_TEXTURE_2D, Engine.ImageLoader.Images[GetId("SceneForradiaLogo")]);

    int Width, Height;
    int MipLevel = 0;

    glGetTexLevelParameteriv(GL_TEXTURE_2D, MipLevel, GL_TEXTURE_WIDTH, &Width);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, MipLevel, GL_TEXTURE_HEIGHT, &Height);

    auto ImageWidth = (float)Width / CanvasSize.Width;
    auto ImageHeight = (float)Height / CanvasSize.Height;

    Engine.DrawImage("SceneForradiaLogo", 0.5f - ImageWidth / 2.0f, 0.25f - ImageHeight / 2.0f, ImageWidth, ImageHeight);
    Engine.DrawString("Press to start", { 255, 255 ,255, 255 }, 0.5f, 0.5f, true);
}

void cSceneGameStart::DoMouseDown(Uint8 mouseButton)
{
    Engine.SceneManager.SwitchToScene("SceneMainMenu");
}

}
