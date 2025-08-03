#ifndef GUARD_IRENDERSYSTEM_H
#define GUARD_IRENDERSYSTEM_H

#include "../Rendering/RenderingServerDescriptor.h"

namespace NomadEngine::Runtime
{
    class IRenderingServer
    {
    public:
        /**
         * @brief 소멸자.
         */
        virtual ~IRenderingServer() = default;

        /**
         * @brief 렌더링 시스템을 초기화합니다.
         *
         * @param descriptor_ 렌더링 시스템의 설정 기술.
         *
         * @return bool 성공 여부.
         */
        virtual bool Initialize(const RenderingServerDescriptor& descriptor_) = 0;

        /**
         * @brief 렌더링이 시작되기 전 호출됩니다.
         */
        virtual void PreRender() = 0;

        /**
         * @brief 렌더링이 종료되기 전 호출됩니다.
         */
        virtual void PostRender() = 0;

        /**
         * @brief 렌더링 시스템을 종료합니다.
         *
         * @return bool 성공 여부.
         */
        virtual bool Finalize() = 0;
    };
}

#endif
