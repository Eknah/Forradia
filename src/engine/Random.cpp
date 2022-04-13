// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "Random.h"

namespace Forradia
{

    Random::Random()
    {
        if (!isInitialized)
        {
            mt = std::mt19937(device());
            isInitialized = true;
        }
    }

    int Random::Next() const
    {
        return result(mt);
    }

}  // namespace Forradia
