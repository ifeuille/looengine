set CURDIR=%CD%
set SOURCE_ROOT=%CURDIR%/loo/runtime
set BUILD_DIR=%CURDIR%/build
set ALL=0
set MAIN_CPP=%SOURCE_ROOT%/main.cpp
set ARGS=-- clang++ -D__LOOREFLECT__=1 -I%SOURCE_ROOT%/global/include ^
-I%SOURCE_ROOT%/looreflect/include

if %ALL%==1 (
%CURDIR%/loo/tools/looreflect/looreflect.exe -p %BUILD_DIR% %SOURCE_ROOT% %MAIN_CPP% %ARGS%
) else (
%CURDIR%/loo/tools/looreflect/looreflect.exe ^
-p ^
%BUILD_DIR% %SOURCE_ROOT%/looreflect/source/object/object.cpp ^
%ARGS%
)