# Install script for directory: E:/git/mine/loo/looengine/loo/runtime

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/loo")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("E:/git/mine/loo/looengine/llvmbuild/loo/runtime/global/cmake_install.cmake")
  include("E:/git/mine/loo/looengine/llvmbuild/loo/runtime/looreflect/cmake_install.cmake")
  include("E:/git/mine/loo/looengine/llvmbuild/loo/runtime/modulemanager/cmake_install.cmake")
  include("E:/git/mine/loo/looengine/llvmbuild/loo/runtime/plog/cmake_install.cmake")
  include("E:/git/mine/loo/looengine/llvmbuild/loo/runtime/filemanager/cmake_install.cmake")
  include("E:/git/mine/loo/looengine/llvmbuild/loo/runtime/core/cmake_install.cmake")
  include("E:/git/mine/loo/looengine/llvmbuild/loo/runtime/ifvk/cmake_install.cmake")
  include("E:/git/mine/loo/looengine/llvmbuild/loo/runtime/vkfg/cmake_install.cmake")

endif()
