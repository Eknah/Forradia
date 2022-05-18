// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include <SDL2/SDL.h>
#include <ctime>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include <utility>

namespace Forradia
{
    template <typename T, typename U>
    using UMap = std::unordered_map<T, U>;

    // Pointer related

    template <typename T>
    using UPtr = std::unique_ptr<T>;

    template <typename T, typename U>
    using UPtrEx = std::unique_ptr<T, U>;

    template <typename T>
    using SPtr = std::shared_ptr<T>;

    template <typename T, typename... Args>
    inline std::unique_ptr<T> MakeUPtr(Args &&...args)
    {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }

    template <typename T, typename... Args>
    inline std::shared_ptr<T> MakeSPtr(Args &&...args)
    {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }

    // Commonly used

    inline int GetId(std::string text)
    {
        return static_cast<int>(std::hash<std::string>{}(text));
    }
    constexpr auto Ticks = &SDL_GetTicks;

    inline float CFloat(int val)
    {
        return static_cast<float>(val);
    }

    inline float CFloat(double val)
    {
        return static_cast<float>(val);
    }

    inline int CInt(float val)
    {
        return static_cast<int>(val);
    }

    // Common types

    using String = std::string;

    template <typename T>
    using List = std::vector<T>;

    template <typename T, typename U>
    using Tuple = std::tuple<T, U>;
}  // namespace Forradia
