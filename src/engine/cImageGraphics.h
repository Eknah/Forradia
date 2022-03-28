// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "../engine/Aliases.h"
#include "../engine/iEngine.h"
#include "CommonExternal.h"

namespace Forradia {

class cImageGraphics {

public:
  cImageGraphics(iEngine &engine) : Engine(engine) {}

  // ---- Drawing operations ----

  inline void DrawImage(std::string ImageName, float X, float Y, float Width,
                        float Height) {
    DrawImage(GetId(ImageName), X, Y, Width, Height);
  }

  inline void DrawImage(int ImageNameId, float X, float Y, float Width,
                        float Height) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, Engine.ImageLoader.Images[ImageNameId]);

    glBegin(GL_QUADS);

    glColor3f(1.0f, 1.0f, 1.0f);

    glTexCoord2f(0, 0);
    glVertex2f(X, Y);
    glTexCoord2f(0, 1);
    glVertex2f(X, Y + Height);
    glTexCoord2f(1, 1);
    glVertex2f(X + Width, Y + Height);
    glTexCoord2f(1, 0);
    glVertex2f(X + Width, Y);

    glEnd();

    glDisable(GL_TEXTURE_2D);
  }

private:
  iEngine &Engine;
};

} // namespace Forradia
