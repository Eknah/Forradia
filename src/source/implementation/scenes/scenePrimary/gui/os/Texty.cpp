// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "Texty.h"
#include "Console.h"

namespace Forradia
{
    Texty::Texty(Console& _console) : File(_console)
    {
        name = "Texty";
        runnable = true;
        outputText.push_back("Texty (Ctrl+S to Save) (Ctrl+Q to Quit)");
        outputText.push_back("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    }
}
