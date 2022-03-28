# Forradia

![Forradia!](/resources/images/Icon.png "Forradia")

Forradia is a cross-platform sandbox survival/RPG game written in C++ with OpenGL and SDL2.
The engine loads 3D models in Wavefront-format as well as textures and fonts. The maps are tile-based and fully randomly generated.

## Motivation
The purpose of this project is mainly that I use it to improve my knowledge and experience in this technical areas, and eventually find collaborators.

## Build status
[![Build status](https://ci.appveyor.com/api/projects/status/crge78bph1g0ki14?svg=true)](https://ci.appveyor.com/project/Eknah/forradia)

## Code style
[![MegaLinter](https://github.com/Eknah/Forradia/workflows/MegaLinter/badge.svg?branch=main)](https://github.com/Eknah/Forradia/actions?query=workflow%3AMegaLinter+branch%3Amain)

## Screenshots
![Forradia Screenshot 1!](/resources/images/Screenshot1.png "Forradia Screenshot 1")
![Forradia Screenshot 2!](/resources/images/Screenshot2.png "Forradia Screenshot 2")

## Tech/framework used
**Built with**
* Qt Creator
* CMake

## Features
* Engine allows representation of world map as planets instead of regular flat maps
* Open-source under MIT license
* Cross-platform
* Only two dependencies: OpenGL and SDL2

## Code Example
**Engine implementation example**

    ObjectsContent.Add("ObjectTree1", DescObjectTree1 );
    ObjectsContent.Add("ObjectTree2", DescObjectTree2 );
    ObjectsContent.Add("ObjectCaveWallBlock", DescCaveWallBlock );

    Scenes.Add("SceneGameStart", MakeUPtr<CSceneGameStart>(Engine));
    Scenes.Add("SceneMainMenu", MakeUPtr<CSceneMainMenu>(Engine));
    Scenes.Add("ScenePrimary", MakeUPtr<CScenePrimary>(Engine));
    
    WorldMap->GenerateWorldMap(DefaultMapGenerator);
    
    StartingInventory.Add(0, "ObjectWoodaxe");
    
    Engine.Run(move(Scenes), GetId("SceneGameStart"), move(WorldMap), StartingInventory, ObjectsContent);

## Installation
To add

## API Reference
To add

## Tests
To add

## How to use?
To add

## Contribute
To add

## License
MIT