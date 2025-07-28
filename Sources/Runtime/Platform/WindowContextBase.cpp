#include "WindowContextBase.h"

WindowContextBase::~WindowContextBase()
{
    CleanUp();
}

bool WindowContextBase::Initialize(const char* title, int width, int height)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        // Initialization failed
        return false;
    }

    m_window = SDL_CreateWindow(title, width, height, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
    if (!m_window)
    {
        // Window creation failed
        SDL_Quit();
        return false;
    }

    return true;
}

void WindowContextBase::CleanUp()
{
    if (m_window)
    {
        SDL_DestroyWindow(m_window);
        m_window = nullptr;
    }
    SDL_Quit();
}