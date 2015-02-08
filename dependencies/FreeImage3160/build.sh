#!/bin/bash
if [ -z "$JENKINS_NICE_BUILD" ]; then
cd jni && ndk-build clean && ndk-build -j8
else
cd jni && ndk-build clean && nice -n 20 ndk-build	
fi

