// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once

#include <string>
#include "Aliases.h"
#include "IEngine.h"

namespace Forradia
{
    class ImageGraphics
    {
    public:
        explicit ImageGraphics(IEngine& _e)
		: e(_e) {}

        // ---- Drawing operations ----
        void DrawImage(
			std::string imageName,
			float x,
			float y,
			float width,
			float height
		) const;
		
        void DrawImage(
			int  imageNameId,
			float x,
			float y,
			float width,
			float height
		) const;
		
        SizeF GetImageSizeF(std::string ImageName) const;

    private:
        IEngine& e;
        Utilities utils;
    };
}