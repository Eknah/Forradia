// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include <utility>
#include "cGameInstance.h"
#include "../engine/cEngine.h"
#include "implementation/content/cDefaultMapGenerator.h"
#include "../engine/cSceneGameStart.h"
#include "implementation/scenes/cSceneMainMenu.h"
#include "implementation/scenes/cScenePrimary.h"

namespace Forradia {

// Randomizes for the purpose of map generation and mobs movement
// Prepares custom object descriptions for some objects
// Prepares scenes
// Generates world map
// Prepares player starting inventory
// Runs engine with all the preparation data

void cGameInstance::StartGame() {
  using std::move;

  Randomize();

  const int MapAreaSize = 150;
  auto WorldMap = MakeUPtr<cWorldMap>(MapAreaSize, 1, 1);

  cEngine Engine;
  cObjectsContent ObjectsContent;
  cScenesCollection ScenesCollection;

  UMap<int, SPtr<cObject>> StartingInventory;

  WorldMap->GenerateWorldMap(cDefaultMapGenerator(Engine, WorldMap));

  StartingInventory.insert({0, MakeSPtr<cObject>("ObjectWoodaxe")});
  StartingInventory.insert({1, MakeSPtr<cObject>("ObjectSaw")});

  ObjectsContent.Add("ObjectTree1", ObjectMovementBlock);
  ObjectsContent.Add("ObjectTree2", ObjectMovementBlock);
  ObjectsContent.Add("ObjectCaveWallBlock", ObjectMovementBlock);

  ScenesCollection.Add("SceneGameStart",
                       MakeUPtr<cSceneGameStart>(Engine,
                                                 "SceneMainMenu",
                                                 "SceneGameStartBackground",
                                                 "SceneForradiaLogo",
                                                 "Press to start"));
  ScenesCollection.Add("SceneMainMenu", MakeUPtr<cSceneMainMenu>(Engine));
  ScenesCollection.Add("ScenePrimary", MakeUPtr<cScenePrimary>(Engine));

  Engine.Run(move(ScenesCollection), GetId("SceneGameStart"), move(WorldMap),
             StartingInventory, ObjectsContent);
}

}  // namespace Forradia
