#ifndef GUARD_RENDERINGSERVER_SDLRENDERER_H
#define GUARD_RENDERINGSERVER_SDLRENDERER_H

#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>

#include "../Runtime/Application/Backends/IRenderingServer.h"

namespace NomadEngine::Runtime
{
    class RenderingServer_SDLRenderer
        : public IRenderingServer
    {
    public:
        /**
         * @brief 생성자.
         */
        RenderingServer_SDLRenderer();

        /**
         * @brief 소멸자.
         */
        virtual ~RenderingServer_SDLRenderer() override;

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
         * @brief SDL 렌더러.
         */
        SDL_Renderer* mRenderer;

        /**
         * @brief GL 컨텍스트.
         */
        SDL_GLContext mGLContext;

    };

}

#endif
