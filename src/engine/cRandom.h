// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include <random>
#include <ctime>

namespace Forradia {

class cRandom {
 public:
    inline int Next() {

        return mt();
    }

 private:
    inline static std::mt19937 mt = std::mt19937(static_cast<unsigned int>(time(nullptr)));
};

}  // namespace Forradia
