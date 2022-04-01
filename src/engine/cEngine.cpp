// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "cEngine.h"

namespace Forradia {

void cEngine::Run(cScenesCollection ScenesCollection_, int StartScene_,
                  UPtr<cWorldMap> World_,
                  cInventory StartingInventory_,
                  cObjectsContent ObjectsContent_) {
    using std::move;

    InitializeGL();

    World = move(World_);
    ObjectsContent = ObjectsContent_;

    cPoint3 PlayerWorldPos = {
        World->WorldMapWidth/2,
        World->WorldMapHeight/2,
        0
    };

    cPoint2F PlayerTilePos = World->GetArea(PlayerWorldPos)->SpawnPos;
    cPoint2 PlayerTilePosI = {
        static_cast<int>(PlayerTilePos.X),
        static_cast<int>(PlayerTilePos.Y)
    };

    World->GetArea(PlayerWorldPos)->GetTile(PlayerTilePosI)
            .Actor = MakeUPtr<cPlayer>(*this);

    PlayerPtrPtr = MakeUPtr<cPlayer*>(
                static_cast<cPlayer*>(World->GetArea(PlayerWorldPos)
                                      ->GetTile(PlayerTilePosI).Actor.get()));

    GetPlayer().WorldMapCoord = PlayerWorldPos;
    GetPlayer().Position = GetCurrentMapArea().SpawnPos;
    GetPlayer().GetModule<cModuleInventory>().Inventory = StartingInventory_;
    SceneManager.Initialize(move(ScenesCollection_), StartScene_);
    ModelLoader.LoadModels();
    ImageLoader.LoadImages();
    TextGraphics.Initialize();
    CustomCursor.Initialize();

    GameLoop.Run();

    SDL_Quit();
  }

void cEngine::DrawImage(std::string ImageName, float X, float Y, float Width,
                      float Height) const {
  ImageGraphics.DrawImage(ImageName, X, Y, Width, Height);
}

void cEngine::DrawImage(int ImageNameHash, float X, float Y, float Width,
                        float Height) const {
    ImageGraphics.DrawImage(ImageNameHash, X, Y, Width, Height);
  }

void cEngine::FillRectangle(SDL_Color Color, float X, float Y, float Width,
                            float Height) const {
    PaintGraphics.FillRectangle(Color, X, Y, Width, Height);
  }

void cEngine::DrawRectangle(SDL_Color Color, float X, float Y, float Width,
                            float Height) const {
    PaintGraphics.DrawRectangle(Color, X, Y, Width, Height);
  }

void cEngine::DrawLine(SDL_Color Color, float X0, float Y0, float X1,
                       float Y1) const {
    PaintGraphics.DrawLine(Color, X0, Y0, X1, Y1);
  }

void cEngine::DrawString(std::string Message, SDL_Color Color, float X, float Y,
                         bool CenterAlign) const {
    TextGraphics.DrawString(Message, Color, X, Y, CenterAlign);
  }

void cEngine::DrawModel(std::string ModelName, float X, float Y, float Z,
                        float Rotation,
                        float SpecificScaling) const {
    ModelGraphics.DrawModel(ModelName, X, Y, Z, Rotation, SpecificScaling);
  }

void cEngine::DrawModel(int ModelNameHash, float X, float Y, float Z,
                        float Rotation,
                        float SpecificScaling) const {
    ModelGraphics.DrawModel(ModelNameHash, X, Y, Z, Rotation, SpecificScaling);
  }

cSizeF cEngine::GetImageSizeF(std::string ImageName) const {
    return ImageGraphics.GetImageSizeF(ImageName);
  }

cMapArea& cEngine::GetCurrentMapArea() const {
    // return *WorldMap->MapAreas.at(Player.CurrentMapArea);
    return *World->GetArea(GetPlayer().WorldMapCoord);
  }

void cEngine::InitializeGL() {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                        SDL_GL_CONTEXT_PROFILE_CORE);

    Window = F_WindowPtr(
        SDL_CreateWindow(Title.c_str(), SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED, DefaultWindowSize.Width,
                         DefaultWindowSize.Height,
                         SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN |
                             SDL_WINDOW_FULLSCREEN_DESKTOP),
        cSDL_Deleter());

    FullscreenController.ToggleFullscreen();
    SDL_SetWindowResizable(Window.get(), SDL_TRUE);
    FullscreenController.ToggleFullscreen();

    SDL_GL_CreateContext(Window.get());
    SDL_GL_SetSwapInterval(1);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  }


}  // namespace Forradia
