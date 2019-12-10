cmake_minimum_required (VERSION 2.8) #最低要求的CMake版本
project(CStart) # 项目名称
file(GLOB SRC_FILE *.c) # 建立变量SRC_FILE为目录下.c文件列表
add_executable (${PROJECT_NAME} ${SRC_FILE}) # 要求编译可执行文件