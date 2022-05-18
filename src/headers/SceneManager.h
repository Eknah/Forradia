// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include <string>
#include <utility>
#include "IEngine.h"
#include "ISceneManager.h"

namespace Forradia
{

    class SceneManager : public ISceneManager
    {
    public:
        explicit SceneManager(const IEngine& e) :
            ISceneManager(e)
        {}

        void Init(ScenesCollection scenes, int startScene) override;

        SPtr<SceneBase>& GetCurrentScene() override;

        void SwitchToScene(std::string newScene) const override;
    };

}