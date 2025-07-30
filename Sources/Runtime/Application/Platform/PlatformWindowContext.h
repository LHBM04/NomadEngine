#ifndef GUARD_PLATFORMWINDOWCONTEXT_H
#define GUARD_PLATFORMWINDOWCONTEXT_H

namespace NomadEngine::Runtime
{
    struct PlatformWindowContext
    {
        /**
         * @brief 윈도우의 제목.
         */
        const wchar_t* title;

        /**
         * @brief 윈도우의 너비.
         */
        int width;

        /**
         * @brief 윈도우의 높이.
         */
        int height;

    };

}

#endif
