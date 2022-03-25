#pragma once
namespace Forradia
{

	class CSceneManager
	{

	public:

                inline void InitializeEngine(CScenesCollection scenes, int startScene)
		{
			Scenes = std::move(scenes);
			CurrentScene = startScene;
		}
		inline UPtr<CSceneBase>& GetCurrentScene()
		{
                        return Scenes.Scenes.at(CurrentScene);
		}
		inline void SwitchToScene(String newScene)
		{
			CurrentScene = Hash(newScene);
                        Scenes.Scenes[CurrentScene]->Enter();
		}

	private:
                CScenesCollection Scenes;
		int CurrentScene;

	};

}
