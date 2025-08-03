#include "DisplayServer_Windows.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <string>
#include <sstream>

namespace NomadEngine::Runtime
{
    DisplayServer_Windows::DisplayServer_Windows()
        : mWindow(nullptr)
        , m_hinstance(nullptr)
    {
        // Create a unique window class name for each instance.
        static int windowCount = 0;
        std::ostringstream oss;
        oss << "NomadEngineWindowClass" << ++windowCount;
        m_windowClassName = new char[oss.str().size() + 1];
        strcpy_s(const_cast<char*>(m_windowClassName), oss.str().size() + 1, oss.str().c_str());
    }

    DisplayServer_Windows::~DisplayServer_Windows()
    {
        delete[] m_windowClassName;
        Finalize();
    }

    bool DisplayServer_Windows::Initialize(const DisplayServerDescriptor& descriptor_)
    {
        m_hinstance = GetModuleHandle(nullptr);

        WNDCLASSEX wc = {};
        wc.cbSize = sizeof(WNDCLASSEX);
        wc.style = CS_HREDRAW | CS_VREDRAW;
        wc.lpfnWndProc = WindowProc;
        wc.cbClsExtra = NULL;
        wc.cbWndExtra = NULL;
        wc.hInstance = reinterpret_cast<HINSTANCE>(m_hinstance);
        wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
        wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
        wc.lpszClassName = m_windowClassName.c_str();
        wc.lpszMenuName = nullptr;
        RegisterClassEx(&wc);

        mWindow = CreateWindowEx(
            0,
            m_windowClassName.c_str(),
            descriptor_.title,
            WS_OVERLAPPEDWINDOW,
            descriptor_.x,
            descriptor_.y,
            descriptor_.width,
            descriptor_.height,
            nullptr,
            nullptr,
            reinterpret_cast<HINSTANCE>(m_hinstance),
            nullptr
        );

        ShowWindow(mWindow, SW_SHOWDEFAULT);
        UpdateWindow(mWindow);

        return true;
    }

    bool DisplayServer_Windows::Finalize()
    {
        if (mWindow)
        {
            DestroyWindow(reinterpret_cast<HWND>(mWindow));
            mWindow = nullptr;
        }

        if (m_hinstance)
        {
            UnregisterClass(m_windowClassName, reinterpret_cast<HINSTANCE>(m_hinstance));
            m_hinstance = nullptr;
        }

        return true;
    }

    HWND__* DisplayServer_Windows::GetWindowHandle() const
    {
        return mWindow;
    }

    long long __stdcall DisplayServer_Windows::WindowProc(HWND__* hwnd, unsigned int msg, unsigned long long wParam, long long lParam)
    {
        switch (msg)
        {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        }

        return DefWindowProc(reinterpret_cast<HWND>(hwnd), msg, wParam, lParam);
    }
}
