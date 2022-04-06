// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "cActor.h"
#include "modules/cModuleMovement.h"
#include "../engine/iEngine.h"
#include "modules/cModuleMovementData.h"

namespace Forradia {

cActor::cActor(const iEngine &Engine_, float X, float Y,
               std::string ModelName_) :
    engine(Engine_), modelName(ModelName_),
    actorId(currentActorId++) {
    AddIfNotExists<cModuleMovementData>();
    GetModule<cModuleMovementData>().position = {X, Y};
}

void cActor::ResetForNewFrame() const {
  for (auto &[Key, Module] : modules)
    Module->ResetForNewFrame();
}

void cActor::Update() const {
  for (auto &[Key, Module] : modules)
    Module->Update();
}

int cActor::GetAnimatedModelId() const {
    if (!HasModule<cModuleMovementData>()) {
        return GetId(modelName);
    } else {
        auto ModelNameAnimated = modelName;

        if (GetModule<cModuleMovementData>().isWalking) {
          auto AnimIndex = ((Ticks() + actorId*10) % 300) / 75;

          if (AnimIndex > 0)
            ModelNameAnimated.append(std::to_string(AnimIndex));
        }

        if (engine.modelLoader.ModelExists(ModelNameAnimated))
            return GetId(ModelNameAnimated);
        else
            return GetId(modelName);
    }
}

}  // namespace Forradia
