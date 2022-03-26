#pragma once
#include "framework/world_structure/F_WorldMap.h"
#include "framework/F_ObjectsContent.h"
#include "F_Model3D.h"
#include "F_SceneManager.h"
#include "F_ImageLoader.h"
#include "F_FpsCounter.h"
#include "F_KeyboardHandler.h"
#include "F_ModelLoader.h"
#include "F_CustomCursor.h"
#include "F_FullscreenController.h"
#include "F_IEngine.h"
#include "../game/engine/F_ImageGraphics.h"
#include "../game/engine/F_PaintGraphics.h"
#include "../game/engine/F_MouseHandler.h"
#include "../game/engine/F_TextGraphics.h"
#include "../game/engine/F_ModelGraphics.h"
#include "../game/engine/F_GameLoop.h"
#include "../game/engine/F_Player.h"

namespace Forradia
{

class F_Engine : public F_IEngine
{

public:

    F_Engine() : GameLoop(*this), ModelGraphics(*this), TextGraphics(*this), FpsCounter(*this), CustomCursor(*this), ImageGraphics(*this), PaintGraphics(*this), FullscreenController(*this), Player(*this) {}

    inline void Run(F_ScenesCollection scenes, int startScene, UPtr<F_WorldMap> worldMap, F_Inventory startingInventory, F_ObjectsContent objectsContent)
    {
        SceneManager.Initialize(std::move(scenes), startScene);
        WorldMap = std::move(worldMap);
        Player.CurrentMapArea = 0;
        Player.Position = { GetCurrentMapArea().PlayerStartPosition.X, GetCurrentMapArea().PlayerStartPosition.Y };
        Player.Inventory = startingInventory;
        ObjectsContent = objectsContent;
        InitializeEngine();
        ModelLoader.LoadModels();
        ImageLoader.LoadImages();
        TextGraphics.Initialize();
        GameLoop.Run();
        SDL_Quit();
    }

    inline void DrawImage(std::string imageName, float x, float y, float width, float height) override { ImageGraphics.DrawImage(imageName, x, y, width, height); }
    inline void DrawImage(int imageNameHash, float x, float y, float width, float height)  override { ImageGraphics.DrawImage(imageNameHash, x, y, width, height); }

    inline void FillRectangle(SDL_Color color, float x, float y, float width, float height) override { PaintGraphics.FillRectangle(color, x, y, width, height); }
    inline void DrawRectangle(SDL_Color color, float X, float Y, float width, float height) override { PaintGraphics.DrawRectangle(color, X, Y, width, height); }
    inline void DrawLine(SDL_Color color, float x0, float y0, float x1, float y1)  override { PaintGraphics.DrawLine(color, x0, y0, x1, y1); }

    inline void DrawString(std::string message, SDL_Color color, float x, float y, bool centerAlign = false) override { TextGraphics.DrawString(message, color, x, y, centerAlign); }

    inline void DrawModel(std::string modelName, float x, float y, float z, float rotation = 0.0f, float specificScaling = 1.0f)  override { ModelGraphics.DrawModel(modelName, x, y, z, rotation, specificScaling); }
    inline void DrawModel(int modelNameHash, float x, float y, float z, float rotation = 0.0f, float specificScaling = 1.0f)  override { ModelGraphics.DrawModel(modelNameHash, x, y, z, rotation, specificScaling); }

    inline F_MapArea& GetCurrentMapArea()  override
    {
        return *WorldMap->MapAreas.at(Player.CurrentMapArea);
    }

    F_GameLoop GameLoop;
    F_Player Player;
    F_SceneManager SceneManager;
    F_ImageLoader ImageLoader;
    F_FpsCounter FpsCounter;
    F_KeyboardHandler KeyboardHandler;
    F_ModelLoader ModelLoader;
    F_MouseHandler MouseHandler;
    F_CustomCursor CustomCursor;
    F_FullscreenController FullscreenController;
    UPtr<F_WorldMap> WorldMap;
    F_ObjectsContent ObjectsContent;

    float TileSize = 0.5f;

    WindowPtr Window;

private:

    inline void InitializeEngine()
    {
        SDL_Init(SDL_INIT_VIDEO);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        Window = WindowPtr(SDL_CreateWindow("Forradia", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 0, 0, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_MAXIMIZED), F_SDL_Deleter());
        SDL_GL_CreateContext(Window.get());
        SDL_GL_SetSwapInterval(1);
        SDL_ShowCursor(0);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    F_ImageGraphics ImageGraphics;
    F_PaintGraphics PaintGraphics;
    F_TextGraphics TextGraphics;
    F_ModelGraphics ModelGraphics;

};

}
