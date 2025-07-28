// SDL3 + OpenGL + ImGui + ImGuizmo 테스트 코드
// 이 코드는 SDL3, OpenGL, ImGui, ImGuizmo를 사용하여 간단한 테스트를 진행합니다.

#include <iostream>

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_sdlrenderer3.h>

// 매크로 정의
#define UNREFERENCED_PARAMETER(P) (P)   // 사용되지 않는 매개변수 경고 방지
#define TEXT(text) L## text              // 문자열을 와이드 문자열로 변환
#define PRINT_ERROR(text) std::wcerr << TEXT("Failed to create SDL window") << std::endl \
                                     << TEXT("Error: ") << SDL_GetError() << TEXT("\n") // 오류 메시지 출력
#define ISNULL(ptr) (ptr == nullptr)      // 포인터가 nullptr인지 확인

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
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // 키보드 네비게이션 활성화
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // 도킹 기능 활성화
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // 멀티 뷰포트 활성화 (선택사항)

    int width = 0, height = 0;
    SDL_GetWindowSize(gWindowContext, &width, &height);
    io.DisplaySize = ImVec2(static_cast<float>(width), static_cast<float>(height)); // 수동 지정 (임시방편)
    io.Fonts->AddFontFromFileTTF("C:/Windows/Fonts/malgun.ttf", 16.0f, nullptr,
                                 io.Fonts->GetGlyphRangesKorean());
    ImGui::StyleColorsDark();                                       // ImGui 스타일 설정

    // 뷰포트 활성화 시 스타일 조정
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    ImGui_ImplSDL3_InitForSDLRenderer(gWindowContext, gRendererContext);
    ImGui_ImplSDLRenderer3_Init(gRendererContext);

    Run();
    CleanUp();

    return 0;
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
            // ImGui에 이벤트 전달 (드래그, 마우스, 키보드 입력 등을 위해 필요)
            ImGui_ImplSDL3_ProcessEvent(&event);

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

        // 도킹 스페이스 생성 (전체 화면)
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

        // 도킹 스페이스 제출
        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }

        // 메뉴바
        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("파일"))
            {
                if (ImGui::MenuItem("새 파일", "Ctrl+N")) {}
                if (ImGui::MenuItem("열기", "Ctrl+O")) {}
                if (ImGui::MenuItem("저장", "Ctrl+S")) {}
                ImGui::Separator();
                if (ImGui::MenuItem("종료", "Alt+F4"))
                {
                    isRunning = false;
                }
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("창"))
            {
                ImGui::MenuItem("도킹 사용", nullptr, &dockspaceOpen);
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }

        ImGui::End();

        // 도킹 테스트용 창들

        // 1. 계층 구조 창
        ImGui::Begin("계층 구조");
        ImGui::Text("씬 오브젝트 목록");
        if (ImGui::TreeNode("메인 씬"))
        {
            if (ImGui::TreeNode("플레이어"))
            {
                ImGui::Text("- 메시 렌더러");
                ImGui::Text("- 콜라이더");
                ImGui::Text("- 플레이어 스크립트");
                ImGui::TreePop();
            }
            if (ImGui::TreeNode("적"))
            {
                ImGui::Text("- AI 컨트롤러");
                ImGui::Text("- 메시 렌더러");
                ImGui::TreePop();
            }
            if (ImGui::TreeNode("환경"))
            {
                ImGui::Text("- 지형");
                ImGui::Text("- 조명");
                ImGui::TreePop();
            }
            ImGui::TreePop();
        }
        ImGui::End();

        // 2. 인스펙터 창
        ImGui::Begin("인스펙터");
        ImGui::Text("선택된 오브젝트 속성");
        ImGui::Separator();

        static float position[3] = {0.0f, 0.0f, 0.0f};
        static float rotation[3] = {0.0f, 0.0f, 0.0f};
        static float scale[3] = {1.0f, 1.0f, 1.0f};

        if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
        {
            ImGui::DragFloat3("위치", position, 0.1f);
            ImGui::DragFloat3("회전", rotation, 1.0f);
            ImGui::DragFloat3("크기", scale, 0.1f);
        }

        if (ImGui::CollapsingHeader("렌더링"))
        {
            static bool castShadows = true;
            static bool receiveShadows = true;
            ImGui::Checkbox("그림자 생성", &castShadows);
            ImGui::Checkbox("그림자 받기", &receiveShadows);

            static float color[4] = {1.0f, 1.0f, 1.0f, 1.0f};
            ImGui::ColorEdit4("색상", color);
        }
        ImGui::End();

        // 3. 콘솔 창
        ImGui::Begin("콘솔");
        ImGui::Text("시스템 로그");
        ImGui::Separator();

        static ImGuiTextBuffer log_buffer;
        static bool auto_scroll = true;

        // 샘플 로그 메시지들
        static bool first_time = true;
        if (first_time)
        {
            log_buffer.append("[INFO] 엔진이 시작되었습니다.\n");
            log_buffer.append("[DEBUG] SDL3 초기화 완료\n");
            log_buffer.append("[INFO] ImGui 도킹 기능이 활성화되었습니다.\n");
            log_buffer.append("[WARNING] 일부 텍스처를 로드할 수 없습니다.\n");
            first_time = false;
        }

        ImGui::BeginChild("ScrollingRegion", ImVec2(0, -ImGui::GetFrameHeightWithSpacing()), false, ImGuiWindowFlags_HorizontalScrollbar);
        ImGui::TextUnformatted(log_buffer.begin(), log_buffer.end());

        if (auto_scroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
            ImGui::SetScrollHereY(1.0f);

        ImGui::EndChild();

        if (ImGui::Button("로그 지우기"))
            log_buffer.clear();
        ImGui::SameLine();
        ImGui::Checkbox("자동 스크롤", &auto_scroll);

        ImGui::End();

        // 4. 프로젝트 브라우저 창
        ImGui::Begin("프로젝트");
        ImGui::Text("애셋 브라우저");
        ImGui::Separator();

        // 폴더 구조 시뮬레이션
        if (ImGui::TreeNode("Assets"))
        {
            if (ImGui::TreeNode("Textures"))
            {
                ImGui::Selectable("player_texture.png");
                ImGui::Selectable("enemy_texture.png");
                ImGui::Selectable("ground_texture.jpg");
                ImGui::TreePop();
            }
            if (ImGui::TreeNode("Models"))
            {
                ImGui::Selectable("player.fbx");
                ImGui::Selectable("weapon.obj");
                ImGui::TreePop();
            }
            if (ImGui::TreeNode("Scripts"))
            {
                ImGui::Selectable("PlayerController.cs");
                ImGui::Selectable("EnemyAI.cs");
                ImGui::TreePop();
            }
            ImGui::TreePop();
        }
        ImGui::End();

        // 5. 게임 뷰 창
        ImGui::Begin("게임 뷰");
        ImGui::Text("게임 화면이 여기에 표시됩니다");

        // 게임 뷰 컨트롤
        if (ImGui::Button("플레이"))
        {
            // 게임 시작 로직
        }
        ImGui::SameLine();
        if (ImGui::Button("일시정지"))
        {
            // 게임 일시정지 로직
        }
        ImGui::SameLine();
        if (ImGui::Button("정지"))
        {
            // 게임 정지 로직
        }

        // 가상의 게임 화면 영역
        ImVec2 canvas_p0 = ImGui::GetCursorScreenPos();
        ImVec2 canvas_sz = ImGui::GetContentRegionAvail();
        if (canvas_sz.x < 50.0f) canvas_sz.x = 50.0f;
        if (canvas_sz.y < 50.0f) canvas_sz.y = 50.0f;
        ImVec2 canvas_p1 = ImVec2(canvas_p0.x + canvas_sz.x, canvas_p0.y + canvas_sz.y);

        ImDrawList* draw_list = ImGui::GetWindowDrawList();
        draw_list->AddRectFilled(canvas_p0, canvas_p1, IM_COL32(50, 50, 50, 255));
        draw_list->AddRect(canvas_p0, canvas_p1, IM_COL32(255, 255, 255, 255));
        draw_list->AddText(ImVec2(canvas_p0.x + 10, canvas_p0.y + 10), IM_COL32(255, 255, 255, 255), "게임 화면");

        ImGui::End();

        // 6. 성능 모니터 창
        ImGui::Begin("성능 모니터");
        ImGui::Text("애플리케이션 평균 %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

        // 메모리 사용량 (가상 데이터)
        static float memory_usage = 128.5f;
        ImGui::Text("메모리 사용량: %.1f MB", memory_usage);
        ImGui::ProgressBar(memory_usage / 1024.0f, ImVec2(0.0f, 0.0f));

        // GPU 사용량 (가상 데이터)
        static float gpu_usage = 0.6f;
        ImGui::Text("GPU 사용률: %.1f%%", gpu_usage * 100.0f);
        ImGui::ProgressBar(gpu_usage, ImVec2(0.0f, 0.0f));

        ImGui::End();

        ImGui::Render();

        SDL_SetRenderDrawColor(gRendererContext, 0, 0, 0, 255);
        SDL_RenderClear(gRendererContext);

        ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), gRendererContext);

        // 멀티 뷰포트 업데이트 및 렌더링 (선택사항)
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
        }

        SDL_RenderPresent(gRendererContext);
    }

    return true;
}

void _stdcall CleanUp()
{
    // ImGui 정리
    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();

    // SDL3 리소스 정리
    if (!ISNULL(gRendererContext))
    {
        SDL_DestroyRenderer(gRendererContext);
        gRendererContext = nullptr;
    }

    if (!ISNULL(gWindowContext))
    {
        SDL_DestroyWindow(gWindowContext);
        gWindowContext = nullptr;
    }

    SDL_Quit();
}
