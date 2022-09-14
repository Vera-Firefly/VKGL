/* VKGL (c) 2018 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef VKGL_VK_UTILS_H
#define VKGL_VK_UTILS_H

#include "OpenGL/types.h"

namespace OpenGL
{
    namespace VKUtils
    {
        GLContextStateBindingReferencesUniquePtr create_gl_context_state_binding_references(const OpenGL::IContextObjectManagers*  in_frontend_managers_ptr,
                                                                                            		const OpenGL::GLContextStateReference* in_context_state_reference_ptr);

        Anvil::ImageUsageFlags   get_image_usage_flags_for_gl_internal_format(const OpenGL::InternalFormat& in_internal_format);
        Anvil::BufferUsageFlags   get_buffer_usage_flags_for_gl_buffer			(const uint32_t&             in_n_buffer_targets,
                                                                         			const OpenGL::BufferTarget* in_buffer_targets_ptr);
        Anvil::MemoryFeatureFlags get_memory_feature_flags_for_gl_buffer	(const OpenGL::BufferUsage&  in_buffer_usage);

        Anvil::CompareOp         get_anvil_compare_op_for_depth_function        (const OpenGL::DepthFunction&        in_depth_func);
        Anvil::CompareOp         get_anvil_compare_op_for_stencil_function      (const OpenGL::StencilFunction&      in_stencil_func);
        Anvil::CullModeFlags     get_anvil_cull_mode_flags_for_cull_face_mode   (const OpenGL::CullMode&             in_cull_face_mode);
        Anvil::FrontFace         get_anvil_front_face_for_front_face_orientation	(const OpenGL::FrontFaceOrientation& in_front_face_orientation);
        Anvil::LogicOp           get_anvil_logic_op_for_logic_op_mode           (const OpenGL::LogicOpMode&          in_logic_op_mode);
        Anvil::PolygonMode       get_anvil_polygon_mode_for_polygon_mode	(const OpenGL::PolygonMode&          in_polygon_mode);
        Anvil::PrimitiveTopology get_anvil_primitive_topology_for_draw_call_mode(const OpenGL::DrawCallMode&         in_draw_call_mode);
        Anvil::StencilOp         get_anvil_stencil_op_for_stencil_operation     	(const OpenGL::StencilOperation&     in_stencil_op);
        
        Anvil::Filter 				get_anvil_filter_for_mag_filter									(const OpenGL::TextureMagFilter&		in_mag_filter);
        Anvil::Filter 				get_anvil_filter_for_min_filter									(const OpenGL::TextureMinFilter&		in_min_filter);
        Anvil::SamplerMipmapMode get_anvil_mipmap_mode_for_min_filter					(const OpenGL::TextureMinFilter&		in_min_filter);
        Anvil::SamplerAddressMode get_anvil_sampler_address_mode_for_texture_wrap_mode(const OpenGL::TextureWrapMode& in_wrap_mode);
        Anvil::CompareOp 		get_anvil_compare_op_for_compare_function				(const OpenGL::TextureCompareFunction& in_compare_function);
    }
}

#endif /* VKGL_VK_UTILS_H */