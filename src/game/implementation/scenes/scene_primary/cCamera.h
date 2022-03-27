
#pragma once
#include "../engine/cUtilities.h"

namespace Forradia
{

class cEngine;

class cCamera
{

public:

    cCamera(cEngine& engine) : Engine(engine) {}

    void Update(int rotationDirection, float zoomChange);
    void UpdateCameraMovement();

    float LookingAngle = 0.0f;
    float ZoomAmount = 2.0f;

    float RayCastingX = 0.0f;
    float RayCastingY = 0.0f;
    float RayCastingZ = 0.0f;

    cPoint2 GetHoveredTile();
    float CameraHeight = 0.0f;

    int GetRenderDistance();

private:

    cEngine& Engine;
    cUtilities Utilities;

    cPoint2 PreviousMousePosition = { -1, -1 };
    int RenderDistance = 80;
    int RenderDistanceCave = 15;
    unsigned int TickLastUpdate = 0;
    int UpdateSpeed = 20;
    float RotationAmount = 5.0f;
    float ZoomMultiplier = 8.0;

};


}