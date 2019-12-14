@echo off
set DIR=%CD%
cd %DIR%
IF EXIST %DIR%/build (
	rd /s /Q %DIR%\build
)
IF NOT EXIST %DIR%/build (
	mkdir build
	cd %DIR%
)
cd %DIR%/build
cmake ..
cmake --build .

cd %DIR%/bin
generate_keywords.exe>>../../keywords.cpp
generate_keywords.exe preprocessor>>../../ppkeywords.cpp

cd %DIR%