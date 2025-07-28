#ifndef NOMAD_RENDERERCONTEXTBASE_H
#define NOMAD_RENDERERCONTEXTBASE_H

#include "Application/Platform/PlatformData.h"

namespace NomadEngine::Runtime
{
    /**
     * @class RenderBackendBase
     *
     * @brief 렌더링 백엔드의 기본 클래스를 정의합니다.
     */
    class RenderBackendBase
    {
    public:
        /**
         * @brief 생성자.
         */
        virtual ~RenderBackendBase() = default;

        /**
         * @brief 해당 백엔드를 초기화합니다.
         *
         * @param platformData_ 플랫폼 데이터.
         *
         * @return bool 성공하면 true, 실패하면 false를 반환합니다.
         */
        virtual bool __fastcall Initialize(const PlatformData& platformData_) = 0;

        /**
         * @brief 해당 백엔드의 프레임을 시작합니다.
         */
        virtual void __fastcall BeginFrame() = 0;

        /**
         * @brief 해당 백엔드의 프레임을 종료합니다.
         */
        virtual void __fastcall EndFrame() = 0;

        /**
         * @brief 해당 백엔드의 모든 리소스를 해제합니다.
         */
        virtual void __fastcall Release() = 0;

    };
}

#endif // !NOMAD_RENDERERCONTEXTBASE_H
