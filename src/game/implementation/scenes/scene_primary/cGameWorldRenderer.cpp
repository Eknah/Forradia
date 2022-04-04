// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include <string>
#include "cGameWorldRenderer.h"
#include "../engine/cEngine.h"
#include "implementation/functionality/actor/modules/cModuleMovementData.h"

namespace Forradia {

void cGameWorldRenderer::Render() {
  Background.Render(Camera.ZoomAmount);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45, 1.333, 0.5, 100);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  auto CameraX = 0.0f;
  auto CameraZ = -1.0f;
  auto AngleRadians =
      atan2(CameraZ, CameraX) + Camera.LookingAngle / 180.0f * M_PI;
  auto CameraDist = 1;
  auto Zoom = Camera.ZoomAmount;

  glTranslatef(0.0f, -Zoom, -2.0f - Zoom * 4.0f);

  CameraX = static_cast<float>(cos(AngleRadians)) * CameraDist;
  CameraZ = -static_cast<float>(sin(AngleRadians)) * CameraDist;

  gluLookAt(CameraX-Engine.tileSize/2,
            Camera.CameraHeight,
            CameraZ-Engine.tileSize/2,
            -Engine.tileSize/2,
            -1,
            -Engine.tileSize/2,
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
  RenderActors();
  RenderRoof();

  glPopMatrix();
  glDisable(GL_DEPTH_TEST);
}

void cGameWorldRenderer::RenderTilesAndObjects() {
    auto MapAreaSize = Engine.world->mapAreaSize;

    auto ElevAmount = 5.0f;
    auto PlayerXInt = static_cast<int>(Engine.GetPlayer().GetModule<cModuleMovementData>().Position.x);
    auto PlayerYInt = static_cast<int>(Engine.GetPlayer().GetModule<cModuleMovementData>().Position.y);
    auto ElevPlayer0 =
        Engine.GetCurrentMapArea().tiles[PlayerXInt][PlayerYInt].elevation /
        ElevAmount;
    auto ElevPlayer1 =
        Engine.GetCurrentMapArea().tiles[PlayerXInt + 1][PlayerYInt].elevation /
        ElevAmount;
    auto ElevPlayer2 = Engine.GetCurrentMapArea()
                           .tiles[PlayerXInt + 1][PlayerYInt + 1]
                           .elevation /
                       ElevAmount;
    auto ElevPlayer3 =
        Engine.GetCurrentMapArea().tiles[PlayerXInt][PlayerYInt + 1].elevation /
        ElevAmount;
    auto ElevX = Engine.GetPlayer().GetModule<cModuleMovementData>().Position.x - PlayerXInt;
    auto ElevY = Engine.GetPlayer().GetModule<cModuleMovementData>().Position.y - PlayerYInt;
    auto ElevPlayer = (ElevPlayer0 + (ElevPlayer1 - ElevPlayer0) * ElevX +
                       ElevPlayer3 + (ElevPlayer2 - ElevPlayer3) * ElevX +
                       ElevPlayer0 + (ElevPlayer3 - ElevPlayer0) * ElevY +
                       ElevPlayer1 + (ElevPlayer2 - ElevPlayer1) * ElevY) /
                      4.0f;

    float SubStepX = Engine.GetPlayer().GetModule<cModuleMovementData>().Position.x -
            static_cast<int>(Engine.GetPlayer().GetModule<cModuleMovementData>().Position.x);

    float SubStepY = Engine.GetPlayer().GetModule<cModuleMovementData>().Position.y -
            static_cast<int>(Engine.GetPlayer().GetModule<cModuleMovementData>().Position.y);

    auto OffsetX = -static_cast<float>(2.0f * Camera.GetRenderDistance() + 1.0f)
            / 2.0f * Engine.tileSize - SubStepX * Engine.tileSize;
    auto OffsetY = -static_cast<float>(2.0f * Camera.GetRenderDistance() - 1.0f)
            / 2.0f * Engine.tileSize - SubStepY * Engine.tileSize;

    for (auto Y = 0; Y < 2 * Camera.GetRenderDistance() + 1; Y++) {
      for (auto X = 0; X < 2 * Camera.GetRenderDistance() + 1; X++) {
        auto DX = X - Camera.GetRenderDistance();
        auto DY = Y - Camera.GetRenderDistance();

        if (DX * DX + DY * DY >=
            Camera.GetRenderDistance() * Camera.GetRenderDistance())
          continue;

        auto TileX = Engine.GetPlayer().GetModule<cModuleMovementData>().Position.x
                - Camera.GetRenderDistance() + X;

        auto TileY = Engine.GetPlayer().GetModule<cModuleMovementData>().Position.y
                - Camera.GetRenderDistance() + Y;

        if (TileX < 0 || TileY < 0 || TileX >= MapAreaSize ||
            TileY >= MapAreaSize)
          continue;

        auto TileXI = static_cast<int>(TileX);
        auto TileYI = static_cast<int>(TileY);

        auto GroundTypeId =
            Engine.GetCurrentMapArea().tiles[TileXI][TileYI].groundType;

        auto WaterAnimIndex0 = 0;
        auto WaterAnimIndex1 = 0;
        auto WaterAnimIndex2 = 0;
        auto WaterAnimIndex3 = 0;

        if (GroundTypeId == GetId("GroundTypeWater")) {
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
                GetId("GroundTypeWater" + std::to_string(WaterAnimIndex0));
        }

        auto Elev0 = 0.0f;
        auto Elev1 = 0.0f;
        auto Elev2 = 0.0f;
        auto Elev3 = 0.0f;

        auto WaterWaveHeight0 = WaterAnimIndex0 * Engine.tileSize / 4.0f;
        auto WaterWaveHeight1 = WaterAnimIndex1 * Engine.tileSize / 4.0f;
        auto WaterWaveHeight2 = WaterAnimIndex2 * Engine.tileSize / 4.0f;
        auto WaterWaveHeight3 = WaterAnimIndex3 * Engine.tileSize / 4.0f;

        if (TileX >= 0 && TileY >= 0 && TileX < MapAreaSize &&
            TileY < MapAreaSize)
          Elev0 =
              Engine.GetCurrentMapArea().tiles[TileXI][TileYI].elevation /
                  ElevAmount -
              ElevPlayer;

        if (TileX >= 0 && TileY - 1 >= 0 && TileX < MapAreaSize &&
            TileY - 1 < MapAreaSize)
          Elev1 = Engine.GetCurrentMapArea()
                          .tiles[TileXI][TileYI - 1]
                          .elevation /
                      ElevAmount -
                  ElevPlayer;
        else
          Elev1 = Elev0;

        if (TileX + 1 >= 0 && TileY - 1 >= 0 && TileX + 1 < MapAreaSize &&
            TileY - 1 < MapAreaSize)
          Elev2 = Engine.GetCurrentMapArea()
                          .tiles[TileXI + 1][TileYI - 1]
                          .elevation /
                      ElevAmount -
                  ElevPlayer;
        else if (TileX + 1 < MapAreaSize)
          Elev2 = Engine.GetCurrentMapArea()
                          .tiles[TileXI + 1][TileYI]
                          .elevation /
                      ElevAmount -
                  ElevPlayer;
        else if (TileY - 1 >= 0)
          Elev2 = Engine.GetCurrentMapArea()
                          .tiles[TileXI][TileYI - 1]
                          .elevation /
                      ElevAmount -
                  ElevPlayer;
        else
          Elev2 = Elev0;

        if (TileX + 1 >= 0 && TileY >= 0 && TileX + 1 < MapAreaSize &&
            TileY < MapAreaSize)
          Elev3 = Engine.GetCurrentMapArea()
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

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,
                      Engine.imageLoader.images.at(GroundTypeId));

        auto TileX0 = OffsetX + X * Engine.tileSize;
        auto TileY0 = Elev0;
        auto TileZ0 = OffsetY + Y * Engine.tileSize;
        auto TileX1 = OffsetX + X * Engine.tileSize;
        auto TileY1 = Elev1;
        auto TileZ1 = OffsetY + Y * Engine.tileSize - Engine.tileSize;
        auto TileX2 = OffsetX + X * Engine.tileSize + Engine.tileSize;
        auto TileY2 = Elev2;
        auto TileZ2 = OffsetY + Y * Engine.tileSize - Engine.tileSize;
        auto TileX3 = OffsetX + X * Engine.tileSize + Engine.tileSize;
        auto TileY3 = Elev3;
        auto TileZ3 = OffsetY + Y * Engine.tileSize;

        TileY0 = PlanetShaper.GetNewY(TileY0,
                                             static_cast<float>(TileXI),
                                             static_cast<float>(TileYI));
        TileY1 = PlanetShaper.GetNewY(TileY1,
                                             static_cast<float>(TileXI),
                                             static_cast<float>(TileYI) - 1);
        TileY2 = PlanetShaper.GetNewY(TileY2,
                                             static_cast<float>(TileXI) + 1,
                                             static_cast<float>(TileYI) - 1);
        TileY3 = PlanetShaper.GetNewY(TileY3,
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



        auto HoveredX = Camera.GetHoveredTile().x;
        auto HoveredY = Camera.GetHoveredTile().y;

        if (HoveredX == TileXI && HoveredY == TileYI &&
            Engine.customCursor.cursorType != eCursorTypes::Hidden) {
          glBindTexture(GL_TEXTURE_2D,
                        Engine.imageLoader.images.at(GetId("TileHovering")));

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
             Engine.GetCurrentMapArea().tiles[TileXI][TileYI].objects) {

            auto dropShadow = true;

            if (Engine.objectsContent.ObjectDescriptions.count(Object->ObjectType))
            if (Engine.objectsContent.ObjectDescriptions.at(Object->ObjectType).Flags & ObjectNoShadow)
                dropShadow = false;

                if (dropShadow) {
glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,
                          Engine.imageLoader.images.at(GetId("TileShadow")));

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




          auto TileObject = Object->ObjectType;
          auto opacity = 1.0f;

          if (Engine.objectsContent.ObjectDescriptions.count(TileObject))
              opacity = Engine.objectsContent.ObjectDescriptions.at(TileObject).Opacity;

          if (TileObject != 0)
            Engine.DrawModel(TileObject, TileX0 + Engine.tileSize / 2,
                             (TileY0 + TileY1 + TileY2 + TileY3) / 4.0f,
                             TileZ0 - Engine.tileSize / 2, Object->Rotation,
                             Object->Scaling, opacity);
        }
      }
    }
}

void cGameWorldRenderer::RenderActors() {
    auto MapAreaSize = Engine.world->mapAreaSize;
    auto ElevAmount = 5.0f;
    auto PlayerXInt = static_cast<int>(Engine.GetPlayer().GetModule<cModuleMovementData>().Position.x);
    auto PlayerYInt = static_cast<int>(Engine.GetPlayer().GetModule<cModuleMovementData>().Position.y);
    auto ElevPlayer0 =
        Engine.GetCurrentMapArea().tiles[PlayerXInt][PlayerYInt].elevation /
        ElevAmount;
    auto ElevPlayer1 =
        Engine.GetCurrentMapArea().tiles[PlayerXInt + 1][PlayerYInt].elevation /
        ElevAmount;
    auto ElevPlayer2 = Engine.GetCurrentMapArea()
                           .tiles[PlayerXInt + 1][PlayerYInt + 1]
                           .elevation /
                       ElevAmount;
    auto ElevPlayer3 =
        Engine.GetCurrentMapArea().tiles[PlayerXInt][PlayerYInt + 1].elevation /
        ElevAmount;
    auto ElevX = Engine.GetPlayer().GetModule<cModuleMovementData>().Position.x - PlayerXInt;
    auto ElevY = Engine.GetPlayer().GetModule<cModuleMovementData>().Position.y - PlayerYInt;
    auto ElevPlayer = (ElevPlayer0 + (ElevPlayer1 - ElevPlayer0) * ElevX +
                       ElevPlayer3 + (ElevPlayer2 - ElevPlayer3) * ElevX +
                       ElevPlayer0 + (ElevPlayer3 - ElevPlayer0) * ElevY +
                       ElevPlayer1 + (ElevPlayer2 - ElevPlayer1) * ElevY) /
                      4.0f;

    float SubStepX = Engine.GetPlayer().GetModule<cModuleMovementData>().Position.x -
            static_cast<int>(Engine.GetPlayer().GetModule<cModuleMovementData>().Position.x);

    float SubStepY = Engine.GetPlayer().GetModule<cModuleMovementData>().Position.y -
            static_cast<int>(Engine.GetPlayer().GetModule<cModuleMovementData>().Position.y);

    auto OffsetX = -static_cast<float>(2.0f * Camera.GetRenderDistance() + 1.0f)
            / 2.0f * Engine.tileSize - SubStepX * Engine.tileSize;
    auto OffsetY = -static_cast<float>(2.0f * Camera.GetRenderDistance() - 1.0f)
            / 2.0f * Engine.tileSize - SubStepY * Engine.tileSize;

    for (auto Y = 0; Y < 2 * Camera.GetRenderDistance() + 1; Y++) {
      for (auto X = 0; X < 2 * Camera.GetRenderDistance() + 1; X++) {
          auto DX = X - Camera.GetRenderDistance();
          auto DY = Y - Camera.GetRenderDistance();

          if (DX * DX + DY * DY >=
              Camera.GetRenderDistance() * Camera.GetRenderDistance())
            continue;

          auto TileX = Engine.GetPlayer().GetModule<cModuleMovementData>().Position.x
                  - Camera.GetRenderDistance() + X;

          auto TileY = Engine.GetPlayer().GetModule<cModuleMovementData>().Position.y
                  - Camera.GetRenderDistance() + Y;

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
                Engine.GetCurrentMapArea().tiles[TileXI][TileYI].elevation /
                    ElevAmount -
                ElevPlayer;

          if (TileX >= 0 && TileY - 1 >= 0 && TileX < MapAreaSize &&
              TileY - 1 < MapAreaSize)
            Elev1 = Engine.GetCurrentMapArea()
                            .tiles[TileXI][TileYI - 1]
                            .elevation /
                        ElevAmount -
                    ElevPlayer;
          else
            Elev1 = Elev0;

          if (TileX + 1 >= 0 && TileY - 1 >= 0 && TileX + 1 < MapAreaSize &&
              TileY - 1 < MapAreaSize)
            Elev2 = Engine.GetCurrentMapArea()
                            .tiles[TileXI + 1][TileYI - 1]
                            .elevation /
                        ElevAmount -
                    ElevPlayer;
          else if (TileX + 1 < MapAreaSize)
            Elev2 = Engine.GetCurrentMapArea()
                            .tiles[TileXI + 1][TileYI]
                            .elevation /
                        ElevAmount -
                    ElevPlayer;
          else if (TileY - 1 >= 0)
            Elev2 = Engine.GetCurrentMapArea()
                            .tiles[TileXI][TileYI - 1]
                            .elevation /
                        ElevAmount -
                    ElevPlayer;
          else
            Elev2 = Elev0;

          if (TileX + 1 >= 0 && TileY >= 0 && TileX + 1 < MapAreaSize &&
              TileY < MapAreaSize)
            Elev3 = Engine.GetCurrentMapArea()
                            .tiles[TileXI + 1][TileYI]
                            .elevation /
                        ElevAmount -
                    ElevPlayer;
          else
            Elev3 = Elev0;

          auto TileX0 = OffsetX + X * Engine.tileSize;
          auto TileY0 = Elev0;
          auto TileZ0 = OffsetY + Y * Engine.tileSize;
          auto TileX1 = OffsetX + X * Engine.tileSize;
          auto TileY1 = Elev1;
          auto TileZ1 = OffsetY + Y * Engine.tileSize - Engine.tileSize;
          auto TileX2 = OffsetX + X * Engine.tileSize + Engine.tileSize;
          auto TileY2 = Elev2;
          auto TileZ2 = OffsetY + Y * Engine.tileSize - Engine.tileSize;
          auto TileX3 = OffsetX + X * Engine.tileSize + Engine.tileSize;
          auto TileY3 = Elev3;
          auto TileZ3 = OffsetY + Y * Engine.tileSize;

          TileY0 = PlanetShaper.GetNewY(TileY0,
                                               static_cast<float>(TileXI),
                                               static_cast<float>(TileYI));
          TileY1 = PlanetShaper.GetNewY(TileY1,
                                               static_cast<float>(TileXI),
                                               static_cast<float>(TileYI) - 1);
          TileY2 = PlanetShaper.GetNewY(TileY2,
                                               static_cast<float>(TileXI) + 1,
                                               static_cast<float>(TileYI) - 1);
          TileY3 = PlanetShaper.GetNewY(TileY3,
                                               static_cast<float>(TileXI) + 1,
                                               static_cast<float>(TileYI));

        if (Engine.GetCurrentMapArea().tiles[TileXI][TileYI].actor !=
            nullptr) {
          auto SubXPos = (Engine.GetCurrentMapArea()
                              .tiles[TileXI][TileYI]
                              .actor->GetModule<cModuleMovementData>().Position.x -
                          static_cast<int>(Engine.GetCurrentMapArea()
                                  .tiles[TileXI][TileYI]
                                  .actor->GetModule<cModuleMovementData>().Position.x)) *
                         Engine.tileSize;
          auto SubYPos = (Engine.GetCurrentMapArea()
                              .tiles[TileXI][TileYI]
                              .actor->GetModule<cModuleMovementData>().Position.y -
                          static_cast<int>(Engine.GetCurrentMapArea()
                                  .tiles[TileXI][TileYI]
                                  .actor->GetModule<cModuleMovementData>().Position.y)) *
                         Engine.tileSize;

          glEnable(GL_TEXTURE_2D);

          glBindTexture(GL_TEXTURE_2D,
                        Engine.imageLoader.images.at(GetId("TileShadow")));

          glBegin(GL_QUADS);

          glColor3f(1, 1, 1);

          glTexCoord2f(0, 0);
          glVertex3f(TileX0 - Engine.tileSize/2 + SubXPos,
                     TileY0 + 0.05f,
                     TileZ0 - Engine.tileSize/2 + SubYPos);
          glTexCoord2f(1, 0);
          glVertex3f(TileX1 - Engine.tileSize/2 + SubXPos,
                     TileY1 + 0.05f,
                     TileZ1 - Engine.tileSize/2 + SubYPos);
          glTexCoord2f(1, 1);
          glVertex3f(TileX2 - Engine.tileSize/2 + SubXPos,
                     TileY2 + 0.05f,
                     TileZ2 - Engine.tileSize/2 + SubYPos);
          glTexCoord2f(0, 1);
          glVertex3f(TileX3 - Engine.tileSize/2 + SubXPos,
                     TileY3 + 0.05f,
                     TileZ3 - Engine.tileSize/2 + SubYPos);

          glEnd();

          glDisable(GL_TEXTURE_2D);

          auto ModelYPos0 = TileY1 + (TileY2 - TileY1)*SubXPos/Engine.tileSize;
          auto ModelYPos1 = TileY0 + (TileY3 - TileY0)*SubXPos/Engine.tileSize;
          auto ModelYPos = ModelYPos0
                  + (ModelYPos1 - ModelYPos0)*SubYPos/Engine.tileSize;

          Engine.DrawModel(Engine.GetCurrentMapArea()
                           .tiles[TileXI][TileYI]
                           .actor->GetAnimatedModelId(), TileX0 + SubXPos,
                           ModelYPos  + Engine.GetCurrentMapArea()
                                                      .tiles[TileXI][TileYI]
                                                      .actor->GetModule<cModuleMovementData>().PositionZ,
                           TileZ0 - Engine.tileSize + SubYPos,
                           *Engine.GetCurrentMapArea()
                               .tiles[TileXI][TileYI]
                               .actor->GetModule<cModuleMovementData>().FacingAngle);
        }
      }
    }
}









void cGameWorldRenderer::RenderRoof() {
    auto MapAreaSize = Engine.world->mapAreaSize;

    auto ElevAmount = 5.0f;
    auto PlayerXInt = static_cast<int>(Engine.GetPlayer().GetModule<cModuleMovementData>().Position.x);
    auto PlayerYInt = static_cast<int>(Engine.GetPlayer().GetModule<cModuleMovementData>().Position.y);
    auto ElevPlayer0 =
        Engine.GetCurrentMapArea().tiles[PlayerXInt][PlayerYInt].elevation /
        ElevAmount;
    auto ElevPlayer1 =
        Engine.GetCurrentMapArea().tiles[PlayerXInt + 1][PlayerYInt].elevation /
        ElevAmount;
    auto ElevPlayer2 = Engine.GetCurrentMapArea()
                           .tiles[PlayerXInt + 1][PlayerYInt + 1]
                           .elevation /
                       ElevAmount;
    auto ElevPlayer3 =
        Engine.GetCurrentMapArea().tiles[PlayerXInt][PlayerYInt + 1].elevation /
        ElevAmount;
    auto ElevX = Engine.GetPlayer().GetModule<cModuleMovementData>().Position.x - PlayerXInt;
    auto ElevY = Engine.GetPlayer().GetModule<cModuleMovementData>().Position.y - PlayerYInt;
    auto ElevPlayer = (ElevPlayer0 + (ElevPlayer1 - ElevPlayer0) * ElevX +
                       ElevPlayer3 + (ElevPlayer2 - ElevPlayer3) * ElevX +
                       ElevPlayer0 + (ElevPlayer3 - ElevPlayer0) * ElevY +
                       ElevPlayer1 + (ElevPlayer2 - ElevPlayer1) * ElevY) /
                      4.0f;

    float SubStepX = Engine.GetPlayer().GetModule<cModuleMovementData>().Position.x -
            static_cast<int>(Engine.GetPlayer().GetModule<cModuleMovementData>().Position.x);

    float SubStepY = Engine.GetPlayer().GetModule<cModuleMovementData>().Position.y -
            static_cast<int>(Engine.GetPlayer().GetModule<cModuleMovementData>().Position.y);

    auto OffsetX = -static_cast<float>(2.0f * Camera.GetRenderDistance() + 1.0f)
            / 2.0f * Engine.tileSize - SubStepX * Engine.tileSize;
    auto OffsetY = -static_cast<float>(2.0f * Camera.GetRenderDistance() - 1.0f)
            / 2.0f * Engine.tileSize - SubStepY * Engine.tileSize;

    for (auto Y = 0; Y < 2 * Camera.GetRenderDistance() + 1; Y++) {
      for (auto X = 0; X < 2 * Camera.GetRenderDistance() + 1; X++) {
        auto DX = X - Camera.GetRenderDistance();
        auto DY = Y - Camera.GetRenderDistance();

        if (DX * DX + DY * DY >=
            Camera.GetRenderDistance() * Camera.GetRenderDistance())
          continue;

        auto TileX = Engine.GetPlayer().GetModule<cModuleMovementData>().Position.x
                - Camera.GetRenderDistance() + X;

        auto TileY = Engine.GetPlayer().GetModule<cModuleMovementData>().Position.y
                - Camera.GetRenderDistance() + Y;

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
              Engine.GetCurrentMapArea().tiles[TileXI][TileYI].elevation /
                  ElevAmount -
              ElevPlayer;

        if (TileX >= 0 && TileY - 1 >= 0 && TileX < MapAreaSize &&
            TileY - 1 < MapAreaSize)
          Elev1 = Engine.GetCurrentMapArea()
                          .tiles[TileXI][TileYI - 1]
                          .elevation /
                      ElevAmount -
                  ElevPlayer;
        else
          Elev1 = Elev0;

        if (TileX + 1 >= 0 && TileY - 1 >= 0 && TileX + 1 < MapAreaSize &&
            TileY - 1 < MapAreaSize)
          Elev2 = Engine.GetCurrentMapArea()
                          .tiles[TileXI + 1][TileYI - 1]
                          .elevation /
                      ElevAmount -
                  ElevPlayer;
        else if (TileX + 1 < MapAreaSize)
          Elev2 = Engine.GetCurrentMapArea()
                          .tiles[TileXI + 1][TileYI]
                          .elevation /
                      ElevAmount -
                  ElevPlayer;
        else if (TileY - 1 >= 0)
          Elev2 = Engine.GetCurrentMapArea()
                          .tiles[TileXI][TileYI - 1]
                          .elevation /
                      ElevAmount -
                  ElevPlayer;
        else
          Elev2 = Elev0;

        if (TileX + 1 >= 0 && TileY >= 0 && TileX + 1 < MapAreaSize &&
            TileY < MapAreaSize)
          Elev3 = Engine.GetCurrentMapArea()
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

        auto TileX0 = OffsetX + X * Engine.tileSize;
        auto TileY0 = Elev0;
        auto TileZ0 = OffsetY + Y * Engine.tileSize;
        auto TileX1 = OffsetX + X * Engine.tileSize;
        auto TileY1 = Elev1;
        auto TileZ1 = OffsetY + Y * Engine.tileSize - Engine.tileSize;
        auto TileX2 = OffsetX + X * Engine.tileSize + Engine.tileSize;
        auto TileY2 = Elev2;
        auto TileZ2 = OffsetY + Y * Engine.tileSize - Engine.tileSize;
        auto TileX3 = OffsetX + X * Engine.tileSize + Engine.tileSize;
        auto TileY3 = Elev3;
        auto TileZ3 = OffsetY + Y * Engine.tileSize;

        TileY0 = PlanetShaper.GetNewY(TileY0,
                                             static_cast<float>(TileXI),
                                             static_cast<float>(TileYI));
        TileY1 = PlanetShaper.GetNewY(TileY1,
                                             static_cast<float>(TileXI),
                                             static_cast<float>(TileYI) - 1);
        TileY2 = PlanetShaper.GetNewY(TileY2,
                                             static_cast<float>(TileXI) + 1,
                                             static_cast<float>(TileYI) - 1);
        TileY3 = PlanetShaper.GetNewY(TileY3,
                                             static_cast<float>(TileXI) + 1,
                                             static_cast<float>(TileYI));



        glDisable(GL_TEXTURE_2D);


if (Engine.GetCurrentMapArea()
        .tiles[TileXI][TileYI]
        .roof != nullptr) {

    auto& roof = Engine.GetCurrentMapArea()
            .tiles[TileXI][TileYI]
            .roof;


  auto RoofObject = roof->ObjectType;
  auto opacity = 1.0f;

  if (Engine.objectsContent.ObjectDescriptions.count(RoofObject))
      opacity = Engine.objectsContent.ObjectDescriptions.at(RoofObject).Opacity;

  Engine.DrawModel(RoofObject, TileX0 + Engine.tileSize / 2,
                   (TileY0 + TileY1 + TileY2 + TileY3) / 4.0f,
                   TileZ0 - Engine.tileSize / 2, roof->Rotation,
                   roof->Scaling, opacity);

}

      }
    }
}









}  // namespace Forradia
