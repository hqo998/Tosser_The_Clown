#include "AnimationPlayer.hpp"

#include <raylib.h>

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
};

void AnimationPlayer::PlayAnimation(const AnimationSequence& animationSeq)
{
    currentAnimation = std::make_unique<AnimationSequence>(animationSeq);
    currentFrameIndex = currentAnimation->startFrame;
};

frameIndex AnimationPlayer::GetCurrentFrameIndex()
{
    return currentFrameIndex;
};

void AnimationPlayer::Update()
{
    float dt = GetFrameTime();
};