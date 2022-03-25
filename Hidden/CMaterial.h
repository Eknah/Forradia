#pragma once
#include "Aliases.h"
#include "CVector3.h"
namespace Forradia
{
class CMaterial
{

public:
    CMaterial() : Name(""), Ns(0.0f), Ni(0.0f), D(0.0f), Illum(0) {}

    String Name;
    CVector3 Ka;
    CVector3 Kd;
    CVector3 Ks;
    float Ns;
    float Ni;
    float D;
    int Illum;
    String MapKa;
    String MapKd;
    String MapKs;
    String MapNs;
    String MapD;
    String MapBump;
};
}
