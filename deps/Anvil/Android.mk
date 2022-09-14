LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := Anvil

LOCAL_C_INCLUDES := $(LOCAL_PATH)
LOCAL_C_INCLUDES += $(LOCAL_PATH)/include
LOCAL_C_INCLUDES += $(LOCAL_PATH)/deps
LOCAL_C_INCLUDES += $(LOCAL_PATH)/deps/glslang
LOCAL_C_INCLUDES += $(LOCAL_PATH)/deps/glslang/include

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_C_INCLUDES)

LOCAL_SRC_FILES := \
    src/misc/memalloc_backends/backend_oneshot.cpp \
    src/misc/memalloc_backends/backend_vma.cpp \
    src/misc/base_pipeline_create_info.cpp \
    src/misc/base_pipeline_manager.cpp \
    src/misc/buffer_create_info.cpp \
    src/misc/buffer_view_create_info.cpp \
    src/misc/compute_pipeline_create_info.cpp \
    src/misc/debug.cpp \
    src/misc/debug_marker.cpp \
    src/misc/debug_messenger_create_info.cpp \
    src/misc/descriptor_pool_create_info.cpp \
    src/misc/descriptor_set_create_info.cpp \
    src/misc/device_create_info.cpp \
    src/misc/dummy_window.cpp \
    src/misc/external_handle.cpp \
    src/misc/event_create_info.cpp \
    src/misc/fence_create_info.cpp \
    src/misc/formats.cpp \
    src/misc/fp16.cpp \
    src/misc/framebuffer_create_info.cpp \
    src/misc/graphics_pipeline_create_info.cpp \
    src/misc/image_create_info.cpp \
    src/misc/image_view_create_info.cpp \
    src/misc/instance_create_info.cpp \
    src/misc/io.cpp \
    src/misc/library.cpp \
    src/misc/memory_allocator.cpp \
    src/misc/memory_block_create_info.cpp \
    src/misc/object_tracker.cpp \
    src/misc/page_tracker.cpp \
    src/misc/pools.cpp \
    src/misc/render_pass_create_info.cpp \
    src/misc/rendering_surface_create_info.cpp \
    src/misc/sampler_create_info.cpp \
    src/misc/sampler_ycbcr_conversion_create_info.cpp \
    src/misc/semaphore_create_info.cpp \
    src/misc/shader_module_cache.cpp \
    src/misc/swapchain_create_info.cpp \
    src/misc/time.cpp \
    src/misc/types.cpp \
    src/misc/types_classes.cpp \
    src/misc/types_struct.cpp \
    src/misc/types_utils.cpp \
    src/misc/vulkan.cpp \
    src/misc/window.cpp \
    src/misc/window_android.cpp \
    src/misc/window_factory.cpp \
    src/wrappers/buffer.cpp \
    src/wrappers/buffer_view.cpp \
    src/wrappers/command_buffer.cpp \
    src/wrappers/command_pool.cpp \
    src/wrappers/compute_pipeline_manager.cpp \
    src/wrappers/debug_messenger.cpp \
    src/wrappers/descriptor_pool.cpp \
    src/wrappers/descriptor_set.cpp \
    src/wrappers/descriptor_set_group.cpp \
    src/wrappers/descriptor_set_layout.cpp \
    src/wrappers/descriptor_set_layout_manager.cpp \
    src/wrappers/descriptor_update_template.cpp \
    src/wrappers/device.cpp \
    src/wrappers/event.cpp \
    src/wrappers/fence.cpp \
    src/wrappers/framebuffer.cpp \
    src/wrappers/graphics_pipeline_manager.cpp \
    src/wrappers/image.cpp \
    src/wrappers/image_view.cpp \
    src/wrappers/instance.cpp \
    src/wrappers/memory_block.cpp \
    src/wrappers/physical_device.cpp \
    src/wrappers/pipeline_cache.cpp \
    src/wrappers/pipeline_layout.cpp \
    src/wrappers/pipeline_layout_manager.cpp \
    src/wrappers/query_pool.cpp \
    src/wrappers/queue.cpp \
    src/wrappers/render_pass.cpp \
    src/wrappers/rendering_surface.cpp \
    src/wrappers/sampler.cpp \
    src/wrappers/sampler_ycbcr_conversion.cpp \
    src/wrappers/semaphore.cpp \
    src/wrappers/shader_module.cpp \
    src/wrappers/swapchain.cpp \
    src/misc/glsl_to_spirv.cpp \
    

LOCAL_CXXFLAGS = -g -std=c++11 -Wall
LOCAL_CXXFLAGS += -frtti -fno-exceptions
LOCAL_CXXFLAGS += -fpermissive
LOCAL_CXXFLAGS += -D_DEBUG
#LOCAL_CXXFLAGS += -O3
#LOCAL_CXXFLAGS += -funwind-tables -fvisibility=hidden

LOCAL_CXXFLAGS += -DVK_USE_PLATFORM_ANDROID_KHR

LOCAL_CXXFLAGS += -DANVIL_USE_BUILT_IN_VULKAN_HEADERS
LOCAL_CXXFLAGS += -DANVIL_USE_BUILT_IN_GLSLANG

#building as a static lib

LOCAL_STATIC_LIBRARIES := OSDependent
LOCAL_STATIC_LIBRARIES += OGLCompiler
LOCAL_STATIC_LIBRARIES += HLSL
LOCAL_STATIC_LIBRARIES += glslang
LOCAL_STATIC_LIBRARIES += SPIRV

include $(BUILD_STATIC_LIBRARY)

include $(LOCAL_PATH)/deps/glslang/Android.mk
