#pragma once
#include <string>
#include <memory>
#include "../core/Aliases.h"

namespace Forradia
{

class F_Object
{

public:

    F_Object(std::string objectTypeName, bool randomScaling = true);

    // Object usage
    void UseOn(std::unique_ptr<F_Object>& other);

    // Core
    int ObjectType = 0;

    // Rendering
    float Rotation = 0.0f;
    float Scaling = 1.0f;

private:

    void TransformInto(std::string objectName);

};

}
