// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include <string>
#include "GameWorldRenderer.h"
#include "../engine/Engine.h"
#include "implementation/functionality/actor/modules/CoreMovementModule.h"

namespace Forradia
{

    void GameWorldRenderer::Render()
    {
        background.Render(camera.zoomAmount);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(e.cfg.fov, 1.333, 0.5, 100);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        auto cameraX = 0.0f;
        auto cameraZ = -1.0f;
        auto angleRadians = atan2(cameraZ, cameraX) + camera.lookingAngle / 180.0f * M_PI;
        auto cameraDist = 1;
        auto zoom = camera.zoomAmount;
        auto zoomEx = std::max(zoom, 1.0f);

        glTranslatef(0.0f, -zoomEx - 1, -(zoomEx - 1.0f) * 4.0f);

        cameraX = CFloat(cos(angleRadians)) * cameraDist;
        cameraZ = -CFloat(sin(angleRadians)) * cameraDist;

        gluLookAt
        (
            cameraX - e.cfg.tileSize / 2,
            camera.cameraHeight * (zoomEx - 0.5f),
            cameraZ - e.cfg.tileSize / 2,
            -e.cfg.tileSize / 2,
            -1,
            -e.cfg.tileSize / 2,
            0,
            1,
            0
        );

        glEnable(GL_DEPTH_TEST);
        glDepthMask(GL_TRUE);
        glDepthFunc(GL_LEQUAL);
        glDepthRange(0.0f, 1000.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glPushMatrix();
        glTranslatef(0.0, -2 + 2.0, 0.0);

        RenderAllExceptRoofAndRays();
        RenderRoofAndRays();

        glPopMatrix();
        glDisable(GL_DEPTH_TEST);
    }

    void GameWorldRenderer::RenderAllExceptRoofAndRays()
    {
        auto mapAreaSize = e.world->mapAreaSize;
        auto& movementData = e.GetPlayer().GetModule<CoreMovementModule>();
        auto& tiles = e.GetCurrMapArea().tiles;
        auto elevPlayer = CalcPlayerElev();
        auto offset = CalcOffset();

        for (auto y = 0; y < 2 * camera.GetRenderDistance() + 1; y++)
        {
            for (auto x = 0; x < 2 * camera.GetRenderDistance() + 1; x++)
            {
                auto dx = x - camera.GetRenderDistance();
                auto dy = y - camera.GetRenderDistance();

                if (dx * dx + dy * dy >= camera.GetRenderDistance() * camera.GetRenderDistance()) continue;

                auto tileX = movementData.position.x - camera.GetRenderDistance() + x;
                auto tileY = movementData.position.y - camera.GetRenderDistance() + y;

                if (tileX < 0 || tileY < 0 || tileX >= mapAreaSize || tileY >= mapAreaSize) continue;

                auto tileXI = CInt(tileX);
                auto tileYI = CInt(tileY);

                auto groundTypeId = tiles[tileXI][tileYI].groundType;

                auto waterAnimIndex0 = 0;
                auto waterAnimIndex1 = 0;
                auto waterAnimIndex2 = 0;
                auto waterAnimIndex3 = 0;

                auto tileIsWater = false;

                if (groundTypeId == groundTypeWaterId)
                {
                    tileIsWater = true;

                    waterAnimIndex0 = ((Ticks() * 1 + (tileXI * tileYI) * 10) % 3600) / 1200;
                    waterAnimIndex1 = ((Ticks() * 1 + (tileXI * (tileYI - 1)) * 10) % 3600) / 1200;
                    waterAnimIndex2 = ((Ticks() * 1 + ((tileXI + 1) * (tileYI - 1)) * 10) % 3600) / 1200;
                    waterAnimIndex3 = ((Ticks() * 1 + ((tileXI + 1) * tileYI) * 10) % 3600) / 1200;

                    if (waterAnimIndex0 > 0)
                        groundTypeId = animWaterId[waterAnimIndex0];
                }

                auto elev0 = 0.0f;
                auto elev1 = 0.0f;
                auto elev2 = 0.0f;
                auto elev3 = 0.0f;

                auto waterWaveHeight0 = waterAnimIndex0 * e.cfg.tileSize / 4.0f - e.cfg.tileSize / 10;
                auto waterWaveHeight1 = waterAnimIndex1 * e.cfg.tileSize / 4.0f - e.cfg.tileSize / 10;
                auto waterWaveHeight2 = waterAnimIndex2 * e.cfg.tileSize / 4.0f - e.cfg.tileSize / 10;
                auto waterWaveHeight3 = waterAnimIndex3 * e.cfg.tileSize / 4.0f - e.cfg.tileSize / 10;

                if (tileX >= 0 && tileY >= 0 && tileX < mapAreaSize && tileY < mapAreaSize)
                    elev0 = tiles[tileXI][tileYI].elevation / elevAmount - elevPlayer;

                if (tileX >= 0 && tileY - 1 >= 0 && tileX < mapAreaSize && tileY - 1 < mapAreaSize)
                    elev1 = tiles[tileXI][tileYI - 1].elevation / elevAmount - elevPlayer;
                else
                    elev1 = elev0;

                if (tileX + 1 >= 0 && tileY - 1 >= 0 && tileX + 1 < mapAreaSize && tileY - 1 < mapAreaSize)
                    elev2 = tiles[tileXI + 1][tileYI - 1].elevation / elevAmount - elevPlayer;
                else if (tileX + 1 < mapAreaSize)
                    elev2 = tiles[tileXI + 1][tileYI].elevation / elevAmount - elevPlayer;
                else if (tileY - 1 >= 0)
                    elev2 = tiles[tileXI][tileYI - 1].elevation / elevAmount - elevPlayer;
                else
                    elev2 = elev0;

                if (tileX + 1 >= 0 && tileY >= 0 && tileX + 1 < mapAreaSize && tileY < mapAreaSize)
                    elev3 = tiles[tileXI + 1][tileYI].elevation / elevAmount - elevPlayer;
                else
                    elev3 = elev0;

                auto slope = elev3 - elev0 + elev0 - elev1;

                auto r = 0.9f;
                auto g = 0.9f;
                auto b = 0.5f;

                if (tileIsWater)
                {
                    r = 1.0f;
                    g = 1.0f;
                    b = 1.0f;
                }
                else if (slope < 0)
                {
                    r = 0.6f;
                    g = 0.6f;
                    b = 0.5f;
                }
                else if (slope > 0)
                {
                    r = 1.0f;
                    g = 1.0f;
                    b = 0.5f;
                }
                else if (slope == 0)
                {
                    r = 0.7f;
                    g = 0.7f;
                    b = 0.5f;
                }

                glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D, e.imageLoader.images.at(groundTypeId));

                auto tileX0 = offset.x + x * e.cfg.tileSize;
                auto tileY0 = elev0;
                auto tileZ0 = offset.y + y * e.cfg.tileSize;
                auto tileX1 = offset.x + x * e.cfg.tileSize;
                auto tileY1 = elev1;
                auto tileZ1 = offset.y + y * e.cfg.tileSize - e.cfg.tileSize;
                auto tileX2 = offset.x + x * e.cfg.tileSize + e.cfg.tileSize;
                auto tileY2 = elev2;
                auto tileZ2 = offset.y + y * e.cfg.tileSize - e.cfg.tileSize;
                auto tileX3 = offset.x + x * e.cfg.tileSize + e.cfg.tileSize;
                auto tileY3 = elev3;
                auto tileZ3 = offset.y + y * e.cfg.tileSize;

                tileY0 = planetShaper.GetNewY(tileY0, CFloat(tileXI), CFloat(tileYI));
                tileY1 = planetShaper.GetNewY(tileY1, CFloat(tileXI), CFloat(tileYI) - 1);
                tileY2 = planetShaper.GetNewY(tileY2, CFloat(tileXI) + 1, CFloat(tileYI) - 1);
                tileY3 = planetShaper.GetNewY(tileY3, CFloat(tileXI) + 1, CFloat(tileYI));

                glEnable(GL_CULL_FACE);
                glCullFace(GL_FRONT);
                glBegin(GL_QUADS);

                glColor3f(r, g, b);

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

                auto hoveredx = camera.GetHoveredTile().x;
                auto hoveredy = camera.GetHoveredTile().y;

                if (hoveredx == tileXI && hoveredy == tileYI && e.customCursor.cursType != CursorTypes::Hidden)
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
                
                for (auto& Object : tiles[tileXI][tileYI].objects)
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


                if (e.GetCurrMapArea().tiles[tileXI][tileYI].actor != nullptr)
                {
                    auto subxpos = (e.GetCurrMapArea().tiles[tileXI][tileYI].actor->GetModule<CoreMovementModule>().position.x - CInt(e.GetCurrMapArea().tiles[tileXI][tileYI].actor->GetModule<CoreMovementModule>().position.x)) * e.cfg.tileSize;
                    auto subypos = (e.GetCurrMapArea().tiles[tileXI][tileYI].actor->GetModule<CoreMovementModule>().position.y - CInt(e.GetCurrMapArea().tiles[tileXI][tileYI].actor->GetModule<CoreMovementModule>().position.y)) * e.cfg.tileSize;

                    glDisable(GL_TEXTURE_2D);

                    auto modelYPos0 = tileY1 + (tileY2 - tileY1) * subxpos / e.cfg.tileSize;
                    auto modelYPos1 = tileY0 + (tileY3 - tileY0) * subxpos / e.cfg.tileSize;
                    auto modelYPos = modelYPos0 + (modelYPos1 - modelYPos0) * subypos / e.cfg.tileSize;

                    e.DrawModel
                    (
                        "Shadow",
                        tileX0 + subxpos,
                        modelYPos + e.GetCurrMapArea().tiles[tileXI][tileYI].actor->GetModule<CoreMovementModule>().positionZ,
                        tileZ0 - e.cfg.tileSize + subypos,
                        0,
                        1.0f,
                        1.0f);

                    e.DrawModel
                    (
                        e.GetCurrMapArea().tiles[tileXI][tileYI].actor->GetAnimatedModelId(),
                        tileX0 + subxpos,
                        modelYPos + e.GetCurrMapArea().tiles[tileXI][tileYI].actor->GetModule<CoreMovementModule>().positionZ,
                        tileZ0 - e.cfg.tileSize + subypos,
                        *e.GetCurrMapArea().tiles[tileXI][tileYI].actor->GetModule<CoreMovementModule>().facingAngle
                    );
                }



            }
        }
    }




    void GameWorldRenderer::RenderRoofAndRays()
    {

        auto mapAreaSize = e.world->mapAreaSize;
        auto elevPlayer = CalcPlayerElev();
        auto offset = CalcOffset();

        for (auto y = 0; y < 2 * camera.GetRenderDistance() + 1; y++)
        {
            for (auto x = 0; x < 2 * camera.GetRenderDistance() + 1; x++)
            {
                auto dx = x - camera.GetRenderDistance();
                auto dy = y - camera.GetRenderDistance();

                if (dx * dx + dy * dy >= camera.GetRenderDistance() * camera.GetRenderDistance()) continue;

                auto tileX = e.GetPlayer().GetModule<CoreMovementModule>().position.x - camera.GetRenderDistance() + x;
                auto tileY = e.GetPlayer().GetModule<CoreMovementModule>().position.y - camera.GetRenderDistance() + y;

                if (tileX < 0 || tileY < 0 || tileX >= mapAreaSize || tileY >= mapAreaSize) continue;

                auto tileXI = CInt(tileX);
                auto tileYI = CInt(tileY);

                auto elev0 = 0.0f;
                auto elev1 = 0.0f;
                auto elev2 = 0.0f;
                auto elev3 = 0.0f;

                if (tileX >= 0 && tileY >= 0 && tileX < mapAreaSize && tileY < mapAreaSize)
                    elev0 = e.GetCurrMapArea().tiles[tileXI][tileYI].elevation / elevAmount - elevPlayer;

                if (tileX >= 0 && tileY - 1 >= 0 && tileX < mapAreaSize && tileY - 1 < mapAreaSize)
                    elev1 = e.GetCurrMapArea().tiles[tileXI][tileYI - 1].elevation / elevAmount - elevPlayer;
                else
                    elev1 = elev0;

                if (tileX + 1 >= 0 && tileY - 1 >= 0 && tileX + 1 < mapAreaSize && tileY - 1 < mapAreaSize)
                    elev2 = e.GetCurrMapArea().tiles[tileXI + 1][tileYI - 1].elevation / elevAmount - elevPlayer;
                else if (tileX + 1 < mapAreaSize)
                    elev2 = e.GetCurrMapArea().tiles[tileXI + 1][tileYI].elevation / elevAmount - elevPlayer;
                else if (tileY - 1 >= 0)
                    elev2 = e.GetCurrMapArea().tiles[tileXI][tileYI - 1].elevation / elevAmount - elevPlayer;
                else
                    elev2 = elev0;

                if (tileX + 1 >= 0 && tileY >= 0 && tileX + 1 < mapAreaSize && tileY < mapAreaSize)
                    elev3 = e.GetCurrMapArea().tiles[tileXI + 1][tileYI].elevation / elevAmount - elevPlayer;
                else
                    elev3 = elev0;

                auto slope = elev3 - elev0 + elev0 - elev1;

                auto r = 0.9f;
                auto g = 0.9f;
                auto b = 0.5f;

                if (slope < 0)
                {
                    r = 0.6f;
                    g = 0.6f;
                    b = 0.5f;
                }
                else if (slope > 0)
                {
                    r = 1.0f;
                    g = 1.0f;
                    b = 0.5f;
                }
                else if (slope == 0)
                {
                    r = 0.7f;
                    g = 0.7f;
                    b = 0.5f;
                }

                auto tileX0 = offset.x + x * e.cfg.tileSize;
                auto tileY0 = elev0;
                auto tileZ0 = offset.y + y * e.cfg.tileSize;
                auto tileX1 = offset.x + x * e.cfg.tileSize;
                auto tileY1 = elev1;
                auto tileZ1 = offset.y + y * e.cfg.tileSize - e.cfg.tileSize;
                auto tileX2 = offset.x + x * e.cfg.tileSize + e.cfg.tileSize;
                auto tileY2 = elev2;
                auto tileZ2 = offset.y + y * e.cfg.tileSize - e.cfg.tileSize;
                auto tileX3 = offset.x + x * e.cfg.tileSize + e.cfg.tileSize;
                auto tileY3 = elev3;
                auto tileZ3 = offset.y + y * e.cfg.tileSize;

                tileY0 = planetShaper.GetNewY(tileY0,
                    CFloat(tileXI),
                    CFloat(tileYI));
                tileY1 = planetShaper.GetNewY(tileY1,
                    CFloat(tileXI),
                    CFloat(tileYI) - 1);
                tileY2 = planetShaper.GetNewY(tileY2,
                    CFloat(tileXI) + 1,
                    CFloat(tileYI) - 1);
                tileY3 = planetShaper.GetNewY(tileY3,
                    CFloat(tileXI) + 1,
                    CFloat(tileYI));



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

        auto offsetX = -CFloat(2.0f * camera.GetRenderDistance() + 1.0f) / 2.0f * e.cfg.tileSize - subStepX * e.cfg.tileSize;
        auto offsetY = -CFloat(2.0f * camera.GetRenderDistance() - 1.0f) / 2.0f * e.cfg.tileSize - subStepY * e.cfg.tileSize;

        return {offsetX, offsetY};
    }

}  // namespace Forradia
