#include "../Editor/Application.h"

#include <iostream>

#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui.h>
#include <imgui_impl_sdlrenderer3.h>

namespace NomadEngine::Editor
{
     Application::Application()
     {

     }

    Application::~Application()
     {

     }


    bool Application::Initialize()
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();

         io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
         io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
         io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
         io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    }

    void Application::Run()
    {
        std::cout << "Running..." << std::endl;

        while (true) // 무한 루프 예시
        {
            Update();
            Render();
        }
    }

    void Application::Update()
    {
        std::cout << "Updating..." << std::endl;

        // 여기에 업데이트 로직을 추가합니다.
    }

    void Application::Render()
    {
        std::cout << "Rendering..." << std::endl;

        // 여기에 렌더링 로직을 추가합니다.
    }

    void Application::Release()
    {
        std::cout << "Releasing resources..." << std::endl;

        // 여기에 리소스 해제 로직을 추가합니다.
    }

}
