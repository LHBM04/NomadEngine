#ifndef GUARD_IPLATFORM_H
#define GUARD_IPLATFORM_H

namespace NomadEngine::Editor
{
    /**
     * @class IPlatform
     *
     * @brief 플랫폼 인터페이스를 정의합니다.
     */
    class IPlatform
    {
    public:
        /**
         * @brief 생성자.
         */
        virtual ~IPlatform() = default;

        /**
         * @brief 플랫폼을 초기화합니다.
         *
         * @return bool 성공하면 true, 실패하면 false를 반환합니다.
         */
        virtual bool Initialize() = 0;

        /**
         * @brief 플랫폼을 실행합니다.
         */
        virtual void Run() = 0;

        /**
         * @brief 플랫폼을 종료합니다.
         */
        virtual void Finalize() = 0;
    };

}

#endif
