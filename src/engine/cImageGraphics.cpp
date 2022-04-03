// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "cImageGraphics.h"

namespace Forradia {

void cImageGraphics::DrawImage(std::string ImageName, float X, float Y, float Width,
                        float Height) const {
    DrawImage(GetId(ImageName), X, Y, Width, Height);
  }

void cImageGraphics::DrawImage(int ImageNameId, float X, float Y, float Width,
                        float Height) const {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, engine.imageLoader.images[ImageNameId]);

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

cSizeF cImageGraphics::GetImageSizeF(std::string ImageName) const {
      auto canvasSize = utilities.GetCanvasSize();

      glBindTexture(GL_TEXTURE_2D,
                    engine.imageLoader.images.at(GetId(ImageName)));

      int w, h;
      int mipLevel = 0;

      glGetTexLevelParameteriv(GL_TEXTURE_2D, mipLevel, GL_TEXTURE_WIDTH, &w);
      glGetTexLevelParameteriv(GL_TEXTURE_2D, mipLevel, GL_TEXTURE_HEIGHT, &h);

      auto imageWidth = static_cast<float>(w) / canvasSize.width;
      auto imageHeight = static_cast<float>(h) / canvasSize.height;

      return {imageWidth, imageHeight};
  }

}  // namespace Forradia
