// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "SceneServer.h"
#include "../engine/Engine.h"

namespace Forradia
{

    void SceneServer::Enter()
    {

    }

    void SceneServer::Update()
    {

    }

    void SceneServer::Render()
    {
        e.DrawImage("SceneGameStartBackground", 0, 0, 1, 1);
    }

}  // namespace Forradia
