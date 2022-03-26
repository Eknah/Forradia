
#pragma once
#include "Aliases.h"
#include "F_Vector3.h"

namespace Forradia
{

class F_Material
{

public:

    std::string Name;
    F_Vector3 Ka;
    F_Vector3 Kd;
    F_Vector3 Ks;
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
