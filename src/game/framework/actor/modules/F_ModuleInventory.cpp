
#include "F_ModuleInventory.h"

namespace Forradia
{

void F_ModuleInventory::ResetForNewFrame()
{}

void F_ModuleInventory::Update()
{}

void F_ModuleInventory::Add(int Position, std::string ObjectName)
{
    Objects.insert({ Position, MakeUPtr<F_Object>(ObjectName) });
}

}
