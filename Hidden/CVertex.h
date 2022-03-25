#pragma once
#include "CVector2.h"
#include "CVector3.h"

namespace Forradia
{

class CVertex
{

public:

    CVector3 Position;
    CVector3 Normal;
    CVector2 TextureCoordinate;
};

}
