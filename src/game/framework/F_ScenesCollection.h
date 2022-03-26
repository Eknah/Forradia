#pragma once
#include "../core/Aliases.h"
#include "F_SceneBase.h"

namespace Forradia
{

class F_ScenesCollection
{

public:

    // Collection operations
    void Add(std::string sceneName, UPtr<F_SceneBase> scene);

    // Collection structure
    UMap<int, UPtr<F_SceneBase>> Scenes;

};

}
