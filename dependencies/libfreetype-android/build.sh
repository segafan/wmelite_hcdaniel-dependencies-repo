#!/bin/sh
if [ -z "$JENKINS_NICE_BUILD" ]; then
ndk-build NDK_PROJECT_PATH=./ clean && ndk-build NDK_PROJECT_PATH=./ -j8
else
ndk-build NDK_PROJECT_PATH=./ clean && nice -n 20 ndk-build NDK_PROJECT_PATH=./
fi

