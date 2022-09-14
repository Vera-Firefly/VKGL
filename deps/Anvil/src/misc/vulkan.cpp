//
// Copyright (c) 2017-2018 Advanced Micro Devices, Inc. All rights reserved.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
#define ANVIL_VULKAN_CPP

#include "misc/library.h"
#include "misc/vulkan.h"
#include <mutex>

/* For Anvil builds which statically link with Vulkan DLL,  the pointers are set to the system-provided func ptrs.
 * For Anvil builds which link dynamically with Vulkan DLL, the pointers are initialized at Anvil::Instance creation time.
 */

#if !defined(ANVIL_LINK_STATICALLY_WITH_VULKAN_LIB)
    PFN_vkCreateInstance                                Anvil::Vulkan::vkCreateInstance                               = nullptr;
    PFN_vkDestroyInstance                               Anvil::Vulkan::vkDestroyInstance                              = nullptr;
    PFN_vkEnumeratePhysicalDevices                      Anvil::Vulkan::vkEnumeratePhysicalDevices                     = nullptr;
    PFN_vkGetPhysicalDeviceFeatures                     Anvil::Vulkan::vkGetPhysicalDeviceFeatures                    = nullptr;
    PFN_vkGetPhysicalDeviceFormatProperties             Anvil::Vulkan::vkGetPhysicalDeviceFormatProperties            = nullptr;
    PFN_vkGetPhysicalDeviceImageFormatProperties        Anvil::Vulkan::vkGetPhysicalDeviceImageFormatProperties       = nullptr;
    PFN_vkGetPhysicalDeviceProperties                   Anvil::Vulkan::vkGetPhysicalDeviceProperties                  = nullptr;
    PFN_vkGetPhysicalDeviceQueueFamilyProperties        Anvil::Vulkan::vkGetPhysicalDeviceQueueFamilyProperties       = nullptr;
    PFN_vkGetPhysicalDeviceMemoryProperties             Anvil::Vulkan::vkGetPhysicalDeviceMemoryProperties            = nullptr;
    PFN_vkGetInstanceProcAddr                           Anvil::Vulkan::vkGetInstanceProcAddr                          = nullptr;
    PFN_vkGetDeviceProcAddr                             Anvil::Vulkan::vkGetDeviceProcAddr                            = nullptr;
    PFN_vkCreateDevice                                  Anvil::Vulkan::vkCreateDevice                                 = nullptr;
    PFN_vkDestroyDevice                                 Anvil::Vulkan::vkDestroyDevice                                = nullptr;
    PFN_vkEnumerateInstanceExtensionProperties          Anvil::Vulkan::vkEnumerateInstanceExtensionProperties         = nullptr;
    PFN_vkEnumerateDeviceExtensionProperties            Anvil::Vulkan::vkEnumerateDeviceExtensionProperties           = nullptr;
    PFN_vkEnumerateInstanceLayerProperties              Anvil::Vulkan::vkEnumerateInstanceLayerProperties             = nullptr;
    PFN_vkEnumerateDeviceLayerProperties                Anvil::Vulkan::vkEnumerateDeviceLayerProperties               = nullptr;
    PFN_vkGetDeviceQueue                                Anvil::Vulkan::vkGetDeviceQueue                               = nullptr;
    PFN_vkQueueSubmit                                   Anvil::Vulkan::vkQueueSubmit                                  = nullptr;
    PFN_vkQueueWaitIdle                                 Anvil::Vulkan::vkQueueWaitIdle                                = nullptr;
    PFN_vkDeviceWaitIdle                                Anvil::Vulkan::vkDeviceWaitIdle                               = nullptr;
    PFN_vkAllocateMemory                                Anvil::Vulkan::vkAllocateMemory                               = nullptr;
    PFN_vkFreeMemory                                    Anvil::Vulkan::vkFreeMemory                                   = nullptr;
    PFN_vkMapMemory                                     Anvil::Vulkan::vkMapMemory                                    = nullptr;
    PFN_vkUnmapMemory                                   Anvil::Vulkan::vkUnmapMemory                                  = nullptr;
    PFN_vkFlushMappedMemoryRanges                       Anvil::Vulkan::vkFlushMappedMemoryRanges                      = nullptr;
    PFN_vkInvalidateMappedMemoryRanges                  Anvil::Vulkan::vkInvalidateMappedMemoryRanges                 = nullptr;
    PFN_vkGetDeviceMemoryCommitment                     Anvil::Vulkan::vkGetDeviceMemoryCommitment                    = nullptr;
    PFN_vkBindBufferMemory                              Anvil::Vulkan::vkBindBufferMemory                             = nullptr;
    PFN_vkBindImageMemory                               Anvil::Vulkan::vkBindImageMemory                              = nullptr;
    PFN_vkGetBufferMemoryRequirements                   Anvil::Vulkan::vkGetBufferMemoryRequirements                  = nullptr;
    PFN_vkGetImageMemoryRequirements                    Anvil::Vulkan::vkGetImageMemoryRequirements                   = nullptr;
    PFN_vkGetImageSparseMemoryRequirements              Anvil::Vulkan::vkGetImageSparseMemoryRequirements             = nullptr;
    PFN_vkGetPhysicalDeviceSparseImageFormatProperties  Anvil::Vulkan::vkGetPhysicalDeviceSparseImageFormatProperties = nullptr;
    PFN_vkQueueBindSparse                               Anvil::Vulkan::vkQueueBindSparse                              = nullptr;
    PFN_vkCreateFence                                   Anvil::Vulkan::vkCreateFence                                  = nullptr;
    PFN_vkDestroyFence                                  Anvil::Vulkan::vkDestroyFence                                 = nullptr;
    PFN_vkResetFences                                   Anvil::Vulkan::vkResetFences                                  = nullptr;
    PFN_vkGetFenceStatus                                Anvil::Vulkan::vkGetFenceStatus                               = nullptr;
    PFN_vkWaitForFences                                 Anvil::Vulkan::vkWaitForFences                                = nullptr;
    PFN_vkCreateSemaphore                               Anvil::Vulkan::vkCreateSemaphore                              = nullptr;
    PFN_vkDestroySemaphore                              Anvil::Vulkan::vkDestroySemaphore                             = nullptr;
    PFN_vkCreateEvent                                   Anvil::Vulkan::vkCreateEvent                                  = nullptr;
    PFN_vkDestroyEvent                                  Anvil::Vulkan::vkDestroyEvent                                 = nullptr;
    PFN_vkGetEventStatus                                Anvil::Vulkan::vkGetEventStatus                               = nullptr;
    PFN_vkSetEvent                                      Anvil::Vulkan::vkSetEvent                                     = nullptr;
    PFN_vkResetEvent                                    Anvil::Vulkan::vkResetEvent                                   = nullptr;
    PFN_vkCreateQueryPool                               Anvil::Vulkan::vkCreateQueryPool                              = nullptr;
    PFN_vkDestroyQueryPool                              Anvil::Vulkan::vkDestroyQueryPool                             = nullptr;
    PFN_vkGetQueryPoolResults                           Anvil::Vulkan::vkGetQueryPoolResults                          = nullptr;
    PFN_vkCreateBuffer                                  Anvil::Vulkan::vkCreateBuffer                                 = nullptr;
    PFN_vkDestroyBuffer                                 Anvil::Vulkan::vkDestroyBuffer                                = nullptr;
    PFN_vkCreateBufferView                              Anvil::Vulkan::vkCreateBufferView                             = nullptr;
    PFN_vkDestroyBufferView                             Anvil::Vulkan::vkDestroyBufferView                            = nullptr;
    PFN_vkCreateImage                                   Anvil::Vulkan::vkCreateImage                                  = nullptr;
    PFN_vkDestroyImage                                  Anvil::Vulkan::vkDestroyImage                                 = nullptr;
    PFN_vkGetImageSubresourceLayout                     Anvil::Vulkan::vkGetImageSubresourceLayout                    = nullptr;
    PFN_vkCreateImageView                               Anvil::Vulkan::vkCreateImageView                              = nullptr;
    PFN_vkDestroyImageView                              Anvil::Vulkan::vkDestroyImageView                             = nullptr;
    PFN_vkCreateShaderModule                            Anvil::Vulkan::vkCreateShaderModule                           = nullptr;
    PFN_vkDestroyShaderModule                           Anvil::Vulkan::vkDestroyShaderModule                          = nullptr;
    PFN_vkCreatePipelineCache                           Anvil::Vulkan::vkCreatePipelineCache                          = nullptr;
    PFN_vkDestroyPipelineCache                          Anvil::Vulkan::vkDestroyPipelineCache                         = nullptr;
    PFN_vkGetPipelineCacheData                          Anvil::Vulkan::vkGetPipelineCacheData                         = nullptr;
    PFN_vkMergePipelineCaches                           Anvil::Vulkan::vkMergePipelineCaches                          = nullptr;
    PFN_vkCreateGraphicsPipelines                       Anvil::Vulkan::vkCreateGraphicsPipelines                      = nullptr;
    PFN_vkCreateComputePipelines                        Anvil::Vulkan::vkCreateComputePipelines                       = nullptr;
    PFN_vkDestroyPipeline                               Anvil::Vulkan::vkDestroyPipeline                              = nullptr;
    PFN_vkCreatePipelineLayout                          Anvil::Vulkan::vkCreatePipelineLayout                         = nullptr;
    PFN_vkDestroyPipelineLayout                         Anvil::Vulkan::vkDestroyPipelineLayout                        = nullptr;
    PFN_vkCreateSampler                                 Anvil::Vulkan::vkCreateSampler                                = nullptr;
    PFN_vkDestroySampler                                Anvil::Vulkan::vkDestroySampler                               = nullptr;
    PFN_vkCreateDescriptorSetLayout                     Anvil::Vulkan::vkCreateDescriptorSetLayout                    = nullptr;
    PFN_vkDestroyDescriptorSetLayout                    Anvil::Vulkan::vkDestroyDescriptorSetLayout                   = nullptr;
    PFN_vkCreateDescriptorPool                          Anvil::Vulkan::vkCreateDescriptorPool                         = nullptr;
    PFN_vkDestroyDescriptorPool                         Anvil::Vulkan::vkDestroyDescriptorPool                        = nullptr;
    PFN_vkResetDescriptorPool                           Anvil::Vulkan::vkResetDescriptorPool                          = nullptr;
    PFN_vkAllocateDescriptorSets                        Anvil::Vulkan::vkAllocateDescriptorSets                       = nullptr;
    PFN_vkFreeDescriptorSets                            Anvil::Vulkan::vkFreeDescriptorSets                           = nullptr;
    PFN_vkUpdateDescriptorSets                          Anvil::Vulkan::vkUpdateDescriptorSets                         = nullptr;
    PFN_vkCreateFramebuffer                             Anvil::Vulkan::vkCreateFramebuffer                            = nullptr;
    PFN_vkDestroyFramebuffer                            Anvil::Vulkan::vkDestroyFramebuffer                           = nullptr;
    PFN_vkCreateRenderPass                              Anvil::Vulkan::vkCreateRenderPass                             = nullptr;
    PFN_vkDestroyRenderPass                             Anvil::Vulkan::vkDestroyRenderPass                            = nullptr;
    PFN_vkGetRenderAreaGranularity                      Anvil::Vulkan::vkGetRenderAreaGranularity                     = nullptr;
    PFN_vkCreateCommandPool                             Anvil::Vulkan::vkCreateCommandPool                            = nullptr;
    PFN_vkDestroyCommandPool                            Anvil::Vulkan::vkDestroyCommandPool                           = nullptr;
    PFN_vkResetCommandPool                              Anvil::Vulkan::vkResetCommandPool                             = nullptr;
    PFN_vkAllocateCommandBuffers                        Anvil::Vulkan::vkAllocateCommandBuffers                       = nullptr;
    PFN_vkFreeCommandBuffers                            Anvil::Vulkan::vkFreeCommandBuffers                           = nullptr;
    PFN_vkBeginCommandBuffer                            Anvil::Vulkan::vkBeginCommandBuffer                           = nullptr;
    PFN_vkEndCommandBuffer                              Anvil::Vulkan::vkEndCommandBuffer                             = nullptr;
    PFN_vkResetCommandBuffer                            Anvil::Vulkan::vkResetCommandBuffer                           = nullptr;
    PFN_vkCmdBindPipeline                               Anvil::Vulkan::vkCmdBindPipeline                              = nullptr;
    PFN_vkCmdSetViewport                                Anvil::Vulkan::vkCmdSetViewport                               = nullptr;
    PFN_vkCmdSetScissor                                 Anvil::Vulkan::vkCmdSetScissor                                = nullptr;
    PFN_vkCmdSetLineWidth                               Anvil::Vulkan::vkCmdSetLineWidth                              = nullptr;
    PFN_vkCmdSetDepthBias                               Anvil::Vulkan::vkCmdSetDepthBias                              = nullptr;
    PFN_vkCmdSetBlendConstants                          Anvil::Vulkan::vkCmdSetBlendConstants                         = nullptr;
    PFN_vkCmdSetDepthBounds                             Anvil::Vulkan::vkCmdSetDepthBounds                            = nullptr;
    PFN_vkCmdSetStencilCompareMask                      Anvil::Vulkan::vkCmdSetStencilCompareMask                     = nullptr;
    PFN_vkCmdSetStencilWriteMask                        Anvil::Vulkan::vkCmdSetStencilWriteMask                       = nullptr;
    PFN_vkCmdSetStencilReference                        Anvil::Vulkan::vkCmdSetStencilReference                       = nullptr;
    PFN_vkCmdBindDescriptorSets                         Anvil::Vulkan::vkCmdBindDescriptorSets                        = nullptr;
    PFN_vkCmdBindIndexBuffer                            Anvil::Vulkan::vkCmdBindIndexBuffer                           = nullptr;
    PFN_vkCmdBindVertexBuffers                          Anvil::Vulkan::vkCmdBindVertexBuffers                         = nullptr;
    PFN_vkCmdDraw                                       Anvil::Vulkan::vkCmdDraw                                      = nullptr;
    PFN_vkCmdDrawIndexed                                Anvil::Vulkan::vkCmdDrawIndexed                               = nullptr;
    PFN_vkCmdDrawIndirect                               Anvil::Vulkan::vkCmdDrawIndirect                              = nullptr;
    PFN_vkCmdDrawIndexedIndirect                        Anvil::Vulkan::vkCmdDrawIndexedIndirect                       = nullptr;
    PFN_vkCmdDispatch                                   Anvil::Vulkan::vkCmdDispatch                                  = nullptr;
    PFN_vkCmdDispatchIndirect                           Anvil::Vulkan::vkCmdDispatchIndirect                          = nullptr;
    PFN_vkCmdCopyBuffer                                 Anvil::Vulkan::vkCmdCopyBuffer                                = nullptr;
    PFN_vkCmdCopyImage                                  Anvil::Vulkan::vkCmdCopyImage                                 = nullptr;
    PFN_vkCmdBlitImage                                  Anvil::Vulkan::vkCmdBlitImage                                 = nullptr;
    PFN_vkCmdCopyBufferToImage                          Anvil::Vulkan::vkCmdCopyBufferToImage                         = nullptr;
    PFN_vkCmdCopyImageToBuffer                          Anvil::Vulkan::vkCmdCopyImageToBuffer                         = nullptr;
    PFN_vkCmdUpdateBuffer                               Anvil::Vulkan::vkCmdUpdateBuffer                              = nullptr;
    PFN_vkCmdFillBuffer                                 Anvil::Vulkan::vkCmdFillBuffer                                = nullptr;
    PFN_vkCmdClearColorImage                            Anvil::Vulkan::vkCmdClearColorImage                           = nullptr;
    PFN_vkCmdClearDepthStencilImage                     Anvil::Vulkan::vkCmdClearDepthStencilImage                    = nullptr;
    PFN_vkCmdClearAttachments                           Anvil::Vulkan::vkCmdClearAttachments                          = nullptr;
    PFN_vkCmdResolveImage                               Anvil::Vulkan::vkCmdResolveImage                              = nullptr;
    PFN_vkCmdSetEvent                                   Anvil::Vulkan::vkCmdSetEvent                                  = nullptr;
    PFN_vkCmdResetEvent                                 Anvil::Vulkan::vkCmdResetEvent                                = nullptr;
    PFN_vkCmdWaitEvents                                 Anvil::Vulkan::vkCmdWaitEvents                                = nullptr;
    PFN_vkCmdPipelineBarrier                            Anvil::Vulkan::vkCmdPipelineBarrier                           = nullptr;
    PFN_vkCmdBeginQuery                                 Anvil::Vulkan::vkCmdBeginQuery                                = nullptr;
    PFN_vkCmdEndQuery                                   Anvil::Vulkan::vkCmdEndQuery                                  = nullptr;
    PFN_vkCmdResetQueryPool                             Anvil::Vulkan::vkCmdResetQueryPool                            = nullptr;
    PFN_vkCmdWriteTimestamp                             Anvil::Vulkan::vkCmdWriteTimestamp                            = nullptr;
    PFN_vkCmdCopyQueryPoolResults                       Anvil::Vulkan::vkCmdCopyQueryPoolResults                      = nullptr;
    PFN_vkCmdPushConstants                              Anvil::Vulkan::vkCmdPushConstants                             = nullptr;
    PFN_vkCmdBeginRenderPass                            Anvil::Vulkan::vkCmdBeginRenderPass                           = nullptr;
    PFN_vkCmdNextSubpass                                Anvil::Vulkan::vkCmdNextSubpass                               = nullptr;
    PFN_vkCmdEndRenderPass                              Anvil::Vulkan::vkCmdEndRenderPass                             = nullptr;
    PFN_vkCmdExecuteCommands                            Anvil::Vulkan::vkCmdExecuteCommands                           = nullptr;

    PFN_vkBindBufferMemory2                             Anvil::Vulkan::vkBindBufferMemory2                             = nullptr;
    PFN_vkBindImageMemory2                              Anvil::Vulkan::vkBindImageMemory2                              = nullptr;
    PFN_vkCmdDispatchBase                               Anvil::Vulkan::vkCmdDispatchBase                               = nullptr;
    PFN_vkCmdSetDeviceMask                              Anvil::Vulkan::vkCmdSetDeviceMask                              = nullptr;
    PFN_vkCreateDescriptorUpdateTemplate                Anvil::Vulkan::vkCreateDescriptorUpdateTemplate                = nullptr;
    PFN_vkCreateSamplerYcbcrConversion                  Anvil::Vulkan::vkCreateSamplerYcbcrConversion                  = nullptr;
    PFN_vkDestroyDescriptorUpdateTemplate               Anvil::Vulkan::vkDestroyDescriptorUpdateTemplate               = nullptr;
    PFN_vkDestroySamplerYcbcrConversion                 Anvil::Vulkan::vkDestroySamplerYcbcrConversion                 = nullptr;
    PFN_vkEnumerateInstanceVersion                      Anvil::Vulkan::vkEnumerateInstanceVersion                      = nullptr;
    PFN_vkEnumeratePhysicalDeviceGroups                 Anvil::Vulkan::vkEnumeratePhysicalDeviceGroups                 = nullptr;
    PFN_vkGetBufferMemoryRequirements2                  Anvil::Vulkan::vkGetBufferMemoryRequirements2                  = nullptr;
    PFN_vkGetDescriptorSetLayoutSupport                 Anvil::Vulkan::vkGetDescriptorSetLayoutSupport                 = nullptr;
    PFN_vkGetDeviceGroupPeerMemoryFeatures              Anvil::Vulkan::vkGetDeviceGroupPeerMemoryFeatures              = nullptr;
    PFN_vkGetDeviceQueue2                               Anvil::Vulkan::vkGetDeviceQueue2                               = nullptr;
    PFN_vkGetImageMemoryRequirements2                   Anvil::Vulkan::vkGetImageMemoryRequirements2                   = nullptr;
    PFN_vkGetImageSparseMemoryRequirements2             Anvil::Vulkan::vkGetImageSparseMemoryRequirements2             = nullptr;
    PFN_vkGetPhysicalDeviceExternalBufferProperties     Anvil::Vulkan::vkGetPhysicalDeviceExternalBufferProperties     = nullptr;
    PFN_vkGetPhysicalDeviceExternalFenceProperties      Anvil::Vulkan::vkGetPhysicalDeviceExternalFenceProperties      = nullptr;
    PFN_vkGetPhysicalDeviceExternalSemaphoreProperties  Anvil::Vulkan::vkGetPhysicalDeviceExternalSemaphoreProperties  = nullptr;
    PFN_vkGetPhysicalDeviceFeatures2                    Anvil::Vulkan::vkGetPhysicalDeviceFeatures2                    = nullptr;
    PFN_vkGetPhysicalDeviceFormatProperties2            Anvil::Vulkan::vkGetPhysicalDeviceFormatProperties2            = nullptr;
    PFN_vkGetPhysicalDeviceImageFormatProperties2       Anvil::Vulkan::vkGetPhysicalDeviceImageFormatProperties2       = nullptr;
    PFN_vkGetPhysicalDeviceMemoryProperties2            Anvil::Vulkan::vkGetPhysicalDeviceMemoryProperties2            = nullptr;
    PFN_vkGetPhysicalDeviceProperties2                  Anvil::Vulkan::vkGetPhysicalDeviceProperties2                  = nullptr;
    PFN_vkGetPhysicalDeviceQueueFamilyProperties2       Anvil::Vulkan::vkGetPhysicalDeviceQueueFamilyProperties2       = nullptr;
    PFN_vkGetPhysicalDeviceSparseImageFormatProperties2 Anvil::Vulkan::vkGetPhysicalDeviceSparseImageFormatProperties2 = nullptr;
    PFN_vkTrimCommandPool                               Anvil::Vulkan::vkTrimCommandPool                               = nullptr;
    PFN_vkUpdateDescriptorSetWithTemplate               Anvil::Vulkan::vkUpdateDescriptorSetWithTemplate               = nullptr;

#else
    PFN_vkCreateInstance                                Anvil::Vulkan::vkCreateInstance                               = ::vkCreateInstance;
    PFN_vkDestroyInstance                               Anvil::Vulkan::vkDestroyInstance                              = ::vkDestroyInstance;
    PFN_vkEnumeratePhysicalDevices                      Anvil::Vulkan::vkEnumeratePhysicalDevices                     = ::vkEnumeratePhysicalDevices;
    PFN_vkGetPhysicalDeviceFeatures                     Anvil::Vulkan::vkGetPhysicalDeviceFeatures                    = ::vkGetPhysicalDeviceFeatures;
    PFN_vkGetPhysicalDeviceFormatProperties             Anvil::Vulkan::vkGetPhysicalDeviceFormatProperties            = ::vkGetPhysicalDeviceFormatProperties;
    PFN_vkGetPhysicalDeviceImageFormatProperties        Anvil::Vulkan::vkGetPhysicalDeviceImageFormatProperties       = ::vkGetPhysicalDeviceImageFormatProperties;
    PFN_vkGetPhysicalDeviceProperties                   Anvil::Vulkan::vkGetPhysicalDeviceProperties                  = ::vkGetPhysicalDeviceProperties;
    PFN_vkGetPhysicalDeviceQueueFamilyProperties        Anvil::Vulkan::vkGetPhysicalDeviceQueueFamilyProperties       = ::vkGetPhysicalDeviceQueueFamilyProperties;
    PFN_vkGetPhysicalDeviceMemoryProperties             Anvil::Vulkan::vkGetPhysicalDeviceMemoryProperties            = ::vkGetPhysicalDeviceMemoryProperties;
    PFN_vkGetInstanceProcAddr                           Anvil::Vulkan::vkGetInstanceProcAddr                          = ::vkGetInstanceProcAddr;
    PFN_vkGetDeviceProcAddr                             Anvil::Vulkan::vkGetDeviceProcAddr                            = ::vkGetDeviceProcAddr;
    PFN_vkCreateDevice                                  Anvil::Vulkan::vkCreateDevice                                 = ::vkCreateDevice;
    PFN_vkDestroyDevice                                 Anvil::Vulkan::vkDestroyDevice                                = ::vkDestroyDevice;
    PFN_vkEnumerateInstanceExtensionProperties          Anvil::Vulkan::vkEnumerateInstanceExtensionProperties         = ::vkEnumerateInstanceExtensionProperties;
    PFN_vkEnumerateDeviceExtensionProperties            Anvil::Vulkan::vkEnumerateDeviceExtensionProperties           = ::vkEnumerateDeviceExtensionProperties;
    PFN_vkEnumerateInstanceLayerProperties              Anvil::Vulkan::vkEnumerateInstanceLayerProperties             = ::vkEnumerateInstanceLayerProperties;
    PFN_vkEnumerateDeviceLayerProperties                Anvil::Vulkan::vkEnumerateDeviceLayerProperties               = ::vkEnumerateDeviceLayerProperties;
    PFN_vkGetDeviceQueue                                Anvil::Vulkan::vkGetDeviceQueue                               = ::vkGetDeviceQueue;
    PFN_vkQueueSubmit                                   Anvil::Vulkan::vkQueueSubmit                                  = ::vkQueueSubmit;
    PFN_vkQueueWaitIdle                                 Anvil::Vulkan::vkQueueWaitIdle                                = ::vkQueueWaitIdle;
    PFN_vkDeviceWaitIdle                                Anvil::Vulkan::vkDeviceWaitIdle                               = ::vkDeviceWaitIdle;
    PFN_vkAllocateMemory                                Anvil::Vulkan::vkAllocateMemory                               = ::vkAllocateMemory;
    PFN_vkFreeMemory                                    Anvil::Vulkan::vkFreeMemory                                   = ::vkFreeMemory;
    PFN_vkMapMemory                                     Anvil::Vulkan::vkMapMemory                                    = ::vkMapMemory;
    PFN_vkUnmapMemory                                   Anvil::Vulkan::vkUnmapMemory                                  = ::vkUnmapMemory;
    PFN_vkFlushMappedMemoryRanges                       Anvil::Vulkan::vkFlushMappedMemoryRanges                      = ::vkFlushMappedMemoryRanges;
    PFN_vkInvalidateMappedMemoryRanges                  Anvil::Vulkan::vkInvalidateMappedMemoryRanges                 = ::vkInvalidateMappedMemoryRanges;
    PFN_vkGetDeviceMemoryCommitment                     Anvil::Vulkan::vkGetDeviceMemoryCommitment                    = ::vkGetDeviceMemoryCommitment;
    PFN_vkBindBufferMemory                              Anvil::Vulkan::vkBindBufferMemory                             = ::vkBindBufferMemory;
    PFN_vkBindImageMemory                               Anvil::Vulkan::vkBindImageMemory                              = ::vkBindImageMemory;
    PFN_vkGetBufferMemoryRequirements                   Anvil::Vulkan::vkGetBufferMemoryRequirements                  = ::vkGetBufferMemoryRequirements;
    PFN_vkGetImageMemoryRequirements                    Anvil::Vulkan::vkGetImageMemoryRequirements                   = ::vkGetImageMemoryRequirements;
    PFN_vkGetImageSparseMemoryRequirements              Anvil::Vulkan::vkGetImageSparseMemoryRequirements             = ::vkGetImageSparseMemoryRequirements;
    PFN_vkGetPhysicalDeviceSparseImageFormatProperties  Anvil::Vulkan::vkGetPhysicalDeviceSparseImageFormatProperties = ::vkGetPhysicalDeviceSparseImageFormatProperties;
    PFN_vkQueueBindSparse                               Anvil::Vulkan::vkQueueBindSparse                              = ::vkQueueBindSparse;
    PFN_vkCreateFence                                   Anvil::Vulkan::vkCreateFence                                  = ::vkCreateFence;
    PFN_vkDestroyFence                                  Anvil::Vulkan::vkDestroyFence                                 = ::vkDestroyFence;
    PFN_vkResetFences                                   Anvil::Vulkan::vkResetFences                                  = ::vkResetFences;
    PFN_vkGetFenceStatus                                Anvil::Vulkan::vkGetFenceStatus                               = ::vkGetFenceStatus;
    PFN_vkWaitForFences                                 Anvil::Vulkan::vkWaitForFences                                = ::vkWaitForFences;
    PFN_vkCreateSemaphore                               Anvil::Vulkan::vkCreateSemaphore                              = ::vkCreateSemaphore;
    PFN_vkDestroySemaphore                              Anvil::Vulkan::vkDestroySemaphore                             = ::vkDestroySemaphore;
    PFN_vkCreateEvent                                   Anvil::Vulkan::vkCreateEvent                                  = ::vkCreateEvent;
    PFN_vkDestroyEvent                                  Anvil::Vulkan::vkDestroyEvent                                 = ::vkDestroyEvent;
    PFN_vkGetEventStatus                                Anvil::Vulkan::vkGetEventStatus                               = ::vkGetEventStatus;
    PFN_vkSetEvent                                      Anvil::Vulkan::vkSetEvent                                     = ::vkSetEvent;
    PFN_vkResetEvent                                    Anvil::Vulkan::vkResetEvent                                   = ::vkResetEvent;
    PFN_vkCreateQueryPool                               Anvil::Vulkan::vkCreateQueryPool                              = ::vkCreateQueryPool;
    PFN_vkDestroyQueryPool                              Anvil::Vulkan::vkDestroyQueryPool                             = ::vkDestroyQueryPool;
    PFN_vkGetQueryPoolResults                           Anvil::Vulkan::vkGetQueryPoolResults                          = ::vkGetQueryPoolResults;
    PFN_vkCreateBuffer                                  Anvil::Vulkan::vkCreateBuffer                                 = ::vkCreateBuffer;
    PFN_vkDestroyBuffer                                 Anvil::Vulkan::vkDestroyBuffer                                = ::vkDestroyBuffer;
    PFN_vkCreateBufferView                              Anvil::Vulkan::vkCreateBufferView                             = ::vkCreateBufferView;
    PFN_vkDestroyBufferView                             Anvil::Vulkan::vkDestroyBufferView                            = ::vkDestroyBufferView;
    PFN_vkCreateImage                                   Anvil::Vulkan::vkCreateImage                                  = ::vkCreateImage;
    PFN_vkDestroyImage                                  Anvil::Vulkan::vkDestroyImage                                 = ::vkDestroyImage;
    PFN_vkGetImageSubresourceLayout                     Anvil::Vulkan::vkGetImageSubresourceLayout                    = ::vkGetImageSubresourceLayout;
    PFN_vkCreateImageView                               Anvil::Vulkan::vkCreateImageView                              = ::vkCreateImageView;
    PFN_vkDestroyImageView                              Anvil::Vulkan::vkDestroyImageView                             = ::vkDestroyImageView;
    PFN_vkCreateShaderModule                            Anvil::Vulkan::vkCreateShaderModule                           = ::vkCreateShaderModule;
    PFN_vkDestroyShaderModule                           Anvil::Vulkan::vkDestroyShaderModule                          = ::vkDestroyShaderModule;
    PFN_vkCreatePipelineCache                           Anvil::Vulkan::vkCreatePipelineCache                          = ::vkCreatePipelineCache;
    PFN_vkDestroyPipelineCache                          Anvil::Vulkan::vkDestroyPipelineCache                         = ::vkDestroyPipelineCache;
    PFN_vkGetPipelineCacheData                          Anvil::Vulkan::vkGetPipelineCacheData                         = ::vkGetPipelineCacheData;
    PFN_vkMergePipelineCaches                           Anvil::Vulkan::vkMergePipelineCaches                          = ::vkMergePipelineCaches;
    PFN_vkCreateGraphicsPipelines                       Anvil::Vulkan::vkCreateGraphicsPipelines                      = ::vkCreateGraphicsPipelines;
    PFN_vkCreateComputePipelines                        Anvil::Vulkan::vkCreateComputePipelines                       = ::vkCreateComputePipelines;
    PFN_vkDestroyPipeline                               Anvil::Vulkan::vkDestroyPipeline                              = ::vkDestroyPipeline;
    PFN_vkCreatePipelineLayout                          Anvil::Vulkan::vkCreatePipelineLayout                         = ::vkCreatePipelineLayout;
    PFN_vkDestroyPipelineLayout                         Anvil::Vulkan::vkDestroyPipelineLayout                        = ::vkDestroyPipelineLayout;
    PFN_vkCreateSampler                                 Anvil::Vulkan::vkCreateSampler                                = ::vkCreateSampler;
    PFN_vkDestroySampler                                Anvil::Vulkan::vkDestroySampler                               = ::vkDestroySampler;
    PFN_vkCreateDescriptorSetLayout                     Anvil::Vulkan::vkCreateDescriptorSetLayout                    = ::vkCreateDescriptorSetLayout;
    PFN_vkDestroyDescriptorSetLayout                    Anvil::Vulkan::vkDestroyDescriptorSetLayout                   = ::vkDestroyDescriptorSetLayout;
    PFN_vkCreateDescriptorPool                          Anvil::Vulkan::vkCreateDescriptorPool                         = ::vkCreateDescriptorPool;
    PFN_vkDestroyDescriptorPool                         Anvil::Vulkan::vkDestroyDescriptorPool                        = ::vkDestroyDescriptorPool;
    PFN_vkResetDescriptorPool                           Anvil::Vulkan::vkResetDescriptorPool                          = ::vkResetDescriptorPool;
    PFN_vkAllocateDescriptorSets                        Anvil::Vulkan::vkAllocateDescriptorSets                       = ::vkAllocateDescriptorSets;
    PFN_vkFreeDescriptorSets                            Anvil::Vulkan::vkFreeDescriptorSets                           = ::vkFreeDescriptorSets;
    PFN_vkUpdateDescriptorSets                          Anvil::Vulkan::vkUpdateDescriptorSets                         = ::vkUpdateDescriptorSets;
    PFN_vkCreateFramebuffer                             Anvil::Vulkan::vkCreateFramebuffer                            = ::vkCreateFramebuffer;
    PFN_vkDestroyFramebuffer                            Anvil::Vulkan::vkDestroyFramebuffer                           = ::vkDestroyFramebuffer;
    PFN_vkCreateRenderPass                              Anvil::Vulkan::vkCreateRenderPass                             = ::vkCreateRenderPass;
    PFN_vkDestroyRenderPass                             Anvil::Vulkan::vkDestroyRenderPass                            = ::vkDestroyRenderPass;
    PFN_vkGetRenderAreaGranularity                      Anvil::Vulkan::vkGetRenderAreaGranularity                     = ::vkGetRenderAreaGranularity;
    PFN_vkCreateCommandPool                             Anvil::Vulkan::vkCreateCommandPool                            = ::vkCreateCommandPool;
    PFN_vkDestroyCommandPool                            Anvil::Vulkan::vkDestroyCommandPool                           = ::vkDestroyCommandPool;
    PFN_vkResetCommandPool                              Anvil::Vulkan::vkResetCommandPool                             = ::vkResetCommandPool;
    PFN_vkAllocateCommandBuffers                        Anvil::Vulkan::vkAllocateCommandBuffers                       = ::vkAllocateCommandBuffers;
    PFN_vkFreeCommandBuffers                            Anvil::Vulkan::vkFreeCommandBuffers                           = ::vkFreeCommandBuffers;
    PFN_vkBeginCommandBuffer                            Anvil::Vulkan::vkBeginCommandBuffer                           = ::vkBeginCommandBuffer;
    PFN_vkEndCommandBuffer                              Anvil::Vulkan::vkEndCommandBuffer                             = ::vkEndCommandBuffer;
    PFN_vkResetCommandBuffer                            Anvil::Vulkan::vkResetCommandBuffer                           = ::vkResetCommandBuffer;
    PFN_vkCmdBindPipeline                               Anvil::Vulkan::vkCmdBindPipeline                              = ::vkCmdBindPipeline;
    PFN_vkCmdSetViewport                                Anvil::Vulkan::vkCmdSetViewport                               = ::vkCmdSetViewport;
    PFN_vkCmdSetScissor                                 Anvil::Vulkan::vkCmdSetScissor                                = ::vkCmdSetScissor;
    PFN_vkCmdSetLineWidth                               Anvil::Vulkan::vkCmdSetLineWidth                              = ::vkCmdSetLineWidth;
    PFN_vkCmdSetDepthBias                               Anvil::Vulkan::vkCmdSetDepthBias                              = ::vkCmdSetDepthBias;
    PFN_vkCmdSetBlendConstants                          Anvil::Vulkan::vkCmdSetBlendConstants                         = ::vkCmdSetBlendConstants;
    PFN_vkCmdSetDepthBounds                             Anvil::Vulkan::vkCmdSetDepthBounds                            = ::vkCmdSetDepthBounds;
    PFN_vkCmdSetStencilCompareMask                      Anvil::Vulkan::vkCmdSetStencilCompareMask                     = ::vkCmdSetStencilCompareMask;
    PFN_vkCmdSetStencilWriteMask                        Anvil::Vulkan::vkCmdSetStencilWriteMask                       = ::vkCmdSetStencilWriteMask;
    PFN_vkCmdSetStencilReference                        Anvil::Vulkan::vkCmdSetStencilReference                       = ::vkCmdSetStencilReference;
    PFN_vkCmdBindDescriptorSets                         Anvil::Vulkan::vkCmdBindDescriptorSets                        = ::vkCmdBindDescriptorSets;
    PFN_vkCmdBindIndexBuffer                            Anvil::Vulkan::vkCmdBindIndexBuffer                           = ::vkCmdBindIndexBuffer;
    PFN_vkCmdBindVertexBuffers                          Anvil::Vulkan::vkCmdBindVertexBuffers                         = ::vkCmdBindVertexBuffers;
    PFN_vkCmdDraw                                       Anvil::Vulkan::vkCmdDraw                                      = ::vkCmdDraw;
    PFN_vkCmdDrawIndexed                                Anvil::Vulkan::vkCmdDrawIndexed                               = ::vkCmdDrawIndexed;
    PFN_vkCmdDrawIndirect                               Anvil::Vulkan::vkCmdDrawIndirect                              = ::vkCmdDrawIndirect;
    PFN_vkCmdDrawIndexedIndirect                        Anvil::Vulkan::vkCmdDrawIndexedIndirect                       = ::vkCmdDrawIndexedIndirect;
    PFN_vkCmdDispatch                                   Anvil::Vulkan::vkCmdDispatch                                  = ::vkCmdDispatch;
    PFN_vkCmdDispatchIndirect                           Anvil::Vulkan::vkCmdDispatchIndirect                          = ::vkCmdDispatchIndirect;
    PFN_vkCmdCopyBuffer                                 Anvil::Vulkan::vkCmdCopyBuffer                                = ::vkCmdCopyBuffer;
    PFN_vkCmdCopyImage                                  Anvil::Vulkan::vkCmdCopyImage                                 = ::vkCmdCopyImage;
    PFN_vkCmdBlitImage                                  Anvil::Vulkan::vkCmdBlitImage                                 = ::vkCmdBlitImage;
    PFN_vkCmdCopyBufferToImage                          Anvil::Vulkan::vkCmdCopyBufferToImage                         = ::vkCmdCopyBufferToImage;
    PFN_vkCmdCopyImageToBuffer                          Anvil::Vulkan::vkCmdCopyImageToBuffer                         = ::vkCmdCopyImageToBuffer;
    PFN_vkCmdUpdateBuffer                               Anvil::Vulkan::vkCmdUpdateBuffer                              = ::vkCmdUpdateBuffer;
    PFN_vkCmdFillBuffer                                 Anvil::Vulkan::vkCmdFillBuffer                                = ::vkCmdFillBuffer;
    PFN_vkCmdClearColorImage                            Anvil::Vulkan::vkCmdClearColorImage                           = ::vkCmdClearColorImage;
    PFN_vkCmdClearDepthStencilImage                     Anvil::Vulkan::vkCmdClearDepthStencilImage                    = ::vkCmdClearDepthStencilImage;
    PFN_vkCmdClearAttachments                           Anvil::Vulkan::vkCmdClearAttachments                          = ::vkCmdClearAttachments;
    PFN_vkCmdResolveImage                               Anvil::Vulkan::vkCmdResolveImage                              = ::vkCmdResolveImage;
    PFN_vkCmdSetEvent                                   Anvil::Vulkan::vkCmdSetEvent                                  = ::vkCmdSetEvent;
    PFN_vkCmdResetEvent                                 Anvil::Vulkan::vkCmdResetEvent                                = ::vkCmdResetEvent;
    PFN_vkCmdWaitEvents                                 Anvil::Vulkan::vkCmdWaitEvents                                = ::vkCmdWaitEvents;
    PFN_vkCmdPipelineBarrier                            Anvil::Vulkan::vkCmdPipelineBarrier                           = ::vkCmdPipelineBarrier;
    PFN_vkCmdBeginQuery                                 Anvil::Vulkan::vkCmdBeginQuery                                = ::vkCmdBeginQuery;
    PFN_vkCmdEndQuery                                   Anvil::Vulkan::vkCmdEndQuery                                  = ::vkCmdEndQuery;
    PFN_vkCmdResetQueryPool                             Anvil::Vulkan::vkCmdResetQueryPool                            = ::vkCmdResetQueryPool;
    PFN_vkCmdWriteTimestamp                             Anvil::Vulkan::vkCmdWriteTimestamp                            = ::vkCmdWriteTimestamp;
    PFN_vkCmdCopyQueryPoolResults                       Anvil::Vulkan::vkCmdCopyQueryPoolResults                      = ::vkCmdCopyQueryPoolResults;
    PFN_vkCmdPushConstants                              Anvil::Vulkan::vkCmdPushConstants                             = ::vkCmdPushConstants;
    PFN_vkCmdBeginRenderPass                            Anvil::Vulkan::vkCmdBeginRenderPass                           = ::vkCmdBeginRenderPass;
    PFN_vkCmdNextSubpass                                Anvil::Vulkan::vkCmdNextSubpass                               = ::vkCmdNextSubpass;
    PFN_vkCmdEndRenderPass                              Anvil::Vulkan::vkCmdEndRenderPass                             = ::vkCmdEndRenderPass;
    PFN_vkCmdExecuteCommands                            Anvil::Vulkan::vkCmdExecuteCommands                           = ::vkCmdExecuteCommands;

    PFN_vkBindBufferMemory2                             Anvil::Vulkan::vkBindBufferMemory2                             = nullptr;
    PFN_vkBindImageMemory2                              Anvil::Vulkan::vkBindImageMemory2                              = nullptr;
    PFN_vkCmdDispatchBase                               Anvil::Vulkan::vkCmdDispatchBase                               = nullptr;
    PFN_vkCmdSetDeviceMask                              Anvil::Vulkan::vkCmdSetDeviceMask                              = nullptr;
    PFN_vkCreateDescriptorUpdateTemplate                Anvil::Vulkan::vkCreateDescriptorUpdateTemplate                = nullptr;
    PFN_vkCreateSamplerYcbcrConversion                  Anvil::Vulkan::vkCreateSamplerYcbcrConversion                  = nullptr;
    PFN_vkDestroyDescriptorUpdateTemplate               Anvil::Vulkan::vkDestroyDescriptorUpdateTemplate               = nullptr;
    PFN_vkDestroySamplerYcbcrConversion                 Anvil::Vulkan::vkDestroySamplerYcbcrConversion                 = nullptr;
    PFN_vkEnumerateInstanceVersion                      Anvil::Vulkan::vkEnumerateInstanceVersion                      = nullptr;
    PFN_vkEnumeratePhysicalDeviceGroups                 Anvil::Vulkan::vkEnumeratePhysicalDeviceGroups                 = nullptr;
    PFN_vkGetBufferMemoryRequirements2                  Anvil::Vulkan::vkGetBufferMemoryRequirements2                  = nullptr;
    PFN_vkGetDescriptorSetLayoutSupport                 Anvil::Vulkan::vkGetDescriptorSetLayoutSupport                 = nullptr;
    PFN_vkGetDeviceGroupPeerMemoryFeatures              Anvil::Vulkan::vkGetDeviceGroupPeerMemoryFeatures              = nullptr;
    PFN_vkGetDeviceQueue2                               Anvil::Vulkan::vkGetDeviceQueue2                               = nullptr;
    PFN_vkGetImageMemoryRequirements2                   Anvil::Vulkan::vkGetImageMemoryRequirements2                   = nullptr;
    PFN_vkGetImageSparseMemoryRequirements2             Anvil::Vulkan::vkGetImageSparseMemoryRequirements2             = nullptr;
    PFN_vkGetPhysicalDeviceExternalBufferProperties     Anvil::Vulkan::vkGetPhysicalDeviceExternalBufferProperties     = nullptr;
    PFN_vkGetPhysicalDeviceExternalFenceProperties      Anvil::Vulkan::vkGetPhysicalDeviceExternalFenceProperties      = nullptr;
    PFN_vkGetPhysicalDeviceExternalSemaphoreProperties  Anvil::Vulkan::vkGetPhysicalDeviceExternalSemaphoreProperties  = nullptr;
    PFN_vkGetPhysicalDeviceFeatures2                    Anvil::Vulkan::vkGetPhysicalDeviceFeatures2                    = nullptr;
    PFN_vkGetPhysicalDeviceFormatProperties2            Anvil::Vulkan::vkGetPhysicalDeviceFormatProperties2            = nullptr;
    PFN_vkGetPhysicalDeviceImageFormatProperties2       Anvil::Vulkan::vkGetPhysicalDeviceImageFormatProperties2       = nullptr;
    PFN_vkGetPhysicalDeviceMemoryProperties2            Anvil::Vulkan::vkGetPhysicalDeviceMemoryProperties2            = nullptr;
    PFN_vkGetPhysicalDeviceProperties2                  Anvil::Vulkan::vkGetPhysicalDeviceProperties2                  = nullptr;
    PFN_vkGetPhysicalDeviceQueueFamilyProperties2       Anvil::Vulkan::vkGetPhysicalDeviceQueueFamilyProperties2       = nullptr;
    PFN_vkGetPhysicalDeviceSparseImageFormatProperties2 Anvil::Vulkan::vkGetPhysicalDeviceSparseImageFormatProperties2 = nullptr;
    PFN_vkTrimCommandPool                               Anvil::Vulkan::vkTrimCommandPool                               = nullptr;
    PFN_vkUpdateDescriptorSetWithTemplate               Anvil::Vulkan::vkUpdateDescriptorSetWithTemplate               = nullptr;
#endif


static bool                    g_vk_func_ptrs_inited     = false;
static std::mutex              g_vk_func_ptr_init_mutex;
static Anvil::LibraryUniquePtr g_vk_library_ptr;

__attribute__((constructor))
static bool init_vk_func_ptrs()
{
    std::lock_guard<std::mutex> lock  (g_vk_func_ptr_init_mutex);
    bool                        result(true);

    typedef struct
    {
        std::string func_name;
        void**      result_func_ptr;
    } FunctionData;

    #if !defined(ANVIL_LINK_STATICALLY_WITH_VULKAN_LIB)
        static FunctionData functions_vk10[] =
        {
            /* NOTE: All functions with @param requires_getter_call equal to false should come first! */
            {"vkCreateInstance",                               reinterpret_cast<void**>(&Anvil::Vulkan::vkCreateInstance)},
            {"vkDestroyInstance",                              reinterpret_cast<void**>(&Anvil::Vulkan::vkDestroyInstance)},
            {"vkEnumeratePhysicalDevices",                     reinterpret_cast<void**>(&Anvil::Vulkan::vkEnumeratePhysicalDevices)},
            {"vkEnumerateInstanceExtensionProperties",         reinterpret_cast<void**>(&Anvil::Vulkan::vkEnumerateInstanceExtensionProperties)},
            {"vkEnumerateInstanceLayerProperties",             reinterpret_cast<void**>(&Anvil::Vulkan::vkEnumerateInstanceLayerProperties)},
            {"vkGetDeviceProcAddr",                            reinterpret_cast<void**>(&Anvil::Vulkan::vkGetDeviceProcAddr)},
            {"vkGetInstanceProcAddr",                          reinterpret_cast<void**>(&Anvil::Vulkan::vkGetInstanceProcAddr)},

            /* instance-dependent functions */
            {"vkGetPhysicalDeviceFeatures",                    reinterpret_cast<void**>(&Anvil::Vulkan::vkGetPhysicalDeviceFeatures)},
            {"vkGetPhysicalDeviceFormatProperties",            reinterpret_cast<void**>(&Anvil::Vulkan::vkGetPhysicalDeviceFormatProperties)},
            {"vkGetPhysicalDeviceImageFormatProperties",       reinterpret_cast<void**>(&Anvil::Vulkan::vkGetPhysicalDeviceImageFormatProperties)},
            {"vkGetPhysicalDeviceProperties",                  reinterpret_cast<void**>(&Anvil::Vulkan::vkGetPhysicalDeviceProperties)},
            {"vkGetPhysicalDeviceQueueFamilyProperties",       reinterpret_cast<void**>(&Anvil::Vulkan::vkGetPhysicalDeviceQueueFamilyProperties)},
            {"vkGetPhysicalDeviceMemoryProperties",            reinterpret_cast<void**>(&Anvil::Vulkan::vkGetPhysicalDeviceMemoryProperties)},
            {"vkCreateDevice",                                 reinterpret_cast<void**>(&Anvil::Vulkan::vkCreateDevice)},
            {"vkDestroyDevice",                                reinterpret_cast<void**>(&Anvil::Vulkan::vkDestroyDevice)},
            {"vkEnumerateDeviceExtensionProperties",           reinterpret_cast<void**>(&Anvil::Vulkan::vkEnumerateDeviceExtensionProperties)},
            {"vkEnumerateDeviceLayerProperties",               reinterpret_cast<void**>(&Anvil::Vulkan::vkEnumerateDeviceLayerProperties)},
            {"vkGetDeviceQueue",                               reinterpret_cast<void**>(&Anvil::Vulkan::vkGetDeviceQueue)},
            {"vkQueueSubmit",                                  reinterpret_cast<void**>(&Anvil::Vulkan::vkQueueSubmit)},
            {"vkQueueWaitIdle",                                reinterpret_cast<void**>(&Anvil::Vulkan::vkQueueWaitIdle)},
            {"vkDeviceWaitIdle",                               reinterpret_cast<void**>(&Anvil::Vulkan::vkDeviceWaitIdle)},
            {"vkAllocateMemory",                               reinterpret_cast<void**>(&Anvil::Vulkan::vkAllocateMemory)},
            {"vkFreeMemory",                                   reinterpret_cast<void**>(&Anvil::Vulkan::vkFreeMemory)},
            {"vkMapMemory",                                    reinterpret_cast<void**>(&Anvil::Vulkan::vkMapMemory)},
            {"vkUnmapMemory",                                  reinterpret_cast<void**>(&Anvil::Vulkan::vkUnmapMemory)},
            {"vkFlushMappedMemoryRanges",                      reinterpret_cast<void**>(&Anvil::Vulkan::vkFlushMappedMemoryRanges)},
            {"vkInvalidateMappedMemoryRanges",                 reinterpret_cast<void**>(&Anvil::Vulkan::vkInvalidateMappedMemoryRanges)},
            {"vkGetDeviceMemoryCommitment",                    reinterpret_cast<void**>(&Anvil::Vulkan::vkGetDeviceMemoryCommitment)},
            {"vkBindBufferMemory",                             reinterpret_cast<void**>(&Anvil::Vulkan::vkBindBufferMemory)},
            {"vkBindImageMemory",                              reinterpret_cast<void**>(&Anvil::Vulkan::vkBindImageMemory)},
            {"vkGetBufferMemoryRequirements",                  reinterpret_cast<void**>(&Anvil::Vulkan::vkGetBufferMemoryRequirements)},
            {"vkGetImageMemoryRequirements",                   reinterpret_cast<void**>(&Anvil::Vulkan::vkGetImageMemoryRequirements)},
            {"vkGetImageSparseMemoryRequirements",             reinterpret_cast<void**>(&Anvil::Vulkan::vkGetImageSparseMemoryRequirements)},
            {"vkGetPhysicalDeviceSparseImageFormatProperties", reinterpret_cast<void**>(&Anvil::Vulkan::vkGetPhysicalDeviceSparseImageFormatProperties)},
            {"vkQueueBindSparse",                              reinterpret_cast<void**>(&Anvil::Vulkan::vkQueueBindSparse)},
            {"vkCreateFence",                                  reinterpret_cast<void**>(&Anvil::Vulkan::vkCreateFence)},
            {"vkDestroyFence",                                 reinterpret_cast<void**>(&Anvil::Vulkan::vkDestroyFence)},
            {"vkResetFences",                                  reinterpret_cast<void**>(&Anvil::Vulkan::vkResetFences)},
            {"vkGetFenceStatus",                               reinterpret_cast<void**>(&Anvil::Vulkan::vkGetFenceStatus)},
            {"vkWaitForFences",                                reinterpret_cast<void**>(&Anvil::Vulkan::vkWaitForFences)},
            {"vkCreateSemaphore",                              reinterpret_cast<void**>(&Anvil::Vulkan::vkCreateSemaphore)},
            {"vkDestroySemaphore",                             reinterpret_cast<void**>(&Anvil::Vulkan::vkDestroySemaphore)},
            {"vkCreateEvent",                                  reinterpret_cast<void**>(&Anvil::Vulkan::vkCreateEvent)},
            {"vkDestroyEvent",                                 reinterpret_cast<void**>(&Anvil::Vulkan::vkDestroyEvent)},
            {"vkGetEventStatus",                               reinterpret_cast<void**>(&Anvil::Vulkan::vkGetEventStatus)},
            {"vkSetEvent",                                     reinterpret_cast<void**>(&Anvil::Vulkan::vkSetEvent)},
            {"vkResetEvent",                                   reinterpret_cast<void**>(&Anvil::Vulkan::vkResetEvent)},
            {"vkCreateQueryPool",                              reinterpret_cast<void**>(&Anvil::Vulkan::vkCreateQueryPool)},
            {"vkDestroyQueryPool",                             reinterpret_cast<void**>(&Anvil::Vulkan::vkDestroyQueryPool)},
            {"vkGetQueryPoolResults",                          reinterpret_cast<void**>(&Anvil::Vulkan::vkGetQueryPoolResults)},
            {"vkCreateBuffer",                                 reinterpret_cast<void**>(&Anvil::Vulkan::vkCreateBuffer)},
            {"vkDestroyBuffer",                                reinterpret_cast<void**>(&Anvil::Vulkan::vkDestroyBuffer)},
            {"vkCreateBufferView",                             reinterpret_cast<void**>(&Anvil::Vulkan::vkCreateBufferView)},
            {"vkDestroyBufferView",                            reinterpret_cast<void**>(&Anvil::Vulkan::vkDestroyBufferView)},
            {"vkCreateImage",                                  reinterpret_cast<void**>(&Anvil::Vulkan::vkCreateImage)},
            {"vkDestroyImage",                                 reinterpret_cast<void**>(&Anvil::Vulkan::vkDestroyImage)},
            {"vkGetImageSubresourceLayout",                    reinterpret_cast<void**>(&Anvil::Vulkan::vkGetImageSubresourceLayout)},
            {"vkCreateImageView",                              reinterpret_cast<void**>(&Anvil::Vulkan::vkCreateImageView)},
            {"vkDestroyImageView",                             reinterpret_cast<void**>(&Anvil::Vulkan::vkDestroyImageView)},
            {"vkCreateShaderModule",                           reinterpret_cast<void**>(&Anvil::Vulkan::vkCreateShaderModule)},
            {"vkDestroyShaderModule",                          reinterpret_cast<void**>(&Anvil::Vulkan::vkDestroyShaderModule)},
            {"vkCreatePipelineCache",                          reinterpret_cast<void**>(&Anvil::Vulkan::vkCreatePipelineCache)},
            {"vkDestroyPipelineCache",                         reinterpret_cast<void**>(&Anvil::Vulkan::vkDestroyPipelineCache)},
            {"vkGetPipelineCacheData",                         reinterpret_cast<void**>(&Anvil::Vulkan::vkGetPipelineCacheData)},
            {"vkMergePipelineCaches",                          reinterpret_cast<void**>(&Anvil::Vulkan::vkMergePipelineCaches)},
            {"vkCreateGraphicsPipelines",                      reinterpret_cast<void**>(&Anvil::Vulkan::vkCreateGraphicsPipelines)},
            {"vkCreateComputePipelines",                       reinterpret_cast<void**>(&Anvil::Vulkan::vkCreateComputePipelines)},
            {"vkDestroyPipeline",                              reinterpret_cast<void**>(&Anvil::Vulkan::vkDestroyPipeline)},
            {"vkCreatePipelineLayout",                         reinterpret_cast<void**>(&Anvil::Vulkan::vkCreatePipelineLayout)},
            {"vkDestroyPipelineLayout",                        reinterpret_cast<void**>(&Anvil::Vulkan::vkDestroyPipelineLayout)},
            {"vkCreateSampler",                                reinterpret_cast<void**>(&Anvil::Vulkan::vkCreateSampler)},
            {"vkDestroySampler",                               reinterpret_cast<void**>(&Anvil::Vulkan::vkDestroySampler)},
            {"vkCreateDescriptorSetLayout",                    reinterpret_cast<void**>(&Anvil::Vulkan::vkCreateDescriptorSetLayout)},
            {"vkDestroyDescriptorSetLayout",                   reinterpret_cast<void**>(&Anvil::Vulkan::vkDestroyDescriptorSetLayout)},
            {"vkCreateDescriptorPool",                         reinterpret_cast<void**>(&Anvil::Vulkan::vkCreateDescriptorPool)},
            {"vkDestroyDescriptorPool",                        reinterpret_cast<void**>(&Anvil::Vulkan::vkDestroyDescriptorPool)},
            {"vkResetDescriptorPool",                          reinterpret_cast<void**>(&Anvil::Vulkan::vkResetDescriptorPool)},
            {"vkAllocateDescriptorSets",                       reinterpret_cast<void**>(&Anvil::Vulkan::vkAllocateDescriptorSets)},
            {"vkFreeDescriptorSets",                           reinterpret_cast<void**>(&Anvil::Vulkan::vkFreeDescriptorSets)},
            {"vkUpdateDescriptorSets",                         reinterpret_cast<void**>(&Anvil::Vulkan::vkUpdateDescriptorSets)},
            {"vkCreateFramebuffer",                            reinterpret_cast<void**>(&Anvil::Vulkan::vkCreateFramebuffer)},
            {"vkDestroyFramebuffer",                           reinterpret_cast<void**>(&Anvil::Vulkan::vkDestroyFramebuffer)},
            {"vkCreateRenderPass",                             reinterpret_cast<void**>(&Anvil::Vulkan::vkCreateRenderPass)},
            {"vkDestroyRenderPass",                            reinterpret_cast<void**>(&Anvil::Vulkan::vkDestroyRenderPass)},
            {"vkGetRenderAreaGranularity",                     reinterpret_cast<void**>(&Anvil::Vulkan::vkGetRenderAreaGranularity)},
            {"vkCreateCommandPool",                            reinterpret_cast<void**>(&Anvil::Vulkan::vkCreateCommandPool)},
            {"vkDestroyCommandPool",                           reinterpret_cast<void**>(&Anvil::Vulkan::vkDestroyCommandPool)},
            {"vkResetCommandPool",                             reinterpret_cast<void**>(&Anvil::Vulkan::vkResetCommandPool)},
            {"vkAllocateCommandBuffers",                       reinterpret_cast<void**>(&Anvil::Vulkan::vkAllocateCommandBuffers)},
            {"vkFreeCommandBuffers",                           reinterpret_cast<void**>(&Anvil::Vulkan::vkFreeCommandBuffers)},
            {"vkBeginCommandBuffer",                           reinterpret_cast<void**>(&Anvil::Vulkan::vkBeginCommandBuffer)},
            {"vkEndCommandBuffer",                             reinterpret_cast<void**>(&Anvil::Vulkan::vkEndCommandBuffer)},
            {"vkResetCommandBuffer",                           reinterpret_cast<void**>(&Anvil::Vulkan::vkResetCommandBuffer)},
            {"vkCmdBindPipeline",                              reinterpret_cast<void**>(&Anvil::Vulkan::vkCmdBindPipeline)},
            {"vkCmdSetViewport",                               reinterpret_cast<void**>(&Anvil::Vulkan::vkCmdSetViewport)},
            {"vkCmdSetScissor",                                reinterpret_cast<void**>(&Anvil::Vulkan::vkCmdSetScissor)},
            {"vkCmdSetLineWidth",                              reinterpret_cast<void**>(&Anvil::Vulkan::vkCmdSetLineWidth)},
            {"vkCmdSetDepthBias",                              reinterpret_cast<void**>(&Anvil::Vulkan::vkCmdSetDepthBias)},
            {"vkCmdSetBlendConstants",                         reinterpret_cast<void**>(&Anvil::Vulkan::vkCmdSetBlendConstants)},
            {"vkCmdSetDepthBounds",                            reinterpret_cast<void**>(&Anvil::Vulkan::vkCmdSetDepthBounds)},
            {"vkCmdSetStencilCompareMask",                     reinterpret_cast<void**>(&Anvil::Vulkan::vkCmdSetStencilCompareMask)},
            {"vkCmdSetStencilWriteMask",                       reinterpret_cast<void**>(&Anvil::Vulkan::vkCmdSetStencilWriteMask)},
            {"vkCmdSetStencilReference",                       reinterpret_cast<void**>(&Anvil::Vulkan::vkCmdSetStencilReference)},
            {"vkCmdBindDescriptorSets",                        reinterpret_cast<void**>(&Anvil::Vulkan::vkCmdBindDescriptorSets)},
            {"vkCmdBindIndexBuffer",                           reinterpret_cast<void**>(&Anvil::Vulkan::vkCmdBindIndexBuffer)},
            {"vkCmdBindVertexBuffers",                         reinterpret_cast<void**>(&Anvil::Vulkan::vkCmdBindVertexBuffers)},
            {"vkCmdDraw",                                      reinterpret_cast<void**>(&Anvil::Vulkan::vkCmdDraw)},
            {"vkCmdDrawIndexed",                               reinterpret_cast<void**>(&Anvil::Vulkan::vkCmdDrawIndexed)},
            {"vkCmdDrawIndirect",                              reinterpret_cast<void**>(&Anvil::Vulkan::vkCmdDrawIndirect)},
            {"vkCmdDrawIndexedIndirect",                       reinterpret_cast<void**>(&Anvil::Vulkan::vkCmdDrawIndexedIndirect)},
            {"vkCmdDispatch",                                  reinterpret_cast<void**>(&Anvil::Vulkan::vkCmdDispatch)},
            {"vkCmdDispatchIndirect",                          reinterpret_cast<void**>(&Anvil::Vulkan::vkCmdDispatchIndirect)},
            {"vkCmdCopyBuffer",                                reinterpret_cast<void**>(&Anvil::Vulkan::vkCmdCopyBuffer)},
            {"vkCmdCopyImage",                                 reinterpret_cast<void**>(&Anvil::Vulkan::vkCmdCopyImage)},
            {"vkCmdBlitImage",                                 reinterpret_cast<void**>(&Anvil::Vulkan::vkCmdBlitImage)},
            {"vkCmdCopyBufferToImage",                         reinterpret_cast<void**>(&Anvil::Vulkan::vkCmdCopyBufferToImage)},
            {"vkCmdCopyImageToBuffer",                         reinterpret_cast<void**>(&Anvil::Vulkan::vkCmdCopyImageToBuffer)},
            {"vkCmdUpdateBuffer",                              reinterpret_cast<void**>(&Anvil::Vulkan::vkCmdUpdateBuffer)},
            {"vkCmdFillBuffer",                                reinterpret_cast<void**>(&Anvil::Vulkan::vkCmdFillBuffer)},
            {"vkCmdClearColorImage",                           reinterpret_cast<void**>(&Anvil::Vulkan::vkCmdClearColorImage)},
            {"vkCmdClearDepthStencilImage",                    reinterpret_cast<void**>(&Anvil::Vulkan::vkCmdClearDepthStencilImage)},
            {"vkCmdClearAttachments",                          reinterpret_cast<void**>(&Anvil::Vulkan::vkCmdClearAttachments)},
            {"vkCmdResolveImage",                              reinterpret_cast<void**>(&Anvil::Vulkan::vkCmdResolveImage)},
            {"vkCmdSetEvent",                                  reinterpret_cast<void**>(&Anvil::Vulkan::vkCmdSetEvent)},
            {"vkCmdResetEvent",                                reinterpret_cast<void**>(&Anvil::Vulkan::vkCmdResetEvent)},
            {"vkCmdWaitEvents",                                reinterpret_cast<void**>(&Anvil::Vulkan::vkCmdWaitEvents)},
            {"vkCmdPipelineBarrier",                           reinterpret_cast<void**>(&Anvil::Vulkan::vkCmdPipelineBarrier)},
            {"vkCmdBeginQuery",                                reinterpret_cast<void**>(&Anvil::Vulkan::vkCmdBeginQuery)},
            {"vkCmdEndQuery",                                  reinterpret_cast<void**>(&Anvil::Vulkan::vkCmdEndQuery)},
            {"vkCmdResetQueryPool",                            reinterpret_cast<void**>(&Anvil::Vulkan::vkCmdResetQueryPool)},
            {"vkCmdWriteTimestamp",                            reinterpret_cast<void**>(&Anvil::Vulkan::vkCmdWriteTimestamp)},
            {"vkCmdCopyQueryPoolResults",                      reinterpret_cast<void**>(&Anvil::Vulkan::vkCmdCopyQueryPoolResults)},
            {"vkCmdPushConstants",                             reinterpret_cast<void**>(&Anvil::Vulkan::vkCmdPushConstants)},
            {"vkCmdBeginRenderPass",                           reinterpret_cast<void**>(&Anvil::Vulkan::vkCmdBeginRenderPass)},
            {"vkCmdNextSubpass",                               reinterpret_cast<void**>(&Anvil::Vulkan::vkCmdNextSubpass)},
            {"vkCmdEndRenderPass",                             reinterpret_cast<void**>(&Anvil::Vulkan::vkCmdEndRenderPass)},
            {"vkCmdExecuteCommands",                           reinterpret_cast<void**>(&Anvil::Vulkan::vkCmdExecuteCommands)}
        };
    #endif

    static FunctionData functions_vk11[] =
    {
        {"vkBindBufferMemory2",                             reinterpret_cast<void**>(&Anvil::Vulkan::vkBindBufferMemory2)},
        {"vkCmdDispatchBase",                               reinterpret_cast<void**>(&Anvil::Vulkan::vkCmdDispatchBase)},
        {"vkCmdSetDeviceMask",                              reinterpret_cast<void**>(&Anvil::Vulkan::vkCmdSetDeviceMask)},
        {"vkCreateDescriptorUpdateTemplate",                reinterpret_cast<void**>(&Anvil::Vulkan::vkCreateDescriptorUpdateTemplate)},
        {"vkCreateSamplerYcbcrConversion",                  reinterpret_cast<void**>(&Anvil::Vulkan::vkCreateSamplerYcbcrConversion)},
        {"vkDestroyDescriptorUpdateTemplate",               reinterpret_cast<void**>(&Anvil::Vulkan::vkDestroyDescriptorUpdateTemplate)},
        {"vkDestroySamplerYcbcrConversion",                 reinterpret_cast<void**>(&Anvil::Vulkan::vkDestroySamplerYcbcrConversion)},
        {"vkEnumerateInstanceVersion",                      reinterpret_cast<void**>(&Anvil::Vulkan::vkEnumerateInstanceVersion)},
        {"vkEnumeratePhysicalDeviceGroups",                 reinterpret_cast<void**>(&Anvil::Vulkan::vkEnumeratePhysicalDeviceGroups)},
        {"vkGetBufferMemoryRequirements2",                  reinterpret_cast<void**>(&Anvil::Vulkan::vkGetBufferMemoryRequirements2)},
        {"vkGetDescriptorSetLayoutSupport",                 reinterpret_cast<void**>(&Anvil::Vulkan::vkGetDescriptorSetLayoutSupport)},
        {"vkGetDeviceGroupPeerMemoryFeatures",              reinterpret_cast<void**>(&Anvil::Vulkan::vkGetDeviceGroupPeerMemoryFeatures)},
        {"vkGetDeviceQueue2",                               reinterpret_cast<void**>(&Anvil::Vulkan::vkGetDeviceQueue2)},
        {"vkGetImageMemoryRequirements2",                   reinterpret_cast<void**>(&Anvil::Vulkan::vkGetImageMemoryRequirements2)},
        {"vkGetImageSparseMemoryRequirements2",             reinterpret_cast<void**>(&Anvil::Vulkan::vkGetImageSparseMemoryRequirements2)},
        {"vkGetPhysicalDeviceExternalBufferProperties",     reinterpret_cast<void**>(&Anvil::Vulkan::vkGetPhysicalDeviceExternalBufferProperties)},
        {"vkGetPhysicalDeviceExternalFenceProperties",      reinterpret_cast<void**>(&Anvil::Vulkan::vkGetPhysicalDeviceExternalFenceProperties)},
        {"vkGetPhysicalDeviceExternalSemaphoreProperties",  reinterpret_cast<void**>(&Anvil::Vulkan::vkGetPhysicalDeviceExternalSemaphoreProperties)},
        {"vkGetPhysicalDeviceFeatures2",                    reinterpret_cast<void**>(&Anvil::Vulkan::vkGetPhysicalDeviceFeatures2)},
        {"vkGetPhysicalDeviceFormatProperties2",            reinterpret_cast<void**>(&Anvil::Vulkan::vkGetPhysicalDeviceFormatProperties2)},
        {"vkGetPhysicalDeviceImageFormatProperties2",       reinterpret_cast<void**>(&Anvil::Vulkan::vkGetPhysicalDeviceImageFormatProperties2)},
        {"vkGetPhysicalDeviceMemoryProperties2",            reinterpret_cast<void**>(&Anvil::Vulkan::vkGetPhysicalDeviceMemoryProperties2)},
        {"vkGetPhysicalDeviceProperties2",                  reinterpret_cast<void**>(&Anvil::Vulkan::vkGetPhysicalDeviceProperties2)},
        {"vkGetPhysicalDeviceQueueFamilyProperties2",       reinterpret_cast<void**>(&Anvil::Vulkan::vkGetPhysicalDeviceQueueFamilyProperties2)},
        {"vkGetPhysicalDeviceSparseImageFormatProperties2", reinterpret_cast<void**>(&Anvil::Vulkan::vkGetPhysicalDeviceSparseImageFormatProperties2)},
        {"vkTrimCommandPool",                               reinterpret_cast<void**>(&Anvil::Vulkan::vkTrimCommandPool)},
        {"vkUpdateDescriptorSetWithTemplate",               reinterpret_cast<void**>(&Anvil::Vulkan::vkUpdateDescriptorSetWithTemplate)},
    };

    if (g_vk_func_ptrs_inited)
    {
        result = true;

        goto end;
    }

    #if !defined(ANVIL_LINK_STATICALLY_WITH_VULKAN_LIB)
    {
        if (g_vk_library_ptr == nullptr)
        {
            g_vk_library_ptr = Anvil::Library::create(ANVIL_VULKAN_DYNAMIC_DLL);

            if (g_vk_library_ptr == nullptr)
            {
                anvil_assert(g_vk_library_ptr != nullptr);

                goto end;
            }
        }

        /* VK 1.0 func ptrgetters - all entrypoints must be present */
        for (const auto& current_func_data : functions_vk10)
        {
            if (!g_vk_func_ptrs_inited)
            {
                *current_func_data.result_func_ptr = g_vk_library_ptr->get_proc_address(current_func_data.func_name.c_str() );

                if (*current_func_data.result_func_ptr == nullptr)
                {
                    anvil_assert(*current_func_data.result_func_ptr != nullptr);

                    goto end;
                }
            }
        }
    }
    #endif

    /* VK 1.1 func ptr getters - all entrypoints may be missing on implementations that do not support the API */
    for (const auto& current_func_data : functions_vk11)
    {
        if (!g_vk_func_ptrs_inited)
        {
            *current_func_data.result_func_ptr = g_vk_library_ptr->get_proc_address(current_func_data.func_name.c_str() );
        }
    }

    /* Done */
    g_vk_func_ptrs_inited = true;

end:
    return result;
}

