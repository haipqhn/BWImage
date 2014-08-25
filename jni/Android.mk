LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_LDLIBS := -llog -ljnigraphics

LOCAL_MODULE    := grayscale
LOCAL_SRC_FILES := grayscale.c 

include $(BUILD_SHARED_LIBRARY)