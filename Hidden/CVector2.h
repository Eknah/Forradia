#pragma once
namespace Forradia
{

	class CVector2
	{

	public:
		CVector2() : X(0.0f), Y(0.0f) {}
		CVector2(float x, float y) : X(x), Y(y) {}

		float X;
		float Y;
	};

}