
#pragma once
#include "CommonExternal.h"
#include "../engine/Aliases.h"
#include "../engine/F_IEngine.h"

namespace Forradia
{

class F_ImageGraphics
{

public:

    F_ImageGraphics(F_IEngine& engine) : Engine(engine) {}

    // ---- Drawing operations ----

    inline void DrawImage(std::string ImageName, float X, float Y, float Width, float Height)
    {
        DrawImage(GetId(ImageName), X, Y, Width, Height);
    }

    inline void DrawImage(int ImageNameId, float X, float Y, float Width, float Height)
    {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        glOrtho(0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f);

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, Engine.ImageLoader.Images[ImageNameId]);

        glBegin(GL_QUADS);

        glColor3f(1.0f, 1.0f, 1.0f);

        glTexCoord2f(0, 0); glVertex2f(X, Y);
        glTexCoord2f(0, 1); glVertex2f(X, Y + Height);
        glTexCoord2f(1, 1); glVertex2f(X + Width, Y + Height);
        glTexCoord2f(1, 0); glVertex2f(X + Width, Y);

        glEnd();

        glDisable(GL_TEXTURE_2D);

    }

private:

    F_IEngine& Engine;

};

}
