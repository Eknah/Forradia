// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include <string>
#include "GameWorldRenderer.h"
#include "../engine/Engine.h"
#include "implementation/functionality/actor/modules/ModuleMovementData.h"

namespace Forradia {

void cGameWorldRenderer::Render() {
  background.Render(camera.zoomAmount);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  //gluPerspective(45, 1.333, 0.5, 100);
  gluPerspective(engine.fov, 1.333, 0.5, 100);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  auto cameraX = 0.0f;
  auto cameraZ = -1.0f;
  auto angleRadians =
      atan2(cameraZ, cameraX) + camera.lookingAngle / 180.0f * M_PI;
  auto cameraDist = 1;
  auto zoom = camera.zoomAmount;


  auto zoomEx = std::max(zoom, 1.0f);
  glTranslatef(0.0f, -zoomEx - 1, - (zoomEx - 1.0f)* 4.0f);

  cameraX = static_cast<float>(cos(angleRadians)) * cameraDist;
  cameraZ = -static_cast<float>(sin(angleRadians)) * cameraDist;

  gluLookAt(cameraX-engine.tileSize/2,
            camera.cameraHeight*(zoomEx - 0.5f),
            cameraZ-engine.tileSize/2,
            -engine.tileSize/2,
            -1,
            -engine.tileSize/2,
            0,
            1,
            0);

  glEnable(GL_DEPTH_TEST);
  glDepthMask(GL_TRUE);
  glDepthFunc(GL_LEQUAL);
  glDepthRange(0.0f, 1000.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glPushMatrix();
  glTranslatef(0.0, -2 + 2.0, 0.0);

  RenderTilesAndObjects();
  RenderSunRaysAndActors();
  RenderRoof();

  glPopMatrix();
  glDisable(GL_DEPTH_TEST);
}

void cGameWorldRenderer::RenderTilesAndObjects() {
    auto mapAreaSize = engine.world->mapAreaSize;
    auto& movementData = engine.GetPlayer().GetModule<cModuleMovementData>();
    auto& tiles = engine.GetCurrentMapArea().tiles;

    auto elevAmount = 5.0f;
    auto playerXInt = static_cast<int>(movementData.position.x);
    auto playerYInt = static_cast<int>(movementData.position.y);
    auto elevPlayer0 =
        tiles[playerXInt][playerYInt].elevation /
        elevAmount;
    auto elevPlayer1 =
        tiles[playerXInt + 1][playerYInt].elevation /
        elevAmount;
    auto elevPlayer2 = tiles[playerXInt + 1][playerYInt + 1]
                           .elevation /
                       elevAmount;
    auto elevPlayer3 =
        tiles[playerXInt][playerYInt + 1].elevation /
        elevAmount;
    auto elevX = movementData.position.x - playerXInt;
    auto elevY = movementData.position.y - playerYInt;
    auto elevPlayer = (elevPlayer0 + (elevPlayer1 - elevPlayer0) * elevX +
                       elevPlayer3 + (elevPlayer2 - elevPlayer3) * elevX +
                       elevPlayer0 + (elevPlayer3 - elevPlayer0) * elevY +
                       elevPlayer1 + (elevPlayer2 - elevPlayer1) * elevY) /
                      4.0f;

    float subStepX = movementData.position.x -
            playerXInt;

    float subStepY = movementData.position.y -
            playerYInt;

    auto offsetX = -static_cast<float>(2.0f * camera.GetRenderDistance() + 1.0f)
            / 2.0f * engine.tileSize - subStepX * engine.tileSize;
    auto offsetY = -static_cast<float>(2.0f * camera.GetRenderDistance() - 1.0f)
            / 2.0f * engine.tileSize - subStepY * engine.tileSize;

    for (auto y = 0; y < 2 * camera.GetRenderDistance() + 1; y++) {
      for (auto x = 0; x < 2 * camera.GetRenderDistance() + 1; x++) {
        auto dx = x - camera.GetRenderDistance();
        auto dy = y - camera.GetRenderDistance();

        if (dx * dx + dy * dy >=
            camera.GetRenderDistance() * camera.GetRenderDistance())
          continue;

        auto tileX = movementData.position.x
                - camera.GetRenderDistance() + x;

        auto tileY = movementData.position.y
                - camera.GetRenderDistance() + y;

        if (tileX < 0 || tileY < 0 || tileX >= mapAreaSize ||
            tileY >= mapAreaSize)
          continue;

        auto tileXI = static_cast<int>(tileX);
        auto tileYI = static_cast<int>(tileY);

        auto groundTypeId =
            tiles[tileXI][tileYI].groundType;

        auto waterAnimIndex0 = 0;
        auto waterAnimIndex1 = 0;
        auto waterAnimIndex2 = 0;
        auto waterAnimIndex3 = 0;

        if (groundTypeId == groundTypeWaterId) {
          waterAnimIndex0 =
              ((Ticks() * 3 + (tileXI * tileYI) * 10) % 3600) / 1200;
          waterAnimIndex1 =
              ((Ticks() * 3 + (tileXI * (tileYI - 1)) * 10) % 3600) /
              1200;
          waterAnimIndex2 =
              ((Ticks() * 3 + ((tileXI + 1) * (tileYI - 1)) * 10) %
               3600) /
              1200;
          waterAnimIndex3 =
              ((Ticks() * 3 + ((tileXI + 1) * tileYI) * 10) % 3600) /
              1200;

          if (waterAnimIndex0 > 0)
            groundTypeId =
                groundTypeWaterAnimatedId[waterAnimIndex0];
        }

        auto elev0 = 0.0f;
        auto elev1 = 0.0f;
        auto elev2 = 0.0f;
        auto elev3 = 0.0f;

        auto waterWaveHeight0 = waterAnimIndex0 * engine.tileSize / 4.0f;
        auto waterWaveHeight1 = waterAnimIndex1 * engine.tileSize / 4.0f;
        auto waterWaveHeight2 = waterAnimIndex2 * engine.tileSize / 4.0f;
        auto waterWaveHeight3 = waterAnimIndex3 * engine.tileSize / 4.0f;

        if (tileX >= 0 && tileY >= 0 && tileX < mapAreaSize &&
            tileY < mapAreaSize)
          elev0 =
              tiles[tileXI][tileYI].elevation /
                  elevAmount -
              elevPlayer;

        if (tileX >= 0 && tileY - 1 >= 0 && tileX < mapAreaSize &&
            tileY - 1 < mapAreaSize)
          elev1 = tiles[tileXI][tileYI - 1]
                          .elevation /
                      elevAmount -
                  elevPlayer;
        else
          elev1 = elev0;

        if (tileX + 1 >= 0 && tileY - 1 >= 0 && tileX + 1 < mapAreaSize &&
            tileY - 1 < mapAreaSize)
          elev2 = tiles[tileXI + 1][tileYI - 1]
                          .elevation /
                      elevAmount -
                  elevPlayer;
        else if (tileX + 1 < mapAreaSize)
          elev2 = tiles[tileXI + 1][tileYI]
                          .elevation /
                      elevAmount -
                  elevPlayer;
        else if (tileY - 1 >= 0)
          elev2 = tiles[tileXI][tileYI - 1]
                          .elevation /
                      elevAmount -
                  elevPlayer;
        else
          elev2 = elev0;

        if (tileX + 1 >= 0 && tileY >= 0 && tileX + 1 < mapAreaSize &&
            tileY < mapAreaSize)
          elev3 = tiles[tileXI + 1][tileYI]
                          .elevation /
                      elevAmount -
                  elevPlayer;
        else
          elev3 = elev0;

        auto slope = elev3 - elev0 + elev0 - elev1;

        auto r = 0.9f;
        auto g = 0.9f;
        auto b = 0.5f;

        if (slope < 0) {
          r = 0.6f;
          g = 0.6f;
          b = 0.5f;
        } else if (slope > 0) {
          r = 1.0f;
          g = 1.0f;
          b = 0.5f;
        } else if (slope == 0) {
            r = 0.7f;
            g = 0.7f;
            b = 0.5f;
        }

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,
                      engine.imageLoader.images.at(groundTypeId));

        auto tileX0 = offsetX + x * engine.tileSize;
        auto tileY0 = elev0;
        auto tileZ0 = offsetY + y * engine.tileSize;
        auto tileX1 = offsetX + x * engine.tileSize;
        auto tileY1 = elev1;
        auto tileZ1 = offsetY + y * engine.tileSize - engine.tileSize;
        auto tileX2 = offsetX + x * engine.tileSize + engine.tileSize;
        auto tileY2 = elev2;
        auto tileZ2 = offsetY + y * engine.tileSize - engine.tileSize;
        auto tileX3 = offsetX + x * engine.tileSize + engine.tileSize;
        auto tileY3 = elev3;
        auto tileZ3 = offsetY + y * engine.tileSize;

        tileY0 = planetShaper.GetNewY(tileY0,
                                             static_cast<float>(tileXI),
                                             static_cast<float>(tileYI));
        tileY1 = planetShaper.GetNewY(tileY1,
                                             static_cast<float>(tileXI),
                                             static_cast<float>(tileYI) - 1);
        tileY2 = planetShaper.GetNewY(tileY2,
                                             static_cast<float>(tileXI) + 1,
                                             static_cast<float>(tileYI) - 1);
        tileY3 = planetShaper.GetNewY(tileY3,
                                             static_cast<float>(tileXI) + 1,
                                             static_cast<float>(tileYI));

        glBegin(GL_QUADS);

        //glColor3f(R, G, B);
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

        if (waterAnimIndex0 > 0) {
          glBegin(GL_QUADS);

            glColor3f(r, g, b);
//          glColor3f(R, G, B);

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




        auto hoveredX = camera.GetHoveredTile().x;
        auto hoveredY = camera.GetHoveredTile().y;

        if (hoveredX == tileXI && hoveredY == tileYI &&
            engine.customCursor.cursorType != eCursorTypes::Hidden) {
          glBindTexture(GL_TEXTURE_2D,
                        engine.imageLoader.images.at(GetId("TileHovering")));

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

        for (auto &Object :
             tiles[tileXI][tileYI].objects) {

            auto dropShadow = true;

            if (engine.objectsContent.objectDescriptions.count(Object->objectType))
            if (engine.objectsContent.objectDescriptions.at(Object->objectType).flags & ObjectNoShadow)
                dropShadow = false;

                if (dropShadow) {
glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,
                          engine.imageLoader.images.at(GetId("TileShadow")));

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

}

                glDisable(GL_TEXTURE_2D);




          auto tileObject = Object->objectType;
          auto opacity = 1.0f;

          if (engine.objectsContent.objectDescriptions.count(tileObject))
              opacity = engine.objectsContent.objectDescriptions.at(tileObject).opacity;

          if (tileObject != 0)
            engine.DrawModel(tileObject, tileX0 + engine.tileSize / 2,
                             (tileY0 + tileY1 + tileY2 + tileY3) / 4.0f,
                             tileZ0 - engine.tileSize / 2, Object->rotation,
                             Object->scaling, opacity);
        }
      }
    }
}

void cGameWorldRenderer::RenderSunRaysAndActors() {
    auto mapAreaSize = engine.world->mapAreaSize;
    auto elevAmount = 5.0f;
    auto playerXInt = static_cast<int>(engine.GetPlayer().GetModule<cModuleMovementData>().position.x);
    auto playerYInt = static_cast<int>(engine.GetPlayer().GetModule<cModuleMovementData>().position.y);
    auto elevPlayer0 =
        engine.GetCurrentMapArea().tiles[playerXInt][playerYInt].elevation /
        elevAmount;
    auto elevPlayer1 =
        engine.GetCurrentMapArea().tiles[playerXInt + 1][playerYInt].elevation /
        elevAmount;
    auto elevPlayer2 = engine.GetCurrentMapArea()
                           .tiles[playerXInt + 1][playerYInt + 1]
                           .elevation /
                       elevAmount;
    auto elevPlayer3 =
        engine.GetCurrentMapArea().tiles[playerXInt][playerYInt + 1].elevation /
        elevAmount;
    auto elevX = engine.GetPlayer().GetModule<cModuleMovementData>().position.x - playerXInt;
    auto elevY = engine.GetPlayer().GetModule<cModuleMovementData>().position.y - playerYInt;
    auto elevPlayer = (elevPlayer0 + (elevPlayer1 - elevPlayer0) * elevX +
                       elevPlayer3 + (elevPlayer2 - elevPlayer3) * elevX +
                       elevPlayer0 + (elevPlayer3 - elevPlayer0) * elevY +
                       elevPlayer1 + (elevPlayer2 - elevPlayer1) * elevY) /
                      4.0f;

    float subStepX = engine.GetPlayer().GetModule<cModuleMovementData>().position.x -
            static_cast<int>(engine.GetPlayer().GetModule<cModuleMovementData>().position.x);

    float subStepY = engine.GetPlayer().GetModule<cModuleMovementData>().position.y -
            static_cast<int>(engine.GetPlayer().GetModule<cModuleMovementData>().position.y);

    auto offsetX = -static_cast<float>(2.0f * camera.GetRenderDistance() + 1.0f)
            / 2.0f * engine.tileSize - subStepX * engine.tileSize;
    auto offsetY = -static_cast<float>(2.0f * camera.GetRenderDistance() - 1.0f)
            / 2.0f * engine.tileSize - subStepY * engine.tileSize;

    for (auto y = 0; y < 2 * camera.GetRenderDistance() + 1; y++) {
      for (auto x = 0; x < 2 * camera.GetRenderDistance() + 1; x++) {
          auto dx = x - camera.GetRenderDistance();
          auto dy = y - camera.GetRenderDistance();

          if (dx * dx + dy * dy >=
              camera.GetRenderDistance() * camera.GetRenderDistance())
            continue;

          auto tileX = engine.GetPlayer().GetModule<cModuleMovementData>().position.x
                  - camera.GetRenderDistance() + x;

          auto tileY = engine.GetPlayer().GetModule<cModuleMovementData>().position.y
                  - camera.GetRenderDistance() + y;

          if (tileX < 0 || tileY < 0 || tileX >= mapAreaSize ||
              tileY >= mapAreaSize)
            continue;

          auto tileXI = static_cast<int>(tileX);
          auto tileYI = static_cast<int>(tileY);

          auto elev0 = 0.0f;
          auto elev1 = 0.0f;
          auto elev2 = 0.0f;
          auto elev3 = 0.0f;

          if (tileX >= 0 && tileY >= 0 && tileX < mapAreaSize &&
              tileY < mapAreaSize)
            elev0 =
                engine.GetCurrentMapArea().tiles[tileXI][tileYI].elevation /
                    elevAmount -
                elevPlayer;

          if (tileX >= 0 && tileY - 1 >= 0 && tileX < mapAreaSize &&
              tileY - 1 < mapAreaSize)
            elev1 = engine.GetCurrentMapArea()
                            .tiles[tileXI][tileYI - 1]
                            .elevation /
                        elevAmount -
                    elevPlayer;
          else
            elev1 = elev0;

          if (tileX + 1 >= 0 && tileY - 1 >= 0 && tileX + 1 < mapAreaSize &&
              tileY - 1 < mapAreaSize)
            elev2 = engine.GetCurrentMapArea()
                            .tiles[tileXI + 1][tileYI - 1]
                            .elevation /
                        elevAmount -
                    elevPlayer;
          else if (tileX + 1 < mapAreaSize)
            elev2 = engine.GetCurrentMapArea()
                            .tiles[tileXI + 1][tileYI]
                            .elevation /
                        elevAmount -
                    elevPlayer;
          else if (tileY - 1 >= 0)
            elev2 = engine.GetCurrentMapArea()
                            .tiles[tileXI][tileYI - 1]
                            .elevation /
                        elevAmount -
                    elevPlayer;
          else
            elev2 = elev0;

          if (tileX + 1 >= 0 && tileY >= 0 && tileX + 1 < mapAreaSize &&
              tileY < mapAreaSize)
            elev3 = engine.GetCurrentMapArea()
                            .tiles[tileXI + 1][tileYI]
                            .elevation /
                        elevAmount -
                    elevPlayer;
          else
            elev3 = elev0;

          auto tileX0 = offsetX + x * engine.tileSize;
          auto tileY0 = elev0;
          auto tileZ0 = offsetY + y * engine.tileSize;
          auto tileX1 = offsetX + x * engine.tileSize;
          auto tileY1 = elev1;
          auto tileZ1 = offsetY + y * engine.tileSize - engine.tileSize;
          auto tileX2 = offsetX + x * engine.tileSize + engine.tileSize;
          auto tileY2 = elev2;
          auto tileZ2 = offsetY + y * engine.tileSize - engine.tileSize;
          auto tileX3 = offsetX + x * engine.tileSize + engine.tileSize;
          auto tileY3 = elev3;
          auto tileZ3 = offsetY + y * engine.tileSize;

          tileY0 = planetShaper.GetNewY(tileY0,
                                               static_cast<float>(tileXI),
                                               static_cast<float>(tileYI));
          tileY1 = planetShaper.GetNewY(tileY1,
                                               static_cast<float>(tileXI),
                                               static_cast<float>(tileYI) - 1);
          tileY2 = planetShaper.GetNewY(tileY2,
                                               static_cast<float>(tileXI) + 1,
                                               static_cast<float>(tileYI) - 1);
          tileY3 = planetShaper.GetNewY(tileY3,
                                               static_cast<float>(tileXI) + 1,
                                               static_cast<float>(tileYI));
        if ((tileXI + tileYI) % 16 == 0) {
          auto sunx = -500.0f;
          auto suny = 500.0f;
          auto sunz = -500.0f;

          auto alpha = ((Ticks() + tileXI*tileYI) % 1000)/1000.0f;
          if (alpha >= 0.5f)
              alpha = 0.5f - (alpha - 0.5f);

          alpha /= 6.0f;

                      glBegin(GL_LINE_STRIP);
                      glColor4f(1.0f, 1.0f, 0.0f, alpha);
                      glVertex3f(tileX0, tileY0, tileZ0);
                      glVertex3f(sunx, suny, sunz);
                      glEnd();
        }

        if (engine.GetCurrentMapArea().tiles[tileXI][tileYI].actor !=
            nullptr) {
          auto subxpos = (engine.GetCurrentMapArea()
                              .tiles[tileXI][tileYI]
                              .actor->GetModule<cModuleMovementData>().position.x -
                          static_cast<int>(engine.GetCurrentMapArea()
                                  .tiles[tileXI][tileYI]
                                  .actor->GetModule<cModuleMovementData>().position.x)) *
                         engine.tileSize;
          auto subypos = (engine.GetCurrentMapArea()
                              .tiles[tileXI][tileYI]
                              .actor->GetModule<cModuleMovementData>().position.y -
                          static_cast<int>(engine.GetCurrentMapArea()
                                  .tiles[tileXI][tileYI]
                                  .actor->GetModule<cModuleMovementData>().position.y)) *
                         engine.tileSize;

          glEnable(GL_TEXTURE_2D);

          glBindTexture(GL_TEXTURE_2D,
                        engine.imageLoader.images.at(GetId("TileShadow")));

          glBegin(GL_QUADS);

          glColor3f(1, 1, 1);

          glTexCoord2f(0, 0);
          glVertex3f(tileX0 - engine.tileSize/2 + subxpos,
                     tileY0 + 0.05f,
                     tileZ0 - engine.tileSize/2 + subypos);
          glTexCoord2f(1, 0);
          glVertex3f(tileX1 - engine.tileSize/2 + subxpos,
                     tileY1 + 0.05f,
                     tileZ1 - engine.tileSize/2 + subypos);
          glTexCoord2f(1, 1);
          glVertex3f(tileX2 - engine.tileSize/2 + subxpos,
                     tileY2 + 0.05f,
                     tileZ2 - engine.tileSize/2 + subypos);
          glTexCoord2f(0, 1);
          glVertex3f(tileX3 - engine.tileSize/2 + subxpos,
                     tileY3 + 0.05f,
                     tileZ3 - engine.tileSize/2 + subypos);

          glEnd();

          glDisable(GL_TEXTURE_2D);

          auto modelYPos0 = tileY1 + (tileY2 - tileY1)*subxpos/engine.tileSize;
          auto modelYPos1 = tileY0 + (tileY3 - tileY0)*subxpos/engine.tileSize;
          auto modelYPos = modelYPos0
                  + (modelYPos1 - modelYPos0)*subypos/engine.tileSize;

          engine.DrawModel(engine.GetCurrentMapArea()
                           .tiles[tileXI][tileYI]
                           .actor->GetAnimatedModelId(), tileX0 + subxpos,
                           modelYPos  + engine.GetCurrentMapArea()
                                                      .tiles[tileXI][tileYI]
                                                      .actor->GetModule<cModuleMovementData>().positionZ,
                           tileZ0 - engine.tileSize + subypos,
                           *engine.GetCurrentMapArea()
                               .tiles[tileXI][tileYI]
                               .actor->GetModule<cModuleMovementData>().facingAngle);
        }
      }
    }
}









void cGameWorldRenderer::RenderRoof() {
    auto mapAreaSize = engine.world->mapAreaSize;

    auto elevAmount = 5.0f;
    auto playerXInt = static_cast<int>(engine.GetPlayer().GetModule<cModuleMovementData>().position.x);
    auto playerYInt = static_cast<int>(engine.GetPlayer().GetModule<cModuleMovementData>().position.y);
    auto elevPlayer0 =
        engine.GetCurrentMapArea().tiles[playerXInt][playerYInt].elevation /
        elevAmount;
    auto elevPlayer1 =
        engine.GetCurrentMapArea().tiles[playerXInt + 1][playerYInt].elevation /
        elevAmount;
    auto elevPlayer2 = engine.GetCurrentMapArea()
                           .tiles[playerXInt + 1][playerYInt + 1]
                           .elevation /
                       elevAmount;
    auto elevPlayer3 =
        engine.GetCurrentMapArea().tiles[playerXInt][playerYInt + 1].elevation /
        elevAmount;
    auto elevX = engine.GetPlayer().GetModule<cModuleMovementData>().position.x - playerXInt;
    auto elevY = engine.GetPlayer().GetModule<cModuleMovementData>().position.y - playerYInt;
    auto elevPlayer = (elevPlayer0 + (elevPlayer1 - elevPlayer0) * elevX +
                       elevPlayer3 + (elevPlayer2 - elevPlayer3) * elevX +
                       elevPlayer0 + (elevPlayer3 - elevPlayer0) * elevY +
                       elevPlayer1 + (elevPlayer2 - elevPlayer1) * elevY) /
                      4.0f;

    float subStepX = engine.GetPlayer().GetModule<cModuleMovementData>().position.x -
            static_cast<int>(engine.GetPlayer().GetModule<cModuleMovementData>().position.x);

    float subStepY = engine.GetPlayer().GetModule<cModuleMovementData>().position.y -
            static_cast<int>(engine.GetPlayer().GetModule<cModuleMovementData>().position.y);

    auto offsetX = -static_cast<float>(2.0f * camera.GetRenderDistance() + 1.0f)
            / 2.0f * engine.tileSize - subStepX * engine.tileSize;
    auto offsetY = -static_cast<float>(2.0f * camera.GetRenderDistance() - 1.0f)
            / 2.0f * engine.tileSize - subStepY * engine.tileSize;

    for (auto y = 0; y < 2 * camera.GetRenderDistance() + 1; y++) {
      for (auto x = 0; x < 2 * camera.GetRenderDistance() + 1; x++) {
        auto dx = x - camera.GetRenderDistance();
        auto dy = y - camera.GetRenderDistance();

        if (dx * dx + dy * dy >=
            camera.GetRenderDistance() * camera.GetRenderDistance())
          continue;

        auto tileX = engine.GetPlayer().GetModule<cModuleMovementData>().position.x
                - camera.GetRenderDistance() + x;

        auto tileY = engine.GetPlayer().GetModule<cModuleMovementData>().position.y
                - camera.GetRenderDistance() + y;

        if (tileX < 0 || tileY < 0 || tileX >= mapAreaSize ||
            tileY >= mapAreaSize)
          continue;

        auto tileXI = static_cast<int>(tileX);
        auto tileYI = static_cast<int>(tileY);

        auto elev0 = 0.0f;
        auto elev1 = 0.0f;
        auto elev2 = 0.0f;
        auto elev3 = 0.0f;

        if (tileX >= 0 && tileY >= 0 && tileX < mapAreaSize &&
            tileY < mapAreaSize)
          elev0 =
              engine.GetCurrentMapArea().tiles[tileXI][tileYI].elevation /
                  elevAmount -
              elevPlayer;

        if (tileX >= 0 && tileY - 1 >= 0 && tileX < mapAreaSize &&
            tileY - 1 < mapAreaSize)
          elev1 = engine.GetCurrentMapArea()
                          .tiles[tileXI][tileYI - 1]
                          .elevation /
                      elevAmount -
                  elevPlayer;
        else
          elev1 = elev0;

        if (tileX + 1 >= 0 && tileY - 1 >= 0 && tileX + 1 < mapAreaSize &&
            tileY - 1 < mapAreaSize)
          elev2 = engine.GetCurrentMapArea()
                          .tiles[tileXI + 1][tileYI - 1]
                          .elevation /
                      elevAmount -
                  elevPlayer;
        else if (tileX + 1 < mapAreaSize)
          elev2 = engine.GetCurrentMapArea()
                          .tiles[tileXI + 1][tileYI]
                          .elevation /
                      elevAmount -
                  elevPlayer;
        else if (tileY - 1 >= 0)
          elev2 = engine.GetCurrentMapArea()
                          .tiles[tileXI][tileYI - 1]
                          .elevation /
                      elevAmount -
                  elevPlayer;
        else
          elev2 = elev0;

        if (tileX + 1 >= 0 && tileY >= 0 && tileX + 1 < mapAreaSize &&
            tileY < mapAreaSize)
          elev3 = engine.GetCurrentMapArea()
                          .tiles[tileXI + 1][tileYI]
                          .elevation /
                      elevAmount -
                  elevPlayer;
        else
          elev3 = elev0;

        auto slope = elev3 - elev0 + elev0 - elev1;

        auto r = 0.9f;
        auto g = 0.9f;
        auto b = 0.5f;

        if (slope < 0) {
          r = 0.6f;
          g = 0.6f;
          b = 0.5f;
        } else if (slope > 0) {
          r = 1.0f;
          g = 1.0f;
          b = 0.5f;
        } else if (slope == 0) {
            r = 0.7f;
            g = 0.7f;
            b = 0.5f;
        }

        auto tileX0 = offsetX + x * engine.tileSize;
        auto tileY0 = elev0;
        auto tileZ0 = offsetY + y * engine.tileSize;
        auto tileX1 = offsetX + x * engine.tileSize;
        auto tileY1 = elev1;
        auto tileZ1 = offsetY + y * engine.tileSize - engine.tileSize;
        auto tileX2 = offsetX + x * engine.tileSize + engine.tileSize;
        auto tileY2 = elev2;
        auto tileZ2 = offsetY + y * engine.tileSize - engine.tileSize;
        auto tileX3 = offsetX + x * engine.tileSize + engine.tileSize;
        auto tileY3 = elev3;
        auto tileZ3 = offsetY + y * engine.tileSize;

        tileY0 = planetShaper.GetNewY(tileY0,
                                             static_cast<float>(tileXI),
                                             static_cast<float>(tileYI));
        tileY1 = planetShaper.GetNewY(tileY1,
                                             static_cast<float>(tileXI),
                                             static_cast<float>(tileYI) - 1);
        tileY2 = planetShaper.GetNewY(tileY2,
                                             static_cast<float>(tileXI) + 1,
                                             static_cast<float>(tileYI) - 1);
        tileY3 = planetShaper.GetNewY(tileY3,
                                             static_cast<float>(tileXI) + 1,
                                             static_cast<float>(tileYI));



        glDisable(GL_TEXTURE_2D);


if (engine.GetCurrentMapArea()
        .tiles[tileXI][tileYI]
        .roof != nullptr) {

    auto& roof = engine.GetCurrentMapArea()
            .tiles[tileXI][tileYI]
            .roof;


  auto roofObject = roof->objectType;
  auto opacity = 1.0f;

  if (engine.objectsContent.objectDescriptions.count(roofObject))
      opacity = engine.objectsContent.objectDescriptions.at(roofObject).opacity;

  engine.DrawModel(roofObject, tileX0 + engine.tileSize / 2,
                   (tileY0 + tileY1 + tileY2 + tileY3) / 4.0f,
                   tileZ0 - engine.tileSize / 2, roof->rotation,
                   roof->scaling, opacity);

}

      }
    }
}









}  // namespace Forradia
