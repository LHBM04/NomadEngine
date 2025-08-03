#ifndef GUARD_SINGLETONBASE_H
#define GUARD_SINGLETONBASE_H

namespace NomadEngine::Runtime
{
    template <typename T>
    class SingletonBase
    {
    public:
        /**
         * @brief 생성자.
         */
        SingletonBase() = default;

        /**
         * @brief 소멸자.
         */
        virtual ~SingletonBase() = default;

        /**
         * @brief 복사 생성자. (삭제.)
         */
        SingletonBase(const SingletonBase&) = delete;

        /**
         * @brief 대입 연산자. (삭제.)
         */
        SingletonBase& operator=(const SingletonBase&) = delete;

        /**
         * @brief 생성된 정적 인스턴스를 가져옵니다.
         *
         * @return T& - 정적 인스턴스에 대한 참조
         */
        static T& GetInstance()
        {
            static T instance; // 정적 인스턴스 생성
            return instance;   // 인스턴스 반환
        }

    };
}

#endif
