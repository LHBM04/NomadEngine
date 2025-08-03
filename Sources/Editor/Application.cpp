#include "Application.h"

#include <iostream>

#include <SDL3/SDL.h>

#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_sdlrenderer3.h>

#include "../Runtime/Display/DisplayServer_SDL.h"
#include "../Runtime/Rendering/RenderingServer_SDLRenderer.h"
#include "../Runtime/Application/Platform/PlatformWindowContext.h"

namespace NomadEngine::Editor
{
    Application::Application() = default;
    Application::~Application() = default;

    bool Application::Initialize()
    {
        // 1. Create Display Server
        mDisplayServer = std::make_unique<Runtime::DisplayServer_SDL>();
        Runtime::PlatformWindowContext context;
        context.title = "NomadEngine Editor";
        context.width = 1280;
        context.height = 720;
        if (!mDisplayServer->Initialize(context))
        {
            return false;
        }

        // 2. Create Rendering Server
        mRenderingServer = std::make_unique<Runtime::RenderingServer_SDLRenderer>();
        if (!mRenderingServer->Initialize(mDisplayServer->GetWindowHandle()))
        {
            return false;
        }

        // 3. Initialize GUI
        if (!mInitializeGUI())
        {
            return false;
        }

        return true;
    }

    void Application::Run()
    {
        bool isRunning = true;
        while (isRunning)
        {
            SDL_Event event;
            while (SDL_PollEvent(&event))
            {
                ImGui_ImplSDL3_ProcessEvent(&event);
                if (event.type == SDL_EVENT_QUIT)
                    isRunning = false;
            }

            Update();
            Render();
        }
    }

    void Application::Update()
    {
        // Update logic here
    }

    void Application::Render()
    {
        mRenderingServer->BeginFrame();

        // ImGui Rendering
        ImGui_ImplSDLRenderer3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();
        ImGui::ShowDemoWindow(); // Example
        ImGui::Render();
        ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData());

        mRenderingServer->Present();
        mRenderingServer->EndFrame();
    }

    void Application::Finalize()
    {
        ImGui_ImplSDLRenderer3_Shutdown();
        ImGui_ImplSDL3_Shutdown();
        ImGui::DestroyContext();

        mRenderingServer->Finalize();
        mDisplayServer->Finalize();
    }

    bool Application::mInitializeGUI()
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

        ImGui::StyleColorsDark();

        auto sdl_renderer = static_cast<Runtime::RenderingServer_SDLRenderer*>(mRenderingServer.get());

        if (!ImGui_ImplSDL3_InitForSDLRenderer((SDL_Window*)mDisplayServer->GetWindowHandle(), sdl_renderer->GetRenderer()))
        {
            return false;
        }
        if (!ImGui_ImplSDLRenderer3_Init(sdl_renderer->GetRenderer()))
        {
            return false;
        }

        return true;
    }

}  // namespace NomadEngine::Editor