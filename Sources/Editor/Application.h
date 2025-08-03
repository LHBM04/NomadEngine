#pragma once

#include <memory>
#include "SingletonBase.h"

namespace NomadEngine::Editor
{
    class EditorWindow_Main;

    /**
     * @class Application
     *
     * @brief 에디터 어플리케이션의 동작을 정의합니다.
     */
    class Application : public SingletonBase<Application>
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
         * @brief 에디터 어플리케이션을 업데이트합니다. (Legacy)
         */
        void Update();

        /**
         * @brief 에디터 어플리케이션을 렌더합니다. (Legacy)
         */
        void Render();

        /**
         * @brief 에디터 어플리케이션을 종료합니다.
         */
        void Shutdown();

        /**
         * @brief 에디터 어플리케이션을 종료합니다. (Legacy)
         */
        void Finalize();

    private:
        std::unique_ptr<EditorWindow_Main> mMainWindow;
        bool mIsRunning = true;
    };
}
