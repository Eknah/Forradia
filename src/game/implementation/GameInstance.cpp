// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include <utility>
#include "GameInstance.h"
#include "../engine/Engine.h"
#include "../engine/SceneGameStart.h"
#include "../engine/Inventory.h"
#include "implementation/scenes/SceneMainMenu.h"
#include "implementation/scenes/ScenePrimary.h"
#include "implementation/content/DefaultMapGenerator.h"
#include "implementation/content/ValleyMapGenerator.h"

namespace Forradia
{

    void GameInstance::StartGame()
    {
        const int mapAreaSize = 150;
        auto planetMap = MakeUPtr<PlanetWorldMap>(mapAreaSize, 1, 1);

        Engine e;
        ObjectsContent objectsContent;
        ScenesCollection scenesCollection;
        Inventory startingInventory;

        auto defaultMapGen = MakeSPtr<DefaultMapGenerator>(e, planetMap);
        //auto defaultMapGen = MakeSPtr<ValleyMapGenerator>(e, planetMap);
        auto worldMapGens = UMap<int, UMap<int, SPtr<IMapGenerator>>>();
        worldMapGens[0][0] = defaultMapGen;
        worldMapGens[1][0] = defaultMapGen;
        planetMap->GenerateWorldMap(worldMapGens);

        startingInventory.AddMany({ "ObjectWoodaxe",
                                  "ObjectSaw" });

        objectsContent.AddMany({ {"ObjectTree1", ObjObstacle},
                                {"ObjectTree2", ObjObstacle},
                                {"ObjectCaveWallBlock", ObjObstacle},
                                {"ObjectTallGrass", ObjNoShadow},
                                {"ObjectWoodFence", ObjNoShadow | ObjObstacle},
                                {"ObjectWoodWall", ObjNoShadow | ObjObstacle},
                                {"ObjectRoof", ObjNoShadow} });

        objectsContent.SetOpacity("ObjectRoof", 0.5f);

        scenesCollection.AddMany({ {"SceneGameStart",
                                   MakeSPtr<SceneGameStart>(e,
                                   "SceneGameStartBackground",
                                   "SceneForradiaLogo",
                                   "Press to start",
                                   "SceneMainMenu")},

                                  {"SceneMainMenu", MakeSPtr<SceneMainMenu>(e)},

                                  {"ScenePrimary", MakeSPtr<ScenePrimary>(e)} });

        e.Run(std::move(scenesCollection), GetId("SceneGameStart"), std::move(planetMap),
            startingInventory, objectsContent);
    }

}  // namespace Forradia
