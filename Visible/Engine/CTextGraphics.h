#pragma once
namespace Forradia
{

	class CEngine;

	class CTextGraphics
	{

	public:
		CTextGraphics(CEngine& engine) : Engine(engine) {}

		void InitializeEngine();

		void DrawString(String message, SDL_Color color, float x, float y, bool centerAlign = false);

	protected:


	private:
		const String DefaultFontPath = "/Resources/Fonts/PixeloidSans.ttf";
		const int DefaultFontSize = 9;
		const float Scaling = 0.8f;

		CEngine& Engine;
		std::unique_ptr<TTF_Font, CSDL_Deleter> DefaultFont;

	};

}