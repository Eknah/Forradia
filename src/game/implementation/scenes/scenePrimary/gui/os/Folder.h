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
        Folder(String _name, SPtr<Folder> _parentFolder) : name(_name), parentFolder(_parentFolder) {}

        String name = "Unnamed folder";
        List<SPtr<Folder>> subFolders;
        List<File> files;
        SPtr<Folder> parentFolder = nullptr;

    };

}  // namespace Forradia
