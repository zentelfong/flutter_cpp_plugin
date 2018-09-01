LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := flutter_cpp_plugin

LOCAL_SRC_FILES := cpp_plugin_jni.cpp\
	jni_unity.cpp \
    ../../src/json_method_call.cc \
	../../src/json_method_codec.cc \
	../../src/json_plugin.cc \
    ../../src/standard_method_call.cc \
	../../src/standard_method_codec.cc \
	../../src/standard_plugin.cc \
	../../src/standard_value.cc \
	../../src/method_call.cc \
	../../src/method_codec.cc \
	../../src/method_result.cc \
	../../src/plugin.cc \
	../../src/plugin_manager.cc \
	../../src/libjson/json_reader.cpp \
	../../src/libjson/json_value.cpp \
	../../src/libjson/json_writer.cpp \
	../../example/example.cpp \


LOCAL_C_INCLUDES := ../../include

LOCAL_LDLIBS    := -llog

include $(BUILD_SHARED_LIBRARY)
