// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "InventoryModule.h"
#include "Object.h"

namespace Forradia
{

    void InventoryModule::ResetForNewFrame() {}

    void InventoryModule::Update() {}

    void InventoryModule::Add(int position, std::string objectName)
    {
        inventory.objects.insert({ position, MakeSPtr<Object>(objectName) });
    }

}