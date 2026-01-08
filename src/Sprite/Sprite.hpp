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

// cant redefine since raylib has def as float.
struct Vector2int
{
    int x {};
    int y {};
};

class Sprite
{
private:
    // variables
    Texture2D texture;
    bool textureLoaded {false};

    Rectangle sourceRect;
    Vector2 currentOrigin;

    int spriteFrames;
    // functions

public:
    // variables
    Vector2 position {0, 0};
    Vector2 scale {0, 0};


    // functions
    Sprite();
    Sprite(const std::string& texture_path);
    ~Sprite();
    void LoadSprite(const char *texture_path);
    void SetOrigin(Origins origin_value);
    void Draw();
};