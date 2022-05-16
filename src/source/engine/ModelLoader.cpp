// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "ModelLoader.h"
#include <filesystem>

namespace Forradia
{

    void ModelLoader::LoadModels()
    {
        models.clear();
        modelNames.clear();

        auto file_path = std::string(SDL_GetBasePath());
        file_path.append(modelsPath);

        auto entries =
            std::filesystem::recursive_directory_iterator(file_path.c_str());

        for (auto& file : entries)
        {
            auto full_filename = file.path().filename().string();
            auto filename = full_filename.substr(0, full_filename.find("."));
            auto image_name_hash = int();

            if (file.is_directory() ||
                modelNameExtension !=
                full_filename.substr(full_filename.length() -
                    modelNameExtension.length(),
                    modelNameExtension.length()))
                continue;

            Forradia::Model3D loaded_model;
            loaded_model.LoadFile(file.path().string());

            image_name_hash = GetId(filename);

            models[image_name_hash] = loaded_model;
            modelNames[image_name_hash] = filename;
        }
    }

    bool ModelLoader::ModelExists(std::string ModelName) const
    {
        auto result = modelNames.count(GetId(ModelName)) > 0;
        return result;
    }

}  // namespace Forradia
