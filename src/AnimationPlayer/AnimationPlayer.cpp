#include "AnimationPlayer.hpp"

#include <raylib.h>

#include <print>

AnimationPlayer::AnimationPlayer() {
};

void AnimationPlayer::AddAnimation(const std::string &animationName, const AnimationSequence &aniSeq)
{
    const auto &result = savedAnimations.try_emplace(animationName, aniSeq);
    if (!result.second)
    {
        std::println("[WARNING] - Animation Player FAILED to add '{}' | Might of already been added.", result.first->first);
    }
};

void AnimationPlayer::AddAnimation(const AnimationSequence &aniSeq)
{
    AddAnimation(aniSeq.name, aniSeq);
};

void AnimationPlayer::PlayAnimation(const AnimationSequence &animationSeq)
{
    AddAnimation(animationSeq.name, animationSeq);
    PlayAnimation(animationSeq.name);
};

void AnimationPlayer::PlayAnimation(const std::string &animationName)
{
    finished = false;
    currentAnimation = std::make_unique<AnimationSequence>(savedAnimations.at(animationName));
    currentFrameIndex = currentAnimation->startFrame;
    holdCount = 0;
    lastHoldIndex = -1;
};

std::string_view AnimationPlayer::GetCurrentAnimationName()
{
    return currentAnimation->name;
};

frameIndex AnimationPlayer::GetCurrentFrameIndex()
{
    if (!currentAnimation)
        return {};
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

        // check for custom frame holds for accurate timing
        if (currentAnimation->frameHolds.contains(currentFrameIndex.x - 1) && !holdCount && lastHoldIndex != currentFrameIndex.x - 1)
        {
            holdCount = currentAnimation->frameHolds.at(currentFrameIndex.x - 1) - 1;
            lastHoldIndex = currentFrameIndex.x - 1;
            currentFrameIndex.x--;
        }
        else if (holdCount)
        {
            currentFrameIndex.x--;
            holdCount--;
        }

        // check whether to loop or finish
        if (currentFrameIndex.x >= currentAnimation->Length)
        {
            if (currentAnimation->loop)
            {
                currentFrameIndex.x = currentAnimation->startFrame.x;
                lastHoldIndex = -1;
            }
            else
            {
                currentFrameIndex.x = currentAnimation->Length - 1;
                lastHoldIndex = -1;
                finished = true;

                currentAnimation = nullptr;
            }
        }
    }
}; // Update()