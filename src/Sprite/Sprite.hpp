#pragma once
#include <string>
#include "raylib.h"

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

public:
    // variables
    Vector2 position {0, 0};
    Vector2 scale {1, 1};


    // functions
    Sprite();
    Sprite(const std::string& texture_path);
    Sprite(const std::string& texture_path, int spriteFramesX, int spriteFramesY);
    ~Sprite();
    void LoadSprite(const std::string& texture_path);
    void SetOrigin(Origins origin_value);
    void SetFrame(int frameIndexX, int frameIndexY);
    void Draw();
};