
#include "CommonExternal.h"
#include "F_TextGraphics.h"
#include "../core/F_Engine.h"

namespace Forradia
{

void F_TextGraphics::Initialize()
{
    TTF_Init();

    auto font_path = std::string(SDL_GetBasePath());
    font_path.append(DefaultFontPath);

    DefaultFont = UPtrEx<TTF_Font, F_SDL_Deleter>(TTF_OpenFont(font_path.c_str(), DefaultFontSize));
}

void F_TextGraphics::DrawString(std::string message, SDL_Color color, float x, float y, bool centerAlign)
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glEnable(GL_TEXTURE_2D);
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    SDL_Surface* s_font = TTF_RenderText_Blended(DefaultFont.get(), message.c_str(), color);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, s_font->w, s_font->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, s_font->pixels);
    auto canvasSize = Utilities.GetCanvasSize();
    auto width = (float)s_font->w / canvasSize.Width * Scaling;
    auto height = (float)s_font->h / canvasSize.Height * Scaling;
    glColor4f(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, color.a / 255.0f);

    if (centerAlign)
    {
        x -= width/2;
        y -= height/2;
    }

    glBegin(GL_QUADS);
    {
        glTexCoord2f(0, 1); glVertex2f(x, y + height);
        glTexCoord2f(1, 1); glVertex2f(x + width, y + height);
        glTexCoord2f(1, 0); glVertex2f(x + width, y);
        glTexCoord2f(0, 0); glVertex2f(x, y);
    }

    glEnd();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glDeleteTextures(1, &texture);
    SDL_FreeSurface(s_font);
}

}