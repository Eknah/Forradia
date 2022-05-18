// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "ImageGraphics.h"
#include <iostream>

namespace Forradia
{

    void ImageGraphics::DrawImage(std::string imageName, float x, float y, float width, float height) const
    {
        DrawImage(GetId(imageName), x, y, width, height);
    }

    void ImageGraphics::DrawImage(int imageNameId, float x, float y, float width, float height) const
    {

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        glOrtho(0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f);

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, e.imageLoader.images[imageNameId]);

        glBegin(GL_QUADS);

        glColor3f(1.0f, 1.0f, 1.0f);

        glTexCoord2f(0, 0);
        glVertex2f(x, y);
        glTexCoord2f(0, 1);
        glVertex2f(x, y + height);
        glTexCoord2f(1, 1);
        glVertex2f(x + width, y + height);
        glTexCoord2f(1, 0);
        glVertex2f(x + width, y);

        glEnd();

        glDisable(GL_TEXTURE_2D);

    }

    SizeF ImageGraphics::GetImageSizeF(std::string imageName) const
    {

        glBindTexture(GL_TEXTURE_2D,
            e.imageLoader.images.at(GetId(imageName)));

        int w, h;
        int mipLevel = 0;

        glGetTexLevelParameteriv(GL_TEXTURE_2D, mipLevel, GL_TEXTURE_WIDTH, &w);
        glGetTexLevelParameteriv(GL_TEXTURE_2D, mipLevel, GL_TEXTURE_HEIGHT, &h);

        auto imageWidth = static_cast<float>(w) / utils.GetOrigCanvasSize().w;
        auto imageHeight = static_cast<float>(h) / utils.GetOrigCanvasSize().h;


        //std::cout << utils.GetOrigCanvasSize().w << " " << utils.GetOrigCanvasSize().h << std::endl;

        return { imageWidth, imageHeight };
    }

}  // namespace Forradia
