#pragma once
#include <string>

#include "raylib.h"

#include "../AnimationPlayer/AnimationPlayer.hpp"

enum Origins {
    O_TOP_LEFT,
    O_CENTER_LEFT,
    O_BOTTOM_LEFT,
    O_BOTTOM_CENTER,
    O_BOTTOM_RIGHT,
    O_CENTER_RIGHT,
    O_TOP_RIGHT,
    O_CENTER_TOP,
    O_CENTER
};

class Sprite
{
private:
    // variables
    Texture2D texture;
    bool textureLoaded {false};

    Rectangle sourceRect;
    Vector2 Origin;

    int spriteFramesX {1};
    int spriteFramesY {1};
    // functions

    [[nodiscard]] Rectangle GetDestRect();
    [[nodiscard]] Vector2 GetDestOrigin(Rectangle rect);
    [[nodiscard]] Rectangle DestPro(Rectangle dest, Vector2 origin);

    void LoadSprite(const std::string& texturePath);
    void LoadSprite(const std::string& texturePath, int spriteFramesX, int spriteFramesY);
    void LoadSprite(const Texture2D& sharedTexture);
public:
    // variables
    Vector2 position {0, 0};
    float rotation {0};
    Vector2 scale {1, 1};

    bool flip { false };

    // functions
    Sprite();
    Sprite(const std::string& texturePath);
    Sprite(const std::string& texturePath, int spriteFramesX, int spriteFramesY);
    Sprite(const Texture2D& sharedTexture);
    Sprite(const Texture2D& sharedTexture, int spriteFramesX, int spriteFramesY);
    ~Sprite();
    // void LoadSprite(const std::string& texturePath);
    // void LoadSprite(const std::string& texturePath, int spriteFramesX, int spriteFramesY);
    void SetOrigin(Origins origin_value);
    void SetFrame(int frameIndexX, int frameIndexY);
    void SetFrame(frameIndex);
    void Draw(float rotation = 0);
    void DrawRect(float thickness);
    bool IsOnScreen();

    [[nodiscard]] Vector2 GetSpriteSourceSize();

    [[nodiscard]] Vector2 GetRelativeScale();

    [[nodiscard]] Rectangle GetBounds();
};