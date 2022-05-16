// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "Actor.h"
#include "InventoryModule.h"
#include "JumpingModule.h"
#include "DestMovmModule.h"
#include "DirectionMovmModule.h"
#include "CraftSkillsModule.h"

namespace Forradia
{

    class Player : public Actor
    {
    public:
        explicit Player(IEngine& e);
    };

}  // namespace Forradia
