#include "PlatformWindow_Win32.h"
#include "PlatformWindowEvent.h"
#include <iostream>

namespace NomadEngine::Runtime
{
    PlatformWindow_Win32::PlatformWindow_Win32(
        std::wstring_view caption_,
        int width_,
        int height_)
        : PlatformWindowBase(caption_, width_, height_), mWindow(nullptr)
    {
    }

    // Win32 윈도우 프로시저
    LRESULT CALLBACK PlatformWindow_Win32::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        PlatformWindow_Win32* window = reinterpret_cast<PlatformWindow_Win32*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));

        if (window)
        {
            return window->HandleMessage(uMsg, wParam, lParam);
        }

        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    bool PlatformWindow_Win32::Initialize()
    {
        WNDCLASSEX classEx = {};
        classEx.cbSize = sizeof(WNDCLASSEX);
        classEx.style = CS_HREDRAW | CS_VREDRAW;
        classEx.lpfnWndProc = WindowProc;
        classEx.hInstance = GetModuleHandle(nullptr);
        classEx.hCursor = LoadCursor(nullptr, IDC_ARROW);
        classEx.lpszClassName = L"NomadEngineWindowClass";

        if (!RegisterClassEx(&classEx))
        {
            std::cerr << "Failed to register window class: " << GetLastError() << std::endl;
            return false;
        }

        mWindow = CreateWindowExW(
            0,
            classEx.lpszClassName,
            GetCaption().data(),
            WS_OVERLAPPEDWINDOW | WS_VISIBLE,
            CW_USEDEFAULT, CW_USEDEFAULT,
            GetWidth(), GetHeight(),
            nullptr, nullptr,
            classEx.hInstance,
            nullptr);

        if (!mWindow)
        {
            std::cerr << "Failed to create window: " << GetLastError() << std::endl;
            return false;
        }

        // 윈도우에 this 포인터 저장
        SetWindowLongPtr(mWindow, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));

        return true;
    }

    PlatformData PlatformWindow_Win32::GetPlatformData() const
    {
        PlatformData data;
        data.type = PlatformData::EType::Win32;
        data.window = mWindow;
        return data;
    }

    WindowHandle PlatformWindow_Win32::GetWindowHandle() const
    {
        return static_cast<WindowHandle>(mWindow);
    }

    bool PlatformWindow_Win32::ProcessMessages()
    {
        MSG msg = { };
        // 메시지 큐에서 메시지를 가져옵니다.
        while (PeekMessage(&msg, mWindow, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                // 종료 이벤트 생성하여 큐에 추가
                PlatformWindowEvent quitEvent;
                quitEvent.type = PlatformWindowEvent::EType::Quit;
                mWindowEventQueue.push(quitEvent);
                return false; // 종료 신호
            }

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        return true; // 계속 실행
    }

    LRESULT PlatformWindow_Win32::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        // Win32 메시지를 PlatformWindowEvent로 변환하여 큐에 추가
        PlatformWindowEvent event = ConvertWin32Message(uMsg, wParam, lParam);

        if (event.type != PlatformWindowEvent::EType::None)
        {
            mWindowEventQueue.push(event);
        }

        // 기본 메시지 처리
        switch (uMsg)
        {
            case WM_CLOSE:
                PostQuitMessage(0);
                return 0;

            case WM_SETFOCUS:
                mFocused = true;
                break;

            case WM_KILLFOCUS:
                mFocused = false;
                break;
        }

        return DefWindowProc(mWindow, uMsg, wParam, lParam);
    }

    PlatformWindowEvent PlatformWindow_Win32::ConvertNativeEvent(void* nativeEvent)
    {
        // Win32에서는 MSG 구조체를 받아서 처리
        MSG* msg = static_cast<MSG*>(nativeEvent);
        return ConvertWin32Message(msg->message, msg->wParam, msg->lParam);
    }

    PlatformWindowEvent PlatformWindow_Win32::ConvertWin32Message(UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        PlatformWindowEvent event;
        event.type = PlatformWindowEvent::EType::None;
        event.native = reinterpret_cast<void*>(static_cast<uintptr_t>(uMsg));

        switch (uMsg)
        {
            case WM_QUIT:
            case WM_CLOSE:
                event.type = PlatformWindowEvent::EType::Quit;
                break;

            case WM_KEYDOWN:
            case WM_SYSKEYDOWN:
                event.type = PlatformWindowEvent::EType::KeyDown;
                event.keyCode = static_cast<int>(wParam);
                break;

            case WM_KEYUP:
            case WM_SYSKEYUP:
                event.type = PlatformWindowEvent::EType::KeyUp;
                event.keyCode = static_cast<int>(wParam);
                break;

            case WM_MOUSEMOVE:
                event.type = PlatformWindowEvent::EType::MouseMove;
                event.x = LOWORD(lParam);
                event.y = HIWORD(lParam);
                break;

            case WM_LBUTTONDOWN:
            case WM_RBUTTONDOWN:
            case WM_MBUTTONDOWN:
                event.type = PlatformWindowEvent::EType::MouseButtonDown;
                event.keyCode = (uMsg == WM_LBUTTONDOWN) ? 0 : (uMsg == WM_RBUTTONDOWN) ? 1 : 2;
                event.x = LOWORD(lParam);
                event.y = HIWORD(lParam);
                break;

            case WM_LBUTTONUP:
            case WM_RBUTTONUP:
            case WM_MBUTTONUP:
                event.type = PlatformWindowEvent::EType::MouseButtonUp;
                event.keyCode = (uMsg == WM_LBUTTONUP) ? 0 : (uMsg == WM_RBUTTONUP) ? 1 : 2;
                event.x = LOWORD(lParam);
                event.y = HIWORD(lParam);
                break;
        }

        return event;
    }

}
