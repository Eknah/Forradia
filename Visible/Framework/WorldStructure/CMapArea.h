#pragma once
namespace Forradia
{

	class CMapArea
	{

	public:
		CMapArea(CEngine& Engine, int mapAreaSize);

		int Size = -1;
		bool IsCave = False;
		List<List<CTile>> Tiles;
		CPoint2F PlayerStartPosition = {-1, -1};
		List<std::reference_wrapper<UPtr<CMob>>> MobsMirror;

	};

}