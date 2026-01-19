#include "Application/Application.hpp"

#include "Entities.hpp"

AimGuide::AimGuide()
{
    texture = LoadTexture("resources/tmp/AimGuider_Sprite.png");
    SetTextureWrap(texture, TEXTURE_WRAP_CLAMP);

    for (int i = 0; i < 5; i++)
    {
        guidePoints.push_back({texture, 2, 1});
    }

    for (auto point : guidePoints)
    {
        point.SetOrigin(O_CENTER);
    }
};

void AimGuide::Hide()
{
    for (auto point : guidePoints)
    {
        point.SetFrame({1, 0});
    }
};

void AimGuide::Show()
{
    for (auto point : guidePoints)
    {
        point.SetFrame({0, 0});
    }
};

void AimGuide::Draw()
{
    int i = 0;
    for (auto point : guidePoints)
    {
        point.Draw();
        i++;
    }
};

void AimGuide::Update()
{

};