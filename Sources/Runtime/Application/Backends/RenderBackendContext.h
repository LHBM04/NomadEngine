#ifndef GUARD_RENDERBACKENDCONTEXT_H
#define GUARD_RENDERBACKENDCONTEXT_H

#include "../Runtime/Utilities/Math/Color.h"

namespace NomadEngine::Runtime
{
    /**
     *
     */
    struct RenderBackendContext
    {
        /**
         * @brief VSync 사용 여부.
         */
        bool useVSync;

        /**
         * @brief 화면 새로 고침 빈도.
         */
        int refreshRate;

        /**
         * @brief 렌더링 영역의 너비.
         */
        int width;

        /**
         * @brief 렌더링 영역의 높이.
         */
        int height;

        /**
         * @brief 기본 렌더 색상.
         */
        Color drawColor;

    };

}

#endif
