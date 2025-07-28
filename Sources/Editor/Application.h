#ifndef GUARD_APPLICATION_H
#define GUARD_APPLICATION_H

#include "../Editor/SingletonBase.h"
#include "../Editor/EditorWindow.h"

namespace NomadEngine::Editor
{
    /**
     * @class Application
     *
     * @brief 에디터 어플리케이션의 동작을 정의합니다.
     */
    class Application
        : public SingletonBase<Application>
    {
    public:
        /**
         * @brief 생성자.
         */
        Application();
        /**
         * @brief 소멸자.
         */
        virtual ~Application() override;

        /**
         * @brief 에디터 어플리케이션을 초기화합니다.
         *
         * @return 성공하면 true, 실패하면 false를 반환합니다.
         */
        bool Initialize();

        /**
         * @brief 에디터 어플리케이션을 실행합니다.
         */
        void Run();

        /**
         * @brief 에디터 어플리케이션을 업데이트합니다.
         */
        void Update();

        /**
         * @brief 에디터 어플리케이션을 렌더합니다.
         */
        void Render();

        /**
         * @brief 에디터 어플리케이션을 종료합니다.
         */
        void Release();

    private:
        EditorWindow mWindow;

    };

}

#endif // !GUARD_APPLICATION_H
