
APP_PLATFORM := android-9

APP_OPTIM := release

ifeq ($(BUILD_ARM_HARD_FLOAT),true)
	APP_ABI := armeabi armeabi-v7a-hard x86 mips arm64-v8a x86_64 mips64
else
	APP_ABI := armeabi armeabi-v7a x86 mips arm64-v8a x86_64 mips64
endif

APP_MODULES := libfreetype

