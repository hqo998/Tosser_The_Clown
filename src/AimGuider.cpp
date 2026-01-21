#include "Application/Application.hpp"

#include "Entities.hpp"

#include "raymath.h"

#include <print>
#include <cmath>

const double pi = 3.14159265358979323846;

float calculateAngleFromPoint(Vector2 point, Vector2 mouse)
{
    return std::atan2((point.y - mouse.y), (point.x - mouse.x));
}

float radiansToDegrees(float radians)
{
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

    guidePoints.back().scale *= 2.5f;
};

void AimGuide::Draw()
{
    if (hidden)
        return;

    int i = 0;
    for (auto &point : guidePoints)
    {

        point.Draw(radiansToDegrees(point.rotation * static_cast<float>(pi)));
        // std::println("rot: {}, pos: ({},{}) scale: {}", radiansToDegrees(point.rotation), point.position.x, point.position.y, point.scale.x);
        if (i == 4)
            point.SetFrame({1, 2});
        i++;
    }
}; // Draw


void AimGuide::Update(Vector2 mouse)
{
    // return radians of (x,y flipped) points arctan2 then asdds an offset for rotating 180 degree
    float angleRadians = -calculateAngleFromPoint({mouse.y, mouse.x}, {origin.y, origin.x});

    float spriteSize = guidePoints.at(0).GetBounds().width;

    Vector2 clampedMouse = Vector2ClampValue(mouse - origin, spriteSize/2, spriteSize*2);

    std::println("spriteSize: {} \n normal: {}, {} \n clamped: {}, {}", spriteSize, mouse.x, mouse.y, clampedMouse.x, clampedMouse.y);
    int i = 0;

    for (auto &point : guidePoints)
    {
        point.rotation = ((angleRadians / static_cast<float>(pi) / 4) * (i + 1));

        if (i == 0)
        {
            point.position = origin;
            i++;
            continue;
        }

        point.position = guidePoints.at(i - 1).position - Vector2Rotate(clampedMouse, point.rotation);

        // std::println("[{}], {}, {}", i, point.position.x, point.position.y);
        i++;
    }
}; // Update
