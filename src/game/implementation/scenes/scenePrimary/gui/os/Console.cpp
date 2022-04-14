// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "Console.h"
#include "../engine/Engine.h"
#include <iostream>

namespace Forradia
{

    void Console::Update()
    {
        auto resizeIconBounds = GetResizeIconBounds();
        
        if (resizeIconBounds.Contains(utils.GetMousePosF()))
        {
            e.customCursor.cursType = CursorTypes::Hovering;
        }
    }

    void Console::Render()
    {

        e.FillRect(palette.mediumBlueSemiTrans, bounds);
        e.DrawRect(palette.wheat, bounds);

        auto inputBounds = bounds.Copy().Translate(0.0f, bounds.h - inputLineHeight).SetHeight(inputLineHeight);

        if (inputActive)
            e.FillRect(palette.mediumBlue, inputBounds);

        e.DrawLine(palette.wheat, inputBounds.GetTopEdge());

        if (inputActive)
        {
            auto textPrinted = e.text;
            textPrinted.insert(e.cursor, "|");
            e.DrawString(textPrinted, palette.white, inputBounds.GetTopLeftCorner().Translate(0.005f, 0.0f));
        }

        auto textx = bounds.x + margin;
        auto texty = bounds.y + margin;

        List<String> textToPrint;

        if (fileSystem.runningProgram == nullptr)
            textToPrint = textBoxText;
        else
            textToPrint = fileSystem.runningProgram->outputText;

        auto lineHeight = 0.02f;
        auto numShownLines = CInt(bounds.h / lineHeight);
        auto startline = std::max(CInt(textToPrint.size() + 1 - numShownLines), 0);
        auto endline = std::min(startline + numShownLines - 2, CInt(textToPrint.size() - 1));

        auto y = texty;

        for (auto i = startline; i <= endline; i++)
        {
            e.DrawString(textToPrint.at(i), palette.wheat, textx, y, false, 0.7f);
            y += lineHeight;
        }

        auto resizeIconBounds = GetResizeIconBounds();
        e.DrawImage("ConsoleResizeIcon", resizeIconBounds.x, resizeIconBounds.y, resizeIconBounds.w, resizeIconBounds.h);

    }

    void Console::ToggleInput()
    {

        if (inputActive)
        {
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

        inputActive = !inputActive;
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

    void Console::DoKeyDown(SDL_Keycode key)
    {
        if (key == SDLK_q && e.keyboardHandler.keysBeingPressed->count(SDLK_LCTRL) > 0 && fileSystem.runningProgram != nullptr)
        {
            Print("Exiting program: " + fileSystem.runningProgram->name);
            fileSystem.runningProgram = nullptr;
        }
    }

    RectF Console::GetResizeIconBounds()
    {
        auto result = RectF { bounds.x + bounds.w - utils.ConvertToFloat(resizeIconSize).w, bounds.y - utils.ConvertToFloat(resizeIconSize).h, utils.ConvertToFloat(resizeIconSize).w, utils.ConvertToFloat(resizeIconSize).h };
        return result;
    }

    bool Console::DoMouseDown(Uint8 mouseButton)
    {
        if (mouseButton != SDL_BUTTON_LEFT) return false;

        auto resizeIconBounds = GetResizeIconBounds();
        
        if (resizeIconBounds.Contains(utils.GetMousePosF()))
        {
            if (bounds.h == 0.15f)
            {
                bounds.h = 0.45f;
            }
            else
            {
                bounds.h = 0.15f;
            }

            bounds.y = 1.0f - 0.03f - bounds.h;

            return true;
        }

        return false;
    }

}  // namespace Forradia
