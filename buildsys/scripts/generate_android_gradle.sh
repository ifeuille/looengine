#!/bin/bash
# Copyright (c) 2019, Arm Limited and Contributors
#
# SPDX-License-Identifier: MIT
#
# Permission is hereby granted, free of charge,
# to any person obtaining a copy of this software and associated documentation files (the "Software"),
# to deal in the Software without restriction, including without limitation the rights to
# use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
# and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
# INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
# IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
# WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#


ROOT_DIR="$(cd "$(dirname "$0")"; pwd)/../.."

if [ "$#" -ne 1 ]; then
	BUILD_DIR=$ROOT_DIR/android_gradle
else
	BUILD_DIR="$1"
fi

cmake -DPROJECT_NAME="looengine" \
	  -DANDROID_API=24 \
	  -DARCH_ABI="arm64-v8a;armeabi-v7a" \
	  -DANDROID_MANIFEST=$ROOT_DIR/loo/thirdpart/android/AndroidManifest.xml \
	  -DJAVA_DIRS=$ROOT_DIR/loo/thirdpart/android/java \
	  -DRES_DIRS=$ROOT_DIR/loo/thirdpart/android/res \
	  -DOUTPUT_DIR=$BUILD_DIR \
	  -DASSET_DIRS="" \
	  -DJNI_LIBS_DIRS="" \
	  -DNATIVE_SCRIPT=$ROOT_DIR/CMakeLists.txt \
	  -DNATIVE_ARGUMENTS="ANDROID_TOOLCHAIN=clang;ANDROID_STL=c++_static" \
	  -P $ROOT_DIR/buildsys/cmake/create_gradle_project.cmake
