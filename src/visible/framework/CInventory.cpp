#include "CInventory.h"
#include "../hidden/Aliases.h"

namespace Forradia
{

void CInventory::Add(int position, std::string objectName)
{
    Objects.insert({ position, MakeUPtr<CObject>(objectName) });
}

}
