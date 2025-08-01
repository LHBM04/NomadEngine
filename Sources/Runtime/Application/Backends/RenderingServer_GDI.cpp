#include "../Runtime/Application/Backends/RenderingServer_GDI.h"

#include <winuser.h>

namespace NomadEngine::Runtime
{
    RenderingServer_GDI::RenderingServer_GDI()
    {

    }

    RenderingServer_GDI::~RenderingServer_GDI()
    {
        RenderingServer_GDI::Finalize();
    }

    bool RenderingServer_GDI::Initialize()
    {
        // GDI 초기화 로직을 여기에 추가합니다.
        return true;
    }

    void RenderingServer_GDI::BeginFrame()
    {
        RECT rc;
        GetClientRect(mWindowDC, &rc);
        HBRUSH brush = CreateSolidBrush(RGB(30, 30, 30));
        FillRect(mBackBufferDC, &rc, brush);
        DeleteObject(brush);
    }

    void RenderingServer_GDI::Present()
    {
        // 프레임 렌더링 로직을 여기에 추가합니다.
        // GDI를 사용하여 화면에 그리기 작업을 수행합니다.
    }

    void RenderingServer_GDI::EndFrame()
    {
        // 프레임 종료 로직을 여기에 추가합니다.
    }

    bool RenderingServer_GDI::Finalize()
    {

    }

}
