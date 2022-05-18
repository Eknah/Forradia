// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "Point2F.h"

namespace Forradia
{

    bool Point2F::IsUndefined()
    {
        return x == -1.0f && y == -1.0f;
    }

    void Point2F::MakeUndefined()
    {
        x = -1.0f;
        y = -1.0f;
    }

    Point2F Point2F::Translate(float dx, float dy)
    {
        x += dx;
        y += dy;

        return *this;
    }

}