#include "CommonExternal.h"
#include "CImageGraphics.h"
#include "../Hidden/CEngine.h"
namespace Forradia
{
void CImageGraphics::DrawImage(String imageName, float X, float Y, float width, float height)
{
    DrawImage(GetId(imageName), X, Y, width, height);
}
void CImageGraphics::DrawImage(int imageNameHash, float X, float Y, float width, float height)
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glPushMatrix();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, Engine.ImageLoader.Images[imageNameHash]);
    int _width, _height;
    int miplevel = 0;
    glGetTexLevelParameteriv(GL_TEXTURE_2D, miplevel, GL_TEXTURE_WIDTH, &_width);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, miplevel, GL_TEXTURE_HEIGHT, &_height);
    glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0, 0); glVertex2f(X, Y);
    glTexCoord2f(0, 1); glVertex2f(X, Y + height);
    glTexCoord2f(1, 1); glVertex2f(X + width, Y + height);
    glTexCoord2f(1, 0); glVertex2f(X + width, Y);
    glEnd();
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
}
}
