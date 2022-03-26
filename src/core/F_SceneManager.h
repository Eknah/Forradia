#pragma once
#include "framework/F_ScenesCollection.h"
#include "framework/F_SceneBase.h"

namespace Forradia
{

class F_SceneManager
{

public:

    inline void Initialize(F_ScenesCollection scenes, int startScene)
    {
        Scenes = std::move(scenes);
        CurrentScene = startScene;
    }

    inline UPtr<F_SceneBase>& GetCurrentScene()
    {
        return Scenes.Scenes.at(CurrentScene);
    }

    inline void SwitchToScene(std::string newScene)
    {
        CurrentScene = GetId(newScene);
        Scenes.Scenes[CurrentScene]->Enter();
    }

private:

    F_ScenesCollection Scenes;
    int CurrentScene;

};

}
