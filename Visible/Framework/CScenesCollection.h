#pragma once

namespace Forradia
{

class CScenesCollection
{

public:

    // Collection operations
    void Add(String sceneName, UPtr<CSceneBase> scene);

    // Collection structure
    UMap<int, UPtr<CSceneBase>> Scenes;

};

}
