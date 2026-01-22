#pragma once
#include "raylib.h"
#include <vector>
#include <memory>

struct Transform
{
    Vector2 position {0, 0};
    float   rotation {0};
    Vector2 scale    {1, 1};
};
    
class GameObject
{
public:
    Transform transform {};

    virtual void Draw()   = 0;
    virtual void Update() = 0;
};

enum class GameState
{
    START,
    PLAYING,
    PAUSED,
    GAMEOVER
}; // GameState

class GameInstance
{
    GameState currentState  {};
    std::vector<std::shared_ptr<GameObject>> gameObjects {};

public:

    GameInstance();

    void Update()
    {
        if (currentState != GameState::PLAYING)
            return;
            
        for (const auto& object : gameObjects)
        {
            object->Update();
        }
    }

    void Draw()
    {
        for (const auto& object : gameObjects)
        {
            object->Draw();
        }
    }

    // std::derived_from is a concept that checks if T inherits from GameObject
    // typename... Args is a parameter pack that allows passing any number of arguments
    template<std::derived_from<GameObject> T, typename... Args>
    std::shared_ptr<T> CreateGameObject(Args&&... args)
    {
        auto object = std::make_shared<T>(std::forward<Args>(args)...);
        gameObjects.push_back(object);
        return object;
    }
};