#pragma once
namespace Forradia
{

class CObject
{

public:
    CObject(std::string objectTypeName, bool randomScaling = True);

    // Object usage
    void UseOn(std::unique_ptr<CObject>& other);

    // Core
    int ObjectType = 0;

    // Rendering
    float Rotation = 0.0f;
    float Scaling = 1.0f;

private:
    void TransformInto(String objectName);

};

}
