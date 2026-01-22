#pragma  once

#include "AnimationPlayer/AnimationPlayer.hpp"
#include "Sprite/Sprite.hpp"

#pragma region AIM_GUIDER

// Use a list of sprites that all share an aim guide texture to generate points and render them according to an offset.
class AimGuide
{
    std::vector<Sprite> guidePoints;

    Texture2D texture;

    

public:
    Vector2 origin {};

    float scale  {};
    bool hidden { false };

    AimGuide();

    void Draw();
    void Update(Vector2 offset);
    void Refresh();
};

#pragma endregion


#pragma region CLOWN
enum class ClownState
{
    IDLE,
    AIM,
    THROW
}; // ClownState

enum class ClownCommands
{
    TRY_IDLE,
    TRY_THROW
}; // ClownCommands

class Clown : public Sprite
{
    AnimationPlayer AnimPlayer;

    ClownState currentState {};

    void SwitchState(ClownState toState);

    AimGuide aimGuide;
public:
    Clown();

    void Draw();

    void Update();

    void handleEvent();
}; // Clown

#pragma endregion

#pragma region CROWD
enum class CrowdState
{
    IDLE,
    THROW,
    RELEASE
}; // CrowdState

// make the crowd sprites share one texture

class CrowdPerson : public Sprite
{
    AnimationPlayer AnimPlayer;
    CrowdState currentState {};

    void SwitchState(CrowdState toState);
    // void LoadAnims();
public:
    CrowdPerson(const Texture2D sharedTex);

    void Update();

    void handleEvent();


}; // CrowdPerson

// The `CrowdManager` class is managing a collection of `CrowdPerson` objects. This class acts as a manager for handling and controlling a group of `CrowdPerson` instances.
class CrowdManager : public GameObject
{
    std::vector<std::unique_ptr<CrowdPerson>> people;
    Texture2D texture;
    bool CheckIfCloseToAnother(const Vector2 pos, const Vector2 minimum);
    Vector2 GeneratePostion();

public:
    CrowdManager();
    ~CrowdManager();
    void AddPerson();

    void Update();
    void Draw();
}; // Crowd

#pragma endregion

