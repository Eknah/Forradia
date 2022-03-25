#pragma once
#include "CModel3D.h"
#include "CSceneManager.h"
#include "CImageLoader.h"
#include "CFpsCounter.h"
#include "CKeyboardHandler.h"
#include "CModelLoader.h"
#include "CCustomCursor.h"
#include "CFullscreenController.h"

#include "IEngine.h"

#include "../Visible/Engine/CImageGraphics.h"
#include "../Visible/Engine/CPaintGraphics.h"
#include "../Visible/Engine/CMouseHandler.h"
#include "../Visible/Engine/CTextGraphics.h"
#include "../Visible/Engine/CModelGraphics.h"
#include "../Visible/Engine/CGameLoop.h"
#include "../Visible/Engine/CPlayer.h"

namespace Forradia
{

class CEngine : public IEngine
{

public:
    CEngine() : GameLoop(*this), ModelGraphics(*this), TextGraphics(*this), FpsCounter(*this), CustomCursor(*this), ImageGraphics(*this), PaintGraphics(*this), FullscreenController(*this), KeyboardHandler(*this), Player(*this) {}

    inline void Run(CScenesCollection scenes, int startScene, UPtr<CWorldMap> worldMap, CInventory startingInventory, CObjectsContent objectsContent)
    {
        SceneManager.InitializeEngine(std::move(scenes), startScene);
        WorldMap = std::move(worldMap);
        Player.CurrentMapArea = 0;
        Player.Position = { GetCurrentMapArea().PlayerStartPosition.X, GetCurrentMapArea().PlayerStartPosition.Y };
        Player.Inventory = startingInventory;
        ObjectsContent = objectsContent;
        InitializeEngine();
        ModelLoader.LoadModels();
        ImageLoader.LoadImages();
        TextGraphics.InitializeEngine();
        GameLoop.Run();
        StopEngine();
    }

    inline void DrawImage(String imageName, float x, float y, float width, float height) override { ImageGraphics.DrawImage(imageName, x, y, width, height); }
    inline void DrawImage(int imageNameHash, float x, float y, float width, float height)  override { ImageGraphics.DrawImage(imageNameHash, x, y, width, height); }

    inline void FillRectangle(SDL_Color color, float x, float y, float width, float height) override { PaintGraphics.FillRectangle(color, x, y, width, height); }
    inline void DrawRectangle(SDL_Color color, float X, float Y, float width, float height) override { PaintGraphics.DrawRectangle(color, X, Y, width, height); }
    inline void DrawLine(SDL_Color color, float x0, float y0, float x1, float y1)  override { PaintGraphics.DrawLine(color, x0, y0, x1, y1); }

    inline void DrawString(String message, SDL_Color color, float x, float y, bool centerAlign = false) override { TextGraphics.DrawString(message, color, x, y, centerAlign); }

    inline void DrawModel(String modelName, float x, float y, float z, float rotation = 0.0f, float alpha = 1.0f, float specificScaling = 1.0f, CVector3 rotVec = CVector3(0, 0, 0))  override { ModelGraphics.DrawModel(modelName, x, y, z, rotation, alpha, specificScaling, rotVec); }
    inline void DrawModel(int modelNameHash, float x, float y, float z, float rotation = 0.0f, float alpha = 1.0f, float specificScaling = 1.0f, CVector3 rotVec = CVector3(0, 0, 0))  override { ModelGraphics.DrawModel(modelNameHash, x, y, z, rotation, alpha, specificScaling, rotVec); }

    inline CMapArea& GetCurrentMapArea()  override
    {
        return *WorldMap->MapAreas.at(Player.CurrentMapArea);
    }

    CGameLoop GameLoop;
    CPlayer Player;
    CSceneManager SceneManager;
    CImageLoader ImageLoader;
    CFpsCounter FpsCounter;
    CKeyboardHandler KeyboardHandler;
    CModelLoader ModelLoader;
    CMouseHandler MouseHandler;
    CCustomCursor CustomCursor;
    CFullscreenController FullscreenController;
    UPtr<CWorldMap> WorldMap;
    CObjectsContent ObjectsContent;




    float TileSize = 0.5f;

    const int ScreenWidth = 640;
    const int ScreenHeight = 480;

private:
    inline void InitializeEngine()
    {
        SDL_Init(SDL_INIT_VIDEO);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        GWindow = SDL_CreateWindow("Forradia", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ScreenWidth, ScreenHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_MAXIMIZED);
        SDL_GL_CreateContext(GWindow);
        SDL_GL_SetSwapInterval(1);
        SDL_ShowCursor(0);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }
    inline void StopEngine()
    {
        SDL_DestroyWindow(GWindow);
        GWindow = NULL;
        SDL_Quit();
    }

    CImageGraphics ImageGraphics;
    CPaintGraphics PaintGraphics;
    CTextGraphics TextGraphics;
    CModelGraphics ModelGraphics;

};

}
