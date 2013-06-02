
#include "android.h"

char* android_getLogFileDirectory()
{
	// FIXME create a Java callback to retrieve the path
	return "/mnt/sdcard/";
}

char* android_getPrivateFilesPath()
{
	// FIXME create a Java callback to retrieve the path
	return "/data/data/org.libsdl.app/files/";
}

char* android_getDeviceTypeHint()
{
	// FIXME ask Android about screen size and decide
	return "tablet";
}

char* android_getGamePackagePath()
{
	// FIXME create a Java callback to retrieve the path
	return "/mnt/sdcard/";
}

char* android_getGameFilePath()
{
	// FIXME create a Java callback to retrieve the path
	return "/mnt/sdcard/";
}

char* android_getFontPath()
{
	// FIXME create a Java callback to retrieve the path
	return "/data/data/org.libsdl.app/assets/fonts/";
}
