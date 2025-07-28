#ifndef SINGLETONBASE_H
#define SINGLETONBASE_H


namespace NomadEngine::Editor
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
        static T& GetInstance();

    };
}

#endif //SINGLETONBASE_H

#include "../Editor/SingletonBase.inl"
