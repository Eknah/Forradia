
#pragma once
#include "CommonExternal.h"
#include "scene_primary/cCamera.h"
#include "scene_primary/gui/cGui.h"
#include "scene_primary/cMobsEngine.h"
#include "scene_primary/cGameWorldRenderer.h"

namespace Forradia
{

class cScenePrimary : public cSceneBase
{

public:

    cScenePrimary(cEngine& engine) : cSceneBase(engine), Gui(engine), Camera(engine), MobsEngine(engine), GameWorldRenderer(engine, Camera) {}

    void Enter() override;
    void Update() override;
    void Render() override;
    void DoMouseDown(Uint8 mouseButton) override;
    void DoMouseUp(Uint8 mouseButton) override;

private:

    cCamera Camera;
    cGui Gui;
    cUtilities Utilities;
    cMobsEngine MobsEngine;
    cGameWorldRenderer GameWorldRenderer;

};

}
