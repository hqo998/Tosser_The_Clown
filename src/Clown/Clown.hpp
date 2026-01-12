#pragma  once

#include "../AnimationPlayer/AnimationPlayer.hpp"
#include "../Sprite/Sprite.hpp"

#pragma region CLOWN_ANIMATIONS
AnimationSequence clownThrow = {
        .name = "Throw",
        .startFrame = {0, 0}, // start frame
        .Length = 9,      // how many frames long
        .speedFPS = 5,      // fps speed
        .loop = false,  // do loop
        .frameHolds = {},     // what frames to pause on and how many frames for
    };

AnimationSequence clownTalk = {
        .name = "Talk",
        .startFrame = {0, 1}, // start frame
        .Length = 2,      // how many frames long
        .speedFPS = 2,      // fps speed
        .loop = true,   // do loop
        .frameHolds = {},     // what frames to pause on and how many frames for
    };
#pragma endregion


class Clown
{
    AnimationPlayer AniPlayer;
    Sprite sprite;


public:
    Clown();
};