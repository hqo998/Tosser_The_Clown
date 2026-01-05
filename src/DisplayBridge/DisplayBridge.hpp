#pragma once

#include <raylib.h>

enum bridgeMode
{
    STRETCH_TO_SCREEN,
    FIT_TO_SCREEN,
};

class DisplayBridge
{
public:
    // variables
    int renderWidth {};
    int renderHeight {};

    int displayWidth {};
    int displayHeight {};

    // functions
    DisplayBridge(int renWidth, int renHeight, int dispWidth, int dispHeight);

    void TexFilter(TextureFilter filterMode);
    void BeginTextureDraw();
    void EndTextureDraw();

    void drawBridge(bridgeMode mode = FIT_TO_SCREEN);

private:
    // variables
    RenderTexture2D target;

    // functions

};