#include "Application.hpp"

void GameInstance::RequestMenu()
{
    if (CurrentState != EGameState::MENU)
    {
        CurrentState = EGameState::MENU;
        // Whatever you want to do to switch to main menu
    }
}

void GameInstance::RequestPause()
{
    if (CurrentState != EGameState::PLAY)
    {
        CurrentState = EGameState::PLAY;
        // Whatever you want to do to start playing
    }
}

void GameInstance::RequestPlay()
{
    if (CurrentState != EGameState::PLAY)
    {
        CurrentState = EGameState::PLAY;
        // Whatever you want to do to start playing
    }
}