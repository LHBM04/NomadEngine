#include "RenderBackend_GL.h"

#include <iostream>
#include <GL/glew.h>

#ifdef _WIN32
#include <windows.h>
#include <GL/wglew.h>
#endif

#ifdef SDL_VERSION
#include <SDL3/SDL.h>
#endif

namespace NomadEngine::Runtime
{
    RenderBackend_GL::RenderBackend_GL()
#ifdef _WIN32
        : mHDC(nullptr), mHGLRC(nullptr)
#endif
    {
    }

    RenderBackend_GL::~RenderBackend_GL()
    {
        Release();
    }

    bool RenderBackend_GL::Initialize(const PlatformData& platformData_)
    {
        // 플랫폼별 OpenGL 컨텍스트 설정
        if (!mSetupOpenGLContext(platformData_))
        {
            std::cerr << "Failed to setup OpenGL context for platform" << std::endl;
            return false;
        }

        // GLEW 초기화
        GLenum glewResult = glewInit();
        if (glewResult != GLEW_OK)
        {
            std::cerr << "Failed to initialize GLEW: " << glewGetErrorString(glewResult) << std::endl;
            return false;
        }

        // OpenGL 버전 확인
        const GLubyte* version = glGetString(GL_VERSION);
        const GLubyte* vendor = glGetString(GL_VENDOR);
        const GLubyte* renderer = glGetString(GL_RENDERER);

        if (!version || !vendor || !renderer)
        {
            std::cerr << "Failed to get OpenGL information" << std::endl;
            return false;
        }

        std::cout << "OpenGL initialized successfully:" << std::endl;
        std::cout << "  Version: " << version << std::endl;
        std::cout << "  Vendor: " << vendor << std::endl;
        std::cout << "  Renderer: " << renderer << std::endl;

        // OpenGL 기본 설정
        // 깊이 테스트 활성화
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        // 알파 블렌딩 활성화
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // 백페이스 컬링 활성화
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        glFrontFace(GL_CCW);

        // 뷰포트 설정 (기본값)
        GLint viewport[4];
        glGetIntegerv(GL_VIEWPORT, viewport);
        glViewport(0, 0, viewport[2], viewport[3]);

        // 기본 클리어 색상 설정 (어두운 회색)
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

        // OpenGL 오류 확인
        GLenum error = glGetError();
        if (error != GL_NO_ERROR)
        {
            std::cerr << "OpenGL initialization error: " << error << std::endl;
            return false;
        }

        return true;
    }

    bool RenderBackend_GL::mSetupOpenGLContext(const PlatformData& platformData_)
    {
        switch (platformData_.type)
        {
            case PlatformData::EType::Win32:
                return mSetupWin32OpenGL(platformData_);

            case PlatformData::EType::SDL:
                return mSetupSDL3OpenGL(platformData_);

            case PlatformData::EType::GLFW:
                // GLFW는 자체적으로 OpenGL 컨텍스트를 관리하므로 별도 설정 불필요
                std::cout << "GLFW OpenGL context detected" << std::endl;
                return true;

            default:
                std::cerr << "Unsupported platform type for OpenGL backend" << std::endl;
                return false;
        }
    }

#ifdef _WIN32
    bool RenderBackend_GL::mSetupWin32OpenGL(const PlatformData& platformData_)
    {
        HWND hwnd = static_cast<HWND>(platformData_.window);
        if (!hwnd)
        {
            std::cerr << "Invalid Win32 window handle" << std::endl;
            return false;
        }

        mHDC = GetDC(hwnd);
        if (!mHDC)
        {
            std::cerr << "Failed to get device context" << std::endl;
            return false;
        }

        // 픽셀 포맷 설정
        PIXELFORMATDESCRIPTOR pfd = {};
        pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
        pfd.nVersion = 1;
        pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
        pfd.iPixelType = PFD_TYPE_RGBA;
        pfd.cColorBits = 32;
        pfd.cDepthBits = 24;
        pfd.cStencilBits = 8;
        pfd.iLayerType = PFD_MAIN_PLANE;

        int pixelFormat = ChoosePixelFormat(mHDC, &pfd);
        if (!pixelFormat)
        {
            std::cerr << "Failed to choose pixel format" << std::endl;
            return false;
        }

        if (!SetPixelFormat(mHDC, pixelFormat, &pfd))
        {
            std::cerr << "Failed to set pixel format" << std::endl;
            return false;
        }

        // OpenGL 렌더링 컨텍스트 생성
        mHGLRC = wglCreateContext(mHDC);
        if (!mHGLRC)
        {
            std::cerr << "Failed to create OpenGL context" << std::endl;
            return false;
        }

        // 컨텍스트를 현재 스레드에 바인드
        if (!wglMakeCurrent(mHDC, mHGLRC))
        {
            std::cerr << "Failed to make OpenGL context current" << std::endl;
            return false;
        }

        std::cout << "Win32 OpenGL context created successfully" << std::endl;
        return true;
    }
#endif

    bool RenderBackend_GL::mSetupSDL3OpenGL(const PlatformData& platformData_)
    {
#ifdef SDL_VERSION
        SDL_Window* window = static_cast<SDL_Window*>(platformData_.window);
        if (!window)
        {
            std::cerr << "Invalid SDL3 window pointer" << std::endl;
            return false;
        }

        // SDL3에서는 윈도우 생성 시 이미 OpenGL 컨텍스트가 설정되어 있어야 함
        // 여기서는 컨텍스트가 올바르게 설정되어 있는지만 확인
        SDL_GLContext context = SDL_GL_GetCurrentContext();
        if (!context)
        {
            std::cerr << "No current OpenGL context in SDL3" << std::endl;
            return false;
        }

        // VSync 설정
        if (SDL_GL_SetSwapInterval(1) < 0)
        {
            std::cerr << "Warning: Unable to set VSync: " << SDL_GetError() << std::endl;
        }

        std::cout << "SDL3 OpenGL context validated successfully" << std::endl;
        return true;
#else
        std::cerr << "SDL3 support not compiled in" << std::endl;
        return false;
#endif
    }

    void RenderBackend_GL::BeginFrame()
    {
        // 프레임버퍼 클리어
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        // OpenGL 오류 확인
        GLenum error = glGetError();
        if (error != GL_NO_ERROR)
        {
            std::cerr << "OpenGL error in BeginFrame: " << error << std::endl;
        }
    }

    void RenderBackend_GL::EndFrame()
    {
        // OpenGL 명령들이 모두 처리되도록 강제 실행
        glFlush();

        // 플랫폼별 버퍼 스왑
        mSwapBuffers();

        // OpenGL 오류 확인
        GLenum error = glGetError();
        if (error != GL_NO_ERROR)
        {
            std::cerr << "OpenGL error in EndFrame: " << error << std::endl;
        }
    }

    void RenderBackend_GL::mSwapBuffers()
    {
        // 플랫폼별 버퍼 스왑 처리는 플랫폼 윈도우에서 처리하도록 함
        // 이 함수는 필요시 플랫폼별 스왑 로직을 위한 확장 포인트
    }

    void RenderBackend_GL::Release()
    {
#ifdef _WIN32
        // Win32 OpenGL 컨텍스트 해제
        if (mHGLRC)
        {
            wglMakeCurrent(nullptr, nullptr);
            wglDeleteContext(mHGLRC);
            mHGLRC = nullptr;
        }

        if (mHDC)
        {
            // HDC는 윈도우가 소유하므로 ReleaseDC 호출하지 않음
            mHDC = nullptr;
        }
#endif

        std::cout << "OpenGL backend resources released." << std::endl;
    }

}