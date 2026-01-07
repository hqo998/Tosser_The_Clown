#include "DisplayBridge.hpp"

#include <raylib.h>

DisplayBridge::DisplayBridge(float canvasWidth, float canvasHeight, float dispWidth, float dispHeight)
    : canvasWidth{canvasWidth}, canvasHeight{canvasHeight}, displayWidth{dispWidth}, displayHeight{dispHeight}
{
    LoadTexture(canvasWidth, canvasHeight);
};

DisplayBridge::DisplayBridge(float canvasWidth, float canvasHeight)
    : canvasWidth{canvasWidth}, canvasHeight{canvasHeight}
{
    displayWidth = static_cast<float>(GetScreenWidth());
    displayHeight = static_cast<float>(GetScreenHeight());

    LoadTexture(canvasWidth, canvasHeight);
};

DisplayBridge::~DisplayBridge()
{
    if (texLoaded)
    {
        UnloadRenderTexture(target);
    }
};

void DisplayBridge::LoadTexture(float canWidth, float canHeight)
{
    target = LoadRenderTexture(static_cast<int>(canWidth), static_cast<int>(canHeight));
    texLoaded = true;
    SetTexFilter(TEXTURE_FILTER_BILINEAR);
};

void DisplayBridge::SetDisplaySize(float dispWidth, float dispHeight)
{
    this->displayWidth = dispWidth;
    this->displayHeight = dispHeight;
};

void DisplayBridge::SetTexFilter(TextureFilter filterMode)
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

void DisplayBridge::DrawBridge(bridgeMode mode)
{
    Rectangle sourceRecTarget = {0.0f, 0.0f,
                                 (canvasWidth),
                                 -(canvasHeight)};

    Rectangle destRecTarget = {0.0f, 0.0f,
                               displayWidth,
                               displayHeight};

    Vector2 originTarget = {0.0f, 0.0f}; // centre of canvas

    float widthScaledToHeight{0};
    float heightScaledToWidth{0};

    switch (mode)
    {
    case NATIVE:
        destRecTarget = {0, 0,
                         canvasWidth,
                         canvasHeight};
        break;
    case STRETCH_TO_SCREEN:
        break;
    case CENTRE_TO_SCREEN:
        originTarget = {canvasWidth / 2, canvasHeight / 2};

        destRecTarget = {displayWidth / 2, displayHeight / 2,
                         (canvasWidth),
                         (canvasHeight)};
        break;
    case SCALE_MAINTAIN_SCREEN:
        heightScaledToWidth = (displayWidth / canvasWidth) * canvasHeight;

        originTarget = {displayWidth / 2, heightScaledToWidth / 2};

        destRecTarget = {displayWidth / 2, displayHeight / 2,
                         displayWidth,
                         heightScaledToWidth};
        if (heightScaledToWidth < displayHeight)
            break;
    case SCALE_HEIGHT_CENTRE_TO_SCREEN:
    default:
        widthScaledToHeight = (displayHeight / canvasHeight) * canvasWidth;

        originTarget = {widthScaledToHeight / 2, displayHeight / 2};

        destRecTarget = {displayWidth / 2, displayHeight / 2,
                         widthScaledToHeight,
                         displayHeight};
        break;
    }

    DrawTexturePro(target.texture, sourceRecTarget, destRecTarget, originTarget, 0.0f, WHITE);
    DrawCircle((int)originTarget.x, (int)originTarget.y, 20, RED);
    DrawText(TextFormat("Origin: x=%f y=%f", originTarget.x, originTarget.y), 10, (int)50, 20, RED);
};

void DisplayBridge::DrawDebugResolutions()
{
    DrawText(TextFormat("RenderCanvas: x=%f y=%f", canvasWidth, canvasHeight), 10, (int)displayHeight - 50, 20, GREEN);
    DrawText(TextFormat("Display: x=%f y=%f", displayWidth, displayHeight), 10, (int)displayHeight - 20, 20, GREEN);
};

Vector2 DisplayBridge::GetMousePositionScaled()
{
    Vector2 realMousePosition = GetMousePosition();

    if (displayWidth <= 0 || displayHeight <= 0)
        return {0, 0};

    Vector2 scaledMousePosition{(realMousePosition.x / displayWidth) * canvasWidth,
                                (realMousePosition.y / displayHeight) * canvasHeight};
    return scaledMousePosition;
};