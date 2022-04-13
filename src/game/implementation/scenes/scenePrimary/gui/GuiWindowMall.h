// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include "../engine/Utilities.h"
#include "framework/GuiWindowBase.h"

namespace Forradia
{

    class GuiWindowMall : public GuiWindowBase
    {
    public:
        using GuiWindowBase::GuiWindowBase;

        void RenderDerived() override;
        void DoMouseDownDerived(Uint8 mouseButton) override;

    private:
        Utilities utils;
        Palette palette;
    };

}  // namespace Forradia
