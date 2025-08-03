#ifndef GUARD_IEDITORWINDOW_H
#define GUARD_IEDITORWINDOW_H

#include <memory>
#include <vector>
#include "../Platform/IPlatformWindow.h"
#include "Panels/IEditorPanel.h"

namespace NomadEngine::Editor
{
    /**
     * @brief 메인 에디터 윈도우 - 플랫폼별 메인 윈도우와 ImGui 패널들을 관리
     */
    class IEditorWindow
    {
    public:
        virtual ~IEditorWindow() = default;

        /**
         * @brief 에디터 윈도우를 초기화합니다.
         * @return 성공 시 true
         */
        virtual bool Initialize() = 0;

        /**
         * @brief 에디터를 실행합니다. (메인 루프)
         */
        virtual void Run() = 0;

        /**
         * @brief 에디터 윈도우를 해제합니다.
         */
        virtual void Finalize() = 0;

    protected:
        /**
         * @brief 에디터를 업데이트합니다.
         * @param deltaTime 델타 타임
         */
        virtual void Update(float deltaTime) = 0;

        /**
         * @brief 에디터를 렌더링합니다.
         */
        virtual void Render() = 0;

        /**
         * @brief 에디터 패널을 추가합니다.
         * @param panel 추가할 패널
         */
        virtual void AddPanel(EditorPanelPtr panel) = 0;

        /**
         * @brief 에디터 패널을 제거합니다.  
         * @param panelName 제거할 패널 이름
         */
        virtual void RemovePanel(const std::string& panelName) = 0;

    protected:
        std::unique_ptr<IPlatformWindow> mPlatformWindow;
        std::vector<EditorPanelPtr> mPanels;
    };
}

#endif
