#pragma once
#include "CModel3D.h"
namespace Forradia
{

class CModelLoader
{

public:

    inline void LoadModels()
    {
        Models.clear();
        ModelNames.clear();
        auto file_path = String(SDL_GetBasePath());
        file_path.append(ModelsPath);
        auto entries = std::filesystem::recursive_directory_iterator(file_path.c_str());
        auto index = 0;
        for (auto& file : entries)
        {
            auto full_filename = file.path().filename().string();
            auto filename = full_filename.substr(0, full_filename.find("."));
            auto image_name_hash = int();
            if (file.is_directory() || ModelNameExtension != full_filename.substr(full_filename.length() - ModelNameExtension.length(), ModelNameExtension.length()))
                continue;
            Forradia::CModel3D loaded_model;
            loaded_model.LoadFile(file.path().string());
            image_name_hash = GetId(filename);
            Models[image_name_hash] = loaded_model;
            ModelNames[image_name_hash] = filename;
        }
    }

    UMap<int, Forradia::CModel3D> Models;
    UMap<int, std::string> ModelNames;

private:

    const String ModelsPath = "/Resources/Models";
    const String ModelNameExtension = ".obj";
};

}
