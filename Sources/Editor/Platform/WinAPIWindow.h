#ifndef GUARD_WINAPIWINDOW_H
#define GUARD_WINAPIWINDOW_H

#pragma once

#include "../../Runtime/Common/Defines.h"

#ifdef NOMAD_PLATFORM_WINDOWS

#include "IPlatformWindow.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

namespace NomadEngine::Editor
{
    /**
     * @brief Windows WinAPI 기반 메인 윈도우
     */
    class WinAPIWindow : public IPlatformWindow
    {
    public:
        WinAPIWindow();
        virtual ~WinAPIWindow();

        bool Initialize(const WindowDescriptor& descriptor) override;
        void Finalize() override;
        bool ProcessEvents() override;
        void BeginFrame() override;
        void EndFrame() override;
        void* GetNativeHandle() const override;
        void GetSize(uint32_t& width, uint32_t& height) const override;
        bool IsMinimized() const override;

    private:
        static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
        
        HWND mHwnd;
        HDC mHdc;
        HINSTANCE mHinstance;
        std::string mClassName;
        uint32_t mWidth;
        uint32_t mHeight;
        bool mIsMinimized;
        bool mShouldClose;
    };
}

#endif // NOMAD_PLATFORM_WINDOWS

#endif
