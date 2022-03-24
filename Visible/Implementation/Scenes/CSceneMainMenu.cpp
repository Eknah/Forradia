#include "Pch.h"
#include "CSceneMainMenu.h"
#include "../Hidden/CEngine.h"
namespace Forradia
{
	void CSceneMainMenu::Update()
	{
		if (Engine.KeyboardHandler.KeysBeingPressed.size() > 0)
			Engine.SceneManager.SwitchToScene("ScenePrimary");
	}
	void CSceneMainMenu::Render()
	{
		Engine.DrawImage("SceneGameStartBackground", 0, 0, 1, 1);
		auto canvas_size = Utilities.GetCanvasSize();
		glBindTexture(GL_TEXTURE_2D, Engine.ImageLoader.Images[Hash("SceneForradiaLogo")]);
		int width, height;
		int miplevel = 0;
		glGetTexLevelParameteriv(GL_TEXTURE_2D, miplevel, GL_TEXTURE_WIDTH, &width);
		glGetTexLevelParameteriv(GL_TEXTURE_2D, miplevel, GL_TEXTURE_HEIGHT, &height);
		auto image_width = (float)width / canvas_size.Width/2;
		auto image_height = (float)height / canvas_size.Height / 2;
		Engine.DrawImage("SceneForradiaLogo", 0.5 - image_width / 2, 0.15 - image_height / 2, image_width, image_height);
	}
	void CSceneMainMenu::DoMouseDown(Uint8 mouseButton)
	{
		Engine.SceneManager.SwitchToScene("ScenePrimary");
	}
}
