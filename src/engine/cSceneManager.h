
#pragma once
#include "cScenesCollection.h"
#include "framework/cSceneBase.h"

namespace Forradia
{

class cSceneManager
{

public:

    inline void Initialize(cScenesCollection scenes, int startScene)
    {
        ScenesCollection = std::move(scenes);
        CurrentScene = startScene;
    }

    inline UPtr<cSceneBase>& GetCurrentScene()
    {
        return ScenesCollection.Scenes.at(CurrentScene);
    }

    inline void SwitchToScene(std::string newScene)
    {
        CurrentScene = GetId(newScene);
        ScenesCollection.Scenes[CurrentScene]->Enter();
    }

private:

    cScenesCollection ScenesCollection;
    int CurrentScene;

};

}
