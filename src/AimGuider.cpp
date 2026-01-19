#include "Application/Application.hpp"

#include "Entities.hpp"

AimGuide::AimGuide()
{
    texture = LoadTexture("resources/tmp/AimGuider_Sprite.png");
    SetTextureWrap(texture, TEXTURE_WRAP_REPEAT);

    for (int i = 0; i < 5; i++)
    {
        guidePoints.push_back({texture, 2, 1});
    }

    for (auto point : guidePoints)
    {
        point.SetOrigin(O_CENTER);
    }
}; // AimGuide

void AimGuide::Draw()
{
    if (hidden) return;

    int i = 0;
    for (auto point : guidePoints)
    {
        point.Draw(point.rotation);
        i++;
    }
}; // Draw

void AimGuide::Update()
{
    int i = 0;
    for (auto point : guidePoints)
    {
        point.position;
        point.rotation;
        i++;
    }
}; // Update