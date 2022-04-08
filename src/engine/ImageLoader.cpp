// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "ImageLoader.h"

namespace Forradia {

void ImageLoader::LoadImages() {
    images.clear();
    imageNames.clear();

    auto filePath = std::string(SDL_GetBasePath());
    filePath.append(imagesPath);

    auto entries =
        std::filesystem::recursive_directory_iterator(filePath.c_str());

    for (auto &file : entries) {
      auto fullFilename = file.path().filename().string();
      auto filename = fullFilename.substr(0, fullFilename.find("."));
      auto imageNameHash = int();

      if (file.is_directory() ||
          imageNameExtension !=
              fullFilename.substr(fullFilename.length() -
                                       imageNameExtension.length(),
                                   imageNameExtension.length()))
        continue;


      auto surface =
          SurfacePtr(IMG_Load(file.path().string().c_str()), SDL_Deleter());
      auto textureId = GLuint(images.size());

//    for (auto i = 0; i < surface->w*surface->h*4; i+= 4) {
//        auto p = (Uint8 *)surface->pixels;
//        auto temp = p[i + 2];
//        p[i + 2] = p[i + 1];
//        p[i + 1] = temp;
//    }

      glGenTextures(1, &textureId);
      glBindTexture(GL_TEXTURE_2D, textureId);

      int mode = GL_RGB;

      if (surface->format->BytesPerPixel == 4)
        mode = GL_RGBA;


      glTexImage2D(GL_TEXTURE_2D, 0, mode, surface->w, surface->h, 0, mode,
                   GL_UNSIGNED_BYTE, surface->pixels);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

      imageNameHash = GetId(filename);

      images[imageNameHash] = textureId;
      imageNames[imageNameHash] = filename;
    }
  }

}  // namespace Forradia
