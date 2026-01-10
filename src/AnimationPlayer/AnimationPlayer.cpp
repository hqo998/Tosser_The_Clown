#include "AnimationPlayer.hpp"

#include <raylib.h>

#include <print>

AnimationPlayer::AnimationPlayer()
{
};

void AnimationPlayer::AddAnimation(std::string_view animationName ,const AnimationSequence &aniSeq)
{
    savedAnimations.emplace(animationName, aniSeq);
};

void AnimationPlayer::PlayAnimation(const std::string& animationName)
{
    currentAnimation = std::make_unique<AnimationSequence>(savedAnimations.at(animationName));
    currentFrameIndex = currentAnimation->startFrame;
    finished = false;
};

void AnimationPlayer::PlayAnimation(const AnimationSequence& animationSeq)
{
    currentAnimation = std::make_unique<AnimationSequence>(animationSeq);
    currentFrameIndex = currentAnimation->startFrame;
    finished = false;
};

frameIndex AnimationPlayer::GetCurrentFrameIndex()
{
    return currentFrameIndex;
};

void AnimationPlayer::Update()
{
    if (!currentAnimation) return; // return if nullptr.

    timer += GetFrameTime();

    if (timer >= 1/currentAnimation->speedFPS && !finished)
    {
        currentFrameIndex.x += static_cast<int>(timer / (1/currentAnimation->speedFPS));
        // ^ So ani skips frames if fps goes too slow
        timer = 0;

        if (currentFrameIndex.x >= currentAnimation->framesLength && currentAnimation->loop)
        {
            currentFrameIndex.x = currentAnimation->startFrame.x;
        }
        else if (currentFrameIndex.x >= currentAnimation->framesLength - 1 && !currentAnimation->loop)
        {

            finished = true;
        }
    }



};