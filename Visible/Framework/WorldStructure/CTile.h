#pragma once
namespace Forradia
{

class CEngine;
class CObject;

class CTile
{

public:
    CTile(CEngine& engine) : Engine(engine) {}

    bool MovementBlocked();
    bool HasObjectOfType(String objectName);

    int GroundType = 0;
    List<UPtr<CObject>> Objects;
    int Elevation = 0;
    UPtr<CMob> mob = nullptr;
    int WarpToMap = -1;

private:
    CEngine& Engine;

};

}
