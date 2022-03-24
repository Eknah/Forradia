#pragma once
#include "../Hidden/CUtilities.h"
namespace Forradia
{

	class CSceneMainMenu : public CSceneBase
	{

	public:
		using CSceneBase::CSceneBase;

		void Enter() override {}
		void Update() override;
		void Render() override;
		void DoMouseDown(Uint8 mouseButton) override;
		void DoMouseUp(Uint8 mouseButton) override {}

	private:
		CUtilities Utilities;

	};

}
