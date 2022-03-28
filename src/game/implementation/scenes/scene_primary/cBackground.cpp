// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "cBackground.h"
#include "../engine/cEngine.h"

namespace Forradia {

void cBackground::Render(float Zoom) {
  if (Engine.GetCurrentMapArea().IsUnderground()) {
    glClearColor(0, 0, 0, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
  } else {
    glClearColor(0, 0.4f, 1, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
  }

  //    if (Engine.GetCurrentMapArea().IsCave)
  //    {
  //        glClearColor(0, 0, 0, 1.0f);
  //        glClear(GL_COLOR_BUFFER_BIT);
  //    }
  //    else
  //    {
  //        auto blackness = std::pow(zoom / 4.0f, 2.0f);
  //        auto r = 0.0f;
  //        auto g = std::max(std::min(0.15f / (blackness * 4.0f), 1.0f), 0.0f);
  //        auto b = std::max(std::min(1.0f / blackness, 1.0f), 0.0f);

  //        glClearColor(r, g, b, 1.0f);
  //        glClear(GL_COLOR_BUFFER_BIT);
  //    }
}

} // namespace Forradia
