set CURDIR=%CD%
set SOURCE_ROOT=%CURDIR%/loo/runtime
set THIRD_ROOT=%CURDIR%/loo/thirdpart
set BUILD_DIR=%CURDIR%/llvmbuild
set ALL=0
set MAIN_CPP=%SOURCE_ROOT%/main.cpp
set ARGS=-- clang++ -D__LOOREFLECT__=1  ^
-I%THIRD_ROOT%/glm ^
-I%SOURCE_ROOT%/global/include ^
-I%SOURCE_ROOT%/looreflect/include ^
-I%SOURCE_ROOT%/core/include
rem 一次只能生成一个文件。。待改进
if %ALL%==1 (
%CURDIR%/loo/tools/looreflect/looreflect.exe -p %BUILD_DIR% %SOURCE_ROOT% %MAIN_CPP% %ARGS%
) else (
%CURDIR%/loo/tools/looreflect/looreflect.exe ^
-p ^
%BUILD_DIR% %SOURCE_ROOT%/core/source/core/application/keycode.cpp ^
%ARGS%
)