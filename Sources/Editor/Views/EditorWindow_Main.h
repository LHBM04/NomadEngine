#ifndef GUARD_EDITORWINDOW_MAIN_H
#define GUARD_EDITORWINDOW_MAIN_H

#include "IEditorWindow.h"
#include <memory>
#include <chrono>

namespace NomadEngine::Editor
{
    /**
     * @brief 메인 에디터 윈도우 구현
     */
    class EditorWindow_Main : public IEditorWindow
    {
    public:
        EditorWindow_Main();
        virtual ~EditorWindow_Main();

        bool Initialize() override;
        void Run() override;
        void Finalize() override;

    protected:
        void Update(float deltaTime) override;
        void Render() override;
        void AddPanel(EditorPanelPtr panel) override;
        void RemovePanel(const std::string& panelName) override;

    private:
        bool InitializePlatformWindow();
        bool InitializeImGui();
        bool InitializePanels();
        void FinalizeImGui();

        void RenderMainMenuBar();
        void RenderDockSpace();

        bool mInitialized;
        bool mShouldClose;
        
        // 타이밍
        std::chrono::high_resolution_clock::time_point mLastFrameTime;
        float mDeltaTime;
    };
}

#endif