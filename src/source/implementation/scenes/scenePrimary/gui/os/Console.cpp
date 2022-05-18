// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "Console.h"
#include "Engine.h"
#include <iostream>


namespace Forradia
{
    void Console::Update()
	{

        auto resize_icon_bounds = GetResizeIconBounds();

        if (resize_icon_bounds.Contains(utils.GetMousePosF()))
            e.cursor.type = CursorTypes::Hovering;

    }

    void Console::Render()
	{

        using namespace Palette;

        e.FillRect(MediumBlueSemiTrans, bounds);
        e.DrawRect(Wheat, bounds);

        auto input_bounds = bounds.Copy().Translate(0.0f, bounds.h - inputLineHeight).SetHeight(inputLineHeight);

        if (input_active)
            e.FillRect(LightMediumBlueSemiTrans, input_bounds);

        e.DrawLine(Wheat, input_bounds.GetTopEdge());

        if (input_active)
		{

            auto text_printed = e.text;
            text_printed.insert(e.textCursor, "|");
            e.DrawString(text_printed, White, input_bounds.GetTopLeftCorner().Translate(0.005f, 0.0f));

        }

        auto textx = bounds.x + margin;
        auto texty = bounds.y + margin;

        List<String> textToPrint;

        if (fileSystem.runningProgram == nullptr)
            textToPrint = textBoxText;
        else
            textToPrint = fileSystem.runningProgram->outputText;

        auto line_height = 0.02f;
        auto num_shown_lines = CInt(bounds.h / line_height);
        auto startline = std::max(CInt(textToPrint.size() + 1 - num_shown_lines), 0);
        auto endline = std::min(startline + num_shown_lines - 2, CInt(textToPrint.size() - 1));

        auto y = texty;

        for (auto i = startline; i <= endline; i++)
		{

            e.DrawString(textToPrint.at(i), Wheat, textx, y, false, 0.7f);
            y += line_height;

        }

        auto resize_icon_bounds = GetResizeIconBounds();
        e.DrawImage("ConsoleResizeIcon", resize_icon_bounds.x, resize_icon_bounds.y, resize_icon_bounds.w, resize_icon_bounds.h);

    }

    void Console::ToggleInput()
	{

        if (input_active) {

            if (fileSystem.runningProgram != nullptr)
			{

                fileSystem.runningProgram->GiveInput(e.text);

            }
            else
			{

                if (InputBeginsWith("echo"))
                    Print(e.text.substr(5));
                else if (InputBeginsWith("quit"))
                    e.gameLoop.quit = true;
                else if (InputBeginsWith("list"))
                    fileSystem.PrintCurrentDirectory();
                else if (InputBeginsWith("clear"))
                    textBoxText.clear();
                else if (InputBeginsWith("move"))
                    fileSystem.MoveToFolder(e.text.substr(5));
                else if (InputBeginsWith("run"))
                    fileSystem.RunProgram(e.text.substr(4));

            }

        }

        input_active = !input_active;
    }

    void Console::Print(String message)
	{

        textBoxText.push_back(message);

    }

    void Console::Clear()
	{

        textBoxText.clear();

    }

    bool Console::InputBeginsWith(String text)
	{

        return e.text.substr(0, text.length()) == text;

    }

    void Console::KeyDown(SDL_Keycode key)
	{

        if (key == SDLK_q && e.keyboardHandler.keysBeingPressed->count(SDLK_LCTRL) > 0 && fileSystem.runningProgram != nullptr) {

            Print("Exiting program: " + fileSystem.runningProgram->name);
            fileSystem.runningProgram = nullptr;

        }

    }

    RectF Console::GetResizeIconBounds()
	{

        auto result = RectF
        {
                bounds.x + bounds.w - utils.ConvertToFloat(resizeIconSize).w,
                bounds.y - utils.ConvertToFloat(resizeIconSize).h,
                utils.ConvertToFloat(resizeIconSize).w,
                utils.ConvertToFloat(resizeIconSize).h
        };

        return result;

    }

    bool Console::MouseDown(Uint8 mouseButton)
	{

        if (mouseButton != SDL_BUTTON_LEFT) return false;

        auto resize_icon_bounds = GetResizeIconBounds();
        
        if (resize_icon_bounds.Contains(utils.GetMousePosF())) {

            if (bounds.h == 0.15f)
                bounds.h = 0.45f;
            else
                bounds.h = 0.15f;

            bounds.y = 1.0f - 0.03f - bounds.h;

            return true;

        }

        return false;

    }
}