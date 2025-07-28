// SDL3 + OpenGL + ImGui + ImGuizmo 테스트 코드
// 이 코드는 SDL3, OpenGL, ImGui, ImGuizmo를 사용하여 간단한 테스트를 진행합니다.

#include <iostream>

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_sdlrenderer3.h>
#include <ImGuizmo.h>

// 매크로 정의
#define UNREFERENCED_PARAMETER(P) (P)   // 사용되지 않는 매개변수 경고 방지
#define TEXT(text) L## text              // 문자열을 와이드 문자열로 변환
#define PRINT_ERROR(text) std::wcerr << TEXT("Failed to create SDL window") << std::endl \
                                     << TEXT("Error: ") << SDL_GetError() << TEXT("\n") // 오류 메시지 출력
#define ISNULL(ptr) ptr == nullptr      // 포인터가 nullptr인지 확인

/**
 * @brief SDL3 윈도우 핸들러.
 */
static SDL_Window* gWindowContext;

/**
 * @brief SDL3 렌더러 핸들러.
 */
static SDL_Renderer* gRendererContext;

/**
 * @brief SDL3 윈도우 핸들러 초기화.
 */
bool _stdcall InitializeWindow();

/**
 * @brief SDL3 렌더러 핸들러 초기화.
 */
bool _stdcall InitializeRenderer();

/**
 * @brief SDL3 및 OpenGL 렌더링 루프.
 */
bool _stdcall Run();

/**
 * @brief SDL3 및 OpenGL 리소스 정리.
 */
void _stdcall CleanUp();

int _stdcall main(int argc_, char** argv_)
{
    UNREFERENCED_PARAMETER(argc_);
    UNREFERENCED_PARAMETER(argv_);

    // SDL 초기화
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        PRINT_ERROR(TEXT("Failed to initialize SDL3"));
        return -1;
    }

    // GL 어트리뷰트 설정.
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    if (!InitializeWindow() ||
        !InitializeRenderer())
    {
        // SDL3 윈도우 또는 렌더러 초기화 실패
        CleanUp();
        return -1;
    }

    IMGUI_CHECKVERSION();                                           // ImGui 버전 확인

    // ImGui 초기화
    ImGui::CreateContext();                                         // ImGui 컨텍스트 생성

    ImGuiIO& io = ImGui::GetIO();                                   // ImGui IO 객체 가져오기

    int width = 0, height = 0;
    SDL_GetWindowSize(gWindowContext, &width, &height);
    io.DisplaySize = ImVec2(static_cast<float>(width), static_cast<float>(height)); // 수동 지정 (임시방편)
    io.Fonts->AddFontFromFileTTF("C:/Windows/Fonts/malgun.ttf", 16.0f, nullptr,
                                 io.Fonts->GetGlyphRangesKorean());
    ImGui::StyleColorsDark();                                       // ImGui 스타일 설정

    ImGui_ImplSDL3_InitForSDLRenderer(gWindowContext, gRendererContext);
    ImGui_ImplSDLRenderer3_Init(gRendererContext);

    if (Run())
    {
        CleanUp();
        return 0;
    }

    return -1;
}

bool _stdcall InitializeWindow()
{
    // SDL3 윈도우 핸들러 초기화
    gWindowContext = SDL_CreateWindow(
        "Nomad Engine",
        1280, 720,
        SDL_WINDOW_EXTERNAL | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    if (ISNULL(gWindowContext))
    {
        PRINT_ERROR(TEXT("Failed to create SDL window"));
        // std::wcerr << TEXT("Failed to create SDL window\n");
        // std::wcerr << TEXT("Error: ") << SDL_GetError() << TEXT("\n");
        return false;
    }

    return true;
}

bool _stdcall InitializeRenderer()
{
    // SDL3 렌더러 핸들러 초기화
    gRendererContext = SDL_CreateRenderer(
        gWindowContext,
        nullptr);

    if (ISNULL(gRendererContext))
    {
        PRINT_ERROR(TEXT("Failed to create SDL Renderer"));
        // std::wcerr << TEXT("Failed to create SDL Renderer\n");
        // std::wcerr << TEXT("Error: ") << SDL_GetError() << TEXT("\n");
        return false;
    }

    return true;
}

bool _stdcall Run()
{
    bool isRunning = true;

    while (isRunning)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_EVENT_WINDOW_RESIZED:
                {
                    int width = event.window.data1;
                    int height = event.window.data2;
                    SDL_SetWindowSize(gWindowContext, width, height);
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

        ImGui_ImplSDLRenderer3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Hello");
        ImGui::Text("안녕하세요");
        ImGui::End();

        ImGui::Render();

        SDL_SetRenderDrawColor(gRendererContext, 0, 0, 0, 255);
        SDL_RenderClear(gRendererContext);

        ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), gRendererContext);
        SDL_RenderPresent(gRendererContext);
    }

    return true;
}

void _stdcall CleanUp()
{
    SDL_DestroyRenderer(gRendererContext);
    SDL_DestroyWindow(gWindowContext);
    SDL_Quit();
}
