--- jni/include/SDL_hints.h.orig	2015-05-30 19:12:24.124733732 +0200
+++ jni/include/SDL_hints.h	2015-05-30 19:09:19.640724544 +0200
@@ -535,6 +535,11 @@
  */
 #define SDL_HINT_ANDROID_APK_EXPANSION_PATCH_FILE_VERSION "SDL_ANDROID_APK_EXPANSION_PATCH_FILE_VERSION"
 
+ /**
+ * \brief If set to 1, sets UI_LOW_PROFILE setting for SDLActivity
+ */
+#define SDL_HINT_ANDROID_USE_UI_LOW_PROFILE "SDL_ANDROID_USE_UI_LOW_PROFILE"
+
 /**
  * \brief A variable to control whether certain IMEs should handle text editing internally instead of sending SDL_TEXTEDITING events.
  *
