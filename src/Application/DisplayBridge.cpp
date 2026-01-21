#include "Application.hpp"

#include <raylib.h>

DisplayBridge::DisplayBridge(float canvasWidth, float canvasHeight, float dispWidth, float dispHeight)
    : canvasWidth{canvasWidth}, canvasHeight{canvasHeight}, displayWidth{dispWidth}, displayHeight{dispHeight}
{
    LoadTexture(canvasWidth, canvasHeight);
}; // DisplayBridge

DisplayBridge::DisplayBridge(float canvasWidth, float canvasHeight)
    : canvasWidth{canvasWidth}, canvasHeight{canvasHeight}
{
    displayWidth = static_cast<float>(GetScreenWidth());
    displayHeight = static_cast<float>(GetScreenHeight());

    LoadTexture(canvasWidth, canvasHeight);
}; // DisplayBridge

DisplayBridge::~DisplayBridge()
{
    if (texLoaded)
    {
        UnloadRenderTexture(target);
    }
}; // ~DisplayBridge

void DisplayBridge::LoadTexture(float canWidth, float canHeight)
{
    target = LoadRenderTexture(static_cast<int>(canWidth), static_cast<int>(canHeight));
    texLoaded = true;
    SetTexFilter(TEXTURE_FILTER_BILINEAR);
}; // LoadTexture

void DisplayBridge::SetDisplaySize(float dispWidth, float dispHeight)
{
    this->displayWidth = dispWidth;
    this->displayHeight = dispHeight;
};

void DisplayBridge::SetTexFilter(TextureFilter filterMode)
{
    SetTextureFilter(target.texture, filterMode);
}; // SetTexFilter

void DisplayBridge::BeginTextureDraw()
{
    BeginTextureMode(target);
}; // BeginTextureDraw

void DisplayBridge::EndTextureDraw()
{
    EndTextureMode();
}; // EndTextureDraw

void DisplayBridge::DrawBridge(bridgeMode mode)
{
    Rectangle sourceRecTarget = {0.0f, 0.0f,
                                 (canvasWidth),
                                 -(canvasHeight)};

    Rectangle destRecTarget = {0.0f, 0.0f,
                               displayWidth,
                               displayHeight};

    Vector2 originTarget = {0.0f, 0.0f}; // centre of canvas

    switch (mode)
    {
    case bridgeMode::NATIVE:
        destRecTarget = {0, 0,
                         canvasWidth,
                         canvasHeight};
        break;
    case bridgeMode::STRETCH_TO_SCREEN:
        break;
    case bridgeMode::CENTRE_TO_SCREEN:
        originTarget = {canvasWidth / 2, canvasHeight / 2};

        destRecTarget = {displayWidth / 2, displayHeight / 2,
                         (canvasWidth),
                         (canvasHeight)};
        break;
    case bridgeMode::SCALE_MAINTAIN_SCREEN:
    {
        float heightScaledToWidth = (displayWidth / canvasWidth) * canvasHeight;

        originTarget = {displayWidth / 2, heightScaledToWidth / 2};

        destRecTarget = {displayWidth / 2, displayHeight / 2,
                         displayWidth,
                         heightScaledToWidth};
        if (heightScaledToWidth < displayHeight)
            break;
    } // case CENTRE_TO_SCREEN local scope
    case bridgeMode::SCALE_HEIGHT_CENTRE_TO_SCREEN:
    default:
    {
        float widthScaledToHeight = (displayHeight / canvasHeight) * canvasWidth;

        originTarget = {widthScaledToHeight / 2, displayHeight / 2};

        destRecTarget = {displayWidth / 2, displayHeight / 2,
                         widthScaledToHeight,
                         displayHeight};
        break;
    } // case default local scope
    } // switch

    DrawTexturePro(target.texture, sourceRecTarget, destRecTarget, originTarget, 0.0f, WHITE);
    // DrawCircle((int)originTarget.x, (int)originTarget.y, 20, RED);
    // DrawText(TextFormat("Origin: x=%f y=%f", originTarget.x, originTarget.y), 10, (int)50, 20, RED);
};

void DisplayBridge::DrawDebugResolutions()
{
    DrawText(TextFormat("RenderCanvas: x=%f y=%f", canvasWidth, canvasHeight), 10, (int)displayHeight - 50, 20, GREEN);
    DrawText(TextFormat("Display: x=%f y=%f", displayWidth, displayHeight), 10, (int)displayHeight - 20, 20, GREEN);
}; // DrawDebugResolutions

Vector2 DisplayBridge::GetMousePositionCanvas()
{
    Vector2 realMousePosition = GetMousePosition();

    if (displayWidth <= 0 || displayHeight <= 0)
        return {0, 0};

    Vector2 scaledMousePosition{(realMousePosition.x / displayWidth) * canvasWidth,
                                (realMousePosition.y / displayHeight) * canvasHeight};
    return scaledMousePosition;
}; // GetMousePositionCanvas

Vector2 DisplayBridge::GetCanvasSize()
{
    return {canvasWidth, canvasHeight};
}; // GetCanvasSize