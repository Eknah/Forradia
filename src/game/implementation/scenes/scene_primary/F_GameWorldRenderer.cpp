
#include "F_GameWorldRenderer.h"
#include "../core/F_Engine.h"

namespace Forradia
{

void F_GameWorldRenderer::Render()
{
    Background.Render(Camera.ZoomAmount);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, 1.333, 0.5, 100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    auto camera_x = 0.0f;
    auto camera_z = -1.0f;
    auto angle_radians = atan2(camera_z, camera_x) + Camera.LookingAngle / 180.0f * M_PI;
    auto camera_dist = 1;
    auto zoom = Camera.ZoomAmount;

    glTranslatef(0.0f, -zoom, -2.0f - zoom * 4.0f);
    camera_x = (float)cos(angle_radians) * camera_dist;
    camera_z = -(float)sin(angle_radians) * camera_dist;
    gluLookAt(camera_x, Camera.CameraHeight, camera_z, 0, -1, 0, 0, 1, 0);

    float sub_step_x = Engine.Player.Position.X - (int)Engine.Player.Position.X;
    float sub_step_y = Engine.Player.Position.Y - (int)Engine.Player.Position.Y;

    auto offset_x = -(float)(2.0f * Camera.GetRenderDistance() + 1.0f) / 2.0f * Engine.TileSize - sub_step_x * Engine.TileSize;
    auto offset_y = -(float)(2.0f * Camera.GetRenderDistance() - 1.0f) / 2.0f * Engine.TileSize - sub_step_y * Engine.TileSize;

    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);
    glDepthRange(0.0f, 1000.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glTranslatef(0.0, -2 + 2.0, 0.0);

    auto elev_amount = 5.0f;
    auto player_x_int = (int)Engine.Player.Position.X;
    auto player_y_int = (int)Engine.Player.Position.Y;
    auto elev_player_0 = Engine.GetCurrentMapArea().Tiles[player_x_int][player_y_int].Elevation / elev_amount;
    auto elev_player_1 = Engine.GetCurrentMapArea().Tiles[player_x_int + 1][player_y_int].Elevation / elev_amount;
    auto elev_player_2 = Engine.GetCurrentMapArea().Tiles[player_x_int + 1][player_y_int + 1].Elevation / elev_amount;
    auto elev_player_3 = Engine.GetCurrentMapArea().Tiles[player_x_int][player_y_int + 1].Elevation / elev_amount;
    auto elev_x = Engine.Player.Position.X - player_x_int;
    auto elev_y = Engine.Player.Position.Y - player_y_int;
    auto elev_player = (elev_player_0 + (elev_player_1 - elev_player_0) * elev_x + elev_player_3 + (elev_player_2 - elev_player_3) * elev_x + elev_player_0 + (elev_player_3 - elev_player_0) * elev_y + elev_player_1 + (elev_player_2 - elev_player_1) * elev_y) / 4.0f;
    auto map_area_size = Engine.WorldMap->MapAreaSize;

    for (auto y = 0; y < 2 * Camera.GetRenderDistance() + 1; y++)
    {
        for (auto x = 0; x < 2 * Camera.GetRenderDistance() + 1; x++)
        {
            auto dx = x - Camera.GetRenderDistance();
            auto dy = y - Camera.GetRenderDistance();

            if (dx * dx + dy * dy >= Camera.GetRenderDistance() * Camera.GetRenderDistance()) continue;

            auto map_x = Engine.Player.Position.X - Camera.GetRenderDistance() + x;
            auto map_y = Engine.Player.Position.Y - Camera.GetRenderDistance() + y;

            if (map_x < 0 || map_y < 0 || map_x >= map_area_size || map_y >= map_area_size) continue;

            auto groundtype_index = Engine.GetCurrentMapArea().Tiles[(int)map_x][(int)map_y].GroundType;
            auto water_anim_index_0 = 0;
            auto water_anim_index_1 = 0;
            auto water_anim_index_2 = 0;
            auto water_anim_index_3 = 0;

            if (groundtype_index == GetId("GroundtypeWater"))
            {
                water_anim_index_0 = ((Ticks() * 3 + ((int)map_x * (int)map_y) * 10) % 3600) / 1200;
                water_anim_index_1 = ((Ticks() * 3 + ((int)map_x * (int)(map_y - 1)) * 10) % 3600) / 1200;
                water_anim_index_2 = ((Ticks() * 3 + ((int)(map_x + 1) * (int)(map_y - 1)) * 10) % 3600) / 1200;
                water_anim_index_3 = ((Ticks() * 3 + ((int)(map_x + 1) * (int)map_y) * 10) % 3600) / 1200;
                if (water_anim_index_0 > 0)
                    groundtype_index = GetId("GroundtypeWater" + std::to_string(water_anim_index_0));
            }

            auto elev_0 = 0.0f;
            auto elev_1 = 0.0f;
            auto elev_2 = 0.0f;
            auto elev_3 = 0.0f;
            auto water_wave_height_0 = water_anim_index_0 * Engine.TileSize / 4.0f;
            auto water_wave_height_1 = water_anim_index_1 * Engine.TileSize / 4.0f;
            auto water_wave_height_2 = water_anim_index_2 * Engine.TileSize / 4.0f;
            auto water_wave_height_3 = water_anim_index_3 * Engine.TileSize / 4.0f;

            if (map_x >= 0 && map_y >= 0 && map_x < map_area_size && map_y < map_area_size)
                elev_0 = Engine.GetCurrentMapArea().Tiles[(int)map_x][(int)map_y].Elevation / elev_amount - elev_player;

            if (map_x >= 0 && map_y - 1 >= 0 && map_x < map_area_size && map_y - 1 < map_area_size)
                elev_1 = Engine.GetCurrentMapArea().Tiles[(int)map_x][(int)map_y - 1].Elevation / elev_amount - elev_player;
            else
                elev_1 = elev_0;

            if (map_x + 1 >= 0 && map_y - 1 >= 0 && map_x + 1 < map_area_size && map_y - 1 < map_area_size)
                elev_2 = Engine.GetCurrentMapArea().Tiles[(int)map_x + 1][(int)map_y - 1].Elevation / elev_amount - elev_player;
            else if (map_x + 1 < map_area_size)
                elev_2 = Engine.GetCurrentMapArea().Tiles[(int)map_x + 1][(int)map_y].Elevation / elev_amount - elev_player;
            else if (map_y - 1 >= 0)
                elev_2 = Engine.GetCurrentMapArea().Tiles[(int)map_x][(int)map_y - 1].Elevation / elev_amount - elev_player;
            else
                elev_2 = elev_0;

            if (map_x + 1 >= 0 && map_y >= 0 && map_x + 1 < map_area_size && map_y < map_area_size)
                elev_3 = Engine.GetCurrentMapArea().Tiles[(int)map_x + 1][(int)map_y].Elevation / elev_amount - elev_player;
            else
                elev_3 = elev_0;

            auto slope = elev_3 - elev_0 + elev_0 - elev_1;
            auto r = 0.85f;
            auto g = 0.85f;
            auto b = 0.85f;

            if (slope < 0)
            {
                r = 0.7f;
                g = 0.7f;
                b = 0.7f;
            }
            else if (slope > 0)
            {
                r = 1.0f;
                g = 1.0f;
                b = 1.0f;
            }

            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, Engine.ImageLoader.Images[groundtype_index]);

            auto tile_x_0 = offset_x + x * Engine.TileSize;
            auto tile_y_0 = elev_0;
            auto tile_z_0 = offset_y + y * Engine.TileSize;
            auto tile_x_1 = offset_x + x * Engine.TileSize;
            auto tile_y_1 = elev_1;
            auto tile_z_1 = offset_y + y * Engine.TileSize - Engine.TileSize;
            auto tile_x_2 = offset_x + x * Engine.TileSize + Engine.TileSize;
            auto tile_y_2 = elev_2;
            auto tile_z_2 = offset_y + y * Engine.TileSize - Engine.TileSize;
            auto tile_x_3 = offset_x + x * Engine.TileSize + Engine.TileSize;
            auto tile_y_3 = elev_3;
            auto tile_z_3 = offset_y + y * Engine.TileSize;

            tile_y_0 = PlanetTransformator.GetNewY(tile_y_0, (float)(int)map_x, (float)(int)map_y);
            tile_y_1 = PlanetTransformator.GetNewY(tile_y_1, (float)(int)map_x, (float)(int)map_y - 1);
            tile_y_2 = PlanetTransformator.GetNewY(tile_y_2, (float)(int)map_x + 1, (float)(int)map_y - 1);
            tile_y_3 = PlanetTransformator.GetNewY(tile_y_3, (float)(int)map_x + 1, (float)(int)map_y);

            glBegin(GL_QUADS);
            glColor3f(r, g, b);
            glTexCoord2f(0, 0); glVertex3f(tile_x_0, tile_y_0, tile_z_0);
            glTexCoord2f(1, 0); glVertex3f(tile_x_1, tile_y_1, tile_z_1);
            glTexCoord2f(1, 1); glVertex3f(tile_x_2, tile_y_2, tile_z_2);
            glTexCoord2f(0, 1); glVertex3f(tile_x_3, tile_y_3, tile_z_3);
            glEnd();

            if (water_anim_index_0 > 0)
            {
                glBegin(GL_QUADS);
                glColor3f(r, g, b);
                glTexCoord2f(0, 0); glVertex3f(tile_x_0, tile_y_0 + water_wave_height_0, tile_z_0);
                glTexCoord2f(1, 0); glVertex3f(tile_x_1, tile_y_1 + water_wave_height_1, tile_z_1);
                glTexCoord2f(1, 1); glVertex3f(tile_x_2, tile_y_2 + water_wave_height_2, tile_z_2);
                glTexCoord2f(0, 1); glVertex3f(tile_x_3, tile_y_3 + water_wave_height_3, tile_z_3);
                glEnd();
            }

            if (Engine.GetCurrentMapArea().Tiles[(int)map_x][(int)map_y].Objects.size() > 0)
            {
                glBindTexture(GL_TEXTURE_2D, Engine.ImageLoader.Images[GetId("TileShadow")]);
                glBegin(GL_QUADS);
                glColor3f(r, g, b);
                glTexCoord2f(0, 0); glVertex3f(tile_x_0, tile_y_0, tile_z_0);
                glTexCoord2f(1, 0); glVertex3f(tile_x_1, tile_y_1, tile_z_1);
                glTexCoord2f(1, 1); glVertex3f(tile_x_2, tile_y_2, tile_z_2);
                glTexCoord2f(0, 1); glVertex3f(tile_x_3, tile_y_3, tile_z_3);
                glEnd();
            }

            auto hovered_x = Camera.GetHoveredTile().X;
            auto hovered_y = Camera.GetHoveredTile().Y;

            if (hovered_x == (int)map_x && hovered_y == (int)map_y && Engine.CustomCursor.CursorType != F_ECursorTypes::Hidden)
            {
                glBindTexture(GL_TEXTURE_2D, Engine.ImageLoader.Images[GetId("TileHovering")]);
                glBegin(GL_QUADS);
                auto left = offset_x + x * Engine.TileSize;
                auto top = offset_y + y * Engine.TileSize - Engine.TileSize;
                auto right = offset_x + x * Engine.TileSize + Engine.TileSize;
                auto bottom = offset_y + y * Engine.TileSize;
                glColor3f(1.0f, 1.0f, 1.0f);
                glTexCoord2f(0, 0); glVertex3f(tile_x_0, tile_y_0, tile_z_0);
                glTexCoord2f(1, 0); glVertex3f(tile_x_1, tile_y_1, tile_z_1);
                glTexCoord2f(1, 1); glVertex3f(tile_x_2, tile_y_2, tile_z_2);
                glTexCoord2f(0, 1); glVertex3f(tile_x_3, tile_y_3, tile_z_3);
                glEnd();
            }

            glDisable(GL_TEXTURE_2D);

            for (auto& object : Engine.GetCurrentMapArea().Tiles[(int)map_x][(int)map_y].Objects)
            {
                auto tile_object = object->ObjectType;

                if (tile_object != 0)
                    Engine.DrawModel(tile_object,tile_x_0 + Engine.TileSize / 2, (tile_y_0 + tile_y_1 + tile_y_2 + tile_y_3)/4.0f, tile_z_0 - Engine.TileSize / 2, object->Rotation, object->Scaling);
            }

            if (Engine.GetCurrentMapArea().Tiles[(int)map_x][(int)map_y].mob != nullptr)
            {
                auto sub_x_pos = (Engine.GetCurrentMapArea().Tiles[(int)map_x][(int)map_y].mob->Position.X - int(Engine.GetCurrentMapArea().Tiles[(int)map_x][(int)map_y].mob->Position.X)) * Engine.TileSize;
                auto sub_y_pos = (Engine.GetCurrentMapArea().Tiles[(int)map_x][(int)map_y].mob->Position.Y - int(Engine.GetCurrentMapArea().Tiles[(int)map_x][(int)map_y].mob->Position.Y)) * Engine.TileSize;

                Engine.DrawModel(GetId("MobRabbit"), tile_x_0 + sub_x_pos, (tile_y_0 + tile_y_1 + tile_y_2 + tile_y_3) / 4.0f, tile_z_0 - Engine.TileSize + sub_y_pos, Engine.GetCurrentMapArea().Tiles[(int)map_x][(int)map_y].mob->FacingAngle);
            }
        }
    }

    auto player_x0 = offset_x + Camera.GetRenderDistance() * Engine.TileSize + Engine.TileSize + sub_step_x * Engine.TileSize;
    auto player_y0 = 0.0f + Engine.Player.GetModule<F_ModuleJumping>().PositionZ;
    auto player_z0 = offset_y + Camera.GetRenderDistance() * Engine.TileSize - Engine.TileSize + sub_step_y * Engine.TileSize;

    auto player_x1 = offset_x + Camera.GetRenderDistance() * Engine.TileSize + Engine.TileSize + sub_step_x * Engine.TileSize - Engine.TileSize;
    auto player_y1 = 0.0f + Engine.Player.GetModule<F_ModuleJumping>().PositionZ;
    auto player_z1 = offset_y + Camera.GetRenderDistance() * Engine.TileSize - Engine.TileSize + sub_step_y * Engine.TileSize;

    auto player_x2 = offset_x + Camera.GetRenderDistance() * Engine.TileSize + Engine.TileSize + sub_step_x * Engine.TileSize - Engine.TileSize;
    auto player_y2 = 0.0f + Engine.Player.GetModule<F_ModuleJumping>().PositionZ;
    auto player_z2 = offset_y + Camera.GetRenderDistance() * Engine.TileSize - Engine.TileSize + sub_step_y * Engine.TileSize + Engine.TileSize;

    auto player_x3 = offset_x + Camera.GetRenderDistance() * Engine.TileSize + Engine.TileSize + sub_step_x * Engine.TileSize;
    auto player_y3 = 0.0f + Engine.Player.GetModule<F_ModuleJumping>().PositionZ;
    auto player_z3 = offset_y + Camera.GetRenderDistance() * Engine.TileSize - Engine.TileSize + sub_step_y * Engine.TileSize + Engine.TileSize;

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, Engine.ImageLoader.Images[GetId("TileShadow")]);
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glTexCoord2f(0, 0); glVertex3f(player_x0, player_y0, player_z0);
    glTexCoord2f(1, 0); glVertex3f(player_x1, player_y1, player_z1);
    glTexCoord2f(1, 1); glVertex3f(player_x2, player_y2, player_z2);
    glTexCoord2f(0, 1); glVertex3f(player_x3, player_y3, player_z3);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    auto mode_name_player = std::string("Player");

    if (Engine.Player.GetModule<F_ModuleMovement>().IsWalking)
    {
        auto animIndex = (Ticks() % 300) / 75;
        if (animIndex > 0)
            mode_name_player.append(std::to_string(animIndex));
    }

    Engine.DrawModel(mode_name_player, offset_x + Camera.GetRenderDistance() * Engine.TileSize + Engine.TileSize / 2.0f + sub_step_x * Engine.TileSize, 0.0f + Engine.Player.GetModule<F_ModuleJumping>().PositionZ, offset_y + Camera.GetRenderDistance() * Engine.TileSize - Engine.TileSize / 2.0f + sub_step_y * Engine.TileSize, Engine.Player.GetModule<F_ModuleMovement>().FacingAngleRotated);

    glPopMatrix();
    glDisable(GL_DEPTH_TEST);
}

}
