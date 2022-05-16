// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)
//
// This source file is built upon source code from the OBJ-Loader
// repo by Bly7 at https://github.com/Bly7/OBJ-Loader

#pragma once
#include <vector>
#include <string>
#include "Aliases.h"

namespace Forradia
{

    class AlgorithmsStrings
    {
    public:
        void Split(const std::string& in, std::vector<std::string>* out, std::string token);

        std::string Tail(const std::string& in);

        std::string FirstToken(const std::string& in);
    };
}  // namespace Forradia
