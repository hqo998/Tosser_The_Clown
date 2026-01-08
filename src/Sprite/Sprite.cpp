#include "Sprite.hpp"

#include "raylib.h"

#include <print>

// use class heritance for other sprites as this as parent.

Sprite::Sprite()
{
}

Sprite::Sprite(const std::string& texture_path)
{
    LoadSprite(texture_path.c_str());
}

Sprite::~Sprite()
{
    if (textureLoaded)
    {
        UnloadTexture(texture);
    }
}

void Sprite::LoadSprite(const char *texture_path)
{
    texture = LoadTexture(texture_path);
    textureLoaded = true;

    sourceRect = { 0.f, 0.f, static_cast<float>(texture.width), static_cast<float>(texture.height) };

    SetOrigin(O_TOP_LEFT);
}

void Sprite::SetOrigin(Origins origin_value)
{
    switch (origin_value)
    {
    case O_CENTER_LEFT:
        currentOrigin = {0.0f, sourceRect.height * 0.5f}; // Middle of left edge
        break;
    case O_BOTTOM_LEFT:
        currentOrigin = {0.0f, sourceRect.height}; // Bottom-left corner
        break;
    case O_BOTTOM_CENTER:
        currentOrigin = {sourceRect.width * 0.5f, sourceRect.height}; // Middle of bottom edge
        break;
    case O_BOTTOM_RIGHT:
        currentOrigin = {sourceRect.width, sourceRect.height}; // Bottom-right corner
        break;
    case O_CENTER_RIGHT:
        currentOrigin = {sourceRect.width, sourceRect.height * 0.5f}; // Middle of right edge
        break;
    case O_TOP_RIGHT:
        currentOrigin = {sourceRect.width, 0.0f}; // Top-right corner
        break;
    case O_CENTER_TOP:
        currentOrigin = {sourceRect.width * 0.5f, 0.0f}; // Middle of top edge
        break;
    case O_CENTER:
        currentOrigin = {sourceRect.width * 0.5f, sourceRect.height * 0.5f}; // Center of texture
        break;
    case O_TOP_LEFT:
    default:
        currentOrigin = {0.0f, 0.0f}; // Fallback to top-left
        break;
    }
}

void Sprite::Draw()
{
    Rectangle destRect = { position.x, position.y, sourceRect.width * scale.x, sourceRect.height * scale.y};

    DrawTexturePro(texture, sourceRect, destRect, currentOrigin, 0.f, WHITE);
}