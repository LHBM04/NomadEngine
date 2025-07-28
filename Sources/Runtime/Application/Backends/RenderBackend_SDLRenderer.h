#ifndef GUARD_RENDERBACKEND_SDLRENDERER_H
#define GUARD_RENDERBACKEND_SDLRENDERER_H

#include <memory>
#include <iostream>

#include <SDL3/SDL_render.h>
#include <SDL3/SDL_gpu.h>

#include "../Backends/RenderBackendBase.h"

namespace NomadEngine::Runtime
{
    /**
     * @class RenderBackend_SDLRenderer
     *
     * @brief SDL3 렌더러 백엔드 클래스입니다.
     */
    class RenderBackend_SDLRenderer
        : public RenderBackendBase
    {
    public:
        /**
         * @brief 생성자.
         */
        RenderBackend_SDLRenderer();

        /**
         * @brief 소멸자.
         */
        virtual ~RenderBackend_SDLRenderer() override;

        /**
         * @brief SDL3 렌더러를 초기화합니다.
         *
         * @param platformData_ 플랫폼 데이터.
         *
         * @return bool 성공하면 true, 실패하면 false를 반환합니다.
         */
        virtual bool __fastcall Initialize(const PlatformData& platformData_) override;

        /**
         * @brief SDL 백엔드 내에서 렌더링을 시작합니다.
         */
        virtual void __fastcall BeginFrame() override;

        /**
         * @brief SDL 백엔드 내에서 렌더링을 종료합니다.
         */
        virtual void __fastcall EndFrame() override;

        /**
         * @brief SDL 백엔드 내 모든 리소스를 해제합니다.
         */
        virtual void __fastcall Release() override;

    private:
        /**
         * @brief SDL 렌더러.
         */
        std::shared_ptr<SDL_Renderer> mSDLRenderer;

    };

}

#endif // !GUARD_RENDERBACKEND_SDLRENDERER_H
