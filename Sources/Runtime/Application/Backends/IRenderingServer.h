#ifndef GUARD_IRENDERBACKED_H
#define GUARD_IRENDERBACKED_H

namespace NomadEngine::Runtime
{
    /**
     * @class IRenderingServer
     *
     * @brief 렌더링 서버를 정의합니다.
     */
    class IRenderingServer
    {
    public:
        /**
         * @brief 소멸자.
         */
        virtual ~IRenderingServer() = default;

        /**
         * @brief 렌더링 백엔드를 초기화합니다.
         *
         * @return bool 성공하면 true, 실패하면 false를 반환합니다.
         */
        virtual bool Initialize() = 0;

        /**
         * @brief 프레임 시작.
         */
        virtual void BeginFrame() = 0;

        /**
         * @brief 프레임 렌더.
         */
        virtual void Present() = 0;

        /**
         * @brief 프레임 종료.
         */
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
