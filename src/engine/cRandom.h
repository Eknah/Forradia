// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include <random>
#include <ctime>

namespace Forradia {

class cRandom {
 public:
    cRandom() {
        if (!IsInitialized) {
            mt = std::mt19937(rd());
            IsInitialized = true;
        }
    }

    inline int Next() const {
        return result(mt);
    }

 private:
    inline static std::uniform_int_distribution<int> result = std::uniform_int_distribution<int>(0, 10000);
    inline static std::random_device rd;
    inline static bool IsInitialized = false;
    inline static std::mt19937 mt;
};

}  // namespace Forradia
