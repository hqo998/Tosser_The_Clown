#include "Application/Application.hpp"

#include "Entities.hpp"

AimGuide::AimGuide()
{
    texture = LoadTexture("resources/tmp/AimGuider_Sprite.png");

    for (int i = 0; i < 5; i++)
    {
        guidePoints.push_back(texture);
    }
};

void AimGuide::Hide()
{

};

void AimGuide::Show()
{

};

void AimGuide::Update()
{

};