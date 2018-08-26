/* VKGL (c) 2018 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.0/gl_clear.h"
#include "OpenGL/entrypoints/GL1.0/gl_clear_color.h"
#include "OpenGL/entrypoints/GL1.0/gl_clear_depth.h"
#include "OpenGL/entrypoints/GL1.0/gl_clear_stencil.h"
#include "OpenGL/entrypoints/GL1.0/gl_color_mask.h"
#include "OpenGL/entrypoints/GL1.0/gl_cull_face.h"
#include "OpenGL/entrypoints/GL1.0/gl_depth_func.h"
#include "OpenGL/entrypoints/GL1.0/gl_depth_mask.h"
#include "OpenGL/entrypoints/GL1.0/gl_depth_range.h"
#include "OpenGL/entrypoints/GL1.0/gl_disable.h"
#include "OpenGL/entrypoints/GL1.0/gl_draw_buffer.h"
#include "OpenGL/entrypoints/GL1.0/gl_enable.h"
#include "OpenGL/entrypoints/GL1.0/gl_finish.h"
#include "OpenGL/entrypoints/GL1.0/gl_flush.h"
#include "OpenGL/entrypoints/GL1.0/gl_front_face.h"
#include "OpenGL/entrypoints/GL1.0/gl_get_booleanv.h"
#include "OpenGL/entrypoints/GL1.0/gl_get_doublev.h"
#include "OpenGL/entrypoints/GL1.0/gl_get_error.h"
#include "OpenGL/entrypoints/GL1.0/gl_get_floatv.h"
#include "OpenGL/entrypoints/GL1.0/gl_get_integerv.h"
#include "OpenGL/entrypoints/GL1.0/gl_get_string.h"
#include "OpenGL/entrypoints/GL1.0/gl_get_tex_image.h"
#include "OpenGL/entrypoints/GL1.0/gl_get_tex_level_parameterfv.h"
#include "OpenGL/entrypoints/GL1.0/gl_get_tex_level_parameteriv.h"
#include "OpenGL/entrypoints/GL1.0/gl_get_tex_parameterfv.h"
#include "OpenGL/entrypoints/GL1.0/gl_get_tex_parameteriv.h"
#include "OpenGL/entrypoints/GL1.0/gl_hint.h"
#include "OpenGL/entrypoints/GL1.0/gl_is_enabled.h"
#include "OpenGL/entrypoints/GL1.0/gl_line_width.h"
#include "OpenGL/entrypoints/GL1.0/gl_logic_op.h"
#include "OpenGL/entrypoints/GL1.0/gl_pixel_storef.h"
#include "OpenGL/entrypoints/GL1.0/gl_pixel_storei.h"
#include "OpenGL/entrypoints/GL1.0/gl_point_size.h"
#include "OpenGL/entrypoints/GL1.0/gl_polygon_mode.h"
#include "OpenGL/entrypoints/GL1.0/gl_read_buffer.h"
#include "OpenGL/entrypoints/GL1.0/gl_read_pixels.h"
#include "OpenGL/entrypoints/GL1.0/gl_scissor.h"
#include "OpenGL/entrypoints/GL1.0/gl_stencil_func.h"
#include "OpenGL/entrypoints/GL1.0/gl_stencil_mask.h"
#include "OpenGL/entrypoints/GL1.0/gl_stencil_op.h"
#include "OpenGL/entrypoints/GL1.0/gl_tex_image_1d.h"
#include "OpenGL/entrypoints/GL1.0/gl_tex_image_2d.h"
#include "OpenGL/entrypoints/GL1.0/gl_tex_parameterf.h"
#include "OpenGL/entrypoints/GL1.0/gl_tex_parameterfv.h"
#include "OpenGL/entrypoints/GL1.0/gl_tex_parameteri.h"
#include "OpenGL/entrypoints/GL1.0/gl_tex_parameteriv.h"
#include "OpenGL/entrypoints/GL1.0/gl_viewport.h"

#include "OpenGL/entrypoints/GL1.1/gl_bind_texture.h"
#include "OpenGL/entrypoints/GL1.1/gl_copy_tex_image_1d.h"
#include "OpenGL/entrypoints/GL1.1/gl_copy_tex_image_2d.h"
#include "OpenGL/entrypoints/GL1.1/gl_copy_tex_sub_image_1d.h"
#include "OpenGL/entrypoints/GL1.1/gl_copy_tex_sub_image_2d.h"
#include "OpenGL/entrypoints/GL1.1/gl_delete_textures.h"
#include "OpenGL/entrypoints/GL1.1/gl_draw_arrays.h"
#include "OpenGL/entrypoints/GL1.1/gl_draw_elements.h"
#include "OpenGL/entrypoints/GL1.1/gl_gen_textures.h"
#include "OpenGL/entrypoints/GL1.1/gl_is_texture.h"
#include "OpenGL/entrypoints/GL1.1/gl_polygon_offset.h"
#include "OpenGL/entrypoints/GL1.1/gl_tex_sub_image_1d.h"
#include "OpenGL/entrypoints/GL1.1/gl_tex_sub_image_2d.h"

#include "OpenGL/entrypoints/GL1.2/gl_copy_tex_sub_image_3d.h"
#include "OpenGL/entrypoints/GL1.2/gl_draw_range_elements.h"
#include "OpenGL/entrypoints/GL1.2/gl_tex_image_3d.h"
#include "OpenGL/entrypoints/GL1.2/gl_tex_sub_image_3d.h"

#include "OpenGL/entrypoints/GL1.3/gl_active_texture.h"
#include "OpenGL/entrypoints/GL1.3/gl_compressed_tex_image_1d.h"
#include "OpenGL/entrypoints/GL1.3/gl_compressed_tex_image_2d.h"
#include "OpenGL/entrypoints/GL1.3/gl_compressed_tex_image_3d.h"
#include "OpenGL/entrypoints/GL1.3/gl_compressed_tex_sub_image_1d.h"
#include "OpenGL/entrypoints/GL1.3/gl_compressed_tex_sub_image_2d.h"
#include "OpenGL/entrypoints/GL1.3/gl_compressed_tex_sub_image_3d.h"
#include "OpenGL/entrypoints/GL1.3/gl_get_compressed_tex_image.h"
#include "OpenGL/entrypoints/GL1.3/gl_sample_coverage.h"

#include "OpenGL/entrypoints/GL1.4/gl_blend_color.h"
#include "OpenGL/entrypoints/GL1.4/gl_blend_equation.h"
#include "OpenGL/entrypoints/GL1.4/gl_blend_func_separate.h"
#include "OpenGL/entrypoints/GL1.4/gl_multi_draw_arrays.h"
#include "OpenGL/entrypoints/GL1.4/gl_multi_draw_elements.h"
#include "OpenGL/entrypoints/GL1.4/gl_point_parameterf.h"
#include "OpenGL/entrypoints/GL1.4/gl_point_parameterfv.h"
#include "OpenGL/entrypoints/GL1.4/gl_point_parameteri.h"
#include "OpenGL/entrypoints/GL1.4/gl_point_parameteriv.h"

#include "OpenGL/entrypoints/GL1.5/gl_begin_query.h"
#include "OpenGL/entrypoints/GL1.5/gl_bind_buffer.h"
#include "OpenGL/entrypoints/GL1.5/gl_buffer_data.h"
#include "OpenGL/entrypoints/GL1.5/gl_buffer_sub_data.h"
#include "OpenGL/entrypoints/GL1.5/gl_delete_buffers.h"
#include "OpenGL/entrypoints/GL1.5/gl_delete_queries.h"
#include "OpenGL/entrypoints/GL1.5/gl_end_query.h"
#include "OpenGL/entrypoints/GL1.5/gl_gen_buffers.h"
#include "OpenGL/entrypoints/GL1.5/gl_gen_queries.h"
#include "OpenGL/entrypoints/GL1.5/gl_get_buffer_parameteriv.h"
#include "OpenGL/entrypoints/GL1.5/gl_get_buffer_pointerv.h"
#include "OpenGL/entrypoints/GL1.5/gl_get_buffer_sub_data.h"
#include "OpenGL/entrypoints/GL1.5/gl_get_queryiv.h"
#include "OpenGL/entrypoints/GL1.5/gl_get_query_objectiv.h"
#include "OpenGL/entrypoints/GL1.5/gl_get_query_objectuiv.h"
#include "OpenGL/entrypoints/GL1.5/gl_is_buffer.h"
#include "OpenGL/entrypoints/GL1.5/gl_is_query.h"
#include "OpenGL/entrypoints/GL1.5/gl_map_buffer.h"
#include "OpenGL/entrypoints/GL1.5/gl_unmap_buffer.h"

#include "OpenGL/entrypoints/GL2.0/gl_attach_shader.h"
#include "OpenGL/entrypoints/GL2.0/gl_bind_attrib_location.h"
#include "OpenGL/entrypoints/GL2.0/gl_blend_equation_separate.h"
#include "OpenGL/entrypoints/GL2.0/gl_compile_shader.h"
#include "OpenGL/entrypoints/GL2.0/gl_create_program.h"
#include "OpenGL/entrypoints/GL2.0/gl_create_shader.h"
#include "OpenGL/entrypoints/GL2.0/gl_delete_program.h"
#include "OpenGL/entrypoints/GL2.0/gl_delete_shader.h"
#include "OpenGL/entrypoints/GL2.0/gl_detach_shader.h"
#include "OpenGL/entrypoints/GL2.0/gl_disable_vertex_attrib_array.h"
#include "OpenGL/entrypoints/GL2.0/gl_draw_buffers.h"
#include "OpenGL/entrypoints/GL2.0/gl_enable_vertex_attrib_array.h"
#include "OpenGL/entrypoints/GL2.0/gl_get_active_attrib.h"
#include "OpenGL/entrypoints/GL2.0/gl_get_active_uniform.h"
#include "OpenGL/entrypoints/GL2.0/gl_get_attached_shaders.h"
#include "OpenGL/entrypoints/GL2.0/gl_get_attrib_location.h"
#include "OpenGL/entrypoints/GL2.0/gl_get_programiv.h"
#include "OpenGL/entrypoints/GL2.0/gl_get_program_info_log.h"
#include "OpenGL/entrypoints/GL2.0/gl_get_shaderiv.h"
#include "OpenGL/entrypoints/GL2.0/gl_get_shader_info_log.h"
#include "OpenGL/entrypoints/GL2.0/gl_get_shader_source.h"
#include "OpenGL/entrypoints/GL2.0/gl_get_uniformfv.h"
#include "OpenGL/entrypoints/GL2.0/gl_get_uniformiv.h"
#include "OpenGL/entrypoints/GL2.0/gl_get_uniform_location.h"
#include "OpenGL/entrypoints/GL2.0/gl_get_vertex_attribdv.h"
#include "OpenGL/entrypoints/GL2.0/gl_get_vertex_attribfv.h"
#include "OpenGL/entrypoints/GL2.0/gl_get_vertex_attribiv.h"
#include "OpenGL/entrypoints/GL2.0/gl_get_vertex_attrib_pointerv.h"
#include "OpenGL/entrypoints/GL2.0/gl_is_program.h"
#include "OpenGL/entrypoints/GL2.0/gl_is_shader.h"
#include "OpenGL/entrypoints/GL2.0/gl_link_program.h"
#include "OpenGL/entrypoints/GL2.0/gl_shader_source.h"
#include "OpenGL/entrypoints/GL2.0/gl_stencil_func_separate.h"
#include "OpenGL/entrypoints/GL2.0/gl_stencil_mask_separate.h"
#include "OpenGL/entrypoints/GL2.0/gl_stencil_op_separate.h"
#include "OpenGL/entrypoints/GL2.0/gl_uniform_1f.h"
#include "OpenGL/entrypoints/GL2.0/gl_uniform_1fv.h"
#include "OpenGL/entrypoints/GL2.0/gl_uniform_1i.h"
#include "OpenGL/entrypoints/GL2.0/gl_uniform_1iv.h"
#include "OpenGL/entrypoints/GL2.0/gl_uniform_2f.h"
#include "OpenGL/entrypoints/GL2.0/gl_uniform_2fv.h"
#include "OpenGL/entrypoints/GL2.0/gl_uniform_2i.h"
#include "OpenGL/entrypoints/GL2.0/gl_uniform_2iv.h"
#include "OpenGL/entrypoints/GL2.0/gl_uniform_3f.h"
#include "OpenGL/entrypoints/GL2.0/gl_uniform_3fv.h"
#include "OpenGL/entrypoints/GL2.0/gl_uniform_3i.h"
#include "OpenGL/entrypoints/GL2.0/gl_uniform_3iv.h"
#include "OpenGL/entrypoints/GL2.0/gl_uniform_4f.h"
#include "OpenGL/entrypoints/GL2.0/gl_uniform_4fv.h"
#include "OpenGL/entrypoints/GL2.0/gl_uniform_4i.h"
#include "OpenGL/entrypoints/GL2.0/gl_uniform_4iv.h"
#include "OpenGL/entrypoints/GL2.0/gl_uniform_matrix_2fv.h"
#include "OpenGL/entrypoints/GL2.0/gl_uniform_matrix_3fv.h"
#include "OpenGL/entrypoints/GL2.0/gl_uniform_matrix_4fv.h"
#include "OpenGL/entrypoints/GL2.0/gl_use_program.h"
#include "OpenGL/entrypoints/GL2.0/gl_validate_program.h"
#include "OpenGL/entrypoints/GL2.0/gl_vertex_attrib_1d.h"
#include "OpenGL/entrypoints/GL2.0/gl_vertex_attrib_1dv.h"
#include "OpenGL/entrypoints/GL2.0/gl_vertex_attrib_1f.h"
#include "OpenGL/entrypoints/GL2.0/gl_vertex_attrib_1fv.h"
#include "OpenGL/entrypoints/GL2.0/gl_vertex_attrib_1s.h"
#include "OpenGL/entrypoints/GL2.0/gl_vertex_attrib_1sv.h"
#include "OpenGL/entrypoints/GL2.0/gl_vertex_attrib_2d.h"
#include "OpenGL/entrypoints/GL2.0/gl_vertex_attrib_2dv.h"
#include "OpenGL/entrypoints/GL2.0/gl_vertex_attrib_2f.h"
#include "OpenGL/entrypoints/GL2.0/gl_vertex_attrib_2fv.h"
#include "OpenGL/entrypoints/GL2.0/gl_vertex_attrib_2s.h"
#include "OpenGL/entrypoints/GL2.0/gl_vertex_attrib_2sv.h"
#include "OpenGL/entrypoints/GL2.0/gl_vertex_attrib_3d.h"
#include "OpenGL/entrypoints/GL2.0/gl_vertex_attrib_3dv.h"
#include "OpenGL/entrypoints/GL2.0/gl_vertex_attrib_3f.h"
#include "OpenGL/entrypoints/GL2.0/gl_vertex_attrib_3fv.h"
#include "OpenGL/entrypoints/GL2.0/gl_vertex_attrib_3s.h"
#include "OpenGL/entrypoints/GL2.0/gl_vertex_attrib_3sv.h"
#include "OpenGL/entrypoints/GL2.0/gl_vertex_attrib_4bv.h"
#include "OpenGL/entrypoints/GL2.0/gl_vertex_attrib_4d.h"
#include "OpenGL/entrypoints/GL2.0/gl_vertex_attrib_4dv.h"
#include "OpenGL/entrypoints/GL2.0/gl_vertex_attrib_4f.h"
#include "OpenGL/entrypoints/GL2.0/gl_vertex_attrib_4fv.h"
#include "OpenGL/entrypoints/GL2.0/gl_vertex_attrib_4iv.h"
#include "OpenGL/entrypoints/GL2.0/gl_vertex_attrib_4Nbv.h"
#include "OpenGL/entrypoints/GL2.0/gl_vertex_attrib_4Niv.h"
#include "OpenGL/entrypoints/GL2.0/gl_vertex_attrib_4Nsv.h"
#include "OpenGL/entrypoints/GL2.0/gl_vertex_attrib_4Nub.h"
#include "OpenGL/entrypoints/GL2.0/gl_vertex_attrib_4Nubv.h"
#include "OpenGL/entrypoints/GL2.0/gl_vertex_attrib_4Nuiv.h"
#include "OpenGL/entrypoints/GL2.0/gl_vertex_attrib_4Nusv.h"
#include "OpenGL/entrypoints/GL2.0/gl_vertex_attrib_4s.h"
#include "OpenGL/entrypoints/GL2.0/gl_vertex_attrib_4sv.h"
#include "OpenGL/entrypoints/GL2.0/gl_vertex_attrib_4ubv.h"
#include "OpenGL/entrypoints/GL2.0/gl_vertex_attrib_4uiv.h"
#include "OpenGL/entrypoints/GL2.0/gl_vertex_attrib_4usv.h"
#include "OpenGL/entrypoints/GL2.0/gl_vertex_attrib_pointer.h"

#include "OpenGL/entrypoints/GL2.1/gl_uniform_matrix_2x3_fv.h"
#include "OpenGL/entrypoints/GL2.1/gl_uniform_matrix_2x4_fv.h"
#include "OpenGL/entrypoints/GL2.1/gl_uniform_matrix_3x2_fv.h"
#include "OpenGL/entrypoints/GL2.1/gl_uniform_matrix_3x4_fv.h"
#include "OpenGL/entrypoints/GL2.1/gl_uniform_matrix_4x2_fv.h"
#include "OpenGL/entrypoints/GL2.1/gl_uniform_matrix_4x3_fv.h"

#include "OpenGL/entrypoints/GL3.0/gl_begin_conditional_render.h"
#include "OpenGL/entrypoints/GL3.0/gl_begin_transform_feedback.h"
#include "OpenGL/entrypoints/GL3.0/gl_bind_buffer_base.h"
#include "OpenGL/entrypoints/GL3.0/gl_bind_buffer_range.h"
#include "OpenGL/entrypoints/GL3.0/gl_bind_frag_data_location.h"
#include "OpenGL/entrypoints/GL3.0/gl_bind_framebuffer.h"
#include "OpenGL/entrypoints/GL3.0/gl_bind_renderbuffer.h"
#include "OpenGL/entrypoints/GL3.0/gl_bind_vertex_array.h"
#include "OpenGL/entrypoints/GL3.0/gl_blit_framebuffer.h"
#include "OpenGL/entrypoints/GL3.0/gl_check_framebuffer_status.h"
#include "OpenGL/entrypoints/GL3.0/gl_clamp_color.h"
#include "OpenGL/entrypoints/GL3.0/gl_clear_buffer_fi.h"
#include "OpenGL/entrypoints/GL3.0/gl_clear_buffer_fv.h"
#include "OpenGL/entrypoints/GL3.0/gl_clear_buffer_iv.h"
#include "OpenGL/entrypoints/GL3.0/gl_clear_buffer_uiv.h"
#include "OpenGL/entrypoints/GL3.0/gl_color_maski.h"
#include "OpenGL/entrypoints/GL3.0/gl_delete_framebuffers.h"
#include "OpenGL/entrypoints/GL3.0/gl_delete_renderbuffers.h"
#include "OpenGL/entrypoints/GL3.0/gl_delete_vertex_arrays.h"
#include "OpenGL/entrypoints/GL3.0/gl_disablei.h"
#include "OpenGL/entrypoints/GL3.0/gl_enablei.h"
#include "OpenGL/entrypoints/GL3.0/gl_end_conditional_render.h"
#include "OpenGL/entrypoints/GL3.0/gl_end_transform_feedback.h"
#include "OpenGL/entrypoints/GL3.0/gl_flush_mapped_buffer_range.h"
#include "OpenGL/entrypoints/GL3.0/gl_framebuffer_renderbuffer.h"
#include "OpenGL/entrypoints/GL3.0/gl_framebuffer_texture_1d.h"
#include "OpenGL/entrypoints/GL3.0/gl_framebuffer_texture_2d.h"
#include "OpenGL/entrypoints/GL3.0/gl_framebuffer_texture_3d.h"
#include "OpenGL/entrypoints/GL3.0/gl_framebuffer_texture_layer.h"
#include "OpenGL/entrypoints/GL3.0/gl_generate_mipmap.h"
#include "OpenGL/entrypoints/GL3.0/gl_gen_framebuffers.h"
#include "OpenGL/entrypoints/GL3.0/gl_gen_renderbuffers.h"
#include "OpenGL/entrypoints/GL3.0/gl_gen_vertex_arrays.h"
#include "OpenGL/entrypoints/GL3.0/gl_get_booleani_v.h"
#include "OpenGL/entrypoints/GL3.0/gl_get_frag_data_location.h"
#include "OpenGL/entrypoints/GL3.0/gl_get_framebuffer_attachment_parameteriv.h"
#include "OpenGL/entrypoints/GL3.0/gl_get_integeri_v.h"
#include "OpenGL/entrypoints/GL3.0/gl_get_renderbuffer_parameteriv.h"
#include "OpenGL/entrypoints/GL3.0/gl_get_stringi.h"
#include "OpenGL/entrypoints/GL3.0/gl_get_tex_parameter_i_iv.h"
#include "OpenGL/entrypoints/GL3.0/gl_get_tex_parameter_i_uiv.h"
#include "OpenGL/entrypoints/GL3.0/gl_get_transform_feedback_varying.h"
#include "OpenGL/entrypoints/GL3.0/gl_get_uniformuiv.h"
#include "OpenGL/entrypoints/GL3.0/gl_get_vertex_attrib_i_iv.h"
#include "OpenGL/entrypoints/GL3.0/gl_get_vertex_attrib_i_uiv.h"
#include "OpenGL/entrypoints/GL3.0/gl_is_enabledi.h"
#include "OpenGL/entrypoints/GL3.0/gl_is_framebuffer.h"
#include "OpenGL/entrypoints/GL3.0/gl_is_renderbuffer.h"
#include "OpenGL/entrypoints/GL3.0/gl_is_vertex_array.h"
#include "OpenGL/entrypoints/GL3.0/gl_map_buffer_range.h"
#include "OpenGL/entrypoints/GL3.0/gl_renderbuffer_storage.h"
#include "OpenGL/entrypoints/GL3.0/gl_renderbuffer_storage_multisample.h"
#include "OpenGL/entrypoints/GL3.0/gl_tex_parameter_i_iv.h"
#include "OpenGL/entrypoints/GL3.0/gl_tex_parameter_i_uiv.h"
#include "OpenGL/entrypoints/GL3.0/gl_transform_feedback_varyings.h"
#include "OpenGL/entrypoints/GL3.0/gl_uniform_1ui.h"
#include "OpenGL/entrypoints/GL3.0/gl_uniform_1uiv.h"
#include "OpenGL/entrypoints/GL3.0/gl_uniform_2ui.h"
#include "OpenGL/entrypoints/GL3.0/gl_uniform_2uiv.h"
#include "OpenGL/entrypoints/GL3.0/gl_uniform_3ui.h"
#include "OpenGL/entrypoints/GL3.0/gl_uniform_3uiv.h"
#include "OpenGL/entrypoints/GL3.0/gl_uniform_4ui.h"
#include "OpenGL/entrypoints/GL3.0/gl_uniform_4uiv.h"
#include "OpenGL/entrypoints/GL3.0/gl_vertex_attrib_i_1i.h"
#include "OpenGL/entrypoints/GL3.0/gl_vertex_attrib_i_1iv.h"
#include "OpenGL/entrypoints/GL3.0/gl_vertex_attrib_i_1ui.h"
#include "OpenGL/entrypoints/GL3.0/gl_vertex_attrib_i_1uiv.h"
#include "OpenGL/entrypoints/GL3.0/gl_vertex_attrib_i_2i.h"
#include "OpenGL/entrypoints/GL3.0/gl_vertex_attrib_i_2iv.h"
#include "OpenGL/entrypoints/GL3.0/gl_vertex_attrib_i_2ui.h"
#include "OpenGL/entrypoints/GL3.0/gl_vertex_attrib_i_2uiv.h"
#include "OpenGL/entrypoints/GL3.0/gl_vertex_attrib_i_3i.h"
#include "OpenGL/entrypoints/GL3.0/gl_vertex_attrib_i_3iv.h"
#include "OpenGL/entrypoints/GL3.0/gl_vertex_attrib_i_3ui.h"
#include "OpenGL/entrypoints/GL3.0/gl_vertex_attrib_i_3uiv.h"
#include "OpenGL/entrypoints/GL3.0/gl_vertex_attrib_i_4bv.h"
#include "OpenGL/entrypoints/GL3.0/gl_vertex_attrib_i_4i.h"
#include "OpenGL/entrypoints/GL3.0/gl_vertex_attrib_i_4iv.h"
#include "OpenGL/entrypoints/GL3.0/gl_vertex_attrib_i_4sv.h"
#include "OpenGL/entrypoints/GL3.0/gl_vertex_attrib_i_4ubv.h"
#include "OpenGL/entrypoints/GL3.0/gl_vertex_attrib_i_4ui.h"
#include "OpenGL/entrypoints/GL3.0/gl_vertex_attrib_i_4uiv.h"
#include "OpenGL/entrypoints/GL3.0/gl_vertex_attrib_i_4usv.h"
#include "OpenGL/entrypoints/GL3.0/gl_vertex_attrib_i_pointer.h"

#include "OpenGL/entrypoints/GL3.1/gl_copy_buffer_sub_data.h"
#include "OpenGL/entrypoints/GL3.1/gl_draw_arrays_instanced.h"
#include "OpenGL/entrypoints/GL3.1/gl_draw_elements_instanced.h"
#include "OpenGL/entrypoints/GL3.1/gl_get_active_uniformsiv.h"
#include "OpenGL/entrypoints/GL3.1/gl_get_active_uniform_blockiv.h"
#include "OpenGL/entrypoints/GL3.1/gl_get_active_uniform_block_name.h"
#include "OpenGL/entrypoints/GL3.1/gl_get_active_uniform_name.h"
#include "OpenGL/entrypoints/GL3.1/gl_get_uniform_block_index.h"
#include "OpenGL/entrypoints/GL3.1/gl_get_uniform_indices.h"
#include "OpenGL/entrypoints/GL3.1/gl_primitive_restart_index.h"
#include "OpenGL/entrypoints/GL3.1/gl_tex_buffer.h"
#include "OpenGL/entrypoints/GL3.1/gl_uniform_block_binding.h"

#include "OpenGL/entrypoints/GL3.2/gl_client_wait_sync.h"
#include "OpenGL/entrypoints/GL3.2/gl_delete_sync.h"
#include "OpenGL/entrypoints/GL3.2/gl_draw_elements_base_vertex.h"
#include "OpenGL/entrypoints/GL3.2/gl_draw_elements_instanced_base_vertex.h"
#include "OpenGL/entrypoints/GL3.2/gl_draw_range_elements_base_vertex.h"
#include "OpenGL/entrypoints/GL3.2/gl_fence_sync.h"
#include "OpenGL/entrypoints/GL3.2/gl_framebuffer_texture.h"
#include "OpenGL/entrypoints/GL3.2/gl_get_buffer_parameteri64v.h"
#include "OpenGL/entrypoints/GL3.2/gl_get_integer64i_v.h"
#include "OpenGL/entrypoints/GL3.2/gl_get_integer64v.h"
#include "OpenGL/entrypoints/GL3.2/gl_get_multisamplefv.h"
#include "OpenGL/entrypoints/GL3.2/gl_get_synciv.h"
#include "OpenGL/entrypoints/GL3.2/gl_is_sync.h"
#include "OpenGL/entrypoints/GL3.2/gl_multi_draw_elements_base_vertex.h"
#include "OpenGL/entrypoints/GL3.2/gl_provoking_vertex.h"
#include "OpenGL/entrypoints/GL3.2/gl_sample_maski.h"
#include "OpenGL/entrypoints/GL3.2/gl_tex_image_2d_multisample.h"
#include "OpenGL/entrypoints/GL3.2/gl_tex_image_3d_multisample.h"
#include "OpenGL/entrypoints/GL3.2/gl_wait_sync.h"

#include "OpenGL/entrypoints/GL_ARB_color_buffer_float/gl_clamp_color_arb.h"

#include "OpenGL/entrypoints/GL_ARB_draw_buffers/gl_draw_buffers_arb.h"

#include "OpenGL/entrypoints/GL_ARB_draw_instanced/gl_draw_arrays_instanced_arb.h"
#include "OpenGL/entrypoints/GL_ARB_draw_instanced/gl_draw_elements_instanced_arb.h"

#include "OpenGL/entrypoints/GL_ARB_multisample/gl_sample_coverage_arb.h"

#include "OpenGL/entrypoints/GL_ARB_multitexture/gl_active_texture_arb.h"

#include "OpenGL/entrypoints/GL_ARB_occlusion_query/gl_begin_query_arb.h"
#include "OpenGL/entrypoints/GL_ARB_occlusion_query/gl_delete_queries_arb.h"
#include "OpenGL/entrypoints/GL_ARB_occlusion_query/gl_end_query_arb.h"
#include "OpenGL/entrypoints/GL_ARB_occlusion_query/gl_gen_queries_arb.h"
#include "OpenGL/entrypoints/GL_ARB_occlusion_query/gl_get_queryiv_arb.h"
#include "OpenGL/entrypoints/GL_ARB_occlusion_query/gl_get_query_objectiv_arb.h"
#include "OpenGL/entrypoints/GL_ARB_occlusion_query/gl_get_query_objectuiv_arb.h"
#include "OpenGL/entrypoints/GL_ARB_occlusion_query/gl_is_query_arb.h"

#include "OpenGL/entrypoints/GL_ARB_point_parameters/gl_point_parameterf_arb.h"
#include "OpenGL/entrypoints/GL_ARB_point_parameters/gl_point_parameterfv_arb.h"

#include "OpenGL/entrypoints/GL_ARB_texture_buffer_object/gl_tex_buffer_arb.h"

#include "OpenGL/entrypoints/GL_ARB_texture_compression/gl_compressed_tex_image_1d_arb.h"
#include "OpenGL/entrypoints/GL_ARB_texture_compression/gl_compressed_tex_image_2d_arb.h"
#include "OpenGL/entrypoints/GL_ARB_texture_compression/gl_compressed_tex_image_3d_arb.h"
#include "OpenGL/entrypoints/GL_ARB_texture_compression/gl_compressed_tex_sub_image_1d_arb.h"
#include "OpenGL/entrypoints/GL_ARB_texture_compression/gl_compressed_tex_sub_image_2d_arb.h"
#include "OpenGL/entrypoints/GL_ARB_texture_compression/gl_compressed_tex_sub_image_3d_arb.h"
#include "OpenGL/entrypoints/GL_ARB_texture_compression/gl_get_compressed_tex_image_arb.h"

#include "OpenGL/entrypoints/GL_ARB_vertex_buffer_object/gl_bind_buffer_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_buffer_object/gl_buffer_data_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_buffer_object/gl_buffer_sub_data_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_buffer_object/gl_delete_buffers_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_buffer_object/gl_gen_buffers_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_buffer_object/gl_get_buffer_parameteriv_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_buffer_object/gl_get_buffer_pointerv_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_buffer_object/gl_get_buffer_sub_data_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_buffer_object/gl_is_buffer_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_buffer_object/gl_map_buffer_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_buffer_object/gl_unmap_buffer_arb.h"

#include "OpenGL/entrypoints/GL_ARB_vertex_program/gl_disable_vertex_attrib_array_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_program/gl_enable_vertex_attrib_array_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_program/gl_get_vertex_attribdv_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_program/gl_get_vertex_attribfv_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_program/gl_get_vertex_attribiv_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_program/gl_get_vertex_attrib_pointerv_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_1dv_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_1d_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_1fv_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_1f_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_1sv_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_1s_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_2dv_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_2d_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_2fv_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_2f_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_2sv_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_2s_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_3dv_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_3d_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_3fv_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_3f_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_3sv_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_3s_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_4bv_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_4dv_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_4d_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_4fv_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_4f_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_4iv_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_4Nbv_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_4Niv_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_4Nsv_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_4Nubv_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_4Nub_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_4Nuiv_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_4sv_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_4s_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_4ubv_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_4uiv_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_4usv_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_pointer_arb.h"

#include "OpenGL/entrypoints/GL_ARB_vertex_shader/gl_bind_attrib_location_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_shader/gl_get_active_attrib_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_shader/gl_get_attrib_location_arb.h"

#include "OpenGL/globals.h"
#include "OpenGL/interceptors.h"

std::unordered_map<std::string, void*> vkgl_get_func_name_to_func_ptr_map()
{
    /* >= GL 1.2 */
    std::unordered_map<std::string, void*> result;

    result["glCopyTexSubImage3D"] = vkglCopyTexSubImage3D_with_validation;
    result["glDrawRangeElements"] = vkglDrawRangeElements_with_validation;
    result["glTexImage3D"]        = vkglTexImage3D;
    result["glTexSubImage3D"]     = vkglTexSubImage3D;

    result["glActiveTexture"]           = vkglActiveTexture_with_validation;
    result["glCompressedTexImage1D"]    = vkglCompressedTexImage1D_with_validation;
    result["glCompressedTexImage2D"]    = vkglCompressedTexImage2D_with_validation;
    result["glCompressedTexImage3D"]    = vkglCompressedTexImage3D_with_validation;
    result["glCompressedTexSubImage1D"] = vkglCompressedTexSubImage1D_with_validation;
    result["glCompressedTexSubImage2D"] = vkglCompressedTexSubImage2D_with_validation;
    result["glCompressedTexSubImage3D"] = vkglCompressedTexSubImage3D_with_validation;
    result["glGetCompressedTexImage"]   = vkglGetCompressedTexImage_with_validation;
    result["glSampleCoverage"]          = vkglSampleCoverage_with_validation;

    result["glBlendColor"]        = vkglBlendColor_with_validation;
    result["glBlendEquation"]     = vkglBlendEquation_with_validation;
    result["glBlendFuncSeparate"] = vkglBlendFuncSeparate_with_validation;
    result["glMultiDrawArrays"]   = vkglMultiDrawArrays_with_validation;
    result["glMultiDrawElements"] = vkglMultiDrawElements_with_validation;
    result["glPointParameterf"]   = vkglPointParameterf_with_validation;
    result["glPointParameterfv"]  = vkglPointParameterfv_with_validation;
    result["glPointParameteri"]   = vkglPointParameteri_with_validation;
    result["glPointParameteriv"]  = vkglPointParameteriv_with_validation;

    result["glBeginQuery"]           = vkglBeginQuery_with_validation;
    result["glBindBuffer"]           = vkglBindBuffer_with_validation;
    result["glBufferData"]           = vkglBufferData_with_validation;
    result["glBufferSubData"]        = vkglBufferSubData_with_validation;
    result["glDeleteBuffers"]        = vkglDeleteBuffers_with_validation;
    result["glDeleteQueries"]        = vkglDeleteQueries_with_validation;
    result["glEndQuery"]             = vkglEndQuery_with_validation;
    result["glGenBuffers"]           = vkglGenBuffers_with_validation;
    result["glGenQueries"]           = vkglGenQueries_with_validation;
    result["glGetBufferParameteriv"] = vkglGetBufferParameteriv_with_validation;
    result["glGetBufferPointerv"]    = vkglGetBufferPointerv_with_validation;
    result["glGetBufferSubData"]     = vkglGetBufferSubData_with_validation;
    result["glGetQueryiv"]           = vkglGetQueryiv_with_validation;
    result["glGetQueryObjectiv"]     = vkglGetQueryObjectiv_with_validation;
    result["glGetQueryObjectuiv"]    = vkglGetQueryObjectuiv_with_validation;
    result["glIsBuffer"]             = vkglIsBuffer_with_validation;
    result["glIsQuery"]              = vkglIsQuery_with_validation;
    result["glMapBuffer"]            = vkglMapBuffer_with_validation;
    result["glUnmapBuffer"]          = vkglUnmapBuffer_with_validation;

    result["glAttachShader"]             = vkglAttachShader_with_validation;
    result["glBindAttribLocation"]       = vkglBindAttribLocation_with_validation;
    result["glBlendEquationSeparate"]    = vkglBlendEquationSeparate_with_validation;
    result["glCompileShader"]            = vkglCompileShader_with_validation;
    result["glCreateProgram"]            = vkglCreateProgram_with_validation;
    result["glCreateShader"]             = vkglCreateShader_with_validation;
    result["glDeleteProgram"]            = vkglDeleteProgram_with_validation;
    result["glDeleteShader"]             = vkglDeleteShader_with_validation;
    result["glDetachShader"]             = vkglDetachShader_with_validation;
    result["glDisableVertexAttribArray"] = vkglDisableVertexAttribArray_with_validation;
    result["glDrawBuffers"]              = vkglDrawBuffers_with_validation;
    result["glEnableVertexAttribArray"]  = vkglEnableVertexAttribArray_with_validation;
    result["glGetActiveAttrib"]          = vkglGetActiveAttrib_with_validation;
    result["glGetActiveUniform"]         = vkglGetActiveUniform_with_validation;
    result["glGetAttachedShaders"]       = vkglGetAttachedShaders_with_validation;
    result["glGetAttribLocation"]        = vkglGetAttribLocation_with_validation;
    result["glGetProgramiv"]             = vkglGetProgramiv_with_validation;
    result["glGetProgramInfoLog"]        = vkglGetProgramInfoLog_with_validation;
    result["glGetShaderiv"]              = vkglGetShaderiv_with_validation;
    result["glGetShaderInfoLog"]         = vkglGetShaderInfoLog_with_validation;
    result["glGetShaderSource"]          = vkglGetShaderSource_with_validation;
    result["glGetUniformfv"]             = vkglGetUniformfv_with_validation;
    result["glGetUniformiv"]             = vkglGetUniformiv_with_validation;
    result["glGetUniformLocation"]       = vkglGetUniformLocation_with_validation;
    result["glGetVertexAttribdv"]        = vkglGetVertexAttribdv_with_validation;
    result["glGetVertexAttribfv"]        = vkglGetVertexAttribfv_with_validation;
    result["glGetVertexAttribiv"]        = vkglGetVertexAttribiv_with_validation;
    result["glGetVertexAttribPointerv"]  = vkglGetVertexAttribPointerv_with_validation;
    result["glIsProgram"]                = vkglIsProgram_with_validation;
    result["glIsShader"]                 = vkglIsShader_with_validation;
    result["glLinkProgram"]              = vkglLinkProgram_with_validation;
    result["glShaderSource"]             = vkglShaderSource_with_validation;
    result["glStencilFuncSeparate"]      = vkglStencilFuncSeparate_with_validation;
    result["glStencilMaskSeparate"]      = vkglStencilMaskSeparate_with_validation;
    result["glStencilOpSeparate"]        = vkglStencilOpSeparate_with_validation;
    result["glUniform1f"]                = vkglUniform1f_with_validation;
    result["glUniform1fv"]               = vkglUniform1fv_with_validation;
    result["glUniform1i"]                = vkglUniform1i_with_validation;
    result["glUniform1iv"]               = vkglUniform1iv_with_validation;
    result["glUniform2f"]                = vkglUniform2f_with_validation;
    result["glUniform2fv"]               = vkglUniform2fv_with_validation;
    result["glUniform2i"]                = vkglUniform2i_with_validation;
    result["glUniform2iv"]               = vkglUniform2iv_with_validation;
    result["glUniform3f"]                = vkglUniform3f_with_validation;
    result["glUniform3fv"]               = vkglUniform3fv_with_validation;
    result["glUniform3i"]                = vkglUniform3i_with_validation;
    result["glUniform3iv"]               = vkglUniform3iv_with_validation;
    result["glUniform4f"]                = vkglUniform4f_with_validation;
    result["glUniform4fv"]               = vkglUniform4fv_with_validation;
    result["glUniform4i"]                = vkglUniform4i_with_validation;
    result["glUniform4iv"]               = vkglUniform4iv_with_validation;
    result["glUniformMatrix2fv"]         = vkglUniformMatrix2fv_with_validation;
    result["glUniformMatrix3fv"]         = vkglUniformMatrix3fv_with_validation;
    result["glUniformMatrix4fv"]         = vkglUniformMatrix4fv_with_validation;
    result["glUseProgram"]               = vkglUseProgram_with_validation;
    result["glValidateProgram"]          = vkglValidateProgram_with_validation;
    result["glVertexAttrib1d"]           = vkglVertexAttrib1d_with_validation;
    result["glVertexAttrib1dv"]          = vkglVertexAttrib1dv_with_validation;
    result["glVertexAttrib1f"]           = vkglVertexAttrib1f_with_validation;
    result["glVertexAttrib1fv"]          = vkglVertexAttrib1fv_with_validation;
    result["glVertexAttrib1s"]           = vkglVertexAttrib1s_with_validation;
    result["glVertexAttrib1sv"]          = vkglVertexAttrib1sv_with_validation;
    result["glVertexAttrib2d"]           = vkglVertexAttrib2d_with_validation;
    result["glVertexAttrib2dv"]          = vkglVertexAttrib2dv_with_validation;
    result["glVertexAttrib2f"]           = vkglVertexAttrib2f_with_validation;
    result["glVertexAttrib2fv"]          = vkglVertexAttrib2fv_with_validation;
    result["glVertexAttrib2s"]           = vkglVertexAttrib2s_with_validation;
    result["glVertexAttrib2sv"]          = vkglVertexAttrib2sv_with_validation;
    result["glVertexAttrib3d"]           = vkglVertexAttrib3d_with_validation;
    result["glVertexAttrib3dv"]          = vkglVertexAttrib3dv_with_validation;
    result["glVertexAttrib3f"]           = vkglVertexAttrib3f_with_validation;
    result["glVertexAttrib3fv"]          = vkglVertexAttrib3fv_with_validation;
    result["glVertexAttrib3s"]           = vkglVertexAttrib3s_with_validation;
    result["glVertexAttrib3sv"]          = vkglVertexAttrib3sv_with_validation;
    result["glVertexAttrib4bv"]          = vkglVertexAttrib4bv_with_validation;
    result["glVertexAttrib4d"]           = vkglVertexAttrib4d_with_validation;
    result["glVertexAttrib4dv"]          = vkglVertexAttrib4dv_with_validation;
    result["glVertexAttrib4f"]           = vkglVertexAttrib4f_with_validation;
    result["glVertexAttrib4fv"]          = vkglVertexAttrib4fv_with_validation;
    result["glVertexAttrib4iv"]          = vkglVertexAttrib4iv_with_validation;
    result["glVertexAttrib4Nbv"]         = vkglVertexAttrib4Nbv_with_validation;
    result["glVertexAttrib4Niv"]         = vkglVertexAttrib4Niv_with_validation;
    result["glVertexAttrib4Nsv"]         = vkglVertexAttrib4Nsv_with_validation;
    result["glVertexAttrib4Nub"]         = vkglVertexAttrib4Nub_with_validation;
    result["glVertexAttrib4Nubv"]        = vkglVertexAttrib4Nubv_with_validation;
    result["glVertexAttrib4Nuiv"]        = vkglVertexAttrib4Nuiv_with_validation;
    result["glVertexAttrib4Nusv"]        = vkglVertexAttrib4Nusv_with_validation;
    result["glVertexAttrib4s"]           = vkglVertexAttrib4s_with_validation;
    result["glVertexAttrib4sv"]          = vkglVertexAttrib4sv_with_validation;
    result["glVertexAttrib4ubv"]         = vkglVertexAttrib4ubv_with_validation;
    result["glVertexAttrib4uiv"]         = vkglVertexAttrib4uiv_with_validation;
    result["glVertexAttrib4usv"]         = vkglVertexAttrib4usv_with_validation;
    result["glVertexAttribPointer"]      = vkglVertexAttribPointer_with_validation;

    result["glUniformMatrix2x3fv"] = vkglUniformMatrix2x3fv_with_validation;
    result["glUniformMatrix2x4fv"] = vkglUniformMatrix2x4fv_with_validation;
    result["glUniformMatrix3x2fv"] = vkglUniformMatrix3x2fv_with_validation;
    result["glUniformMatrix3x4fv"] = vkglUniformMatrix3x4fv_with_validation;
    result["glUniformMatrix4x2fv"] = vkglUniformMatrix4x2fv_with_validation;
    result["glUniformMatrix4x3fv"] = vkglUniformMatrix4x3fv_with_validation;

    result["glBeginConditionalRender"]              = vkglBeginConditionalRender_with_validation;
    result["glBeginTransformFeedback"]              = vkglBeginTransformFeedback_with_validation;
    result["glBindBufferBase"]                      = vkglBindBufferBase_with_validation;
    result["glBindBufferRange"]                     = vkglBindBufferRange_with_validation;
    result["glBindFragDataLocation"]                = vkglBindFragDataLocation_with_validation;
    result["glBindFramebuffer"]                     = vkglBindFramebuffer_with_validation;
    result["glBindRenderbuffer"]                    = vkglBindRenderbuffer_with_validation;
    result["glBindVertexArray"]                     = vkglBindVertexArray_with_validation;
    result["glBlitFramebuffer"]                     = vkglBlitFramebuffer_with_validation;
    result["glCheckFramebufferStatus"]              = vkglCheckFramebufferStatus_with_validation;
    result["glClampColor"]                          = vkglClampColor_with_validation;
    result["glClearBufferfi"]                       = vkglClearBufferfi_with_validation;
    result["glClearBufferfv"]                       = vkglClearBufferfv_with_validation;
    result["glClearBufferiv"]                       = vkglClearBufferiv_with_validation;
    result["glClearBufferuiv"]                      = vkglClearBufferuiv_with_validation;
    result["glColorMaski"]                          = vkglColorMaski_with_validation;
    result["glDeleteFramebuffers"]                  = vkglDeleteFramebuffers_with_validation;
    result["glDeleteRenderbuffers"]                 = vkglDeleteRenderbuffers_with_validation;
    result["glDeleteVertexArrays"]                  = vkglDeleteVertexArrays_with_validation;
    result["glDisablei"]                            = vkglDisablei_with_validation;
    result["glEnablei"]                             = vkglEnablei_with_validation;
    result["glEndConditionalRender"]                = vkglEndConditionalRender_with_validation;
    result["glEndTransformFeedback"]                = vkglEndTransformFeedback_with_validation;
    result["glFlushMappedBufferRange"]              = vkglFlushMappedBufferRange_with_validation;
    result["glFramebufferRenderbuffer"]             = vkglFramebufferRenderbuffer_with_validation;
    result["glFramebufferTexture1D"]                = vkglFramebufferTexture1D_with_validation;
    result["glFramebufferTexture2D"]                = vkglFramebufferTexture2D_with_validation;
    result["glFramebufferTexture3D"]                = vkglFramebufferTexture3D_with_validation;
    result["glFramebufferTextureLayer"]             = vkglFramebufferTextureLayer_with_validation;
    result["glGenerateMipmap"]                      = vkglGenerateMipmap_with_validation;
    result["glGenFramebuffers"]                     = vkglGenFramebuffers_with_validation;
    result["glGenRenderbuffers"]                    = vkglGenRenderbuffers_with_validation;
    result["glGenVertexArrays"]                     = vkglGenVertexArrays_with_validation;
    result["glGetBooleani_v"]                       = vkglGetBooleani_v_with_validation;
    result["glGetFragDataLocation"]                 = vkglGetFragDataLocation_with_validation;
    result["glGetFramebufferAttachmentParameteriv"] = vkglGetFramebufferAttachmentParameteriv_with_validation;
    result["glGetIntegeri_v"]                       = vkglGetIntegeri_v_with_validation;
    result["glGetRenderbufferParameteriv"]          = vkglGetRenderbufferParameteriv_with_validation;
    result["glGetStringi"]                          = vkglGetStringi_with_validation;
    result["glGetTexParameterIiv"]                  = vkglGetTexParameterIiv_with_validation;
    result["glGetTexParameterIuiv"]                 = vkglGetTexParameterIuiv_with_validation;
    result["glGetTransformFeedbackVarying"]         = vkglGetTransformFeedbackVarying_with_validation;
    result["glGetUniformuiv"]                       = vkglGetUniformuiv_with_validation;
    result["glGetVertexAttribIiv"]                  = vkglGetVertexAttribIiv_with_validation;
    result["glGetVertexAttribIuiv"]                 = vkglGetVertexAttribIuiv_with_validation;
    result["glIsEnabledi"]                          = vkglIsEnabledi_with_validation;
    result["glIsFramebuffer"]                       = vkglIsFramebuffer_with_validation;
    result["glIsRenderbuffer"]                      = vkglIsRenderbuffer_with_validation;
    result["glIsVertexArray"]                       = vkglIsVertexArray_with_validation;
    result["glMapBufferRange"]                      = vkglMapBufferRange_with_validation;
    result["glRenderbufferStorage"]                 = vkglRenderbufferStorage_with_validation;
    result["glRenderbufferStorageMultisample"]      = vkglRenderbufferStorageMultisample_with_validation;
    result["glTexParameterIiv"]                     = vkglTexParameterIiv_with_validation;
    result["glTexParameterIuiv"]                    = vkglTexParameterIuiv_with_validation;
    result["glTransformFeedbackVaryings"]           = vkglTransformFeedbackVaryings_with_validation;
    result["glUniform1ui"]                          = vkglUniform1ui_with_validation;
    result["glUniform1uiv"]                         = vkglUniform1uiv_with_validation;
    result["glUniform2ui"]                          = vkglUniform2ui_with_validation;
    result["glUniform2uiv"]                         = vkglUniform2uiv_with_validation;
    result["glUniform3ui"]                          = vkglUniform3ui_with_validation;
    result["glUniform3uiv"]                         = vkglUniform3uiv_with_validation;
    result["glUniform4ui"]                          = vkglUniform4ui_with_validation;
    result["glUniform4uiv"]                         = vkglUniform4uiv_with_validation;
    result["glVertexAttribI1i"]                     = vkglVertexAttribI1i_with_validation;
    result["glVertexAttribI1iv"]                    = vkglVertexAttribI1iv_with_validation;
    result["glVertexAttribI1ui"]                    = vkglVertexAttribI1ui_with_validation;
    result["glVertexAttribI1uiv"]                   = vkglVertexAttribI1uiv_with_validation;
    result["glVertexAttribI2i"]                     = vkglVertexAttribI2i_with_validation;
    result["glVertexAttribI2iv"]                    = vkglVertexAttribI2iv_with_validation;
    result["glVertexAttribI2ui"]                    = vkglVertexAttribI2ui_with_validation;
    result["glVertexAttribI2uiv"]                   = vkglVertexAttribI2uiv_with_validation;
    result["glVertexAttribI3i"]                     = vkglVertexAttribI3i_with_validation;
    result["glVertexAttribI3iv"]                    = vkglVertexAttribI3iv_with_validation;
    result["glVertexAttribI3ui"]                    = vkglVertexAttribI3ui_with_validation;
    result["glVertexAttribI3uiv"]                   = vkglVertexAttribI3uiv_with_validation;
    result["glVertexAttribI4bv"]                    = vkglVertexAttribI4bv_with_validation;
    result["glVertexAttribI4i"]                     = vkglVertexAttribI4i_with_validation;
    result["glVertexAttribI4iv"]                    = vkglVertexAttribI4iv_with_validation;
    result["glVertexAttribI4sv"]                    = vkglVertexAttribI4sv_with_validation;
    result["glVertexAttribI4ubv"]                   = vkglVertexAttribI4ubv_with_validation;
    result["glVertexAttribI4ui"]                    = vkglVertexAttribI4ui_with_validation;
    result["glVertexAttribI4uiv"]                   = vkglVertexAttribI4uiv_with_validation;
    result["glVertexAttribI4usv"]                   = vkglVertexAttribI4usv_with_validation;
    result["glVertexAttribIPointer"]                = vkglVertexAttribIPointer_with_validation;

    result["glCopyBufferSubData"]         = vkglCopyBufferSubData_with_validation;
    result["glDrawArraysInstanced"]       = vkglDrawArraysInstanced_with_validation;
    result["glDrawElementsInstanced"]     = vkglDrawElementsInstanced_with_validation;
    result["glGetActiveUniformsiv"]       = vkglGetActiveUniformsiv_with_validation;
    result["glGetActiveUniformBlockiv"]   = vkglGetActiveUniformBlockiv_with_validation;
    result["glGetActiveUniformBlockName"] = vkglGetActiveUniformBlockName_with_validation;
    result["glGetActiveUniformName"]      = vkglGetActiveUniformName_with_validation;
    result["glGetUniformBlockIndex"]      = vkglGetUniformBlockIndex_with_validation;
    result["glGetUniformIndices"]         = vkglGetUniformIndices_with_validation;
    result["glPrimitiveRestartIndex"]     = vkglPrimitiveRestartIndex_with_validation;
    result["glTexBuffer"]                 = vkglTexBuffer_with_validation;
    result["glUniformBlockBinding"]       = vkglUniformBlockBinding_with_validation;

    result["glClientWaitSync"]                  = vkglClientWaitSync_with_validation;
    result["glDeleteSync"]                      = vkglDeleteSync_with_validation;
    result["glDrawElementsBaseVertex"]          = vkglDrawElementsBaseVertex_with_validation;
    result["glDrawElementsInstancedBaseVertex"] = vkglDrawElementsInstancedBaseVertex_with_validation;
    result["glDrawRangeElementsBaseVertex"]     = vkglDrawRangeElementsBaseVertex_with_validation;
    result["glFenceSync"]                       = vkglFenceSync_with_validation;
    result["glFramebufferTexture"]              = vkglFramebufferTexture_with_validation;
    result["glGetBufferParameteri64v"]          = vkglGetBufferParameteri64v_with_validation;
    result["glGetInteger64i_v"]                 = vkglGetInteger64i_v_with_validation;
    result["glGetInteger64v"]                   = vkglGetInteger64v_with_validation;
    result["glGetMultisamplefv"]                = vkglGetMultisamplefv_with_validation;
    result["glGetSynciv"]                       = vkglGetSynciv_with_validation;
    result["glIsSync"]                          = vkglIsSync_with_validation;
    result["glMultiDrawElementsBaseVertex"]     = vkglMultiDrawElementsBaseVertex_with_validation;
    result["glProvokingVertex"]                 = vkglProvokingVertex_with_validation;
    result["glSampleMaski"]                     = vkglSampleMaski_with_validation;
    result["glTexImage2DMultisample"]           = vkglTexImage2DMultisample_with_validation;
    result["glTexImage3DMultisample"]           = vkglTexImage3DMultisample_with_validation;
    result["glWaitSync"]                        = vkglWaitSync_with_validation;

    result["glClampColorARB"] = vkglClampColorARB_with_validation;

    result["glDrawBuffersARB"] = vkglDrawBuffersARB_with_validation;

    result["glDrawArraysInstancedARB"]   = vkglDrawArraysInstancedARB_with_validation;
    result["glDrawElementsInstancedARB"] = vkglDrawElementsInstancedARB_with_validation;

    result["glSampleCoverageARB"] = vkglSampleCoverageARB_with_validation;

    result["glActiveTextureARB"] = vkglActiveTextureARB_with_validation;

    result["glBeginQueryARB"]        = vkglBeginQueryARB_with_validation;
    result["glDeleteQueriesARB"]     = vkglDeleteQueriesARB_with_validation;
    result["glEndQueryARB"]          = vkglEndQueryARB_with_validation;
    result["glGenQueriesARB"]        = vkglGenQueriesARB_with_validation;
    result["glGetQueryivARB"]        = vkglGetQueryivARB_with_validation;
    result["glGetQueryObjectivARB"]  = vkglGetQueryObjectivARB_with_validation;
    result["glGetQueryObjectuivARB"] = vkglGetQueryObjectuivARB_with_validation;
    result["glIsQueryARB"]           = vkglIsQueryARB_with_validation;

    result["glPointParameterfARB"]  = vkglPointParameterfARB_with_validation;
    result["glPointParameterfvARB"] = vkglPointParameterfvARB_with_validation;

    result["glTexBufferARB"] = vkglTexBufferARB_with_validation;

    result["glCompressedTexImage1DARB"]    = vkglCompressedTexImage1DARB_with_validation;
    result["glCompressedTexImage2DARB"]    = vkglCompressedTexImage2DARB_with_validation;
    result["glCompressedTexImage3DARB"]    = vkglCompressedTexImage3DARB_with_validation;
    result["glCompressedTexSubImage1DARB"] = vkglCompressedTexSubImage1DARB_with_validation;
    result["glCompressedTexSubImage2DARB"] = vkglCompressedTexSubImage2DARB_with_validation;
    result["glCompressedTexSubImage3DARB"] = vkglCompressedTexSubImage3DARB_with_validation;
    result["glGetCompressedTexImageARB"]   = vkglGetCompressedTexImageARB_with_validation;

    result["glBindBufferARB"]           = vkglBindBufferARB_with_validation;
    result["glBufferDataARB"]           = vkglBufferDataARB_with_validation;
    result["glBufferSubDataARB"]        = vkglBufferSubDataARB_with_validation;
    result["glDeleteBuffersARB"]        = vkglDeleteBuffersARB_with_validation;
    result["glGenBuffersARB"]           = vkglGenBuffersARB_with_validation;
    result["glGetBufferParameterivARB"] = vkglGetBufferParameterivARB_with_validation;
    result["glGetBufferPointervARB"]    = vkglGetBufferPointervARB_with_validation;
    result["glGetBufferSubDataARB"]     = vkglGetBufferSubDataARB_with_validation;
    result["glIsBufferARB"]             = vkglIsBufferARB_with_validation;
    result["glMapBufferARB"]            = vkglMapBufferARB_with_validation;
    result["glUnmapBufferARB"]          = vkglUnmapBufferARB_with_validation;

    result["glDisableVertexAttribArrayARB"] = vkglDisableVertexAttribArrayARB_with_validation;
    result["glEnableVertexAttribArrayARB"]  = vkglEnableVertexAttribArrayARB_with_validation;
    result["glGetVertexAttribdvARB"]        = vkglGetVertexAttribdvARB_with_validation;
    result["glGetVertexAttribfvARB"]        = vkglGetVertexAttribfvARB_with_validation;
    result["glGetVertexAttribivARB"]        = vkglGetVertexAttribivARB_with_validation;
    result["glGetVertexAttribPointervARB"]  = vkglGetVertexAttribPointervARB_with_validation;
    result["glVertexAttrib1dvARB"]          = vkglVertexAttrib1dvARB_with_validation;
    result["glVertexAttrib1dARB"]           = vkglVertexAttrib1dARB_with_validation;
    result["glVertexAttrib1fvARB"]          = vkglVertexAttrib1fvARB_with_validation;
    result["glVertexAttrib1fARB"]           = vkglVertexAttrib1fARB_with_validation;
    result["glVertexAttrib1svARB"]          = vkglVertexAttrib1svARB_with_validation;
    result["glVertexAttrib1sARB"]           = vkglVertexAttrib1sARB_with_validation;
    result["glVertexAttrib2dvARB"]          = vkglVertexAttrib2dvARB_with_validation;
    result["glVertexAttrib2dARB"]           = vkglVertexAttrib2dARB_with_validation;
    result["glVertexAttrib2fvARB"]          = vkglVertexAttrib2fvARB_with_validation;
    result["glVertexAttrib2fARB"]           = vkglVertexAttrib2fARB_with_validation;
    result["glVertexAttrib2svARB"]          = vkglVertexAttrib2svARB_with_validation;
    result["glVertexAttrib2sARB"]           = vkglVertexAttrib2sARB_with_validation;
    result["glVertexAttrib3dvARB"]          = vkglVertexAttrib3dvARB_with_validation;
    result["glVertexAttrib3dARB"]           = vkglVertexAttrib3dARB_with_validation;
    result["glVertexAttrib3fvARB"]          = vkglVertexAttrib3fvARB_with_validation;
    result["glVertexAttrib3fARB"]           = vkglVertexAttrib3fARB_with_validation;
    result["glVertexAttrib3svARB"]          = vkglVertexAttrib3svARB_with_validation;
    result["glVertexAttrib3sARB"]           = vkglVertexAttrib3sARB_with_validation;
    result["glVertexAttrib4bvARB"]          = vkglVertexAttrib4bvARB_with_validation;
    result["glVertexAttrib4dvARB"]          = vkglVertexAttrib4dvARB_with_validation;
    result["glVertexAttrib4dARB"]           = vkglVertexAttrib4dARB_with_validation;
    result["glVertexAttrib4fvARB"]          = vkglVertexAttrib4fvARB_with_validation;
    result["glVertexAttrib4fARB"]           = vkglVertexAttrib4fARB_with_validation;
    result["glVertexAttrib4ivARB"]          = vkglVertexAttrib4ivARB_with_validation;
    result["glVertexAttrib4NbvARB"]         = vkglVertexAttrib4NbvARB_with_validation;
    result["glVertexAttrib4NivARB"]         = vkglVertexAttrib4NivARB_with_validation;
    result["glVertexAttrib4NsvARB"]         = vkglVertexAttrib4NsvARB_with_validation;
    result["glVertexAttrib4NubvARB"]        = vkglVertexAttrib4NubvARB_with_validation;
    result["glVertexAttrib4NubARB"]         = vkglVertexAttrib4NubARB_with_validation;
    result["glVertexAttrib4NuivARB"]        = vkglVertexAttrib4NuivARB_with_validation;
    result["glVertexAttrib4svARB"]          = vkglVertexAttrib4svARB_with_validation;
    result["glVertexAttrib4sARB"]           = vkglVertexAttrib4sARB_with_validation;
    result["glVertexAttrib4ubvARB"]         = vkglVertexAttrib4ubvARB_with_validation;
    result["glVertexAttrib4uivARB"]         = vkglVertexAttrib4uivARB_with_validation;
    result["glVertexAttrib4usvARB"]         = vkglVertexAttrib4usvARB_with_validation;
    result["glVertexAttribPointerARB"]      = vkglVertexAttribPointerARB_with_validation;

    result["glBindAttribLocationARB"] = vkglBindAttribLocationARB_with_validation;
    result["glGetActiveAttribARB"]    = vkglGetActiveAttribARB_with_validation;
    result["glGetAttribLocationARB"]  = vkglGetAttribLocationARB_with_validation;

    return result;
}

std::vector<FunctionInterceptor> vkgl_get_function_interceptors()
{
    /* <= GL 1.1 */
    return std::vector<FunctionInterceptor>
    {
        FunctionInterceptor(&(PVOID&) g_cached_gl_bind_texture,              vkglBindTexture),
        FunctionInterceptor(&(PVOID&) g_cached_gl_clear,                     vkglClear),
        FunctionInterceptor(&(PVOID&) g_cached_gl_clear_color,               vkglClearColor),
        FunctionInterceptor(&(PVOID&) g_cached_gl_clear_depth,               vkglClearDepth),
        FunctionInterceptor(&(PVOID&) g_cached_gl_clear_stencil,             vkglClearStencil),
        FunctionInterceptor(&(PVOID&) g_cached_gl_color_mask,                vkglColorMask),
        FunctionInterceptor(&(PVOID&) g_cached_gl_copy_tex_image_1d,         vkglCopyTexImage1D),
        FunctionInterceptor(&(PVOID&) g_cached_gl_copy_tex_image_2d,         vkglCopyTexImage2D),
        FunctionInterceptor(&(PVOID&) g_cached_gl_copy_tex_sub_image_1d,     vkglCopyTexSubImage1D),
        FunctionInterceptor(&(PVOID&) g_cached_gl_copy_tex_sub_image_2d,     vkglCopyTexSubImage2D),
        FunctionInterceptor(&(PVOID&) g_cached_gl_cull_face,                 vkglCullFace),
        FunctionInterceptor(&(PVOID&) g_cached_gl_delete_textures,           vkglDeleteTextures),
        FunctionInterceptor(&(PVOID&) g_cached_gl_depth_func,                vkglDepthFunc),
        FunctionInterceptor(&(PVOID&) g_cached_gl_depth_mask,                vkglDepthMask),
        FunctionInterceptor(&(PVOID&) g_cached_gl_depth_range,               vkglDepthRange),
        FunctionInterceptor(&(PVOID&) g_cached_gl_disable,                   vkglDisable),
        FunctionInterceptor(&(PVOID&) g_cached_gl_draw_arrays,               vkglDrawArrays),
        FunctionInterceptor(&(PVOID&) g_cached_gl_draw_buffer,               vkglDrawBuffer),
        FunctionInterceptor(&(PVOID&) g_cached_gl_draw_elements,             vkglDrawElements),
        FunctionInterceptor(&(PVOID&) g_cached_gl_enable,                    vkglEnable),
        FunctionInterceptor(&(PVOID&) g_cached_gl_finish,                    vkglFinish),
        FunctionInterceptor(&(PVOID&) g_cached_gl_flush,                     vkglFlush),
        FunctionInterceptor(&(PVOID&) g_cached_gl_front_face,                vkglFrontFace),
        FunctionInterceptor(&(PVOID&) g_cached_gl_gen_textures,              vkglGenTextures),
        FunctionInterceptor(&(PVOID&) g_cached_gl_get_booleanv,              vkglGetBooleanv),
        FunctionInterceptor(&(PVOID&) g_cached_gl_get_doublev,               vkglGetDoublev),
        FunctionInterceptor(&(PVOID&) g_cached_gl_get_error,                 vkglGetError),
        FunctionInterceptor(&(PVOID&) g_cached_gl_get_floatv,                vkglGetFloatv),
        FunctionInterceptor(&(PVOID&) g_cached_gl_get_integerv,              vkglGetIntegerv),
        FunctionInterceptor(&(PVOID&) g_cached_gl_get_string,                vkglGetString),
        FunctionInterceptor(&(PVOID&) g_cached_gl_get_tex_image,             vkglGetTexImage),
        FunctionInterceptor(&(PVOID&) g_cached_gl_get_tex_level_parameterfv, vkglGetTexLevelParameterfv),
        FunctionInterceptor(&(PVOID&) g_cached_gl_get_tex_level_parameteriv, vkglGetTexLevelParameteriv),
        FunctionInterceptor(&(PVOID&) g_cached_gl_get_tex_parameterfv,       vkglGetTexParameterfv),
        FunctionInterceptor(&(PVOID&) g_cached_gl_get_tex_parameteriv,       vkglGetTexParameteriv),
        FunctionInterceptor(&(PVOID&) g_cached_gl_hint,                      vkglHint),
        FunctionInterceptor(&(PVOID&) g_cached_gl_is_enabled,                vkglIsEnabled),
        FunctionInterceptor(&(PVOID&) g_cached_gl_is_texture,                vkglIsTexture),
        FunctionInterceptor(&(PVOID&) g_cached_gl_line_width,                vkglLineWidth),
        FunctionInterceptor(&(PVOID&) g_cached_gl_logic_op,                  vkglLogicOp),
        FunctionInterceptor(&(PVOID&) g_cached_gl_pixel_storef,              vkglPixelStoref),
        FunctionInterceptor(&(PVOID&) g_cached_gl_pixel_storei,              vkglPixelStorei),
        FunctionInterceptor(&(PVOID&) g_cached_gl_point_size,                vkglPointSize),
        FunctionInterceptor(&(PVOID&) g_cached_gl_polygon_mode,              vkglPolygonMode),
        FunctionInterceptor(&(PVOID&) g_cached_gl_polygon_offset,            vkglPolygonOffset),
        FunctionInterceptor(&(PVOID&) g_cached_gl_read_buffer,               vkglReadBuffer),
        FunctionInterceptor(&(PVOID&) g_cached_gl_read_pixels,               vkglReadPixels),
        FunctionInterceptor(&(PVOID&) g_cached_gl_scissor,                   vkglScissor),
        FunctionInterceptor(&(PVOID&) g_cached_gl_stencil_func,              vkglStencilFunc),
        FunctionInterceptor(&(PVOID&) g_cached_gl_stencil_mask,              vkglStencilMask),
        FunctionInterceptor(&(PVOID&) g_cached_gl_stencil_op,                vkglStencilOp),
        FunctionInterceptor(&(PVOID&) g_cached_gl_tex_image_1d,              vkglTexImage1D),
        FunctionInterceptor(&(PVOID&) g_cached_gl_tex_image_2d,              vkglTexImage2D),
        FunctionInterceptor(&(PVOID&) g_cached_gl_tex_parameterf,            vkglTexParameterf),
        FunctionInterceptor(&(PVOID&) g_cached_gl_tex_parameterfv,           vkglTexParameterfv),
        FunctionInterceptor(&(PVOID&) g_cached_gl_tex_parameteri,            vkglTexParameteri),
        FunctionInterceptor(&(PVOID&) g_cached_gl_tex_parameteriv,           vkglTexParameteriv),
        FunctionInterceptor(&(PVOID&) g_cached_gl_tex_sub_image_1d,          vkglTexSubImage1D),
        FunctionInterceptor(&(PVOID&) g_cached_gl_tex_sub_image_2d,          vkglTexSubImage2D),
        FunctionInterceptor(&(PVOID&) g_cached_gl_viewport_func_ptr,         vkglViewport),
    };
}