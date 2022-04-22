// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once

#include "../engine/IModule.h"
#include "../engine/Random.h"

namespace Forradia
{

    class MobAIMovmModule : public IModule
    {

        // Functions

    public:
        MobAIMovmModule(const IEngine& _e, Actor* _parentActor);

        void ResetForNewFrame() override {};
        void Update() override;

        // Members

    private:
        Random rnd;

    };

}  // namespace Forradia
