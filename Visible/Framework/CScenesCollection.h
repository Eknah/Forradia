#pragma once

namespace Forradia
{

    class CScenesCollection
    {
    public:
        void Add(String sceneName, UPtr<CSceneBase> scene);
        int GetSceneId(String sceneName);

        UMap<int, UPtr<CSceneBase>> Scenes;
    };

}
