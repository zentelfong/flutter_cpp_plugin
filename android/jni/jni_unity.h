#pragma once
#include <jni.h>
#include <stdint.h>
#include <assert.h>
#include <stdlib.h>
#include <android/log.h>
#include <string>

#define LOG_TAG "flutter_cpp_plugin"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

std::string jstring2string(JNIEnv* env, jstring jstr);

jstring char2Jstring(JNIEnv* env, const char* pat);

inline jlong jlongFromPointer(void* ptr) {
  // Going through intptr_t to be obvious about the definedness of the
  // conversion from pointer to integral type.  intptr_t to jlong is a standard
  // widening by the static_assert above.
  jlong ret = reinterpret_cast<intptr_t>(ptr);
  assert(reinterpret_cast<void*>(ret) == ptr);
  return ret;
}