# looengine

## folders

loo

loo/thirdpart lib/dll

loo/core lib

loo/tools exe

loo/engine dll

resources/template

resources/public

projects

projects/Tests

projects/samples

buildsys

buildsys/cmake

buildsys/scripts

buildsys/toolchain

build

output

output/bin

output/lib

document

## define

c++11

c++/lua

llvm/clang only

vulkan only

platform : windows,linux,android,mac,ios

wish:ps5(vulkan supported half life5),switch

more:xbox(need vulkan wrap dx)

## build

### windows
http://llvm.org/builds/

https://marketplace.visualstudio.com/items?itemName=LLVMExtensions.llvm-toolchain

dic : build

cmake ..\.. -T"LLVM-vs2014" -G "Visual Studio 15 2017 Win64" -DCMAKE_CXX_COMPILER:PATH="D:\env\clang\LLVM\bin\clang-cl.exe" -DCMAKE_C_COMPILER:PATH="D:\env\clang\LLVM\bin\clang-cl.exe" -DCMAKE_LINKER:PATH="D:\env\clang\LLVM\bin\lld-link.exe"


run

````
msbuild  LOO.sln /t:material_sandbox /m /p:configuration=Release


````
