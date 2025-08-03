#ifndef GUARD_DEFINES_H
#define GUARD_DEFINES_H

// 플랫폼 감지
#if defined(_WIN32) || defined(_WIN64)
    #define NOMAD_PLATFORM_WINDOWS 1
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

#endif