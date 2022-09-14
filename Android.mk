LOCAL_PATH := $(call my-dir)

###########################
#
# GL shared library
#
###########################

include $(CLEAR_VARS)

LOCAL_MODULE := VKGL32

LOCAL_C_INCLUDES := $(LOCAL_PATH)/include
LOCAL_C_INCLUDES += $(LOCAL_PATH)/deps
LOCAL_C_INCLUDES += $(LOCAL_PATH)/deps/Anvil/include
LOCAL_C_INCLUDES += $(LOCAL_PATH)/deps/Anvil/deps/glslang
LOCAL_C_INCLUDES += $(LOCAL_PATH)/deps/Anvil/deps/glslang/include
LOCAL_C_INCLUDES += $(LOCAL_PATH)/include/Khronos
LOCAL_C_INCLUDES += $(LOCAL_PATH)/include/Khronos/GL
LOCAL_C_INCLUDES += $(LOCAL_PATH)/include/Khronos/KHR

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_C_INCLUDES)

MY_FILES_PATH := \
	$(LOCAL_PATH)/src/OpenGL \
	$(LOCAL_PATH)/src/Common \

MY_FILES_SUFFIX := %.cpp

My_All_Files := $(foreach src_path,$(MY_FILES_PATH), $(shell find "$(src_path)" -type f) ) 
My_All_Files := $(My_All_Files:$(MY_CPP_PATH)/./%=$(MY_CPP_PATH)%)

MY_SRC_LIST  := $(filter $(MY_FILES_SUFFIX),$(My_All_Files)) 
MY_SRC_LIST  := $(MY_SRC_LIST:$(LOCAL_PATH)/%=%)

LOCAL_SRC_FILES := $(MY_SRC_LIST)


LOCAL_CXXFLAGS = -g -std=c++17 -Wall
LOCAL_CXXFLAGS += -frtti -fno-exceptions
LOCAL_CXXFLAGS += -fdeclspec
LOCAL_CXXFLAGS += -fms-extensions
#LOCAL_CXXFLAGS += -O3
LOCAL_CXXFLAGS += -funwind-tables -fvisibility=hidden

LOCAL_CXXFLAGS += -DVK_USE_PLATFORM_ANDROID_KHR

LOCAL_LDLIBS := -ldl
#building as a shared lib

LOCAL_STATIC_LIBRARIES := Anvil

LOCAL_STATIC_LIBRARIES += OSDependent
LOCAL_STATIC_LIBRARIES += OGLCompiler
LOCAL_STATIC_LIBRARIES += HLSL
LOCAL_STATIC_LIBRARIES += glslang
LOCAL_STATIC_LIBRARIES += SPIRV

LOCAL_STATIC_LIBRARIES += enkiTS

include $(BUILD_SHARED_LIBRARY)


###########################
#
# EGL shared library
#
###########################

include $(CLEAR_VARS)

LOCAL_MODULE := VKGL32_EGL

LOCAL_C_INCLUDES := $(LOCAL_PATH)/include
LOCAL_C_INCLUDES += $(LOCAL_PATH)/deps
LOCAL_C_INCLUDES += $(LOCAL_PATH)/deps/Anvil/include
LOCAL_C_INCLUDES += $(LOCAL_PATH)/deps/Anvil/deps/glslang
LOCAL_C_INCLUDES += $(LOCAL_PATH)/deps/Anvil/deps/glslang/include
LOCAL_C_INCLUDES += $(LOCAL_PATH)/include/Khronos
LOCAL_C_INCLUDES += $(LOCAL_PATH)/include/Khronos/GL
LOCAL_C_INCLUDES += $(LOCAL_PATH)/include/Khronos/KHR

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_C_INCLUDES)

MY_FILES_PATH := \
	$(LOCAL_PATH)/src/EGL \
	$(LOCAL_PATH)/src/Common \

MY_FILES_SUFFIX := %.cpp

My_All_Files := $(foreach src_path,$(MY_FILES_PATH), $(shell find "$(src_path)" -type f) ) 
My_All_Files := $(My_All_Files:$(MY_CPP_PATH)/./%=$(MY_CPP_PATH)%)

MY_SRC_LIST  := $(filter $(MY_FILES_SUFFIX),$(My_All_Files)) 
MY_SRC_LIST  := $(MY_SRC_LIST:$(LOCAL_PATH)/%=%)

LOCAL_SRC_FILES := $(MY_SRC_LIST)


LOCAL_CXXFLAGS = -g -std=c++11 -Wall
#LOCAL_CXXFLAGS += -O3
LOCAL_CXXFLAGS += -funwind-tables -fvisibility=hidden

LOCAL_CXXFLAGS += -DVK_USE_PLATFORM_ANDROID_KHR

LOCAL_LDLIBS := -ldl -landroid
#building as a shared lib

include $(BUILD_SHARED_LIBRARY)

include $(LOCAL_PATH)/deps/Anvil/Android.mk \
		$(LOCAL_PATH)/deps/enkiTS/Android.mk
