set CURDIR=%CD%
set SOURCE_ROOT=%CURDIR%/test
set LLVMPATH=E:/git/cpp/llvm/build/Release/bin
rem set LLVMPATH=E:/git/cpp/llvm/tools/clang/tools/extra/looreflect
rem set LLVMPATH=E:/git/language/llvm/llvm-project/build-vs/Debug/bin
set BUILD_DIR=%CURDIR%/build
set ALL=0
set MAIN_CPP=%SOURCE_ROOT%/main.cpp
set LOOREFLECTEXE=%LLVMPATH%/looreflect.exe
set ARGS=-- clang++ -D__LOOREFLECT__=1 -I%CURDIR%
if %ALL%==1 (
%LLVMPATH%/looreflect.exe -p %BUILD_DIR% %SOURCE_ROOT% %MAIN_CPP% %ARGS%
) else (
%LLVMPATH%/looreflect.exe ^
-p ^
%BUILD_DIR% %SOURCE_ROOT%/test.cpp ^
%ARGS%
)