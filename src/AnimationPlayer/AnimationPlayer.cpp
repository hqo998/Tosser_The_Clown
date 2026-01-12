#include "AnimationPlayer.hpp"

#include <raylib.h>

// #include <print>

AnimationPlayer::AnimationPlayer() {
};

void AnimationPlayer::AddAnimation(const std::string &animationName, const AnimationSequence &aniSeq)
{
    savedAnimations.try_emplace(animationName, aniSeq);
};

void AnimationPlayer::PlayAnimation(const AnimationSequence &animationSeq)
{
    AddAnimation(animationSeq.name, animationSeq);
    PlayAnimation(animationSeq.name);
};

void AnimationPlayer::PlayAnimation(const std::string &animationName)
{
    currentAnimation = std::make_unique<AnimationSequence>(savedAnimations.at(animationName));
    currentFrameIndex = currentAnimation->startFrame;
    finished = false;
    holdCount = 0;
    lastHoldIndex = -1;
};

std::string_view AnimationPlayer::GetCurrentAnimationName()
{
    return currentAnimation->name;
};

frameIndex AnimationPlayer::GetCurrentFrameIndex()
{
    return currentFrameIndex;
};

bool AnimationPlayer::Finished()
{
    return finished;
}

void AnimationPlayer::Update()
{
    if (!currentAnimation)
        return; // return if nullptr.
    if (currentAnimation->speedFPS <= 0.f)
        return; // return if speed is 0

    timer += GetFrameTime();
    const float timePerFrame = 1 / currentAnimation->speedFPS;

    while (timer >= timePerFrame)
    {
        timer -= timePerFrame;
        currentFrameIndex.x++;

        if (currentAnimation->frameHolds.contains(currentFrameIndex.x - 1) && !holdCount && lastHoldIndex != currentFrameIndex.x - 1)
        {
            // std::println("found map");
            holdCount = currentAnimation->frameHolds.at(currentFrameIndex.x - 1) - 1;
            lastHoldIndex = currentFrameIndex.x - 1;
            currentFrameIndex.x--;
        }
        else if (holdCount)
        {
            // std::println("hold not 0");
            currentFrameIndex.x--;
            holdCount--;
        }

        if (currentFrameIndex.x >= currentAnimation->Length)
        {
            if (currentAnimation->loop)
            {
                // std::println("pop loop");
                currentFrameIndex.x = currentAnimation->startFrame.x;
                lastHoldIndex = -1;
            }
            else
            {
                // std::println("pop not loop");
                currentFrameIndex.x = currentAnimation->Length - 1;
                finished = true;
                lastHoldIndex = -1;
            }
        }
    }

    // std::println("{}", currentFrameIndex.x);
};