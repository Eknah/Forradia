#pragma once

namespace Forradia
{

constexpr auto GetId = std::hash<std::string>{};
constexpr auto Ticks = &SDL_GetTicks;
constexpr auto True = true;
constexpr auto False = false;

using String = std::string;

template <typename T, typename U>
using UMap = std::unordered_map<T, U>;

template <typename T>
using UPtr = std::unique_ptr<T>;

template <typename T, typename U>
using UPtrEx = std::unique_ptr<T, U>;

template <typename T>
using SPtr = std::shared_ptr<T>;

template <typename T>
using List = std::vector<T>;

template <typename T, typename... Args>
inline std::unique_ptr<T> MakeUPtr(Args && ... args)
{
    return std::make_unique<T>(std::forward<Args>(args)...);
}

inline void Randomize() {srand(time(NULL));}

}
