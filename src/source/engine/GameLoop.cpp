// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "GameLoop.h"

namespace Forradia
{

    void GameLoop::Run()
    {

        SDL_Event event;

        SDL_SetEventFilter((SDL_EventFilter)EventFilter, &e);

        while (!quit)
        {
            ResetForNewFrame();

            while (SDL_PollEvent(&event) != 0)
            {
                switch (event.type)
                {
                case SDL_QUIT:
                {
                    quit = true;

                    break;
                }

                case SDL_KEYDOWN:
                {
                    e.keyboardHandler.KeyDown(event.key.keysym.sym);

                    e.fullscreenController.UpdateFullscreenToggling();

                    if (event.key.keysym.sym == SDLK_RETURN)
                    {
                        if (SDL_IsTextInputActive())
                        {
                            SDL_StopTextInput();
                        }
                        else
                        {
                            SDL_StartTextInput();
                            e.text.clear();
                            e.textCursor = 0;
                        }
                    }

                    if (SDL_IsTextInputActive())
                    {
                        if (event.key.keysym.sym == SDLK_LEFT)
                        {
                            e.textCursor = std::max(0, e.textCursor - 1);
                        }
                        else if (event.key.keysym.sym == SDLK_RIGHT)
                        {
                            e.textCursor =
                                std::min(static_cast<int>(e.text.size()), e.textCursor + 1);
                        }
                        else if (event.key.keysym.sym == SDLK_BACKSPACE)
                        {
                            if (e.textCursor > 0)
                            {
                                e.text.erase(e.textCursor - 1, 1);
                                e.textCursor = std::max(0, e.textCursor - 1);
                            }
                        }
                        else if (event.key.keysym.sym == SDLK_DELETE)
                        {
                            if (e.textCursor < e.text.size())
                            {
                                e.text.erase(e.textCursor, 1);
                            }
                        }
                    }

                    e.sceneManager.GetCurrentScene()->KeyDown(event.key.keysym.sym);

                    break;
                }

                case SDL_KEYUP:
                {
                    e.keyboardHandler.KeyUp(event.key.keysym.sym);
                    e.sceneManager.GetCurrentScene()->KeyUp(event.key.keysym.sym);

                    break;
                }

                case SDL_MOUSEBUTTONDOWN:
                {

                    if (event.button.button == SDL_BUTTON_LEFT)
                    {
                        e.mouseHandler.leftButtonDown = true;
                        e.mouseHandler.SetLeftButtonBeenFired();
                        e.mouseHandler.leftDownPos = utils.GetMousePosF();
                    }
                    else if (event.button.button == SDL_BUTTON_RIGHT)
                    {
                        e.mouseHandler.rightButtonDown = true;
                        e.mouseHandler.SetRightButtonBeenFired();
                        e.mouseHandler.rightDownPos = utils.GetMousePosF();
                    }

                    e.sceneManager.GetCurrentScene()->MouseDown(event.button.button);

                    break;
                }
                case SDL_TEXTINPUT:
                {
                    e.text.append(event.text.text);
                    e.textCursor++;
                    break;
                }
                case SDL_TEXTEDITING:
                {
                    e.composition = event.edit.text;
                    e.textCursor = event.edit.start;
                    e.selection_len = event.edit.length;
                    break;
                }

                case SDL_MOUSEBUTTONUP:
                {

                    if (event.button.button == SDL_BUTTON_LEFT)
                    {
                        e.mouseHandler.leftButtonDown = false;
                        auto mousePos = utils.GetMousePosF();
                        auto dx = mousePos.x - e.mouseHandler.leftDownPos.x;
                        auto dy = mousePos.y - e.mouseHandler.leftDownPos.y;
                        e.mouseHandler.leftClickDeltaPos = dx*dx + dy*dy;
                    }
                    else if (event.button.button == SDL_BUTTON_RIGHT)
                    {
                        e.mouseHandler.rightButtonDown = false;}
                    auto mousePos = utils.GetMousePosF();
                    auto dx = mousePos.x - e.mouseHandler.rightDownPos.x;
                    auto dy = mousePos.y - e.mouseHandler.rightDownPos.y;
                    e.mouseHandler.rightClickDeltaPos = dx*dx + dy*dy;

                    e.sceneManager.GetCurrentScene()->MouseUp(event.button.button);

                    break;
                }

                case SDL_MOUSEWHEEL:
                {
                    *e.mouseHandler.wheelAmount = static_cast<float>(event.wheel.y);

                    break;
                }
                }
            }

            Update();
            Render();
        }
    }

    void GameLoop::ResetForNewFrame()
    {
        e.keyboardHandler.ResetForNewFrame();
        e.mouseHandler.ResetForNewFrame();
        e.cursor.ResetForNewFrame();
    }

    void GameLoop::Update()
    {
        e.sceneManager.GetCurrentScene()->Update();
        e.fpsCounter.Update();
    }

    void GameLoop::Render()
    {
        if (!initialized)
        {
            utilities.SetOrigCanvasSize(utilities.GetCanvasSize());

            glGenFramebuffers(1, &fbo);

            glBindFramebuffer(GL_FRAMEBUFFER, fbo);
            // The texture we're going to render to

            glGenTextures(1, &renderedTexture);

            // "Bind" the newly created texture : all future texture functions will modify this texture
            glBindTexture(GL_TEXTURE_2D, renderedTexture);

            // Give an empty image to OpenGL ( the last "0" )
            glTexImage2D(GL_TEXTURE_2D, 0,GL_RGBA, RES_WIDTH, RES_HEIGHT, 0,GL_RGBA, GL_UNSIGNED_BYTE, 0);

            // Poor filtering. Needed !
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

            glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, renderedTexture, 0);



            glGenRenderbuffers(1, &rbo);
            glBindRenderbuffer(GL_RENDERBUFFER, rbo);
            glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 800, 600);
            glBindRenderbuffer(GL_RENDERBUFFER, 0);

            glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, RES_WIDTH, RES_HEIGHT);

            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

            // Set the list of draw buffers.
            GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
            glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers

            initialized = true;
        }


        glViewport(0, 0, RES_WIDTH, RES_HEIGHT);
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);

        glClear(GL_COLOR_BUFFER_BIT);

        e.sceneManager.GetCurrentScene()->Render();
        e.fpsCounter.Render();
        e.cursor.Render();




        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
        glBlitFramebuffer(
        0, 0, RES_WIDTH, RES_HEIGHT,
        0, 0, utilities.GetOrigCanvasSize().w, utilities.GetOrigCanvasSize().h,
        GL_COLOR_BUFFER_BIT, GL_NEAREST);

        glViewport(0, 0, utilities.GetOrigCanvasSize().w, utilities.GetOrigCanvasSize().h);



        e.textGraphics.RenderAllStrings();

        SDL_GL_SwapWindow(e.window.get());
    }

    int GameLoop::EventFilter(void* pthis, const SDL_Event* event)
    {
        auto do_handle_event = event->type == SDL_WINDOWEVENT &&
            event->window.event == SDL_WINDOWEVENT_SIZE_CHANGED;

        if (!do_handle_event)
            return 1;

        IEngine* e = reinterpret_cast<IEngine*>(pthis);

        e->gameLoop.Update();
        e->gameLoop.Render();

        return 1;
    }

}  // namespace Forradia
