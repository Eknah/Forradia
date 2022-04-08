// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "Actor.h"
#include "modules/ModuleMovement.h"
#include "../engine/iEngine.h"
#include "modules/ModuleMovementData.h"

namespace Forradia {

cActor::cActor(const iEngine &engine_, float x, float y,
               std::string modelName_) :
    engine(engine_), modelName(modelName_),
    actorId(currentActorId++) {
    AddIfNotExists<cModuleMovementData>();
    GetModule<cModuleMovementData>().position = {x, y};
}

void cActor::ResetForNewFrame() const {
  for (auto &[key, module] : modules)
    module->ResetForNewFrame();
}

void cActor::Update() const {
  for (auto &[key, module] : modules)
    module->Update();
}

int cActor::GetAnimatedModelId() const {
    if (!HasModule<cModuleMovementData>()) {
        return GetId(modelName);
    } else {
        auto modelNameAnimated = modelName;

        if (GetModule<cModuleMovementData>().isWalking) {
          auto animIndex = ((Ticks() + actorId*10) % 300) / 75;

          if (animIndex > 0)
            modelNameAnimated.append(std::to_string(animIndex));
        }

        if (engine.modelLoader.ModelExists(modelNameAnimated))
            return GetId(modelNameAnimated);
        else
            return GetId(modelName);
    }
}

}  // namespace Forradia
