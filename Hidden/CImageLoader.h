#pragma once
namespace Forradia
{


class CImageLoader
{
public:
    inline void LoadImages()
    {
        Images.clear();
        ImageNames.clear();
        auto file_path = String(SDL_GetBasePath());
        file_path.append(ImagesPath);
        auto entries = std::filesystem::recursive_directory_iterator(file_path.c_str());
        auto index = 0;
        for (auto& file : entries)
        {
            auto full_filename = file.path().filename().string();
            auto filename = full_filename.substr(0, full_filename.find("."));
            auto image_name_hash = int();
            if (file.is_directory() || ImageNameExtension != full_filename.substr(full_filename.length() - ImageNameExtension.length(), ImageNameExtension.length()))
                continue;
            auto surface = SurfacePtr(IMG_Load(file.path().string().c_str()), CSDL_Deleter());
            auto texture_id = GLuint(Images.size());
            glGenTextures(1, &texture_id);
            glBindTexture(GL_TEXTURE_2D, texture_id);
            int mode = GL_RGB;
            if (surface->format->BytesPerPixel == 4)
                mode = GL_RGBA;
            glTexImage2D(GL_TEXTURE_2D, 0, mode, surface->w, surface->h, 0, mode, GL_UNSIGNED_BYTE, surface->pixels);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            image_name_hash = GetId(filename);
            Images[image_name_hash] = texture_id;
            ImageNames[image_name_hash] = filename;
        }
    }

    UMap<int, GLuint> Images;
    UMap<int, String> ImageNames;

private:

    const String ImagesPath = "/Resources/Images";
    const String ImageNameExtension = ".png";
};

}
