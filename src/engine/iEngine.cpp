// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "IEngine.h"

namespace Forradia {

Player &IEngine::GetPlayer() const {
    return **playerPtrPtr;
}

}  // namespace Forradia
