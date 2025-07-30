#ifndef GUARD_IPLATFORMWINDOW_H
#define GUARD_IPLATFORMWINDOW_H

#include "../Runtime/Application/Platform/PlatformWindowContext.h"

namespace NomadEngine::Runtime
{
    /**
     * @class IPlatformWindow
     *
     * @brief 플랫폼 윈도우의 인터페이스를 정의합니다.
     */
    class IPlatformWindow
    {
    public:
        /**
         * @brief 생성자.
         */
        virtual ~IPlatformWindow() = default;

        /**
         * @brief 플랫폼 윈도우를 초기화합니다.
         *
         * @param context_ 플랫폼 윈도우 생성 컨텍스트.
         *
         * @return bool 성공하면 true, 실패하면 false를 반환합니다.
         */
        virtual bool Initialize(const PlatformWindowContext& context_) = 0;

        /**
         * @brief 플랫폼 윈도우를 해제합니다.
         *
         * @return bool 성공하면 true, 실패하면 false를 반환합니다.
         */
        virtual bool Finalize() = 0;

    };
}

#endif
