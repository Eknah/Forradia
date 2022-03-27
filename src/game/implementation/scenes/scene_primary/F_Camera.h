
#pragma once
#include "../core/F_Utilities.h"

namespace Forradia
{

class F_Engine;

class F_Camera
{

public:

    F_Camera(F_Engine& engine) : Engine(engine) {}

    void Update(int rotationDirection, float zoomChange);
    void UpdateCameraMovement();

    float LookingAngle = 0.0f;
    float ZoomAmount = 2.0f;

    float RayCastingX = 0.0f;
    float RayCastingY = 0.0f;
    float RayCastingZ = 0.0f;

    F_Point2 GetHoveredTile();
    float CameraHeight = 0.0f;

    int GetRenderDistance();

private:

    F_Engine& Engine;
    F_Utilities Utilities;

    F_Point2 PreviousMousePosition = { -1, -1 };
    int RenderDistance = 80;
    int RenderDistanceCave = 15;
    unsigned int TickLastUpdate = 0;
    int UpdateSpeed = 20;
    float RotationAmount = 5.0f;
    float ZoomMultiplier = 8.0;

};


}
