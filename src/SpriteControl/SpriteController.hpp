#pragma once
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

class SpriteController
{
private:
    // variables
    Texture2D texture;
    bool textureLoaded {false};

    float rect_width, rect_height;

    Vector2 current_origin;

    // functions
    ~SpriteController();
public:
    // variables
    Vector2 position;
    Vector2 scale;
    

    // functions
    SpriteController();
    SpriteController(const char *texture_path);
    void LoadSprite(const char *texture_path);
    void SetOrigin(Origins origin_value);
    void Draw();
};