#pragma once
#include "CommonExternal.h"
#include "scene_primary/CCamera.h"
#include "scene_primary/gui/CGui.h"
#include "scene_primary/CMobsEngine.h"
#include "scene_primary/CGameWorldRenderer.h"

namespace Forradia
{

class CScenePrimary : public CSceneBase
{

public:

    CScenePrimary(CEngine& engine) : CSceneBase(engine), Gui(engine), Camera(engine), MobsEngine(engine), GameWorldRenderer(engine, Camera) {}

    void Enter() override;
    void Update() override;
    void Render() override;
    void DoMouseDown(Uint8 mouseButton) override;
    void DoMouseUp(Uint8 mouseButton) override;

private:

    CCamera Camera;
    CGui Gui;
    CUtilities Utilities;
    CMobsEngine MobsEngine;
    CGameWorldRenderer GameWorldRenderer;

};

}
