// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "cTextGraphics.h"

namespace Forradia {

void cTextGraphics::Initialize() {
    TTF_Init();

    auto FontPath = std::string(SDL_GetBasePath());
    FontPath.append(DefaultFontPath);

    DefaultFont = UPtrEx<TTF_Font, cSDL_Deleter>(
        TTF_OpenFont(FontPath.c_str(), DefaultFontSize));
  }

void cTextGraphics::DrawString(std::string Text, SDL_Color Color, float X, float Y,
                         bool CenterAlign) const {
    GLuint Texture;

    glEnable(GL_TEXTURE_2D);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glGenTextures(1, &Texture);
    glBindTexture(GL_TEXTURE_2D, Texture);

    auto FontSurface =
        TTF_RenderText_Blended(DefaultFont.get(), Text.c_str(), Color);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, FontSurface->w, FontSurface->h, 0,
                 GL_BGRA, GL_UNSIGNED_BYTE, FontSurface->pixels);

    auto CanvasSize = Utilities.GetCanvasSize();

    auto Width = static_cast<float>(FontSurface->w)
            / CanvasSize.Width * Scaling;

    auto Height = static_cast<float>(FontSurface->h)
            / CanvasSize.Height * Scaling;

    glColor4f(Color.r / 255.0f, Color.g / 255.0f, Color.b / 255.0f,
              Color.a / 255.0f);

    if (CenterAlign) {
      X -= Width / 2;
      Y -= Height / 2;
    }

    glBegin(GL_QUADS);
    {
      glTexCoord2f(0, 1);
      glVertex2f(X, Y + Height);
      glTexCoord2f(1, 1);
      glVertex2f(X + Width, Y + Height);
      glTexCoord2f(1, 0);
      glVertex2f(X + Width, Y);
      glTexCoord2f(0, 0);
      glVertex2f(X, Y);
    }

    glEnd();

    glDeleteTextures(1, &Texture);
    SDL_FreeSurface(FontSurface);

    glDisable(GL_TEXTURE_2D);
  }

}  // namespace Forradia
