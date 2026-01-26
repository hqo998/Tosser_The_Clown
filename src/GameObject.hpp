#pragma once

#include "raylib.h"
#include <vector>
#include <memory>
#include <algorithm>

class GameObject
{
public:
    // Transform transform {};
    int zOrder = 0;
    virtual void Draw() {};
    virtual void Update() {}; // virtual = 0 means no function for class
};

enum class GameState
{
    START,
    PLAYING,
    PAUSED,
    GAMEOVER
}; // GameState

// This `GameInstance` class is responsible for managing the game state and game objects within the game.
class GameInstance
{
    GameState currentState{GameState::PLAYING};
    std::vector<std::shared_ptr<GameObject>> gameObjects{};

public:
    GameInstance() = default;

    void Init();

    void Shutdown();

    void Update()
    {
        if (currentState != GameState::PLAYING)
            return;

        for (const auto &object : gameObjects)
        {
            object->Update();
        }
    }

    void Draw()
    {
        std::sort(gameObjects.begin(), gameObjects.end(), [](const auto &a, const auto &b)
                  { return a->zOrder < b->zOrder; });
        for (const auto &object : gameObjects)
        {
            object->Draw();
        }
    }

    // std::derived_from is a concept that checks if T inherits from GameObject
    // typename... Args is a parameter pack that allows passing any number of arguments
    template <std::derived_from<GameObject> T, typename... Args>
    std::shared_ptr<T> CreateGameObject(Args &&...args)
    {
        auto object = std::make_shared<T>(std::forward<Args>(args)...);
        gameObjects.push_back(object);
        return object;
    }
};