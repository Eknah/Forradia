#pragma once
namespace Forradia
{


class CImageGraphics
{

public:
    CImageGraphics(CEngine& engine) : Engine(engine) {}

    void DrawImage(String imageName, float X, float Y, float width, float height);
    void DrawImage(int imageNameHash, float X, float Y, float width, float height);
private:

    CEngine& Engine;

};

}
