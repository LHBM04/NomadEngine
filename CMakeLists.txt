# NomadEngine CMake Configuration
# This file sets up the build configuration for the NomadEngine project.

cmake_minimum_required(VERSION 3.20)
project(NomadEngine)

# ================================================
# Basic Configuration
# ================================================
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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

# SDL3
add_library(SDL3 INTERFACE)
target_include_directories(SDL3 SYSTEM INTERFACE ${EXTERNAL_INCLUDES}/SDL3)
target_link_libraries(SDL3 INTERFACE
    $<$<CONFIG:Debug>:${EXTERNAL_LIBS_DEBUG}/SDL3-static.lib>
    $<$<CONFIG:Release>:${EXTERNAL_LIBS_RELEASE}/SDL3-static.lib>
)

# ImGui
add_library(ImGui INTERFACE)
target_include_directories(ImGui SYSTEM INTERFACE ${EXTERNAL_INCLUDES})
target_link_libraries(ImGui INTERFACE
    $<$<CONFIG:Debug>:${EXTERNAL_LIBS_DEBUG}/imguid.lib>
    $<$<CONFIG:Release>:${EXTERNAL_LIBS_RELEASE}/imgui.lib>
)

# ImGuizmo
add_library(ImGuizmo INTERFACE)
target_link_libraries(ImGuizmo INTERFACE
    $<$<CONFIG:Debug>:${EXTERNAL_LIBS_DEBUG}/imguizmo.lib>
    $<$<CONFIG:Release>:${EXTERNAL_LIBS_RELEASE}/imguizmo.lib>
)

# FreeType
add_library(FreeType INTERFACE)
target_include_directories(FreeType SYSTEM INTERFACE ${EXTERNAL_INCLUDES}/freetype)
target_link_libraries(FreeType INTERFACE
    $<$<CONFIG:Debug>:${EXTERNAL_LIBS_DEBUG}/freetyped.lib>
    $<$<CONFIG:Release>:${EXTERNAL_LIBS_RELEASE}/freetype.lib>
)

# PlutoSVG
add_library(PlutoSVG INTERFACE)
target_link_libraries(PlutoSVG INTERFACE
    $<$<CONFIG:Debug>:${EXTERNAL_LIBS_DEBUG}/plutosvg.lib>
    $<$<CONFIG:Release>:${EXTERNAL_LIBS_RELEASE}/plutosvg.lib>
    $<$<CONFIG:Debug>:${EXTERNAL_LIBS_DEBUG}/plutovg.lib>
    $<$<CONFIG:Release>:${EXTERNAL_LIBS_RELEASE}/plutovg.lib>
)

# PNG
add_library(PNG INTERFACE)
target_link_libraries(PNG INTERFACE
    $<$<CONFIG:Debug>:${EXTERNAL_LIBS_DEBUG}/libpng16d.lib>
    $<$<CONFIG:Release>:${EXTERNAL_LIBS_RELEASE}/libpng16.lib>
)

# Zlib
add_library(Zlib INTERFACE)
target_link_libraries(Zlib INTERFACE
    $<$<CONFIG:Debug>:${EXTERNAL_LIBS_DEBUG}/zlibd.lib>
    $<$<CONFIG:Release>:${EXTERNAL_LIBS_RELEASE}/zlib.lib>
)

# Brotli
add_library(Brotli INTERFACE)
target_link_libraries(Brotli INTERFACE
    $<$<CONFIG:Debug>:${EXTERNAL_LIBS_DEBUG}/brotlidec.lib>
    $<$<CONFIG:Debug>:${EXTERNAL_LIBS_DEBUG}/brotlicommon.lib>
    $<$<CONFIG:Release>:${EXTERNAL_LIBS_RELEASE}/brotlidec.lib>
    $<$<CONFIG:Release>:${EXTERNAL_LIBS_RELEASE}/brotlicommon.lib>
)

# bzip2
add_library(bzip2 INTERFACE)
target_link_libraries(bzip2 INTERFACE
    $<$<CONFIG:Debug>:${EXTERNAL_LIBS_DEBUG}/bz2d.lib>
    $<$<CONFIG:Release>:${EXTERNAL_LIBS_RELEASE}/bz2.lib>
)

# GameInput
add_library(GameInput INTERFACE)
target_link_libraries(GameInput INTERFACE gameinput)

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
        Sources/Runtime/Application/Platform/PlatformWindowContext.h)

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
)

# ================================================
# Include Directories
# ================================================
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/Sources/Editor
    ${CMAKE_SOURCE_DIR}/Sources/Runtime
    ${EXTERNAL_INCLUDES}
)

# ================================================
# Additional Compiler Definitions
# ================================================
target_compile_definitions(${PROJECT_NAME} PRIVATE
    WIN32_LEAN_AND_MEAN
    NOMINMAX
    $<$<CONFIG:Debug>:_DEBUG>
    $<$<CONFIG:Release>:NDEBUG>
)

# ================================================
# Copy External Binaries to Output Directory
# ================================================
if(WIN32)
    # Copy debug binaries for debug configuration
    if(EXISTS ${EXTERNAL_BINARIES_DEBUG})
        file(GLOB DEBUG_DLLS "${EXTERNAL_BINARIES_DEBUG}/*.dll")
        foreach(dll ${DEBUG_DLLS})
            add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${dll}"
                "$<$<CONFIG:Debug>:${CMAKE_BINARY_DIR}/bin/Debug/>"
                COMMENT "Copying debug DLL: ${dll}"
            )
        endforeach()
    endif()

    # Copy release binaries for release configuration
    if(EXISTS ${EXTERNAL_BINARIES_RELEASE})
        file(GLOB RELEASE_DLLS "${EXTERNAL_BINARIES_RELEASE}/*.dll")
        foreach(dll ${RELEASE_DLLS})
            add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${dll}"
                "$<$<CONFIG:Release>:${CMAKE_BINARY_DIR}/bin/Release/>"
                COMMENT "Copying release DLL: ${dll}"
            )
        endforeach()
    endif()
endif()

# ================================================
# Visual Studio specific settings
# ================================================
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        /W4                     # Warning level 4
        /permissive-           # Disable non-conforming code
        /Zc:__cplusplus        # Enable correct __cplusplus macro
        $<$<CONFIG:Debug>:/MDd>
        $<$<CONFIG:Release>:/MD>
    )

    # Set startup project in Visual Studio
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

    # Set working directory for debugging
    set_target_properties(${PROJECT_NAME} PROPERTIES
        VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
    )
endif()

# ================================================
# Post-build Actions
# ================================================
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "$<$<CONFIG:Debug>:${EXTERNAL_BINARIES_DEBUG}/dxcompiler.dll>"
    "$<$<CONFIG:Release>:${EXTERNAL_BINARIES_RELEASE}/dxcompiler.dll>"
    "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
    COMMENT "Copying DirectX Compiler DLL"
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "$<$<CONFIG:Debug>:${EXTERNAL_BINARIES_DEBUG}/dxil.dll>"
    "$<$<CONFIG:Release>:${EXTERNAL_BINARIES_RELEASE}/dxil.dll>"
    "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
    COMMENT "Copying DXIL DLL"
)
