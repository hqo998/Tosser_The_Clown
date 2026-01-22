#include "Application/Application.hpp"
#include "GameObject.hpp"
#include "Entities.hpp"

void GameInstance::Init()
{

    const float canvasWidth = app.GetCanvas().canvasWidth;
    const float canvasHeight = app.GetCanvas().canvasHeight;

    auto stage = CreateGameObject<Sprite>("resources/tmp/Stage.png");

    stage->SetOrigin(O_BOTTOM_CENTER);
    stage->position = {canvasWidth / 2, canvasHeight};
    Vector2 relativeScale = stage->GetRelativeScale();
    float adjustedScale = (relativeScale.x < relativeScale.y) ? relativeScale.x : relativeScale.y;
    float uniform_scale = 1.f * adjustedScale;
    stage->scale = {uniform_scale, uniform_scale};

    auto crowdManager = CreateGameObject<CrowdManager>();

    for (int i{}; i < 5; i++)
    {
        crowdManager->AddPerson();
    }

    CreateGameObject<Clown>()->zOrder = 10;
}

void GameInstance::Shutdown()
{
}
