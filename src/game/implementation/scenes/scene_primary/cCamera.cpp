
#include "cCamera.h"
#include "../engine/cEngine.h"

namespace Forradia
{

void cCamera::Update(int RotationDirection, float ZoomChange)
{
    if (Ticks() > TickLastUpdate + UpdateSpeed)
    {
        if (RotationDirection == GetId("Right"))
            LookingAngle -= RotationAmount;
        else if (RotationDirection == GetId("Left"))
            LookingAngle += RotationAmount;
        TickLastUpdate = Ticks();
    }

    ZoomAmount += ZoomChange * ZoomMultiplier / 100.0f;
    ZoomAmount = std::min(std::max(ZoomAmount, 0.5f), 15.0f);

    //-----------Ray Casting----------------

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, 1.333, 0.5, 100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    auto tile_size = 0.3;
    auto camera_x = 0.0f;
    auto camera_z = -1.0f;
    auto angle_radians = atan2(camera_z, camera_x) + LookingAngle / 180.0f * M_PI;
    auto camera_dist = 1;
    auto zoom = ZoomAmount;

    glTranslatef(0.0f, -zoom, -2.0f - zoom * 4.0f);
    camera_x = (float)cos(angle_radians) * camera_dist;
    camera_z = -(float)sin(angle_radians) * camera_dist;
    gluLookAt(camera_x, CameraHeight, camera_z, 0, -1, 0, 0, 1, 0);
    GLint viewport[4];                  // Where The Viewport Values Will Be Stored
    glGetIntegerv(GL_VIEWPORT, viewport);
    GLdouble modelview[16];
    glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
    GLdouble projection[16];                // Where The 16 Doubles Of The Projection Matrix Are To Be Stored
    glGetDoublev(GL_PROJECTION_MATRIX, projection);
    auto mouse_position = Utilities.GetMousePositionI();
    GLfloat win_x, win_y, win_z;               // Holds Our X, Y and Z Coordinates
    win_x = (float)mouse_position.X;                  // Holds The Mouse X Coordinate
    win_y = (float)mouse_position.Y;
    win_y = (float)viewport[3] - win_y;
    glReadPixels((GLint)win_x, (GLint)win_y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &win_z);
    GLdouble pos_x, pos_y, pos_z;
    gluUnProject(win_x, win_y, win_z, modelview, projection, viewport, &pos_x, &pos_y, &pos_z);

    RayCastingX = (float)pos_x;
    RayCastingY = (float)pos_y;
    RayCastingZ = (float)pos_z;
}

cPoint2 cCamera::GetHoveredTile()
{
    float sub_step_x = Engine.Player.Position.X - (int)Engine.Player.Position.X;
    float sub_step_y = Engine.Player.Position.Y - (int)Engine.Player.Position.Y;

    auto offset_x = -(double)(2 * RenderDistance + 1) / 2.0 * Engine.TileSize - sub_step_x * Engine.TileSize;
    auto offset_y = -(double)(2 * RenderDistance - 1) / 2.0 * Engine.TileSize - sub_step_y * Engine.TileSize;
    auto map_x = Engine.Player.Position.X - RenderDistance + (RayCastingX - offset_x) / Engine.TileSize;
    auto map_y = Engine.Player.Position.Y - RenderDistance + (RayCastingZ - offset_y) / Engine.TileSize + 1;

    return { (int)map_x, (int)map_y };
}

int cCamera::GetRenderDistance()
{
    auto& map_area = Engine.GetCurrentMapArea();

    if (map_area.IsUnderground())
        return RenderDistanceCave;
    else
        return RenderDistance;
}

void cCamera::UpdateCameraMovement()
{
    auto mouse_position = Utilities.GetMousePositionI();
    auto delta_mouse_x = mouse_position.X - PreviousMousePosition.X;

    if (Engine.MouseHandler.RightButtonDown)
        LookingAngle -= delta_mouse_x / 5.0f;

    auto delta_mouse_y = mouse_position.Y - PreviousMousePosition.Y;

    if (Engine.MouseHandler.RightButtonDown)
    {
        CameraHeight += delta_mouse_y / 100.0f;
        CameraHeight = std::max(std::min(CameraHeight, 2.0f), -1.0f);
    }

    PreviousMousePosition = mouse_position;
}

}
