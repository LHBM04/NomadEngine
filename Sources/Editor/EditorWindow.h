#ifndef GUARD_EDITORWINDOWBASE_H
#define GUARD_EDITORWINDOWBASE_H

#include <string>
#include <string_view>
#include <memory>

#include <SDL3/SDL.h>

namespace NomadEngine::Editor
{
    /**
     * @class EditorWindow
     *
     * @brief 에디터 윈도우의 기본 클래스를 정의합니다.
     */
    class EditorWindow
    {
    public:
        /**
         * @brief 생성자.
         *
         * @param width_ 윈도우의 너비 (기본값: 1280)
         * @param height_ 윈도우의 높이 (기본값: 720)
         */
        EditorWindow(
            int width_ = 1280,
            int height_ = 720);

        /**
         * @brief 소멸자.
         */
        ~EditorWindow();

        /**
         * @brief 에디터 윈도우를 초기화합니다.
         */
        void __stdcall SetWindowSize(int width, int height)
        {
            // TODO: 테스트하고 .cpp로 옮기기.
            mWindowWidth = width;
            mWindowHeight = height;
        }

    private:
        std::wstring mCaption;

        int mWindowWidth;

        int mWindowHeight;

        SDL_Window* mWindowContext;
    };

}

#endif // !GUARD_EDITORWINDOWBASE_H
