@echo off
setlocal DisableDelayedExpansion


set BUILD_TESTING=OFF
if not "%1"=="" if "%1"=="ON" (
	set BUILD_TESTING=ON
)


call scripts\find_cmake
if %errorlevel% GTR 0 (
	exit /b 1
)

mkdir build
call %CMAKE_FILE%^
 -DBUILD_TESTING=%BUILD_TESTING%^
 -DCMAKE_CONFIGURATION_TYPES=Debug;Release^
 -G "Visual Studio 17 2022" -A x64^
 -S . -B build
