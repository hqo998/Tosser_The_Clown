#include "Application/Application.hpp"
#include "Entities.hpp"

#include <raymath.h>
#include <print>

// talks on main menu screen
// when playing clicks and drags does throwing idle
// on release does throw animation
// get hit animation?

#pragma region CLOWN_ANIMATIONS

AnimationSequence ClownAniThrow = {
    .name = "Throw",
    .startFrame = {0, 0}, // start frame
    .Length = 9,          // how many frames long
    .speedFPS = 5,        // fps speed
    .loop = false,        // do loop
    .frameHolds = {},     // what frames to pause on and how many frames for
};

AnimationSequence clownAniAim = {
    .name = "Aim",
    .startFrame = {0, 0}, // start frame
    .Length = 2,          // how many frames long
    .speedFPS = 5,        // fps speed
    .loop = true,         // do loop
    .frameHolds = {},     // what frames to pause on and how many frames for
};

AnimationSequence clownAniTalk = {
    .name = "Talk",
    .startFrame = {0, 1}, // start frame
    .Length = 2,          // how many frames long
    .speedFPS = 2,        // fps speed
    .loop = true,         // do loop
    .frameHolds = {},     // what frames to pause on and how many frames for
};
#pragma endregion

Clown::Clown() : Sprite("resources/tmp/TosserSpritesheetTest.png", 9, 2)
{
    Vector2 relativeScale = GetRelativeScale();
    float adjustedScale = (relativeScale.x < relativeScale.y) ? relativeScale.x : relativeScale.y;
    float uniform_scale = .9f * adjustedScale;

    scale = {uniform_scale, uniform_scale};                                       // stop using magic numbers and base off canvas dimensions
    position = {(app.GetCanvas().canvasWidth / 2), app.GetCanvas().canvasHeight}; // need to remove hardcoding and base it off canvas dimensions
    SetOrigin(O_BOTTOM_CENTER);

    aimGuide.hidden = true;
    aimGuide.scale = uniform_scale * .04f;
    aimGuide.origin = {position.x + (GetBounds().width *.25f), position.y - (GetBounds().height * .25f)};
    aimGuide.Refresh();

    SwitchState(ClownState::IDLE);
};

void Clown::Update()
{

    switch (currentState)
    {
    case ClownState::IDLE:
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            SwitchState(ClownState::AIM);
        }
        break;

    case ClownState::AIM:
    {
        Vector2 offset {app.GetCanvas().GetMousePositionCanvas()};

        aimGuide.Update(offset);

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        {
            SwitchState(ClownState::THROW);
        }
        break;
    }
    case ClownState::THROW:
        if (AnimPlayer.Finished())
        {
            SwitchState(ClownState::IDLE);
        }
        break;
    }

    AnimPlayer.Update();
    SetFrame(AnimPlayer.GetCurrentFrameIndex());
};

void Clown::SwitchState(ClownState toState)
{
    currentState = toState;

    switch (toState)
    {
    case ClownState::IDLE:
        AnimPlayer.PlayAnimation(clownAniTalk);
        break;
    case ClownState::AIM:
        aimGuide.hidden = false;
        AnimPlayer.PlayAnimation(clownAniAim);
        break;
    case ClownState::THROW:
        aimGuide.hidden = true;
        AnimPlayer.PlayAnimation(ClownAniThrow);
        break;
    }
};

void Clown::Draw()
{
    // Call the base class draw method
    Sprite::Draw();

    // Draw the aim guide if it's not hidden
    if (!aimGuide.hidden)
    {
        aimGuide.Draw();
    }
};
