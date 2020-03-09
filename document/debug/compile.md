
1.error C2059 4430
https://social.msdn.microsoft.com/Forums/en-US/0c7b7b85-4064-4bfe-b16e-cd52bfba91fd/error-c2146-c4430-c2059?forum=vcgeneral
头文件包含顺序有问题
.cpp一般先包含自己的.h就没问题了

2.c++ constexpr
需要c++17
LOO_FORCEINLINE int ReadIntScalar (const StaticArray<uint, 4> &data)
{
    const uint	value = ReadUIntScalar< Bits, OffsetBits > (data);

    if constexpr (Bits == 0)
        return 0;
    else
        if constexpr (Bits == 32)
            return int (value);
        else
            return (value >> (Bits - 1)) ? -int (value) : int (value);	// TODO: check
}

改为如下形式，就可以c++11实现了
struct ReadIntScalar
{
    const uint Bits;
    const uint OffsetBits;
    ReadIntScalar (const uint& bits, const uint& offsetBits) :Bits (bits), OffsetBits (offsetBits) {}
    LOO_FORCEINLINE int operator()(const StaticArray<uint, 4> &data)
    {
        const uint	value = ReadUIntScalar(Bits,OffsetBits) (data);

        if (Bits == 0)
            return 0;
        else if (Bits == 32)
            return int (value);
        else
            return (value >> (Bits - 1)) ? -int (value) : int (value);	// TODO: check
    }
};

3.visit，variant引发得编译问题
其一：非标准visit不支持lambda
改为struct operator()实现
其二：error C3849: 类型“const Visitor”的表达式中的函数样式调用会丢失所有 8 个可用运算符重载的 const 和/或 volatile 限定符
原因是nonstd variant visit实现使用了 const VIsitor
改为struct operator() const实现


4.core.dll,exe
vulkandll在exe里initilize和load得，core.dll里访问不到，在core.dll里另外load,initilize一份就ok了


5.ExternalProject_Add
编译glslang时一直报错glslang CMake Error at ChooseMSVCCRT.cmake:31 (string):
查看可知，分隔符被设为了|
而cmake仍然采用;
也就是设置失败了
不替换就好了


## android环境
除了一堆clang下不符合语法火linux下没有的接口外，就是android环境问题了
还有引用路径linux是区分大小写的,windows不区分
vulkan头文件里一直报错android Vulkan isn't supported for the 'armeabi' NDK ABI
_ARMEEABI 是4
ndk { abiFilters  'arm64-v8a','armeabi-v7a' }没起作用？
把'arm64-v8a' 去掉就好了。。

其次是android_native_app_glue這個東西，一般是不用ndk里面那个，而采用一个改过后的，增加了get_app函数，可以屏蔽activity等中间java-c接口层

遇到一個关于operator==的问题，模板ArrayView的operator==要求模板参数有==
完整报错
````
In file included from ..\..\..\..\..\loo\runtime\vkfg\source\vkfg\vulkan\renderpass\vrenderpass.cpp:4:
In file included from ..\..\..\..\..\loo\runtime\vkfg\include\vkfg\vulkan\renderpass\vrenderpass.h:3:
In file included from ..\..\..\..\..\loo\runtime\vkfg\include\vkfg\fg\pipeline.h:4:
In file included from ..\..\..\..\..\loo\runtime\vkfg\include\vkfg\fg\renderstate.h:4:
In file included from ..\..\..\..\..\loo\runtime\vkfg\include\vkfg\fg\multisamples.h:4:
In file included from ..\..\..\..\..\loo\runtime\global\include\global\types.h:20:
..\..\..\..\..\loo\runtime\global\include\global\extstd\arrayview.h:77:25: error: call to function 'operator==' that is neither visible in the template definition nor found by argument-dependent lookup
````

调用ArrayView==的地方是某个文件的cpp
T的operator==放到这个cpp里的
在vs里没问题
但clang是在ArrayView<T>申明的时候就要知道有哦没有T的operator==，所以要移出来就好了

编译android，log.cpp里找不到log库的函数，原因是android lib没引用
参见：https://blog.csdn.net/sinat_22657459/article/details/80425743
具体就是
if(LOO_PLATFORM_ANDROID)
    find_library(log-lib log)
    set(EXTRA_LINKED_LIBRARIES ${EXTRA_LINKED_LIBRARIES}  ${log-lib})
endif()

常用库
LOCAL_LDLIBS := -llog -landroid -lEGL 
https://developer.android.com/studio/projects/configure-cmakea


一些c++17特性(要求c++14)
比如if constexpr
这类可以改为
constexpr bool cb=..
if(cb)..


android下ExternalProject_Add机制有点失灵了。不能编译时下载，动态更新工程
改为cmake项目时下载


一个project只能有一个shared lib



有的时候要用子项目的option控制是否cmake子项目
需要用cache变量


 java.lang.IllegalArgumentException: Unable to find native library testframework using classloader: (目标shared library)
原因是debug版本的.so 带后缀"_d"，不知道怎么产生的，用发行版就好了，太开心了，查这个问题用了10多个小时
移留问题：为什么debug版本后缀带"_d",输出名字明明没有设置

通过在src/下增加一个debug/AndroidManifest.xml来解决debug版下lib名字问题
<meta-data 
    tools:replace="android:value"
    android:name="android.app.lib_name"
    android:value='testframework_d'/>


todo: 设计一套更标准多用的android工程结构，支持多app

logcat 日志查看
adb logcat   -v time -s *:E >D:\log1.txt


android_native_app_glue这个东西现在常用的是两套方案，一套是用 原生的，需要注意链接符号ANativeActivity_onCreate
一套是修改后的：增加get_app接口，将入口函数改为main,这样可以使得多个平台入口相同，同时少了ANativeActivity_onCreate的问题

只有用第二种方案，又遇到这个问题 
undefined symbol: ANativeActivity_onCreate
at android.app.NativeActivity.onCreate(NativeActivity.java:181)
看起来像是native_app_glue链接失败了，导致没找到这个符号



解决办法是在创建app时将.cpp加进去
add_library(${EXE_NAME} SHARED  ${SOURCE_PRIVATE} 
${LOO_THIRDPART_ROOT_DIR}/android_native_app_glue/android_native_app_glue.c)
问题很明确不用猜
明显也不对

追根溯源

找到java报错点android.app.NativeActivity.onCreate(NativeActivity.java:181)
````
String libname = "main";
String funcname = "ANativeActivity_onCreate";
...
try {
        ai = getPackageManager().getActivityInfo(
            getIntent().getComponent(), PackageManager.GET_META_DATA);
        if (ai.metaData != null) {
            String ln = ai.metaData.getString(META_DATA_LIB_NAME);
            if (ln != null) libname = ln;
            ln = ai.metaData.getString(META_DATA_FUNC_NAME);
            if (ln != null) funcname = ln;
        }
    } catch (PackageManager.NameNotFoundException e) {
        throw new RuntimeException("Error getting activity info", e);
    }
````
这里可以知道可以通过定义meta-data指定libname以及入口函数META_DATA_FUNC_NAME = "android.app.func_name";


这是加载native的地方
mNativeHandle = loadNativeCode(path, funcname, Looper.myQueue(),
        getAbsolutePath(getFilesDir()), getAbsolutePath(getObbDir()),
        getAbsolutePath(getExternalFilesDir(null)),
        Build.VERSION.SDK_INT, getAssets(), nativeSavedState,
        classLoader, classLoader.getLdLibraryPath());


从armabi-v7a切换到arm64-v8a后报错了
packageDebug FAILED  Unable to find EOCD signature
原因是导出的*.apk文件已经存在删除就好了


-----
vulkan头文件vk_platform.h有个报错，在arm64-v8a情况下 __ARM_ARCH = 4
#elif defined(__ANDROID__) && defined(__ARM_ARCH) && __ARM_ARCH < 7  //注释掉
    #error "Vulkan isn't supported for the 'armeabi' NDK ABI"   //注释掉
#elif defined(__ANDROID__) && defined(__ARM_ARCH) && __ARM_ARCH >= 7 && defined(__ARM_32BIT_STATE)
    // On Android 32-bit ARM targets, Vulkan functions use the "hardfloat"
    // calling convention, i.e. float parameters are passed in registers. This
    // is true even if the rest of the application passes floats on the stack,
    // as it does by default when compiling for the armeabi-v7a NDK ABI.
    #define VKAPI_ATTR __attribute__((pcs("aapcs-vfp")))
    #define VKAPI_CALL
    #define VKAPI_PTR  VKAPI_ATTR
#else

-----
android studio调试lldb 失败，
A few people and I from the Visual Studio Developer Community have triaged the issue, and found that downgrading the Android Platform Tools back to version 28.0.x solves the issues being caused by version 29.0.x.

View the community thread here: 
https://developercommunity.visualstudio.com/content/problem/733170/error-starting-application-failed-to-forward-ports.html?childToView=739773#comment-739773

Resolution:
1. Close Visual Studio
2. Delete the existing platform-tools from your android SDK
3. Download platform-tools version 28.0.2 from Google's repository here: https://dl-ssl.google.com/android/repository/platform-tools_r28.0.2-windows.zip
4. Un-zip and move the platform-tools (version 28.0.2) into to your Android SDK.
5. Delete the 'bin' and 'obj' folders from your project/solution
6. Clean project/solution
7. Rebuild project/solution


----------
大概率是link出问题了
.so link .a的问题
路径？

SET(SO_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/libs/${LOO_ARCH_NAME})
    set_target_properties(${MODULE_NAME} PROPERTIES 
        ARCHIVE_OUTPUT_DIRECTORY ${SO_OUTPUT_DIR}
        ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${SO_OUTPUT_DIR}
        ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${SO_OUTPUT_DIR}
        ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO ${SO_OUTPUT_DIR}
        ARCHIVE_OUTPUT_DIRECTORY_MINSIZEREL ${SO_OUTPUT_DIR}
    )
        SET(SO_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/libs/${LOO_ARCH_NAME})
    SET_TARGET_PROPERTIES(${EXE_NAME} PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY ${SO_OUTPUT_DIR}
        LIBRARY_OUTPUT_DIRECTORY_DEBUG ${SO_OUTPUT_DIR}
        LIBRARY_OUTPUT_DIRECTORY_RELEASE ${SO_OUTPUT_DIR}
        LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO ${SO_OUTPUT_DIR}
        LIBRARY_OUTPUT_DIRECTORY_MINSIZEREL ${SO_OUTPUT_DIR}
    )
在android模式下，这个路径不能是工程外路径

改过之后，release版本ok了，debug版本还是不行

经过比较，发现.so的debug版本比release小--也不对



todo 显示link不要用库依赖自动link