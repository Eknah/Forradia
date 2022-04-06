// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "cRandom.h"

namespace Forradia {

cRandom::cRandom() {
    if (!isInitialized) {
        mt = std::mt19937(device());
        isInitialized = true;
    }
}

int cRandom::Next() const {
        return result(mt);
    }

}  // namespace Forradia
