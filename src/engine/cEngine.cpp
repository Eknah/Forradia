// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "cEngine.h"
#include "../game/implementation/functionality/actor/modules/cModuleMovementData.h"

namespace Forradia {

void cEngine::Run(cScenesCollection scenesCollection_, int startScene_,
                  UPtr<cPlanetWorldMap> world_,
                  cInventory startingInventory_,
                  cObjectsContent objectsContent_) {
    using std::move;

    InitializeGL();

    World = move(world_);
    ObjectsContent = objectsContent_;

    cPoint3 playerWorldPos = {
        World->WorldMapWidth/2,
        World->WorldMapHeight/2,
        0
    };

    cPoint2F playerTilePos = World->GetArea(playerWorldPos)->SpawnPos;
    cPoint2 playerTilePosI = {
        static_cast<int>(playerTilePos.X),
        static_cast<int>(playerTilePos.Y)
    };

    World->GetArea(playerWorldPos)->GetTile(playerTilePosI)
            .Actor = MakeUPtr<cPlayer>(*this);

    PlayerPtrPtr = MakeUPtr<cPlayer*>(
                static_cast<cPlayer*>(World->GetArea(playerWorldPos)
                                      ->GetTile(playerTilePosI).Actor.get()));

    GetPlayer().GetModule<cModuleMovementData>().WorldMapCoord = playerWorldPos;
    GetPlayer().GetModule<cModuleMovementData>().Position = GetCurrentMapArea().SpawnPos;
    GetPlayer().GetModule<cModuleInventory>().Inventory = startingInventory_;
    SceneManager.Initialize(move(scenesCollection_), startScene_);
    ModelLoader.LoadModels();
    ImageLoader.LoadImages();
    TextGraphics.Initialize();
    CustomCursor.Initialize();

    GameLoop.Run();

    SDL_Quit();
  }

void cEngine::DrawImage(std::string imageName, float x, float y, float width,
                      float height) const {
  imageGraphics.DrawImage(imageName, x, y, width, height);
}

void cEngine::DrawImage(int imageNameHash, float x, float y, float width,
                        float height) const {
    imageGraphics.DrawImage(imageNameHash, x, y, width, height);
  }

void cEngine::FillRectangle(SDL_Color color, float x, float y, float width,
                            float height) const {
    paintGraphics.FillRectangle(color, x, y, width, height);
  }

void cEngine::DrawRectangle(SDL_Color color, float x, float y, float width,
                            float height) const {
    paintGraphics.DrawRectangle(color, x, y, width, height);
  }

void cEngine::DrawLine(SDL_Color color, float x0, float y0, float x1,
                       float y1) const {
    paintGraphics.DrawLine(color, x0, y0, x1, y1);
  }

void cEngine::DrawString(std::string message, SDL_Color color, float x, float y,
                         bool centerAlign) const {
    TextGraphics.DrawString(message, color, x, y, centerAlign);
  }

void cEngine::DrawModel(std::string modelName, float x, float y, float z,
                        float rotation,
                        float specificScaling) const {
    modelGraphics.DrawModel(modelName, x, y, z, rotation, specificScaling);
  }

void cEngine::DrawModel(int modelNameHash, float x, float y, float z,
                        float rotation,
                        float specificScaling) const {
    modelGraphics.DrawModel(modelNameHash, x, y, z, rotation, specificScaling);
  }

cSizeF cEngine::GetImageSizeF(std::string imageName) const {
    return imageGraphics.GetImageSizeF(imageName);
  }

cMapArea& cEngine::GetCurrentMapArea() const {
    // return *WorldMap->MapAreas.at(Player.CurrentMapArea);
    return *World->GetArea(GetPlayer().GetModule<cModuleMovementData>().WorldMapCoord);
  }

void cEngine::InitializeGL() {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                        SDL_GL_CONTEXT_PROFILE_CORE);

    Window = F_WindowPtr(
        SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED, defaultWindowSize.Width,
                         defaultWindowSize.Height,
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
