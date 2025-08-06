#ifndef RUNTIME_LOGGER_H
#define RUNTIME_LOGGER_H

#include <string_view>

namespace NomadEngine::Runtime
{
    /**
     * @class Logger
     *
     * @brief 런타임에서 로그 메시지를 출력하는 기능을 제공합니다.
     */
    class Logger
    {
      public:
        /**
         * @brief 로그 메시지를 출력합니다.
         *
         * @param message_ 출력할 메시지.
         */
        static void Log(std::string_view message_) noexcept;

        /**
         * @brief 경고 메시지를 출력합니다.
         *
         * @param message_ 출력할 경고 메시지.
         */
        static void LogWarn(std::string_view message_) noexcept;

        /**
         * @brief 오류 메시지를 출력합니다.
         *
         * @param message_ 출력할 오류 메시지.
         */
        static void LogError(std::string_view message_) noexcept;

      private:
        static constexpr const char *const LOG_HEADER;
        static constexpr const char *const LOG_WARN_HEADER;
        static constexpr const char *const LOG_ERROR_HEADER;
    };
} // namespace NomadEngine::Runtime

#endif