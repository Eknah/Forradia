#include "CommonExternal.h"
#include "CPlayer.h"
#include "../Hidden/CEngine.h"

namespace Forradia
{

void CPlayer::Jump()
{
    IsJumping = true;
    TickStartJumping = Ticks();
}

void CPlayer::ResetForNewFrame()
{
    IsWalking = false;
    FacingAngleRotated = FacingAngle;
}

void CPlayer::UpdateDestMovement()
{
    if (!(Ticks() > TickLastMove + MoveSpeed && MoveDestination.X != -1 && MoveDestination.Y != -1)) return;

    auto dx = MoveDestination.X - Position.X;
    auto dy = MoveDestination.Y - Position.Y;
    auto abs_dx = std::abs(dx);
    auto abs_dy = std::abs(dy);

    if (abs_dx < StepMultiplier && abs_dy < StepMultiplier)
    {
        MoveDestination = { -1, -1 };
    }
    else
    {
        IsWalking = true;
        FacingAngle = std::atan2(-dx, -dy) / M_PI * 180.0f;

        auto angle = FacingAngle / 180.0f * M_PI - M_PI / 2 + 0 * M_PI / 2;
        auto dx = -std::cos(angle) * StepMultiplier;
        auto dy = std::sin(angle) * StepMultiplier;
        auto new_x = Position.X + dx * StepSize;
        auto new_y = Position.Y + dy * StepSize;

        if (new_x < 0)
            new_x += Engine.GetCurrentMapArea().Size;
        if (new_y < 0)
            new_y += Engine.GetCurrentMapArea().Size;
        if (new_x >= Engine.GetCurrentMapArea().Size)
            new_x -= Engine.GetCurrentMapArea().Size;
        if (new_y >= Engine.GetCurrentMapArea().Size)
            new_y -= Engine.GetCurrentMapArea().Size;

        auto new_x_rounded = int(std::round(new_x));
        auto new_y_rounded = int(std::round(new_y));

        if (!Engine.GetCurrentMapArea().Tiles[new_x_rounded][new_y_rounded].MovementBlocked())
        {
            Position.X = new_x;
            Position.Y = new_y;
        }

        if (Engine.GetCurrentMapArea().Tiles[int(new_x)][int(new_y)].WarpToMap != -1)
        {
            CurrentMapArea = Engine.GetCurrentMapArea().Tiles[int(new_x)][int(new_y)].WarpToMap;
            auto angle = FacingAngle / 180.0f * M_PI - M_PI / 2 + 0 * M_PI / 2;
            auto dx = -std::cos(angle) * StepMultiplier;
            auto dy = std::sin(angle) * StepMultiplier;
            new_x += dx * StepSize * 10;
            new_y += dy * StepSize * 10;
            Position.X = new_x;
            Position.Y = new_y;
        }
    }

    TickLastMove = Ticks();
}

void CPlayer::UpdateKboardMovement(MovementInstruction instr)
{
    if (!(Ticks() > TickLastMove + MoveSpeed && (instr.TryMoveForward || instr.TryMoveRight || instr.TryMoveBack || instr.TryMoveLeft))) return;

    IsWalking = true;

    auto new_x = Position.X;
    auto new_y = Position.Y;
    auto angle = 0.0f;

    if (instr.TryMoveForward)
    {
        angle = FacingAngle / 180.0f * M_PI - M_PI / 2 + 0 * M_PI / 2;
    }

    if (instr.TryMoveLeft)
    {
        angle = FacingAngle / 180.0f * M_PI - M_PI / 2 + 1 * M_PI / 2;
        FacingAngleRotated = FacingAngle + 1 * 90.0f;
    }

    if (instr.TryMoveBack)
    {
        angle =
                FacingAngle / 180.0f * M_PI - M_PI / 2 + 2 * M_PI / 2;
    }

    if (instr.TryMoveRight)
    {
        angle = FacingAngle / 180.0f * M_PI - M_PI / 2 + 3 * M_PI / 2;
        FacingAngleRotated = FacingAngle + 3 * 90.0f;
    }

    auto dx = -std::cos(angle) * StepMultiplier;
    auto dy = std::sin(angle) * StepMultiplier;

    new_x += dx * StepSize;
    new_y += dy * StepSize;

    if (new_x < 0)
        new_x += Engine.GetCurrentMapArea().Size;

    if (new_y < 0)
        new_y += Engine.GetCurrentMapArea().Size;

    if (new_x >= Engine.GetCurrentMapArea().Size)
        new_x -= Engine.GetCurrentMapArea().Size;

    if (new_y >= Engine.GetCurrentMapArea().Size)
        new_y -= Engine.GetCurrentMapArea().Size;

    auto new_x_rounded = int(std::round(new_x));
    auto new_y_rounded = int(std::round(new_y));

    if (!Engine.GetCurrentMapArea().Tiles[new_x_rounded][new_y_rounded].MovementBlocked())
    {
        Position.X = new_x;
        Position.Y = new_y;
    }

    if (Engine.GetCurrentMapArea().Tiles[int(new_x)][int(new_y)].WarpToMap != -1)
    {
        Engine.Player.CurrentMapArea = Engine.GetCurrentMapArea().Tiles[int(new_x)][int(new_y)].WarpToMap;
        auto angle = FacingAngle / 180.0f * M_PI - M_PI / 2 + 0 * M_PI / 2;
        auto dx = -std::cos(angle) * StepMultiplier;
        auto dy = std::sin(angle) * StepMultiplier;
        new_x += dx * StepSize * 10;
        new_y += dy * StepSize * 10;
        Position.X = new_x;
        Position.Y = new_y;
    }

    TickLastMove = Ticks();
}

void CPlayer::UpdateRotation(float newFacingAngle)
{
    FacingAngle = newFacingAngle;
}

void CPlayer::UpdateJumping()
{
    if (IsJumping)
    {
        auto delta_ticks = Ticks() - TickStartJumping;
        auto jump_height = std::pow((-std::pow((delta_ticks - JumpDuration / 2.0f), 2.0f) + 250000.0f) / 250000.0f, 3.0f) * MaxJumpHeight;
        PositionZ = jump_height;
    }
    if (Ticks() > TickStartJumping + JumpDuration)
    {
        PositionZ = 0.0f;
        IsJumping = false;
    }
}

}
