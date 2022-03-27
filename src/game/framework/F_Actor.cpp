
#include "F_Actor.h"

namespace Forradia
{

void F_Actor::AddModule(std::string ModuleName, F_IActorModule& Module)
{
    Modules.insert({GetId(ModuleName), Module});
}


F_IActorModule& F_Actor::GetModule(std::string ModuleName)
{
    return Modules.at(GetId(ModuleName));
}

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
