#include "Application.h"
#include "Views/EditorWindow_Main.h"
#include <iostream>

namespace NomadEngine::Editor
{
    Application::Application() = default;
    Application::~Application() = default;

    bool Application::Initialize()
    {
        // 메인 에디터 윈도우 생성
        mMainWindow = std::make_unique<EditorWindow_Main>();
        
        if (!mMainWindow->Initialize())
        {
            std::cerr << "Failed to initialize main editor window!" << std::endl;
            return false;
        }

        std::cout << "NomadEngine Editor initialized successfully!" << std::endl;
        return true;
    }

    void Application::Run()
    {
        if (!mMainWindow)
        {
            std::cerr << "Main window not initialized!" << std::endl;
            return;
        }

        // EditorWindow_Main이 자체적으로 메인 루프를 관리
        mMainWindow->Run();
    }

    void Application::Shutdown()
    {
        if (mMainWindow)
        {
            mMainWindow->Finalize();
            mMainWindow.reset();
        }

        std::cout << "NomadEngine Editor shutdown complete." << std::endl;
    }

    void Application::Update()
    {
        // Legacy method - now handled by EditorWindow_Main
    }

    void Application::Render()
    {
        // Legacy method - now handled by EditorWindow_Main
    }

    void Application::Finalize()
    {
        Shutdown();
    }
}
