#include "raylib.h"

#include "DisplayBridge/DisplayBridge.hpp"
#include "Sprite/Sprite.hpp"
#include "Entities.hpp"
#include "Crowd.hpp"
#include <print>

int main()
{
    #pragma region SCREEN_INIT
    int screenWidth{500};
    int screenHeight{500};

    
    
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT | FLAG_WINDOW_HIGHDPI);
    InitWindow(screenWidth, screenHeight, "Tosser the Clown");

    SetWindowMinSize(300, 300);
    // ToggleBorderlessWindowed();
    SetTargetFPS(60);

    DisplayBridge canvasTarget(1920, 1080);
    canvasTarget.SetTexFilter(TEXTURE_FILTER_BILINEAR);

    #pragma endregion

    const float &canvasWidth = canvasTarget.canvasWidth;
    const float &canvasHeight = canvasTarget.canvasHeight;

    Sprite stage {"resources/tmp/Stage.png"};
    stage.SetOrigin(O_BOTTOM_CENTER);
    stage.position = {canvasWidth/2, canvasHeight};
    stage.scale = {.7f, .7f};

    Clown clown;
    CrowdPerson crowd;
    
    while (!WindowShouldClose())
    {

        clown.Update();
        crowd.Update();

        std::println("{}", clown.IsOnScreen({canvasWidth, canvasHeight}));

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
