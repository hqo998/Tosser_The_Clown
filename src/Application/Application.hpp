#pragma once

#include <memory>

#include "DisplayBridge.hpp"


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
};