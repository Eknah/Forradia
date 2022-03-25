#pragma once
namespace Forradia
{

class CEngine;

class CBackground
{
public:

    CBackground(CEngine& engine) : Engine(engine) {}

    void Render(float zoom);

private:

    CEngine& Engine;
};

}
