#!/bin/bash
cd jni && ndk-build clean && NDK_TOOLCHAIN_VERSION=4.6 ndk-build -j8

