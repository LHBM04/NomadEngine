#include "WinAPIWindow.h"

#ifdef NOMAD_PLATFORM_WINDOWS

#include <iostream>

namespace NomadEngine::Editor
{
    WinAPIWindow::WinAPIWindow()
        : mHwnd(nullptr)
        , mHdc(nullptr)
        , mHinstance(GetModuleHandle(nullptr))
        , mClassName("NomadEngineEditor")
        , mWidth(1280)
        , mHeight(720)
        , mIsMinimized(false)
        , mShouldClose(false)
    {
    }

    WinAPIWindow::~WinAPIWindow()
    {
        Finalize();
    }

    bool WinAPIWindow::Initialize(const WindowDescriptor& descriptor)
    {
        mWidth = descriptor.width;
        mHeight = descriptor.height;

        // 윈도우 클래스 등록
        WNDCLASSEX wc = {};
        wc.cbSize = sizeof(WNDCLASSEX);
        wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
        wc.lpfnWndProc = WindowProc;
        wc.hInstance = mHinstance;
        wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
        wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
        wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
        wc.lpszClassName = mClassName.c_str();
        wc.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);

        if (!RegisterClassEx(&wc))
        {
            std::cerr << "Failed to register window class" << std::endl;
            return false;
        }

        // 윈도우 스타일 설정
        DWORD dwStyle = WS_OVERLAPPEDWINDOW;
        if (!descriptor.resizable)
        {
            dwStyle &= ~(WS_THICKFRAME | WS_MAXIMIZEBOX);
        }

        // 클라이언트 영역 크기 계산
        RECT rect = {0, 0, static_cast<LONG>(mWidth), static_cast<LONG>(mHeight)};
        AdjustWindowRect(&rect, dwStyle, FALSE);

        int windowWidth = rect.right - rect.left;
        int windowHeight = rect.bottom - rect.top;

        // 화면 중앙에 위치
        int screenWidth = GetSystemMetrics(SM_CXSCREEN);
        int screenHeight = GetSystemMetrics(SM_CYSCREEN);
        int x = (screenWidth - windowWidth) / 2;
        int y = (screenHeight - windowHeight) / 2;

        // 윈도우 생성
        mHwnd = CreateWindowEx(
            0,
            mClassName.c_str(),
            descriptor.title.c_str(),
            dwStyle,
            x, y,
            windowWidth, windowHeight,
            nullptr,
            nullptr,
            mHinstance,
            this
        );

        if (!mHwnd)
        {
            std::cerr << "Failed to create window" << std::endl;
            return false;
        }

        // 윈도우 표시
        int nCmdShow = descriptor.maximized ? SW_MAXIMIZE : SW_SHOW;
        ShowWindow(mHwnd, nCmdShow);
        UpdateWindow(mHwnd);

        // 디바이스 컨텍스트 가져오기
        mHdc = GetDC(mHwnd);
        if (!mHdc)
        {
            std::cerr << "Failed to get device context" << std::endl;
            return false;
        }

        std::cout << "WinAPI window initialized successfully" << std::endl;
        return true;
    }

    void WinAPIWindow::Finalize()
    {
        if (mHdc && mHwnd)
        {
            ReleaseDC(mHwnd, mHdc);
            mHdc = nullptr;
        }

        if (mHwnd)
        {
            DestroyWindow(mHwnd);
            mHwnd = nullptr;
        }

        if (mHinstance)
        {
            UnregisterClass(mClassName.c_str(), mHinstance);
        }
    }

    bool WinAPIWindow::ProcessEvents()
    {
        MSG msg;
        while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                mShouldClose = true;
                return false;
            }

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        return !mShouldClose;
    }

    void WinAPIWindow::BeginFrame()
    {
        // WinAPI 전용 프레임 시작 처리
    }

    void WinAPIWindow::EndFrame()
    {
        // WinAPI 전용 프레임 종료 처리
        // OpenGL의 경우 SwapBuffers가 여기서 호출됨
    }

    void* WinAPIWindow::GetNativeHandle() const
    {
        return static_cast<void*>(mHwnd);
    }

    void WinAPIWindow::GetSize(uint32_t& width, uint32_t& height) const
    {
        width = mWidth;
        height = mHeight;
    }

    bool WinAPIWindow::IsMinimized() const
    {
        return mIsMinimized;
    }

    LRESULT CALLBACK WinAPIWindow::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        WinAPIWindow* window = nullptr;

        if (uMsg == WM_NCCREATE)
        {
            CREATESTRUCT* pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
            window = reinterpret_cast<WinAPIWindow*>(pCreate->lpCreateParams);
            SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(window));
        }
        else
        {
            window = reinterpret_cast<WinAPIWindow*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
        }

        if (window)
        {
            switch (uMsg)
            {
            case WM_CLOSE:
                window->mShouldClose = true;
                return 0;

            case WM_SIZE:
                {
                    window->mWidth = LOWORD(lParam);
                    window->mHeight = HIWORD(lParam);
                    window->mIsMinimized = (wParam == SIZE_MINIMIZED);
                }
                break;

            case WM_DESTROY:
                PostQuitMessage(0);
                return 0;
            }
        }

        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}

#endif // NOMAD_PLATFORM_WINDOWS
