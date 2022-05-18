// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "RectF.h"

namespace Forradia
{

    bool RectF::Contains(Point2F point)
    {
        if (point.x >= x && point.y >= y && point.x < x + w &&
            point.y < y + h)
            return true;

        return false;
    }

    RectF RectF::Copy()
    {
        return *this;
    }

    RectF RectF::Translate(float dx, float dy)
    {
        x += dx;
        y += dy;

        return *this;
    }

    RectF RectF::SetHeight(float newh)
    {
        h = newh;

        return *this;
    }

    LineF RectF::GetTopEdge()
    {
        return {x, y, x + w, y};
    }

    Point2F RectF::GetTopLeftCorner()
    {
        return {x, y};
    }

    Point2F RectF::GetCenter()
    {
        return {x + w/2, y + h/2};
    }

}