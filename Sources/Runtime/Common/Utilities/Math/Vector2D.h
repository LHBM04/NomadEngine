#ifndef GUARD_VECTOR2D_H
#define GUARD_VECTOR2D_H

namespace NomadEngine::Runtime
{
    /**
     * @struct Vector2D
     *
     * @brief 2차원 벡터를 정의합니다.
     */
    struct Vector2D
    {
        float x; ///< X 좌표
        float y; ///< Y 좌표

        /**
         * @brief 생성자.
         *
         * @param x_ X 좌표
         * @param y_ Y 좌표
         */
        explicit Vector2D(
            const float x_ = 0.0f,
            const float y_ = 0.0f)
            : x(x_)
            , y(y_)
        {

        }

    };

    struct Vector2DInt
    {
        int x;
        int y;

        /**
        * @brief 생성자.
        *
        * @param x_ X 좌표
        * @param y_ Y 좌표
        */
        explicit Vector2D(
            const int x_ = 0,
            const int y_ = 0)
            : x(x_)
            , y(y_)
        {

        }

    };

}

#endif

