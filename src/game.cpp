#include "raylib.h"

#include "GameObject.hpp"
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
    SetTargetFPS(60);

    app.StartUp(1920, 1080);


    #pragma endregion


    game.Init();


    while (!WindowShouldClose())
    {
        app.GetCanvas().SetDisplaySize(static_cast<float>(GetScreenWidth()),
                                        static_cast<float>(GetScreenHeight()));

        game.Update();

        #pragma region CANVAS_RENDER
        app.GetCanvas().BeginTextureDraw();
        {
            game.Draw();
            ClearBackground(LIGHTGRAY);

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
