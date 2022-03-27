
#pragma once
#include "../engine/Aliases.h"
#include "cSceneBase.h"

namespace Forradia
{

class cScenesCollection
{

public:

    // Collection operations
    void Add(std::string sceneName, UPtr<cSceneBase> scene);

    // Collection structure
    UMap<int, UPtr<cSceneBase>> Scenes;

};

}
