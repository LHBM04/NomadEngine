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
echo Generating Visual Studio 2022 Debug project...
cmake --preset vs2022-debug-x64
if %errorlevel% neq 0 (
    echo Error: Failed to generate Debug project
    pause
    exit /b 1
)

echo.
echo Generating Visual Studio 2022 Release project...
cmake --preset vs2022-release-x64
if %errorlevel% neq 0 (
    echo Error: Failed to generate Release project
    pause
    exit /b 1
)

echo.
echo ================================================
echo Project generation completed successfully!
echo ================================================
echo.
echo Debug project location:   Build\VS2022\vs2022-debug-x64\
echo Release project location: Build\VS2022\vs2022-release-x64\
echo.
echo To open the solution in Visual Studio:
echo   - Debug:   Build\VS2022\vs2022-debug-x64\NomadEngine.sln
echo   - Release: Build\VS2022\vs2022-release-x64\NomadEngine.sln
echo.

set /p choice="Open Debug solution in Visual Studio? (y/n): "
if /i "%choice%"=="y" (
    if exist "Build\VS2022\vs2022-debug-x64\NomadEngine.sln" (
        start "" "Build\VS2022\vs2022-debug-x64\NomadEngine.sln"
    ) else (
        echo Solution file not found!
    )
)

pause
