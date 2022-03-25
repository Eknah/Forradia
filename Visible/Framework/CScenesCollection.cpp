#include "CScenesCollection.h"

namespace Forradia
{

void CScenesCollection::Add(std::string sceneName, UPtr<CSceneBase> scene)
{
    Scenes.insert({ GetId(sceneName), std::move(scene) });
}

}
