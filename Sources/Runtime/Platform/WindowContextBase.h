#ifndef WINDOWCONTEXTBASE_H
#define WINDOWCONTEXTBASE_H

#include <SDL3/SDL.h>

class WindowContextBase
{
public:
    WindowContextBase() = default;
    virtual ~WindowContextBase();

    virtual bool Initialize(const char* title, int width, int height);
    virtual void ProcessEvents() = 0;
    virtual void Render() = 0;
    virtual void CleanUp();

    bool IsRunning() const { return bIsRunning; }

protected:
    SDL_Window* m_window = nullptr;
    bool bIsRunning = true;
};

#endif // !WINDOWCONTEXTBASE_H