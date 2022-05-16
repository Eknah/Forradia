// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once

namespace Forradia
{

    class IEngine;
    class Actor;

    class IModule
    {
    public:
        IModule(const IEngine& _e, Actor* _parentActor) : e(_e), parentActor(_parentActor)
        {}

        virtual void ResetForNewFrame() = 0;
        virtual void Update() = 0;

        Actor& GetParentActor();

    protected:
        const IEngine& e;

    private:
        Actor* parentActor;
    };

}  // namespace Forradia
