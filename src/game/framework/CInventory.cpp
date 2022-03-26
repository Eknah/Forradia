#include "CInventory.h"
#include "../core/Aliases.h"

namespace Forradia
{

void CInventory::Add(int position, std::string objectName)
{
    Objects.insert({ position, MakeUPtr<CObject>(objectName) });
}

}
