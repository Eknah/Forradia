// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "iEngine.h"

namespace Forradia {

cPlayer &iEngine::GetPlayer() const {
    return **playerPtrPtr;
}

}  // namespace Forradia
