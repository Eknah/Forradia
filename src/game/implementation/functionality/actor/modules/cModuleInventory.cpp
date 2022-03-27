
#include "cModuleInventory.h"

namespace Forradia
{

void cModuleInventory::ResetForNewFrame()
{}

void cModuleInventory::Update()
{}

void cModuleInventory::Add(int Position, std::string ObjectName)
{
    Objects.insert({ Position, MakeUPtr<cObject>(ObjectName) });
}

}
