#include "Pch.h"
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
		Randomize();

        auto MapAreaSize = 150;

        CEngine Engine;
        UMap<int, UPtr<CSceneBase>> Scenes;
        CObjectsContent ObjectsContent;

        ObjectsContent.Add("ObjectTree1", {False, True, True} );
        ObjectsContent.Add("ObjectTree2", {False, True, True}  );
        ObjectsContent.Add("ObjectBoulder", {False, True, True}  );
        ObjectsContent.Add("ObjectCaveWallBlock", {False, True, False} );

        Scenes.insert({ Hash("SceneGameStart"), MakeUPtr<CSceneGameStart>(Engine) });
        Scenes.insert({ Hash("SceneMainMenu"), MakeUPtr<CSceneMainMenu>(Engine) });
        Scenes.insert({ Hash("ScenePrimary"),  MakeUPtr<CScenePrimary>(Engine) });

        auto WorldMap = MakeUPtr<CWorldMap>(MapAreaSize );

        CDefaultMapGenerator DefaultMapGenerator;

		for (auto worldy = 0; worldy < 3; worldy++)
		{
			for (auto worldx = 0; worldx < 3; worldx++)
			{
                DefaultMapGenerator.GenerateDefaultMapArea(Engine, WorldMap, {worldx, worldy});
			}
		};

        CInventory StartingInventory;
        StartingInventory.Objects.insert({ 0, MakeUPtr<CObject>("ObjectWoodaxe") });

        Engine.Run(std::move(Scenes), Hash("SceneGameStart"), std::move(WorldMap), StartingInventory, ObjectsContent);
	}
}
