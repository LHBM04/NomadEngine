#ifndef GUARD_PLATFORMWINDOW_SDL3_H
#define GUARD_PLATFORMWINDOW_SDL3_H

#include <SDL3/SDL_video.h>

#include "../Runtime/Application/Platform/PlatformWindowBase.h"
#include "../Runtime/Application/Platform/PlatformData.h"

namespace NomadEngine::Runtime
{
    /**
     * @class PlatformWindow_SDL
     *
     * @brief SDL3 플랫폼에서 실행되는 어플리케이션의 윈도우를 정의합니다.
     */
    class PlatformWindow_SDL
        : public PlatformWindowBase
    {
    public:
        /**
         * @brief 생성자.
         *
         * @param caption_ 윈도우 캡션.
         * @param width_ 윈도우 너비.
         * @param height_ 윈도우 높이.
         */
        PlatformWindow_SDL(
            std::wstring_view caption_,
            int width,
            int height);

        /**
         * @brief 소멸자.
         */
        virtual ~PlatformWindow_SDL() override;

        /**
         * @brief SDL3 플랫폼의 윈도우를 초기화합니다.
         */
        virtual bool __stdcall Initialize() override;

        /**
         * @brief SDL3 플랫폼의 정보를 반환합니다.
         *
         * @return PlatformData SDL3 플랫폼 데이터.
         */
        [[nodiscard]]
        virtual PlatformData GetPlatformData() const override;

        /**
         * @brief SDL3 윈도우 핸들을 반환합니다.
         */
        [[nodiscard]]
        virtual WindowHandle GetWindowHandle() const override;

    private:
        /**
         * @brief SDL3 이벤트를 추상화된 메시지로 변환합니다.
         *
         * @param event SDL3 이벤트
         * @return Message 변환된 메시지
         */
        Message ConvertMessage(const SDL_Event& event);

        /**
         * @brief SDL 윈도우 핸들.
         */
        SDL_Window* mWindow;

    };
}

#endif // !GUARD_PLATFORMWINDOW_SDL3_H
