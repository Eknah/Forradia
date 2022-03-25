#include "Common.h"
#include "CGameInstance.h"
#include "../Hidden/CEngine.h"
#include "Implementation/Scenes/CSceneGameStart.h"
#include "Implementation/Scenes/CSceneMainMenu.h"
#include "Implementation/Scenes/CScenePrimary.h"
#include "Implementation/Content/CDefaultMapGenerator.h"
namespace Forradia
{

	void CGameInstance::StartGame()
	{
        using std::move;

		Randomize();

        auto MapAreaSize = 150;

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
