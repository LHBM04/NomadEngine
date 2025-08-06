#ifndef GUARD_RENDERSYSTEMDESCRIPTOR_H
#define GUARD_RENDERSYSTEMDESCRIPTOR_H

#include <cstdint>
#include <windows.h>

#include "../Common/Defines.h"

namespace NomadEngine::Runtime
{
/**
 * @struct RenderingServerDescriptor
 *
 * @brief 렌더링 시스템의 설정을 기술합니다.
 */
struct RenderingServerDescriptor
{
#if defined(NOMAD_PLATFORM_WINDOWS)
    HWND Hwnd;
#else
    SDL_Window *WindowHandle;
#endif
    uint32_t Width;
    uint32_t Height;
};
} // namespace NomadEngine::Runtime

#endif // !GUARD_RENDERSYSTEMDESCRIPTOR_H
