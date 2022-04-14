// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glu.h>
#include "../engine/Utilities.h"
#include "../engine/Timer.h"

namespace Forradia
{

    class Engine;

    class Camera
    {

    public:

        explicit Camera(const Engine& _e) : e(_e), timer(UPtr<int>(&updateSpeed)) {}

        void SetupCamera() const;
        void Update();
        void UpdateRotation(int rotationDirection);
        void UpdateZoomChange(float zoomChange);
        void UpdateCameraMovement();

        float lookingAngle = 0.0f;
        float zoomAmount = 2.0f;

        float rayCastingX = 0.0f;
        float rayCastingY = 0.0f;
        float rayCastingZ = 0.0f;
        float cameraHeight = 0.0f;

        int GetRenderDistance() const;
        Point2 GetHoveredTile() const;

    private:
        const Engine& e;
        Utilities utils;

        Point2 previousMousePos = { -1, -1 };
        int renderDistance = 80;
        int renderDistanceCave = 15;
        unsigned int tickLastUpdate = 0;
        int updateSpeed = 20;
        float rotationAmount = 5.0f;
        float zoomMultiplier = 8.0;

        Timer timer;

    };

}  // namespace Forradia
