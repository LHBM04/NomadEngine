# Visual Studio 2022 Project Generator for NomadEngine
param(
    [switch]$OpenSolution = $false,
    [ValidateSet("Debug", "Release", "Both")]
    [string]$Configuration = "Both"
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

# Function to generate project
function Generate-Project {
    param($PresetName, $ConfigName)

    Write-Host ""
    Write-Host "Generating Visual Studio 2022 $ConfigName project..." -ForegroundColor Green

    try {
        & cmake --preset $PresetName
        if ($LASTEXITCODE -ne 0) {
            throw "CMake configuration failed with exit code $LASTEXITCODE"
        }
        Write-Host "✓ $ConfigName project generated successfully" -ForegroundColor Green
        return $true
    }
    catch {
        Write-Error "Failed to generate $ConfigName project: $_"
        return $false
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
    exit 1
}

Write-Host ""
Write-Host "Press any key to continue..." -ForegroundColor Gray
$null = $Host.UI.RawUI.ReadKey("NoEcho,IncludeKeyDown")
