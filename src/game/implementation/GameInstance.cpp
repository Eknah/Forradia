// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include <utility>
#include "GameInstance.h"
#include "../engine/Engine.h"
#include "../engine/SceneGameStart.h"
#include "../engine/Inventory.h"
#include "implementation/scenes/SceneMainMenu.h"
#include "implementation/scenes/ScenePrimary.h"
#include "implementation/content/DefaultMapGen.h"
#include "implementation/content/ValleyMapGen.h"

namespace Forradia
{

    void GameInstance::StartGame()
    {
        const int mapAreaSize = 150;
        auto planetMap = MakeUPtr<PlanetWorldMap>(mapAreaSize, 1, 1);

        Engine e;
        ObjectsBehaviour objsBehaviour;
        ScenesCollection scenes;
        Inventory startInv;

        auto defaultMapGen = MakeSPtr<ValleyMapGen>(e, planetMap);
        auto worldMapGens = UMap<int, UMap<int, SPtr<IMapGenerator>>>();

        worldMapGens[0][0] = defaultMapGen;
        worldMapGens[1][0] = defaultMapGen;

        planetMap->GenerateWorldMap(worldMapGens);

        startInv.AddMany({ "ObjectWoodaxe",
                                  "ObjectSaw" });

        objsBehaviour.AddMany({ {"ObjectTree1", FlagObstacle},
                                {"ObjectTree2", FlagObstacle},
                                {"ObjectCaveWallBlock", FlagObstacle},
                                {"ObjectTallGrass", FlagNoShadow},
                                {"ObjectWoodFence", FlagNoShadow | FlagObstacle},
                                {"ObjectWoodWall", FlagNoShadow | FlagObstacle},
                                {"ObjectRoof", FlagNoShadow} });

        objsBehaviour.SetOpacity("ObjectRoof", 0.5f);

        auto gameStartScene = MakeSPtr<SceneGameStart>
                            (
                                e,
                                "SceneGameStartBackground",
                                "SceneForradiaLogo",
                                "Press to start",
                                "SceneMainMenu"
                            );

        scenes.AddMany({ {"SceneGameStart", gameStartScene},

                        {"SceneMainMenu", MakeSPtr<SceneMainMenu>(e)},

                        {"ScenePrimary", MakeSPtr<ScenePrimary>(e)} });

        _ Run
        (
            std::move(scenes),
            GetId("SceneGameStart"),
            std::move(planetMap),
            startInv,
            objsBehaviour
        );
    }

}  // namespace Forradia
