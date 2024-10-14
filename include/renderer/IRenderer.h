#pragma once

class IRenderer {
public:
    virtual ~IRenderer() = default;

    virtual void initialize() = 0;
    virtual void clearScreen() = 0;
    virtual void render() = 0;
    virtual void swapBuffers() = 0;
    virtual void pollEvents() = 0;
    virtual bool shouldClose() = 0;
};
