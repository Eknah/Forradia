
#include "CommonExternal.h"
#include "F_SceneMainMenu.h"
#include "../core/F_Engine.h"

namespace Forradia
{

void F_SceneMainMenu::Update()
{
    if (Engine.KeyboardHandler.KeysBeingPressed.size() > 0)
        Engine.SceneManager.SwitchToScene("ScenePrimary");
}

void F_SceneMainMenu::Render()
{
    Engine.DrawImage("SceneGameStartBackground", 0, 0, 1, 1);
    auto canvas_size = Utilities.GetCanvasSize();
    glBindTexture(GL_TEXTURE_2D, Engine.ImageLoader.Images[GetId("SceneForradiaLogo")]);
    int width, height;
    int miplevel = 0;
    glGetTexLevelParameteriv(GL_TEXTURE_2D, miplevel, GL_TEXTURE_WIDTH, &width);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, miplevel, GL_TEXTURE_HEIGHT, &height);
    auto image_width = (float)width / canvas_size.Width/2.0f;
    auto image_height = (float)height / canvas_size.Height / 2.0f;
    Engine.DrawImage("SceneForradiaLogo", 0.5f - image_width / 2.0f, 0.15f - image_height / 2.0f, image_width, image_height);
}

void F_SceneMainMenu::DoMouseDown(Uint8 mouseButton)
{
    Engine.SceneManager.SwitchToScene("ScenePrimary");
}

}
