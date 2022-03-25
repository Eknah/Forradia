#pragma once

#include <string>
#include <unordered_map>
#include <memory>
#include <vector>
#include <SDL2/SDL_timer.h>

namespace Forradia
{

// Pointers

template <typename T, typename U>
using UMap = std::unordered_map<T, U>;

template <typename T>
using UPtr = std::unique_ptr<T>;

template <typename T, typename U>
using UPtrEx = std::unique_ptr<T, U>;

template <typename T>
using SPtr = std::shared_ptr<T>;

template <typename T, typename... Args>
inline std::unique_ptr<T> MakeUPtr(Args && ... args)
{
    return std::make_unique<T>(std::forward<Args>(args)...);
}

// Common used functions

inline int GetId(std::string text) { return (int)std::hash<std::string>{}(text); }
constexpr auto Ticks = &SDL_GetTicks;

// Rarely used functions

inline void Randomize() {srand(time(NULL));}

}
