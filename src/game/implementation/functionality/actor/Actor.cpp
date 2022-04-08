// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "Actor.h"
#include "modules/ModuleMovement.h"
#include "../engine/IEngine.h"
#include "modules/ModuleMovementData.h"

namespace Forradia {

Actor::Actor(const IEngine &_e, float x, float y,
               std::string modelName_) :
    e(_e), modelName(modelName_),
    actorId(currentActorId++) {
    AddIfNotExists<ModuleMovementData>();
    GetModule<ModuleMovementData>().position = {x, y};
}

void Actor::ResetForNewFrame() const {
  for (auto &[key, module] : modules)
    module->ResetForNewFrame();
}

void Actor::Update() const {
  for (auto &[key, module] : modules)
    module->Update();
}

int Actor::GetAnimatedModelId() const {
    if (!HasModule<ModuleMovementData>()) {
        return GetId(modelName);
    } else {
        auto modelNameAnimated = modelName;

        if (GetModule<ModuleMovementData>().isWalking) {
          auto animIndex = ((Ticks() + actorId*10) % 300) / 75;

          if (animIndex > 0)
            modelNameAnimated.append(std::to_string(animIndex));
        }

        if (e.modelLoader.ModelExists(modelNameAnimated))
            return GetId(modelNameAnimated);
        else
            return GetId(modelName);
    }
}

}  // namespace Forradia
