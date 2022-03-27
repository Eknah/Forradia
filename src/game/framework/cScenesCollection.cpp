
#include "cScenesCollection.h"

namespace Forradia
{

void cScenesCollection::Add(std::string sceneName, UPtr<cSceneBase> scene)
{
    Scenes.insert({ GetId(sceneName), std::move(scene) });
}

}
