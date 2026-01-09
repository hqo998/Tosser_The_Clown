#include "AnimationPlayer.hpp"

#include <raylib.h>

AnimationPlayer::AnimationPlayer()
{
};

void AnimationPlayer::AddAnimation(std::string_view animationName ,const AnimationSequence &aniSeq)
{
    savedAnimations.emplace(animationName, aniSeq);
};