// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once

#include <string>
#include <tuple>
#include <vector>
#include "../engine/Aliases.h"
#include "../engine/ObjectDescriber.h"
#include "../engine/ObjectFlags.h"

namespace Forradia
{

    class ObjectsBehaviour
    {

    public:

        void Add(String objectName, ObjectDescriber describer);
        void Add(String objectName, char flags);
        void AddMany(List<Tuple<String, char>> describers);

        void SetOpacity(String objectName, float opacity);

        bool Movable(int objectType) const;
        bool BlocksMovement(int objectType) const;

        UMap<int, ObjectDescriber> objDescribers;
    };

}  // namespace Forradia
