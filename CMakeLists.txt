# NomadEngine CMake Configuration
# This file sets up the build configuration for the NomadEngine project.

cmake_minimum_required(VERSION 3.20)
project(NomadEngine)

# ================================================
# Basic Configuration
# ================================================
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_CXX_STANDARD 20)
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
# Compiler-specific Settings
# ================================================
if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang" AND CMAKE_CXX_COMPILER_FRONTEND_VARIANT STREQUAL "MSVC")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m64 --target=x86_64-pc-windows-msvc")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m64 --target=x86_64-pc-windows-msvc")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /MACHINE:X64")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MDd")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD")
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
target_link_libraries(DirectX INTERFACE
    d3d12
    dxgi
    dxguid
    d3dcompiler
)

# Assimp  
add_library(Assimp INTERFACE)
target_include_directories(Assimp SYSTEM INTERFACE ${EXTERNAL_INCLUDES}/assimp)
# Note: Assimp library not available, commented out
# target_link_libraries(Assimp INTERFACE
#     $<$<CONFIG:Debug>:assimpd>
#     $<$<CONFIG:Release>:assimp>
# )

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

# FMT
add_library(FMT INTERFACE)
target_include_directories(FMT SYSTEM INTERFACE ${EXTERNAL_INCLUDES}/fmt)
# Note: FMT library not available, commented out  
# target_link_libraries(FMT INTERFACE
#     $<$<CONFIG:Debug>:fmtd>
#     $<$<CONFIG:Release>:fmt>
# )

# GLFW
add_library(GLFW INTERFACE)
target_include_directories(GLFW SYSTEM INTERFACE ${EXTERNAL_INCLUDES}/GLFW)
target_link_libraries(GLFW INTERFACE
    $<$<CONFIG:Debug>:glfw3>
    $<$<CONFIG:Release>:glfw3>
)

# GLM (header-only)
add_library(GLM INTERFACE)
target_include_directories(GLM SYSTEM INTERFACE ${EXTERNAL_INCLUDES}/glm)

# OpenAL
add_library(OpenAL INTERFACE)
target_include_directories(OpenAL SYSTEM INTERFACE ${EXTERNAL_INCLUDES}/AL)
# Note: OpenAL library not available, commented out
# target_link_libraries(OpenAL INTERFACE
#     $<$<CONFIG:Debug>:OpenAL32d>
#     $<$<CONFIG:Release>:OpenAL32>
# )

# Poly2Tri
add_library(Poly2Tri INTERFACE)
target_include_directories(Poly2Tri SYSTEM INTERFACE ${EXTERNAL_INCLUDES}/poly2tri)
# Note: Poly2Tri library not available, commented out
# target_link_libraries(Poly2Tri INTERFACE
#     $<$<CONFIG:Debug>:poly2trid>
#     $<$<CONFIG:Release>:poly2tri>
# )

# Polyclipping
add_library(Polyclipping INTERFACE)
target_include_directories(Polyclipping SYSTEM INTERFACE ${EXTERNAL_INCLUDES}/polyclipping)
# Note: Polyclipping library not available, commented out
# target_link_libraries(Polyclipping INTERFACE
#     $<$<CONFIG:Debug>:polyclippingd>
#     $<$<CONFIG:Release>:polyclipping>
# )

# PugiXML
add_library(PugiXML INTERFACE)
target_include_directories(PugiXML SYSTEM INTERFACE ${EXTERNAL_INCLUDES})
# Note: PugiXML library not available, commented out
# target_link_libraries(PugiXML INTERFACE
#     $<$<CONFIG:Debug>:pugixmld>
#     $<$<CONFIG:Release>:pugixml>
# )

# RapidJSON (header-only)
add_library(RapidJSON INTERFACE)
target_include_directories(RapidJSON SYSTEM INTERFACE ${EXTERNAL_INCLUDES}/rapidjson)

# STB (header-only)
add_library(STB INTERFACE)
target_include_directories(STB SYSTEM INTERFACE ${EXTERNAL_INCLUDES})

# UTF8-CPP (header-only)
add_library(UTF8CPP INTERFACE)
target_include_directories(UTF8CPP SYSTEM INTERFACE ${EXTERNAL_INCLUDES}/utf8cpp)

# KubaZip
add_library(KubaZip INTERFACE)
target_include_directories(KubaZip SYSTEM INTERFACE ${EXTERNAL_INCLUDES}/kubazip)
# Note: KubaZip library not available, commented out
# target_link_libraries(KubaZip INTERFACE
#     $<$<CONFIG:Debug>:kubazip>
#     $<$<CONFIG:Release>:kubazip>
# )

# MiniZip
add_library(MiniZip INTERFACE)
target_include_directories(MiniZip SYSTEM INTERFACE ${EXTERNAL_INCLUDES}/minizip)
# Note: MiniZip library not available, commented out
# target_link_libraries(MiniZip INTERFACE
#     $<$<CONFIG:Debug>:minizip>
#     $<$<CONFIG:Release>:minizip>
# )

# Draco
add_library(Draco INTERFACE)
target_include_directories(Draco SYSTEM INTERFACE ${EXTERNAL_INCLUDES}/draco)
# Note: Draco library not available, commented out
# target_link_libraries(Draco INTERFACE
#     $<$<CONFIG:Debug>:dracod>
#     $<$<CONFIG:Release>:draco>
# )

# SDL3
add_library(SDL3 INTERFACE)
target_include_directories(SDL3 SYSTEM INTERFACE ${EXTERNAL_INCLUDES}/SDL3)
target_link_libraries(SDL3 INTERFACE
    $<$<CONFIG:Debug>:SDL3-static>
    $<$<CONFIG:Release>:SDL3-static>
    # Required Windows system libraries for SDL3
    winmm
    setupapi
    cfgmgr32
    version
    imm32
)

# ImGui
add_library(ImGui INTERFACE)
target_include_directories(ImGui SYSTEM INTERFACE ${EXTERNAL_INCLUDES})
target_link_libraries(ImGui INTERFACE
    $<$<CONFIG:Debug>:imguid>
    $<$<CONFIG:Release>:imgui>
)

# ImGuizmo
add_library(ImGuizmo INTERFACE)
target_include_directories(ImGuizmo SYSTEM INTERFACE ${EXTERNAL_INCLUDES})
target_link_libraries(ImGuizmo INTERFACE
    $<$<CONFIG:Debug>:imguizmo>
    $<$<CONFIG:Release>:imguizmo>
)

# FreeType
add_library(FreeType INTERFACE)
target_include_directories(FreeType SYSTEM INTERFACE ${EXTERNAL_INCLUDES}/freetype)
target_link_libraries(FreeType INTERFACE
    $<$<CONFIG:Debug>:freetyped>
    $<$<CONFIG:Release>:freetype>
)

# PlutoSVG
add_library(PlutoSVG INTERFACE)
target_include_directories(PlutoSVG SYSTEM INTERFACE ${EXTERNAL_INCLUDES}/plutosvg)
target_link_libraries(PlutoSVG INTERFACE
    $<$<CONFIG:Debug>:plutosvg>
    $<$<CONFIG:Release>:plutosvg>
    $<$<CONFIG:Debug>:plutovg>
    $<$<CONFIG:Release>:plutovg>
)

# PNG
add_library(PNG INTERFACE)
target_include_directories(PNG SYSTEM INTERFACE ${EXTERNAL_INCLUDES}/libpng)
target_link_libraries(PNG INTERFACE
    $<$<CONFIG:Debug>:libpng16d>
    $<$<CONFIG:Release>:libpng16>
)

# Zlib
add_library(Zlib INTERFACE)
target_include_directories(Zlib SYSTEM INTERFACE ${EXTERNAL_INCLUDES}/zlib)
target_link_libraries(Zlib INTERFACE
    $<$<CONFIG:Debug>:zlibd>
    $<$<CONFIG:Release>:zlib>
)

# Brotli
add_library(Brotli INTERFACE)
target_include_directories(Brotli SYSTEM INTERFACE ${EXTERNAL_INCLUDES}/brotli)
target_link_libraries(Brotli INTERFACE
    $<$<CONFIG:Debug>:brotlidec>
    $<$<CONFIG:Debug>:brotlicommon>
    $<$<CONFIG:Release>:brotlidec>
    $<$<CONFIG:Release>:brotlicommon>
)

# bzip2
add_library(bzip2 INTERFACE)
target_include_directories(bzip2 SYSTEM INTERFACE ${EXTERNAL_INCLUDES}/bzip2)
target_link_libraries(bzip2 INTERFACE
    $<$<CONFIG:Debug>:bz2d>
    $<$<CONFIG:Release>:bz2>
)

# GameInput
add_library(GameInput INTERFACE)
target_link_libraries(GameInput INTERFACE gameinput)

# FMOD
add_library(FMOD INTERFACE)
target_include_directories(FMOD SYSTEM INTERFACE ${EXTERNAL_INCLUDES}/fmod)
# Note: FMOD library not available, commented out
# target_link_libraries(FMOD INTERFACE
#     $<$<CONFIG:Debug>:fmodL_vc>
#     $<$<CONFIG:Release>:fmod_vc>
#     $<$<CONFIG:Debug>:fmodstudioL_vc>
#     $<$<CONFIG:Release>:fmodstudio_vc>
# )

# ================================================
# Source Files
# ================================================
file(GLOB_RECURSE SOURCES
    "Sources/Editor/*.h"
    "Sources/Editor/*.cpp"
    "Sources/Runtime/*.h"
    "Sources/Runtime/*.cpp"
)

# ================================================
# Executable Target
# ================================================
add_executable(${PROJECT_NAME} ${SOURCES}
        Sources/Runtime/Display/PlatformWindowContext.h
        Sources/Editor/Views/IEditorWindow.h
        Sources/Editor/Views/EditorWindow_Main.cpp
        Sources/Editor/Views/EditorWindow_Main.h
        Sources/Editor/Platform/IPlatform.h
        Sources/Editor/Platform/Platform_Windows.cpp
        Sources/Editor/Platform/Platform_Windows.h
        Sources/Runtime/Rendering/RenderingServer_SDLRenderer.h
        Sources/Runtime/Rendering/RenderingServer_SDLRenderer.cpp
        Sources/Runtime/Rendering/RenderingServer_GDI.cpp
        Sources/Runtime/Rendering/RenderingServer_GDI.h)

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)

# ================================================
# Link External Libraries to Main Target
# ================================================
target_link_libraries(${PROJECT_NAME} PRIVATE
    DirectX
    DirectXMath
    DirectXMesh
    DirectXTex
    GLFW
    GLM
    SDL3
    ImGui
    ImGuizmo
    FreeType
    PlutoSVG
    PNG
    Zlib
    Brotli
    bzip2
    GameInput
    # Commented out libraries without available .lib files:
    # Assimp
    # FMT  
    # OpenAL
    # Poly2Tri
    # Polyclipping
    # PugiXML
    # KubaZip
    # MiniZip
    # Draco
    # FMOD
)

# ================================================
# Include Directories
# ================================================
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/Sources/Editor
    ${CMAKE_SOURCE_DIR}/Sources/Runtime
)

# Add External include directories to appear in Visual Studio UI
target_include_directories(${PROJECT_NAME} PRIVATE
    ${EXTERNAL_INCLUDES}
    ${EXTERNAL_INCLUDES}/directx
    ${EXTERNAL_INCLUDES}/directx-dxc
    ${EXTERNAL_INCLUDES}/directxtk12
    ${EXTERNAL_INCLUDES}/assimp
    ${EXTERNAL_INCLUDES}/fmt
    ${EXTERNAL_INCLUDES}/GLFW
    ${EXTERNAL_INCLUDES}/glm
    ${EXTERNAL_INCLUDES}/AL
    ${EXTERNAL_INCLUDES}/poly2tri
    ${EXTERNAL_INCLUDES}/polyclipping
    ${EXTERNAL_INCLUDES}/rapidjson
    ${EXTERNAL_INCLUDES}/utf8cpp
    ${EXTERNAL_INCLUDES}/kubazip
    ${EXTERNAL_INCLUDES}/minizip
    ${EXTERNAL_INCLUDES}/draco
    ${EXTERNAL_INCLUDES}/SDL3
    ${EXTERNAL_INCLUDES}/freetype
    ${EXTERNAL_INCLUDES}/plutosvg
    ${EXTERNAL_INCLUDES}/libpng
    ${EXTERNAL_INCLUDES}/zlib
    ${EXTERNAL_INCLUDES}/brotli
    ${EXTERNAL_INCLUDES}/bzip2
    ${EXTERNAL_INCLUDES}/fmod
)

# ================================================
# Library Directories  
# ================================================
target_link_directories(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Debug>:${EXTERNAL_LIBS_DEBUG}>
    $<$<CONFIG:Release>:${EXTERNAL_LIBS_RELEASE}>
)

# ================================================
# Additional Compiler Definitions
# ================================================
target_compile_definitions(${PROJECT_NAME} PRIVATE
    WIN32_LEAN_AND_MEAN
    NOMINMAX
    $<$<CONFIG:Debug>:_DEBUG>
    $<$<CONFIG:Release>:NDEBUG>
    # Platform definitions
    $<$<PLATFORM_ID:Windows>:NOMAD_PLATFORM_WINDOWS=1>
    $<$<PLATFORM_ID:Linux>:NOMAD_PLATFORM_LINUX=1>
    $<$<PLATFORM_ID:Darwin>:NOMAD_PLATFORM_MACOS=1>
)

# ================================================
# Visual Studio specific settings
# ================================================
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        /W4                     # Warning level 4
        /permissive-           # Disable non-conforming code
        /Zc:__cplusplus        # Enable correct __cplusplus macro
        /utf-8                 # Set source file encoding to UTF-8
        $<$<CONFIG:Debug>:/MDd>
        $<$<CONFIG:Release>:/MD>
    )

    # Set startup project in Visual Studio
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

    # Set working directory for debugging
    set_target_properties(${PROJECT_NAME} PROPERTIES
        VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
    )
    
    # Additional Visual Studio properties
    set_target_properties(${PROJECT_NAME} PROPERTIES
        VS_GLOBAL_UseMultiToolTask "true"
        VS_GLOBAL_EnforceProcessCountAcrossBuilds "true"
    )
endif()

# ================================================
# Post-build DLL Copy Commands (Simplified)
# ================================================
if(WIN32)
    # Function to safely copy DLL files
    function(copy_dll_safely dll_name)
        set(DEBUG_DLL "${EXTERNAL_BINARIES_DEBUG}/${dll_name}")
        set(RELEASE_DLL "${EXTERNAL_BINARIES_RELEASE}/${dll_name}")
        
        # Copy debug DLL for debug builds
        if(EXISTS "${DEBUG_DLL}")
            add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${DEBUG_DLL}"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
                COMMENT "Copying debug DLL: ${dll_name}"
            )
        endif()
        
        # Copy release DLL for release builds  
        if(EXISTS "${RELEASE_DLL}")
            add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${RELEASE_DLL}"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
                COMMENT "Copying release DLL: ${dll_name}"
            )
        endif()
    endfunction()

    # Copy specific DLLs that are available
    copy_dll_safely("dxcompiler.dll")
    copy_dll_safely("dxil.dll")
    copy_dll_safely("D3D12Core.dll")
    
    # Optional DLLs (only copy if they exist)
    copy_dll_safely("fmodL.dll")
    copy_dll_safely("fmod.dll")
    copy_dll_safely("fmodstudioL.dll")
    copy_dll_safely("fmodstudio.dll")
    copy_dll_safely("OpenAL32.dll")
    copy_dll_safely("assimp-vc143-mtd.dll")
    copy_dll_safely("assimp-vc143-mt.dll")
endif()

# ================================================
# Testing (Google Test)
# ================================================
enable_testing()

add_library(GTest INTERFACE)
target_include_directories(GTest SYSTEM INTERFACE
    ${EXTERNAL_INCLUDES}/gtest
    ${EXTERNAL_INCLUDES}/gmock
)
target_link_libraries(GTest INTERFACE
    $<$<CONFIG:Debug>:gtestd>
    $<$<CONFIG:Debug>:gmockd>
    $<$<CONFIG:Release>:gtest>
    $<$<CONFIG:Release>:gmock>
)

add_executable(NomadEngine_Tests
    Tests/DisplayServer/DisplayServerTests.cpp
)

target_link_libraries(NomadEngine_Tests PRIVATE ${PROJECT_NAME} GTest)

include(GoogleTest)
gtest_discover_tests(NomadEngine_Tests)


