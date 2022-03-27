
#include "CommonExternal.h"
#include "cGameInstance.h"
#include "../engine/cEngine.h"
#include "implementation/scenes/cSceneGameStart.h"
#include "implementation/scenes/cSceneMainMenu.h"
#include "implementation/scenes/cScenePrimary.h"
#include "implementation/content/cDefaultMapGenerator.h"

namespace Forradia
{

// Randomizes for the purpose of map generation and mobs movement
// Prepares custom object descriptions for some objects
// Prepares scenes
// Generates world map
// Prepares player starting inventory
// Runs engine with all the preparation data

void cGameInstance::StartGame()
{

    using std::move;

    Randomize();

    const int               MapAreaSize = 150;
    auto                    WorldMap = MakeUPtr<cWorldMap>(MapAreaSize);

    cEngine                Engine;
    cObjectsContent        ObjectsContent;
    cScenesCollection      Scenes;
    UMap<int, SPtr<cObject>> StartingInventory;
    cDefaultMapGenerator   DefaultMapGenerator(Engine, WorldMap);

    cObjectDescription     DescObjectTree1;
    cObjectDescription     DescObjectTree2;
    cObjectDescription     DescCaveWallBlock;

    WorldMap            ->GenerateWorldMap(DefaultMapGenerator);
    StartingInventory   .insert({0, MakeSPtr<cObject>("ObjectWoodaxe")});
    StartingInventory   .insert({1, MakeSPtr<cObject>("ObjectSaw")});

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

    Scenes              .Add("SceneGameStart",    MakeUPtr<cSceneGameStart>(Engine));
    Scenes              .Add("SceneMainMenu",     MakeUPtr<cSceneMainMenu>(Engine));
    Scenes              .Add("ScenePrimary",      MakeUPtr<cScenePrimary>(Engine));

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