#pragma once
namespace Forradia
{

	class CObjectsContent
	{

	public:

        void Add(String objectName, CObjectDescription description);
		bool IsMovable(int objectType);
		bool BlocksMovement(int objectType);
		bool BlocksSight(int objectType);

		UMap<int, CObjectDescription> ObjectDescriptions;

	};

}
