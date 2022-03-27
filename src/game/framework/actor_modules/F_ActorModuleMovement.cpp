
#include "F_ActorModuleMovement.h"
#include "../core/Aliases.h"
#include "../core/F_IEngine.h"
#include "framework/F_Actor.h"

namespace Forradia
{

void F_ActorModuleMovement::ResetForNewFrame()
{
    IsWalking = false;
    FacingAngleRotated = FacingAngle;
}

void F_ActorModuleMovement::Update()
{
    UpdateDirectionalMovement();
    UpdateDestinationMovement();
}

void F_ActorModuleMovement::UpdateDirectionalMovement()
{
    if (!(Ticks() > TickLastMove + MoveSpeed && (Instruction.TryMoveForward || Instruction.TryMoveRight || Instruction.TryMoveBack || Instruction.TryMoveLeft))) return;

    IsWalking = true;

    auto new_x = ParentActor.Position.X;
    auto new_y = ParentActor.Position.Y;
    auto angle = 0.0f;

    if (Instruction.TryMoveForward)
    {
        angle = FacingAngle / 180.0f * M_PI - M_PI / 2 + 0 * M_PI / 2;
    }

    if (Instruction.TryMoveLeft)
    {
        angle = FacingAngle / 180.0f * M_PI - M_PI / 2 + 1 * M_PI / 2;
        FacingAngleRotated = FacingAngle + 1 * 90.0f;
    }

    if (Instruction.TryMoveBack)
    {
        angle =
                FacingAngle / 180.0f * M_PI - M_PI / 2 + 2 * M_PI / 2;
    }

    if (Instruction.TryMoveRight)
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
        ParentActor.Position.X = new_x;
        ParentActor.Position.Y = new_y;
    }

    if (Engine.GetCurrentMapArea().Tiles[int(new_x)][int(new_y)].WarpToMap != -1)
    {
        ParentActor.CurrentMapArea = Engine.GetCurrentMapArea().Tiles[int(new_x)][int(new_y)].WarpToMap;
        auto angle = FacingAngle / 180.0f * M_PI - M_PI / 2 + 0 * M_PI / 2;
        auto dx = -std::cos(angle) * StepMultiplier;
        auto dy = std::sin(angle) * StepMultiplier;
        new_x += dx * StepSize * 10;
        new_y += dy * StepSize * 10;
        ParentActor.Position.X = new_x;
        ParentActor.Position.Y = new_y;
    }

    TickLastMove = Ticks();
}

void F_ActorModuleMovement::UpdateDestinationMovement()
{
    if (!(Ticks() > TickLastMove + MoveSpeed && MoveDestination.X != -1 && MoveDestination.Y != -1)) return;

    auto dx = MoveDestination.X - ParentActor.Position.X;
    auto dy = MoveDestination.Y - ParentActor.Position.Y;
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
        auto new_x = ParentActor.Position.X + dx * StepSize;
        auto new_y = ParentActor.Position.Y + dy * StepSize;

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
            ParentActor.Position.X = new_x;
            ParentActor.Position.Y = new_y;
        }

        if (Engine.GetCurrentMapArea().Tiles[int(new_x)][int(new_y)].WarpToMap != -1)
        {
            ParentActor.CurrentMapArea = Engine.GetCurrentMapArea().Tiles[int(new_x)][int(new_y)].WarpToMap;
            auto angle = FacingAngle / 180.0f * M_PI - M_PI / 2 + 0 * M_PI / 2;
            auto dx = -std::cos(angle) * StepMultiplier;
            auto dy = std::sin(angle) * StepMultiplier;
            new_x += dx * StepSize * 10;
            new_y += dy * StepSize * 10;
            ParentActor.Position.X = new_x;
            ParentActor.Position.Y = new_y;
        }
    }

    TickLastMove = Ticks();
}

}
