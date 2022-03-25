#pragma once
namespace Forradia
{

class CRectF
{
public:

    inline bool ContainsPoint(CPoint2F point)
    {
        if (point.X >= X && point.Y >= Y && point.X < X + Width && point.Y < Y + Height)
            return True;
        return False;
    }

    float X = 0.0f;
    float Y = 0.0f;
    float Width = 0.0f;
    float Height = 0.0f;
};

}
