// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include <string>
#include <vector>
#include "../engine/Aliases.h"
#include "../engine/Actor.h"
#include "../engine/ObjectFlags.h"
#include "../engine/Object.h"

namespace Forradia
{

    class IEngine;

    class Tile
    {
    public:
        explicit Tile(const IEngine& _e) : e(_e) {}

        // Get info about tile

        bool HasObjectWithFlag(ObjectFlags flag);
        bool HasObjectOfType(std::string objectName);

        // Core tile data structure

        int groundType = 0;
        std::vector<SPtr<Object>> objects;
        SPtr<Object> roof;
        int elevation = 0;
        SPtr<Actor> actor = nullptr;
        std::unordered_map<std::string, std::string> properties;
        Point2F vertexOffset = {0, 0};

    private:
        const IEngine& e;
    };

}  // namespace Forradia
