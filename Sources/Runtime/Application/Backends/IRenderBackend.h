#ifndef GUARD_IRENDERBACKED_H
#define GUARD_IRENDERBACKED_H

namespace NomadEngine::Runtime
{
    /**
     * @class IRenderBackend
     *
     * @brief 렌더링 백엔드의 인터페이스를 정의합니다.
     */
    class IRenderBackend
    {
    public:
        /**
         * @brief 생성자.
         */
        virtual ~IRenderBackend() = default;

        /**
         * @brief 렌더링 백엔드를 초기화합니다.
         *
         * @return bool 성공하면 true, 실패하면 false를 반환합니다.
         */
        virtual bool Initialize() = 0;

        virtual void BeginFrame() = 0;

        virtual void EndFrame() = 0;

        /**
         * @brief 렌더링 백엔드를 해제합니다.
         *
         * @return bool 성공하면 true, 실패하면 false를 반환합니다.
         */
        virtual bool Finalize() = 0;

    };
}

#endif
