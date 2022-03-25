#include "Common.h"
#include "CScenesCollection.h"

namespace Forradia
{

    void CScenesCollection::Add(String sceneName, UPtr<CSceneBase> scene)
    {
        Scenes.insert({ GetId(sceneName), std::move(scene) });
    }

}
