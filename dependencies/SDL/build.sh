#!/bin/sh
ndk-build NDK_PROJECT_PATH=./ clean && ndk-build NDK_PROJECT_PATH=./ -j8

