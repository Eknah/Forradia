#include "CommonExternal.h"
#include "CGameInstance.h"
#include "../core/CEngine.h"
#include "implementation/scenes/CSceneGameStart.h"
#include "implementation/scenes/CSceneMainMenu.h"
#include "implementation/scenes/CScenePrimary.h"
#include "implementation/content/CDefaultMapGenerator.h"

namespace Forradia
{

/**
 * @brief Prepares game content and runs engine with it.
 *
 * Randomizes for the purpose of map generation and mobs movement.
 * Prepares custom object descriptions for some objects.
 * Prepares scenes.
 * Generates world map.
 * Prepares player starting inventory.
 * Runs engine with all the preparation data.
 */
void CGameInstance::StartGame()
{

    using std::move;

    Randomize();

    const auto MapAreaSize = 150;

    CEngine Engine;
    CObjectsContent ObjectsContent;
    CScenesCollection Scenes;

    CObjectDescription DescObjectTree1;
    CObjectDescription DescObjectTree2;
    CObjectDescription DescCaveWallBlock;

    DescObjectTree1.BlocksMovement = true;
    DescObjectTree1.BlocksSight = true;
    DescObjectTree1.Movable = false;

    DescObjectTree2.BlocksMovement = true;
    DescObjectTree2.BlocksSight = true;
    DescObjectTree2.Movable = false;

    DescCaveWallBlock.BlocksMovement = true;
    DescCaveWallBlock.BlocksSight = true;
    DescCaveWallBlock.Movable = false;

    ObjectsContent.Add("ObjectTree1", DescObjectTree1 );
    ObjectsContent.Add("ObjectTree2", DescObjectTree2 );
    ObjectsContent.Add("ObjectCaveWallBlock", DescCaveWallBlock );

    Scenes.Add("SceneGameStart", MakeUPtr<CSceneGameStart>(Engine));
    Scenes.Add("SceneMainMenu", MakeUPtr<CSceneMainMenu>(Engine));
    Scenes.Add("ScenePrimary", MakeUPtr<CScenePrimary>(Engine));

    auto WorldMap = MakeUPtr<CWorldMap>(MapAreaSize);

    CDefaultMapGenerator DefaultMapGenerator(Engine, WorldMap);

    WorldMap->GenerateWorldMap(DefaultMapGenerator);

    CInventory StartingInventory;
    StartingInventory.Add(0, "ObjectWoodaxe");

    Engine.Run(move(Scenes), GetId("SceneGameStart"), move(WorldMap), StartingInventory, ObjectsContent);
}

}
