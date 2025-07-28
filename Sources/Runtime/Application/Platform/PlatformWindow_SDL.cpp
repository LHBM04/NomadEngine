#include "Application/Platform/PlatformWindow_SDL.h"

#include <iostream>

#include "SDL3/SDL_video.h"
#include "SDL3/SDL_init.h"

namespace NomadEngine::Runtime
{
    PlatformWindow_SDL::PlatformWindow_SDL(
        std::wstring_view caption_,
        int width,
        int height)
        : PlatformWindowBase(
            L"NomadEngine",
            1280,
            720)
        , mWindow(nullptr)
    {

    }

    PlatformWindow_SDL::~PlatformWindow_SDL()
    {
        if (mWindow)
        {
            SDL_DestroyWindow(mWindow);
            mWindow = nullptr;
        }
    }

    bool PlatformWindow_SDL::Initialize()
    {
        if (!SDL_WasInit(SDL_INIT_VIDEO))
        {
            std::wcerr << L"SDL 초기화 안됨." << std::endl;
            return false;
        }

        mWindow =  SDL_CreateWindow(
                "NomadEngine",
                GetWidth(),
                GetHeight(),
                SDL_WINDOW_RESIZABLE);

        if (!mWindow)
        {
            std::wcerr << L"SDL 윈도우 생성 실패: " << SDL_GetError() << std::endl;
            return false;
        }

        return true;
    }

    PlatformData PlatformWindow_SDL::GetPlatformData() const
    {
        PlatformData data;
        data.type = PlatformData::EType::SDL;
        data.window = mWindow;
        return data;
    }

    WindowHandle PlatformWindow_SDL::GetWindowHandle() const
    {
        return static_cast<WindowHandle>(mWindow);
    }

    bool PlatformWindow_SDL::ProcessMessages()
    {
        SDL_Event event;

        // 큐에 있는 모든 이벤트 처리
        while (SDL_PollEvent(&event))
        {
            // SDL3 이벤트를 추상화된 메시지로 변환
            Message abstractMessage = ConvertMessage(event);

            // 변환된 메시지가 유효한 경우 디스패치
            if (abstractMessage.type != Message::EType::None)
            {
                DispatchEvent(abstractMessage);
            }

            // 종료 이벤트 처리
            if (event.type == SDL_EVENT_QUIT)
            {
                return false; // 종료 신호
            }

            // 윈도우 포커스 관련 이벤트 처리
            if (event.type == SDL_EVENT_WINDOW_FOCUS_GAINED)
            {
                mFocused = true;
            }
            else if (event.type == SDL_EVENT_WINDOW_FOCUS_LOST)
            {
                mFocused = false;
            }
        }

        return true; // 계속 실행
    }

    Message PlatformWindow_SDL::ConvertMessage(const SDL_Event& event)
    {
        Message message;
        message.type = Message::EType::None;
        message.native = const_cast<void*>(static_cast<const void*>(&event));

        switch (event.type)
        {
            case SDL_EVENT_QUIT:
                message.type = Message::EType::Quit;
                break;

            case SDL_EVENT_KEY_DOWN:
                message.type = Message::EType::KeyDown;
                message.keyCode = static_cast<int>(event.key.key);
                break;

            case SDL_EVENT_KEY_UP:
                message.type = Message::EType::KeyUp;
                message.keyCode = static_cast<int>(event.key.key);
                break;

            case SDL_EVENT_MOUSE_MOTION:
                message.type = Message::EType::MouseMove;
                message.x = static_cast<int>(event.motion.x);
                message.y = static_cast<int>(event.motion.y);
                break;

            case SDL_EVENT_MOUSE_BUTTON_DOWN:
                message.type = Message::EType::MouseButtonDown;
                message.keyCode = static_cast<int>(event.button.button - 1); // SDL uses 1-based, we use 0-based
                message.x = static_cast<int>(event.button.x);
                message.y = static_cast<int>(event.button.y);
                break;

            case SDL_EVENT_MOUSE_BUTTON_UP:
                message.type = Message::EType::MouseButtonUp;
                message.keyCode = static_cast<int>(event.button.button - 1); // SDL uses 1-based, we use 0-based
                message.x = static_cast<int>(event.button.x);
                message.y = static_cast<int>(event.button.y);
                break;
        }

        return message;
    }
}