// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "Actor.h"
#include "DestMovmModule.h"
#include "IEngine.h"
#include "CoreMovmModule.h"

namespace Forradia
{
    Actor::Actor(const IEngine& _e, float x, float y, std::string modelName_) :
	e(_e), modelName(modelName_), actorId(currentActorId++)
    {
        AddIfNotExists<CoreMovmModule>();
        GetModule<CoreMovmModule>().position = { x, y };
    }

    void Actor::ResetForNewFrame() const
    {
        for (auto& [key, module] : modules)
            module->ResetForNewFrame();
    }

    void Actor::Update() const
    {
        for (auto& [key, module] : modules)
            module->Update();
    }

    int Actor::GetAnimatedModelId() const
    {
        if (!HasModule<CoreMovmModule>())
        {
            return GetId(modelName);
        }
        else
        {
            auto modelNameAnimated = modelName;

            if (GetModule<CoreMovmModule>().isWalking)
            {
                auto animIndex = ((Ticks() + actorId * 10) % 600) / 150;

                if (animIndex > 0)
                    modelNameAnimated.append(std::to_string(animIndex));
            }

            if (e.modelLoader.ModelExists(modelNameAnimated))
                return GetId(modelNameAnimated);
            else
                return GetId(modelName);
        }
    }

}