#include "Common.h"
#include "CPaintGraphics.h"
namespace Forradia
{
	void CPaintGraphics::FillRectangle(SDL_Color color, float X, float Y, float width, float height)
	{
		std::vector<CPoint2F> vertices =
		{
		 {X,Y},
		 {X, Y + height},
		 {X + width, Y + height},
		 {X + width, Y}
		};
		RenderShape(GL_QUADS, vertices, color);
	}
	void CPaintGraphics::DrawRectangle(SDL_Color color, float X, float Y, float width, float height)
	{
		std::vector<CPoint2F> vertices =
		{
		 {X,Y},
		 {X, Y + height},
		 {X + width, Y + height},
		 {X + width, Y}
		};
		RenderShape(GL_LINE_LOOP, vertices, color);
	}
	void CPaintGraphics::DrawLine(SDL_Color color, float x0, float y0, float x1, float y1)
	{
		std::vector<CPoint2F> vertices =
		{
		 {x0,y0},
		 {x1, y1}
		};
		RenderShape(GL_LINE_STRIP, vertices, color);
	}
	void CPaintGraphics::RenderShape(GLenum geometryType, std::vector<CPoint2F>& vertices, SDL_Color color)
	{
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
		glDisable(GL_TEXTURE_2D);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f);
		glBegin(geometryType);
		glColor4f(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, color.a / 255.0f);
		for (auto& v : vertices)
			glVertex2f(v.X, v.Y);
		glEnd();
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
	}
}