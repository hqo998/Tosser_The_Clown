#include "Cursor.hpp"
#include <raylib.h>

#include <print>

Cursor::Cursor() : Sprite("resources/tmp/cursor.png", 2, 1)
{
    HideCursor();
}

void Cursor::Update()
{
    position = {GetMousePosition()};

    SetOrigin(O_CENTER_TOP);

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
        SetFrame(2,1); // switch to second when held down
    }
    else
    {
        SetFrame(1, 1);
    }

}

void Cursor::Draw()
{
    // std::println("drawing cursor");
    Sprite::Draw();
}