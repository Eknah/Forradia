
#pragma once
#include "CommonExternal.h"
#include "F_Camera.h"
#include "F_PlanetTransformator.h"
#include "F_Background.h"
#include "../engine/F_Engine.h"

namespace Forradia
{

class F_GameWorldRenderer
{

public:

    F_GameWorldRenderer(F_Engine& engine, F_Camera& camera) : Engine(engine), /*Skybox(engine),*/ Background(engine), PlanetTransformator(engine), Camera(camera) {}

    void Render();

private:

    F_Engine& Engine;
    F_Background Background;
    F_Camera& Camera;
    F_PlanetTransformator PlanetTransformator;

};

}
