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

struct frameIndex
{
    int row;
    int column;
};

struct AnimationSequence
{
    frameIndex startFrame;
    int length;
    float playbackSpeed;
    std::unordered_map<int, float> frameHolds;
    bool loop;
};

class AnimationPlayer
{
private:
    std::unordered_map<std::string, AnimationSequence> savedAnimations;
    
    std::unique_ptr<AnimationSequence> currentAnimation = nullptr;

    float timer;
    int currentStep;

public:


    // functions
    AnimationPlayer();

    void AddAnimation(std::string_view animationName ,const AnimationSequence &aniSeq);
    
    void PlayAnimation();
    void GetCurrentFrameIndex();
    void Update();

};
