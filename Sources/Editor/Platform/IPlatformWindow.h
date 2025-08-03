#ifndef GUARD_IPLATFORMWINDOW_H
#define GUARD_IPLATFORMWINDOW_H

#include <cstdint>
#include <string>

namespace NomadEngine::Editor
{
    struct WindowDescriptor
    {
        std::string title = "NomadEngine Editor";
        uint32_t width = 1280;
        uint32_t height = 720;
        bool resizable = true;
        bool maximized = false;
        bool fullscreen = false;
    };

    /**
     * @brief 플랫폼별 메인 윈도우 인터페이스
     */
    class IPlatformWindow
    {
    public:
        virtual ~IPlatformWindow() = default;

        /**
         * @brief 윈도우를 초기화합니다.
         * @param descriptor 윈도우 설정
         * @return 성공 시 true
         */
        virtual bool Initialize(const WindowDescriptor& descriptor) = 0;

        /**
         * @brief 윈도우를 해제합니다.
         */
        virtual void Finalize() = 0;

        /**
         * @brief 윈도우 이벤트를 처리합니다.
         * @return 윈도우가 닫혀야 하면 false
         */
        virtual bool ProcessEvents() = 0;

        /**
         * @brief 윈도우 렌더링을 시작합니다.
         */
        virtual void BeginFrame() = 0;

        /**
         * @brief 윈도우 렌더링을 종료합니다.
         */
        virtual void EndFrame() = 0;

        /**
         * @brief 네이티브 윈도우 핸들을 반환합니다.
         */
        virtual void* GetNativeHandle() const = 0;

        /**
         * @brief 윈도우 크기를 반환합니다.
         */
        virtual void GetSize(uint32_t& width, uint32_t& height) const = 0;

        /**
         * @brief 윈도우가 최소화되어 있는지 확인합니다.
         */
        virtual bool IsMinimized() const = 0;
    };
}

#endif
