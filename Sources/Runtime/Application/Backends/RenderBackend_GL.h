#ifndef GUARD_RENDERBACKEND_GL_H
#define GUARD_RENDERBACKEND_GL_H
#include "RenderBackendBase.h"

#ifdef _WIN32
#include <windows.h>
#endif

#include "../Runtime/Application/Backends/RenderBackendBase.h"

namespace NomadEngine::Runtime
{
    class RenderBackend_GL
        : public RenderBackendBase
    {
    public:
        /**
         * @brief 생성자.
         */
        RenderBackend_GL();

        /**
         * @brief 소멸자.
         */
        virtual ~RenderBackend_GL() override;

        /**
         * @brief GL 렌더러를 초기화합니다.
         *
         * @param platformData_ 플랫폼 데이터.
         *
         * @return bool 성공하면 true, 실패하면 false를 반환합니다.
         */
        virtual bool __fastcall Initialize(const PlatformData& platformData_) override;

        /**
         * @brief GL 백엔드 내에서 렌더링을 시작합니다.
         */
        virtual void __fastcall BeginFrame() override;

        /**
         * @brief GL 백엔드 내에서 렌더링을 종료합니다.
         */
        virtual void __fastcall EndFrame() override;

        /**
         * @brief GL 백엔드 내 모든 리소스를 해제합니다.
         */
        virtual void __fastcall Release() override;

    private:
#ifdef _WIN32
        /**
         * @brief Win32 디바이스 컨텍스트 핸들.
         */
        HDC mHDC;

        /**
         * @brief Win32 OpenGL 렌더러 컨텍스트 핸들.
         */
        HGLRC mHGLRC;

        /**
         * @brief Win32 플랫폼에서 OpenGL 컨텍스트를 설정합니다.
         *
         * @param platformData_ 플랫폼 데이터
         * @return 성공하면 true, 실패하면 false
         */
        bool mSetupWin32OpenGL(const PlatformData& platformData_);

#endif
        /**
         * @brief 플랫폼별 OpenGL 컨텍스트를 설정합니다.
         *
         * @param platformData_ 플랫폼 데이터
         * @return 성공하면 true, 실패하면 false
         */
        bool mSetupOpenGLContext(const PlatformData& platformData_);

        /**
         * @brief SDL3 플랫폼에서 OpenGL 컨텍스트를 설정합니다.
         *
         * @param platformData_ 플랫폼 데이터
         * @return 성공하면 true, 실패하면 false
         */
        bool mSetupSDL3OpenGL(const PlatformData& platformData_);

        /**
         * @brief 플랫폼별 버퍼 스왑을 처리합니다.
         */
        void mSwapBuffers();

    };

}

#endif // !GUARD_RENDERBACKEND_GL_H
