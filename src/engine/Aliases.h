// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include <SDL2/SDL_timer.h>
#include <ctime>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace Forradia {

// Pointer related

template <typename T, typename U> using UMap = std::unordered_map<T, U>;

template <typename T> using UPtr = std::unique_ptr<T>;

template <typename T, typename U> using UPtrEx = std::unique_ptr<T, U>;

template <typename T> using SPtr = std::shared_ptr<T>;

template <typename T, typename... Args>
inline std::unique_ptr<T> MakeUPtr(Args &&...args) {
  return std::make_unique<T>(std::forward<Args>(args)...);
}

template <typename T, typename... Args>
inline std::shared_ptr<T> MakeSPtr(Args &&...args) {
  return std::make_shared<T>(std::forward<Args>(args)...);
}

// Commonly used functions

inline int GetId(std::string text) {
  return static_cast<int>(std::hash<std::string>{}(text));
}
constexpr auto Ticks = &SDL_GetTicks;

// Rarely used functions

inline void Randomize() { srand((unsigned int)time(NULL)); }

}  // namespace Forradia
