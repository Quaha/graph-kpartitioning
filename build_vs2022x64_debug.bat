@echo off
REM Script for building a Visual Studio 2022 project with CMake on Windows

SET BUILD_DIR=build

REM Deleting the build folder, if there is one
IF EXIST %BUILD_DIR% (
    echo Deleting the build folder...
    rmdir /S /Q %BUILD_DIR%
)

mkdir %BUILD_DIR%
cd %BUILD_DIR%

REM Generating .sln for Visual Studio 2022 (x64)
cmake .. -G "Visual Studio 17 2022" -A x64

REM Assembling all targets in the Debug configuration
cmake --build . --config Debug

cd ..
echo Done!
pause