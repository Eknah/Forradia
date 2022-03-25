#include "Common.h"
#include "CInventory.h"
namespace Forradia
{
    void CInventory::Add(int position, String objectName)
    {
        Objects.insert({ position, MakeUPtr<CObject>(objectName) });
    }
}
