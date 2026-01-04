#include "raylib.h"
#include "SpriteControl/SpriteController.hpp"

int main()
{
    int screenWidth{500};
    int screenHeight{500};

    const int gameWidth = 2560;    // Internal Render (720p
    const int gameHeight = 1440;

    // SetConfigFlags(FLAG_MSAA_4X_HINT);
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);


    InitWindow(screenWidth, screenHeight, "Tosser the Clown");
    // ToggleBorderlessWindowed();
    SetTargetFPS(30);
    SetWindowMinSize(300, 300);


    // load image
    Texture2D texture = LoadTexture("resources/tmp/coluredCircles.png");

    // base width
    const float baseWidth = 500.0f;

    RenderTexture2D target = LoadRenderTexture(gameWidth, gameHeight);
    SetTextureFilter(target.texture, TEXTURE_FILTER_BILINEAR); // Smooth scaling

    while (!WindowShouldClose())
    {
        screenWidth = GetScreenWidth();
        screenHeight = GetScreenHeight();

        float scale = (float)gameWidth / baseWidth;

        Rectangle sourceRec = { 0.0f, 0.0f, (float)texture.width, (float)texture.height };

        Rectangle destRec = {
            (float)gameWidth / 2.0f,
            (float)gameHeight / 2.0f,
            (float)texture.width * scale * .1f,
            (float)texture.height * scale * .1f
        };

        Vector2 origin = {
            (float)destRec.width * (float).5,
            (float)destRec.height * (float).5
        };

        BeginTextureMode(target);
            ClearBackground(RAYWHITE);

            DrawTexturePro(texture, sourceRec, destRec, origin, 0.0f, WHITE);

        EndTextureMode();

        BeginDrawing();
            ClearBackground(RAYWHITE); // Background if aspect ratios don't match

            // Define source (720p) and destination rectangles with offset to make sure the target is always centred.
            Rectangle sourceRecTarget = { 0.0f, 0.0f, (float)target.texture.width, (float)-(target.texture.height) };

            float widthScaleTarget =  (float)screenHeight / target.texture.height;
            float centredWidth = (float)target.texture.width * widthScaleTarget;
            float centredOriginOffset = ((centredWidth - float(screenWidth))/2);

            Rectangle destRecTarget = { 0.0f, 0.0f, centredWidth, (float)screenHeight };
            Vector2 originTarget = { 0 + centredOriginOffset, 0 };

            DrawTexturePro(target.texture, sourceRecTarget, destRecTarget, originTarget, 0.0f, WHITE);

            DrawText(TextFormat("Centre X Offset: %f", centredOriginOffset), 10, 40, 20, GREEN);
            DrawFPS(10, 10);
        EndDrawing();
    }

    UnloadRenderTexture(target);
    UnloadTexture(texture);
    CloseWindow();

    return 0;
}
