#ifndef GUARD_IDISPLAYSERVER_H
#define GUARD_IDISPLAYSERVER_H

namespace NomadEngine::Runtime
{
    class IDisplayServer
    {
    public:
        /**
         * @brief 소멸자.
         */
        virtual ~IDisplayServer() = default;

     /**
         * @brief 디스플레이 서버를 초기화합니다.
         *
         * @param descriptor_ 디스플레이 서버의 설정 기술.
         *
         * @return bool 성공 여부.
         */
        virtual bool Initialize(const DisplayServerDescriptor& descriptor_) = 0;

        /**
         * @brief 디스플레이 서버를 시작합니다.
         *
         * @return bool 성공 여부.
         */
        virtual bool Finalize() = 0;
    };
}

#endif // !GUARD_IDISPLAYSERVER_H
