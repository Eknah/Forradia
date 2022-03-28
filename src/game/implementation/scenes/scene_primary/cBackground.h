// Copyright (C) 2022  Andreas Åkerberg

#pragma once

namespace Forradia
{

class cEngine;

class cBackground
{

public:

    cBackground(cEngine& Engine_) : Engine(Engine_) {}

    void        Render(float Zoom);

private:

    cEngine&    Engine;
};

}
