// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "iModule.h"

namespace Forradia {

cActor &iModule::GetParentActor() {
    return *parentActor;
}

}  // namespace Forradia
