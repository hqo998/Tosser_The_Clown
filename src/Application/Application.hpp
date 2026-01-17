#pragma once

#include <raylib.h>
#include <memory>



#pragma region DISPLAY_BRIDGE
enum class bridgeMode
{
    STRETCH_TO_SCREEN,
    CENTRE_TO_SCREEN,
    SCALE_HEIGHT_CENTRE_TO_SCREEN,
    SCALE_MAINTAIN_SCREEN,
    NATIVE
}; // bridgeMode

// Image renders to a fixed render target which display bridge can then redraw on the screen in a controllable manner.
class DisplayBridge
{
public:
    // variables
    const float canvasWidth{};
    const float canvasHeight{};

    float displayWidth{};
    float displayHeight{};

    // functions
    DisplayBridge(float canvasWidth, float canvasHeight, float dispWidth, float dispHeight);
    DisplayBridge(float canvasWidth, float canvasHeight);

    DisplayBridge(DisplayBridge &db) = delete;

    ~DisplayBridge();

    void LoadTexture(float canvasWidth, float canvasHeight);
    void SetTexFilter(TextureFilter filterMode);
    void BeginTextureDraw();
    void EndTextureDraw();

    void DrawBridge(bridgeMode mode = bridgeMode::SCALE_HEIGHT_CENTRE_TO_SCREEN);

    void SetDisplaySize(float dispWidth, float dispHeight);
    Vector2 GetMousePositionScaled();
    Vector2 GetCanvasSize();

    void DrawDebugResolutions();

private:
    // variables
    RenderTexture2D target;
    bool texLoaded{};

}; // DisplayBridge
#pragma endregion


#pragma region APPLICATION
// Application singleton so that it can access the same info from anywhere.
class Application
{
    // constructors
    Application() = default;

    Application(const Application &) = default;
    Application(Application &&) = default;

    Application &operator=(const Application &) = default;
    Application &operator=(Application &&) = default;


    std::unique_ptr<DisplayBridge> canvas = nullptr;

public:
    // Always returns the same Application object.
    static Application& Get()
    {
        static Application onlyApplication{};

        return onlyApplication;
    }

    inline void StartUp(float width, float height)
    {
        canvas = std::make_unique<DisplayBridge>(width, height);
    }

    inline DisplayBridge& GetCanvas()
    {
        return *canvas;
    }
}; // Application
#pragma endregion // Application

