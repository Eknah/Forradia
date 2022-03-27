
#pragma once

namespace Forradia
{

class cEngine;

class cBackground
{

public:

    cBackground(cEngine& engine) : Engine(engine) {}

    void Render(float zoom);

private:

    cEngine& Engine;
};

}
