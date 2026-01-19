#include "raylib.h"

#include "Application/Application.hpp"
#include "Sprite/Sprite.hpp"
#include "Entities.hpp"

#include <print>
#include <chrono>

int main()
{
    SetRandomSeed(static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count()));
    #pragma region SCREEN_INIT
    int screenWidth{1280};
    int screenHeight{720};

    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT | FLAG_WINDOW_HIGHDPI);
    InitWindow(screenWidth, screenHeight, "Tosser the Clown");

    SetWindowMinSize(300, 300);
    // ToggleBorderlessWindowed();
    // SetTargetFPS(60);

    // Application &app = Application::Get(); // application singleton for window info and other systems in future

    app.StartUp(1920, 1000);


    #pragma endregion

    const float &canvasWidth = app.GetCanvas().canvasWidth;
    const float &canvasHeight = app.GetCanvas().canvasHeight;

    Sprite stage {"resources/tmp/Stage.png"};
    stage.SetOrigin(O_BOTTOM_CENTER);
    stage.position = {canvasWidth/2, canvasHeight};
    Vector2 relativeScale = stage.GetRelativeScale();
    float adjustedScale = (relativeScale.x<relativeScale.y) ? relativeScale.x : relativeScale.y;
    float uniform_scale = 1.f * adjustedScale;
    stage.scale = {uniform_scale, uniform_scale};

    Clown clown;
    CrowdManager crowd;
    for (int i {}; i < 10; i++)
    {
        crowd.AddPerson();
    }



    while (!WindowShouldClose())
    {
        app.GetCanvas().SetDisplaySize(static_cast<float>(GetScreenWidth()),
                                        static_cast<float>(GetScreenHeight()));

        clown.Update();
        crowd.Update();

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

            app.GetCanvas().DrawBridge(bridgeMode::SCALE_MAINTAIN_SCREEN);

            DrawFPS(10, 10);
        }
        EndDrawing();
        #pragma endregion
    }

    CloseWindow();
}
