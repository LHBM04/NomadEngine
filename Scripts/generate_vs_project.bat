@echo off
REM VS2022 프로젝트 생성 배치 파일
REM NomadEngine VS2022 프로젝트를 생성하고 External 라이브러리를 포함합니다.

setlocal enabledelayedexpansion

set "CONFIG=%~1"
set "PLATFORM=%~2"

if "%CONFIG%"=="" set "CONFIG=Debug"
if "%PLATFORM%"=="" set "PLATFORM=x64"

echo NomadEngine VS2022 프로젝트 생성 중...
echo 구성: %CONFIG%
echo 플랫폼: %PLATFORM%

REM 스크립트 실행 위치를 프로젝트 루트로 변경
cd /d "%~dp0.."

REM 빌드 디렉토리 설정
set "BUILD_DIR=Build\VS2022\vs2022-debug-x64"

echo CMake 구성 중...

REM CMake 프리셋 확인 - 올바른 위치에서 실행
cd /d "%~dp0.."

REM CMake 프리셋 사용
if exist "CMakePresets.json" (
    echo CMake 프리셋 사용 중...
    cmake --preset vs2022-debug-x64
) else (
    REM 수동 CMake 구성
    mkdir "%BUILD_DIR%" 2>nul
    cd /d "%BUILD_DIR%"
    cmake -G "Visual Studio 17 2022" -A %PLATFORM% -DCMAKE_BUILD_TYPE=%CONFIG% -DCMAKE_CONFIGURATION_TYPES=Debug;Release -DCMAKE_VS_INCLUDE_INSTALL_TO_DEFAULT_BUILD=ON "..\..\..\"
)

if %ERRORLEVEL% equ 0 (
    echo.
    echo ✓ VS2022 프로젝트 생성 완료!
    echo 프로젝트 위치: %BUILD_DIR%
    echo 솔루션 파일: %BUILD_DIR%\NomadEngine.sln
    echo.

    REM 솔루션 파일 열기 옵션
    if exist "%BUILD_DIR%\NomadEngine.sln" (
        set /p OPEN_SOLUTION="Visual Studio에서 솔루션을 여시겠습니까? (y/n): "
        if /i "!OPEN_SOLUTION!"=="y" (
            start "%BUILD_DIR%\NomadEngine.sln"
        )
    )
) else (
    echo.
    echo ✗ 프로젝트 생성 실패!
    pause
    exit /b 1
)

echo.
pause
