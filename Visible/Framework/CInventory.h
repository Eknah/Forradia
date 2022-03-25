#pragma once
namespace Forradia
{
class CInventory
{
public:
    void Add(int position, String objectName);

    UMap<int, SPtr<CObject>> Objects;

};
}
