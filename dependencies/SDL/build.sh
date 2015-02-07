#!/bin/sh
ndk-build NDK_PROJECT_PATH=./ clean && NDK_TOOLCHAIN_VERSION=4.6 ndk-build NDK_PROJECT_PATH=./ -j8

