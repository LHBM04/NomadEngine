    PlatformData PlatformWindow_SDL3::GetPlatformData() const
    {
        PlatformData data;
        data.type = PlatformData::EType::SDL3;
        data.window = mWindow;
        return data;
    }

    WindowHandle PlatformWindow_SDL3::GetWindowHandle() const
    {
        return static_cast<WindowHandle>(mWindow);
    }

    bool PlatformWindow_SDL3::ProcessMessages()
    {
        SDL_Event event;

        // SDL3 이벤트를 PlatformWindowEvent로 변환하여 큐에 추가
        while (SDL_PollEvent(&event))
        {
            PlatformWindowEvent platformEvent = ConvertSDLEvent(event);

            if (platformEvent.type != PlatformWindowEvent::EType::None)
            {
                mWindowEventQueue.push(platformEvent);
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

    PlatformWindowEvent PlatformWindow_SDL3::ConvertNativeEvent(void* nativeEvent)
    {
        // SDL3에서는 SDL_Event 구조체를 받아서 처리
        SDL_Event* event = static_cast<SDL_Event*>(nativeEvent);
        return ConvertSDLEvent(*event);
    }

    PlatformWindowEvent PlatformWindow_SDL3::ConvertSDLEvent(const SDL_Event& event)
    {
        PlatformWindowEvent platformEvent;
        platformEvent.type = PlatformWindowEvent::EType::None;
        platformEvent.native = const_cast<void*>(static_cast<const void*>(&event));

        switch (event.type)
        {
            case SDL_EVENT_QUIT:
                platformEvent.type = PlatformWindowEvent::EType::Quit;
                break;

            case SDL_EVENT_KEY_DOWN:
                platformEvent.type = PlatformWindowEvent::EType::KeyDown;
                platformEvent.keyCode = static_cast<int>(event.key.key);
                break;

            case SDL_EVENT_KEY_UP:
                platformEvent.type = PlatformWindowEvent::EType::KeyUp;
                platformEvent.keyCode = static_cast<int>(event.key.key);
                break;

            case SDL_EVENT_MOUSE_MOTION:
                platformEvent.type = PlatformWindowEvent::EType::MouseMove;
                platformEvent.x = static_cast<int>(event.motion.x);
                platformEvent.y = static_cast<int>(event.motion.y);
                break;

            case SDL_EVENT_MOUSE_BUTTON_DOWN:
                platformEvent.type = PlatformWindowEvent::EType::MouseButtonDown;
                platformEvent.keyCode = static_cast<int>(event.button.button - 1); // SDL uses 1-based, we use 0-based
                platformEvent.x = static_cast<int>(event.button.x);
                platformEvent.y = static_cast<int>(event.button.y);
                break;

            case SDL_EVENT_MOUSE_BUTTON_UP:
                platformEvent.type = PlatformWindowEvent::EType::MouseButtonUp;
                platformEvent.keyCode = static_cast<int>(event.button.button - 1); // SDL uses 1-based, we use 0-based
                platformEvent.x = static_cast<int>(event.button.x);
                platformEvent.y = static_cast<int>(event.button.y);
                break;
        }

        return platformEvent;
    }
