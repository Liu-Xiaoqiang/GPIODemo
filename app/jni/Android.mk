# Android.mk

LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE    := chipsee-hardware
LOCAL_SRC_FILES := chipsee-hardware.c

include $(BUILD_SHARED_LIBRARY)
