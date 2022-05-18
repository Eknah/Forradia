// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "TextGraphics.h"
#include <iostream>

namespace Forradia
{
    void TextGraphics::Init()
    {
        TTF_Init();

        auto fontPath = std::string(SDL_GetBasePath());
        fontPath.append(defaultFontPath);

        defaultFont = UPtrEx<TTF_Font, SDL_Deleter>(
            TTF_OpenFont(fontPath.c_str(), defaultFontSize));
    }

    void TextGraphics::DrawString(std::string text, SDL_Color color, Point2F point, bool centerAlign, float specificScaling)
    {
        DrawString(text, color, point.x, point.y, centerAlign, specificScaling);
    }

    void TextGraphics::DrawString(std::string text, SDL_Color color, float x, float y, bool centerAlign, float specificScaling)
    {

        drawStringOperations.push_back(DrawStringOperation {text, color, x, y, centerAlign, specificScaling});
    }

    void TextGraphics::RenderAllStrings()
    {
        for (auto& oper : drawStringOperations)
        {
            DrawStringActual(oper.text, oper.color, oper.x, oper.y, oper.centerAlign, oper.specificScaling);
        }


        drawStringOperations.clear();
    }

    void TextGraphics::DrawStringActual(std::string text, SDL_Color color, float x, float y,
        bool centerAlign, float specificScaling) const
    {
        if (text == "")
            return;

        GLuint texture;


        glEnable(GL_TEXTURE_2D);

        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();

        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);

        auto fontSurface =
            TTF_RenderText_Blended(defaultFont.get(), text.c_str(), color);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, fontSurface->w, fontSurface->h, 0,
            GL_BGRA, GL_UNSIGNED_BYTE, fontSurface->pixels);

        auto canvasSize = utils.GetCanvasSize();

        auto width = static_cast<float>(fontSurface->w)
            / canvasSize.w * scaling * specificScaling;

        auto height = static_cast<float>(fontSurface->h)
            / canvasSize.h * scaling * specificScaling;

        glColor4f(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f,
            color.a / 255.0f);

        if (centerAlign)
        {
            x -= width / 2;
            y -= height / 2;
        }


        glBegin(GL_QUADS);
        {
            glTexCoord2f(0, 1);
            glVertex2f(x, y + height);
            glTexCoord2f(1, 1);
            glVertex2f(x + width, y + height);
            glTexCoord2f(1, 0);
            glVertex2f(x + width, y);
            glTexCoord2f(0, 0);
            glVertex2f(x, y);
        }

        glEnd();

        glDeleteTextures(1, &texture);
        SDL_FreeSurface(fontSurface);

        glDisable(GL_TEXTURE_2D);
    }
}