// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once

#include <string>
#include <vector>
#include "Aliases.h"

namespace Forradia
{
    class Console;

    class File
    {
        // Functions
    public:
        explicit File(Console& _console)
		: console(_console) {}
		
        File(Console& _console, String _name)
		: console(_console), name(_name) {}

        void GiveInput(std::string input);

        // Members
        String name = "Unnamed folder";
        List<String> outputText = {};
        bool runnable = false;

    private:
        Console& console;
    };
}