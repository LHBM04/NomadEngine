#include "SDLWindow.h"

// 임시로 모든 플랫폼에서 SDL 사용 가능하도록 조건 제거
// #ifdef NOMAD_PLATFORM_LINUX

#include <iostream>

namespace NomadEngine::Editor
{
    SDLWindow::SDLWindow()
        : mWindow(nullptr)
        , mWidth(1280)
        , mHeight(720)
        , mIsMinimized(false)
        , mShouldClose(false)
    {
    }

    SDLWindow::~SDLWindow()
    {
        Finalize();
    }

    bool SDLWindow::Initialize(const WindowDescriptor& descriptor)
    {
        // SDL 초기화
        if (SDL_Init(SDL_INIT_VIDEO) < 0)
        {
            std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
            return false;
        }

        mWidth = descriptor.width;
        mHeight = descriptor.height;

        // 윈도우 플래그 설정
        Uint32 windowFlags = SDL_WINDOW_OPENGL;
        
        if (descriptor.resizable)
            windowFlags |= SDL_WINDOW_RESIZABLE;
        
        if (descriptor.maximized)
            windowFlags |= SDL_WINDOW_MAXIMIZED;
        
        if (descriptor.fullscreen)
            windowFlags |= SDL_WINDOW_FULLSCREEN;

        // OpenGL 속성 설정
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

        // 윈도우 생성
        mWindow = SDL_CreateWindow(
            descriptor.title.c_str(),
            static_cast<int>(mWidth),
            static_cast<int>(mHeight),
            windowFlags
        );

        if (!mWindow)
        {
            std::cerr << "Failed to create SDL window: " << SDL_GetError() << std::endl;
            SDL_Quit();
            return false;
        }

        std::cout << "SDL window initialized successfully" << std::endl;
        return true;
    }

    void SDLWindow::Finalize()
    {
        if (mWindow)
        {
            SDL_DestroyWindow(mWindow);
            mWindow = nullptr;
        }

        SDL_Quit();
    }

    bool SDLWindow::ProcessEvents()
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_EVENT_QUIT:
                mShouldClose = true;
                return false;

            case SDL_EVENT_WINDOW_RESIZED:
                mWidth = static_cast<uint32_t>(event.window.data1);
                mHeight = static_cast<uint32_t>(event.window.data2);
                break;

            case SDL_EVENT_WINDOW_MINIMIZED:
                mIsMinimized = true;
                break;

            case SDL_EVENT_WINDOW_RESTORED:
                mIsMinimized = false;
                break;
            }
        }

        return !mShouldClose;
    }

    void SDLWindow::BeginFrame()
    {
        // SDL 전용 프레임 시작 처리
    }

    void SDLWindow::EndFrame()
    {
        // SDL 전용 프레임 종료 처리
        // OpenGL의 경우 SDL_GL_SwapWindow가 여기서 호출됨
    }

    void* SDLWindow::GetNativeHandle() const
    {
        return static_cast<void*>(mWindow);
    }

    void SDLWindow::GetSize(uint32_t& width, uint32_t& height) const
    {
        width = mWidth;
        height = mHeight;
    }

    bool SDLWindow::IsMinimized() const
    {
        return mIsMinimized;
    }
}

// #endif // NOMAD_PLATFORM_LINUX (임시 제거)
