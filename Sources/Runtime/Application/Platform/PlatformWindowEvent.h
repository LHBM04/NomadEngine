#ifndef GUARD_PLATFORMWINDOWEVENT_H
#define GUARD_PLATFORMWINDOWEVENT_H

#include <iostream>

#include "SDL_events.h"
#include "SDL_system.h"

namespace NomadEngine::Runtime
{
    /**
     * @brief 각 플랫폼의 윈도우에서 발생하는 이벤트를 정의합니다.
     */
    struct PlatformWindowEvent
    {
        /**
         * @brief 이벤트 타입을 정의합니다.
         */
        enum class EType
        {
            Quit,
            KeyDown,
            KeyUp,
            MouseMove,
            MouseButtonDown,
            MouseButtonUp,
            None,
        };

        /**
         * @brief 이벤트 타입.
         */
        EType type = EType::None;

        /**
         * @brief 키 코드.
         */
        int keyCode = 0;

        /**
         * @brief 마우스 X좌표.
         */
        int x = 0;

        /**
         * @brief 마우스 Y좌표.
         */
        int y = 0;

        /**
         * @brief 발생했던 본래 이벤트.
         */
        void * native = nullptr;

    };

    /**
     * @brief Win32 플랫폼의 윈도우 이벤트를 추상화된 이벤트로 변환합니다.
     *
     * @param message_ Win32 메시지
     *
     * @return Message 변환된 메시지
     */
    PlatformWindowEvent __inline TranslateWin32Event(const MSG& message_);

    /**
     * @brief SDL3 이벤트를 추상화된 메시지로 변환합니다.
     *
     * @param event_ SDL3 이벤트
     *
     * @return Message 변환된 메시지
     */
    PlatformWindowEvent __inline TranslateSDL3Event(const SDL_Event& event_);

}

#endif // !GUARD_PLATFORMWINDOWEVENT_H

#include "../Runtime/Application/Platform/PlatformWindowEvent.inl"
