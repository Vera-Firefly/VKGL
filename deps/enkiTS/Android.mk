LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := enkiTS

LOCAL_C_INCLUDES := $(LOCAL_PATH)/src

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_C_INCLUDES)

MY_FILES_PATH := \
	$(LOCAL_PATH)/src

MY_FILES_SUFFIX := %.cpp

My_All_Files := $(foreach src_path,$(MY_FILES_PATH), $(shell find "$(src_path)" -type f) ) 
My_All_Files := $(My_All_Files:$(MY_CPP_PATH)/./%=$(MY_CPP_PATH)%)

MY_SRC_LIST  := $(filter $(MY_FILES_SUFFIX),$(My_All_Files)) 
MY_SRC_LIST  := $(MY_SRC_LIST:$(LOCAL_PATH)/%=%)

LOCAL_SRC_FILES := $(MY_SRC_LIST)


LOCAL_CXXFLAGS = -g -std=c++11 -Wall

#building as a static lib

include $(BUILD_STATIC_LIBRARY)
