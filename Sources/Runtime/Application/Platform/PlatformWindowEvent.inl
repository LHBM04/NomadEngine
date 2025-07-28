namespace NomadEngine::Runtime
{
    PlatformWindowEvent TranslateSDL3Event(const SDL_Event& event_)
    {
        PlatformWindowEvent event = { };

        switch (event_.type)
        {
            case SDL_EVENT_WINDOW_RESIZED:
                event.type = PlatformWindowEvent::Type::WindowResized;
                event.window.width = event_.window.data1;
                event.window.height = event_.window.data2;
                break;

            case SDL_EVENT_WINDOW_CLOSE:
                event.type = PlatformWindowEvent::Type::WindowClosed;
                break;

            case SDL_EVENT_KEY_DOWN:
                event.type = PlatformWindowEvent::Type::KeyPressed;
                event.key.code = event_.key.keysym.sym;
                break;

            case SDL_EVENT_KEY_UP:
                event.type = PlatformWindowEvent::Type::KeyReleased;
                event.key.code = event_.key.keysym.sym;
                break;

            case SDL_EVENT_MOUSE_BUTTON_DOWN:
                event.type = PlatformWindowEvent::Type::MouseButtonPressed;
                event.mouse.button = event_.button.button;
                break;

            case SDL_EVENT_MOUSE_BUTTON_UP:
                event.type = PlatformWindowEvent::Type::MouseButtonReleased;
                event.mouse.button = event_.button.button;
                break;

            case SDL_EVENT_MOUSE_MOTION:
                event.type = PlatformWindowEvent::Type::MouseMoved;
                event.mouse.x = event_.motion.x;
                event.mouse.y = event_.motion.y;
                break;

            default:
                std::cerr << "Unhandled event type: " << event_.type << std::endl;
                return {};
        }

        return event;
    }

    PlatformWindowEvent TranslateWin32Event(const MSG& msg_)
    {

    }
}
