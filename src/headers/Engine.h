// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once

#include <utility>
#include <string>
#include "CustomCursor.h"
#include "FpsCounter.h"
#include "FullscreenController.h"
#include "GameLoop.h"
#include "ImageGraphics.h"
#include "KeyboardHandler.h"
#include "Model3D.h"
#include "ModelGraphics.h"
#include "PaintGraphics.h"
#include "SceneManager.h"
#include "IEngine.h"
#include "Configuration.h"

namespace Forradia
{
    class Engine : public IEngine
    {
    public:
        // ---- Ctor ----
        // Give needed references to this engine to all sub components
        Engine()
            : gameLoopImplemented(*this),
			modelGraphics(*this),
            fpsCounterImplemented(*this),
			customCursorImplemented(*this),
            imageGraphics(*this),
			fullscreenControllerImplemented(*this),
            sceneManagerImplemented(*this),
			IEngine(
					&keyboardHandlerImplemented,
					&customCursorImplemented,
					&fpsCounterImplemented,
					&fullscreenControllerImplemented,
					&gameLoopImplemented,
					&sceneManagerImplemented
				) {}

        // Loads content and initializes all engine components
        // Runs game loop until user exists program
        // Cleans up SDL
        void Run(
			ScenesCollection scenesCollection_, int startScene_,
            UPtr<PlanetWorldMap> world_,
            Inventory startingInventory_,
            ObjectsBehaviour objectsContent_
		);

        // ---- Drawing operations ----
        void DrawImage(
			std::string imageName,
			float x,
			float y,
			float w,
			float h
		) const override;
		
        void DrawImage(
			int imageNameHash,
			float x,
			float y,
			float w,
			float h
		) const override;
		
        void FillRect(
			SDL_Color color,
			float x,
			float y,
			float w,
			float h
		) const override;
		
        void DrawRect(
			SDL_Color color,
			float x,
			float y,
			float w,
			float h
		) const override;
		
        void DrawLine(SDL_Color color, LineF line) const override;
		
        void DrawLine(
			SDL_Color color,
			float x0,
			float y0,
			float x1,
			float y1
		) const override;
		
        void DrawString(
			std::string message,
			SDL_Color color,
			Point2F point,
			bool centerAlign = false,
			float specificScaling = 1.0f
		) override;
		
        void DrawString(
			std::string message,
			SDL_Color color,
			float x,
			float y,
			bool centerAlign = false,
			float specificScaling = 1.0f
		) override;
		
        void DrawModel(
			std::string modelName,
			float x,
			float y,
			float z,
			float rotation = 0.0f,
			float specificScaling = 1.0f,
			float Opacity = 1.0f
		) const override;
		
        void DrawModel(
			int ModelNameHash,
			float x,
			float y,
			float z,
			float rotation = 0.0f,
			float specificScaling = 1.0f,
			float Opacity = 1.0f
		) const override;
		
        void FillRect(SDL_Color color, RectF rect) const override;
        void DrawRect(SDL_Color color, RectF rect) const override;

        // ---- Helper functions ----
        SizeF GetImageSizeF(std::string imageName) const override;
        MapArea& GetCurrMapArea() const override;

        // ---- Public members ----
        KeyboardHandler keyboardHandlerImplemented;
        CustomCursor customCursorImplemented;
        FpsCounter fpsCounterImplemented;
        FullscreenController fullscreenControllerImplemented;
        GameLoop gameLoopImplemented;
        SceneManager sceneManagerImplemented;
        Configuration cfg;

    private:
        // Initializes SDL video module
        // Specifices GL version
        // Creates game window with GL support
        // Enables alpha blending for all following render operations
        void InitGL();

        // ---- Private members ----
        ImageGraphics imageGraphics;
        PaintGraphics paintGraphics;
        ModelGraphics modelGraphics;
        const std::string title = "Forradia";
        const Size defaultWindowSize = { 800, 600 };
    };
}