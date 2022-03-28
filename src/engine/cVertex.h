// Copyright (C) 2022  Andreas Åkerberg

#pragma once
#include "cVector2.h"
#include "cVector3.h"

namespace Forradia
{

class cVertex
{

public:

    cVector3 Position;
    cVector3 Normal;
    cVector2 TextureCoordinate;
};

}
