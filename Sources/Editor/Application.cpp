#include "../Editor/Application.h"

#include <iostream>

#include <SDL3/SDL.h>

#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_sdlrenderer3.h>

namespace NomadEngine::Editor
{
     Application::Application()
     = default;

    Application::~Application()
     = default;

    bool Application::Initialize()
    {
        IMGUI_CHECKVERSION();

        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();

        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

        ImGui::StyleColorsClassic();

        ImGuiStyle& style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        return true;
    }

    void Application::Run()
    {
        std::cout << "Running..." << std::endl;

        bool isRunning = true;
        while (isRunning) // 무한 루프 예시
        {
            SDL_Event event;
            while (SDL_PollEvent(&event))
            {
                ImGui_ImplSDL3_ProcessEvent(&event);

                switch (event.type)
                {
                    case SDL_EVENT_WINDOW_RESIZED:
                    {
                        int width = event.window.data1;
                        int height = event.window.data2;
                        mWindow.SetWindowSize(width, height);
                        break;
                    }
                    case SDL_EVENT_QUIT:
                    {
                        isRunning = false;
                        break;
                    }
                    default:
                    {
                        break;
                    }
                }
            }

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
