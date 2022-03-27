
#include "cActor.h"

namespace Forradia
{

void cActor::ResetForNewFrame()
{
    for (auto& [Key, Module] : Modules)
    {
        Module->ResetForNewFrame();
    }
}

void cActor::Update()
{
    for (auto& [Key, Module] : Modules)
    {
        Module->Update();
    }
}

}
