#include "raylib.h"

#include "DisplayBridge/DisplayBridge.hpp"
#include "AnimationPlayer/AnimationPlayer.hpp"
#include "Sprite/Sprite.hpp"

#include <print>

int main()
{
    #pragma region SCREEN_INIT
    int screenWidth{500};
    int screenHeight{500};

    const int gameWidth = 1080; // Internal Render (720p
    const int gameHeight = 1080;

    // SetConfigFlags(FLAG_MSAA_4X_HINT);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    InitWindow(screenWidth, screenHeight, "Tosser the Clown");
    // ToggleBorderlessWindowed();
    // SetTargetFPS(60);
    SetWindowMinSize(300, 300);


    // display bridge for multi-resolution management
    DisplayBridge canvasTarget(gameWidth, gameHeight);
    canvasTarget.SetTexFilter(TEXTURE_FILTER_BILINEAR);
    #pragma endregion

    Sprite clown("resources/tmp/TosserSpritesheetTest.png", 9, 2);

    clown.scale = {1.f, 1.f};

    clown.position = {gameWidth / 2, gameHeight / 2};

    clown.SetOrigin(O_CENTER);

    AnimationSequence clownThrow = {
        "Throw",
        {0, 0}, // start frame
        9,      // how many frames long
        5,      // fps speed
        false,  // do loop
        {},     // what frames to pause on and how many frames for
    };

    AnimationSequence clownTalk = {
        "Talk",
        {0, 1}, // start frame
        2,      // how many frames long
        2,      // fps speed
        true,   // do loop
        {},     // what frames to pause on and how many frames for
    };

    AnimationPlayer clownAni;
    clownAni.PlayAnimation(clownThrow);

    frameIndex currentFrame = {clownAni.GetCurrentFrameIndex()};

    clown.SetFrame(currentFrame.x, currentFrame.y);

    bool popped = false;

    while (!WindowShouldClose())
    {
        if ((int)GetTime() != 0 && (int)GetTime() % 5 == 0 && !popped)
            {
                std::println("play ani");
                clownAni.PlayAnimation("Throw");
                popped = true;
            }

        clownAni.Update();

        if (clownAni.Finished())
            popped = false;
        // clownAni.PlayAnimation(clownTalk);

        // std::println("{}", clownAni.GetCurrentAnimationName());

        currentFrame = {clownAni.GetCurrentFrameIndex()};

        clown.SetFrame(currentFrame.x, currentFrame.y);

        #pragma region CANVAS_RENDER
        canvasTarget.BeginTextureDraw();
        {
            ClearBackground(LIGHTGRAY);
            clown.Draw();
            clown.DrawRect(5);
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
