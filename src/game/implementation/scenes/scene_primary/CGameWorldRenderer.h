#pragma once
#include "CommonExternal.h"
#include "CCamera.h"
#include "CPlanetTransformator.h"
#include "CBackground.h"
#include "../core/CEngine.h"

namespace Forradia
{

class CGameWorldRenderer
{

public:

    CGameWorldRenderer(CEngine& engine, CCamera& camera) : Engine(engine), /*Skybox(engine),*/ Background(engine), PlanetTransformator(engine), Camera(camera) {}

    void Render();

private:

    CEngine& Engine;
    CBackground Background;
    CCamera& Camera;
    CPlanetTransformator PlanetTransformator;

};

}
