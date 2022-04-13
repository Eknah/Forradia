// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "Console.h"
#include "../engine/Engine.h"
#include <iostream>

namespace Forradia
{

    void Console::Render()
    {

        auto inputTextLineHeight = 0.025f;
        e.FillRectangle({ 0, 50, 100, 200 }, boundsTextBox.x, boundsTextBox.y,
            boundsTextBox.width, boundsTextBox.height);
        e.DrawRectangle({ 255, 255, 255, 100 }, boundsTextBox.x, boundsTextBox.y,
            boundsTextBox.width, boundsTextBox.height);

        if (inputActive)
            e.FillRectangle({ 0, 150, 255, 100 }, boundsTextBox.x, boundsTextBox.y + boundsTextBox.height - inputTextLineHeight, boundsTextBox.width, inputTextLineHeight);

        e.DrawLine({ 255, 255, 255, 100 }, boundsTextBox.x, boundsTextBox.y + boundsTextBox.height - inputTextLineHeight, boundsTextBox.x + boundsTextBox.width, boundsTextBox.y + boundsTextBox.height - inputTextLineHeight);

        if (inputActive)
        {
            auto textPrinted = e.text;
            textPrinted.insert(e.cursor, "|");
            e.DrawString(std::string(textPrinted), { 255, 255, 255, 255 },
                boundsTextBox.x + 0.005f,
                boundsTextBox.y + boundsTextBox.height -
                inputTextLineHeight);
        }
        auto TextBoxTextX = boundsTextBox.x + textBoxMargin;
        auto TextBoxTextY = boundsTextBox.y + textBoxMargin;

        std::vector<std::string> textToPrint;
        if (fileSystem.runningProgram == nullptr)
            textToPrint = textBoxText;
        else
            textToPrint = fileSystem.runningProgram->outputText;

        auto lineHeight = 0.02f;
        auto numShownLines = static_cast<int>(boundsTextBox.height / lineHeight);
        auto startLine = std::max(static_cast<int>(textToPrint.size() + 1 - numShownLines), 0);
        auto endLine = std::min(startLine + numShownLines - 2, static_cast<int>(textToPrint.size() - 1));

        auto y = TextBoxTextY;
        for (auto i = startLine; i <= endLine; i++)
        {
            e.DrawString(textToPrint.at(i), { 255, 255, 210, 255 }, TextBoxTextX, y, false, 0.7f);
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
                if (e.text.substr(0, 4) == "echo")
                {
                    auto toPrint = e.text.substr(4);
                    Print(toPrint);
                }
                else if (e.text.substr(0, 4) == "quit")
                {
                    e.gameLoop.quit = true;
                }
                else if (e.text.substr(0, 4) == "list")
                {
                    fileSystem.PrintCurrentDirectory();
                }
                else if (e.text.substr(0, 5) == "clear")
                {
                    textBoxText.clear();
                }
                else if (e.text.substr(0, 4) == "move")
                {
                    fileSystem.MoveToFolder(e.text.substr(5));
                }
                else if (e.text.substr(0, 3) == "run")
                {
                    fileSystem.RunProgram(e.text.substr(4));
                }
            }
        }

        inputActive = !inputActive;
    }

    void Console::Print(std::string message)
    {
        textBoxText.push_back(message);
    }

    void Console::Clear()
    {
        textBoxText.clear();
    }

}  // namespace Forradia
