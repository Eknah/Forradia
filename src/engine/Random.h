// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include <random>
#include <ctime>

namespace Forradia {

class Random {
 public:
    Random();

    int Next() const;

 private:
    inline static std::uniform_int_distribution<int> result =
            std::uniform_int_distribution<int>(0, 10000);
    inline static std::random_device device;
    inline static bool isInitialized = false;
    inline static std::mt19937 mt;
};

}  // namespace Forradia
