// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include <SDL2/SDL_filesystem.h>
#include <string>
#include "cModel3D.h"

namespace Forradia {

class cModelLoader {
 public:
  void LoadModels();

  bool ModelExists(std::string ModelName) const;

  UMap<int, Forradia::cModel3D> Models;
  UMap<int, std::string> ModelNames;

 private:
  const std::string ModelsPath = "/Resources/Models";
  const std::string ModelNameExtension = ".obj";
};

}  // namespace Forradia
