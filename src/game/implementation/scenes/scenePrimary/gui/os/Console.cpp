// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "Console.h"
#include "../engine/Engine.h"
#include <iostream>

namespace Forradia
{

    void Console::Render()
    {

        auto inTextLineHeight = 0.025f;

        e.FillRect(palette.mediumBlueSemiTrans, bounds.x, bounds.y, bounds.width, bounds.height);
        e.DrawRect(palette.wheat, bounds.x, bounds.y, bounds.width, bounds.height);

        if (inputActive)
            e.FillRect(palette.mediumBlue, bounds.x, bounds.y + bounds.height - inTextLineHeight, bounds.width, inTextLineHeight);

        e.DrawLine(palette.wheat, bounds.x, bounds.y + bounds.height - inTextLineHeight, bounds.x + bounds.width, bounds.y + bounds.height - inTextLineHeight);

        if (inputActive)
        {
            auto textPrinted = e.text;
            textPrinted.insert(e.cursor, "|");
            e.DrawString(std::string(textPrinted), palette.white, bounds.x + 0.005f, bounds.y + bounds.height - inTextLineHeight);
        }

        auto textboxTextX = bounds.x + margin;
        auto textBoxTextY = bounds.y + margin;

        List<String> textToPrint;

        if (fileSystem.runningProgram == nullptr)
            textToPrint = textBoxText;
        else
            textToPrint = fileSystem.runningProgram->outputText;

        auto lineHeight = 0.02f;
        auto numShownLines = CInt(bounds.height / lineHeight);
        auto startline = std::max(CInt(textToPrint.size() + 1 - numShownLines), 0);
        auto endline = std::min(startline + numShownLines - 2, CInt(textToPrint.size() - 1));

        auto y = textBoxTextY;

        for (auto i = startline; i <= endline; i++)
        {
            e.DrawString(textToPrint.at(i), palette.wheat, textboxTextX, y, false, 0.7f);
            y += lineHeight;
        }

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
                {
                    auto toPrint = e.text.substr(4);
                    Print(toPrint);
                }
                else if (InputBeginsWith("quit"))
                {
                    e.gameLoop.quit = true;
                }
                else if (InputBeginsWith("list"))
                {
                    fileSystem.PrintCurrentDirectory();
                }
                else if (InputBeginsWith("clear"))
                {
                    textBoxText.clear();
                }
                else if (InputBeginsWith("move"))
                {
                    fileSystem.MoveToFolder(e.text.substr(5));
                }
                else if (InputBeginsWith("run"))
                {
                    fileSystem.RunProgram(e.text.substr(4));
                }
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

}  // namespace Forradia
