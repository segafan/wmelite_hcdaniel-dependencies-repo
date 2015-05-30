--- jni/src/core/android/SDL_android.c.orig	2015-05-30 19:13:47.848737902 +0200
+++ jni/src/core/android/SDL_android.c	2015-05-30 19:02:47.484705014 +0200
@@ -414,6 +414,32 @@
     return result;
 }
 
+void Android_JNI_HintCallback(void *userdata, const char *name, const char *oldValue, const char *newValue) {
+    JNIEnv *env = Android_JNI_GetEnv();
+
+    jobject callback = (jobject)userdata;
+   jclass cls = (*env)->GetObjectClass(env, callback);
+    jmethodID method = (*env)->GetMethodID(env, cls, "callback", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
+
+    jstring javaName     = (*env)->NewStringUTF(env, name);
+    jstring javaOldValue = (*env)->NewStringUTF(env, oldValue);
+    jstring javaNewValue = (*env)->NewStringUTF(env, newValue);
+
+    (*env)->CallVoidMethod(env, callback, method, javaName, javaOldValue, javaNewValue);
+
+    (*env)->DeleteLocalRef(env, javaName);
+    (*env)->DeleteLocalRef(env, javaOldValue);
+    (*env)->DeleteLocalRef(env, javaNewValue);
+}
+
+void Java_org_libsdl_app_SDLActivity_nativeAddHintCallback(JNIEnv* env, jclass cls, jstring name, jobject callback) {
+    const char *utfname = (*env)->GetStringUTFChars(env, name, NULL);
+
+    SDL_AddHintCallback(utfname, Android_JNI_HintCallback, (*env)->NewGlobalRef(env, callback));
+
+    (*env)->ReleaseStringUTFChars(env, name, utfname);    
+}
+
 /*******************************************************************************
              Functions called by SDL into Java
 *******************************************************************************/
