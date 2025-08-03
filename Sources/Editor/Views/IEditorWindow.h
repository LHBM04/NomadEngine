#ifndef GUARD_IEDITORVIEW_H
#define GUARD_IEDITORVIEW_H

namespace NomadEngine::Editor
{
    class IEditorWindow
    {
    public:
        /**
         * @brief 소멸자.
         */
        virtual ~IEditorWindow() = default;

        /**
         * @brief 해당 윈도우를 초기화합니다.
         *
         * @return bool 성공하면 true, 실패하면 false를 반환합니다.
         */
        bool Initialize();

        /**
         * @brief 해당 윈도우를 실행합니다.
         */
        void Run();

        /**
         * @brief 해당 에디터 윈도우를 업데이트합니다.
         */
        void Update();

        /**
         * @brief 해당 에디터 윈도우를 렌더링합니다.
         */
        void Render();

        /**
         * @brief 해당 에디터 윈도우를 해제합니다.
         */
        void Finalize();

    };

}

#endif
