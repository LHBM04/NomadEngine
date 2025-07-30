@echo off
echo ================================================
echo Visual Studio 2022 Project Generator for NomadEngine
echo ================================================

cd /d "%~dp0\.."

echo.
echo Checking for Visual Studio 2022...
where devenv >nul 2>&1
if %errorlevel% neq 0 (
    echo Warning: Visual Studio 2022 not found in PATH
    echo Make sure Visual Studio 2022 is installed
)

echo.
echo Verifying External Libraries...
if not exist "Sources\External\Includes" (
    echo Error: Missing External\Includes directory
    goto :error
)
if not exist "Sources\External\Libraries\Debug" (
    echo Error: Missing External\Libraries\Debug directory
    goto :error
)
if not exist "Sources\External\Libraries\Release" (
    echo Error: Missing External\Libraries\Release directory
    goto :error
)

echo External library directories verified successfully

echo.
echo Cleaning old CMake cache...
if exist "Build\VS2022\vs2022-debug-x64\CMakeCache.txt" del "Build\VS2022\vs2022-debug-x64\CMakeCache.txt"
if exist "Build\VS2022\vs2022-debug-x64\CMakeFiles" rmdir /s /q "Build\VS2022\vs2022-debug-x64\CMakeFiles"
if exist "Build\VS2022\vs2022-release-x64\CMakeCache.txt" del "Build\VS2022\vs2022-release-x64\CMakeCache.txt"
if exist "Build\VS2022\vs2022-release-x64\CMakeFiles" rmdir /s /q "Build\VS2022\vs2022-release-x64\CMakeFiles"

echo.
echo Generating Visual Studio 2022 Debug project...
cmake --preset vs2022-debug-x64
if %errorlevel% neq 0 (
    echo Error: Failed to generate Debug project
    goto :error
)

echo.
echo Generating Visual Studio 2022 Release project...
cmake --preset vs2022-release-x64
if %errorlevel% neq 0 (
    echo Error: Failed to generate Release project
    goto :error
)

echo.
echo Verifying project configuration...
if exist "Build\VS2022\vs2022-debug-x64\NomadEngine.vcxproj" (
    findstr /c:"Sources\\External\\Includes" "Build\VS2022\vs2022-debug-x64\NomadEngine.vcxproj" >nul
    if %errorlevel% equ 0 (
        echo ✓ External includes properly configured in Debug project
    ) else (
        echo Warning: External includes may not be properly configured
    )

    findstr /c:"Sources\\External\\Libraries" "Build\VS2022\vs2022-debug-x64\NomadEngine.vcxproj" >nul
    if %errorlevel% equ 0 (
        echo ✓ External libraries properly configured in Debug project
    ) else (
        echo Warning: External libraries may not be properly configured
    )
)

echo.
echo ================================================
echo Project generation completed successfully!
echo ================================================
echo.
echo Debug project location:   Build\VS2022\vs2022-debug-x64\
echo Release project location: Build\VS2022\vs2022-release-x64\
echo.
echo Visual Studio Project Features:
echo   ✓ External library include directories automatically configured
echo   ✓ Linker dependencies automatically set for Debug/Release
echo   ✓ DirectX, SDL3, ImGui, FreeType and other libraries linked
echo   ✓ DLL files will be copied to output directory after build
echo   ✓ Working directory set for debugging
echo.
echo To open the solution in Visual Studio:
echo   - Debug:   Build\VS2022\vs2022-debug-x64\NomadEngine.sln
echo   - Release: Build\VS2022\vs2022-release-x64\NomadEngine.sln
echo.

set /p choice="Open Debug solution in Visual Studio? (y/n): "
if /i "%choice%"=="y" (
    if exist "Build\VS2022\vs2022-debug-x64\NomadEngine.sln" (
        echo Opening Visual Studio...
        start "" "Build\VS2022\vs2022-debug-x64\NomadEngine.sln"
    ) else (
        echo Warning: Solution file not found
    )
)

echo.
echo Press any key to continue...
pause >nul
exit /b 0

:error
echo.
echo ================================================
echo Project generation failed!
echo ================================================
echo.
echo Troubleshooting suggestions:
echo   1. Ensure all external libraries are properly installed
echo   2. Check CMakePresets.json for correct preset names
echo   3. Verify Visual Studio 2022 is properly installed
echo   4. Run this script as administrator if needed
echo.
pause
exit /b 1
