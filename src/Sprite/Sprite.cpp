#include "Sprite.hpp"

#include "raylib.h"


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

    sourceRect.x = static_cast<float>(texture.width);
    sourceRect.y = static_cast<float>(texture.height);

    SetOrigin(O_CENTER);
}

void Sprite::SetOrigin(Origins origin_value)
{
    switch (origin_value)
    {
    case O_TOP_LEFT:
        currentOrigin = {0.0f, 0.0f}; // Top-left corner
        break;
    case O_CENTER_LEFT:
        currentOrigin = {0.0f, sourceRect.y * 0.5f}; // Middle of left edge
        break;
    case O_BOTTOM_LEFT:
        currentOrigin = {0.0f, sourceRect.y}; // Bottom-left corner
        break;
    case O_BOTTOM_CENTER:
        currentOrigin = {sourceRect.x * 0.5f, sourceRect.y}; // Middle of bottom edge
        break;
    case O_BOTTOM_RIGHT:
        currentOrigin = {sourceRect.x, sourceRect.y}; // Bottom-right corner
        break;
    case O_CENTER_RIGHT:
        currentOrigin = {sourceRect.x, sourceRect.y * 0.5f}; // Middle of right edge
        break;
    case O_TOP_RIGHT:
        currentOrigin = {sourceRect.x, 0.0f}; // Top-right corner
        break;
    case O_CENTER_TOP:
        currentOrigin = {sourceRect.x * 0.5f, 0.0f}; // Middle of top edge
        break;
    case O_CENTER:
        currentOrigin = {sourceRect.x * 0.5f, sourceRect.y * 0.5f}; // Center of texture
        break;
    default:
        currentOrigin = {0.0f, 0.0f}; // Fallback to top-left
        break;
    }
}

void Sprite::Draw()
{
    Rectangle destRect = { position.x, position.y, sourceRect.x, sourceRect.y};

    DrawTexturePro(texture, sourceRect, destRect, currentOrigin, 0.f, WHITE);
}