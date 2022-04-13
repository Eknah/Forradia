// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "Point2F.h"
#include "LineF.h"

namespace Forradia
{

    class RectF
    {
    public:
        bool ContainsPoint(Point2F point);
        RectF Copy();
        RectF Translate(float dx, float dy);
        RectF SetHeight(float newh);
        LineF GetTopEdge();
        Point2F GetTopLeftCorner();

        float x = 0.0f;
        float y = 0.0f;
        float w = 0.0f;
        float h = 0.0f;
    };

}  // namespace Forradia
