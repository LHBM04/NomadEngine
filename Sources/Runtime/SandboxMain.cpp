#include "Runtime/Common/SandboxHeader.h"
#include "Runtime/Common/SandboxTypes.h"

extern "C" int __argc;
extern "C" char** __argv;

INT APIENTRY wWinMain(
    _In_ HINSTANCE,
    _In_opt_ HINSTANCE,
    _In_ LPWSTR,
    _In_ INT
)
{
    Sandbox::FVOID Test = nullptr;

	// OpenGL 라이브러리 링킹 테스트.
    glutInit(&__argc, __argv);
    glfwInit();

    // Assimp 라이브러리 링킹 테스트.
    Assimp::Importer importer;

	// FMOD 라이브러리 링킹 테스트.
    FMOD::System* fmodSystem = nullptr;
    FMOD::System_Create(&fmodSystem);

    return MessageBox(
        nullptr,
        TEXT("Hello, World!"),
        TEXT("Sandbox Engine"),
        0
    );
}
