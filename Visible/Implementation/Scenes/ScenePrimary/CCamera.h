#pragma once
#include "../Hidden/CUtilities.h"

namespace Forradia
{

class CEngine;

class CCamera
{

public:

    CCamera(CEngine& engine) : Engine(engine) {}

    void Update(int rotationDirection, float zoomChange);
    void UpdateCameraMovement();

    float LookingAngle = 0.0f;
    float ZoomAmount = 2.0f;

    float RayCastingX = 0.0f;
    float RayCastingY = 0.0f;
    float RayCastingZ = 0.0f;

    CPoint2 GetHoveredTile();
    float CameraHeight = 0.0f;

    int GetRenderDistance();

private:

    CEngine& Engine;
    CUtilities Utilities;

    CPoint2 PreviousMousePosition = { -1, -1 };
    int RenderDistance = 80;
    int RenderDistanceCave = 15;
    int TickLastUpdate = 0;
    int UpdateSpeed = 20;
    float RotationAmount = 5.0f;
    float ZoomMultiplier = 8.0;

};


}
