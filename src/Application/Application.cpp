#include "Application.hpp"

void Application::CheckState()
{
    switch (currentState)
    {
    case AppState::MENU:
        break;
    case AppState::PLAY:
        break;
    case AppState::PAUSE:
        break;
    }
}

void Application::SwitchState(AppState toState)
{
    currentState = toState;
    switch (toState)
    {
    case AppState::MENU:
        break;
    case AppState::PLAY:
        break;
    case AppState::PAUSE:
        break;
    }
}