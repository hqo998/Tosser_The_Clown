#include "SpriteController.hpp"

#include "raylib.h"


// use class heritance for other sprites as this as parent.

SpriteController::SpriteController()
{
}

SpriteController::SpriteController(const char *texture_path)
{
    LoadSprite(texture_path);
}

SpriteController::~SpriteController()
{
    if (textureLoaded)
    {
        UnloadTexture(texture);
    }
}

void SpriteController::LoadSprite(const char *texture_path)
{
    texture = LoadTexture(texture_path);
    textureLoaded = true;

    rect_width = static_cast<float>(texture.width);
    rect_height = static_cast<float>(texture.height);
}

void SpriteController::SetOrigin(Origins origin_value)
{
    switch (origin_value)
    {
    case O_TOP_LEFT:
        current_origin = {0.0f, 0.0f}; // Top-left corner
        break;
    case O_CENTER_LEFT:
        current_origin = {0.0f, rect_height * 0.5f}; // Middle of left edge
        break;
    case O_BOTTOM_LEFT:
        current_origin = {0.0f, rect_height}; // Bottom-left corner
        break;
    case O_BOTTOM_CENTER:
        current_origin = {rect_width * 0.5f, rect_height}; // Middle of bottom edge
        break;
    case O_BOTTOM_RIGHT:
        current_origin = {rect_width, rect_height}; // Bottom-right corner
        break;
    case O_CENTER_RIGHT:
        current_origin = {rect_width, rect_height * 0.5f}; // Middle of right edge
        break;
    case O_TOP_RIGHT:
        current_origin = {rect_width, 0.0f}; // Top-right corner
        break;
    case O_CENTER_TOP:
        current_origin = {rect_width * 0.5f, 0.0f}; // Middle of top edge
        break;
    case O_CENTER:
        current_origin = {rect_width * 0.5f, rect_height * 0.5f}; // Center of texture
        break;
    default:
        current_origin = {0.0f, 0.0f}; // Fallback to top-left
        break;
    }
}

void Draw()
{

}