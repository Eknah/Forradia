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

        ObjectsContent.Add("ObjectTree1", {False, True, True} );
        ObjectsContent.Add("ObjectTree2", {False, True, True}  );
        ObjectsContent.Add("ObjectBoulder", {False, True, True}  );
        ObjectsContent.Add("ObjectCaveWallBlock", {False, True, False} );

        Scenes.Add("SceneGameStart", MakeUPtr<CSceneGameStart>(Engine));
        Scenes.Add("SceneMainMenu", MakeUPtr<CSceneMainMenu>(Engine));
        Scenes.Add("ScenePrimary", MakeUPtr<CScenePrimary>(Engine));

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
        StartingInventory.Add(0, "ObjectWoodaxe");

        Engine.Run(move(Scenes), Hash("SceneGameStart"), move(WorldMap), StartingInventory, ObjectsContent);
	}
}
