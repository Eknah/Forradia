// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "Engine.h"
#include "../game/implementation/functionality/actor/modules/MovementDataModule.h"

namespace Forradia {

void Engine::Run(ScenesCollection _scenesCollection, int _startScene,
                  UPtr<PlanetWorldMap> _world,
                  Inventory _startingInventory,
                  ObjectsContent _objectsContent) {
    using std::move;

    InitializeGL();

    world = move(_world);
    objectsContent = _objectsContent;

    Point3 playerWorldPos = {
        world->worldMapWidth/2,
        world->worldMapHeight/2,
        0
    };

    Point2F playerTilePos = world->GetArea(playerWorldPos)->spawnPos;
    Point2 playerTilePosI = {
        static_cast<int>(playerTilePos.x),
        static_cast<int>(playerTilePos.y)
    };

    world->GetArea(playerWorldPos)->GetTile(playerTilePosI)
            .actor = MakeUPtr<Player>(*this);

    playerPtrPtr = MakeUPtr<Player*>(
                static_cast<Player*>(world->GetArea(playerWorldPos)
                                      ->GetTile(playerTilePosI).actor.get()));

    GetPlayer().GetModule<MovementDataModule>().worldMapCoord = playerWorldPos;
    GetPlayer().GetModule<MovementDataModule>().position = GetCurrentMapArea().spawnPos;
    GetPlayer().GetModule<InventoryModule>().inventory = _startingInventory;
    sceneManager.Initialize(move(_scenesCollection), _startScene);
    modelLoader.LoadModels();
    imageLoader.LoadImages();
    textGraphics.Initialize();
    customCursor.Initialize();

    gameLoop.Run();

    SDL_Quit();
  }

void Engine::DrawImage(std::string imageName, float x, float y, float width,
                      float height) const {
  imageGraphics.DrawImage(imageName, x, y, width, height);
}

void Engine::DrawImage(int imageNameHash, float x, float y, float width,
                        float height) const {
    imageGraphics.DrawImage(imageNameHash, x, y, width, height);
  }

void Engine::FillRectangle(SDL_Color color, float x, float y, float width,
                            float height) const {
    paintGraphics.FillRectangle(color, x, y, width, height);
  }

void Engine::DrawRectangle(SDL_Color color, float x, float y, float width,
                            float height) const {
    paintGraphics.DrawRectangle(color, x, y, width, height);
  }

void Engine::DrawLine(SDL_Color color, float x0, float y0, float x1,
                       float y1) const {
    paintGraphics.DrawLine(color, x0, y0, x1, y1);
  }

void Engine::DrawString(std::string message, SDL_Color color, float x, float y,
                         bool centerAlign, float specificScaling) const {
    textGraphics.DrawString(message, color, x, y, centerAlign, specificScaling);
  }

void Engine::DrawModel(std::string modelName, float x, float y, float z,
                        float rotation,
                        float specificScaling, float opacity) const {
    modelGraphics.DrawModel(modelName, x, y, z, rotation, specificScaling, opacity);
  }

void Engine::DrawModel(int modelNameHash, float x, float y, float z,
                        float rotation,
                        float specificScaling, float Opacity) const {
    modelGraphics.DrawModel(modelNameHash, x, y, z, rotation, specificScaling, Opacity);
  }

SizeF Engine::GetImageSizeF(std::string imageName) const {
    return imageGraphics.GetImageSizeF(imageName);
  }

MapArea& Engine::GetCurrentMapArea() const {
    // return *WorldMap->MapAreas.at(Player.CurrentMapArea);
    return *world->GetArea(GetPlayer().GetModule<MovementDataModule>().worldMapCoord);
  }

void Engine::InitializeGL() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_StopTextInput();

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
        SDL_Deleter());

    fullscreenController.ToggleFullscreen();
    SDL_SetWindowResizable(window.get(), SDL_TRUE);
    fullscreenController.ToggleFullscreen();

    SDL_GL_CreateContext(window.get());
    SDL_GL_SetSwapInterval(1);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  }


}  // namespace Forradia
