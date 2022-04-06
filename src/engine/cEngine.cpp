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

    world = move(world_);
    objectsContent = objectsContent_;

    cPoint3 playerWorldPos = {
        world->worldMapWidth/2,
        world->worldMapHeight/2,
        0
    };

    cPoint2F playerTilePos = world->GetArea(playerWorldPos)->spawnPos;
    cPoint2 playerTilePosI = {
        static_cast<int>(playerTilePos.x),
        static_cast<int>(playerTilePos.y)
    };

    world->GetArea(playerWorldPos)->GetTile(playerTilePosI)
            .actor = MakeUPtr<cPlayer>(*this);

    playerPtrPtr = MakeUPtr<cPlayer*>(
                static_cast<cPlayer*>(world->GetArea(playerWorldPos)
                                      ->GetTile(playerTilePosI).actor.get()));

    GetPlayer().GetModule<cModuleMovementData>().worldMapCoord = playerWorldPos;
    GetPlayer().GetModule<cModuleMovementData>().position = GetCurrentMapArea().spawnPos;
    GetPlayer().GetModule<cModuleInventory>().inventory = startingInventory_;
    sceneManager.Initialize(move(scenesCollection_), startScene_);
    modelLoader.LoadModels();
    imageLoader.LoadImages();
    textGraphics.Initialize();
    customCursor.Initialize();

    gameLoop.Run();

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
    textGraphics.DrawString(message, color, x, y, centerAlign);
  }

void cEngine::DrawModel(std::string modelName, float x, float y, float z,
                        float rotation,
                        float specificScaling, float Opacity) const {
    modelGraphics.DrawModel(modelName, x, y, z, rotation, specificScaling, Opacity);
  }

void cEngine::DrawModel(int modelNameHash, float x, float y, float z,
                        float rotation,
                        float specificScaling, float Opacity) const {
    modelGraphics.DrawModel(modelNameHash, x, y, z, rotation, specificScaling, Opacity);
  }

cSizeF cEngine::GetImageSizeF(std::string imageName) const {
    return imageGraphics.GetImageSizeF(imageName);
  }

cMapArea& cEngine::GetCurrentMapArea() const {
    // return *WorldMap->MapAreas.at(Player.CurrentMapArea);
    return *world->GetArea(GetPlayer().GetModule<cModuleMovementData>().worldMapCoord);
  }

void cEngine::InitializeGL() {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                        SDL_GL_CONTEXT_PROFILE_CORE);

    window = WindowPtr(
        SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED, defaultWindowSize.width,
                         defaultWindowSize.height,
                         SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN |
                             SDL_WINDOW_FULLSCREEN_DESKTOP),
        cSDL_Deleter());

    fullscreenController.ToggleFullscreen();
    SDL_SetWindowResizable(window.get(), SDL_TRUE);
    fullscreenController.ToggleFullscreen();

    SDL_GL_CreateContext(window.get());
    SDL_GL_SetSwapInterval(1);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  }


}  // namespace Forradia
