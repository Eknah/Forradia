// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "SceneManager.h"

namespace Forradia
{

    void SceneManager::Init(ScenesCollection scenes, int startScene)
    {
        scenesCollection = std::move(scenes);
        *currentScene = startScene;
    }

    SPtr<SceneBase>& SceneManager::GetCurrentScene()
    {
        return scenesCollection.scenes.at(*currentScene);
    }

    void SceneManager::SwitchToScene(std::string newScene) const
    {
        *currentScene = GetId(newScene);
        scenesCollection.scenes.at(*currentScene)->Enter();
        e.gameLoop.ResetForNewFrame();
    }

}  // namespace Forradia
