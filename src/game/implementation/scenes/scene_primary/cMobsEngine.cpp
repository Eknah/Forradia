
#include "CommonExternal.h"
#include "cMobsEngine.h"
#include "../engine/cEngine.h"

namespace Forradia
{

void cMobsEngine::Update()
{

    for (unsigned int I = 0; I < Engine.GetCurrentMapArea().MobsMirror.size(); I++)
    {
        if (I >= Engine.GetCurrentMapArea().MobsMirror.size()) break;

        auto X = int(Engine.GetCurrentMapArea().MobsMirror.at(I).get()->Position.X);
        auto Y = int(Engine.GetCurrentMapArea().MobsMirror.at(I).get()->Position.Y);

        if (Ticks() > Engine.GetCurrentMapArea().Tiles[X][Y].Mob->TickLastMove + Engine.GetCurrentMapArea().Tiles[X][Y].Mob->MoveSpeed)
        {
            Engine.GetCurrentMapArea().Tiles[X][Y].Mob->TickLastMove = Ticks();

            if (Engine.GetCurrentMapArea().Tiles[X][Y].Mob->MoveDestination.X == -1 || Engine.GetCurrentMapArea().Tiles[X][Y].Mob->MoveDestination.Y == -1)
            {
                auto DestinationX = Engine.GetCurrentMapArea().Tiles[X][Y].Mob->Position.X + rand() % 15 - rand() % 15;
                auto DestinationY = Engine.GetCurrentMapArea().Tiles[X][Y].Mob->Position.Y + rand() % 15 - rand() % 15;

                DestinationX = std::min(std::max(DestinationX, 0.0f), float(Engine.WorldMap->MapAreaSize) - 1.0f);
                DestinationY = std::min(std::max(DestinationY, 0.0f), float(Engine.WorldMap->MapAreaSize) - 1.0f);

                Engine.GetCurrentMapArea().Tiles[X][Y].Mob->MoveDestination = { DestinationX, DestinationY };
            }

            auto DeltaX = Engine.GetCurrentMapArea().Tiles[X][Y].Mob->MoveDestination.X - Engine.GetCurrentMapArea().Tiles[X][Y].Mob->Position.X;
            auto DeltaY = Engine.GetCurrentMapArea().Tiles[X][Y].Mob->MoveDestination.Y - Engine.GetCurrentMapArea().Tiles[X][Y].Mob->Position.Y;
            auto Distance = std::sqrt(DeltaX * DeltaX + DeltaY * DeltaY);

            if (Distance < 1)
            {
                Engine.GetCurrentMapArea().Tiles[X][Y].Mob->MoveDestination = { -1, -1 };

                continue;
            }

            Engine.GetCurrentMapArea().Tiles[X][Y].Mob->FacingAngle = (float)std::atan2(-DeltaX, -DeltaY) / (float)M_PI * 180.0f;

            auto Angle = Engine.GetCurrentMapArea().Tiles[X][Y].Mob->FacingAngle / 180.0f * M_PI - M_PI / 2 + M_PI;
            auto DX = -std::cos(Angle) * Engine.GetCurrentMapArea().Tiles[X][Y].Mob->StepMultiplier;
            auto DY = std::sin(Angle) * Engine.GetCurrentMapArea().Tiles[X][Y].Mob->StepMultiplier;
            auto NewX = float(Engine.GetCurrentMapArea().Tiles[X][Y].Mob->Position.X + DX * Engine.GetCurrentMapArea().Tiles[X][Y].Mob->StepSize);
            auto NewY = float(Engine.GetCurrentMapArea().Tiles[X][Y].Mob->Position.Y + DY * Engine.GetCurrentMapArea().Tiles[X][Y].Mob->StepSize);
            auto NewXI = int(NewX);
            auto NewYI = int(NewY);
            auto OldXI = int(Engine.GetCurrentMapArea().Tiles[X][Y].Mob->Position.X);
            auto OldYI = int(Engine.GetCurrentMapArea().Tiles[X][Y].Mob->Position.Y);

            if (NewXI >= 0 && NewYI >= 0 && NewXI < Engine.WorldMap->MapAreaSize && NewYI < Engine.WorldMap->MapAreaSize)
            {
                if (Engine.GetCurrentMapArea().Tiles[NewXI][NewYI].GroundType != GetId("GroundtypeWater"))
                {
                    if (Engine.GetCurrentMapArea().Tiles[NewXI][NewYI].Mob == nullptr || (NewXI == OldXI && NewYI == OldYI))
                    {
                        Engine.GetCurrentMapArea().Tiles[OldXI][OldYI].Mob->Position = { NewX, NewY };

                        if (NewXI != OldXI || NewYI != OldYI)
                        {
                            Engine.GetCurrentMapArea().Tiles[NewXI][NewYI].Mob = std::move(Engine.GetCurrentMapArea().Tiles[OldXI][OldYI].Mob);
                            Engine.GetCurrentMapArea().Tiles[OldXI][OldYI].Mob = nullptr;
                        }

                        Engine.GetCurrentMapArea().MobsMirror.erase(Engine.GetCurrentMapArea().MobsMirror.begin() + I);
                        Engine.GetCurrentMapArea().MobsMirror.push_back(std::ref(Engine.GetCurrentMapArea().Tiles[NewXI][NewYI].Mob));
                    }
                    else if (Engine.GetCurrentMapArea().Tiles[NewXI][NewYI].Mob != nullptr && (NewXI != OldXI || NewYI != OldYI))
                    {
                        Engine.GetCurrentMapArea().Tiles[X][Y].Mob->MoveDestination = { -1, -1 };
                    }
                }
                else
                {
                    Engine.GetCurrentMapArea().Tiles[X][Y].Mob->MoveDestination = { -1, -1 };
                }
            }
            else
            {
                Engine.GetCurrentMapArea().Tiles[X][Y].Mob->MoveDestination = { -1, -1 };
            }
        }
    }
}

}
