#include <raylib.h>

#include "Application/Application.hpp"
#include "Entities.hpp"

#include <algorithm>
#include <print>

#pragma region CROWD_ANIMATIONS

AnimationSequence CrowdIdle =
{
        .name = "Idle",
        .startFrame = {0, 0},
        .Length = 3,
        .speedFPS = 5,
        .loop = false,
        .frameHolds = {}
};

AnimationSequence CrowdThrow =
{
        .name = "Throw",
        .startFrame = {0, 1},
        .Length = 13,
        .speedFPS = 5,
        .loop = false,
        .frameHolds = {}
};

#pragma endregion

#pragma region CROWD_PERSON

CrowdPerson::CrowdPerson(const Texture2D sharedTex) : Sprite(sharedTex, 13, 2)
{
    Vector2 relativeScale = GetRelativeScale();
    float adjustedScale = (relativeScale.x < relativeScale.y) ? relativeScale.x : relativeScale.y;
    float uniform_scale = .3f * adjustedScale;

    scale = {uniform_scale, uniform_scale};
    SetOrigin(O_CENTER);


    SwitchState(CrowdState::THROW);
}; // CrowdPerson

void CrowdPerson::Update()
{
    switch (currentState)
    {
    case CrowdState::IDLE:
        break;

    case CrowdState::THROW:
        break;

    case CrowdState::RELEASE:
        break;
    }

    AnimPlayer.Update();
    SetFrame(AnimPlayer.GetCurrentFrameIndex());
}; // Update

void CrowdPerson::SwitchState(CrowdState toState)
{
    currentState = toState;

    switch (toState)
    {
    case CrowdState::IDLE:
        AnimPlayer.PlayAnimation(CrowdIdle);
        break;
    case CrowdState::THROW:
        AnimPlayer.PlayAnimation(CrowdThrow);
        break;
    case CrowdState::RELEASE:
        break;
    }
}; // SwitchState

#pragma endregion

#pragma region CROWD_MANAGER


CrowdManager::CrowdManager()
{
    texture = LoadTexture("resources/CrowdThrowers/CrowdMemberBASE_spritesheet.png");
}; // CrowdManager

CrowdManager::~CrowdManager()
{
    UnloadTexture(texture);
}; // ~CrowdManager

void CrowdManager::Update()
{
    for (std::unique_ptr<CrowdPerson> &person : people)
    {
        person->Update();
    }
} // Update

void CrowdManager::Draw()
{
    std::sort(people.begin(), people.end(), [](const auto& a, const auto& b) {
        return a->position.y < b->position.y;
    });

    for (std::unique_ptr<CrowdPerson> &person : people)
    {
        person->Draw();
    }
}; // Draw



void CrowdManager::AddPerson()
{
    

    Vector2 position { 0, 0 };

    Vector2 minDistance = {app.GetCanvas().canvasWidth / 10, app.GetCanvas().canvasHeight / 3};

    const int max_attempts = 1000;
    int attempt = 1;

    bool validPos = false;
    while (!validPos && attempt < max_attempts)
    {
        position = GeneratePostion();
        if ( !CheckIfCloseToAnother(position, minDistance) )
        {
            validPos = true;
            break;
        }
        attempt++;
    }
    if (validPos)
    {
        people.push_back(std::make_unique<CrowdPerson>(texture));
        people.back()->position = position;
    }
}; // AddPerson

Vector2 CrowdManager::GeneratePostion()
{
        // people positions
    const float randX = GetRandomValue(10, 90)/100.f;
    const float posX = randX*app.GetCanvas().canvasWidth;

    // (rand * height - half the height) + 1/3 of the way down the canvas
    const float randY = GetRandomValue(10, 90)/100.f;
    const float posY =  .2f*(randY*app.GetCanvas().canvasHeight - (app.GetCanvas().canvasHeight / 2)) + (app.GetCanvas().canvasHeight * .4f);

    return {posX, posY};
}; // GeneratePosition

bool CrowdManager::CheckIfCloseToAnother(const Vector2 pos, const Vector2 minimum)
{
    for (const auto& person : people)
    {
        const float dx { person->position.x - pos.x };
        const float dy { person->position.y - pos.y };
        // if (std::abs(dx) < minimum.x) return true;
        if (std::abs(dx) < minimum.x && std::abs(dy) < minimum.y) return true;
    }
    return false;
}; // checkIfClose