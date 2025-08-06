#ifndef RUNTIME_DISPLAYPCH_H
#define RUNTIME_DISPLAYPCH_H

#include "../Runtime/Common/Defines.h"
#include "../Runtime/Common/Types.h"

#ifdef ENABLE_PLATFORM_WINDOWS
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#elifdef ENABLE_PLATFORM_LINUX
#include <SDL3/SDL.h>
#endif

#endif // RUNTIME_DISPLAYPCH_H
