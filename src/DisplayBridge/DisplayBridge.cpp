#include "DisplayBridge.hpp"


DisplayBridge::DisplayBridge(int renWidth, int renHeight, int dispWidth, int dispHeight)
    :   renderWidth{renWidth}, renderHeight{renHeight}, displayWidth{dispWidth}, displayHeight{dispHeight}
{
};

void DisplayBridge::TexFilter(TextureFilter filterMode)
{
    SetTextureFilter(target.texture, filterMode);
};

void DisplayBridge::BeginTextureDraw()
{
    BeginTextureMode(target);
};

void DisplayBridge::EndTextureDraw()
{
    EndTextureMode();
};

void drawBridge(bridgeMode mode)
{
    switch (mode)
    {
        case STRETCH_TO_SCREEN:
            break;
        case FIT_TO_SCREEN:
        default:
            break;
    }
};