// Copyright (C) 2022  Andreas Åkerberg

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

    cGameWorldRenderer(cEngine& Engine_, cCamera& Camera_) : Engine(Engine_), Background(Engine_), PlanetTransformator(Engine_), Camera(Camera_) {}

    void                    Render();

private:

    cEngine&                Engine;
    cBackground             Background;
    cCamera&                Camera;
    cPlanetTransformator    PlanetTransformator;

};

}
