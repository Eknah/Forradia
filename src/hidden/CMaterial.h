#pragma once
#include "Aliases.h"
#include "CVector3.h"

namespace Forradia
{

class CMaterial
{

public:

    std::string Name;
    CVector3 Ka;
    CVector3 Kd;
    CVector3 Ks;
    float Ns = 0.0f;
    float Ni = 0.0f;
    float D = 0.0f;
    int Illum = 0;
    std::string MapKa;
    std::string MapKd;
    std::string MapKs;
    std::string MapNs;
    std::string MapD;
    std::string MapBump;

};

}
