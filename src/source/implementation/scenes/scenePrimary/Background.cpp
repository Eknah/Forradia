// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "Background.h"
#include "Engine.h"

namespace Forradia
{
    void Background::Render(float zoom)
    {
        //glClearColor(0.0f, 0.2f, 0.4f, 1.0f);
        //glClear(GL_COLOR_BUFFER_BIT);

        if (e.GetCurrMapArea().IsUnderground())
        {
            glClearColor(0, 0, 0, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
        }
        else
        {
            glClearColor(0.0f, 0.6f, 0.9f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
        }
    }
}