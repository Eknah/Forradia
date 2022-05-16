// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once

#include "Folder.h"

namespace Forradia
{

    class Console;

    class FileSystem
    {

        // Functions

    public:

        explicit FileSystem(Console& _console);

        void PrintCurrentDirectory();
        void MoveToFolder(String folderName);
        void RunProgram(String programName);

        // Members

    public:
        SPtr<File> runningProgram = nullptr;

    private:
        Console& console;
        SPtr<Folder> currentFolder = nullptr;


    };

}  // namespace Forradia
