

@echo off

set SCRIPT_DIR=%~dp0

set ROOT_DIR=%SCRIPT_DIR%..\..

if [%1] == [] (
    set BUILD_DIR=%ROOT_DIR%\android_gradle
) else (
    set BUILD_DIR=%1
)
rem arm64-v8a;armeabi-v7a
call cmake.exe -DPROJECT_NAME="looengine"^
			   -DANDROID_API=24^
			   -DARCH_ABI="armeabi-v7a"^
			   -DANDROID_MANIFEST="%ROOT_DIR%\loo\thirdpart\android\AndroidManifest.xml"^
			   -DJAVA_DIRS="%ROOT_DIR%\loo\thirdpart\android/java"^
			   -DRES_DIRS="%ROOT_DIR%\loo\thirdpart\android\res"^
			   -DOUTPUT_DIR="%BUILD_DIR%"^
			   -DASSET_DIRS=""^
			   -DJNI_LIBS_DIRS=""^
			   -DNATIVE_SCRIPT="%ROOT_DIR%\CMakeLists.txt"^
			   -DNATIVE_ARGUMENTS="ANDROID_TOOLCHAIN=clang;ANDROID_STL=c++_static"^
			   -P "%ROOT_DIR%\buildsys\cmake\create_gradle_project.cmake"
