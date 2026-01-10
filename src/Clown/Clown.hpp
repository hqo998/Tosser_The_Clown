#pragma  once

#include "../AnimationPlayer/AnimationPlayer.hpp"
#include "../Sprite/Sprite.hpp"

#pragma region CLOWN_ANIMATIONS
AnimationSequence clownThrow = {
        "Throw",
        {0, 0}, // start frame
        9,      // how many frames long
        5,      // fps speed
        false,  // do loop
        {},     // what frames to pause on and how many frames for
    };

AnimationSequence clownTalk = {
        "Talk",
        {0, 1}, // start frame
        2,      // how many frames long
        2,      // fps speed
        true,   // do loop
        {},     // what frames to pause on and how many frames for
    };
#pragma endregion


class Clown
{
    AnimationPlayer AniPlayer;
    Sprite sprite;


public:
    Clown();
};