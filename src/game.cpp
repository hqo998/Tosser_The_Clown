#include "raylib.h"

#include "DisplayBridge/DisplayBridge.hpp"
#include "Sprite/Sprite.hpp"

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

    // display bridge for multi-resolution management
    DisplayBridge canvasTarget(gameWidth, gameHeight);
    canvasTarget.SetTexFilter(TEXTURE_FILTER_BILINEAR);

    Sprite clown("resources/tmp/TosserSpritesheetTest.png");

    while (!WindowShouldClose())
    {

        canvasTarget.BeginTextureDraw();

            ClearBackground(RAYWHITE);

            clown.Draw();

            // DrawTexturePro(texture, sourceRec, destRec, origin, 0.0f, WHITE);

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
