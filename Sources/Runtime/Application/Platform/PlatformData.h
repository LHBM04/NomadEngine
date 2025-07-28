#ifndef GUARD_PLATFORMCONTEXT_H
#define GUARD_PLATFORMCONTEXT_H

namespace NomadEngine::Runtime
{
    /**
     * @struct PlatformData
     *
     * @brief 플랫폼 정보를 담습니다.
     */
    struct PlatformData
    {
        /**
         * @brief 플랫폼 타입을 정의합니다.
         */
        enum class EType
        {
            /**
             * @brief SDL.
             */
            SDL,

            /**
             * @brief Win32.
             */
            Win32,

            /**
             * @brief GLFW.
             */
            GLFW,

        };

        /**
         * @brief 타입.
         */
        EType type;

        /**
         * @brief 윈도우.
         */
        void* window;

    };
}

#endif // !GUARD_PLATFORMCONTEXT_H
