#include "raylib.h"

#include "Application/DisplayBridge.hpp"
#include "Application/Application.hpp"
#include "Sprite/Sprite.hpp"
#include "Entities.hpp"
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

    Application &app = Application::Get(); // application singleton for window info and other systems in future

    app.StartUp(1920, 1080);


    #pragma endregion

    const float &canvasWidth = app.GetCanvas().canvasWidth;
    const float &canvasHeight = app.GetCanvas().canvasHeight;

    Sprite stage {"resources/tmp/Stage.png"};
    stage.SetOrigin(O_BOTTOM_CENTER);
    stage.position = {canvasWidth/2, canvasHeight};
    stage.scale = {.7f, .7f};

    Clown clown;
    CrowdPerson crowd;

    while (!WindowShouldClose())
    {
        app.GetCanvas().SetDisplaySize(static_cast<float>(GetScreenWidth()),
                                        static_cast<float>(GetScreenHeight()));

        clown.Update();
        crowd.Update();

        // std::println("{}", clown.IsOnScreen({canvasWidth, canvasHeight}));

        #pragma region CANVAS_RENDER
        app.GetCanvas().BeginTextureDraw();
        {
            ClearBackground(LIGHTGRAY);
            crowd.Draw();
            stage.Draw();
            clown.Draw();
        }
        app.GetCanvas().EndTextureDraw();
        #pragma endregion

        #pragma region SCREEN_RENDER
        BeginDrawing();
        {
            ClearBackground(BLACK); // Background if aspect ratios don't match

            app.GetCanvas().DrawBridge(SCALE_MAINTAIN_SCREEN);

            DrawFPS(10, 10);
        }
        EndDrawing();
        #pragma endregion
    }

    CloseWindow();
}
