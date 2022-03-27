
#pragma once
#include "CommonExternal.h"
#include "cCamera.h"
#include "cPlanetTransformator.h"
#include "cBackground.h"
#include "../engine/cEngine.h"

namespace Forradia
{

class cGameWorldRenderer
{

public:

    cGameWorldRenderer(cEngine& engine, cCamera& camera) : Engine(engine), /*Skybox(engine),*/ Background(engine), PlanetTransformator(engine), Camera(camera) {}

    void Render();

private:

    cEngine& Engine;
    cBackground Background;
    cCamera& Camera;
    cPlanetTransformator PlanetTransformator;

};

}
