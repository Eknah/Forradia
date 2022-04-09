// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "../engine/Aliases.h"
#include "../engine/IModule.h"

namespace Forradia {

class Object;

class ObjectUsageModule : public IModule {
 public:
  using IModule::IModule;

  void ResetForNewFrame() override;
  void Update() override;

  SPtr<Object> objectBeingUsed = nullptr;
};

}  // namespace Forradia
