#include "Sprite.hpp"

#include "raylib.h"

#include <print>

// use class heritance for other sprites as this as parent.

Sprite::Sprite()
{
}

Sprite::Sprite(const std::string& texture_path)
{
    LoadSprite(texture_path);
};

Sprite::Sprite(const std::string& texture_path, int spriteFramesX, int spriteFramesY)
    : spriteFramesX{spriteFramesX}, spriteFramesY{spriteFramesY}
{
    LoadSprite(texture_path);
};

Sprite::~Sprite()
{
    if (textureLoaded)
    {
        UnloadTexture(texture);
    }
}

void Sprite::LoadSprite(const std::string& texture_path)
{
    texture = LoadTexture(texture_path.c_str());
    textureLoaded = true;

    sourceRect = { 0.f, 0.f,
        static_cast<float>(texture.width) / spriteFramesX,
        static_cast<float>(texture.height) / spriteFramesY};

    SetOrigin(O_TOP_LEFT);
}

// void setFrame(int frameIndexX, int frameIndexY)
// {
//     int frame = frameIndexX;
//     int framez = frameIndexY;
// };

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
}

void Sprite::Draw()
{
    Rectangle destRect = { position.x, position.y, sourceRect.width * scale.x, sourceRect.height * scale.y};

    Vector2 destOrigin = {destRect.width * Origin.x, destRect.height * Origin.y};

    DrawTexturePro(texture, sourceRect, destRect, destOrigin, 0.f, WHITE);
}