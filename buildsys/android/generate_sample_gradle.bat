

@echo off

rem arg1 project name

set SCRIPT_DIR=%~dp0
set PROJ_NAME=%1
set ROOT_DIR=%SCRIPT_DIR%..\..

set SAMPLE_TEMPLATE_DIR=%ROOT_DIR%\android\examples\_template
set BUILD_DIR=%ROOT_DIR%\android\examples\%PROJ_NAME%

rem arm64-v8a;armeabi-v7a
call cmake.exe -DPROJECT_NAME="%PROJ_NAME%"^
               -DANDROID_API=24^
			   -DARCH_ABI="armeabi-v7a"^
			   -DJAVA_DIRS=""^
			   -DRES_DIRS=""^
			   -DOUTPUT_DIR="%BUILD_DIR%"^
               -DALL_ROOT="%ROOT_DIR%"^
			   -DASSET_DIRS=""^
			   -DJNI_LIBS_DIRS=""^
			   -DNATIVE_SCRIPT="%ROOT_DIR%\CMakeLists.txt"^
			   -DNATIVE_ARGUMENTS="ANDROID_TOOLCHAIN=clang;ANDROID_STL=c++_shared"^
			   -P "%SCRIPT_DIR%\create_sample_gradle.cmake"
