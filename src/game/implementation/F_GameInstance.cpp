
#include "CommonExternal.h"
#include "F_GameInstance.h"
#include "../core/F_Engine.h"
#include "implementation/scenes/F_SceneGameStart.h"
#include "implementation/scenes/F_SceneMainMenu.h"
#include "implementation/scenes/F_ScenePrimary.h"
#include "implementation/content/F_DefaultMapGenerator.h"

namespace Forradia
{

// Randomizes for the purpose of map generation and mobs movement
// Prepares custom object descriptions for some objects
// Prepares scenes
// Generates world map
// Prepares player starting inventory
// Runs engine with all the preparation data

void F_GameInstance::StartGame()
{

    using std::move;

    Randomize();

    const int               MapAreaSize = 150;
    auto                    WorldMap = MakeUPtr<F_WorldMap>(MapAreaSize);

    F_Engine                Engine;
    F_ObjectsContent        ObjectsContent;
    F_ScenesCollection      Scenes;
    F_Inventory             StartingInventory;
    F_DefaultMapGenerator   DefaultMapGenerator(Engine, WorldMap);

    F_ObjectDescription     DescObjectTree1;
    F_ObjectDescription     DescObjectTree2;
    F_ObjectDescription     DescCaveWallBlock;

    WorldMap            ->GenerateWorldMap(DefaultMapGenerator);
    StartingInventory   .Add(0, "ObjectWoodaxe");
    StartingInventory   .Add(1, "ObjectSaw");

    DescObjectTree1     .BlocksMovement  = true;
    DescObjectTree1     .BlocksSight     = true;
    DescObjectTree1     .Movable         = false;

    DescObjectTree2     .BlocksMovement  = true;
    DescObjectTree2     .BlocksSight     = true;
    DescObjectTree2     .Movable         = false;

    DescCaveWallBlock   .BlocksMovement  = true;
    DescCaveWallBlock   .BlocksSight     = true;
    DescCaveWallBlock   .Movable         = false;

    ObjectsContent      .Add("ObjectTree1",           DescObjectTree1 );
    ObjectsContent      .Add("ObjectTree2",           DescObjectTree2 );
    ObjectsContent      .Add("ObjectCaveWallBlock",   DescCaveWallBlock );

    Scenes              .Add("SceneGameStart",    MakeUPtr<F_SceneGameStart>(Engine));
    Scenes              .Add("SceneMainMenu",     MakeUPtr<F_SceneMainMenu>(Engine));
    Scenes              .Add("ScenePrimary",      MakeUPtr<F_ScenePrimary>(Engine));

    Engine.Run
    (
        move(Scenes),
        GetId("SceneGameStart"),
        move(WorldMap),
        StartingInventory,
        ObjectsContent
    );

}

}
