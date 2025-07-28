#ifndef GUARD_APPLICATION_H
#define GUARD_APPLICATION_H

#include <memory>

#include "../Application/Backends/RenderBackendBase.h"
#include "../Application/Platform/PlatformWindowBase.h"

namespace NomadEngine::Runtime
{
    using PlatformWindow = PlatformWindowBase;
    using RenderBackend = RenderBackendBase;

    class Application
    {
    public:
        /**
         * @brief 생성자.
         */
        Application();

        /**
         * @brief 소멸자.
         */
        virtual ~Application();

        /**
         * @brief 게임 애플리케이션을 초기화합니다.
         *
         * @return bool 성공하면 true, 실패하면 false를 반환합니다.
         */
        bool __stdcall Initialize();

        /**
         * @brief 게임 애플리케이션을 실행합니다.
         */
        void __stdcall Run();

        /**
         * @brief 게임 애플리케이션을 종료합니다.
         */
        void __stdcall Quit();

        /**
         * @brief 게임 애플리케이션을 종료하고 리소스를 해제합니다.
         */
        void __stdcall Release();

    private:
        /**
         * @brief 플랫폼.
         */
        std::unique_ptr<PlatformWindow> mPlatformWindow;

        /**
         * @brief 렌더링 백엔드.
         */
        std::unique_ptr<RenderBackend> mRenderBackend;

    };
}

#endif // !GUARD_APPLICATION_H
