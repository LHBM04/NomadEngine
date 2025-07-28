#include "RenderBackend_SDLRenderer.h"

#include <iostream>
#include "SDL3/SDL_video.h"

#ifdef _WIN32
#include <windows.h>
#endif

namespace NomadEngine::Runtime
{
    RenderBackend_SDLRenderer::RenderBackend_SDLRenderer()
        : mSDLRenderer(nullptr)
    {
    }

    RenderBackend_SDLRenderer::~RenderBackend_SDLRenderer()
    {
        if (mSDLRenderer)
        {
            SDL_DestroyRenderer(mSDLRenderer.get());
        }
    }

    bool RenderBackend_SDLRenderer::Initialize(const PlatformData& platformData_)
    {
        // SDL3 렌더러는 SDL3 윈도우에서만 지원
        if (platformData_.type != PlatformData::EType::SDL)
        {
            std::cerr << "SDL3 renderer only supports SDL3 platform. Current platform: "
                      << static_cast<int>(platformData_.type) << std::endl;
            std::cerr << "For Win32 platform, please use OpenGL backend instead." << std::endl;
            return false;
        }

        SDL_Window* window = static_cast<SDL_Window*>(platformData_.window);
        if (!window)
        {
            std::cerr << "Invalid SDL window pointer." << std::endl;
            return false;
        }

        // SDL3 렌더러 생성
        mSDLRenderer.reset(SDL_CreateRenderer(window, nullptr));
        if (!mSDLRenderer)
        {
            std::cerr << "Failed to create SDL renderer: " << SDL_GetError() << std::endl;
            return false;
        }

        // 렌더러 추가 설정
        // VSync 활성화
        if (SDL_SetRenderVSync(mSDLRenderer.get(), 1) < 0)
        {
            std::cerr << "Warning: Failed to enable VSync: " << SDL_GetError() << std::endl;
        }

        // 렌더 스케일 품질 설정 (선형 필터링)
        if (SDL_SetRenderScale(mSDLRenderer.get(), 1.0f, 1.0f) < 0)
        {
            std::cerr << "Warning: Failed to set render scale: " << SDL_GetError() << std::endl;
        }

        // 블렌드 모드 설정 (알파 블렌딩)
        if (SDL_SetRenderDrawBlendMode(mSDLRenderer.get(), SDL_BLENDMODE_BLEND) < 0)
        {
            std::cerr << "Warning: Failed to set blend mode: " << SDL_GetError() << std::endl;
        }

        // 기본 렌더 색상 설정 (검은색)
        if (SDL_SetRenderDrawColor(mSDLRenderer.get(), 0, 0, 0, 255) < 0)
        {
            std::cerr << "Warning: Failed to set render draw color: " << SDL_GetError() << std::endl;
        }

        // 렌더러 정보 출력
        SDL_RendererInfo info;
        if (SDL_GetRendererInfo(mSDLRenderer.get(), &info) == 0)
        {
            std::cout << "SDL3 Renderer initialized successfully:" << std::endl;
            std::cout << "  Name: " << info.name << std::endl;
            std::cout << "  Flags: " << info.flags << std::endl;
            std::cout << "  Max Texture Width: " << info.max_texture_width << std::endl;
            std::cout << "  Max Texture Height: " << info.max_texture_height << std::endl;
            std::cout << "  Platform: " << (platformData_.type == PlatformData::EType::SDL ? "SDL3" : "Win32") << std::endl;
        }

        return true;
    }

    void RenderBackend_SDLRenderer::BeginFrame()
    {
        if (!mSDLRenderer)
        {
            std::cerr << "SDL renderer is not initialized." << std::endl;
            return;
        }

        // 프레임 시작 시 렌더러를 초기화합니다.
        SDL_SetRenderDrawColor(mSDLRenderer.get(), 0, 0, 0, 255);
        SDL_RenderClear(mSDLRenderer.get());
    }

    void RenderBackend_SDLRenderer::EndFrame()
    {
        if (!mSDLRenderer)
        {
            std::cerr << "SDL renderer is not initialized." << std::endl;
            return;
        }

        // 백버퍼의 내용을 화면에 표시합니다.
        SDL_RenderPresent(mSDLRenderer.get());
    }

} // namespace NomadEngine::Runtime
