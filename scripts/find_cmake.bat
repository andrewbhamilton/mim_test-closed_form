@echo off


set HOME=%~DP0..
rem normalise %HOME% path
pushd %HOME%
	set HOME=%CD%
popd
set CMAKE_HOME=%HOME%\vendor
set CMAKE_BIN=%CMAKE_HOME%\cmake_bin
set CMAKE_FILE=%CMAKE_BIN%\bin\cmake.exe
set CTEST_FILE=%CMAKE_BIN%\bin\ctest.exe


if exist %CMAKE_FILE% (
if exist %CTEST_FILE% (
	goto cmake_found
))

echo downloading cmake...


set CMAKE_VERSION_MAJOR=3.28
set CMAKE_VERSION=%CMAKE_VERSION_MAJOR%.3


mkdir %CMAKE_HOME%
pushd %CMAKE_HOME%
	set TEMP_NAME=temp

	rem download cmake
	curl -L https://github.com/Kitware/CMake/releases/download/v%CMAKE_VERSION%/cmake-%CMAKE_VERSION%-windows-x86_64.zip > %TEMP_NAME%.zip
	rem unzip cmake into a temporary folder called %TEMP_NAME%
	Powershell.exe Expand-Archive -LiteralPath %TEMP_NAME%.zip -Force

	rem make bin folder
	rmdir /s /q %CMAKE_BIN%
	mkdir %CMAKE_BIN%
	rem move cmake.exe into vendor
	move %TEMP_NAME%\cmake-%CMAKE_VERSION%-windows-x86_64\bin %CMAKE_BIN%
	move %TEMP_NAME%\cmake-%CMAKE_VERSION%-windows-x86_64\share %CMAKE_BIN%

	rem delete temporary folder
	rmdir /s /q %TEMP_NAME%
	rem delete zip file
	del /f %TEMP_NAME%.zip
popd

if exist %CMAKE_FILE% (
if exist %CTEST_FILE% (
	goto cmake_found
))


echo failed to download cmake
exit /b 1


:cmake_found


echo cmake @ %CMAKE_FILE%
