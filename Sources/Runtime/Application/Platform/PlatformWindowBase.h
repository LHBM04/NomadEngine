#ifndef GUARD_PLATFORMWINDOWBASE_H
#define GUARD_PLATFORMWINDOWBASE_H

#include <string>
#include <string_view>
#include <queue>

#include "../Runtime/Application/Platform/MessageDispatcher.h"
#include "../Runtime/Application/Platform/PlatformData.h"

namespace NomadEngine::Runtime
{
    /**
     * @typedef void*
     *
     * @brief 플랫폼 데이터를 정의합니다.
     */
    using WindowHandle = void*;

    /**
     * @class PlatformWindowBase
     *
     * @brief 각종 플랫폼 위에서 실행되는 어플리케이션의 윈도우의 기본 동작을 정의합니다.
     */
    class PlatformWindowBase
    {
    public:
        /**
         * @brief 생성자.
         *
         * @param caption_ 윈도우 캡션.
         * @param width 너비.
         * @param height 높이.
         */
        PlatformWindowBase(
            std::wstring_view caption_,
            int width,
            int height);

        /**
         * @brief 소멸자.
         */
        virtual ~PlatformWindowBase();

        /**
         * @brief 플랫폼 윈도우를 초기화합니다.
         *
         * @return bool 성공하면 true, 실패하면 false를 반환합니다.
         */
        virtual bool Initialize() = 0;

        /**
         * @brief 윈도우 캡션을 반환합니다.
         *
         * @return std::wstring 윈도우 캡션.
         */
        [[nodiscard]]
        std::wstring_view __inline GetCaption() const
        {
            return mCaption;
        }

        /**
         * @brief 윈도우 캡션을 설정합니다.
         *
         * @param caption_ 윈도우 캡션.
         */
        void __inline SetCaption(std::wstring_view caption_)
        {
            mCaption = caption_;
        }

        [[nodiscard]]
        int __inline GetWidth() const
        {
            return mWidth;
        }

        void __inline SetWidth(int width_)
        {
            mWidth = width_;
        }

        [[nodiscard]]
        int __inline GetHeight() const
        {
            return mHeight;
        }

        void __inline SetHeight(int height_)
        {
            mHeight = height_;
        }

        /**
         * @brief 플랫폼 데이터를 반환합니다.
         *
         * @return PlatformData 플랫폼 데이터.
         */
        [[nodiscard]]
        virtual PlatformData GetPlatformData() const = 0;

        /**
         * @brief 윈도우 핸들을 반환합니다.
         *
         * @return WindowHandle 윈도우 핸들.
         */
        [[nodiscard]]
        virtual WindowHandle GetWindowHandle() const = 0;

        /**
         * @brief 플랫폼 윈도우 이벤트를 Poll할 때까지 대기합니다.
         *
         * @param message_ Poll한 메시지를 담을 변수.
         *
         * @return bool 메시지가 성공적으로 가져와졌다면 true, 아니면 false를 반환합니다.
         */
        bool WaitPlatformWindowEvent(PlatformWindowEvent& message_);

        /**
         * @brief 플랫폼 윈도우 이벤트를 Peek해옵니다.
         *
         * @param message_ Peek한 메시지를 담을 변수.
         *
         * @return bool 메시지가 성공적으로 Peek되었다면 true, 아니면 false를 반환합니다.
         */
        bool PollPlatformWindowEvent(PlatformWindowEvent& message_);

        /**
         * @brief 플랫폼 윈도우 이벤트를 윈도우 플랫폼에 맞게 변환합니다.
         *
         * @param message_ 변환할 플랫폼 윈도우 이벤트.
         */
        void TranslatePlatformWindowEvent(const PlatformWindowEvent& message_);

        /**
         * @brief 랫폼 윈도우 이벤트를 디스패치합니다.
         *
         * @param message_ 디스패치할 플랫폼 윈도우 이벤트.
         */
        void DispatchPlatformWindowEvent(const PlatformWindowEvent& message_);

        /**
         * @brief 플랫폼별 메시지를 처리합니다.
         *
         * @return bool 계속 실행하려면 true, 종료하려면 false를 반환합니다.
         */
        virtual bool ProcessMessages() = 0;

    protected:
        /**
         * @brief 네이티브 이벤트를 PlatformWindowEvent로 변환합니다.
         * 각 플랫폼에서 구현해야 합니다.
         */
        virtual PlatformWindowEvent ConvertNativeEvent(void* nativeEvent) = 0;

    private:
        /**
         * @brief 윈도우 캡션.
         */
        std::wstring mCaption;

        /**
         * @brief 윈도우 너비.
         */
        int mWidth;

        /**
         * @brief 윈도우 높이.
         */
        int mHeight;

        /**
         * @brief 윈도우 포커스 여부.
         */
        bool mFocused;

    };

}

#endif // !GUARD_PLATFORMWINDOWBASE_H
