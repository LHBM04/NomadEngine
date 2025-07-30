# Visual Studio 2022 Project Generator for NomadEngine
param(
    [switch]$OpenSolution = $false,
    [ValidateSet("Debug", "Release", "Both")]
    [string]$Configuration = "Both",
    [switch]$CleanCache = $false,
    [switch]$VerifyLibraries = $true
)

Write-Host "================================================" -ForegroundColor Cyan
Write-Host "Visual Studio 2022 Project Generator for NomadEngine" -ForegroundColor Cyan
Write-Host "================================================" -ForegroundColor Cyan

# Change to project root directory
$scriptDir = Split-Path -Parent $MyInvocation.MyCommand.Path
$projectRoot = Split-Path -Parent $scriptDir
Set-Location $projectRoot

Write-Host ""
Write-Host "Checking for Visual Studio 2022..." -ForegroundColor Yellow

# Check if Visual Studio is available
$vsInstallations = Get-ChildItem "HKLM:\SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall" |
    Get-ItemProperty |
    Where-Object { $_.DisplayName -like "*Visual Studio*2022*" }

if (-not $vsInstallations) {
    Write-Warning "Visual Studio 2022 not detected in registry"
    Write-Host "Make sure Visual Studio 2022 is installed" -ForegroundColor Red
}

# Function to verify external libraries exist
function Verify-ExternalLibraries {
    Write-Host ""
    Write-Host "Verifying External Libraries..." -ForegroundColor Yellow

    $externalDir = "Sources\External"
    $includesDir = "$externalDir\Includes"
    $libsDebugDir = "$externalDir\Libraries\Debug"
    $libsReleaseDir = "$externalDir\Libraries\Release"
    $binariesDebugDir = "$externalDir\Binaries\Debug"
    $binariesReleaseDir = "$externalDir\Binaries\Release"

    $missingDirs = @()

    if (-not (Test-Path $includesDir)) { $missingDirs += $includesDir }
    if (-not (Test-Path $libsDebugDir)) { $missingDirs += $libsDebugDir }
    if (-not (Test-Path $libsReleaseDir)) { $missingDirs += $libsReleaseDir }

    if ($missingDirs.Count -gt 0) {
        Write-Warning "Missing External Library directories:"
        foreach ($dir in $missingDirs) {
            Write-Host "  - $dir" -ForegroundColor Red
        }
        Write-Host ""
        Write-Host "Please ensure all external libraries are properly installed." -ForegroundColor Yellow
        return $false
    }

    # Check for specific library files
    $requiredLibs = @(
        @{ Debug = "$libsDebugDir\SDL3-static.lib"; Release = "$libsReleaseDir\SDL3-static.lib"; Name = "SDL3" },
        @{ Debug = "$libsDebugDir\imguid.lib"; Release = "$libsReleaseDir\imgui.lib"; Name = "ImGui" },
        @{ Debug = "$libsDebugDir\freetyped.lib"; Release = "$libsReleaseDir\freetype.lib"; Name = "FreeType" }
    )

    $missingLibs = @()
    foreach ($lib in $requiredLibs) {
        if (-not (Test-Path $lib.Debug)) { $missingLibs += "$($lib.Name) Debug: $($lib.Debug)" }
        if (-not (Test-Path $lib.Release)) { $missingLibs += "$($lib.Name) Release: $($lib.Release)" }
    }

    if ($missingLibs.Count -gt 0) {
        Write-Warning "Missing library files:"
        foreach ($lib in $missingLibs) {
            Write-Host "  - $lib" -ForegroundColor Red
        }
        Write-Host ""
    } else {
        Write-Host "✓ External libraries verified successfully" -ForegroundColor Green
    }

    return $missingLibs.Count -eq 0
}

# Function to clean CMake cache
function Clean-CMakeCache {
    param($BuildDir)

    if (Test-Path $BuildDir) {
        Write-Host "Cleaning CMake cache in $BuildDir..." -ForegroundColor Yellow
        try {
            Remove-Item "$BuildDir\CMakeCache.txt" -Force -ErrorAction SilentlyContinue
            Remove-Item "$BuildDir\CMakeFiles" -Recurse -Force -ErrorAction SilentlyContinue
            Write-Host "✓ Cache cleaned successfully" -ForegroundColor Green
        }
        catch {
            Write-Warning "Failed to clean cache: $_"
        }
    }
}

# Function to generate project
function Generate-Project {
    param($PresetName, $ConfigName)

    Write-Host ""
    Write-Host "Generating Visual Studio 2022 $ConfigName project..." -ForegroundColor Green

    $buildDir = "Build\VS2022\$PresetName"

    # Clean cache if requested
    if ($CleanCache) {
        Clean-CMakeCache $buildDir
    }

    try {
        & cmake --preset $PresetName
        if ($LASTEXITCODE -ne 0) {
            throw "CMake configuration failed with exit code $LASTEXITCODE"
        }

        # Verify the solution file was created
        $solutionPath = "$buildDir\NomadEngine.sln"
        if (-not (Test-Path $solutionPath)) {
            throw "Solution file not generated: $solutionPath"
        }

        # Verify project includes external libraries
        $projectPath = "$buildDir\NomadEngine.vcxproj"
        if (Test-Path $projectPath) {
            $projectContent = Get-Content $projectPath -Raw
            $hasIncludes = $projectContent -match "Sources\\External\\Includes"
            $hasLibraries = $projectContent -match "Sources\\External\\Libraries"

            if ($hasIncludes -and $hasLibraries) {
                Write-Host "✓ External libraries properly integrated in Visual Studio project" -ForegroundColor Green
            } else {
                Write-Warning "External libraries may not be properly integrated. Check project settings."
            }
        }

        Write-Host "✓ $ConfigName project generated successfully" -ForegroundColor Green
        return $true
    }
    catch {
        Write-Error "Failed to generate $ConfigName project: $_"
        return $false
    }
}

# Verify external libraries if requested
if ($VerifyLibraries) {
    $librariesOk = Verify-ExternalLibraries
    if (-not $librariesOk) {
        Write-Host "Consider installing missing libraries or use -VerifyLibraries:$false to skip verification" -ForegroundColor Yellow
    }
}

# Generate projects based on configuration parameter
$success = $true

if ($Configuration -eq "Debug" -or $Configuration -eq "Both") {
    $success = $success -and (Generate-Project "vs2022-debug-x64" "Debug")
}

if ($Configuration -eq "Release" -or $Configuration -eq "Both") {
    $success = $success -and (Generate-Project "vs2022-release-x64" "Release")
}

if ($success) {
    Write-Host ""
    Write-Host "================================================" -ForegroundColor Green
    Write-Host "Project generation completed successfully!" -ForegroundColor Green
    Write-Host "================================================" -ForegroundColor Green
    Write-Host ""

    if ($Configuration -eq "Debug" -or $Configuration -eq "Both") {
        Write-Host "Debug project location:   Build\VS2022\vs2022-debug-x64\" -ForegroundColor Cyan
    }
    if ($Configuration -eq "Release" -or $Configuration -eq "Both") {
        Write-Host "Release project location: Build\VS2022\vs2022-release-x64\" -ForegroundColor Cyan
    }

    Write-Host ""
    Write-Host "Visual Studio Project Features:" -ForegroundColor Yellow
    Write-Host "  ✓ External library include directories automatically configured" -ForegroundColor Green
    Write-Host "  ✓ Linker dependencies automatically set for Debug/Release" -ForegroundColor Green
    Write-Host "  ✓ DirectX, SDL3, ImGui, FreeType and other libraries linked" -ForegroundColor Green
    Write-Host "  ✓ DLL files will be copied to output directory after build" -ForegroundColor Green
    Write-Host "  ✓ Working directory set for debugging" -ForegroundColor Green

    Write-Host ""
    Write-Host "To open the solution in Visual Studio:" -ForegroundColor Yellow
    if ($Configuration -eq "Debug" -or $Configuration -eq "Both") {
        Write-Host "  - Debug:   Build\VS2022\vs2022-debug-x64\NomadEngine.sln" -ForegroundColor White
    }
    if ($Configuration -eq "Release" -or $Configuration -eq "Both") {
        Write-Host "  - Release: Build\VS2022\vs2022-release-x64\NomadEngine.sln" -ForegroundColor White
    }

    # Option to open solution
    if ($OpenSolution -or ($Configuration -eq "Debug" -or $Configuration -eq "Both")) {
        $debugSolutionPath = "Build\VS2022\vs2022-debug-x64\NomadEngine.sln"

        if (-not $OpenSolution) {
            $choice = Read-Host "`nOpen Debug solution in Visual Studio? (y/n)"
            $OpenSolution = $choice -eq "y" -or $choice -eq "Y"
        }

        if ($OpenSolution -and (Test-Path $debugSolutionPath)) {
            Write-Host "Opening Visual Studio..." -ForegroundColor Green
            Start-Process $debugSolutionPath
        }
        elseif ($OpenSolution) {
            Write-Warning "Solution file not found: $debugSolutionPath"
        }
    }
}
else {
    Write-Host ""
    Write-Host "================================================" -ForegroundColor Red
    Write-Host "Project generation failed!" -ForegroundColor Red
    Write-Host "================================================" -ForegroundColor Red
    Write-Host ""
    Write-Host "Troubleshooting suggestions:" -ForegroundColor Yellow
    Write-Host "  1. Try running with -CleanCache to clear old CMake cache" -ForegroundColor White
    Write-Host "  2. Ensure all external libraries are properly installed" -ForegroundColor White
    Write-Host "  3. Check CMakePresets.json for correct preset names" -ForegroundColor White
    Write-Host "  4. Verify Visual Studio 2022 is properly installed" -ForegroundColor White
    exit 1
}

Write-Host ""
Write-Host "Press any key to continue..." -ForegroundColor Gray
$null = $Host.UI.RawUI.ReadKey("NoEcho,IncludeKeyDown")
