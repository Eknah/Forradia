// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once

#include <string>
#include <tuple>
#include <vector>
#include "Aliases.h"
#include "ObjectDescriber.h"
#include "ObjectFlags.h"

namespace Forradia
{

    class ObjectsBehaviour
    {

        // Functions

    public:

        void Add(String objectName, ObjectDescriber describer);
        void Add(String objectName, char flags);
        void AddMany(List<Tuple<String, char>> describers);

        void SetOpacity(String objectName, float opacity);

        bool Movable(int objectType) const;
        bool BlocksMovement(int objectType) const;

        // Members

    public:
        UMap<int, ObjectDescriber> objDescribers;

    };

}