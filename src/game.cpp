#include "raylib.h"

#include "DisplayBridge/DisplayBridge.hpp"

int main()
{
    int screenWidth{500};
    int screenHeight{500};

    const int gameWidth = 300; // Internal Render (720p
    const int gameHeight = 300;

    // SetConfigFlags(FLAG_MSAA_4X_HINT);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    InitWindow(screenWidth, screenHeight, "Tosser the Clown");
    // ToggleBorderlessWindowed();
    SetTargetFPS(60);
    SetWindowMinSize(300, 300);

    // load image
    Texture2D texture = LoadTexture("resources/tmp/coluredCircles.png");

    // base width
    const float baseWidth = 500.0f;

    DisplayBridge canvasTarget(gameWidth, gameHeight);
    canvasTarget.SetTexFilter(TEXTURE_FILTER_BILINEAR);

    while (!WindowShouldClose())
    {
        screenWidth = GetScreenWidth();
        screenHeight = GetScreenHeight();

        float scale = (float)gameWidth / baseWidth;

        Rectangle sourceRec = {0.0f, 0.0f, (float)texture.width, (float)texture.height};

        Rectangle destRec = {
            (float)gameWidth / 2.0f,
            (float)gameHeight / 2.0f,
            (float)texture.width * scale * .1f,
            (float)texture.height * scale * .1f};

        Vector2 origin = {
            (float)destRec.width * (float).5,
            (float)destRec.height * (float).5};

        canvasTarget.BeginTextureDraw();

            ClearBackground(RAYWHITE);

            DrawTexturePro(texture, sourceRec, destRec, origin, 0.0f, WHITE);

            canvasTarget.EndTextureDraw();

        BeginDrawing();
            ClearBackground(BLACK); // Background if aspect ratios don't match

            canvasTarget.SetDisplaySize(static_cast<float>(GetScreenWidth()),
                                        static_cast<float>(GetScreenHeight()));
            canvasTarget.DrawBridge(SCALE_MAINTAIN_SCREEN);
            canvasTarget.DrawBridge(NATIVE);
            canvasTarget.DrawDebugResolutions();

            Vector2 mousePos = canvasTarget.GetMousePositionScaled();

            DrawCircle((int)mousePos.x, (int)mousePos.y, 10, RED);

            // DrawText(TextFormat("Centre X Offset: %f", centredOriginOffset), 10, 40, 20, GREEN);
            DrawFPS(10, 10);
        EndDrawing();
    }

    UnloadTexture(texture);
    CloseWindow();

    return 0;
}
