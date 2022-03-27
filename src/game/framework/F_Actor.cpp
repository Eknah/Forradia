
#include "F_Actor.h"

namespace Forradia
{



void F_Actor::ResetForNewFrame()
{
    for (auto& [Key, Module] : Modules)
    {
        Module.ResetForNewFrame();
    }
}

void F_Actor::Update()
{
    for (auto& [Key, Module] : Modules)
    {
        Module.Update();
    }
}

}
