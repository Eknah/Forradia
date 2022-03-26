
#pragma once
#include "CommonExternal.h"
#include "../core/F_Utilities.h"
#include "framework/F_SceneBase.h"

namespace Forradia
{

class F_SceneMainMenu : public F_SceneBase
{

public:

    using F_SceneBase::F_SceneBase;

    void Enter() override {}
    void Update() override;
    void Render() override;
    void DoMouseDown(Uint8 mouseButton) override;
    void DoMouseUp(Uint8 mouseButton) override {}

private:

    F_Utilities Utilities;

};

}
