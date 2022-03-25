#pragma once

namespace Forradia
{

    class CScenesCollection
    {
    public:
        void Add(String sceneName, UPtr<CSceneBase> scene);

        UMap<int, UPtr<CSceneBase>> Scenes;
    };

}
