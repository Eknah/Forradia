
#include "F_Inventory.h"
#include "../core/Aliases.h"

namespace Forradia
{

void F_Inventory::Add(int position, std::string objectName)
{
    Objects.insert({ position, MakeUPtr<F_Object>(objectName) });
}

}
