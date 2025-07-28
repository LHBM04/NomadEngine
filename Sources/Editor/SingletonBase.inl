#ifndef GUARD_SINGLETONBASE_H
#define GUARD_SINGLETONBASE_H

namespace NomadEngine::Editor
{
    template<typename T>
    inline T& Editor::SingletonBase<T>::GetInstance()
    {
        static T instance; // 정적 인스턴스 생성
        return instance;   // 인스턴스 반환
    }
}

#endif
