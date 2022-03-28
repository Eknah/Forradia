// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include <string>
#include "cGameWorldRenderer.h"
#include "../engine/cEngine.h"

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

  gluLookAt(CameraX, Camera.CameraHeight, CameraZ, 0, -1, 0, 0, 1, 0);

  float SubStepX = Engine.Player.Position.X -
          static_cast<int>(Engine.Player.Position.X);

  float SubStepY = Engine.Player.Position.Y -
          static_cast<int>(Engine.Player.Position.Y);

  auto OffsetX = -static_cast<float>(2.0f * Camera.GetRenderDistance() + 1.0f)
          / 2.0f * Engine.TileSize - SubStepX * Engine.TileSize;
  auto OffsetY = -static_cast<float>(2.0f * Camera.GetRenderDistance() - 1.0f)
          / 2.0f * Engine.TileSize - SubStepY * Engine.TileSize;

  glEnable(GL_DEPTH_TEST);
  glDepthMask(GL_TRUE);
  glDepthFunc(GL_LEQUAL);
  glDepthRange(0.0f, 1000.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glPushMatrix();
  glTranslatef(0.0, -2 + 2.0, 0.0);

  auto ElevAmount = 5.0f;
  auto PlayerXInt = static_cast<int>(Engine.Player.Position.X);
  auto PlayerYInt = static_cast<int>(Engine.Player.Position.Y);
  auto ElevPlayer0 =
      Engine.GetCurrentMapArea().Tiles[PlayerXInt][PlayerYInt].Elevation /
      ElevAmount;
  auto ElevPlayer1 =
      Engine.GetCurrentMapArea().Tiles[PlayerXInt + 1][PlayerYInt].Elevation /
      ElevAmount;
  auto ElevPlayer2 = Engine.GetCurrentMapArea()
                         .Tiles[PlayerXInt + 1][PlayerYInt + 1]
                         .Elevation /
                     ElevAmount;
  auto ElevPlayer3 =
      Engine.GetCurrentMapArea().Tiles[PlayerXInt][PlayerYInt + 1].Elevation /
      ElevAmount;
  auto ElevX = Engine.Player.Position.X - PlayerXInt;
  auto ElevY = Engine.Player.Position.Y - PlayerYInt;
  auto ElevPlayer = (ElevPlayer0 + (ElevPlayer1 - ElevPlayer0) * ElevX +
                     ElevPlayer3 + (ElevPlayer2 - ElevPlayer3) * ElevX +
                     ElevPlayer0 + (ElevPlayer3 - ElevPlayer0) * ElevY +
                     ElevPlayer1 + (ElevPlayer2 - ElevPlayer1) * ElevY) /
                    4.0f;
  auto MapAreaSize = Engine.WorldMap->MapAreaSize;

  for (auto Y = 0; Y < 2 * Camera.GetRenderDistance() + 1; Y++) {
    for (auto X = 0; X < 2 * Camera.GetRenderDistance() + 1; X++) {
      auto DX = X - Camera.GetRenderDistance();
      auto DY = Y - Camera.GetRenderDistance();

      if (DX * DX + DY * DY >=
          Camera.GetRenderDistance() * Camera.GetRenderDistance())
        continue;

      auto TileX = Engine.Player.Position.X - Camera.GetRenderDistance() + X;
      auto TileY = Engine.Player.Position.Y - Camera.GetRenderDistance() + Y;

      if (TileX < 0 || TileY < 0 || TileX >= MapAreaSize ||
          TileY >= MapAreaSize)
        continue;

      auto TileXI = static_cast<int>(TileX);
      auto TileYI = static_cast<int>(TileY);

      auto GroundTypeId =
          Engine.GetCurrentMapArea().Tiles[TileXI][TileYI].GroundType;

      auto WaterAnimIndex0 = 0;
      auto WaterAnimIndex1 = 0;
      auto WaterAnimIndex2 = 0;
      auto WaterAnimIndex3 = 0;

      if (GroundTypeId == GetId("GroundtypeWater")) {
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
              GetId("GroundtypeWater" + std::to_string(WaterAnimIndex0));
      }

      auto Elev0 = 0.0f;
      auto Elev1 = 0.0f;
      auto Elev2 = 0.0f;
      auto Elev3 = 0.0f;

      auto WaterWaveHeight0 = WaterAnimIndex0 * Engine.TileSize / 4.0f;
      auto WaterWaveHeight1 = WaterAnimIndex1 * Engine.TileSize / 4.0f;
      auto WaterWaveHeight2 = WaterAnimIndex2 * Engine.TileSize / 4.0f;
      auto WaterWaveHeight3 = WaterAnimIndex3 * Engine.TileSize / 4.0f;

      if (TileX >= 0 && TileY >= 0 && TileX < MapAreaSize &&
          TileY < MapAreaSize)
        Elev0 =
            Engine.GetCurrentMapArea().Tiles[TileXI][TileYI].Elevation /
                ElevAmount -
            ElevPlayer;

      if (TileX >= 0 && TileY - 1 >= 0 && TileX < MapAreaSize &&
          TileY - 1 < MapAreaSize)
        Elev1 = Engine.GetCurrentMapArea()
                        .Tiles[TileXI][TileYI - 1]
                        .Elevation /
                    ElevAmount -
                ElevPlayer;
      else
        Elev1 = Elev0;

      if (TileX + 1 >= 0 && TileY - 1 >= 0 && TileX + 1 < MapAreaSize &&
          TileY - 1 < MapAreaSize)
        Elev2 = Engine.GetCurrentMapArea()
                        .Tiles[TileXI + 1][TileYI - 1]
                        .Elevation /
                    ElevAmount -
                ElevPlayer;
      else if (TileX + 1 < MapAreaSize)
        Elev2 = Engine.GetCurrentMapArea()
                        .Tiles[TileXI + 1][TileYI]
                        .Elevation /
                    ElevAmount -
                ElevPlayer;
      else if (TileY - 1 >= 0)
        Elev2 = Engine.GetCurrentMapArea()
                        .Tiles[TileXI][TileYI - 1]
                        .Elevation /
                    ElevAmount -
                ElevPlayer;
      else
        Elev2 = Elev0;

      if (TileX + 1 >= 0 && TileY >= 0 && TileX + 1 < MapAreaSize &&
          TileY < MapAreaSize)
        Elev3 = Engine.GetCurrentMapArea()
                        .Tiles[TileXI + 1][TileYI]
                        .Elevation /
                    ElevAmount -
                ElevPlayer;
      else
        Elev3 = Elev0;

      auto Slope = Elev3 - Elev0 + Elev0 - Elev1;

      auto R = 0.85f;
      auto G = 0.85f;
      auto B = 0.85f;

      if (Slope < 0) {
        R = 0.7f;
        G = 0.7f;
        B = 0.7f;
      } else if (Slope > 0) {
        R = 1.0f;
        G = 1.0f;
        B = 1.0f;
      }

      glEnable(GL_TEXTURE_2D);
      glBindTexture(GL_TEXTURE_2D, Engine.ImageLoader.Images.at(GroundTypeId));

      auto TileX0 = OffsetX + X * Engine.TileSize;
      auto TileY0 = Elev0;
      auto TileZ0 = OffsetY + Y * Engine.TileSize;
      auto TileX1 = OffsetX + X * Engine.TileSize;
      auto TileY1 = Elev1;
      auto TileZ1 = OffsetY + Y * Engine.TileSize - Engine.TileSize;
      auto TileX2 = OffsetX + X * Engine.TileSize + Engine.TileSize;
      auto TileY2 = Elev2;
      auto TileZ2 = OffsetY + Y * Engine.TileSize - Engine.TileSize;
      auto TileX3 = OffsetX + X * Engine.TileSize + Engine.TileSize;
      auto TileY3 = Elev3;
      auto TileZ3 = OffsetY + Y * Engine.TileSize;

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

      if (Engine.GetCurrentMapArea()
              .Tiles[TileXI][TileYI]
              .Objects.size() > 0) {
        glBindTexture(GL_TEXTURE_2D,
                      Engine.ImageLoader.Images.at(GetId("TileShadow")));

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

      auto HoveredX = Camera.GetHoveredTile().X;
      auto HoveredY = Camera.GetHoveredTile().Y;

      if (HoveredX == TileXI && HoveredY == TileYI &&
          Engine.CustomCursor.CursorType != eCursorTypes::Hidden) {
        glBindTexture(GL_TEXTURE_2D,
                      Engine.ImageLoader.Images.at(GetId("TileHovering")));

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

      glDisable(GL_TEXTURE_2D);

      for (auto &Object :
           Engine.GetCurrentMapArea().Tiles[TileXI][TileYI].Objects) {
        auto TileObject = Object->ObjectType;

        if (TileObject != 0)
          Engine.DrawModel(TileObject, TileX0 + Engine.TileSize / 2,
                           (TileY0 + TileY1 + TileY2 + TileY3) / 4.0f,
                           TileZ0 - Engine.TileSize / 2, Object->Rotation,
                           Object->Scaling);
      }

      if (Engine.GetCurrentMapArea().Tiles[TileXI][TileYI].Mob !=
          nullptr) {
        auto SubXPos = (Engine.GetCurrentMapArea()
                            .Tiles[TileXI][TileYI]
                            .Mob->Position.X -
                        static_cast<int>(Engine.GetCurrentMapArea()
                                .Tiles[TileXI][TileYI]
                                .Mob->Position.X)) *
                       Engine.TileSize;
        auto SubYPos = (Engine.GetCurrentMapArea()
                            .Tiles[TileXI][TileYI]
                            .Mob->Position.Y -
                        static_cast<int>(Engine.GetCurrentMapArea()
                                .Tiles[TileXI][TileYI]
                                .Mob->Position.Y)) *
                       Engine.TileSize;

        Engine.DrawModel(Engine.GetCurrentMapArea()
                         .Tiles[TileXI][TileYI]
                         .Mob->ModelId, TileX0 + SubXPos,
                         (TileY0 + TileY1 + TileY2 + TileY3) / 4.0f,
                         TileZ0 - Engine.TileSize + SubYPos,
                         Engine.GetCurrentMapArea()
                             .Tiles[TileXI][TileYI]
                             .Mob->FacingAngle);
      }
    }
  }

  auto PlayerX0 = OffsetX + Camera.GetRenderDistance() * Engine.TileSize +
                  Engine.TileSize + SubStepX * Engine.TileSize;
  auto PlayerY0 = 0.0f + Engine.Player.GetModule<cModuleJumping>().PositionZ;
  auto PlayerZ0 = OffsetY + Camera.GetRenderDistance() * Engine.TileSize -
                  Engine.TileSize + SubStepY * Engine.TileSize;

  auto PlayerX1 = OffsetX + Camera.GetRenderDistance() * Engine.TileSize +
                  Engine.TileSize + SubStepX * Engine.TileSize -
                  Engine.TileSize;
  auto PlayerY1 = 0.0f + Engine.Player.GetModule<cModuleJumping>().PositionZ;
  auto PlayerZ1 = OffsetY + Camera.GetRenderDistance() * Engine.TileSize -
                  Engine.TileSize + SubStepY * Engine.TileSize;

  auto PlayerX2 = OffsetX + Camera.GetRenderDistance() * Engine.TileSize +
                  Engine.TileSize + SubStepX * Engine.TileSize -
                  Engine.TileSize;
  auto PlayerY2 = 0.0f + Engine.Player.GetModule<cModuleJumping>().PositionZ;
  auto PlayerZ2 = OffsetY + Camera.GetRenderDistance() * Engine.TileSize -
                  Engine.TileSize + SubStepY * Engine.TileSize +
                  Engine.TileSize;

  auto PlayerX3 = OffsetX + Camera.GetRenderDistance() * Engine.TileSize +
                  Engine.TileSize + SubStepX * Engine.TileSize;
  auto PlayerY3 = 0.0f + Engine.Player.GetModule<cModuleJumping>().PositionZ;
  auto PlayerZ3 = OffsetY + Camera.GetRenderDistance() * Engine.TileSize -
                  Engine.TileSize + SubStepY * Engine.TileSize +
                  Engine.TileSize;

  glEnable(GL_TEXTURE_2D);

  glBindTexture(GL_TEXTURE_2D,
                Engine.ImageLoader.Images.at(GetId("TileShadow")));

  glBegin(GL_QUADS);

  glColor3f(1, 1, 1);

  glTexCoord2f(0, 0);
  glVertex3f(PlayerX0, PlayerY0, PlayerZ0);
  glTexCoord2f(1, 0);
  glVertex3f(PlayerX1, PlayerY1, PlayerZ1);
  glTexCoord2f(1, 1);
  glVertex3f(PlayerX2, PlayerY2, PlayerZ2);
  glTexCoord2f(0, 1);
  glVertex3f(PlayerX3, PlayerY3, PlayerZ3);

  glEnd();

  glDisable(GL_TEXTURE_2D);

  auto ModelNamePlayer = std::string("Player");

  if (Engine.Player.GetModule<cModuleMovement>().IsWalking) {
    auto AnimIndex = (Ticks() % 300) / 75;

    if (AnimIndex > 0)
      ModelNamePlayer.append(std::to_string(AnimIndex));
  }

  Engine.DrawModel(
      ModelNamePlayer,
      OffsetX + Camera.GetRenderDistance() * Engine.TileSize +
          Engine.TileSize / 2.0f + SubStepX * Engine.TileSize,
      0.0f + Engine.Player.GetModule<cModuleJumping>().PositionZ,
      OffsetY + Camera.GetRenderDistance() * Engine.TileSize -
          Engine.TileSize / 2.0f + SubStepY * Engine.TileSize,
      Engine.Player.GetModule<cModuleMovement>().FacingAngleRotated);

  glPopMatrix();
  glDisable(GL_DEPTH_TEST);
}

}  // namespace Forradia
