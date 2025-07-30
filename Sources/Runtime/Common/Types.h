#pragma once

// ================================================
// Platform and Compiler Detection
// ================================================
#if defined(_WIN32) || defined(_WIN64)
    #define NOMAD_PLATFORM_WINDOWS 1
    #define NOMAD_PLATFORM_NAME "Windows"
#elif defined(__linux__)
    #define NOMAD_PLATFORM_LINUX 1
    #define NOMAD_PLATFORM_NAME "Linux"
#elif defined(__APPLE__)
    #define NOMAD_PLATFORM_MACOS 1
    #define NOMAD_PLATFORM_NAME "macOS"
#else
    #error "Unsupported platform"
#endif

#if defined(_MSC_VER)
    #define NOMAD_COMPILER_MSVC 1
    #define NOMAD_COMPILER_NAME "MSVC"
#elif defined(__clang__)
    #define NOMAD_COMPILER_CLANG 1
    #define NOMAD_COMPILER_NAME "Clang"
#elif defined(__GNUC__)
    #define NOMAD_COMPILER_GCC 1
    #define NOMAD_COMPILER_NAME "GCC"
#endif

// ================================================
// Standard Headers
// ================================================
#include <cstdint>
#include <cstddef>
#include <limits>
#include <type_traits>

// ================================================
// Calling Conventions
// ================================================
#ifdef NOMAD_PLATFORM_WINDOWS
    #define NOMAD_STDCALL    __stdcall
    #define NOMAD_CDECL      __cdecl
    #define NOMAD_FASTCALL   __fastcall
    #define NOMAD_VECTORCALL __vectorcall
    #define NOMAD_FORCEINLINE __forceinline
    #define NOMAD_NOINLINE   __declspec(noinline)
    #define NOMAD_ALIGN(x)   __declspec(align(x))
    #define NOMAD_NOVTABLE   __declspec(novtable)
    #define NOMAD_RESTRICT   __restrict
#else
    #define NOMAD_STDCALL
    #define NOMAD_CDECL
    #define NOMAD_FASTCALL
    #define NOMAD_VECTORCALL
    #define NOMAD_FORCEINLINE inline __attribute__((always_inline))
    #define NOMAD_NOINLINE   __attribute__((noinline))
    #define NOMAD_ALIGN(x)   __attribute__((aligned(x)))
    #define NOMAD_NOVTABLE
    #define NOMAD_RESTRICT   __restrict__
#endif

// ================================================
// Build Configuration
// ================================================
#ifdef _DEBUG
    #define NOMAD_DEBUG 1
    #define NOMAD_BUILD_CONFIG "Debug"
#else
    #define NOMAD_RELEASE 1
    #define NOMAD_BUILD_CONFIG "Release"
#endif

// ================================================
// Compiler Attributes
// ================================================
#ifdef __cplusplus
    #ifdef __cpp_constexpr
        #define NOMAD_CONSTEXPR constexpr
    #else
        #define NOMAD_CONSTEXPR inline
    #endif

    #if __cplusplus >= 202002L
        #define NOMAD_CPP20 1
        #define NOMAD_CONSTEVAL consteval
        #define NOMAD_CONSTINIT constinit
    #else
        #define NOMAD_CONSTEVAL constexpr
        #define NOMAD_CONSTINIT
    #endif

    #if __cplusplus >= 201703L
        #define NOMAD_CPP17 1
        #define NOMAD_NODISCARD [[nodiscard]]
        #define NOMAD_MAYBE_UNUSED [[maybe_unused]]
        #define NOMAD_FALLTHROUGH [[fallthrough]]
    #else
        #define NOMAD_NODISCARD
        #define NOMAD_MAYBE_UNUSED
        #define NOMAD_FALLTHROUGH
    #endif
#endif

// ================================================
// API Macros
// ================================================
#ifdef NOMAD_PLATFORM_WINDOWS
    #ifdef NOMAD_ENGINE_EXPORTS
        #define NOMAD_API __declspec(dllexport)
    #else
        #define NOMAD_API __declspec(dllimport)
    #endif
#else
    #define NOMAD_API __attribute__((visibility("default")))
#endif

namespace NomadEngine::Runtime
{
    // ================================================
    // Integer Types
    // ================================================
    using int8   = std::int8_t;         ///< 8비트 부호 있는 정수
    using int16  = std::int16_t;        ///< 16비트 부호 있는 정수
    using int32  = std::int32_t;        ///< 32비트 부호 있는 정수
    using int64  = std::int64_t;        ///< 64비트 부호 있는 정수

    using uint8  = std::uint8_t;        ///< 8비트 부호 없는 정수
    using uint16 = std::uint16_t;       ///< 16비트 부호 없는 정수
    using uint32 = std::uint32_t;       ///< 32비트 부호 없는 정수
    using uint64 = std::uint64_t;       ///< 64비트 부호 없는 정수

    using byte   = uint8;               ///< 바이트 타입
    using size_t = std::size_t;         ///< 크기 타입
    using ptrdiff_t = std::ptrdiff_t;   ///< 포인터 차이 타입

    // ================================================
    // Floating Point Types
    // ================================================
    using float32 = float;              ///< 32비트 부동소수점
    using float64 = double;             ///< 64비트 부동소수점
    using real    = float32;            ///< 기본 실수 타입 (성능을 위해 float32 사용)

    // ================================================
    // Character Types
    // ================================================
    using char8   = char;               ///< ASCII/UTF-8 문자
    using char16  = char16_t;           ///< UTF-16 문자
    using char32  = char32_t;           ///< UTF-32 문자
    using wchar   = wchar_t;            ///< 와이드 문자

    // ================================================
    // Handle Types
    // ================================================
    using Handle = void*;               ///< 일반적인 핸들 타입

    template<typename T>
    using UniqueHandle = T;             ///< 고유 핸들 타입

    // ================================================
    // Memory Size Constants
    // ================================================
    NOMAD_CONSTEXPR size_t KILOBYTE = 1024ULL;
    NOMAD_CONSTEXPR size_t MEGABYTE = KILOBYTE * 1024ULL;
    NOMAD_CONSTEXPR size_t GIGABYTE = MEGABYTE * 1024ULL;
    NOMAD_CONSTEXPR size_t TERABYTE = GIGABYTE * 1024ULL;

    // ================================================
    // Platform-specific Types
    // ================================================
#ifdef NOMAD_PLATFORM_WINDOWS
    using HModule     = void*;          ///< Windows 모듈 핸들
    using HInstance   = void*;          ///< Windows 인스턴스 핸들
    using HWnd        = void*;          ///< Windows 윈도우 핸들
    using HDC         = void*;          ///< Windows 디바이스 컨텍스트
    using HBitmap     = void*;          ///< Windows 비트맵 핸들
    using HIcon       = void*;          ///< Windows 아이콘 핸들
    using HCursor     = void*;          ///< Windows 커서 핸들
    using HBrush      = void*;          ///< Windows 브러시 핸들
    using DWORD       = unsigned long;  ///< Windows DWORD
    using WORD        = unsigned short; ///< Windows WORD
    using BOOL        = int;            ///< Windows BOOL
#endif

    // ================================================
    // Result Types
    // ================================================
    enum class ResultCode : int32
    {
        Success = 0,                    ///< 성공
        Failure = -1,                   ///< 일반적인 실패
        InvalidArgument = -2,           ///< 잘못된 인수
        OutOfMemory = -3,              ///< 메모리 부족
        NotImplemented = -4,           ///< 구현되지 않음
        NotSupported = -5,             ///< 지원되지 않음
        AccessDenied = -6,             ///< 접근 거부
        FileNotFound = -7,             ///< 파일을 찾을 수 없음
        Timeout = -8,                  ///< 시간 초과
        Cancelled = -9,                ///< 취소됨
        AlreadyExists = -10,           ///< 이미 존재함
        EndOfFile = -11,               ///< 파일 끝
        NetworkError = -12,            ///< 네트워크 오류
        ParseError = -13,              ///< 파싱 오류
        CompressionError = -14,        ///< 압축 오류
        GraphicsError = -15,           ///< 그래픽스 오류
        AudioError = -16,              ///< 오디오 오류
        Unknown = -1000                ///< 알 수 없는 오류
    };

    // ================================================
    // Boolean Constants
    // ================================================
    NOMAD_CONSTEXPR bool TRUE_VALUE  = true;
    NOMAD_CONSTEXPR bool FALSE_VALUE = false;

    // ================================================
    // Null Constants
    // ================================================
    NOMAD_CONSTEXPR std::nullptr_t NULL_HANDLE = nullptr;

    // ================================================
    // Numeric Limits
    // ================================================
    NOMAD_CONSTEXPR int8   INT8_MIN_VALUE   = std::numeric_limits<int8>::min();
    NOMAD_CONSTEXPR int8   INT8_MAX_VALUE   = std::numeric_limits<int8>::max();
    NOMAD_CONSTEXPR int16  INT16_MIN_VALUE  = std::numeric_limits<int16>::min();
    NOMAD_CONSTEXPR int16  INT16_MAX_VALUE  = std::numeric_limits<int16>::max();
    NOMAD_CONSTEXPR int32  INT32_MIN_VALUE  = std::numeric_limits<int32>::min();
    NOMAD_CONSTEXPR int32  INT32_MAX_VALUE  = std::numeric_limits<int32>::max();
    NOMAD_CONSTEXPR int64  INT64_MIN_VALUE  = std::numeric_limits<int64>::min();
    NOMAD_CONSTEXPR int64  INT64_MAX_VALUE  = std::numeric_limits<int64>::max();

    NOMAD_CONSTEXPR uint8  UINT8_MAX_VALUE  = std::numeric_limits<uint8>::max();
    NOMAD_CONSTEXPR uint16 UINT16_MAX_VALUE = std::numeric_limits<uint16>::max();
    NOMAD_CONSTEXPR uint32 UINT32_MAX_VALUE = std::numeric_limits<uint32>::max();
    NOMAD_CONSTEXPR uint64 UINT64_MAX_VALUE = std::numeric_limits<uint64>::max();

    NOMAD_CONSTEXPR float32 FLOAT32_MIN_VALUE     = std::numeric_limits<float32>::min();
    NOMAD_CONSTEXPR float32 FLOAT32_MAX_VALUE     = std::numeric_limits<float32>::max();
    NOMAD_CONSTEXPR float32 FLOAT32_EPSILON       = std::numeric_limits<float32>::epsilon();
    NOMAD_CONSTEXPR float32 FLOAT32_INFINITY      = std::numeric_limits<float32>::infinity();
    NOMAD_CONSTEXPR float32 FLOAT32_QUIET_NAN     = std::numeric_limits<float32>::quiet_NaN();

    NOMAD_CONSTEXPR float64 FLOAT64_MIN_VALUE     = std::numeric_limits<float64>::min();
    NOMAD_CONSTEXPR float64 FLOAT64_MAX_VALUE     = std::numeric_limits<float64>::max();
    NOMAD_CONSTEXPR float64 FLOAT64_EPSILON       = std::numeric_limits<float64>::epsilon();
    NOMAD_CONSTEXPR float64 FLOAT64_INFINITY      = std::numeric_limits<float64>::infinity();
    NOMAD_CONSTEXPR float64 FLOAT64_QUIET_NAN     = std::numeric_limits<float64>::quiet_NaN();

    // ================================================
    // Mathematical Constants
    // ================================================
    NOMAD_CONSTEXPR real PI              = 3.14159265358979323846f;
    NOMAD_CONSTEXPR real TWO_PI          = 6.28318530717958647692f;
    NOMAD_CONSTEXPR real HALF_PI         = 1.57079632679489661923f;
    NOMAD_CONSTEXPR real QUARTER_PI      = 0.78539816339744830961f;
    NOMAD_CONSTEXPR real INV_PI          = 0.31830988618379067154f;
    NOMAD_CONSTEXPR real INV_TWO_PI      = 0.15915494309189533577f;
    NOMAD_CONSTEXPR real E               = 2.71828182845904523536f;
    NOMAD_CONSTEXPR real LOG2E           = 1.44269504088896340736f;
    NOMAD_CONSTEXPR real LOG10E          = 0.43429448190325182765f;
    NOMAD_CONSTEXPR real LN2             = 0.69314718055994530942f;
    NOMAD_CONSTEXPR real LN10            = 2.30258509299404568402f;
    NOMAD_CONSTEXPR real SQRT2           = 1.41421356237309504880f;
    NOMAD_CONSTEXPR real INV_SQRT2       = 0.70710678118654752440f;
    NOMAD_CONSTEXPR real SQRT3           = 1.73205080756887729352f;
    NOMAD_CONSTEXPR real INV_SQRT3       = 0.57735026918962576451f;
    NOMAD_CONSTEXPR real GOLDEN_RATIO    = 1.61803398874989484820f;

    // ================================================
    // Angle Conversion Constants
    // ================================================
    NOMAD_CONSTEXPR real DEG_TO_RAD      = PI / 180.0f;
    NOMAD_CONSTEXPR real RAD_TO_DEG      = 180.0f / PI;

    // ================================================
    // Type Traits and Concepts
    // ================================================
    template<typename T>
    NOMAD_CONSTEXPR bool IsIntegral = std::is_integral_v<T>;

    template<typename T>
    NOMAD_CONSTEXPR bool IsFloatingPoint = std::is_floating_point_v<T>;

    template<typename T>
    NOMAD_CONSTEXPR bool IsNumeric = IsIntegral<T> || IsFloatingPoint<T>;

    template<typename T>
    NOMAD_CONSTEXPR bool IsPointer = std::is_pointer_v<T>;

    template<typename T>
    NOMAD_CONSTEXPR bool IsReference = std::is_reference_v<T>;

    template<typename T>
    NOMAD_CONSTEXPR bool IsSigned = std::is_signed_v<T>;

    template<typename T>
    NOMAD_CONSTEXPR bool IsUnsigned = std::is_unsigned_v<T>;

    // ================================================
    // Utility Functions
    // ================================================
    template<typename T>
    NOMAD_CONSTEXPR T Min(const T& a, const T& b) noexcept
    {
        return (a < b) ? a : b;
    }

    template<typename T>
    NOMAD_CONSTEXPR T Max(const T& a, const T& b) noexcept
    {
        return (a > b) ? a : b;
    }

    template<typename T>
    NOMAD_CONSTEXPR T Clamp(const T& value, const T& min, const T& max) noexcept
    {
        return Max(min, Min(value, max));
    }

    template<typename T>
    NOMAD_CONSTEXPR T Abs(const T& value) noexcept
    {
        return (value < T(0)) ? -value : value;
    }

    // ================================================
    // Memory Alignment Utilities
    // ================================================
    template<size_t Alignment>
    NOMAD_CONSTEXPR size_t AlignUp(size_t value) noexcept
    {
        static_assert((Alignment & (Alignment - 1)) == 0, "Alignment must be power of 2");
        return (value + Alignment - 1) & ~(Alignment - 1);
    }

    template<size_t Alignment>
    NOMAD_CONSTEXPR size_t AlignDown(size_t value) noexcept
    {
        static_assert((Alignment & (Alignment - 1)) == 0, "Alignment must be power of 2");
        return value & ~(Alignment - 1);
    }

    template<size_t Alignment>
    NOMAD_CONSTEXPR bool IsAligned(size_t value) noexcept
    {
        static_assert((Alignment & (Alignment - 1)) == 0, "Alignment must be power of 2");
        return (value & (Alignment - 1)) == 0;
    }

    // ================================================
    // Hash Utilities
    // ================================================
    using HashValue = uint64;

    NOMAD_CONSTEXPR HashValue INVALID_HASH = 0;

    // ================================================
    // ID and Index Types
    // ================================================
    using EntityID = uint32;
    using ComponentID = uint32;
    using SystemID = uint32;
    using ResourceID = uint64;
    using Index = uint32;

    NOMAD_CONSTEXPR EntityID INVALID_ENTITY_ID = UINT32_MAX_VALUE;
    NOMAD_CONSTEXPR ComponentID INVALID_COMPONENT_ID = UINT32_MAX_VALUE;
    NOMAD_CONSTEXPR SystemID INVALID_SYSTEM_ID = UINT32_MAX_VALUE;
    NOMAD_CONSTEXPR ResourceID INVALID_RESOURCE_ID = UINT64_MAX_VALUE;
    NOMAD_CONSTEXPR Index INVALID_INDEX = UINT32_MAX_VALUE;

} // namespace NomadEngine::Runtime

// ================================================
// Global Namespace Aliases (선택적)
// ================================================
// 편의를 위한 전역 별칭들 (필요에 따라 사용)
namespace Nomad = NomadEngine::Runtime;
