// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once

#include <memory>
#include <string>
#include "../engine/Aliases.h"
#include "../engine/Random.h"

namespace Forradia
{

    class Object
    {

        // Functions

    public:
        explicit Object(String objTypeName, bool randScaling = false, bool randRotation = false, float _rotation = 0.0f);

        // Members

    public:
        int objectType = 0;
        float rotation = 0.0f;
        float scaling = 1.0f;

    private:
        Random rnd;

    };

}  // namespace Forradia
