#ifndef RUNTIME_DEFINES_H
#define RUNTIME_DEFINES_H

// Notice! Nomad Engine uses C++20 standard.
// Please ensure your compiler supports C++20 features.
constexpr unsigned int CPP_VERSION_MAJOR = 202002L;
static_assert(__cplusplus >= CPP_VERSION_MAJOR, "Nomad Engine requires C++20 or later");

// ----------------------------------------
// Platform Detection
// ----------------------------------------
#pragma region Platform Detection
#if defined(_WIN32) || defined(_WIN64)
    #define ENABLE_PLATFORM_WINDOWS
#elif defined(__APPLE__)
    #define ENABLE_PLATFORM_APPLE
#elif defined(__ANDROID__)
    #define ENABLE_PLATFORM_ANDROID
#elif defined(__linux__)
    #define ENABLE_PLATFORM_LINUX
#else
    #error "Unsupported platform"
#endif
#pragma endregion

// ----------------------------------------
// Architecture Detection
// ----------------------------------------
#pragma region Architecture Detection
#if defined(_M_X64) || defined(__x86_64__)
    #define ENABLE_ARCH_X64
#elif defined(_M_IX86) || defined(__i386__)
    #define ENABLE_ARCH_X86
#elif defined(_M_ARM) || defined(__arm__)
    #define ENABLE_ARCH_ARM
#elif defined(_M_ARM64) || defined(__aarch64__)
    #define ENABLE_ARCH_ARM64
#else
    #error "Unsupported architecture"
#endif
#pragma endregion

// ----------------------------------------
// Compiler Detection
// ----------------------------------------
#pragma region Compiler Detection
#if defined(_MSC_VER)
    #define ENABLE_COMPILER_MSVC
#elif defined(__clang__)
    #define ENABLE_COMPILER_CLANG
#elif defined(__GNUC__) || defined(__GNUG__)
    #define ENABLE_COMPILER_GCC
#else
    #error "Unsupported compiler"
#endif
#pragma endregion

// ----------------------------------------
// Build Configuration Detection
// ----------------------------------------
#pragma region Build Configuration Detection
    #if defined(_DEBUG) || defined(DEBUG)
        #define ENABLE_DEBUG
#elif defined(_RELEASE) || defined(NDEBUG)
    #define ENABLE_RELEASE
#endif
#pragma endregion

// ================================================
// Attributes
// ================================================
#define NODISCARD [[nodiscard]]

// DLL Export/Import
#if defined(ENABLE_PLATFORM_WINDOWS)
    #if defined(ENABLE_EXPORT)
        #define NOMAD_API __declspec(dllexport)
    #elif defined(ENABLE_IMPORT)
        #define NOMAD_API __declspec(dllimport)
    #else
        #define NOMAD_API
    #endif
#else
    #if defined(NOMAD_COMPILER_GCC) || defined(NOMAD_COMPILER_CLANG)
        #define NOMAD_API __attribute__((visibility("default")))
    #else
        #define NOMAD_API
    #endif
#endif

// 함수 호출 규약
#if defined(NOMAD_PLATFORM_WINDOWS) && defined(NOMAD_COMPILER_MSVC)
    #define CDECL __cdecl
    #define STDCALL __stdcall
    #define FASTCALL __fastcall
    #define VECTORCALL __vectorcall
#else
    #define CDECL
    #define STDCALL
    #define FASTCALL
    #define VECTORCALL
#endif

// 인라인 힌트
#if defined(NOMAD_COMPILER_MSVC)
    #define FORCEINLINE __forceinline
    #define NOINLINE __declspec(noinline)
#elif defined(NOMAD_COMPILER_GCC) || defined(NOMAD_COMPILER_CLANG)
    #define FORCEINLINE __attribute__((always_inline)) inline
    #define NOINLINE __attribute__((noinline))
#else
    #define FORCEINLINE inline
    #define NOINLINE
#endif

// 메모리 정렬
#if defined(NOMAD_COMPILER_MSVC)
    #define NOMAD_ALIGN(x) __declspec(align(x))
#elif defined(NOMAD_COMPILER_GCC) || defined(NOMAD_COMPILER_CLANG)
    #define NOMAD_ALIGN(x) __attribute__((aligned(x)))
#else
    #define NOMAD_ALIGN(x) alignas(x)
#endif

// 함수/변수 어트리뷰트
#if defined(NOMAD_COMPILER_MSVC)
    #define DEPRECATED(msg) __declspec(deprecated(msg))
    #define NORETURN __declspec(noreturn)
    #define RESTRICT __restrict
#elif defined(NOMAD_COMPILER_GCC) || defined(NOMAD_COMPILER_CLANG)
    #define DEPRECATED(msg) __attribute__((deprecated(msg)))
    #define NORETURN __attribute__((noreturn))
    #define RESTRICT __restrict__
#else
    #define DEPRECATED(msg) [[deprecated(msg)]]
    #define NORETURN [[noreturn]]
    #define RESTRICT
#endif

// 브랜치 예측 힌트
#if defined(NOMAD_COMPILER_GCC) || defined(NOMAD_COMPILER_CLANG)
    #define LIKELY(x) __builtin_expect(!!(x), 1)
    #define UNLIKELY(x) __builtin_expect(!!(x), 0)
#else
    #define LIKELY(x) (x)
    #define UNLIKELY(x) (x)
#endif

// 컴파일러 최적화 힌트
#if defined(NOMAD_COMPILER_MSVC)
    #define ASSUME(x) __assume(x)
    #define UNREACHABLE() __assume(0)
#elif defined(NOMAD_COMPILER_GCC) || defined(NOMAD_COMPILER_CLANG)
    #define ASSUME(x) do { if (!(x)) __builtin_unreachable(); } while(0)
    #define UNREACHABLE() __builtin_unreachable()
#else
    #define ASSUME(x) (void)(x)
    #define UNREACHABLE()
#endif

// 순수 함수 (부작용 없음)
#if defined(NOMAD_COMPILER_GCC) || defined(NOMAD_COMPILER_CLANG)
    #define PURE __attribute__((pure))
    #define CONST __attribute__((const))
#else
    #define PURE
    #define CONST
#endif

// 핫/콜드 패스 힌트
#if defined(NOMAD_COMPILER_GCC) || defined(NOMAD_COMPILER_CLANG)
    #define HOT __attribute__((hot))
    #define COLD __attribute__((cold))
#else
    #define HOT
    #define COLD
#endif

// 패킹된 구조체
#if defined(NOMAD_COMPILER_MSVC)
    #define PACKED_BEGIN __pragma(pack(push, 1))
    #define PACKED_END __pragma(pack(pop))
    #define PACKED_STRUCT(name) struct name
#elif defined(NOMAD_COMPILER_GCC) || defined(NOMAD_COMPILER_CLANG)
    #define PACKED_BEGIN
    #define PACKED_END
    #define PACKED_STRUCT(name) struct __attribute__((packed)) name
#else
    #define PACKED_BEGIN
    #define PACKED_END
    #define PACKED_STRUCT(name) struct name
#endif

// 경고 제어
#if defined(NOMAD_COMPILER_MSVC)
    #define PUSH_WARNING __pragma(warning(push))
    #define POP_WARNING __pragma(warning(pop))
    #define DISABLE_WARNING(x) __pragma(warning(disable: x))
#elif defined(NOMAD_COMPILER_GCC)
    #define PUSH_WARNING _Pragma("GCC diagnostic push")
    #define POP_WARNING _Pragma("GCC diagnostic pop")
    #define DISABLE_WARNING(x) _Pragma("GCC diagnostic ignored \"" #x "\"")
#elif defined(NOMAD_COMPILER_CLANG)
    #define PUSH_WARNING _Pragma("clang diagnostic push")
    #define POP_WARNING _Pragma("clang diagnostic pop")
    #define DISABLE_WARNING(x) _Pragma("clang diagnostic ignored \"" #x "\"")
#else
    #define PUSH_WARNING
    #define POP_WARNING
    #define DISABLE_WARNING(x)
#endif

// 디버그 전용 매크로
#if defined(NOMAD_DEBUG)
    #define DEBUG_ONLY(x) x
    #define RELEASE_ONLY(x)
#else
    #define DEBUG_ONLY(x)
    #define RELEASE_ONLY(x) x
#endif

#endif