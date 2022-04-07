// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include <string>
#include "cGameWorldRenderer.h"
#include "../engine/cEngine.h"
#include "implementation/functionality/actor/modules/cModuleMovementData.h"

namespace Forradia {

void cGameWorldRenderer::Render() {
  background.Render(camera.zoomAmount);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  //gluPerspective(45, 1.333, 0.5, 100);
  gluPerspective(engine.fov, 1.333, 0.5, 100);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  auto CameraX = 0.0f;
  auto CameraZ = -1.0f;
  auto AngleRadians =
      atan2(CameraZ, CameraX) + camera.lookingAngle / 180.0f * M_PI;
  auto CameraDist = 1;
  auto Zoom = camera.zoomAmount;


  auto ZoomEx = std::max(Zoom, 1.0f);
  glTranslatef(0.0f, -ZoomEx - 1, - (ZoomEx - 1.0f)* 4.0f);

  CameraX = static_cast<float>(cos(AngleRadians)) * CameraDist;
  CameraZ = -static_cast<float>(sin(AngleRadians)) * CameraDist;

  gluLookAt(CameraX-engine.tileSize/2,
            camera.cameraHeight*(ZoomEx - 0.5f),
            CameraZ-engine.tileSize/2,
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
    auto MapAreaSize = engine.world->mapAreaSize;
    auto& movementData = engine.GetPlayer().GetModule<cModuleMovementData>();
    auto& tiles = engine.GetCurrentMapArea().tiles;

    auto ElevAmount = 5.0f;
    auto PlayerXInt = static_cast<int>(movementData.position.x);
    auto PlayerYInt = static_cast<int>(movementData.position.y);
    auto ElevPlayer0 =
        tiles[PlayerXInt][PlayerYInt].elevation /
        ElevAmount;
    auto ElevPlayer1 =
        tiles[PlayerXInt + 1][PlayerYInt].elevation /
        ElevAmount;
    auto ElevPlayer2 = tiles[PlayerXInt + 1][PlayerYInt + 1]
                           .elevation /
                       ElevAmount;
    auto ElevPlayer3 =
        tiles[PlayerXInt][PlayerYInt + 1].elevation /
        ElevAmount;
    auto ElevX = movementData.position.x - PlayerXInt;
    auto ElevY = movementData.position.y - PlayerYInt;
    auto ElevPlayer = (ElevPlayer0 + (ElevPlayer1 - ElevPlayer0) * ElevX +
                       ElevPlayer3 + (ElevPlayer2 - ElevPlayer3) * ElevX +
                       ElevPlayer0 + (ElevPlayer3 - ElevPlayer0) * ElevY +
                       ElevPlayer1 + (ElevPlayer2 - ElevPlayer1) * ElevY) /
                      4.0f;

    float SubStepX = movementData.position.x -
            PlayerXInt;

    float SubStepY = movementData.position.y -
            PlayerYInt;

    auto OffsetX = -static_cast<float>(2.0f * camera.GetRenderDistance() + 1.0f)
            / 2.0f * engine.tileSize - SubStepX * engine.tileSize;
    auto OffsetY = -static_cast<float>(2.0f * camera.GetRenderDistance() - 1.0f)
            / 2.0f * engine.tileSize - SubStepY * engine.tileSize;

    for (auto Y = 0; Y < 2 * camera.GetRenderDistance() + 1; Y++) {
      for (auto X = 0; X < 2 * camera.GetRenderDistance() + 1; X++) {
        auto DX = X - camera.GetRenderDistance();
        auto DY = Y - camera.GetRenderDistance();

        if (DX * DX + DY * DY >=
            camera.GetRenderDistance() * camera.GetRenderDistance())
          continue;

        auto TileX = movementData.position.x
                - camera.GetRenderDistance() + X;

        auto TileY = movementData.position.y
                - camera.GetRenderDistance() + Y;

        if (TileX < 0 || TileY < 0 || TileX >= MapAreaSize ||
            TileY >= MapAreaSize)
          continue;

        auto TileXI = static_cast<int>(TileX);
        auto TileYI = static_cast<int>(TileY);

        auto GroundTypeId =
            tiles[TileXI][TileYI].groundType;

        auto WaterAnimIndex0 = 0;
        auto WaterAnimIndex1 = 0;
        auto WaterAnimIndex2 = 0;
        auto WaterAnimIndex3 = 0;

        if (GroundTypeId == groundTypeWaterId) {
          WaterAnimIndex0 =
              ((Ticks() * 3 + (TileXI * TileYI) * 10) % 3600) / 1200;
          WaterAnimIndex1 =
              ((Ticks() * 3 + (TileXI * (TileYI - 1)) * 10) % 3600) /
              1200;
          WaterAnimIndex2 =
              ((Ticks() * 3 + ((TileXI + 1) * (TileYI - 1)) * 10) %
               3600) /
              1200;
          WaterAnimIndex3 =
              ((Ticks() * 3 + ((TileXI + 1) * TileYI) * 10) % 3600) /
              1200;

          if (WaterAnimIndex0 > 0)
            GroundTypeId =
                groundTypeWaterAnimatedId[WaterAnimIndex0];
        }

        auto Elev0 = 0.0f;
        auto Elev1 = 0.0f;
        auto Elev2 = 0.0f;
        auto Elev3 = 0.0f;

        auto WaterWaveHeight0 = WaterAnimIndex0 * engine.tileSize / 4.0f;
        auto WaterWaveHeight1 = WaterAnimIndex1 * engine.tileSize / 4.0f;
        auto WaterWaveHeight2 = WaterAnimIndex2 * engine.tileSize / 4.0f;
        auto WaterWaveHeight3 = WaterAnimIndex3 * engine.tileSize / 4.0f;

        if (TileX >= 0 && TileY >= 0 && TileX < MapAreaSize &&
            TileY < MapAreaSize)
          Elev0 =
              tiles[TileXI][TileYI].elevation /
                  ElevAmount -
              ElevPlayer;

        if (TileX >= 0 && TileY - 1 >= 0 && TileX < MapAreaSize &&
            TileY - 1 < MapAreaSize)
          Elev1 = tiles[TileXI][TileYI - 1]
                          .elevation /
                      ElevAmount -
                  ElevPlayer;
        else
          Elev1 = Elev0;

        if (TileX + 1 >= 0 && TileY - 1 >= 0 && TileX + 1 < MapAreaSize &&
            TileY - 1 < MapAreaSize)
          Elev2 = tiles[TileXI + 1][TileYI - 1]
                          .elevation /
                      ElevAmount -
                  ElevPlayer;
        else if (TileX + 1 < MapAreaSize)
          Elev2 = tiles[TileXI + 1][TileYI]
                          .elevation /
                      ElevAmount -
                  ElevPlayer;
        else if (TileY - 1 >= 0)
          Elev2 = tiles[TileXI][TileYI - 1]
                          .elevation /
                      ElevAmount -
                  ElevPlayer;
        else
          Elev2 = Elev0;

        if (TileX + 1 >= 0 && TileY >= 0 && TileX + 1 < MapAreaSize &&
            TileY < MapAreaSize)
          Elev3 = tiles[TileXI + 1][TileYI]
                          .elevation /
                      ElevAmount -
                  ElevPlayer;
        else
          Elev3 = Elev0;

        auto Slope = Elev3 - Elev0 + Elev0 - Elev1;

        auto R = 0.9f;
        auto G = 0.9f;
        auto B = 0.5f;

        if (Slope < 0) {
          R = 0.6f;
          G = 0.6f;
          B = 0.5f;
        } else if (Slope > 0) {
          R = 1.0f;
          G = 1.0f;
          B = 0.5f;
        } else if (Slope == 0) {
            R = 0.7f;
            G = 0.7f;
            B = 0.5f;
        }

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,
                      engine.imageLoader.images.at(GroundTypeId));

        auto TileX0 = OffsetX + X * engine.tileSize;
        auto TileY0 = Elev0;
        auto TileZ0 = OffsetY + Y * engine.tileSize;
        auto TileX1 = OffsetX + X * engine.tileSize;
        auto TileY1 = Elev1;
        auto TileZ1 = OffsetY + Y * engine.tileSize - engine.tileSize;
        auto TileX2 = OffsetX + X * engine.tileSize + engine.tileSize;
        auto TileY2 = Elev2;
        auto TileZ2 = OffsetY + Y * engine.tileSize - engine.tileSize;
        auto TileX3 = OffsetX + X * engine.tileSize + engine.tileSize;
        auto TileY3 = Elev3;
        auto TileZ3 = OffsetY + Y * engine.tileSize;

        TileY0 = planetShaper.GetNewY(TileY0,
                                             static_cast<float>(TileXI),
                                             static_cast<float>(TileYI));
        TileY1 = planetShaper.GetNewY(TileY1,
                                             static_cast<float>(TileXI),
                                             static_cast<float>(TileYI) - 1);
        TileY2 = planetShaper.GetNewY(TileY2,
                                             static_cast<float>(TileXI) + 1,
                                             static_cast<float>(TileYI) - 1);
        TileY3 = planetShaper.GetNewY(TileY3,
                                             static_cast<float>(TileXI) + 1,
                                             static_cast<float>(TileYI));

        glBegin(GL_QUADS);

        glColor3f(R, G, B);

        glTexCoord2f(0, 0);
        glVertex3f(TileX0, TileY0, TileZ0);
        glTexCoord2f(1, 0);
        glVertex3f(TileX1, TileY1, TileZ1);
        glTexCoord2f(1, 1);
        glVertex3f(TileX2, TileY2, TileZ2);
        glTexCoord2f(0, 1);
        glVertex3f(TileX3, TileY3, TileZ3);

        glEnd();

        if (WaterAnimIndex0 > 0) {
          glBegin(GL_QUADS);

          glColor3f(R, G, B);

          glTexCoord2f(0, 0);
          glVertex3f(TileX0, TileY0 + WaterWaveHeight0, TileZ0);
          glTexCoord2f(1, 0);
          glVertex3f(TileX1, TileY1 + WaterWaveHeight1, TileZ1);
          glTexCoord2f(1, 1);
          glVertex3f(TileX2, TileY2 + WaterWaveHeight2, TileZ2);
          glTexCoord2f(0, 1);
          glVertex3f(TileX3, TileY3 + WaterWaveHeight3, TileZ3);

          glEnd();
        }




        auto HoveredX = camera.GetHoveredTile().x;
        auto HoveredY = camera.GetHoveredTile().y;

        if (HoveredX == TileXI && HoveredY == TileYI &&
            engine.customCursor.cursorType != eCursorTypes::Hidden) {
          glBindTexture(GL_TEXTURE_2D,
                        engine.imageLoader.images.at(GetId("TileHovering")));

          glBegin(GL_QUADS);

          glColor3f(1.0f, 1.0f, 1.0f);

          glTexCoord2f(0, 0);
          glVertex3f(TileX0, TileY0, TileZ0);
          glTexCoord2f(1, 0);
          glVertex3f(TileX1, TileY1, TileZ1);
          glTexCoord2f(1, 1);
          glVertex3f(TileX2, TileY2, TileZ2);
          glTexCoord2f(0, 1);
          glVertex3f(TileX3, TileY3, TileZ3);

          glEnd();
        }

        for (auto &Object :
             tiles[TileXI][TileYI].objects) {

            auto dropShadow = true;

            if (engine.objectsContent.objectDescriptions.count(Object->objectType))
            if (engine.objectsContent.objectDescriptions.at(Object->objectType).flags & ObjectNoShadow)
                dropShadow = false;

                if (dropShadow) {
glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,
                          engine.imageLoader.images.at(GetId("TileShadow")));

            glBegin(GL_QUADS);

            glColor3f(R, G, B);

            glTexCoord2f(0, 0);
            glVertex3f(TileX0, TileY0, TileZ0);
            glTexCoord2f(1, 0);
            glVertex3f(TileX1, TileY1, TileZ1);
            glTexCoord2f(1, 1);
            glVertex3f(TileX2, TileY2, TileZ2);
            glTexCoord2f(0, 1);
            glVertex3f(TileX3, TileY3, TileZ3);

            glEnd();

}

                glDisable(GL_TEXTURE_2D);




          auto TileObject = Object->objectType;
          auto opacity = 1.0f;

          if (engine.objectsContent.objectDescriptions.count(TileObject))
              opacity = engine.objectsContent.objectDescriptions.at(TileObject).opacity;

          if (TileObject != 0)
            engine.DrawModel(TileObject, TileX0 + engine.tileSize / 2,
                             (TileY0 + TileY1 + TileY2 + TileY3) / 4.0f,
                             TileZ0 - engine.tileSize / 2, Object->rotation,
                             Object->scaling, opacity);
        }
      }
    }
}

void cGameWorldRenderer::RenderSunRaysAndActors() {
    auto MapAreaSize = engine.world->mapAreaSize;
    auto ElevAmount = 5.0f;
    auto PlayerXInt = static_cast<int>(engine.GetPlayer().GetModule<cModuleMovementData>().position.x);
    auto PlayerYInt = static_cast<int>(engine.GetPlayer().GetModule<cModuleMovementData>().position.y);
    auto ElevPlayer0 =
        engine.GetCurrentMapArea().tiles[PlayerXInt][PlayerYInt].elevation /
        ElevAmount;
    auto ElevPlayer1 =
        engine.GetCurrentMapArea().tiles[PlayerXInt + 1][PlayerYInt].elevation /
        ElevAmount;
    auto ElevPlayer2 = engine.GetCurrentMapArea()
                           .tiles[PlayerXInt + 1][PlayerYInt + 1]
                           .elevation /
                       ElevAmount;
    auto ElevPlayer3 =
        engine.GetCurrentMapArea().tiles[PlayerXInt][PlayerYInt + 1].elevation /
        ElevAmount;
    auto ElevX = engine.GetPlayer().GetModule<cModuleMovementData>().position.x - PlayerXInt;
    auto ElevY = engine.GetPlayer().GetModule<cModuleMovementData>().position.y - PlayerYInt;
    auto ElevPlayer = (ElevPlayer0 + (ElevPlayer1 - ElevPlayer0) * ElevX +
                       ElevPlayer3 + (ElevPlayer2 - ElevPlayer3) * ElevX +
                       ElevPlayer0 + (ElevPlayer3 - ElevPlayer0) * ElevY +
                       ElevPlayer1 + (ElevPlayer2 - ElevPlayer1) * ElevY) /
                      4.0f;

    float SubStepX = engine.GetPlayer().GetModule<cModuleMovementData>().position.x -
            static_cast<int>(engine.GetPlayer().GetModule<cModuleMovementData>().position.x);

    float SubStepY = engine.GetPlayer().GetModule<cModuleMovementData>().position.y -
            static_cast<int>(engine.GetPlayer().GetModule<cModuleMovementData>().position.y);

    auto OffsetX = -static_cast<float>(2.0f * camera.GetRenderDistance() + 1.0f)
            / 2.0f * engine.tileSize - SubStepX * engine.tileSize;
    auto OffsetY = -static_cast<float>(2.0f * camera.GetRenderDistance() - 1.0f)
            / 2.0f * engine.tileSize - SubStepY * engine.tileSize;

    for (auto Y = 0; Y < 2 * camera.GetRenderDistance() + 1; Y++) {
      for (auto X = 0; X < 2 * camera.GetRenderDistance() + 1; X++) {
          auto DX = X - camera.GetRenderDistance();
          auto DY = Y - camera.GetRenderDistance();

          if (DX * DX + DY * DY >=
              camera.GetRenderDistance() * camera.GetRenderDistance())
            continue;

          auto TileX = engine.GetPlayer().GetModule<cModuleMovementData>().position.x
                  - camera.GetRenderDistance() + X;

          auto TileY = engine.GetPlayer().GetModule<cModuleMovementData>().position.y
                  - camera.GetRenderDistance() + Y;

          if (TileX < 0 || TileY < 0 || TileX >= MapAreaSize ||
              TileY >= MapAreaSize)
            continue;

          auto TileXI = static_cast<int>(TileX);
          auto TileYI = static_cast<int>(TileY);

          auto Elev0 = 0.0f;
          auto Elev1 = 0.0f;
          auto Elev2 = 0.0f;
          auto Elev3 = 0.0f;

          if (TileX >= 0 && TileY >= 0 && TileX < MapAreaSize &&
              TileY < MapAreaSize)
            Elev0 =
                engine.GetCurrentMapArea().tiles[TileXI][TileYI].elevation /
                    ElevAmount -
                ElevPlayer;

          if (TileX >= 0 && TileY - 1 >= 0 && TileX < MapAreaSize &&
              TileY - 1 < MapAreaSize)
            Elev1 = engine.GetCurrentMapArea()
                            .tiles[TileXI][TileYI - 1]
                            .elevation /
                        ElevAmount -
                    ElevPlayer;
          else
            Elev1 = Elev0;

          if (TileX + 1 >= 0 && TileY - 1 >= 0 && TileX + 1 < MapAreaSize &&
              TileY - 1 < MapAreaSize)
            Elev2 = engine.GetCurrentMapArea()
                            .tiles[TileXI + 1][TileYI - 1]
                            .elevation /
                        ElevAmount -
                    ElevPlayer;
          else if (TileX + 1 < MapAreaSize)
            Elev2 = engine.GetCurrentMapArea()
                            .tiles[TileXI + 1][TileYI]
                            .elevation /
                        ElevAmount -
                    ElevPlayer;
          else if (TileY - 1 >= 0)
            Elev2 = engine.GetCurrentMapArea()
                            .tiles[TileXI][TileYI - 1]
                            .elevation /
                        ElevAmount -
                    ElevPlayer;
          else
            Elev2 = Elev0;

          if (TileX + 1 >= 0 && TileY >= 0 && TileX + 1 < MapAreaSize &&
              TileY < MapAreaSize)
            Elev3 = engine.GetCurrentMapArea()
                            .tiles[TileXI + 1][TileYI]
                            .elevation /
                        ElevAmount -
                    ElevPlayer;
          else
            Elev3 = Elev0;

          auto TileX0 = OffsetX + X * engine.tileSize;
          auto TileY0 = Elev0;
          auto TileZ0 = OffsetY + Y * engine.tileSize;
          auto TileX1 = OffsetX + X * engine.tileSize;
          auto TileY1 = Elev1;
          auto TileZ1 = OffsetY + Y * engine.tileSize - engine.tileSize;
          auto TileX2 = OffsetX + X * engine.tileSize + engine.tileSize;
          auto TileY2 = Elev2;
          auto TileZ2 = OffsetY + Y * engine.tileSize - engine.tileSize;
          auto TileX3 = OffsetX + X * engine.tileSize + engine.tileSize;
          auto TileY3 = Elev3;
          auto TileZ3 = OffsetY + Y * engine.tileSize;

          TileY0 = planetShaper.GetNewY(TileY0,
                                               static_cast<float>(TileXI),
                                               static_cast<float>(TileYI));
          TileY1 = planetShaper.GetNewY(TileY1,
                                               static_cast<float>(TileXI),
                                               static_cast<float>(TileYI) - 1);
          TileY2 = planetShaper.GetNewY(TileY2,
                                               static_cast<float>(TileXI) + 1,
                                               static_cast<float>(TileYI) - 1);
          TileY3 = planetShaper.GetNewY(TileY3,
                                               static_cast<float>(TileXI) + 1,
                                               static_cast<float>(TileYI));
        if ((TileXI + TileYI) % 6 == 0) {
          auto sunx = -500.0f;
          auto suny = 500.0f;
          auto sunz = -500.0f;

          auto alpha = ((Ticks() + TileXI*TileYI) % 1000)/1000.0f;
          if (alpha >= 0.5f)
              alpha = 0.5f - (alpha - 0.5f);

          alpha /= 2.0f;

                      glBegin(GL_LINE_STRIP);
                      glColor4f(1.0f, 1.0f, 0.0f, alpha);
                      glVertex3f(TileX0, TileY0, TileZ0);
                      glVertex3f(sunx, suny, sunz);
                      glEnd();
        }

        if (engine.GetCurrentMapArea().tiles[TileXI][TileYI].actor !=
            nullptr) {
          auto SubXPos = (engine.GetCurrentMapArea()
                              .tiles[TileXI][TileYI]
                              .actor->GetModule<cModuleMovementData>().position.x -
                          static_cast<int>(engine.GetCurrentMapArea()
                                  .tiles[TileXI][TileYI]
                                  .actor->GetModule<cModuleMovementData>().position.x)) *
                         engine.tileSize;
          auto SubYPos = (engine.GetCurrentMapArea()
                              .tiles[TileXI][TileYI]
                              .actor->GetModule<cModuleMovementData>().position.y -
                          static_cast<int>(engine.GetCurrentMapArea()
                                  .tiles[TileXI][TileYI]
                                  .actor->GetModule<cModuleMovementData>().position.y)) *
                         engine.tileSize;

          glEnable(GL_TEXTURE_2D);

          glBindTexture(GL_TEXTURE_2D,
                        engine.imageLoader.images.at(GetId("TileShadow")));

          glBegin(GL_QUADS);

          glColor3f(1, 1, 1);

          glTexCoord2f(0, 0);
          glVertex3f(TileX0 - engine.tileSize/2 + SubXPos,
                     TileY0 + 0.05f,
                     TileZ0 - engine.tileSize/2 + SubYPos);
          glTexCoord2f(1, 0);
          glVertex3f(TileX1 - engine.tileSize/2 + SubXPos,
                     TileY1 + 0.05f,
                     TileZ1 - engine.tileSize/2 + SubYPos);
          glTexCoord2f(1, 1);
          glVertex3f(TileX2 - engine.tileSize/2 + SubXPos,
                     TileY2 + 0.05f,
                     TileZ2 - engine.tileSize/2 + SubYPos);
          glTexCoord2f(0, 1);
          glVertex3f(TileX3 - engine.tileSize/2 + SubXPos,
                     TileY3 + 0.05f,
                     TileZ3 - engine.tileSize/2 + SubYPos);

          glEnd();

          glDisable(GL_TEXTURE_2D);

          auto ModelYPos0 = TileY1 + (TileY2 - TileY1)*SubXPos/engine.tileSize;
          auto ModelYPos1 = TileY0 + (TileY3 - TileY0)*SubXPos/engine.tileSize;
          auto ModelYPos = ModelYPos0
                  + (ModelYPos1 - ModelYPos0)*SubYPos/engine.tileSize;

          engine.DrawModel(engine.GetCurrentMapArea()
                           .tiles[TileXI][TileYI]
                           .actor->GetAnimatedModelId(), TileX0 + SubXPos,
                           ModelYPos  + engine.GetCurrentMapArea()
                                                      .tiles[TileXI][TileYI]
                                                      .actor->GetModule<cModuleMovementData>().positionZ,
                           TileZ0 - engine.tileSize + SubYPos,
                           *engine.GetCurrentMapArea()
                               .tiles[TileXI][TileYI]
                               .actor->GetModule<cModuleMovementData>().facingAngle);
        }
      }
    }
}









void cGameWorldRenderer::RenderRoof() {
    auto MapAreaSize = engine.world->mapAreaSize;

    auto ElevAmount = 5.0f;
    auto PlayerXInt = static_cast<int>(engine.GetPlayer().GetModule<cModuleMovementData>().position.x);
    auto PlayerYInt = static_cast<int>(engine.GetPlayer().GetModule<cModuleMovementData>().position.y);
    auto ElevPlayer0 =
        engine.GetCurrentMapArea().tiles[PlayerXInt][PlayerYInt].elevation /
        ElevAmount;
    auto ElevPlayer1 =
        engine.GetCurrentMapArea().tiles[PlayerXInt + 1][PlayerYInt].elevation /
        ElevAmount;
    auto ElevPlayer2 = engine.GetCurrentMapArea()
                           .tiles[PlayerXInt + 1][PlayerYInt + 1]
                           .elevation /
                       ElevAmount;
    auto ElevPlayer3 =
        engine.GetCurrentMapArea().tiles[PlayerXInt][PlayerYInt + 1].elevation /
        ElevAmount;
    auto ElevX = engine.GetPlayer().GetModule<cModuleMovementData>().position.x - PlayerXInt;
    auto ElevY = engine.GetPlayer().GetModule<cModuleMovementData>().position.y - PlayerYInt;
    auto ElevPlayer = (ElevPlayer0 + (ElevPlayer1 - ElevPlayer0) * ElevX +
                       ElevPlayer3 + (ElevPlayer2 - ElevPlayer3) * ElevX +
                       ElevPlayer0 + (ElevPlayer3 - ElevPlayer0) * ElevY +
                       ElevPlayer1 + (ElevPlayer2 - ElevPlayer1) * ElevY) /
                      4.0f;

    float SubStepX = engine.GetPlayer().GetModule<cModuleMovementData>().position.x -
            static_cast<int>(engine.GetPlayer().GetModule<cModuleMovementData>().position.x);

    float SubStepY = engine.GetPlayer().GetModule<cModuleMovementData>().position.y -
            static_cast<int>(engine.GetPlayer().GetModule<cModuleMovementData>().position.y);

    auto OffsetX = -static_cast<float>(2.0f * camera.GetRenderDistance() + 1.0f)
            / 2.0f * engine.tileSize - SubStepX * engine.tileSize;
    auto OffsetY = -static_cast<float>(2.0f * camera.GetRenderDistance() - 1.0f)
            / 2.0f * engine.tileSize - SubStepY * engine.tileSize;

    for (auto Y = 0; Y < 2 * camera.GetRenderDistance() + 1; Y++) {
      for (auto X = 0; X < 2 * camera.GetRenderDistance() + 1; X++) {
        auto DX = X - camera.GetRenderDistance();
        auto DY = Y - camera.GetRenderDistance();

        if (DX * DX + DY * DY >=
            camera.GetRenderDistance() * camera.GetRenderDistance())
          continue;

        auto TileX = engine.GetPlayer().GetModule<cModuleMovementData>().position.x
                - camera.GetRenderDistance() + X;

        auto TileY = engine.GetPlayer().GetModule<cModuleMovementData>().position.y
                - camera.GetRenderDistance() + Y;

        if (TileX < 0 || TileY < 0 || TileX >= MapAreaSize ||
            TileY >= MapAreaSize)
          continue;

        auto TileXI = static_cast<int>(TileX);
        auto TileYI = static_cast<int>(TileY);

        auto Elev0 = 0.0f;
        auto Elev1 = 0.0f;
        auto Elev2 = 0.0f;
        auto Elev3 = 0.0f;

        if (TileX >= 0 && TileY >= 0 && TileX < MapAreaSize &&
            TileY < MapAreaSize)
          Elev0 =
              engine.GetCurrentMapArea().tiles[TileXI][TileYI].elevation /
                  ElevAmount -
              ElevPlayer;

        if (TileX >= 0 && TileY - 1 >= 0 && TileX < MapAreaSize &&
            TileY - 1 < MapAreaSize)
          Elev1 = engine.GetCurrentMapArea()
                          .tiles[TileXI][TileYI - 1]
                          .elevation /
                      ElevAmount -
                  ElevPlayer;
        else
          Elev1 = Elev0;

        if (TileX + 1 >= 0 && TileY - 1 >= 0 && TileX + 1 < MapAreaSize &&
            TileY - 1 < MapAreaSize)
          Elev2 = engine.GetCurrentMapArea()
                          .tiles[TileXI + 1][TileYI - 1]
                          .elevation /
                      ElevAmount -
                  ElevPlayer;
        else if (TileX + 1 < MapAreaSize)
          Elev2 = engine.GetCurrentMapArea()
                          .tiles[TileXI + 1][TileYI]
                          .elevation /
                      ElevAmount -
                  ElevPlayer;
        else if (TileY - 1 >= 0)
          Elev2 = engine.GetCurrentMapArea()
                          .tiles[TileXI][TileYI - 1]
                          .elevation /
                      ElevAmount -
                  ElevPlayer;
        else
          Elev2 = Elev0;

        if (TileX + 1 >= 0 && TileY >= 0 && TileX + 1 < MapAreaSize &&
            TileY < MapAreaSize)
          Elev3 = engine.GetCurrentMapArea()
                          .tiles[TileXI + 1][TileYI]
                          .elevation /
                      ElevAmount -
                  ElevPlayer;
        else
          Elev3 = Elev0;

        auto Slope = Elev3 - Elev0 + Elev0 - Elev1;

        auto R = 0.9f;
        auto G = 0.9f;
        auto B = 0.5f;

        if (Slope < 0) {
          R = 0.6f;
          G = 0.6f;
          B = 0.5f;
        } else if (Slope > 0) {
          R = 1.0f;
          G = 1.0f;
          B = 0.5f;
        } else if (Slope == 0) {
            R = 0.7f;
            G = 0.7f;
            B = 0.5f;
        }

        auto TileX0 = OffsetX + X * engine.tileSize;
        auto TileY0 = Elev0;
        auto TileZ0 = OffsetY + Y * engine.tileSize;
        auto TileX1 = OffsetX + X * engine.tileSize;
        auto TileY1 = Elev1;
        auto TileZ1 = OffsetY + Y * engine.tileSize - engine.tileSize;
        auto TileX2 = OffsetX + X * engine.tileSize + engine.tileSize;
        auto TileY2 = Elev2;
        auto TileZ2 = OffsetY + Y * engine.tileSize - engine.tileSize;
        auto TileX3 = OffsetX + X * engine.tileSize + engine.tileSize;
        auto TileY3 = Elev3;
        auto TileZ3 = OffsetY + Y * engine.tileSize;

        TileY0 = planetShaper.GetNewY(TileY0,
                                             static_cast<float>(TileXI),
                                             static_cast<float>(TileYI));
        TileY1 = planetShaper.GetNewY(TileY1,
                                             static_cast<float>(TileXI),
                                             static_cast<float>(TileYI) - 1);
        TileY2 = planetShaper.GetNewY(TileY2,
                                             static_cast<float>(TileXI) + 1,
                                             static_cast<float>(TileYI) - 1);
        TileY3 = planetShaper.GetNewY(TileY3,
                                             static_cast<float>(TileXI) + 1,
                                             static_cast<float>(TileYI));



        glDisable(GL_TEXTURE_2D);


if (engine.GetCurrentMapArea()
        .tiles[TileXI][TileYI]
        .roof != nullptr) {

    auto& roof = engine.GetCurrentMapArea()
            .tiles[TileXI][TileYI]
            .roof;


  auto RoofObject = roof->objectType;
  auto opacity = 1.0f;

  if (engine.objectsContent.objectDescriptions.count(RoofObject))
      opacity = engine.objectsContent.objectDescriptions.at(RoofObject).opacity;

  engine.DrawModel(RoofObject, TileX0 + engine.tileSize / 2,
                   (TileY0 + TileY1 + TileY2 + TileY3) / 4.0f,
                   TileZ0 - engine.tileSize / 2, roof->rotation,
                   roof->scaling, opacity);

}

      }
    }
}









}  // namespace Forradia
