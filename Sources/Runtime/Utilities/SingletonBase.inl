namespace NomadEngine::Runtime
{
    template<typename TInstance>
    TInstance& SingletonBase<TInstance>::GetInstance()
    {
        static TInstance instance; // 정적 인스턴스 생성
        return instance;   // 인스턴스 반환
    }
} // NomadEngine::Rumtime
