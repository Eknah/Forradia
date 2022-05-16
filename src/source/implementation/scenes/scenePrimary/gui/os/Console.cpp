// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "Console.h"
#include "Engine.h"
#include <iostream>


namespace Forradia
{

    void Console::Update() {

        dim resize_icon_bounds = GetResizeIconBounds();

        if (resize_icon_bounds.Contains(utils.GetMousePosF()))
            _ cursor.type = CursorTypes::Hovering;

    }

    void Console::Render() {

        using namespace Palette;

        _ FillRect(MediumBlueSemiTrans, bounds);
        _ DrawRect(Wheat, bounds);

        dim input_bounds = bounds.Copy().Translate(0.0f, bounds.h - inputLineHeight).SetHeight(inputLineHeight);

        if (input_active)
            _ FillRect(LightMediumBlueSemiTrans, input_bounds);

        _ DrawLine(Wheat, input_bounds.GetTopEdge());

        if (input_active) {

            dim text_printed = e.text;
            text_printed.insert(e.textCursor, "|");
            _ DrawString(text_printed, White, input_bounds.GetTopLeftCorner().Translate(0.005f, 0.0f));

        }

        dim textx = bounds.x + margin;
        dim texty = bounds.y + margin;

        List<String> textToPrint;

        if (fileSystem.runningProgram == nullptr)
            textToPrint = textBoxText;
        else
            textToPrint = fileSystem.runningProgram->outputText;

        dim line_height = 0.02f;
        dim num_shown_lines = CInt(bounds.h / line_height);
        dim startline = std::max(CInt(textToPrint.size() + 1 - num_shown_lines), 0);
        dim endline = std::min(startline + num_shown_lines - 2, CInt(textToPrint.size() - 1));

        dim y = texty;

        for (dim i = startline; i <= endline; i++) {

            _ DrawString(textToPrint.at(i), Wheat, textx, y, false, 0.7f);
            y += line_height;

        }

        dim resize_icon_bounds = GetResizeIconBounds();
        _ DrawImage("ConsoleResizeIcon", resize_icon_bounds.x, resize_icon_bounds.y, resize_icon_bounds.w, resize_icon_bounds.h);

    }

    void Console::ToggleInput() {

        if (input_active) {

            if (fileSystem.runningProgram != nullptr) {

                fileSystem.runningProgram->GiveInput(e.text);

            }
            else {

                if (InputBeginsWith("echo"))
                    Print(_ text.substr(5));
                elif (InputBeginsWith("quit"))
                    _ gameLoop.quit = true;
                elif (InputBeginsWith("list"))
                    fileSystem.PrintCurrentDirectory();
                elif (InputBeginsWith("clear"))
                    textBoxText.clear();
                elif (InputBeginsWith("move"))
                    fileSystem.MoveToFolder(e.text.substr(5));
                elif (InputBeginsWith("run"))
                    fileSystem.RunProgram(e.text.substr(4));

            }

        }

        input_active = !input_active;
    }

    void Console::Print(String message) {

        textBoxText.push_back(message);

    }

    void Console::Clear() {

        textBoxText.clear();

    }

    bool Console::InputBeginsWith(String text) {

        ret _ text.substr(0, text.length()) == text;

    }

    void Console::KeyDown(SDL_Keycode key) {

        if (key == SDLK_q && e.keyboardHandler.keysBeingPressed->count(SDLK_LCTRL) > 0 && fileSystem.runningProgram != nullptr) {

            Print("Exiting program: " + fileSystem.runningProgram->name);
            fileSystem.runningProgram = nullptr;

        }

    }

    RectF Console::GetResizeIconBounds() {

        dim result = RectF
        {
                bounds.x + bounds.w - utils.ConvertToFloat(resizeIconSize).w,
                bounds.y - utils.ConvertToFloat(resizeIconSize).h,
                utils.ConvertToFloat(resizeIconSize).w,
                utils.ConvertToFloat(resizeIconSize).h
        };

        ret result;

    }

    bool Console::MouseDown(Uint8 mouseButton) {

        if (mouseButton != SDL_BUTTON_LEFT) ret false;

        dim resize_icon_bounds = GetResizeIconBounds();
        
        if (resize_icon_bounds.Contains(utils.GetMousePosF())) {

            if (bounds.h == 0.15f)
                bounds.h = 0.45f;
            else
                bounds.h = 0.15f;

            bounds.y = 1.0f - 0.03f - bounds.h;

            ret true;

        }

        ret false;

    }

}  // namespace Forradia
