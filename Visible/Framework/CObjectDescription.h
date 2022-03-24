#pragma once
namespace Forradia
{

	class CObjectDescription
	{

	public:
		CObjectDescription(bool movable, bool blocksMovement, bool blocksSight) : Movable(movable), BlocksMovement(blocksMovement), BlocksSight(blocksSight) {}

		bool Movable = False;
		bool BlocksMovement = False;
		bool BlocksSight = False;

	};

}