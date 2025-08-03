// NomadEngine Editor - 플랫폼별 메인 윈도우 + ImGui 서브 윈도우 시스템
// Windows: WinAPI, Linux: SDL3, 서브 윈도우: ImGui 패널들

#include <iostream>
#include <memory>

#include "Views/EditorWindow_Main.h"

int main(int argc, char** argv)
{
    // 명령줄 인수 사용하지 않음
    (void)argc;
    (void)argv;

    std::cout << "=== NomadEngine Editor Starting ===" << std::endl;

    // 메인 에디터 윈도우 생성
    auto editorWindow = std::make_unique<NomadEngine::Editor::EditorWindow_Main>();

    // 에디터 초기화
    if (!editorWindow->Initialize())
    {
        std::cerr << "Failed to initialize editor window" << std::endl;
        return -1;
    }

    std::cout << "Editor initialized successfully" << std::endl;

    // 에디터 실행 (메인 루프)
    editorWindow->Run();

    std::cout << "=== NomadEngine Editor Shutting Down ===" << std::endl;

    // 에디터 해제 (RAII로 자동 해제되지만 명시적으로 호출)
    editorWindow->Finalize();
    editorWindow.reset();

    std::cout << "Editor shutdown complete" << std::endl;
    return 0;
}
