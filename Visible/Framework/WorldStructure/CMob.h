#pragma once
namespace Forradia
{

	class CMob
	{
		public:

		CMob(float x, float y) : Position(x, y) {}

		int TickLastMove = 0;
		int MoveSpeed = 30;
		float StepSize = 1.0f;
		float StepMultiplier = 0.1f;
		float FacingAngle = 0.0f;
		CPoint2F Position = {-1, -1};
		CPoint2F MoveDestination = {-1, -1};
	};

}