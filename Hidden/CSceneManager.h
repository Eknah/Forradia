#pragma once
namespace Forradia
{

	class CSceneManager
	{

	public:

		inline void InitializeEngine(UMap<int, UPtr<CSceneBase>> scenes, int startScene)
		{
			Scenes = std::move(scenes);
			CurrentScene = startScene;
		}
		inline UPtr<CSceneBase>& GetCurrentScene()
		{
			return Scenes.at(CurrentScene);
		}
		inline void SwitchToScene(String newScene)
		{
			CurrentScene = Hash(newScene);
			Scenes[CurrentScene]->Enter();
		}

	private:
		UMap<int, UPtr<CSceneBase>> Scenes;
		int CurrentScene;

	};

}