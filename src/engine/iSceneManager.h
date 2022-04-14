// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include <string>
#include "ScenesCollection.h"

namespace Forradia
{

    class IEngine;

    class ISceneManager
    {
    public:

        explicit ISceneManager(const IEngine& _e) : e(_e) {}

        virtual void Init(ScenesCollection _scenes, int startScene) = 0;

        virtual SPtr<SceneBase>& GetCurrentScene() = 0;

        virtual void SwitchToScene(std::string newScene) const = 0;

    protected:

        const IEngine& e;
        ScenesCollection scenesCollection;
        const UPtr<int> currentScene = MakeUPtr<int>(-1);

    };

}  // namespace Forradia
