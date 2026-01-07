#pragma once

#include <raylib.h>

enum bridgeMode
{
    STRETCH_TO_SCREEN,
    CENTRE_TO_SCREEN,
    SCALE_HEIGHT_CENTRE_TO_SCREEN,
    SCALE_MAINTAIN_SCREEN,
    NATIVE
};

class DisplayBridge
{
public:
    // variables
    float canvasWidth {};
    float canvasHeight {};

    float displayWidth {};
    float displayHeight {};

    // functions
    DisplayBridge(float canvasWidth, float canvasHeight, float dispWidth, float dispHeight);
    DisplayBridge(float canvasWidth, float canvasHeight);

    DisplayBridge(DisplayBridge& db) = delete;

    ~DisplayBridge();

    void LoadTexture(float canvasWidth, float canvasHeight);
    void SetTexFilter(TextureFilter filterMode);
    void BeginTextureDraw();
    void EndTextureDraw();

    void DrawBridge(bridgeMode mode = SCALE_HEIGHT_CENTRE_TO_SCREEN);

    void SetDisplaySize(float dispWidth, float dispHeight);
    Vector2 GetMousePositionScaled();

    void DrawDebugResolutions();
private:
    // variables
    RenderTexture2D target;
    bool texLoaded {};

    // functions
    

};