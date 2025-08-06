#ifndef RUNTIME_DISPLAYSERVERWINDOWS_H
#define RUNTIME_DISPLAYSERVERWINDOWS_H

#include "../Runtime/Common/Types.h"
#include "../Runtime/Display/IDisplayServer.h"
#include "../Runtime/Display/DisplayServerDescriptor.h"

namespace NomadEngine::Runtime
{
    class DisplayServer_Windows
        : public IDisplayServer
    {
    public:
        /**
         * @brief 생성자.
         */
        DisplayServer_Windows();

        /**
         * @brief 소멸자.
         */
        ~DisplayServer_Windows() override;

        /**
         * @brief 디스플레이 서버를 초기화합니다.
         *
         * @param descriptor_ 디스플레이 서버의 설정 기술.
         *
         * @return Bool 성공 여부.
         */
        Bool Initialize(const DisplayServerDescriptor& descriptor_) noexcept override;

        /**
         * @brief 디스플레이 서버를 종료합니다.
         *
         * @return Bool 성공 여부.
         */
        Bool Finalize() noexcept override;

        /**
         * @brief 창 핸들을 반환합니다.
         *
         * @return NativeWindow 창 핸들.
         */
        NODISCARD NativeWindow GetNativeWindow() const noexcept override;

    private:
        /**
         * @brief 윈도우 핸들.
         */
        HWND mWindowHandle;
    };
} // namespace NomadEngine::Runtime

#endif // RUNTIME_DISPLAYSERVERWINDOWS_H