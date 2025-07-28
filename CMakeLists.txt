cmake_minimum_required(VERSION 3.20)
project(NomadEngine)

# ================================================
# Basic Configuration
# ================================================
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Ensure 64-bit compilation
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

# External library paths
set(EXTERNAL_DIR ${CMAKE_SOURCE_DIR}/Sources/External)
set(EXTERNAL_INCLUDES ${EXTERNAL_DIR}/Includes)
set(EXTERNAL_LIBS_DEBUG ${EXTERNAL_DIR}/Libraries/Debug)
set(EXTERNAL_LIBS_RELEASE ${EXTERNAL_DIR}/Libraries/Release)
set(EXTERNAL_BINARIES_DEBUG ${EXTERNAL_DIR}/Binaries/Debug)
set(EXTERNAL_BINARIES_RELEASE ${EXTERNAL_DIR}/Binaries/Release)

# ================================================
# Source Files
# ================================================
file(GLOB_RECURSE SOURCES
    "Sources/Editor/*.cpp"
    "Sources/Editor/*.h"
    "Sources/Runtime/*.cpp"
    "Sources/Runtime/*.h"
)

# ================================================
# Executable Target
# ================================================
add_executable(${PROJECT_NAME} ${SOURCES})

# Target properties
set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
    WIN32_EXECUTABLE FALSE
)

# Compile definitions
target_compile_definitions(${PROJECT_NAME} PRIVATE
    SDL_MAIN_HANDLED
    WIN32_LEAN_AND_MEAN
    NOMINMAX
)

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/Sources/Runtime
    ${CMAKE_SOURCE_DIR}/Sources/Editor
    ${EXTERNAL_INCLUDES}
)

# Add SDL3 specific include path
target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE
    ${EXTERNAL_INCLUDES}/SDL3
)

# ================================================
# Libraries
# ================================================
target_link_libraries(${PROJECT_NAME}
    # SDL3 library
    $<$<CONFIG:Debug>:${EXTERNAL_LIBS_DEBUG}/SDL3-static.lib>
    $<$<CONFIG:Release>:${EXTERNAL_LIBS_RELEASE}/SDL3-static.lib>

    # ImGui library and its dependencies
    $<$<CONFIG:Debug>:${EXTERNAL_LIBS_DEBUG}/imguid.lib>
    $<$<CONFIG:Release>:${EXTERNAL_LIBS_RELEASE}/imgui.lib>

    # ImGuizmo
    $<$<CONFIG:Debug>:${EXTERNAL_LIBS_DEBUG}/imguizmo.lib>
    $<$<CONFIG:Release>:${EXTERNAL_LIBS_RELEASE}/imguizmo.lib>

    # FreeType
    $<$<CONFIG:Debug>:${EXTERNAL_LIBS_DEBUG}/freetyped.lib>
    $<$<CONFIG:Release>:${EXTERNAL_LIBS_RELEASE}/freetype.lib>

    # PlutoSVG and PlutoVG
    $<$<CONFIG:Debug>:${EXTERNAL_LIBS_DEBUG}/plutosvg.lib>
    $<$<CONFIG:Release>:${EXTERNAL_LIBS_RELEASE}/plutosvg.lib>
    $<$<CONFIG:Debug>:${EXTERNAL_LIBS_DEBUG}/plutovg.lib>
    $<$<CONFIG:Release>:${EXTERNAL_LIBS_RELEASE}/plutovg.lib>

    # libpng
    $<$<CONFIG:Debug>:${EXTERNAL_LIBS_DEBUG}/libpng16d.lib>
    $<$<CONFIG:Release>:${EXTERNAL_LIBS_RELEASE}/libpng16.lib>

    # zlib
    $<$<CONFIG:Debug>:${EXTERNAL_LIBS_DEBUG}/zlibd.lib>
    $<$<CONFIG:Release>:${EXTERNAL_LIBS_RELEASE}/zlib.lib>

    # brotli
    $<$<CONFIG:Debug>:${EXTERNAL_LIBS_DEBUG}/brotlidec.lib>
    $<$<CONFIG:Debug>:${EXTERNAL_LIBS_DEBUG}/brotlicommon.lib>
    $<$<CONFIG:Release>:${EXTERNAL_LIBS_RELEASE}/brotlidec.lib>
    $<$<CONFIG:Release>:${EXTERNAL_LIBS_RELEASE}/brotlicommon.lib>

    # bzip2
    $<$<CONFIG:Debug>:${EXTERNAL_LIBS_DEBUG}/bz2d.lib>
    $<$<CONFIG:Release>:${EXTERNAL_LIBS_RELEASE}/bz2.lib>

    # OpenGL
    $<$<CONFIG:Debug>:${EXTERNAL_LIBS_DEBUG}/OpenGL32.Lib>
    $<$<CONFIG:Release>:${EXTERNAL_LIBS_RELEASE}/OpenGL32.Lib>
    $<$<CONFIG:Debug>:${EXTERNAL_LIBS_DEBUG}/GlU32.Lib>
    $<$<CONFIG:Release>:${EXTERNAL_LIBS_RELEASE}/GlU32.Lib>

    # Windows system libraries
    user32 gdi32 winmm imm32 ole32 oleaut32
    version setupapi advapi32 shell32 kernel32
)

# ================================================
# Post-build Actions
# ================================================
# Copy required DLLs
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "$<$<CONFIG:Debug>:${EXTERNAL_BINARIES_DEBUG}/dxcompiler.dll>"
    "$<$<CONFIG:Release>:${EXTERNAL_BINARIES_RELEASE}/dxcompiler.dll>"
    $<TARGET_FILE_DIR:${PROJECT_NAME}>
    COMMENT "Copying DirectX Compiler DLL"
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "$<$<CONFIG:Debug>:${EXTERNAL_BINARIES_DEBUG}/dxil.dll>"
    "$<$<CONFIG:Release>:${EXTERNAL_BINARIES_RELEASE}/dxil.dll>"
    $<TARGET_FILE_DIR:${PROJECT_NAME}>
    COMMENT "Copying DXIL DLL"
)
