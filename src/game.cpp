#include "raylib.h"

#include "DisplayBridge/DisplayBridge.hpp"
#include "Sprite/Sprite.hpp"
#include "Clown.hpp"
#include "Crowd.hpp"
#include <print>

int main()
{
    #pragma region SCREEN_INIT
    int screenWidth{500};
    int screenHeight{500};
    InitWindow(screenWidth, screenHeight, "Tosser the Clown");

    DisplayBridge canvasTarget(1080, 1080);
    canvasTarget.SetTexFilter(TEXTURE_FILTER_BILINEAR);

    // ToggleBorderlessWindowed();
    SetTargetFPS(60);
    SetWindowMinSize(300, 300);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT);
    #pragma endregion


    Sprite stage {"resources/tmp/Stage.png"};
    stage.SetOrigin(O_BOTTOM_CENTER);
    stage.position = {1080/2, 1080};
    stage.scale = {.7f, .7f};

    Clown clown;
    CrowdPerson crowd;

    while (!WindowShouldClose())
    {

        clown.Update();
        crowd.Update();

        #pragma region CANVAS_RENDER
        canvasTarget.BeginTextureDraw();
        {
            ClearBackground(LIGHTGRAY);
            crowd.Draw();
            stage.Draw();
            clown.Draw();

            

        }
        canvasTarget.EndTextureDraw();
        #pragma endregion

        #pragma region SCREEN_RENDER
        BeginDrawing();
        {
            ClearBackground(BLACK); // Background if aspect ratios don't match

            canvasTarget.SetDisplaySize(static_cast<float>(GetScreenWidth()),
                                        static_cast<float>(GetScreenHeight()));
            canvasTarget.DrawBridge(SCALE_MAINTAIN_SCREEN);

            DrawFPS(10, 10);
        }
        EndDrawing();
        #pragma endregion
    }


    CloseWindow();
}
