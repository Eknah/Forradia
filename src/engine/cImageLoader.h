// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include <GL/glew.h>
#include <SDL2/SDL_image.h>
#include <filesystem>
#include <string>
#include "Aliases.h"
#include "Typedefs.h"
#include "cSDL_Deleter.h"

namespace Forradia {

class cImageLoader {
 public:
  void LoadImages();

  UMap<int, GLuint> images;
  UMap<int, std::string> imageNames;

 private:
  const std::string imagesPath = "/Resources/Images";
  const std::string imageNameExtension = ".png";
};

}  // namespace Forradia
