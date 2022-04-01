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
  // dummy comment
  // dummy comment 2
  using std::move;

  Randomize();

  const int MapAreaSize = 150;
  auto WorldMap = MakeUPtr<cWorldMap>(MapAreaSize, 1, 1);

  cEngine Engine;
  cObjectsContent ObjectsContent;
  cScenesCollection ScenesCollection;

  UMap<int, SPtr<cObject>> StartingInventory;

  cDefaultMapGenerator DefaultMapGenerator(Engine, WorldMap);

  cObjectDescription DescObjectTree1;
  cObjectDescription DescObjectTree2;
  cObjectDescription DescCaveWallBlock;

  WorldMap->GenerateWorldMap(DefaultMapGenerator);
  StartingInventory.insert({0, MakeSPtr<cObject>("ObjectWoodaxe")});
  StartingInventory.insert({1, MakeSPtr<cObject>("ObjectSaw")});

  DescObjectTree1.BlocksMovement = true;
  DescObjectTree1.BlocksSight = true;
  DescObjectTree1.Movable = false;

  DescObjectTree2.BlocksMovement = true;
  DescObjectTree2.BlocksSight = true;
  DescObjectTree2.Movable = false;

  DescCaveWallBlock.BlocksMovement = true;
  DescCaveWallBlock.BlocksSight = true;
  DescCaveWallBlock.Movable = false;

  ObjectsContent.Add("ObjectTree1", DescObjectTree1);
  ObjectsContent.Add("ObjectTree2", DescObjectTree2);
  ObjectsContent.Add("ObjectCaveWallBlock", DescCaveWallBlock);

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
