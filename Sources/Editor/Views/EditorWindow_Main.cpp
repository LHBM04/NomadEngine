//
// Created by bum26 on 25. 8. 1.
//

#include "EditorWindow_Main.h"

// OpenGL
#include <GL/glew.h>

// 플랫폼별 윈도우 구현
#include "../../Runtime/Common/Defines.h"
#include "../Platform/SDLWindow.h"  // 임시로 모든 플랫폼에서 SDL 사용

// ImGui
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_sdl3.h>  // 임시로 모든 플랫폼에서 SDL3 사용

// 에디터 패널들
#include "Panels/SceneViewPanel.h"
#include "Panels/HierarchyPanel.h"
#include "Panels/InspectorPanel.h"

#include <iostream>
#include <thread>
#include <algorithm>

namespace NomadEngine::Editor
{
    EditorWindow_Main::EditorWindow_Main()
        : mInitialized(false)
        , mShouldClose(false)
        , mDeltaTime(0.0f)
    {
        mLastFrameTime = std::chrono::high_resolution_clock::now();
    }

    EditorWindow_Main::~EditorWindow_Main()
    {
        Finalize();
    }

    bool EditorWindow_Main::Initialize()
    {
        if (mInitialized)
            return true;

        std::cout << "Initializing Main Editor Window..." << std::endl;

        // 1. 플랫폼 윈도우 초기화
        if (!InitializePlatformWindow())
        {
            std::cerr << "Failed to initialize platform window" << std::endl;
            return false;
        }

        // 2. ImGui 초기화
        if (!InitializeImGui())
        {
            std::cerr << "Failed to initialize ImGui" << std::endl;
            return false;
        }

        // 3. 에디터 패널들 초기화
        if (!InitializePanels())
        {
            std::cerr << "Failed to initialize editor panels" << std::endl;
            return false;
        }

        mInitialized = true;
        std::cout << "Main Editor Window initialized successfully" << std::endl;
        return true;
    }

    void EditorWindow_Main::Run()
    {
        if (!mInitialized)
        {
            std::cerr << "Editor window not initialized" << std::endl;
            return;
        }

        std::cout << "Starting main editor loop..." << std::endl;

        // 메인 루프
        while (!mShouldClose)
        {
            // 델타 타임 계산
            auto currentTime = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(currentTime - mLastFrameTime);
            mDeltaTime = duration.count() / 1000000.0f;
            mLastFrameTime = currentTime;

            // 플랫폼 이벤트 처리
            if (!mPlatformWindow->ProcessEvents())
            {
                mShouldClose = true;
                break;
            }

            // 윈도우가 최소화된 경우 대기
            if (mPlatformWindow->IsMinimized())
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
                continue;
            }

            // 업데이트
            Update(mDeltaTime);

            // 렌더링
            Render();
        }
    }

    void EditorWindow_Main::Finalize()
    {
        if (!mInitialized)
            return;

        std::cout << "Finalizing Main Editor Window..." << std::endl;

        // 패널들 해제
        for (auto& panel : mPanels)
        {
            if (panel)
                panel->Finalize();
        }
        mPanels.clear();

        // ImGui 해제
        FinalizeImGui();

        // 플랫폼 윈도우 해제
        if (mPlatformWindow)
        {
            mPlatformWindow->Finalize();
            mPlatformWindow.reset();
        }

        mInitialized = false;
    }

    void EditorWindow_Main::Update(float deltaTime)
    {
        // 패널들 업데이트
        for (auto& panel : mPanels)
        {
            if (panel)
                panel->Update(deltaTime);
        }
    }

    void EditorWindow_Main::Render()
    {
        // 프레임 시작
        mPlatformWindow->BeginFrame();

        // ImGui 프레임 시작
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL3_NewFrame();  // 임시로 모든 플랫폼에서 SDL3 사용
        ImGui::NewFrame();

        // 도킹 공간 설정
        RenderDockSpace();

        // 메인 메뉴바
        RenderMainMenuBar();

        // 패널들 렌더링
        for (auto& panel : mPanels)
        {
            if (panel)
                panel->Render();
        }

        // ImGui 렌더링
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // 프레임 종료
        mPlatformWindow->EndFrame();
    }

    void EditorWindow_Main::AddPanel(EditorPanelPtr panel)
    {
        if (panel)
        {
            panel->Initialize();
            mPanels.push_back(panel);
        }
    }

    void EditorWindow_Main::RemovePanel(const std::string& panelName)
    {
        auto it = std::remove_if(mPanels.begin(), mPanels.end(),
            [&panelName](const EditorPanelPtr& panel)
            {
                if (panel && panel->GetName() == panelName)
                {
                    panel->Finalize();
                    return true;
                }
                return false;
            });
        mPanels.erase(it, mPanels.end());
    }

    bool EditorWindow_Main::InitializePlatformWindow()
    {
        WindowDescriptor desc;
        desc.title = "NomadEngine Editor";
        desc.width = 1600;
        desc.height = 900;
        desc.resizable = true;

        // 임시로 모든 플랫폼에서 SDL3 사용 (ImGui backend 문제 회피)
        mPlatformWindow = std::make_unique<SDLWindow>();

        return mPlatformWindow->Initialize(desc);
    }

    bool EditorWindow_Main::InitializeImGui()
    {
        // ImGui 컨텍스트 생성
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        
        // 도킹과 뷰포트 활성화
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

        // GLEW 초기화 (OpenGL 확장 함수 로드)
        if (glewInit() != GLEW_OK)
        {
            std::cerr << "Failed to initialize GLEW" << std::endl;
            return false;
        }

        // 스타일 설정
        ImGui::StyleColorsDark();

        // 멀티 뷰포트 사용 시 스타일 조정
        ImGuiStyle& style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        // 플랫폼/렌더러 바인딩 (임시로 모든 플랫폼에서 SDL3 사용)
        if (!ImGui_ImplSDL3_InitForOpenGL(static_cast<SDL_Window*>(mPlatformWindow->GetNativeHandle()), nullptr))
        {
            std::cerr << "Failed to initialize ImGui SDL3 implementation" << std::endl;
            return false;
        }

        if (!ImGui_ImplOpenGL3_Init("#version 450"))
        {
            std::cerr << "Failed to initialize ImGui OpenGL3 implementation" << std::endl;
            return false;
        }

        return true;
    }

    bool EditorWindow_Main::InitializePanels()
    {
        // 기본 에디터 패널들 생성
        AddPanel(std::make_shared<SceneViewPanel>());
        AddPanel(std::make_shared<HierarchyPanel>());
        AddPanel(std::make_shared<InspectorPanel>());

        return true;
    }

    void EditorWindow_Main::FinalizeImGui()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplSDL3_Shutdown();  // 임시로 모든 플랫폼에서 SDL3 사용
        ImGui::DestroyContext();
    }

    void EditorWindow_Main::RenderMainMenuBar()
    {
        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("New Scene", "Ctrl+N")) { /* TODO */ }
                if (ImGui::MenuItem("Open Scene", "Ctrl+O")) { /* TODO */ }
                if (ImGui::MenuItem("Save Scene", "Ctrl+S")) { /* TODO */ }
                ImGui::Separator();
                if (ImGui::MenuItem("Build Project", "Ctrl+B")) { /* TODO */ }
                ImGui::Separator();
                if (ImGui::MenuItem("Exit", "Alt+F4")) { mShouldClose = true; }
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Edit"))
            {
                if (ImGui::MenuItem("Undo", "Ctrl+Z")) { /* TODO */ }
                if (ImGui::MenuItem("Redo", "Ctrl+Y")) { /* TODO */ }
                ImGui::Separator();
                if (ImGui::MenuItem("Cut", "Ctrl+X")) { /* TODO */ }
                if (ImGui::MenuItem("Copy", "Ctrl+C")) { /* TODO */ }
                if (ImGui::MenuItem("Paste", "Ctrl+V")) { /* TODO */ }
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Window"))
            {
                for (auto& panel : mPanels)
                {
                    if (panel)
                    {
                        bool visible = panel->IsVisible();
                        if (ImGui::MenuItem(panel->GetName().c_str(), nullptr, &visible))
                        {
                            panel->SetVisible(visible);
                        }
                    }
                }
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Help"))
            {
                if (ImGui::MenuItem("About")) { /* TODO: About 다이얼로그 */ }
                ImGui::EndMenu();
            }

            ImGui::EndMainMenuBar();
        }
    }

    void EditorWindow_Main::RenderDockSpace()
    {
        static bool dockspaceOpen = true;
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
            window_flags |= ImGuiWindowFlags_NoBackground;

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
        ImGui::PopStyleVar();
        ImGui::PopStyleVar(2);

        // DockSpace
        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }

        ImGui::End();
    }
}
