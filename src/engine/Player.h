// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "../engine/Actor.h"
#include "../engine/InventoryModule.h"
#include "implementation/functionality/actor/modules/JumpingModule.h"
#include "implementation/functionality/actor/modules/DestMovmModule.h"
#include "implementation/functionality/actor/modules/DirectionMovmModule.h"
#include "implementation/functionality/actor/modules/CraftSkillsModule.h"

namespace Forradia
{

    class Player : public Actor
    {
    public:
        explicit Player(IEngine& e);
    };

}  // namespace Forradia
