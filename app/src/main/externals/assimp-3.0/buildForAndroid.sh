#!/bin/sh

# Path to Android NDK
export ANDROID_NDK=$CODE/android-ndk-r11c

# Points to the Android SDK
export ANDROID_SDK=$HOME/Android/sdk

# This file must be downloaded from the android-cmake project on github:
# https://github.com/taka-no-me/android-cmake
export ANDROID_STANDALONE_TOOLCHAIN=$CODE/android-cmake/android.toolchain.cmake

# Do not touch these
export PATH=$PATH:$ANDROID_SDK/tools
export PATH=$PATH:$ANDROID_SDK/platform-tools
export PATH=$PATH:$ANDROID_SDK/android-toolchain/bin

# Add additional args here as appropriate
cmake -DCMAKE_TOOLCHAIN_FILE=$ANDROID_STANDALONE_TOOLCHAIN \
      -DANDROID_NDK=$ANDROID_NDK \
      -DCMAKE_BUILD_TYPE=Release \
      -DANDROID_ABI="x86" \
      -DANDROID_NATIVE_API_LEVEL=android-9 \
      -DANDROID_FORCE_ARM_BUILD=TRUE \
      -DCMAKE_INSTALL_PREFIX=install \
      ..

# This is to remove the versioned shared libs in assimp.
# Might be useful for other CMake-based projects, otherwise remove this line.
sed -i s/-soname,libassimp.so.3/-soname,libassimp.so/g code/CMakeFiles/assimp.dir/link.txt

#make -j4
