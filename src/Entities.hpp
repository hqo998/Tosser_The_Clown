#pragma  once

#include "AnimationPlayer/AnimationPlayer.hpp"
#include "Sprite/Sprite.hpp"


#pragma region CLOWN
enum class ClownState
{
    IDLE,
    AIM,
    THROW
};

enum class ClownCommands
{
    TRY_IDLE,
    TRY_THROW
};

class Clown : public Sprite
{
    AnimationPlayer AnimPlayer;

    ClownState currentState {};

    void SwitchState(ClownState toState);
    // void LoadAnims();

public:
    Clown();

    void Update();

    void handleEvent();
};
#pragma endregion

#pragma region Crowd
enum class CrowdState
{
    IDLE,
    THROW,
    RELEASE
};

class CrowdPerson : public Sprite
{
    AnimationPlayer AnimPlayer;
    CrowdState currentState {};

    void SwitchState(CrowdState toState);
    // void LoadAnims();
public:
    CrowdPerson();

    void Update();

    void handleEvent();


};

class Crowd
{

};
#pragma endregion