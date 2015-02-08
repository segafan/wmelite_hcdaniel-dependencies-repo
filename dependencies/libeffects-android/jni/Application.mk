
# Uncomment this if you're using STL in your project
# See CPLUSPLUS-SUPPORT.html in the NDK documentation for more information
# APP_STL := stlport_static 

APP_OPTIM := release

APP_PLATFORM := android-9

ifeq ($(BUILD_ARM_HARD_FLOAT),true)
	APP_ABI := armeabi armeabi-v7a-hard x86 mips arm64-v8a x86_64 mips64
else
	APP_ABI := armeabi armeabi-v7a x86 mips arm64-v8a x86_64 mips64
endif

