#include "CommonExternal.h"
#include "CMobsEngine.h"
#include "../Hidden/CEngine.h"
namespace Forradia
{
void CMobsEngine::Update()
{
    for (auto i = 0; i < Engine.GetCurrentMapArea().MobsMirror.size(); i++)
    {
        if (i >= Engine.GetCurrentMapArea().MobsMirror.size()) break;
        auto x = int(Engine.GetCurrentMapArea().MobsMirror.at(i).get()->Position.X);
        auto y = int(Engine.GetCurrentMapArea().MobsMirror.at(i).get()->Position.Y);
        if (Ticks() > Engine.GetCurrentMapArea().Tiles[x][y].mob->TickLastMove + Engine.GetCurrentMapArea().Tiles[x][y].mob->MoveSpeed)
        {
            Engine.GetCurrentMapArea().Tiles[x][y].mob->TickLastMove = Ticks();
            if (Engine.GetCurrentMapArea().Tiles[x][y].mob->MoveDestination.X == -1 || Engine.GetCurrentMapArea().Tiles[x][y].mob->MoveDestination.Y == -1)
            {
                auto destination_x = Engine.GetCurrentMapArea().Tiles[x][y].mob->Position.X + rand() % 15 - rand() % 15;
                auto destination_y = Engine.GetCurrentMapArea().Tiles[x][y].mob->Position.Y + rand() % 15 - rand() % 15;
                destination_x = std::min(std::max(destination_x, 0.0f), float(Engine.WorldMap->MapAreaSize) - 1.0f);
                destination_y = std::min(std::max(destination_y, 0.0f), float(Engine.WorldMap->MapAreaSize) - 1.0f);
                Engine.GetCurrentMapArea().Tiles[x][y].mob->MoveDestination = { destination_x, destination_y };
            }
            auto delta_x = Engine.GetCurrentMapArea().Tiles[x][y].mob->MoveDestination.X - Engine.GetCurrentMapArea().Tiles[x][y].mob->Position.X;
            auto delta_y = Engine.GetCurrentMapArea().Tiles[x][y].mob->MoveDestination.Y - Engine.GetCurrentMapArea().Tiles[x][y].mob->Position.Y;
            auto distance = std::sqrt(delta_x * delta_x + delta_y * delta_y);
            if (distance < 1)
            {
                Engine.GetCurrentMapArea().Tiles[x][y].mob->MoveDestination = { -1, -1 };
                continue;
            }
            Engine.GetCurrentMapArea().Tiles[x][y].mob->FacingAngle = std::atan2(-delta_x, -delta_y) / M_PI * 180.0f;
            auto angle = Engine.GetCurrentMapArea().Tiles[x][y].mob->FacingAngle / 180.0f * M_PI - M_PI / 2 + M_PI;
            auto dx = -std::cos(angle) * Engine.GetCurrentMapArea().Tiles[x][y].mob->StepMultiplier;
            auto dy = std::sin(angle) * Engine.GetCurrentMapArea().Tiles[x][y].mob->StepMultiplier;
            auto new_x = float(Engine.GetCurrentMapArea().Tiles[x][y].mob->Position.X + dx * Engine.GetCurrentMapArea().Tiles[x][y].mob->StepSize);
            auto new_y = float(Engine.GetCurrentMapArea().Tiles[x][y].mob->Position.Y + dy * Engine.GetCurrentMapArea().Tiles[x][y].mob->StepSize);
            auto new_x_i = int(new_x);
            auto new_y_i = int(new_y);
            auto old_x_i = int(Engine.GetCurrentMapArea().Tiles[x][y].mob->Position.X);
            auto old_y_i = int(Engine.GetCurrentMapArea().Tiles[x][y].mob->Position.Y);
            if (new_x_i >= 0 && new_y_i >= 0 && new_x_i < Engine.WorldMap->MapAreaSize && new_y_i < Engine.WorldMap->MapAreaSize)
            {
                if (Engine.GetCurrentMapArea().Tiles[new_x_i][new_y_i].GroundType != GetId("GroundtypeWater"))
                {
                    if (Engine.GetCurrentMapArea().Tiles[new_x_i][new_y_i].mob == nullptr || (new_x_i == old_x_i && new_y_i == old_y_i))
                    {
                        Engine.GetCurrentMapArea().Tiles[old_x_i][old_y_i].mob->Position = { new_x, new_y };
                        if (new_x_i != old_x_i || new_y_i != old_y_i)
                        {
                            Engine.GetCurrentMapArea().Tiles[new_x_i][new_y_i].mob = std::move(Engine.GetCurrentMapArea().Tiles[old_x_i][old_y_i].mob);
                            Engine.GetCurrentMapArea().Tiles[old_x_i][old_y_i].mob = nullptr;
                        }
                        Engine.GetCurrentMapArea().MobsMirror.erase(Engine.GetCurrentMapArea().MobsMirror.begin() + i);
                        Engine.GetCurrentMapArea().MobsMirror.push_back(std::ref(Engine.GetCurrentMapArea().Tiles[new_x_i][new_y_i].mob));
                    }
                    else if (Engine.GetCurrentMapArea().Tiles[new_x_i][new_y_i].mob != nullptr && (new_x_i != old_x_i || new_y_i != old_y_i))
                    {
                        Engine.GetCurrentMapArea().Tiles[x][y].mob->MoveDestination = { -1, -1 };
                    }
                }
                else
                {
                    Engine.GetCurrentMapArea().Tiles[x][y].mob->MoveDestination = { -1, -1 };
                }
            }
            else
            {
                Engine.GetCurrentMapArea().Tiles[x][y].mob->MoveDestination = { -1, -1 };
            }
        }
    }
}
}
