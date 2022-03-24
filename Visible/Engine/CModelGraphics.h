#pragma once
namespace Forradia
{

	class CEngine;

	class CModelGraphics
	{

	public:
		CModelGraphics(CEngine& engine) : Engine(engine) {}

		void DrawModel(String modelName, float x, float y, float z, float rotation = 0.0f, float alpha = 1.0f, float specificScaling = 1.0f, CVector3 rotVec = CVector3(0, 0, 0));
		void DrawModel(int modelNameHash, float x, float y, float z, float rotation = 0.0f, float alpha = 1.0f, float specificScaling = 1.0f, CVector3 rotVec = CVector3(0, 0, 0));

	private:

		CEngine& Engine;

		float ModelScaling = 0.1f;
	};

}