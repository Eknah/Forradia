// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "Player.h"
#include "CoreMovmModule.h"

namespace Forradia
{

    Player::Player(IEngine& e) : Actor(e, "Player")
    {
        AddModule<JumpingModule>();
        AddModule<DestMovmModule>();
        AddModule<DirectionMovmModule>();
        AddModule<InventoryModule>();
        AddModule<CraftSkillsModule>();

        GetModule<CoreMovmModule>().stepSize = 2.0f;
    }

}  // namespace Forradia
