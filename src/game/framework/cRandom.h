// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include <random>
#include <ctime>

namespace Forradia {


class cRandom {

 public:


    inline int Generate() {

        return mt();
    }

 private:
    std::mt19937 mt = std::mt19937(time(nullptr));
    //std::mt19937 mt = std::mt19937(1);
};

}  // namespace Forradia
