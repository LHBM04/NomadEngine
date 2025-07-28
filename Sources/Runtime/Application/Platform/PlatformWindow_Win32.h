#ifndef GUARD_PLATFORMWINDOW_WIN32_H
#define GUARD_PLATFORMWINDOW_WIN32_H

#include <windows.h>

#include "../Runtime/Application/Platform/PlatformData.h"
#include "../Runtime/Application/Platform/PlatformWindowBase.h"

namespace NomadEngine::Runtime
{
    using Win32_Window = HWND;

    /**
     * @class PlatformWindow_Win32
     *
     * @brief Win32 플랫폼에서 실행되는 어플리케이션의 윈도우를 정의합니다.
     */
    class PlatformWindow_Win32
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
        PlatformWindow_Win32(
            std::wstring_view caption_,
            int width_,
            int height_);

        /**
         * @brief 소멸자.
         */
        virtual ~PlatformWindow_Win32() override = default;

        /**
         * @brief Win32 플랫폼 윈도우를 초기화합니다.
         *
         * @return bool 성공하면 true, 실패하면 false를 반환합니다.
         */
        virtual bool Initialize() override;

        /**
         * @brief Win32 플랫폼의 정보를 반환합니다.
         *
         * @return PlatformData Win32 플랫폼 데이터.
         */
        [[nodiscard]]
        virtual PlatformData GetPlatformData() const override;

        /**
         * @brief Win32 윈도우 핸들을 반환합니다.
         */
        [[nodiscard]]
        virtual WindowHandle GetWindowHandle() const override;

        /**
         * @brief Win32 메시지를 처리합니다.
         */
        virtual bool ProcessMessages() override;

    protected:
        /**
         * @brief Win32 네이티브 이벤트를 PlatformWindowEvent로 변환합니다.
         */
        virtual PlatformWindowEvent ConvertNativeEvent(void* nativeEvent) override;

    private:
        /**
         * @brief Win32 메시지를 PlatformWindowEvent로 변환합니다.
         */
        PlatformWindowEvent ConvertWin32Message(UINT uMsg, WPARAM wParam, LPARAM lParam);

        /**
         * @brief Win32 윈도우 프로시저
         */
        static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

        /**
         * @brief 인스턴스별 메시지 처리
         */
        LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

        /**
         * @brief Win32 윈도우 핸들.
         */
        Win32_Window mWindow;

    };
}

#endif // !GUARD_PLATFORMWINDOW_WIN32_H
