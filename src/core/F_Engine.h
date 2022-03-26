
#pragma once

#include "framework/world_structure/F_WorldMap.h"
#include "framework/F_ObjectsContent.h"
#include "F_Model3D.h"
#include "F_FpsCounter.h"
#include "F_KeyboardHandler.h"
#include "F_ModelLoader.h"
#include "F_CustomCursor.h"
#include "F_FullscreenController.h"
#include "F_GameLoop.h"
#include "F_ImageGraphics.h"
#include "F_IEngine.h"
#include "../game/engine/F_PaintGraphics.h"
#include "../game/engine/F_TextGraphics.h"
#include "../game/engine/F_ModelGraphics.h"
#include "../game/engine/F_Player.h"

namespace Forradia
{

class F_Engine : public F_IEngine
{

public:

    // ---- Ctor ----
    // Give needed references to this engine to all sub components


    F_Engine() :
        GameLoopImplemented(*this),
        ModelGraphics(*this),
        TextGraphics(*this),
        FpsCounterImplemented(*this),
        CustomCursorImplemented(*this),
        ImageGraphics(*this),
        PaintGraphics(*this),
        FullscreenControllerImplemented(*this),
        Player(*this),
        F_IEngine(KeyboardHandlerImplemented, CustomCursorImplemented, FpsCounterImplemented, FullscreenControllerImplemented, GameLoopImplemented)
    {}

    // Loads content and initializes all engine components
    // Runs game loop until user exists program
    // Cleans up SDL

    inline void Run
    (F_ScenesCollection Scenes_, int StartScene_, UPtr<F_WorldMap> WorldMap_, F_Inventory StartingInventory_, F_ObjectsContent ObjectsContent_)
    {
        using std::move;

        InitializeGL();


        WorldMap        = move(WorldMap_);
        ObjectsContent  = ObjectsContent_;

        Player          .CurrentMapArea = 0;
        Player          .Position = GetCurrentMapArea().PlayerStartPosition;
        Player          .Inventory = StartingInventory_;
        SceneManager    .Initialize(move(Scenes_), StartScene_);
        ModelLoader     .LoadModels();
        ImageLoader     .LoadImages();
        TextGraphics    .Initialize();
        CustomCursor    .Initialize();

        GameLoop        .Run();

        SDL_Quit();
    }

    // ---- Drawing operations ----

    inline void DrawImage
    (std::string ImageName, float X, float Y, float Width, float Height) override
    {
        ImageGraphics.DrawImage(ImageName, X, Y, Width, Height);
    }

    inline void DrawImage
    (int ImageNameHash, float X, float Y, float Width, float Height) override
    {
        ImageGraphics.DrawImage(ImageNameHash, X, Y, Width, Height);
    }

    inline void FillRectangle
    (SDL_Color Color, float X, float Y, float Width, float Height) override
    {
        PaintGraphics.FillRectangle(Color, X, Y, Width, Height);
    }

    inline void DrawRectangle
    (SDL_Color Color, float X, float Y, float Width, float Height) override
    {
        PaintGraphics.DrawRectangle(Color, X, Y, Width, Height);
    }

    inline void DrawLine
    (SDL_Color Color, float X0, float Y0, float X1, float Y1) override
    {
        PaintGraphics.DrawLine(Color, X0, Y0, X1, Y1);
    }

    inline void DrawString
    (std::string Message, SDL_Color Color, float X, float Y, bool CenterAlign = false) override
    {
        TextGraphics.DrawString(Message, Color, X, Y, CenterAlign);
    }

    inline void DrawModel
    (std::string ModelName, float X, float Y, float Z, float Rotation = 0.0f, float SpecificScaling = 1.0f) override
    {
        ModelGraphics.DrawModel(ModelName, X, Y, Z, Rotation, SpecificScaling);
    }

    inline void DrawModel
    (int ModelNameHash, float X, float Y, float Z, float Rotation = 0.0f, float SpecificScaling = 1.0f) override
    {
        ModelGraphics.DrawModel(ModelNameHash, X, Y, Z, Rotation, SpecificScaling);
    }

    // ---- Helper functions ----

    inline F_MapArea& GetCurrentMapArea
    ()  override
    {
        return *WorldMap->MapAreas.at(Player.CurrentMapArea);
    }

    // ---- Public members ----

    F_Player                Player;
    F_ModelLoader           ModelLoader;
    UPtr<F_WorldMap>        WorldMap;
    F_ObjectsContent        ObjectsContent;

    F_KeyboardHandler       KeyboardHandlerImplemented;
    F_CustomCursor          CustomCursorImplemented;
    F_FpsCounter            FpsCounterImplemented;
    F_FullscreenController  FullscreenControllerImplemented;
    F_GameLoop              GameLoopImplemented;

    float                   TileSize = 0.5f;

private:

    // Initializes SDL video module
    // Specifices GL version
    // Creates game window with GL support
    // Enables alpha blending for all following render operations

    inline void InitializeGL
    ()
    {
        SDL_Init                (SDL_INIT_VIDEO);

        SDL_GL_SetAttribute     (SDL_GL_CONTEXT_MAJOR_VERSION,  3);
        SDL_GL_SetAttribute     (SDL_GL_CONTEXT_MINOR_VERSION,  1);
        SDL_GL_SetAttribute     (SDL_GL_CONTEXT_PROFILE_MASK,   SDL_GL_CONTEXT_PROFILE_CORE);

        Window = F_WindowPtr
        (
            SDL_CreateWindow
            (
                Title.c_str(),
                SDL_WINDOWPOS_UNDEFINED,
                SDL_WINDOWPOS_UNDEFINED,
                DefaultWindowSize.Width,
                DefaultWindowSize.Height,
                SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP
            ),
            F_SDL_Deleter()
         );

        FullscreenController.ToggleFullscreen();
        SDL_SetWindowResizable(Window.get(), SDL_TRUE);
        FullscreenController.ToggleFullscreen();

        SDL_GL_CreateContext    (Window.get());
        SDL_GL_SetSwapInterval  (1);

        glEnable                (GL_BLEND);
        glBlendFunc             (GL_SRC_ALPHA,                  GL_ONE_MINUS_SRC_ALPHA);
    }

    // ---- Private members ----

    F_ImageGraphics         ImageGraphics;
    F_PaintGraphics         PaintGraphics;
    F_TextGraphics          TextGraphics;
    F_ModelGraphics         ModelGraphics;

    const std::string       Title = "Forradia";
    const F_Size            DefaultWindowSize = {800, 600};

};

}
