// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include <utility>
#include "cGameInstance.h"
#include "../engine/cEngine.h"
#include "implementation/content/cDefaultMapGenerator.h"
#include "../engine/cSceneGameStart.h"
#include "implementation/scenes/cSceneMainMenu.h"
#include "implementation/scenes/cScenePrimary.h"
#include "../engine/cInventory.h"

namespace Forradia {

void cGameInstance::StartGame() {
  const int MapAreaSize = 150;
  auto WorldMap = MakeUPtr<cWorldMap>(MapAreaSize, 1, 1);

  cEngine Engine;
  cObjectsContent ObjectsContent;
  cScenesCollection ScenesCollection;
  cInventory StartingInventory;

  WorldMap->GenerateWorldMap(cDefaultMapGenerator(Engine, WorldMap));

  StartingInventory.AddMany({"ObjectWoodaxe",
                            "ObjectSaw"});

  ObjectsContent.AddMany({{"ObjectTree1", ObjectMovementBlock},
                          {"ObjectTree2", ObjectMovementBlock},
                          {"ObjectCaveWallBlock", ObjectMovementBlock}});

  ScenesCollection.AddMany({{"SceneGameStart",
                             MakeSPtr<cSceneGameStart>(Engine,
                             "SceneGameStartBackground",
                             "SceneForradiaLogo",
                             "Press to start",
                             "SceneMainMenu")},

                            {"SceneMainMenu", MakeSPtr<cSceneMainMenu>(Engine)},

                            {"ScenePrimary", MakeSPtr<cScenePrimary>(Engine)}});

  Engine.Run(std::move(ScenesCollection), GetId("SceneGameStart"), std::move(WorldMap),
             StartingInventory, ObjectsContent);
}

}  // namespace Forradia
