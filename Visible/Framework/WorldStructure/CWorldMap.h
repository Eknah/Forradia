#pragma once
namespace Forradia
{

	class CWorldMap
	{
		public:
			CWorldMap(int mapAreaSize) : MapAreaSize(mapAreaSize) {}

			int MapAreaSize = -1;
			List<UPtr<CMapArea>> MapAreas;
			UMap<int,UMap<int, int>> MapAreaCoords;
			
	};

}