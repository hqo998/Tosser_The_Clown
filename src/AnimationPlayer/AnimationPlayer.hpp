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
    std::string name;
    const frameIndex startFrame;
    const int framesLength;
    const float speedFPS;
    const bool loop;
    const std::unordered_map<int, int> frameHolds; // initialize with eg. { {1, 20}, {2, 1}, {7, 1} }
};

class AnimationPlayer
{
private:
    std::unordered_map<std::string, AnimationSequence> savedAnimations;

    std::unique_ptr<AnimationSequence> currentAnimation = nullptr;

    float timer{0};
    frameIndex currentFrameIndex;
    bool finished{};

    int holdCount{};
    int lastHoldIndex{-5};

public:
    // functions
    AnimationPlayer();

    void AddAnimation(const std::string &animationName, const AnimationSequence &aniSeq);

    void PlayAnimation(const std::string &animationName);
    void PlayAnimation(const AnimationSequence &animationSeq);
    std::string_view GetCurrentAnimationName();
    frameIndex GetCurrentFrameIndex();
    void Update();

    bool Finished();
};
