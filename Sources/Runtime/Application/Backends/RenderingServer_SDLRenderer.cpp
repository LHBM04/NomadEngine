#include "../Runtime/Application/Backends/RenderingServer_SDLRenderer.h"

namespace NomadEngine::Runtime
{
    RenderingServer_SDLRenderer::RenderingServer_SDLRenderer()
        : mRenderer(nullptr)
    {
    }

    RenderingServer_SDLRenderer::~RenderingServer_SDLRenderer()
    {
        RenderingServer_SDLRenderer::Finalize();
    }

    bool RenderingServer_SDLRenderer::Initialize()
    {
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
        SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
        SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

        mRenderer = SDL_CreateRenderer(nullptr, nullptr);
        if (!mRenderer)
        {
            return false;
        }

        mGLContext = SDL_GL_CreateContext(nullptr);

        return true;
    }

    void RenderingServer_SDLRenderer::BeginFrame()
    {
        // 프레임 시작 로직을 여기에 추가합니다.
    }

    void RenderingServer_SDLRenderer::EndFrame()
    {
        // 프레임 종료 로직을 여기에 추가합니다.
    }

    bool RenderingServer_SDLRenderer::Finalize()
    {
        if (mRenderer)
        {
            SDL_DestroyRenderer(mRenderer);
            mRenderer = nullptr;
        }

        return true;
    }

}