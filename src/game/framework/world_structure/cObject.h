
#pragma once
#include <string>
#include <memory>
#include "../engine/Aliases.h"

namespace Forradia
{

class cObject
{

public:

    cObject(std::string ObjectTypeName, bool RandomScaling = true);

    // Object usage
    void UseOn(std::unique_ptr<cObject>& Other);

    // Core
    int ObjectType = 0;

    // Rendering
    float Rotation = 0.0f;
    float Scaling = 1.0f;

private:

    void TransformInto(std::string ObjectName);

};

}
