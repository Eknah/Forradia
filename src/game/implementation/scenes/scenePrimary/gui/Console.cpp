// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "Console.h"
#include "../engine/Engine.h"

namespace Forradia {

void Console::Render() {

    auto inputTextLineHeight = 0.025f;
    e.FillRectangle({0, 150, 255, 20}, boundsTextBox.x, boundsTextBox.y,
                         boundsTextBox.width, boundsTextBox.height);
    e.DrawRectangle({255, 255, 255, 100}, boundsTextBox.x, boundsTextBox.y,
                         boundsTextBox.width, boundsTextBox.height);

    if (inputActive)
        e.FillRectangle({0, 150, 255, 100}, boundsTextBox.x, boundsTextBox.y + boundsTextBox.height - inputTextLineHeight, boundsTextBox.width, inputTextLineHeight);

    e.DrawLine({255, 255, 255, 100}, boundsTextBox.x, boundsTextBox.y + boundsTextBox.height - inputTextLineHeight, boundsTextBox.x + boundsTextBox.width, boundsTextBox.y + boundsTextBox.height - inputTextLineHeight);

    //e.DrawString(inputText, {255, 255, 255, 255}, boundsTextBox.x, boundsTextBox.y + boundsTextBox.height - inputTextLineHeight);
    if (inputActive) {
      auto textPrinted = e.text;
      textPrinted.insert(e.cursor, "|");
      e.DrawString(std::string(textPrinted), {255, 255, 255, 255},
                   boundsTextBox.x + 0.005f,
                   boundsTextBox.y + boundsTextBox.height -
                       inputTextLineHeight);
    }
    auto TextBoxTextX = boundsTextBox.x + textBoxMargin;
    auto TextBoxTextY = boundsTextBox.y + textBoxMargin;

    auto lineHeight = 0.02f;
    auto numShownLines = static_cast<int>(boundsTextBox.height/lineHeight);
    auto startLine = std::max(static_cast<int>(textBoxText.size() - 1 - numShownLines), 0);
    auto endLine = std::min(startLine + numShownLines - 2, static_cast<int>(textBoxText.size() -  1));

    auto y = TextBoxTextY;
    for (auto i = startLine; i <= endLine; i++) {
        e.DrawString(textBoxText.at(i), {255, 255, 255, 255}, TextBoxTextX,
                          y);
        y += lineHeight;
    }


}

void Console::AttemptWriteCharacter(char c) {
    if (inputActive) {
        inputText += c;
    }
}

void Console::ToggleInput() {
    inputActive = !inputActive;
}

void Console::Print(std::string message) {
    textBoxText.push_back(message);
}

}  // namespace Forradia
