#pragma once
#include "Aliases.h"
#include "CVector3.h"
namespace Forradia
{
class CMaterial
{

public:
    CMaterial() : Name(""), Ns(0.0f), Ni(0.0f), D(0.0f), Illum(0) {}

    std::string Name;
    CVector3 Ka;
    CVector3 Kd;
    CVector3 Ks;
    float Ns;
    float Ni;
    float D;
    int Illum;
    std::string MapKa;
    std::string MapKd;
    std::string MapKs;
    std::string MapNs;
    std::string MapD;
    std::string MapBump;
};
}
