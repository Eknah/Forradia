// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once

#include <string>
#include "../engine/Point2F.h"
#include "../engine/Aliases.h"
#include "../engine/Actor.h"

namespace Forradia
{

    class IEngine;

    class Mob : public Actor
    {
    public:
        Mob(const IEngine& e, float x, float y, std::string modelName);
    };

}  // namespace Forradia
