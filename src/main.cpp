#include "raylib.h"

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Tosser the Clown");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("Tosser the Clown!", screenWidth/2, screenHeight/2, 20, LIGHTGRAY);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
