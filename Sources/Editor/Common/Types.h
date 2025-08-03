#ifndef EDITOR_TYPES_H
#define EDITOR_TYPES_H

// Notice! Nomad Engine uses C++20 standard.
// Please ensure your compiler supports C++20 features.
static_assert(__cplusplus >= 202002L, "Require C++20 or later");

#include <cstddef>
#include <cstdint>

namespace NomadEngine::Runtime
{
    using Void      = void;

    using Bool      = bool;
    using Bool8     = uint8_t;
    using Bool16    = uint16_t;

    using Int8      = int8_t;
    using Int16     = int16_t;
    using Int32     = int32_t;
    using Int64     = int64_t;

    using UInt8     = uint8_t;
    using UInt16    = uint16_t;
    using UInt32    = uint32_t;
    using UInt64    = uint64_t;

    using Float32   = float;
    using Float64   = double;

    using Char8     = char8_t;
    using Char16    = char16_t;
    using Char32    = char32_t;
    using WChar     = wchar_t;

    using USize     = std::size_t;
    using Size      = std::ptrdiff_t;

} // namespace NomadEngine::Runtime

#endif