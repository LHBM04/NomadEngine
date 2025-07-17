#ifndef GUARD_TYPES_H
#define GUARD_TYPES_H

#include <cstddef>
#include <cstdint>
#include <cstdio>

// 호출 규약 alias
#define STDCALL __stdcall
#define CDECL __cdecl
#define FASTCALL __fastcall
#define INLINE __inline

#define Ptr *

namespace Sandbox
{
    // void 타입 alias //
    using Void = void;

    using VVoid = volatile void;

    // 정수 타입 alias //
    using UInt8 = std::uint8_t;
    using UInt16 = std::uint16_t;
    using UInt32 = std::uint32_t;
    using UInt64 = std::uint64_t;
    using Int8 = std::int8_t;
    using Int16 = std::int16_t;
    using Int32 = std::int32_t;
    using Int64 = std::int64_t;

    using VUInt8 = volatile UInt8;
    using VUInt16 = volatile UInt16;
    using VUInt32 = volatile UInt32;
    using VUInt64 = volatile UInt64;
    using VInt8 = volatile Int8;
    using VInt16 = volatile Int16;
    using VInt32 = volatile Int32;
    using VInt64 = volatile Int64;

    // 실수 타입 alias //
    using Float32 = float;
    using Float64 = double;

    using VFloat32 = volatile Float32;
    using VFloat64 = volatile Float64;

}
#endif // GUARD_TYPES_H
