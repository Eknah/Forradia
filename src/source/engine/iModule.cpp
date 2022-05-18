// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "IModule.h"

namespace Forradia
{
    Actor& IModule::GetParentActor()
    {
        return *parentActor;
    }
}