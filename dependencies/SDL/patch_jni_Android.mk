--- jni/Android.mk.orig	2015-05-30 20:04:21.904889007 +0200
+++ jni/Android.mk	2015-03-28 11:04:08.271640063 +0100
@@ -12,6 +12,8 @@
 
 LOCAL_C_INCLUDES := $(LOCAL_PATH)/include
 
+# LOCAL_ARM_MODE := arm
+
 LOCAL_EXPORT_C_INCLUDES := $(LOCAL_C_INCLUDES)
 
 LOCAL_SRC_FILES := \
@@ -43,27 +45,11 @@
 	$(wildcard $(LOCAL_PATH)/src/timer/*.c) \
 	$(wildcard $(LOCAL_PATH)/src/timer/unix/*.c) \
 	$(wildcard $(LOCAL_PATH)/src/video/*.c) \
-	$(wildcard $(LOCAL_PATH)/src/video/android/*.c) \
-	$(wildcard $(LOCAL_PATH)/src/test/*.c))
+	$(wildcard $(LOCAL_PATH)/src/video/android/*.c))
+#	$(wildcard $(LOCAL_PATH)/src/test/*.c))
 
 LOCAL_CFLAGS += -DGL_GLEXT_PROTOTYPES
 LOCAL_LDLIBS := -ldl -lGLESv1_CM -lGLESv2 -llog -landroid
 
 include $(BUILD_SHARED_LIBRARY)
 
-###########################
-#
-# SDL static library
-#
-###########################
-
-LOCAL_MODULE := SDL2_static
-
-LOCAL_MODULE_FILENAME := libSDL2
-
-LOCAL_SRC_FILES += $(subst $(LOCAL_PATH)/,,$(LOCAL_PATH)/src/main/android/SDL_android_main.c)
-
-LOCAL_LDLIBS := 
-LOCAL_EXPORT_LDLIBS := -Wl,--undefined=Java_org_libsdl_app_SDLActivity_nativeInit -ldl -lGLESv1_CM -lGLESv2 -llog -landroid
-
-include $(BUILD_STATIC_LIBRARY)
