#include "Sprite.hpp"
#include "../Application/Application.hpp"

#include "raylib.h"



// use class heritance for other sprites as this as parent.

Sprite::Sprite() {};

Sprite::Sprite(const std::string &texturePath)
{
    LoadSprite(texturePath);
};

Sprite::Sprite(const std::string &texturePath, int spriteFramesX, int spriteFramesY)
    : spriteFramesX{spriteFramesX}, spriteFramesY{spriteFramesY}
{
    LoadSprite(texturePath);
};

Sprite::~Sprite()
{
    if (textureLoaded)
    {
        UnloadTexture(texture);
    }
};

void Sprite::LoadSprite(const std::string &texturePath)
{
    texture = LoadTexture(texturePath.c_str());
    textureLoaded = true;

    sourceRect = {0.f, 0.f,
                  static_cast<float>(texture.width) / spriteFramesX,
                  static_cast<float>(texture.height) / spriteFramesY};

    SetOrigin(O_TOP_LEFT);
};

void Sprite::LoadSprite(const std::string &texturePath, int spriteTilesX, int spriteTilesY)
{
    LoadSprite(texturePath);
    this->spriteFramesX = spriteTilesX;
    this->spriteFramesY = spriteTilesY;
};

void Sprite::SetFrame(int frameIndexX, int frameIndexY)
{
    sourceRect = {
        sourceRect.width * (frameIndexX),
        sourceRect.height * (frameIndexY),
        sourceRect.width,
        sourceRect.height};
};

void Sprite::SetFrame(frameIndex frameIndex)
{
    SetFrame(frameIndex.x, frameIndex.y);
};

void Sprite::SetOrigin(Origins origin_value)
{
    switch (origin_value)
    {
    case O_CENTER_LEFT:
        Origin = {0.0f, 0.5f}; // Middle of left edge
        break;
    case O_BOTTOM_LEFT:
        Origin = {0.0f, 1.0f}; // Bottom-left corner
        break;
    case O_BOTTOM_CENTER:
        Origin = {0.5f, 1.0f}; // Middle of bottom edge
        break;
    case O_BOTTOM_RIGHT:
        Origin = {1.0f, 1.0f}; // Bottom-right corner
        break;
    case O_CENTER_RIGHT:
        Origin = {1.0f, 0.5f}; // Middle of right edge
        break;
    case O_TOP_RIGHT:
        Origin = {1.0f, 0.0f}; // Top-right corner
        break;
    case O_CENTER_TOP:
        Origin = {0.5f, 0.0f}; // Middle of top edge
        break;
    case O_CENTER:
        Origin = {0.5f, 0.5f}; // Center of texture
        break;
    case O_TOP_LEFT:
    default:
        Origin = {0.0f, 0.0f}; // Fallback to top-left
        break;
    }
};

Rectangle Sprite::DestPro(Rectangle dest, Vector2 origin)
{
    dest.x = dest.x - origin.x;
    dest.y = dest.y - origin.y;
    return dest;
};

Rectangle Sprite::GetDestRect()
{
    return {position.x, position.y, sourceRect.width * scale.x, sourceRect.height * scale.y};
};

Vector2 Sprite::GetDestOrigin(Rectangle rect)
{
    return {rect.width * Origin.x, rect.height * Origin.y};
};

void Sprite::Draw()
{
    Rectangle destRect = GetDestRect();
    Vector2 destOrigin = GetDestOrigin(destRect);

    // if (!IsOnScreen()) return; // add cull check in sprite draw

    DrawTexturePro(texture,
                   {sourceRect.x, sourceRect.y, flip ? -sourceRect.width : sourceRect.width, sourceRect.height},
                   destRect,
                   destOrigin, 0.f, WHITE);
};

void Sprite::DrawRect(float thickness)
{
    Rectangle destRect = GetDestRect();
    Vector2 destOrigin = GetDestOrigin(destRect);

    // DrawRectanglePro(destRect, destOrigin, 0.f, RED);

    destRect = DestPro(destRect, destOrigin);
    DrawRectangleLinesEx(destRect, thickness, RED);
};

Rectangle Sprite::GetBounds()
{
    Rectangle destRect = GetDestRect();
    Vector2 destOrigin = GetDestOrigin(destRect);
    return DestPro(destRect, destOrigin);
};

Vector2 Sprite::GetSpriteSourceSize()
{
    return {sourceRect.width, sourceRect.height};
};

bool Sprite::IsOnScreen()
{
    DisplayBridge& canvas = Application::Get().GetCanvas();
    return CheckCollisionRecs(GetBounds(),
                              {0, 0, canvas.canvasWidth, canvas.canvasHeight});
};