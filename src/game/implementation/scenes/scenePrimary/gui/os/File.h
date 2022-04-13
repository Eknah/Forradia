// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once

#include <string>
#include <vector>

namespace Forradia
{

    class Console;

    class File
    {
    public:
        explicit File(Console& _console) : console(_console) {}
        File(Console& _console, std::string _name) : console(_console), name(_name) {}

        void GiveInput(std::string input);

        std::string name = "Unnamed folder";
        std::vector<std::string> outputText = {};

        bool runnable = false;

    private:
        Console& console;
    };

}  // namespace Forradia
