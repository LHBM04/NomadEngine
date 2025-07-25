cmake_minimum_required(VERSION 3.20)
project(SandboxEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# mingw에서 GUI 모드로 실행되게 하기 위한 설정
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mwindows")

# 소스 파일
set(SOURCES
    Sources/Editor/Main.cpp
)

# 헤더 포함 경로
include_directories(
    "D:/vcpkg/installed/x64-mingw-static/include"
)

# 링커 경로
link_directories(
    "D:/vcpkg/installed/x64-mingw-static/lib"
)

# 실행 파일 생성
add_executable(SandboxEngine ${SOURCES})

# 라이브러리 링크
target_link_libraries(SandboxEngine
    SDL2
    glew32
    opengl32
    imgui
    gdi32
    winmm
    imm32
    setupapi
    dinput8
    dxguid
    ole32
    oleaut32
    uuid
    version
)
