#include "Application/Application.hpp"

#include "Entities.hpp"

#include "raymath.h"


#include <print>
#include <cmath>

const double pi = 3.14159265358979323846;

float calculateAngleFromPoint(Vector2 point, Vector2 mouse)
{
    float radians = std::atan2((point.y - mouse.y), (point.x - mouse.x));
    return radians * (180 / static_cast<float>(pi));
}

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



void AimGuide::Update(Vector2 offset)
{
    float angle = calculateAngleFromPoint(offset, origin) - 90;

    std::println("{}", angle);

    int i = 0;
    for (auto &point : guidePoints)
    {
        if (i == 0)
        {
            point.position = origin;
        }

        

        point.rotation = angle*(i+1);

        // needs to change so that is basised of last points rotation then forward that vector a set offset amount.
        point.position = origin - (offset - origin) * static_cast<float>(i);

        i++;
    }
}; // Update


