@echo off

REM Script for installing major external dependencies

SET GTEST_DIR=external\gtest

REM Deleting the gtest folder, if there is one
IF EXIST %GTEST_DIR% (
    echo Deleting the gtest folder...
    rmdir /S /Q %GTEST_DIR%
)

echo gtest installing...
git clone --branch v1.17.0 https://github.com/google/googletest.git %GTEST_DIR%

echo Done!
pause