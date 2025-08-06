#include "../Runtime/Common/Logger.h"

#include <cstdio>
#include <format>

namespace NomadEngine::Runtime
{
constexpr const char *const Logger::LOG_HEADER       = "[LOG]";
constexpr const char *const Logger::LOG_WARN_HEADER  = "[WARNING]";
constexpr const char *const Logger::LOG_ERROR_HEADER = "[ERROR]";

void
Logger::Log(std::string_view message_) noexcept
{
    fprintf(stdout, "[LOG] %.*s\n", static_cast<int>(message_.size()), message_.data());
}

void
Logger::LogWarn(std::string_view message_) noexcept
{
    fprintf(stderr, "[WARNING] %.*s\n", static_cast<int>(message_.size()), message_.data());
}

void
Logger::LogError(std::string_view message_) noexcept
{
    fprintf(stderr, "[ERROR] %.*s\n", static_cast<int>(message_.size()), message_.data());
}
} // namespace NomadEngine::Runtime