#ifndef GUARD_RENDERINGSERVER_GDI_H
#define GUARD_RENDERINGSERVER_GDI_H

#include <windef.h>

#include "../Runtime/Application/Backends/IRenderingServer.h"

namespace NomadEngine::Runtime
{
    class RenderingServer_GDI
        : public IRenderingServer
    {
    public:
        /**
         * @brief 생성자.
         */
        RenderingServer_GDI();

        /**
         * @brief 소멸자.
         */
        virtual ~RenderingServer_GDI() override;

        /**
        * @brief 렌더링 백엔드를 초기화합니다.
        *
        * @return bool 성공하면 true, 실패하면 false를 반환합니다.
        */
        virtual bool Initialize() override;

        /**
         * @brief 프레임 시작.
         */
        virtual void BeginFrame() override;

        /**
         * @brief 프레임 렌더.
         */
        virtual void Present() override;

        /**
         * @brief 프레임 종료.
         */
        virtual void EndFrame() override;

        /**
         * @brief 렌더링 백엔드를 해제합니다.
         *
         * @return bool 성공하면 true, 실패하면 false를 반환합니다.
         */
        virtual bool Finalize() override;

    private:
        /**
         * @brief 디바이스 컨텍스트.
         */
        HDC mWindowDC = nullptr;

        /**
         * @brief 백 버퍼 비트맵.
         */
        HBITMAP mBackBufferBitmap = nullptr;

        /**
         * @brief 백 버퍼 디바이스 컨텍스트.
         */
        HDC mBackBufferDC = nullptr;

    };

}

#endif
