#include "Application/Application.hpp"

#include "Entities.hpp"

#include "raymath.h"

#include <print>

AimGuide::AimGuide()
{
    texture = LoadTexture("resources/tmp/AimGuider_Sprite.png");
    SetTextureWrap(texture, TEXTURE_WRAP_REPEAT);

    for (int i = 0; i < 5; i++)
    {
        guidePoints.push_back({texture, 2, 1});
    }

}; // AimGuide

void AimGuide::Refresh()
{
    for (auto &point : guidePoints)
    {
        point.SetOrigin(O_CENTER);
        point.scale = {scale, scale};
        point.position = origin;
        // std::println("pos: ({},{}) scale: {}", point.position.x, point.position.y, point.scale.x);
    }
};

void AimGuide::Draw()
{
    if (hidden)
        return;

    int i = 0;
    for (auto &point : guidePoints)
    {
        point.Draw(point.rotation);
        // std::println("pos: ({},{}) scale: {}", point.position.x, point.position.y, point.scale.x);
        i++;
    }
}; // Draw



void AimGuide::Update(GuideOffsets offset)
{
    int i = 0;
    for (auto &point : guidePoints)
    {
        // needs to change so that is basised of last points rotation then forward that vector a set offset amount.
        point.position = origin - (offset.point - origin) * static_cast<float>(i);
        // point.position = origin;
        point.rotation = offset.rotation;
        i++;
    }
}; // Update