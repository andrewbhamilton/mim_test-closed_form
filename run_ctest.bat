@echo off
setlocal DisableDelayedExpansion


call scripts\find_cmake
if %errorlevel% GTR 0 (
	exit /b 1
)

call generate_VS ON
if %errorlevel% GTR 0 (
	exit /b 1
)

call %CMAKE_FILE% --build build
call %CTEST_FILE% --test-dir build --output-on-failure


pause
