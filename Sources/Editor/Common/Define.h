#ifndef EDTIOR_DEFINES_H
#define EDTIOR_DEFINES_H

// 플랫폼 감지
#if defined(_WIN32) || defined(_WIN64)
    #define NOMAD_PLATFORM_WINDOWS
#elif defined(__APPLE__) && defined(__MACH__)
    #define NOMAD_PLATFORM_APPLE 1
#elif defined(__ANDROID__)
    #define NOMAD_PLATFORM_ANDROID 1
#elif defined(__linux__)
    #define NOMAD_PLATFORM_LINUX 1
#else
    #error "Unsupported platform"
#endif

// 아키텍처 감지
#if defined(_M_X64) || defined(__x86_64__)
    #define NOMAD_ARCH_X64 1
#elif defined(_M_IX86) || defined(__i386__)
    #define NOMAD_ARCH_X86 1
#elif defined(_M_ARM) || defined(__arm__)
    #define NOMAD_ARCH_ARM 1
#elif defined(_M_ARM64) || defined(__aarch64__)
    #define NOMAD_ARCH_ARM64 1
#endif

// 컴파일러 감지
#if defined(_MSC_VER)
#define NOMAD_COMPILER_MSVC 1
#elif defined(__clang__)
#define NOMAD_COMPILER_CLANG 1
#elif defined(__GNUC__) || defined(__GNUG__)
#define NOMAD_COMPILER_GCC 1
#else
#error "Unsupported compiler"
#endif

// 빌드 모드 감지
#if defined(_DEBUG) || defined(DEBUG)
    #define NOMAD_DEBUG 1
    #define NOMAD_RELEASE 0
#else
    #define NOMAD_DEBUG 0
    #define NOMAD_RELEASE 1
#endif

#endif