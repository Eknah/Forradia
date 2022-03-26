
#pragma once
#include "CommonExternal.h"
#include "scene_primary/F_Camera.h"
#include "scene_primary/gui/F_Gui.h"
#include "scene_primary/F_MobsEngine.h"
#include "scene_primary/F_GameWorldRenderer.h"

namespace Forradia
{

class F_ScenePrimary : public F_SceneBase
{

public:

    F_ScenePrimary(F_Engine& engine) : F_SceneBase(engine), Gui(engine), Camera(engine), MobsEngine(engine), GameWorldRenderer(engine, Camera) {}

    void Enter() override;
    void Update() override;
    void Render() override;
    void DoMouseDown(Uint8 mouseButton) override;
    void DoMouseUp(Uint8 mouseButton) override;

private:

    F_Camera Camera;
    F_Gui Gui;
    F_Utilities Utilities;
    F_MobsEngine MobsEngine;
    F_GameWorldRenderer GameWorldRenderer;

};

}
