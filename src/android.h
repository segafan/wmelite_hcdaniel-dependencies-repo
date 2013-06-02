#ifndef __ANDROID_H__
#define __ANDROID_H__

/* This is for C++ and does no harm in C */
#ifdef __cplusplus
extern "C" {
#endif

char* android_getLogFileDirectory(void);

char* android_getPrivateFilesPath(void);

char* android_getDeviceTypeHint(void);

char* android_getGamePackagePath(void);

char* android_getGameFilePath(void);

char* android_getFontPath(void);

#ifdef __cplusplus
}
#endif

#endif // __ANDROID_H__
