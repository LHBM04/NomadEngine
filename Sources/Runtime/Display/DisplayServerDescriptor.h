#ifndef RUNTIME_DISPLAYSERVERDESCRIPTOR_H
#define RUNTIME_DISPLAYSERVERDESCRIPTOR_H

#include <string_view>

#include "../Runtime/Common/Types.h"

namespace NomadEngine::Runtime
{
    /**
     * @struct DisplayServerDescriptor
     *
     * @brief 디스플레이 서버의 설정을 기술합니다.
     */
    struct DisplayServerDescriptor
    {
        /**
         * @brief 생성될 디스플레이의 제목.
         */
        std::string_view title;

        /**
         * @brief 생성될 디스플레이의 X 좌표.
         */
        UInt32 x;

        /**
         * @brief 생성될 디스플레이의 Y 좌표.
         */
        UInt32 y;

        /**
         * @brief 생성될 디스플레이의 너비.
         */
        UInt32 width;

        /**
         * @brief 생성될 디스플레이의 높이.
         */
        UInt32 height;

        /**
         * @brief 생성될 디스플레이의 전체 화면 여부.
         */
        Bool isFullscreen;

        /**
         * @brief 생성될 디스플레이의 VSync 활성화 여부.
         */
        Bool isVsync;

        /**
         * @brief 생성될 디스플레이의 크기 조절 가능 여부.
         */
        Bool isResizable;

        /**
         * @brief 생설될 디스플레이의 테두리 여부.
         */
        Bool isBorderless;
    };
} // namespace NomadEngine::Runtime

#endif
