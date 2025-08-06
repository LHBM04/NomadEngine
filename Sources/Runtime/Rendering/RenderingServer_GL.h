#ifndef GUARD_RENDERINGSERVER_GL_H
#define GUARD_RENDERINGSERVER_GL_H

#include "../Common/Defines.h"
#include "../Common/Types.h"

#include "../Rendering/IRenderingServer.h"
#include "../Rendering/RenderingServerDescriptor.h"

namespace NomadEngine::Runtime
{
    /**
     * @class RenderingServer_GL
     *
     * @brief OpenGL 렌더링 서버를 구현합니다.
     */
    class RenderingServer_GL
        : public IRenderingServer
    {
    public:
        /**
         * @brief 생성자.
         */
        RenderingServer_GL();

        /**
         * @brief 소멸자.
         */
        virtual ~RenderingServer_GL() override;

        /**
         * @brief OpenGL 렌더링 서버를 초기화합니다.
         * 
         * @param descriptor_ 렌더링 시스템의 설정 기술.
         *
         * @return bool 성공하면 true, 실패하면 false를 반환합니다.
         */
        virtual bool Initialize(const RenderingServerDescriptor& descriptor_) override;

         /**
         * @brief 렌더링이 시작되기 전 호출됩니다.
         */
        virtual void PreRender() override;

        /**
         * @brief 렌더링이 종료되기 전 호출됩니다.
         */
        virtual void PostRender() override;

        /**
         * @brief OpenGL 렌더링 서버를 종료합니다.
         */
        virtual bool Finalize() override;
    };
}

#endif // !GUARD_RENDERINGSERVER_GL_H
