
#pragma once

namespace Forradia
{

class F_Engine;

class F_Background
{

public:

    F_Background(F_Engine& engine) : Engine(engine) {}

    void Render(float zoom);

private:

    F_Engine& Engine;
};

}
