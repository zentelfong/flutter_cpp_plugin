APP_STL := c++_static
APP_ABI := all
APP_PLATFORM := android-22
APP_CPPFLAGS += -std=c++14
APP_CPPFLAGS += -fexceptions
APP_CPPFLAGS += -frtti
APP_LDFLAGS := -latomic