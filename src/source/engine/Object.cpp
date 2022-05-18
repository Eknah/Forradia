// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "Object.h"

namespace Forradia
{
    Object::Object(String objTypeName, bool randScaling, bool randRotation, float _rotation) : objectType(GetId(objTypeName))
    {
        if (randRotation) 
            rotation = CFloat(rnd.Next(360));
        else
            rotation = _rotation;

        if (randScaling)
            scaling = 0.6f + CFloat(rnd.Next(8)) / 10.0f;
    }
}