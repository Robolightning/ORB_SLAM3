# Build ORB_SLAM3 on Windows using vcpkg

param(
    [string]$VcpkgRoot = $env:VCPKG_ROOT,
    [string]$Configuration = "Release",
    [switch]$SuppressWarnings = $true,
    [switch]$BuildExamples = $true
)

# Determine vcpkg root
if (-not $VcpkgRoot) {
    $VcpkgRoot = "C:\vcpkg"
    if (-not (Test-Path $VcpkgRoot)) {
        Write-Host "vcpkg not found at default path $VcpkgRoot. Please set VCPKG_ROOT environment variable or pass -VcpkgRoot." -ForegroundColor Red
        exit 1
    }
}
$vcpkgToolchain = Join-Path $VcpkgRoot "scripts\buildsystems\vcpkg.cmake"
if (-not (Test-Path $vcpkgToolchain)) {
    Write-Host "vcpkg toolchain file not found: $vcpkgToolchain" -ForegroundColor Red
    exit 1
}

Write-Host "=== Setting up vcpkg dependencies ===" -ForegroundColor Green
# Install dependencies using manifest mode (requires vcpkg.json in project root)
& "$VcpkgRoot\vcpkg" install --triplet x64-windows

Write-Host "=== Uncompressing vocabulary ===" -ForegroundColor Green
Push-Location Vocabulary
if (Test-Path "ORBvoc.txt.tar.gz") {
    # Use built-in tar (available on Windows 10/11)
    tar -xf ORBvoc.txt.tar.gz
} else {
    Write-Host "Vocabulary archive ORBvoc.txt.tar.gz not found." -ForegroundColor Yellow
}
Pop-Location

Write-Host "=== Configuring and building ORB_SLAM3 ===" -ForegroundColor Green
New-Item -ItemType Directory -Force -Path build | Out-Null
Push-Location build

# Prepare CMake arguments
$cmakeArgs = @(
    "..",
    "-DCMAKE_TOOLCHAIN_FILE=`"$vcpkgToolchain`"",
    "-DCMAKE_BUILD_TYPE=$Configuration"
)
if ($SuppressWarnings) {
    $cmakeArgs += "-DSUPPRESS_WARNINGS=ON"
}
if ($BuildExamples) {
    $cmakeArgs += "-DBUILD_EXAMPLES=ON"
}

# Run CMake configuration
cmake $cmakeArgs
if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }

# Build
cmake --build . --config $Configuration --parallel
if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }

Pop-Location
Write-Host "Build completed successfully." -ForegroundColor Green