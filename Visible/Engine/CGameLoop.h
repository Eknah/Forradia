#pragma once
namespace Forradia
{

	class CEngine;

	class CGameLoop
	{

	public:
		CGameLoop(CEngine& engine) : Engine(engine) {}

		void Run();

	private:
		void Update();
		void Render();
		static int EventFilter(void* pthis, const SDL_Event* event);

		CEngine& Engine;

	};

}