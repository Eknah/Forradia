// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once

#include "IModule.h"
#include "Aliases.h"
#include "Point2F.h"
#include "Point3.h"
#include "Timer.h"

namespace Forradia
{

    class CoreMovmModule : public IModule
    {

        // Functions

    public:
        CoreMovmModule(const IEngine& _e, Actor* _parentActor) : IModule(_e, _parentActor), timer(UPtr<int>(&moveSpeed)) {}

        void ResetForNewFrame() override;
        void Update() override {};
        void TryMoveToTile(float newxRounded, float newyRounded);

        // Members

    public:
        Point3 worldMapCoord = { 1, 1, 0 };
        Point2F position = { 50.0f, 50.0f };
        float positionZ = 0.0f;
        UPtr<float> facingAngle = MakeUPtr<float>(0.0f);

        Point2F dest = { -1, -1 };
        int moveSpeed = 50;
        float stepSize = 1.5f;
        float stepMultiplier = 0.1f;
        bool isWalking = false;

        Timer timer;

    };

}  // namespace Forradia
