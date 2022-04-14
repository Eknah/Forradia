// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "Background.h"
#include "../engine/Engine.h"

namespace Forradia
{

    void Background::Render(float zoom)
    {
        if (e.GetCurrMapArea().IsUnderground())
        {
            glClearColor(0, 0, 0, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
        }
        else
        {
            glClearColor(0.0f, 0.5f, 1.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
        }

    }

}  // namespace Forradia
