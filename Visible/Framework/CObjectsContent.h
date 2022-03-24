#pragma once
namespace Forradia
{

	class CObjectsContent
	{

	public:

		bool IsMovable(int objectType);
		bool BlocksMovement(int objectType);
		bool BlocksSight(int objectType);

		UMap<int, CObjectDescription> ObjectDescriptions;

	};

}