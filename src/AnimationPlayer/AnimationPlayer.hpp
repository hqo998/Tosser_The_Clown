#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include <memory>

#include <raylib.h>


// how many frames to play
// what row
// how long to hold each frame
// what frame to start to play

const struct frameIndex
{
    int x;
    int y;
};

struct AnimationSequence
{
    const frameIndex startFrame;
    const int framesLength;
    const float speedFPS;
    const std::unordered_map<int, float> frameHolds;
    const bool loop;
};

class AnimationPlayer
{
private:
    std::unordered_map<std::string, AnimationSequence> savedAnimations;
    
    std::unique_ptr<AnimationSequence> currentAnimation = nullptr;

    float timer {0};
    frameIndex currentFrameIndex;
    bool finished {};

public:


    // functions
    AnimationPlayer();

    void AddAnimation(std::string_view animationName ,const AnimationSequence &aniSeq);
    
    void PlayAnimation(const std::string& animationName);
    void PlayAnimation(const AnimationSequence& animationSeq);
    frameIndex GetCurrentFrameIndex();
    void Update();

};
