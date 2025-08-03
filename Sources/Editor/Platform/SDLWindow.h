#ifndef GUARD_SDLWINDOW_H
#define GUARD_SDLWINDOW_H

#include "../../Runtime/Common/Defines.h"

// 임시로 모든 플랫폼에서 SDL 사용 가능하도록 조건 제거
// #ifdef NOMAD_PLATFORM_LINUX

#include "../Platform/IPlatformWindow.h"
#include <SDL3/SDL.h>

namespace NomadEngine::Editor
{
    /**
     * @brief SDL3 기반 메인 윈도우 (Linux)
     */
    class SDLWindow : public IPlatformWindow
    {
    public:
        SDLWindow();
        virtual ~SDLWindow();

        bool Initialize(const WindowDescriptor& descriptor) override;
        void Finalize() override;
        bool ProcessEvents() override;
        void BeginFrame() override;
        void EndFrame() override;
        void* GetNativeHandle() const override;
        void GetSize(uint32_t& width, uint32_t& height) const override;
        bool IsMinimized() const override;

    private:
        SDL_Window* mWindow;
        uint32_t mWidth;
        uint32_t mHeight;
        bool mIsMinimized;
        bool mShouldClose;
    };
}

// #endif // NOMAD_PLATFORM_LINUX (임시 제거)

#endif
