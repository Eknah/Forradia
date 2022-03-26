#pragma once
#include "../hidden/Aliases.h"
#include "CSceneBase.h"

namespace Forradia
{

class CScenesCollection
{

public:

    // Collection operations
    void Add(std::string sceneName, UPtr<CSceneBase> scene);

    // Collection structure
    UMap<int, UPtr<CSceneBase>> Scenes;

};

}
