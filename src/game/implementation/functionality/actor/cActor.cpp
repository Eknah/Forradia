// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "cActor.h"
#include "modules/cModuleMovement.h"
#include "../engine/iEngine.h"
#include "modules/cModuleMovementData.h"

namespace Forradia {

cActor::cActor(const iEngine &Engine_, float X, float Y,
               std::string ModelName_) :
    Engine(Engine_), ModelName(ModelName_),
    ActorId(CurrentActorId++) {
    AddIfNotExists<cModuleMovementData>();
    GetModule<cModuleMovementData>().Position = {X, Y};
}

void cActor::ResetForNewFrame() const {
  for (auto &[Key, Module] : Modules)
    Module->ResetForNewFrame();
}

void cActor::Update() const {
  for (auto &[Key, Module] : Modules)
    Module->Update();
}

int cActor::GetAnimatedModelId() const {
    if (!HasModule<cModuleMovementData>()) {
        return GetId(ModelName);
    } else {
        auto ModelNameAnimated = ModelName;

        if (GetModule<cModuleMovementData>().IsWalking) {
          auto AnimIndex = ((Ticks() + ActorId*10) % 300) / 75;

          if (AnimIndex > 0)
            ModelNameAnimated.append(std::to_string(AnimIndex));
        }

        if (Engine.modelLoader.ModelExists(ModelNameAnimated))
            return GetId(ModelNameAnimated);
        else
            return GetId(ModelName);
    }
}

}  // namespace Forradia
