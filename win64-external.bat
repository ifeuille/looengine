@echo off
set DIR=%CD%
IF NOT EXIST %DIR%/loo/thirdpart/build/win64 (
	cd loo/thirdpart/build
    mkdir win64
	cd %DIR%
)

cd %DIR%/loo/thirdpart/build/win64
cls
cmake -G"Visual Studio 15 2017 Win64" ..\..\
cls
cmake --build .
echo.

cd %DIR%


echo Press any key to continue ...
pause > nul