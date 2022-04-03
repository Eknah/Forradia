// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include <utility>
#include "cGameInstance.h"
#include "../engine/cEngine.h"
#include "../engine/cSceneGameStart.h"
#include "../engine/cInventory.h"
#include "implementation/scenes/cSceneMainMenu.h"
#include "implementation/scenes/cScenePrimary.h"
#include "implementation/content/cDefaultMapGenerator.h"
#include "implementation/content/cValleyMapGenerator.h"

namespace Forradia {

void cGameInstance::StartGame() {
  const int mapAreaSize = 150;
  auto planetMap = MakeUPtr<cPlanetWorldMap>(mapAreaSize, 1, 1);

  cEngine engine;
  cObjectsContent objectsContent;
  cScenesCollection scenesCollection;
  cInventory startingInventory;

  //auto defaultMapGen = MakeSPtr<cDefaultMapGenerator>(engine, planetMap);
  auto defaultMapGen = MakeSPtr<cValleyMapGenerator>(engine, planetMap);
  auto worldMapGens = UMap<int, UMap<int, SPtr<iMapGenerator>>>();
  worldMapGens[0][0] = defaultMapGen;
  worldMapGens[1][0] = defaultMapGen;
  planetMap->GenerateWorldMap(worldMapGens);

  startingInventory.AddMany({"ObjectWoodaxe",
                            "ObjectSaw"});

  objectsContent.AddMany({{"ObjectTree1", ObjectMovementBlock},
                          {"ObjectTree2", ObjectMovementBlock},
                          {"ObjectCaveWallBlock", ObjectMovementBlock}});

  scenesCollection.AddMany({{"SceneGameStart",
                             MakeSPtr<cSceneGameStart>(engine,
                             "SceneGameStartBackground",
                             "SceneForradiaLogo",
                             "Press to start",
                             "SceneMainMenu")},

                            {"SceneMainMenu", MakeSPtr<cSceneMainMenu>(engine)},

                            {"ScenePrimary", MakeSPtr<cScenePrimary>(engine)}});

  engine.Run(std::move(scenesCollection), GetId("SceneGameStart"), std::move(planetMap),
             startingInventory, objectsContent);
}

}  // namespace Forradia
