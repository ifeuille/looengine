# looengine

### 简单说明

c++14,未来将支持lua(自动绑定)

vulkan only

platform : windows,android

- 后续会支持ios等

支持反射(还有待扩展)

支持模块管理

利用三方库将C++17若干特性移植到了c++14，比如visit,string_view等



使用或参考了若干第三方开源库

主要包括：

strtk

[framegraph](https://github.com/azhirnov/FrameGraph.git)

metareflect

entt

## build

### windows
````
mkdir build
cd build
cmake .. -G"Visual Studio 15 2017 Win64"
````

### android

使用android studio 打开./android/目录即可

必须编译release版本，debug版本有.so引用问题，待解决

若想增加android测试例子，见./buildsys/android目录下的generate_sample_gradle.bat

