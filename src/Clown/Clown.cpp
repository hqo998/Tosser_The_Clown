#include "Clown.hpp"

// talks on main menu screen
// when playing clicks and drags does throwing idle
// on release does throw animation
// get hit animation?

#pragma region CLOWN_ANIMATIONS

AnimationSequence ClownAniThrow = {
        .name = "Throw",
        .startFrame = {0, 0}, // start frame
        .Length = 9,      // how many frames long
        .speedFPS = 5,      // fps speed
        .loop = false,  // do loop
        .frameHolds = {},     // what frames to pause on and how many frames for
};

AnimationSequence clownAniAim = {
        .name = "Throw",
        .startFrame = {0, 0}, // start frame
        .Length = 2,      // how many frames long
        .speedFPS = 5,      // fps speed
        .loop = true,  // do loop
        .frameHolds = {},     // what frames to pause on and how many frames for
};

AnimationSequence clownAniTalk = {
        .name = "Talk",
        .startFrame = {0, 1}, // start frame
        .Length = 2,      // how many frames long
        .speedFPS = 2,      // fps speed
        .loop = true,   // do loop
        .frameHolds = {},     // what frames to pause on and how many frames for
};
#pragma endregion

Clown::Clown()  : Sprite("resources/tmp/TosserSpritesheetTest.png", 9, 2)
{
    scale = {1.f, 1.f};
    position = {540, 540};
    SetOrigin(O_CENTER);
    AnimPlayer.PlayAnimation(clownAniAim);
};

void Clown::Update()
{
    AnimPlayer.Update();
    SetFrame(AnimPlayer.GetCurrentFrameIndex());

};
