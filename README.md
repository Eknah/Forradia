# Forradia
This is a cross-platform indie game written in C++ which is utilizing OpenGL for 3D rendering.
It loads 3D models in Wavefront .obj-format (and materials in .mtl-format) and textures and sprites in .png-format, as well as a font in ttf-format. The wild-nature-themed maps are fully random-generated, at least in the projects current status.

## Motivation
The purpose of this project is mainly that I use it to improve my knowledge and experience in this technical areas, and eventually find collaborators. It is also a way for me to have fun and express creativity!

## Build status
To add

## Code style
To add

## Screenshots
To add

## Tech/framework used
**Built with**
* Qt Creator
* CMake

## Features
* Open-source
* Cross-platform
* Only two dependencies: OpenGL and SDL2
* Excellent foundation for further development and application performance with C++ as primary language

## Code Example
Implementation example of the game engine from the actual code:

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

## Credits
Inspirational repos:
* [ManaPlus](https://github.com/ManaPlus/ManaPlus)

Game inspiration sources:
* RPG World Online
* Wurm Online

## License
MIT ©
