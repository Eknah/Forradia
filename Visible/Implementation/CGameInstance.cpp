#include "Pch.h"
#include "CGameInstance.h"
#include "../Hidden/CEngine.h"
#include "Implementation/Scenes/CSceneGameStart.h"
#include "Implementation/Scenes/CSceneMainMenu.h"
#include "Implementation/Scenes/CScenePrimary.h"
#include "Implementation/Content/CDefaultMapGenerator.h"
namespace Forradia
{
	/**
	 * @brief Sets up an engine instance, with game content input and then runs it.
	*/
	void CGameInstance::StartGame()
	{
		Randomize();

		auto map_area_size = 150;

		CEngine engine;
		UMap<int, UPtr<CSceneBase>> scenes;
		CObjectsContent objects_content;

		objects_content.ObjectDescriptions.insert({ int(Hash("ObjectTree1")), {False, True, True} });
		objects_content.ObjectDescriptions.insert({ int(Hash("ObjectTree2")), {False, True, True} });
		objects_content.ObjectDescriptions.insert({ int(Hash("ObjectBoulder")), {False, True, True} });
		objects_content.ObjectDescriptions.insert({ int(Hash("ObjectCaveWallBlock")), {False, True, False} });

		scenes.insert({ Hash("SceneGameStart"), MakeUPtr<CSceneGameStart>(engine) });
		scenes.insert({ Hash("SceneMainMenu"), MakeUPtr<CSceneMainMenu>(engine) });
		scenes.insert({ Hash("ScenePrimary"),  MakeUPtr<CScenePrimary>(engine) });

		auto world_map = MakeUPtr<CWorldMap>(map_area_size);

		CDefaultMapGenerator default_map_generator;

		for (auto worldy = 0; worldy < 3; worldy++)
		{
			for (auto worldx = 0; worldx < 3; worldx++)
			{
				default_map_generator.GenerateDefaultMapArea(engine, world_map, {worldx, worldy});
			}
		};

		CInventory starting_inventory;
        starting_inventory.Objects.insert({ 0, MakeUPtr<CObject>("ObjectWoodaxe") });

		engine.Run(std::move(scenes), Hash("SceneGameStart"), std::move(world_map), starting_inventory, objects_content);
	}
}
