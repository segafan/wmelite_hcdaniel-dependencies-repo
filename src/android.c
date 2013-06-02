
#include "android.h"

#include "SDL_android.h"

#include <android/log.h>

const char* className_wmeliteFunctions = "org/deadcode/wmelite";

static jclass callbackClass;

static JNIEnv *localEnv;

void Java_org_deadcode_wmelite_WMELiteFunctions_nativeInit(JNIEnv* env, jobject o)
{

	callbackClass = (*env)->NewGlobalRef(env, o);

	__android_log_print(ANDROID_LOG_VERBOSE, "org.libsdl.app", "Global ref to WMELITE=%s", (o == NULL) ? "NULL" : "OK");

	// localEnv = env;
}

void android_setLocalEnv(JNIEnv *env)
{
	localEnv = env;
}

void android_getLogFileDirectory(char *buffer, int length)
{
	const char *tmp;

	// get the proper jni env from SDL
	// JNIEnv *env = Android_JNI_GetEnv();
	JNIEnv *env = localEnv;
	jmethodID callbackID = (*env)->GetMethodID(env, callbackClass, "getLogFileDirectory", "()Ljava/lang/String;");
	jstring str = (*env)->CallObjectMethod(env, callbackClass, callbackID);

	tmp = (*env)->GetStringUTFChars(env, str, NULL);

	if (strnlen(tmp, length) < length) {
		strncpy(buffer, tmp, length);
	} else {
		buffer[0] = 0;
	}

	__android_log_print(ANDROID_LOG_VERBOSE, "org.libsdl.app", "android_getLogFileDirectory() returns %s", buffer);

	(*env)->ReleaseStringUTFChars(env, str, tmp);
}

void android_getPrivateFilesPath(char *buffer, int length)
{
	const char *tmp;

	// get the proper jni env from SDL
	// JNIEnv *env = Android_JNI_GetEnv();
	JNIEnv *env = localEnv;
	jmethodID callbackID = (*env)->GetMethodID(env, callbackClass, "getPrivateFilesPath", "()Ljava/lang/String;");
	jstring str = (*env)->CallObjectMethod(env, callbackClass, callbackID);

	tmp = (*env)->GetStringUTFChars(env, str, NULL);

	if (strnlen(tmp, length) < length) {
		strncpy(buffer, tmp, length);
	} else {
		buffer[0] = 0;
	}

	__android_log_print(ANDROID_LOG_VERBOSE, "org.libsdl.app", "android_getPrivateFilesPath() returns %s", buffer);

	(*env)->ReleaseStringUTFChars(env, str, tmp);
}

void android_getDeviceTypeHint(char *buffer, int length)
{
	const char *tmp;

	// get the proper jni env from SDL
	// JNIEnv *env = Android_JNI_GetEnv();
	JNIEnv *env = localEnv;
	jmethodID callbackID = (*env)->GetMethodID(env, callbackClass, "getDeviceTypeHint", "()Ljava/lang/String;");
	jstring str = (*env)->CallObjectMethod(env, callbackClass, callbackID);

	tmp = (*env)->GetStringUTFChars(env, str, NULL);

	if (strnlen(tmp, length) < length) {
		strncpy(buffer, tmp, length);
	} else {
		buffer[0] = 0;
	}

	__android_log_print(ANDROID_LOG_VERBOSE, "org.libsdl.app", "android_getDeviceTypeHint() returns %s", buffer);

	(*env)->ReleaseStringUTFChars(env, str, tmp);
}

void android_getGamePackagePath(char *buffer, int length)
{
	const char *tmp;

	// get the proper jni env from SDL
	// JNIEnv *env = Android_JNI_GetEnv();
	JNIEnv *env = localEnv;
	__android_log_print(ANDROID_LOG_VERBOSE, "org.libsdl.app", "android_getGamePackagePath() env=%s", (env == NULL) ? "NULL" : "OK");

	jmethodID callbackID = (*env)->GetMethodID(env, callbackClass, "getGamePackagePath", "()Ljava/lang/String;");

	__android_log_print(ANDROID_LOG_VERBOSE, "org.libsdl.app", "android_getGamePackagePath() callbackid=ds", callbackID);

	jstring str = (*env)->CallObjectMethod(env, callbackClass, callbackID);

	__android_log_print(ANDROID_LOG_VERBOSE, "org.libsdl.app", "android_getGamePackagePath() jstring=%s", (str == NULL) ? "NULL" : "OK");

	tmp = (*env)->GetStringUTFChars(env, str, NULL);

	if (strnlen(tmp, length) < length) {
		strncpy(buffer, tmp, length);
	} else {
		buffer[0] = 0;
	}

	__android_log_print(ANDROID_LOG_VERBOSE, "org.libsdl.app", "android_getGamePackagePath() returns %s", buffer);

	(*env)->ReleaseStringUTFChars(env, str, tmp);
}

void android_getGameFilePath(char *buffer, int length)
{
	const char *tmp;

	// get the proper jni env from SDL
	// JNIEnv *env = Android_JNI_GetEnv();
	JNIEnv *env = localEnv;
	jmethodID callbackID = (*env)->GetMethodID(env, callbackClass, "getGameFilePath", "()Ljava/lang/String;");
	jstring str = (*env)->CallObjectMethod(env, callbackClass, callbackID);

	tmp = (*env)->GetStringUTFChars(env, str, NULL);

	if (strnlen(tmp, length) < length) {
		strncpy(buffer, tmp, length);
	} else {
		buffer[0] = 0;
	}

	__android_log_print(ANDROID_LOG_VERBOSE, "org.libsdl.app", "android_getGameFilePath() returns %s", buffer);

	(*env)->ReleaseStringUTFChars(env, str, tmp);
}

void android_getFontPath(char *buffer, int length)
{
	const char *tmp;

	// get the proper jni env from SDL
	// JNIEnv *env = Android_JNI_GetEnv();
	JNIEnv *env = localEnv;
	jmethodID callbackID = (*env)->GetMethodID(env, callbackClass, "getFontPath", "()Ljava/lang/String;");
	jstring str = (*env)->CallObjectMethod(env, callbackClass, callbackID);

	tmp = (*env)->GetStringUTFChars(env, str, NULL);

	if (strnlen(tmp, length) < length) {
		strncpy(buffer, tmp, length);
	} else {
		buffer[0] = 0;
	}

	__android_log_print(ANDROID_LOG_VERBOSE, "org.libsdl.app", "android_getFontPath() returns %s", buffer);

	(*env)->ReleaseStringUTFChars(env, str, tmp);
}
