// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once

#include <string>
#include <vector>
#include "File.h"
#include "../engine/Aliases.h"

namespace Forradia
{


    class Folder
    {
    public:
        Folder() = default;
        Folder(std::string _name, SPtr<Folder> _parentFolder) : name(_name), parentFolder(_parentFolder) {}

        std::string name = "Unnamed folder";
        std::vector<SPtr<Folder>> subFolders;
        std::vector<File> files;
        SPtr<Folder> parentFolder = nullptr;
    };

}  // namespace Forradia
