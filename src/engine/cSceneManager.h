
#pragma once
#include "framework/cScenesCollection.h"
#include "framework/cSceneBase.h"

namespace Forradia
{

class cSceneManager
{

public:

    inline void Initialize(cScenesCollection scenes, int startScene)
    {
        Scenes = std::move(scenes);
        CurrentScene = startScene;
    }

    inline UPtr<cSceneBase>& GetCurrentScene()
    {
        return Scenes.Scenes.at(CurrentScene);
    }

    inline void SwitchToScene(std::string newScene)
    {
        CurrentScene = GetId(newScene);
        Scenes.Scenes[CurrentScene]->Enter();
    }

private:

    cScenesCollection Scenes;
    int CurrentScene;

};

}
