// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include <string>
#include "cModel3D.h"

namespace Forradia {

class cModelLoader {
 public:
  inline void LoadModels() {
    Models.clear();
    ModelNames.clear();

    auto file_path = std::string(SDL_GetBasePath());
    file_path.append(ModelsPath);

    auto entries =
        std::filesystem::recursive_directory_iterator(file_path.c_str());

    for (auto &file : entries) {
      auto full_filename = file.path().filename().string();
      auto filename = full_filename.substr(0, full_filename.find("."));
      auto image_name_hash = int();

      if (file.is_directory() ||
          ModelNameExtension !=
              full_filename.substr(full_filename.length() -
                                       ModelNameExtension.length(),
                                   ModelNameExtension.length()))
        continue;

      Forradia::cModel3D loaded_model;
      loaded_model.LoadFile(file.path().string());

      image_name_hash = GetId(filename);

      Models[image_name_hash] = loaded_model;
      ModelNames[image_name_hash] = filename;
    }
  }

  inline bool ModelExists(std::string ModelName) const {
    auto result = ModelNames.count(GetId(ModelName)) > 0;
    return result;
  }

  UMap<int, Forradia::cModel3D> Models;
  UMap<int, std::string> ModelNames;

 private:
  const std::string ModelsPath = "/Resources/Models";
  const std::string ModelNameExtension = ".obj";
};

}  // namespace Forradia
