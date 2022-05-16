// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "FileSystem.h"
#include "Console.h"
#include "Engine.h"
#include <iostream>
#include "Texty.h"

namespace Forradia
{

    FileSystem::FileSystem(Console& _console) : console(_console)
    {
        currentFolder = MakeSPtr<Folder>("Top", nullptr);
        currentFolder->subFolders.push_back(MakeSPtr<Folder>("Home", SPtr<Folder>(currentFolder)));
        currentFolder->subFolders.push_back(MakeSPtr<Folder>("Doc", SPtr<Folder>(currentFolder)));
        currentFolder->files.push_back(File(console, "Forradia.str"));

        auto programFolder = MakeSPtr<Folder>("Programs", SPtr<Folder>(currentFolder));
        programFolder->files.push_back(Texty(console));
        currentFolder->subFolders.push_back(programFolder);
    }

    void FileSystem::PrintCurrentDirectory()
    {
        console.Print("Listing contents of current folder: " + currentFolder->name);

        if (currentFolder->subFolders.size() == 0 && currentFolder->files.size() == 0)
        {
            console.Print("Folder is empty");
        }
        else
        {
            for (auto& folder : currentFolder->subFolders)
                console.Print(folder->name + "/");
            
            for (auto& file : currentFolder->files)
                console.Print(file.name);
        }
    }

    void FileSystem::MoveToFolder(String folderName)
    {
        if (folderName == "..")
        {
            currentFolder = currentFolder->parentFolder;
        }
        else
        {
            auto i = 0;

            for (auto& folder : currentFolder->subFolders)
            {
                if (folder->name == folderName)
                {
                    currentFolder = folder;
                    break;
                }
                i++;
            }
        }

        console.Print("Now in folder: " + currentFolder->name);
    }

    void FileSystem::RunProgram(String programName)
    {
        for (auto& file : currentFolder->files)
        {
            if (file.name == programName)
            {
                if (file.runnable)
                {
                    runningProgram = SPtr<File>(&file);
                    console.Print("Running program: " + programName);
                    return;
                }
                else
                {
                    console.Print("File not runnable");
                    return;
                }
            }
        }

        console.Print("No file with name: " + programName);
    }

}
