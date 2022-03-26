
#include "F_ScenesCollection.h"

namespace Forradia
{

void F_ScenesCollection::Add(std::string sceneName, UPtr<F_SceneBase> scene)
{
    Scenes.insert({ GetId(sceneName), std::move(scene) });
}

}
