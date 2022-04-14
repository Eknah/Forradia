// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include <string>
#include "GameWorldRenderer.h"
#include "../engine/Engine.h"
#include "implementation/functionality/actor/modules/CoreMovementModule.h"
#include "../engine/ColorF.h"

namespace Forradia
{

    void GameWorldRenderer::Render()
    {

        background.Render(cam.zoomAmount);
        cam.SetupCamera();

        glEnable(GL_DEPTH_TEST);
        glDepthMask(GL_TRUE);
        glDepthFunc(GL_LEQUAL);
        glDepthRange(0.0f, 1000.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glPushMatrix();
        glTranslatef(0.0, -2 + 2.0, 0.0);

        RenderAllExceptRoofAndRays();
        RenderRoofAndRays();
    }

    void GameWorldRenderer::RenderAllExceptRoofAndRays()
    {
        auto mapAreaSize = e.world->mapAreaSize;
        auto& movementData = e.GetPlayer().GetModule<CoreMovementModule>();
        auto& tiles = e.GetCurrMapArea().tiles;
        auto offset = CalcOffset();

        for (auto y = 0; y < 2 * cam.GetRenderDist() + 1; y++)
        {
            for (auto x = 0; x < 2 * cam.GetRenderDist() + 1; x++)
            {
                auto dx = x - cam.GetRenderDist();
                auto dy = y - cam.GetRenderDist();

                if (dx * dx + dy * dy >= cam.GetRenderDist() * cam.GetRenderDist()) continue;

                auto tilex = movementData.position.x - cam.GetRenderDist() + x;
                auto tiley = movementData.position.y - cam.GetRenderDist() + y;

                if (tilex < 0 || tiley < 0 || tilex >= mapAreaSize || tiley >= mapAreaSize) continue;

                auto tilexI = CInt(tilex);
                auto tileyI = CInt(tiley);

                auto groundTypeId = tiles[tilexI][tileyI].groundType;

                auto waterAnimIndex0 = 0;
                auto waterAnimIndex1 = 0;
                auto waterAnimIndex2 = 0;
                auto waterAnimIndex3 = 0;

                auto tileIsWater = false;

                if (groundTypeId == groundTypeWaterId)
                {
                    tileIsWater = true;

                    waterAnimIndex0 = ((Ticks() * 1 + (tilexI * tileyI) * 10) % 3600) / 1200;
                    waterAnimIndex1 = ((Ticks() * 1 + (tilexI * (tileyI - 1)) * 10) % 3600) / 1200;
                    waterAnimIndex2 = ((Ticks() * 1 + ((tilexI + 1) * (tileyI - 1)) * 10) % 3600) / 1200;
                    waterAnimIndex3 = ((Ticks() * 1 + ((tilexI + 1) * tileyI) * 10) % 3600) / 1200;

                    if (waterAnimIndex0 > 0)
                        groundTypeId = animWaterId[waterAnimIndex0];
                }

                auto waterWaveHeight0 = waterAnimIndex0 * e.cfg.tileSize / 4.0f - e.cfg.tileSize / 10;
                auto waterWaveHeight1 = waterAnimIndex1 * e.cfg.tileSize / 4.0f - e.cfg.tileSize / 10;
                auto waterWaveHeight2 = waterAnimIndex2 * e.cfg.tileSize / 4.0f - e.cfg.tileSize / 10;
                auto waterWaveHeight3 = waterAnimIndex3 * e.cfg.tileSize / 4.0f - e.cfg.tileSize / 10;

                auto elev = GetElevValues(tilexI, tileyI);

                auto slope = elev[3] - elev[0] + elev[0] - elev[1];

                auto tileClr = ColorF();

                if (tileIsWater)
                    tileClr = {1.0f, 1.0f, 1.0f};

                else if (slope < 0)
                    tileClr = { 0.6f, 0.6f, 0.5f };

                else if (slope > 0)
                    tileClr = { 1.0f, 1.0f, 0.5f };

                else if (slope == 0)
                    tileClr = { 0.7f, 0.7f, 0.5f };

                else
                    tileClr = { 0.9f, 0.9f, 0.5f };

                glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D, e.imageLoader.images.at(groundTypeId));

                auto tileX0 = offset.x + x * e.cfg.tileSize;
                auto tileY0 = elev[0];
                auto tileZ0 = offset.y + y * e.cfg.tileSize;
                auto tileX1 = offset.x + x * e.cfg.tileSize;
                auto tileY1 = elev[1];
                auto tileZ1 = offset.y + y * e.cfg.tileSize - e.cfg.tileSize;
                auto tileX2 = offset.x + x * e.cfg.tileSize + e.cfg.tileSize;
                auto tileY2 = elev[2];
                auto tileZ2 = offset.y + y * e.cfg.tileSize - e.cfg.tileSize;
                auto tileX3 = offset.x + x * e.cfg.tileSize + e.cfg.tileSize;
                auto tileY3 = elev[3];
                auto tileZ3 = offset.y + y * e.cfg.tileSize;

                tileY0 = planetShaper.GetNewY(tileY0, CFloat(tilexI), CFloat(tileyI));
                tileY1 = planetShaper.GetNewY(tileY1, CFloat(tilexI), CFloat(tileyI) - 1);
                tileY2 = planetShaper.GetNewY(tileY2, CFloat(tilexI) + 1, CFloat(tileyI) - 1);
                tileY3 = planetShaper.GetNewY(tileY3, CFloat(tilexI) + 1, CFloat(tileyI));

                glEnable(GL_CULL_FACE);
                glCullFace(GL_FRONT);
                glBegin(GL_QUADS);

                glColor3f(tileClr.r, tileClr.g, tileClr.b);

                glTexCoord2f(0, 0);
                glVertex3f(tileX0, tileY0, tileZ0);
                glTexCoord2f(1, 0);
                glVertex3f(tileX1, tileY1, tileZ1);
                glTexCoord2f(1, 1);
                glVertex3f(tileX2, tileY2, tileZ2);
                glTexCoord2f(0, 1);
                glVertex3f(tileX3, tileY3, tileZ3);

                glEnd();

                if (groundTypeId == animWaterId[waterAnimIndex0])
                {
                    glBegin(GL_QUADS);

                    glColor3f(1.0f, 1.0f, 1.0f);

                    glTexCoord2f(0, 0);
                    glVertex3f(tileX0, tileY0 + waterWaveHeight0, tileZ0);
                    glTexCoord2f(1, 0);
                    glVertex3f(tileX1, tileY1 + waterWaveHeight1, tileZ1);
                    glTexCoord2f(1, 1);
                    glVertex3f(tileX2, tileY2 + waterWaveHeight2, tileZ2);
                    glTexCoord2f(0, 1);
                    glVertex3f(tileX3, tileY3 + waterWaveHeight3, tileZ3);

                    glEnd();
                }

                auto hoveredx = cam.GetHoveredTile().x;
                auto hoveredy = cam.GetHoveredTile().y;

                if (hoveredx == tilexI && hoveredy == tileyI && e.customCursor.cursType != CursorTypes::Hidden)
                {
                    glBindTexture(GL_TEXTURE_2D, e.imageLoader.images.at(GetId("TileHovering")));

                    glBegin(GL_QUADS);

                    glColor3f(1.0f, 1.0f, 1.0f);

                    glTexCoord2f(0, 0);
                    glVertex3f(tileX0, tileY0, tileZ0);
                    glTexCoord2f(1, 0);
                    glVertex3f(tileX1, tileY1, tileZ1);
                    glTexCoord2f(1, 1);
                    glVertex3f(tileX2, tileY2, tileZ2);
                    glTexCoord2f(0, 1);
                    glVertex3f(tileX3, tileY3, tileZ3);

                    glEnd();
                }
                glCullFace(GL_BACK);
                
                for (auto& Object : tiles[tilexI][tileyI].objects)
                {
                    auto dropShadow = true;

                    if (e.objectsContent.objectDescribers.count(Object->objectType))
                        if (e.objectsContent.objectDescribers.at(Object->objectType).flags & FlagNoShadow)
                            dropShadow = false;

                    if (dropShadow)
                    {
                        glDisable(GL_TEXTURE_2D);
                        e.DrawModel("Shadow", tileX0 + e.cfg.tileSize / 2, (tileY0 + tileY1 + tileY2 + tileY3) / 4.0f, tileZ0 - e.cfg.tileSize / 2, 0, 1.5f, 1.0f);
                    }

                    glDisable(GL_TEXTURE_2D);

                    auto tileObject = Object->objectType;
                    auto opacity = 1.0f;

                    if (e.objectsContent.objectDescribers.count(tileObject))
                        opacity = e.objectsContent.objectDescribers.at(tileObject).opacity;

                    if (tileObject != 0)
                    {
                        e.DrawModel
                        (
                            tileObject,
                            tileX0 + e.cfg.tileSize / 2,
                            (tileY0 + tileY1 + tileY2 + tileY3) / 4.0f,
                            tileZ0 - e.cfg.tileSize / 2,
                            Object->rotation,
                            Object->scaling, opacity
                        );
                    }
                }


                if (e.GetCurrMapArea().tiles[tilexI][tileyI].actor != nullptr)
                {
                    auto subxpos = (e.GetCurrMapArea().tiles[tilexI][tileyI].actor->GetModule<CoreMovementModule>().position.x - CInt(e.GetCurrMapArea().tiles[tilexI][tileyI].actor->GetModule<CoreMovementModule>().position.x)) * e.cfg.tileSize;
                    auto subypos = (e.GetCurrMapArea().tiles[tilexI][tileyI].actor->GetModule<CoreMovementModule>().position.y - CInt(e.GetCurrMapArea().tiles[tilexI][tileyI].actor->GetModule<CoreMovementModule>().position.y)) * e.cfg.tileSize;

                    glDisable(GL_TEXTURE_2D);

                    auto modelYPos0 = tileY1 + (tileY2 - tileY1) * subxpos / e.cfg.tileSize;
                    auto modelYPos1 = tileY0 + (tileY3 - tileY0) * subxpos / e.cfg.tileSize;
                    auto modelYPos = modelYPos0 + (modelYPos1 - modelYPos0) * subypos / e.cfg.tileSize;

                    e.DrawModel
                    (
                        "Shadow",
                        tileX0 + subxpos,
                        modelYPos + e.GetCurrMapArea().tiles[tilexI][tileyI].actor->GetModule<CoreMovementModule>().positionZ,
                        tileZ0 - e.cfg.tileSize + subypos,
                        0,
                        1.0f,
                        1.0f);

                    e.DrawModel
                    (
                        e.GetCurrMapArea().tiles[tilexI][tileyI].actor->GetAnimatedModelId(),
                        tileX0 + subxpos,
                        modelYPos + e.GetCurrMapArea().tiles[tilexI][tileyI].actor->GetModule<CoreMovementModule>().positionZ,
                        tileZ0 - e.cfg.tileSize + subypos,
                        *e.GetCurrMapArea().tiles[tilexI][tileyI].actor->GetModule<CoreMovementModule>().facingAngle
                    );
                }



            }
        }
    }




    void GameWorldRenderer::RenderRoofAndRays()
    {

        auto mapAreaSize = e.world->mapAreaSize;
        auto offset = CalcOffset();

        for (auto y = 0; y < 2 * cam.GetRenderDist() + 1; y++)
        {
            for (auto x = 0; x < 2 * cam.GetRenderDist() + 1; x++)
            {
                auto dx = x - cam.GetRenderDist();
                auto dy = y - cam.GetRenderDist();

                if (dx * dx + dy * dy >= cam.GetRenderDist() * cam.GetRenderDist()) continue;

                auto tileX = e.GetPlayer().GetModule<CoreMovementModule>().position.x - cam.GetRenderDist() + x;
                auto tileY = e.GetPlayer().GetModule<CoreMovementModule>().position.y - cam.GetRenderDist() + y;

                if (tileX < 0 || tileY < 0 || tileX >= mapAreaSize || tileY >= mapAreaSize) continue;

                auto tileXI = CInt(tileX);
                auto tileYI = CInt(tileY);

                auto elev = GetElevValues(tileXI, tileYI);

                auto slope = elev[3] - elev[0] + elev[0] - elev[1];

                auto tileX0 = offset.x + x * e.cfg.tileSize;
                auto tileY0 = elev[0];
                auto tileZ0 = offset.y + y * e.cfg.tileSize;
                auto tileX1 = offset.x + x * e.cfg.tileSize;
                auto tileY1 = elev[1];
                auto tileZ1 = offset.y + y * e.cfg.tileSize - e.cfg.tileSize;
                auto tileX2 = offset.x + x * e.cfg.tileSize + e.cfg.tileSize;
                auto tileY2 = elev[2];
                auto tileZ2 = offset.y + y * e.cfg.tileSize - e.cfg.tileSize;
                auto tileX3 = offset.x + x * e.cfg.tileSize + e.cfg.tileSize;
                auto tileY3 = elev[3];
                auto tileZ3 = offset.y + y * e.cfg.tileSize;

                tileY0 = planetShaper.GetNewY(tileY0, CFloat(tileXI), CFloat(tileYI));
                tileY1 = planetShaper.GetNewY(tileY1, CFloat(tileXI), CFloat(tileYI) - 1);
                tileY2 = planetShaper.GetNewY(tileY2, CFloat(tileXI) + 1, CFloat(tileYI) - 1);
                tileY3 = planetShaper.GetNewY(tileY3, CFloat(tileXI) + 1, CFloat(tileYI));

                glDisable(GL_TEXTURE_2D);

                if (e.GetCurrMapArea().tiles[tileXI][tileYI].roof != nullptr)
                {

                    auto& roof = e.GetCurrMapArea().tiles[tileXI][tileYI].roof;
                    auto roofObject = roof->objectType;
                    auto opacity = 1.0f;

                    if (e.objectsContent.objectDescribers.count(roofObject))
                        opacity = e.objectsContent.objectDescribers.at(roofObject).opacity;

                    e.DrawModel
                    (
                        roofObject,
                        tileX0 + e.cfg.tileSize / 2,
                        (tileY0 + tileY1 + tileY2 + tileY3) / 4.0f,
                        tileZ0 - e.cfg.tileSize / 2,
                        roof->rotation,
                        roof->scaling,
                        opacity
                    );

                }

                glDisable(GL_TEXTURE_2D);

            }
        }

    }

    float GameWorldRenderer::CalcPlayerElev()
    {
        auto& movementData = e.GetPlayer().GetModule<CoreMovementModule>();
        auto& tiles = e.GetCurrMapArea().tiles;

        auto playerXInt = CInt(movementData.position.x);
        auto playerYInt = CInt(movementData.position.y);
        auto elevPlayer0 = tiles[playerXInt][playerYInt].elevation / elevAmount;
        auto elevPlayer1 = tiles[playerXInt + 1][playerYInt].elevation / elevAmount;
        auto elevPlayer2 = tiles[playerXInt + 1][playerYInt + 1].elevation / elevAmount;
        auto elevPlayer3 = tiles[playerXInt][playerYInt + 1].elevation / elevAmount;
        auto elevX = movementData.position.x - playerXInt;
        auto elevY = movementData.position.y - playerYInt;

        auto elevPlayer =
            (elevPlayer0 + (elevPlayer1 - elevPlayer0) * elevX +
            elevPlayer3 + (elevPlayer2 - elevPlayer3) * elevX +
            elevPlayer0 + (elevPlayer3 - elevPlayer0) * elevY +
            elevPlayer1 + (elevPlayer2 - elevPlayer1) * elevY) /
            4.0f;

            return elevPlayer;
    }

    Point2F GameWorldRenderer::CalcOffset()
    {
        auto& movementData = e.GetPlayer().GetModule<CoreMovementModule>();

        auto playerXInt = CInt(movementData.position.x);
        auto playerYInt = CInt(movementData.position.y);

        float subStepX = movementData.position.x - playerXInt;
        float subStepY = movementData.position.y - playerYInt;

        auto offsetX = -CFloat(2.0f * cam.GetRenderDist() + 1.0f) / 2.0f * e.cfg.tileSize - subStepX * e.cfg.tileSize;
        auto offsetY = -CFloat(2.0f * cam.GetRenderDist() - 1.0f) / 2.0f * e.cfg.tileSize - subStepY * e.cfg.tileSize;

        return {offsetX, offsetY};
    }

    std::array<float, 4> GameWorldRenderer::GetElevValues(int tilexI, int tileyI)
    {
        auto mapAreaSize = e.world->mapAreaSize;
        auto& tiles = e.GetCurrMapArea().tiles;
        auto elevPlayer = CalcPlayerElev();

        auto elev0 = 0.0f;
        auto elev1 = 0.0f;
        auto elev2 = 0.0f;
        auto elev3 = 0.0f;

        if (tilexI >= 0 && tileyI >= 0 && tilexI < mapAreaSize && tileyI < mapAreaSize)
            elev0 = tiles[tilexI][tileyI].elevation / elevAmount - elevPlayer;

        if (tilexI >= 0 && tileyI - 1 >= 0 && tilexI < mapAreaSize && tileyI - 1 < mapAreaSize)
            elev1 = tiles[tilexI][tileyI - 1].elevation / elevAmount - elevPlayer;
        else
            elev1 = elev0;

        if (tilexI + 1 >= 0 && tileyI - 1 >= 0 && tilexI + 1 < mapAreaSize && tileyI - 1 < mapAreaSize)
            elev2 = tiles[tilexI + 1][tileyI - 1].elevation / elevAmount - elevPlayer;
        else if (tilexI + 1 < mapAreaSize)
            elev2 = tiles[tilexI + 1][tileyI].elevation / elevAmount - elevPlayer;
        else if (tileyI - 1 >= 0)
            elev2 = tiles[tilexI][tileyI - 1].elevation / elevAmount - elevPlayer;
        else
            elev2 = elev0;

        if (tilexI + 1 >= 0 && tileyI >= 0 && tilexI + 1 < mapAreaSize && tileyI < mapAreaSize)
            elev3 = tiles[tilexI + 1][tileyI].elevation / elevAmount - elevPlayer;
        else
            elev3 = elev0;

        return { elev0, elev1, elev2, elev3 };

    }

}  // namespace Forradia
