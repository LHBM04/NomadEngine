# NomadEngine CMake Configuration
# This file sets up the build configuration for the NomadEngine project.

cmake_minimum_required(VERSION 3.20)
project(NomadEngine)

# ================================================
# Basic Configuration
# ================================================
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set source file encoding to UTF-8 with BOM for Visual Studio
if(MSVC)
    add_compile_options("/utf-8")
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
    set(CMAKE_VS_INCLUDE_INSTALL_TO_DEFAULT_BUILD 1)
endif()

if(NOT CMAKE_SIZEOF_VOID_P EQUAL 8)
    message(FATAL_ERROR "This project requires 64-bit compilation.")
endif()

# ================================================
# Directory Structure
# ================================================
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

set(EXTERNAL_DIR ${CMAKE_SOURCE_DIR}/Sources/External)
set(EXTERNAL_INCLUDES ${EXTERNAL_DIR}/Includes)
set(EXTERNAL_LIBS_DEBUG ${EXTERNAL_DIR}/Libraries/Debug)
set(EXTERNAL_LIBS_RELEASE ${EXTERNAL_DIR}/Libraries/Release)
set(EXTERNAL_BINARIES_DEBUG ${EXTERNAL_DIR}/Binaries/Debug)
set(EXTERNAL_BINARIES_RELEASE ${EXTERNAL_DIR}/Binaries/Release)

# ================================================
# External Libraries
# ================================================

# DirectX
add_library(DirectX INTERFACE)
target_include_directories(DirectX SYSTEM INTERFACE
    ${EXTERNAL_INCLUDES}/directx
    ${EXTERNAL_INCLUDES}/directx-dxc
    ${EXTERNAL_INCLUDES}/directxtk12
)
target_link_libraries(DirectX INTERFACE d3d12 dxgi dxguid d3dcompiler)

# DirectXMath (header-only)
add_library(DirectXMath INTERFACE)
target_include_directories(DirectXMath SYSTEM INTERFACE ${EXTERNAL_INCLUDES})

# DirectXMesh
add_library(DirectXMesh INTERFACE)
target_include_directories(DirectXMesh SYSTEM INTERFACE ${EXTERNAL_INCLUDES})
target_link_libraries(DirectXMesh INTERFACE
    $<$<CONFIG:Debug>:DirectXMesh>
    $<$<CONFIG:Release>:DirectXMesh>
)

# DirectXTex
add_library(DirectXTex INTERFACE)
target_include_directories(DirectXTex SYSTEM INTERFACE ${EXTERNAL_INCLUDES})
target_link_libraries(DirectXTex INTERFACE
    $<$<CONFIG:Debug>:DirectXTex>
    $<$<CONFIG:Release>:DirectXTex>
)

# SDL3
add_library(SDL3 INTERFACE)
target_include_directories(SDL3 SYSTEM INTERFACE ${EXTERNAL_INCLUDES}/SDL3)
target_link_libraries(SDL3 INTERFACE
    $<$<CONFIG:Debug>:SDL3-static>
    $<$<CONFIG:Release>:SDL3-static>
    winmm setupapi cfgmgr32 version imm32
)

# ImGui
add_library(ImGui INTERFACE)
target_include_directories(ImGui SYSTEM INTERFACE ${EXTERNAL_INCLUDES})
target_link_libraries(ImGui INTERFACE
    $<$<CONFIG:Debug>:imguid>
    $<$<CONFIG:Release>:imgui>
)

# ================================================
# Source Files Collection
# ================================================
# 임시로 에디터만 빌드하도록 Runtime 소스 제외
# file(GLOB_RECURSE RUNTIME_SOURCES "Sources/Runtime/*.cpp" "Sources/Runtime/*.h")
file(GLOB_RECURSE EDITOR_SOURCES "Sources/Editor/*.cpp" "Sources/Editor/*.h")

# 필수 Runtime 헤더만 포함 
file(GLOB_RECURSE RUNTIME_HEADERS "Sources/Runtime/*.h")

# ================================================
# Runtime Library Target (임시 비활성화)
# ================================================
# add_library(NomadEngine_Runtime STATIC ${RUNTIME_SOURCES})
# target_include_directories(NomadEngine_Runtime
#     PUBLIC Sources/Runtime
#     PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
# )
# target_link_libraries(NomadEngine_Runtime PUBLIC DirectX DirectXMath DirectXMesh DirectXTex)

# ================================================
# Main Executable Target
# ================================================
add_executable(${PROJECT_NAME} ${EDITOR_SOURCES} ${RUNTIME_HEADERS})

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/Sources/Editor
    ${CMAKE_SOURCE_DIR}/Sources/Runtime
    ${EXTERNAL_INCLUDES}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    # NomadEngine_Runtime  # 임시 비활성화
    DirectX
    DirectXMath
    DirectXMesh
    DirectXTex
    SDL3
    ImGui
    opengl32  # Windows OpenGL 라이브러리 추가
    $<$<CONFIG:Debug>:glew32d>
    $<$<CONFIG:Release>:glew32>
    $<$<CONFIG:Debug>:freetyped>
    $<$<CONFIG:Release>:freetype>
    $<$<CONFIG:Debug>:libpng16d>
    $<$<CONFIG:Release>:libpng16>
    $<$<CONFIG:Debug>:zlibd>
    $<$<CONFIG:Release>:zlib>
    $<$<CONFIG:Debug>:brotlicommon>
    $<$<CONFIG:Release>:brotlicommon>
)

# ================================================
# Precompiled Headers Configuration (비활성화)
# ================================================
# if(CMAKE_VERSION VERSION_GREATER_EQUAL "3.16")
#     # Runtime PCH (임시 비활성화)
#     # target_precompile_headers(NomadEngine_Runtime PRIVATE Sources/Runtime/RuntimePCH.h)

#     # Editor PCH
#     target_precompile_headers(${PROJECT_NAME} PRIVATE Sources/Editor/EditorPCH.h)

#     message(STATUS "Precompiled headers enabled")
# else()
#     message(WARNING "CMake version ${CMAKE_VERSION} does not support PCH")
# endif()

message(STATUS "Precompiled headers disabled")

# ================================================
# Compiler Optimizations
# ================================================
if(MSVC)
    # target_compile_options(NomadEngine_Runtime PRIVATE /MP /W4 /permissive-)
    target_compile_options(${PROJECT_NAME} PRIVATE /MP /W4 /permissive-)

    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

    message(STATUS "MSVC optimizations enabled")
endif()

# ================================================
# Compiler Definitions
# ================================================
target_compile_definitions(${PROJECT_NAME} PRIVATE
    WIN32_LEAN_AND_MEAN
    NOMINMAX
    $<$<CONFIG:Debug>:_DEBUG>
    $<$<CONFIG:Release>:NDEBUG>
    $<$<PLATFORM_ID:Windows>:NOMAD_PLATFORM_WINDOWS=1>
)

# target_compile_definitions(NomadEngine_Runtime PRIVATE
#     WIN32_LEAN_AND_MEAN
#     NOMINMAX
#     $<$<CONFIG:Debug>:_DEBUG>
#     $<$<CONFIG:Release>:NDEBUG>
#     $<$<PLATFORM_ID:Windows>:NOMAD_PLATFORM_WINDOWS=1>
# )

# ================================================
# Library Directories
# ================================================
target_link_directories(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Debug>:${EXTERNAL_LIBS_DEBUG}>
    $<$<CONFIG:Release>:${EXTERNAL_LIBS_RELEASE}>
)

# ================================================
# Post-build DLL Copy Commands
# ================================================
if(WIN32)
    function(copy_dll_safely dll_name)
        set(DEBUG_DLL "${EXTERNAL_BINARIES_DEBUG}/${dll_name}")
        set(RELEASE_DLL "${EXTERNAL_BINARIES_RELEASE}/${dll_name}")
        
        if(EXISTS "${DEBUG_DLL}")
            add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${DEBUG_DLL}" "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
                COMMENT "Copying debug DLL: ${dll_name}"
            )
        endif()
        
        if(EXISTS "${RELEASE_DLL}")
            add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${RELEASE_DLL}" "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
                COMMENT "Copying release DLL: ${dll_name}"
            )
        endif()
    endfunction()

    copy_dll_safely("dxcompiler.dll")
    copy_dll_safely("dxil.dll")
    copy_dll_safely("D3D12Core.dll")
endif()
