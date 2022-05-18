// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include <string>
#include "WorldRenderer.h"
#include "Engine.h"
#include "CoreMovmModule.h"
#include "ColorF.h"

namespace Forradia
{

    void WorldRenderer::Render()
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

        auto width = e.cfg.tileSize * 150;
        auto height = e.cfg.tileSize * 50;
        auto ybottom = -e.cfg.tileSize*25;

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, e.imageLoader.images.at(GetId("SkyBackground")));

        glBegin(GL_QUADS);

        glColor3f(1.0f, 1.0f, 1.0f);

        glTexCoord2f(0, 1);
        glVertex3f(-width / 2, ybottom, -width / 2);
        glTexCoord2f(1, 1);
        glVertex3f(width / 2, ybottom, -width / 2);
        glTexCoord2f(1, 0);
        glVertex3f(width / 2, ybottom + height, -width / 2);
        glTexCoord2f(0, 0);
        glVertex3f(-width / 2, ybottom + height, -width / 2);

        glTexCoord2f(0, 1);
        glVertex3f(width / 2, ybottom, -width / 2);
        glTexCoord2f(1, 1);
        glVertex3f(width / 2, ybottom, width / 2);
        glTexCoord2f(1, 0);
        glVertex3f(width / 2, ybottom + height, width / 2);
        glTexCoord2f(0, 0);
        glVertex3f(width / 2, ybottom + height, -width / 2);

        glTexCoord2f(0, 1);
        glVertex3f(width / 2, ybottom, width / 2);
        glTexCoord2f(1, 1);
        glVertex3f(-width / 2, ybottom, width / 2);
        glTexCoord2f(1, 0);
        glVertex3f(-width / 2, ybottom + height, width / 2);
        glTexCoord2f(0, 0);
        glVertex3f(width / 2, ybottom + height, width / 2);

        glTexCoord2f(0, 1);
        glVertex3f(-width / 2, ybottom, width / 2);
        glTexCoord2f(1, 1);
        glVertex3f(-width / 2, ybottom, -width / 2);
        glTexCoord2f(1, 0);
        glVertex3f(-width / 2, ybottom + height, -width / 2);
        glTexCoord2f(0, 0);
        glVertex3f(-width / 2, ybottom + height, width / 2);

        glEnd();

        DoRender();

		glLoadIdentity();

    }

    void WorldRenderer::DoRender()
    {
        auto mapAreaSz = e.world->mapAreaSize;
        auto& movmData = e.GetPlayer().GetModule<CoreMovmModule>();
        auto& tiles = e.GetCurrMapArea().tiles;
        auto offset = CalcOffset();
        List<Point2> roofTiles;

        for (auto y = 0; y < 2 * cam.GetRenderDist() + 1; y++)
        {
            for (auto x = 0; x < 2 * cam.GetRenderDist() + 1; x++)
            {
                auto dx = x - cam.GetRenderDist();
                auto dy = y - cam.GetRenderDist();

                if (dx * dx + dy * dy >= cam.GetRenderDist() * cam.GetRenderDist()) continue;

                auto tilex = movmData.position.x - cam.GetRenderDist() + x;
                auto tiley = movmData.position.y - cam.GetRenderDist() + y;

                if (tilex < 0 || tiley < 0 || tilex >= mapAreaSz || tiley >= mapAreaSz) continue;

                auto tilexI = CInt(tilex);
                auto tileyI = CInt(tiley);


                auto angleBehind = std::atan2(-1.0f, 0.0f);
                auto angleBehindActual = angleBehind + cam.lookingAngle*M_PI/180.0f - M_PI/2.0f;

                if (angleBehindActual >= M_PI)
                    angleBehindActual -= M_PI*2;

                if (angleBehindActual <= -M_PI*2)
                    angleBehindActual += M_PI*2;

                auto behindX = movmData.position.x - std::sin(angleBehindActual)*cam.zoomAmount*2;
                auto behindY = movmData.position.y - std::cos(angleBehindActual)*cam.zoomAmount*2;

                auto dxTile = tilexI - behindX;
                auto dyTile = tileyI - behindY;

                auto angle = std::atan2(dyTile, dxTile);
                auto angleActual = angle + cam.lookingAngle*M_PI/180.0f - M_PI/2.0f;

                if (angleActual >= M_PI)
                    angleActual -= M_PI*2;

                if (angleActual <= -M_PI*2)
                    angleActual += M_PI*2;

                if (std::abs(angleActual) < M_PI/2.0f) continue;

//                auto distSqrd = dxplr*dxplr + dyplr*dyplr;

//                if (std::abs(angle + cam.lookingAngle*M_PI/180.0f - M_PI/2.0f) < M_PI/3.0f && distSqrd > 30*cam.zoomAmount) continue;

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

                auto offsetAmount = 4.0f;

                tileX0 += tiles[tilexI][tileyI].vertexOffset.x*e.cfg.tileSize* offsetAmount;
                tileZ0 += tiles[tilexI][tileyI].vertexOffset.y * e.cfg.tileSize * offsetAmount;

                if (tileyI > 0)
                {
                    tileX1 += tiles[tilexI][tileyI - 1].vertexOffset.x * e.cfg.tileSize * offsetAmount;
                    tileZ1 += tiles[tilexI][tileyI - 1].vertexOffset.y * e.cfg.tileSize * offsetAmount;
                }

                if (tilexI < e.GetCurrMapArea().size - 1 && tileyI > 0)
                {
                    tileX2 += tiles[tilexI + 1][tileyI - 1].vertexOffset.x * e.cfg.tileSize * offsetAmount;
                    tileZ2 += tiles[tilexI + 1][tileyI - 1].vertexOffset.y * e.cfg.tileSize * offsetAmount;
                }

                if (tilexI < e.GetCurrMapArea().size - 1)
                {
                    tileX3 += tiles[tilexI + 1][tileyI].vertexOffset.x * e.cfg.tileSize * offsetAmount;
                    tileZ3 += tiles[tilexI + 1][tileyI].vertexOffset.y * e.cfg.tileSize * offsetAmount;
                }

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

                if (hoveredx == tilexI && hoveredy == tileyI && e.cursor.type != CursorTypes::Hidden)
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

                    if (e.objectsContent.objDescribers.count(Object->objectType))
                        if (e.objectsContent.objDescribers.at(Object->objectType).flags & FlagNoShadow)
                            dropShadow = false;

                    if (dropShadow)
                    {
                        glDisable(GL_TEXTURE_2D);
                        e.DrawModel
                        (
                            "Shadow",
                            tileX0 + e.cfg.tileSize / 2,
                            (tileY0 + tileY1 + tileY2 + tileY3) / 4.0f,
                            tileZ0 - e.cfg.tileSize / 2,
                            0,
                            0.7f,
                            1.0f
                        );
                    }

                    glDisable(GL_TEXTURE_2D);

                    auto tileObject = Object->objectType;
                    auto opacity = 1.0f;

                    if (e.objectsContent.objDescribers.count(tileObject))
                        opacity = e.objectsContent.objDescribers.at(tileObject).opacity;

                    if (tileObject != 0)
                    {
                        e.DrawModel
                        (
                            tileObject,
                            tileX0 + e.cfg.tileSize / 2,
                            (tileY0 + tileY1 + tileY2 + tileY3) / 4.0f,
                            tileZ0 - e.cfg.tileSize / 2,
                            Object->rotation,
                            Object->scaling,
                            opacity
                        );
                    }
                }


                if (e.GetCurrMapArea().tiles[tilexI][tileyI].actor != nullptr)
                {
                    auto subxpos = (e.GetCurrMapArea().tiles[tilexI][tileyI].actor->GetModule<CoreMovmModule>().position.x - CInt(e.GetCurrMapArea().tiles[tilexI][tileyI].actor->GetModule<CoreMovmModule>().position.x)) * e.cfg.tileSize;
                    auto subypos = (e.GetCurrMapArea().tiles[tilexI][tileyI].actor->GetModule<CoreMovmModule>().position.y - CInt(e.GetCurrMapArea().tiles[tilexI][tileyI].actor->GetModule<CoreMovmModule>().position.y)) * e.cfg.tileSize;

                    glDisable(GL_TEXTURE_2D);

                    auto modelYPos0 = tileY1 + (tileY2 - tileY1) * subxpos / e.cfg.tileSize;
                    auto modelYPos1 = tileY0 + (tileY3 - tileY0) * subxpos / e.cfg.tileSize;
                    auto modelYPos = modelYPos0 + (modelYPos1 - modelYPos0) * subypos / e.cfg.tileSize;

                    e.DrawModel
                    (
                        "Shadow",
                        tileX0 + subxpos,
                        modelYPos,
                        tileZ0 - e.cfg.tileSize + subypos,
                        0,
                        0.3f,
                        1.0f
                    );

                    e.DrawModel
                    (
                        e.GetCurrMapArea().tiles[tilexI][tileyI].actor->GetAnimatedModelId(),
                        tileX0 + subxpos,
                        modelYPos + e.GetCurrMapArea().tiles[tilexI][tileyI].actor->GetModule<CoreMovmModule>().positionZ,
                        tileZ0 - e.cfg.tileSize + subypos,
                        *e.GetCurrMapArea().tiles[tilexI][tileyI].actor->GetModule<CoreMovmModule>().facingAngle,
                        0.5f
                    );
                }

                if (e.GetCurrMapArea().tiles[tilexI][tileyI].roof != nullptr)
                    roofTiles.push_back({x, y});

            }
        }

        for (auto& tile : roofTiles)
            RenderRoof(tile.x, tile.y);

    }




    void WorldRenderer::RenderRoof(int x, int y)
    {

        auto mapAreaSz = e.world->mapAreaSize;
        auto offset = CalcOffset();

        auto dx = x - cam.GetRenderDist();
        auto dy = y - cam.GetRenderDist();

        if (dx * dx + dy * dy >= cam.GetRenderDist() * cam.GetRenderDist()) return;

        auto tileX = e.GetPlayer().GetModule<CoreMovmModule>().position.x - cam.GetRenderDist() + x;
        auto tileY = e.GetPlayer().GetModule<CoreMovmModule>().position.y - cam.GetRenderDist() + y;

        if (tileX < 0 || tileY < 0 || tileX >= mapAreaSz || tileY >= mapAreaSz) return;

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

            if (e.objectsContent.objDescribers.count(roofObject))
                opacity = e.objectsContent.objDescribers.at(roofObject).opacity;

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

    float WorldRenderer::CalcPlayerElev()
    {
        auto& movmData = e.GetPlayer().GetModule<CoreMovmModule>();
        auto& tiles = e.GetCurrMapArea().tiles;

        auto playerXInt = CInt(movmData.position.x);
        auto playerYInt = CInt(movmData.position.y);
        auto elevPlayer0 = tiles[playerXInt][playerYInt].elevation / elevAmount;
        auto elevPlayer1 = tiles[playerXInt + 1][playerYInt].elevation / elevAmount;
        auto elevPlayer2 = tiles[playerXInt + 1][playerYInt + 1].elevation / elevAmount;
        auto elevPlayer3 = tiles[playerXInt][playerYInt + 1].elevation / elevAmount;
        auto elevX = movmData.position.x - playerXInt;
        auto elevY = movmData.position.y - playerYInt;

        auto elevPlayer =
            (elevPlayer0 + (elevPlayer1 - elevPlayer0) * elevX +
            elevPlayer3 + (elevPlayer2 - elevPlayer3) * elevX +
            elevPlayer0 + (elevPlayer3 - elevPlayer0) * elevY +
            elevPlayer1 + (elevPlayer2 - elevPlayer1) * elevY) /
            4.0f;

            return elevPlayer;
    }

    Point2F WorldRenderer::CalcOffset()
    {
        auto& movmData = e.GetPlayer().GetModule<CoreMovmModule>();

        auto playerxI = CInt(movmData.position.x);
        auto playeryI = CInt(movmData.position.y);

        float substepx = movmData.position.x - playerxI;
        float substepy = movmData.position.y - playeryI;

        auto offsetx = -CFloat(2.0f * cam.GetRenderDist() + 1.0f) / 2.0f * e.cfg.tileSize - substepx * e.cfg.tileSize;
        auto offsety = -CFloat(2.0f * cam.GetRenderDist() - 1.0f) / 2.0f * e.cfg.tileSize - substepy * e.cfg.tileSize;

        return {offsetx, offsety};
    }

    std::array<float, 4> WorldRenderer::GetElevValues(int xI, int yI)
    {
        auto mapAreaSz = e.world->mapAreaSize;
        auto& tiles = e.GetCurrMapArea().tiles;
        auto elevPlayer = CalcPlayerElev();

        auto elev0 = 0.0f;
        auto elev1 = 0.0f;
        auto elev2 = 0.0f;
        auto elev3 = 0.0f;

        if (xI >= 0 && yI >= 0 && xI < mapAreaSz && yI < mapAreaSz)
            elev0 = tiles[xI][yI].elevation / elevAmount - elevPlayer;

        if (xI >= 0 && yI - 1 >= 0 && xI < mapAreaSz && yI - 1 < mapAreaSz)
            elev1 = tiles[xI][yI - 1].elevation / elevAmount - elevPlayer;
        else
            elev1 = elev0;

        if (xI + 1 >= 0 && yI - 1 >= 0 && xI + 1 < mapAreaSz && yI - 1 < mapAreaSz)
            elev2 = tiles[xI + 1][yI - 1].elevation / elevAmount - elevPlayer;
        else if (xI + 1 < mapAreaSz)
            elev2 = tiles[xI + 1][yI].elevation / elevAmount - elevPlayer;
        else if (yI - 1 >= 0)
            elev2 = tiles[xI][yI - 1].elevation / elevAmount - elevPlayer;
        else
            elev2 = elev0;

        if (xI + 1 >= 0 && yI >= 0 && xI + 1 < mapAreaSz && yI < mapAreaSz)
            elev3 = tiles[xI + 1][yI].elevation / elevAmount - elevPlayer;
        else
            elev3 = elev0;

        return { elev0, elev1, elev2, elev3 };

    }

}