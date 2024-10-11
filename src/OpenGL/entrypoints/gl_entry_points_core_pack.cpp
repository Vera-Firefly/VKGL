// Core OpenGL

#include "Common/debug_log.h"
#include "OpenGL/entrypoints/gl_entry_points_pack.h"




// GL_VERSION_1_0
void OpenGL::vkglCullFace (GLenum mode){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto mode_vkgl = OpenGL::Utils::get_cull_mode_for_gl_enum(   mode);

    in_context_p->set_cull_mode(mode_vkgl);

}

void OpenGL::vkglFrontFace (GLenum mode){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto orientation_vkgl = OpenGL::Utils::get_front_face_orientation_for_gl_enum(   mode);

    in_context_p->set_front_face_orientation(orientation_vkgl);

}

void OpenGL::vkglHint (GLenum target, GLenum mode){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto mode_vkgl   = OpenGL::Utils::get_hint_mode_for_gl_enum  (   mode);
    const auto target_vkgl = OpenGL::Utils::get_hint_target_for_gl_enum(   target);

    in_context_p->set_hint(target_vkgl,
                             mode_vkgl);

}

void OpenGL::vkglLineWidth (GLfloat width){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->set_line_width(   width);

}

void OpenGL::vkglPointSize (GLfloat size){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->set_point_size(   size);

}

void OpenGL::vkglPolygonMode (GLenum face, GLenum mode){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto mode_vkgl = OpenGL::Utils::get_polygon_mode_for_gl_enum(   mode);

    vkgl_assert(   face == GL_FRONT_AND_BACK);

    in_context_p->set_polygon_mode(mode_vkgl);

}

void OpenGL::vkglScissor (GLint x, GLint y, GLsizei width, GLsizei height){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->set_scissor(   x,
                                   y,
                                   width,
                                   height);

}

void OpenGL::vkglTexParameterf (GLenum target, GLenum pname, GLfloat param){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto pname_vkgl  = OpenGL::Utils::get_texture_property_for_gl_enum(   pname);
    const auto target_vkgl = OpenGL::Utils::get_texture_target_for_gl_enum  (   target);

    in_context_p->set_texture_parameter(target_vkgl,
                                          pname_vkgl,
                                          OpenGL::GetSetArgumentType::Float,
                                         &   param);

}

void OpenGL::vkglTexParameterfv (GLenum target, GLenum pname, const GLfloat *params){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto pname_vkgl  = OpenGL::Utils::get_texture_property_for_gl_enum(   pname);
    const auto target_vkgl = OpenGL::Utils::get_texture_target_for_gl_enum  (   target);

    in_context_p->set_texture_parameter(target_vkgl,
                                          pname_vkgl,
                                          OpenGL::GetSetArgumentType::Float,
                                             params   );

}

void OpenGL::vkglTexParameteri (GLenum target, GLenum pname, GLint param){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto pname_vkgl  = OpenGL::Utils::get_texture_property_for_gl_enum(   pname);
    const auto target_vkgl = OpenGL::Utils::get_texture_target_for_gl_enum  (   target);

    in_context_p->set_texture_parameter(target_vkgl,
                                          pname_vkgl,
                                          OpenGL::GetSetArgumentType::Int,
                                         &   param);

}

void OpenGL::vkglTexParameteriv (GLenum target, GLenum pname, const GLint *params){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto pname_vkgl  = OpenGL::Utils::get_texture_property_for_gl_enum(   pname);
    const auto target_vkgl = OpenGL::Utils::get_texture_target_for_gl_enum  (   target);

    in_context_p->set_texture_parameter(target_vkgl,
                                          pname_vkgl,
                                          OpenGL::GetSetArgumentType::Int,
                                             params   );

}

void OpenGL::vkglTexImage1D (GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const void *pixels){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

	const auto format_vkgl         = OpenGL::Utils::get_pixel_format_for_gl_enum   (   format);
    const auto internalformat_vkgl = OpenGL::Utils::get_internal_format_for_gl_enum(   internalformat);
    const auto target_vkgl         = OpenGL::Utils::get_texture_target_for_gl_enum (   target);
    const auto type_vkgl           = OpenGL::Utils::get_pixel_type_for_gl_enum     (   type);

    in_context_p->tex_image_1d(target_vkgl,
                                    level,
                                 internalformat_vkgl,
                                    width,
                                    border,
                                 format_vkgl,
                                 type_vkgl,
                                    pixels   );

}

void OpenGL::vkglTexImage2D (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void *pixels){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto format_vkgl         = OpenGL::Utils::get_pixel_format_for_gl_enum   (   format);
    const auto internalformat_vkgl = OpenGL::Utils::get_internal_format_for_gl_enum(   internalformat);
    const auto target_vkgl         = OpenGL::Utils::get_texture_target_for_gl_enum (   target);
    const auto type_vkgl           = OpenGL::Utils::get_pixel_type_for_gl_enum     (   type);

    in_context_p->tex_image_2d(target_vkgl,
                                    level,
                                 internalformat_vkgl,
                                    width,
                                    height,
                                    border,
                                 format_vkgl,
                                 type_vkgl,
                                    pixels   );

}

void OpenGL::vkglDrawBuffer (GLenum buf){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto buffer_vkgl = OpenGL::Utils::get_draw_buffer_for_gl_enum(   buf);

    in_context_p->set_draw_buffer(buffer_vkgl);

}

void OpenGL::vkglClear (GLbitfield mask){
 
    GET_CONTEXT(in_context_p)

    const auto clear_buffer_bits = OpenGL::Utils::get_clear_buffer_bits_for_gl_enum(   mask);

    in_context_p->clear(clear_buffer_bits);

}

void OpenGL::vkglClearColor (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->set_clear_color_value(   red,
                                             green,
                                             blue,
                                             alpha);

}

void OpenGL::vkglClearStencil (GLint s){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->set_clear_stencil_value(   s);

}

void OpenGL::vkglClearDepth (GLdouble depth){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->set_clear_depth_value(   depth);

}

void OpenGL::vkglStencilMask (GLuint mask){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->set_stencil_mask(   mask);

}

void OpenGL::vkglColorMask (GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->set_color_mask( (   red   == GL_TRUE),
                                    (   green == GL_TRUE),
                                    (   blue  == GL_TRUE),
                                    (   alpha == GL_TRUE) );

}

void OpenGL::vkglDepthMask (GLboolean flag){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->set_depth_mask( (   flag == GL_TRUE) );

}

void OpenGL::vkglDisable (GLenum cap){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto cap_vkgl = OpenGL::Utils::get_nonindexed_capability_for_gl_enum(   cap);

    in_context_p->disable(cap_vkgl);

}

void OpenGL::vkglEnable (GLenum cap){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto mode_vkgl = OpenGL::Utils::get_nonindexed_capability_for_gl_enum(   cap);

    in_context_p->enable(mode_vkgl);

}

void OpenGL::vkglFinish (void){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->finish();

}

void OpenGL::vkglFlush (void){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->flush();

}

void OpenGL::vkglBlendFunc (GLenum sfactor, GLenum dfactor){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto sfactor_vkgl = OpenGL::Utils::get_blend_function_for_gl_enum(   sfactor);
    const auto dfactor_vkgl = OpenGL::Utils::get_blend_function_for_gl_enum(   dfactor);

    in_context_p->set_blend_functions(sfactor_vkgl,
                                        dfactor_vkgl);

}

void OpenGL::vkglLogicOp (GLenum opcode){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto opcode_vkgl = OpenGL::Utils::get_logic_op_mode_for_gl_enum(   opcode);

    in_context_p->set_logic_op(opcode_vkgl);

}

void OpenGL::vkglStencilFunc (GLenum func, GLint ref, GLuint mask){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto func_vkgl = OpenGL::Utils::get_stencil_function_for_gl_enum(   func);

    in_context_p->set_stencil_function(func_vkgl,
                                            ref,
                                            mask);

}

void OpenGL::vkglStencilOp (GLenum fail, GLenum zfail, GLenum zpass){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto fail_vkgl  = OpenGL::Utils::get_stencil_operation_for_gl_enum(   fail);
    const auto zfail_vkgl = OpenGL::Utils::get_stencil_operation_for_gl_enum(   zfail);
    const auto zpass_vkgl = OpenGL::Utils::get_stencil_operation_for_gl_enum(   zpass);

    in_context_p->set_stencil_operations(fail_vkgl,
                                           zfail_vkgl,
                                           zpass_vkgl);

}

void OpenGL::vkglDepthFunc (GLenum func){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto depth_func_vkgl = OpenGL::Utils::get_depth_function_for_gl_enum(   func);

    in_context_p->set_depth_function(depth_func_vkgl);

}

void OpenGL::vkglPixelStoref (GLenum pname, GLfloat param){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto pname_vkgl = OpenGL::Utils::get_pixel_store_property_for_gl_enum(   pname);

    in_context_p->set_pixel_store_property(pname_vkgl,
                                             OpenGL::GetSetArgumentType::Float,
                                            &   param);

}

void OpenGL::vkglPixelStorei (GLenum pname, GLint param){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto pname_vkgl = OpenGL::Utils::get_pixel_store_property_for_gl_enum(   pname);

    in_context_p->set_pixel_store_property(pname_vkgl,
                                             OpenGL::GetSetArgumentType::Int,
                                            &   param);

}

void OpenGL::vkglReadBuffer (GLenum src){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto src_vkgl = OpenGL::Utils::get_read_buffer_for_gl_enum(   src);

    in_context_p->set_read_buffer(src_vkgl);

}

void OpenGL::vkglReadPixels (GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void *pixels){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto format_vkgl = OpenGL::Utils::get_pixel_format_for_gl_enum(   format);
    const auto type_vkgl   = OpenGL::Utils::get_pixel_type_for_gl_enum  (   type);

    in_context_p->read_pixels(   x,
                                   y,
                                   width,
                                   height,
                                format_vkgl,
                                type_vkgl,
                                   pixels   );

}

void OpenGL::vkglGetBooleanv (GLenum pname, GLboolean *data){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const OpenGL::ContextProperty pname_vkgl = OpenGL::Utils::get_context_property_for_gl_enum(   pname);

    in_context_p->get_parameter(pname_vkgl,
                                  OpenGL::GetSetArgumentType::Boolean,
                                     data   );

}

void OpenGL::vkglGetDoublev (GLenum pname, GLdouble *data){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto pname_vkgl = OpenGL::Utils::get_context_property_for_gl_enum(   pname);

    in_context_p->get_parameter(pname_vkgl,
                                  OpenGL::GetSetArgumentType::Double,
                                     data   );

}

GLenum OpenGL::vkglGetError (void){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto error_vkgl = in_context_p->get_error();
    const char* error_msg = in_context_p->get_error();
    OUT_DBG(error_msg);

    return OpenGL::Utils::get_gl_enum_for_error_code(error_vkgl);

}

void OpenGL::vkglGetFloatv (GLenum pname, GLfloat *data){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto pname_vkgl = OpenGL::Utils::get_context_property_for_gl_enum(   pname);

    in_context_p->get_parameter(pname_vkgl,
                                  OpenGL::GetSetArgumentType::Float,
                                     data   );

}

void OpenGL::vkglGetIntegerv (GLenum pname, GLint *data){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto pname_vkgl = OpenGL::Utils::get_context_property_for_gl_enum(   pname);

    in_context_p->get_parameter(pname_vkgl,
                                  OpenGL::GetSetArgumentType::Int,
                                     data   );

}

const GLubyte *OpenGL::vkglGetString (GLenum name){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto     name_vkgl  = OpenGL::Utils::get_context_property_for_gl_enum(   name);
    const GLubyte* result    = nullptr;

    in_context_p->get_parameter(name_vkgl,
                                  OpenGL::GetSetArgumentType::String,
                                 &result   );

    return result   ;

}

void OpenGL::vkglGetTexImage (GLenum target, GLint level, GLenum format, GLenum type, void *pixels){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto target_vkgl       = OpenGL::Utils::get_texture_target_for_gl_enum(   target);
    const auto pixel_format_vkgl = OpenGL::Utils::get_pixel_format_for_gl_enum  (   format);
    const auto pixel_type_vkgl   = OpenGL::Utils::get_pixel_type_for_gl_enum    (   type);

    in_context_p->get_texture_image(target_vkgl,
                                         level,
                                      pixel_format_vkgl,
                                      pixel_type_vkgl,
                                         pixels   );

}

void OpenGL::vkglGetTexParameterfv (GLenum target, GLenum pname, GLfloat *params){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto pname_vkgl  = OpenGL::Utils::get_texture_property_for_gl_enum(   pname);
    const auto target_vkgl = OpenGL::Utils::get_texture_target_for_gl_enum  (   target);

    in_context_p->get_texture_parameter(target_vkgl,
                                          pname_vkgl,
                                          OpenGL::GetSetArgumentType::Float,
                                             params   );

}

void OpenGL::vkglGetTexParameteriv (GLenum target, GLenum pname, GLint *params){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto pname_vkgl  = OpenGL::Utils::get_texture_property_for_gl_enum(   pname);
    const auto target_vkgl = OpenGL::Utils::get_texture_target_for_gl_enum  (   target);

    in_context_p->get_texture_parameter(target_vkgl,
                                          pname_vkgl,
                                          OpenGL::GetSetArgumentType::Int,
                                             params   );

}

void OpenGL::vkglGetTexLevelParameterfv (GLenum target, GLint level, GLenum pname, GLfloat *params){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto pname_vkgl  = OpenGL::Utils::get_texture_level_property_for_gl_enum(   pname);
    const auto target_vkgl = OpenGL::Utils::get_texture_target_for_gl_enum        (   target);

    in_context_p->get_texture_level_parameter(target_vkgl,
                                                   level,
                                                pname_vkgl,
                                                OpenGL::GetSetArgumentType::Float,
                                                   params   );

}

void OpenGL::vkglGetTexLevelParameteriv (GLenum target, GLint level, GLenum pname, GLint *params){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto pname_vkgl  = OpenGL::Utils::get_texture_level_property_for_gl_enum(   pname);
    const auto target_vkgl = OpenGL::Utils::get_texture_target_for_gl_enum        (   target);

    in_context_p->get_texture_level_parameter(target_vkgl,
                                                   level,
                                                pname_vkgl,
                                                OpenGL::GetSetArgumentType::Int,
                                                   params   );

}

GLboolean OpenGL::vkglIsEnabled (GLenum cap){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto cap_vkgl = OpenGL::Utils::get_nonindexed_capability_for_gl_enum(   cap);

    return (in_context_p->is_enabled(cap_vkgl) ) ? GL_TRUE
                                                   : GL_FALSE;

}

void OpenGL::vkglDepthRange (GLdouble n, GLdouble f){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->set_depth_range(   n,
                                       f);

}

void OpenGL::vkglViewport (GLint x, GLint y, GLsizei width, GLsizei height){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->set_viewport(   x,
                                    y,
                                    width,
                                    height);

}



// GL_VERSION_1_1
void OpenGL::vkglDrawArrays (GLenum mode, GLint first, GLsizei count){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto mode_vkgl = OpenGL::Utils::get_draw_call_mode_for_gl_enum(   mode);

    in_context_p->draw_arrays(mode_vkgl,
                                   first,
                                   count);

}

void OpenGL::vkglDrawElements (GLenum mode, GLsizei count, GLenum type, const void *indices){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto mode_vkgl = OpenGL::Utils::get_draw_call_mode_for_gl_enum      (   mode);
    const auto type_vkgl = OpenGL::Utils::get_draw_call_index_type_for_gl_enum(   type);

    in_context_p->draw_elements(mode_vkgl,
                                     count,
                                  type_vkgl,
                                     indices);

}

void OpenGL::vkglGetPointerv (GLenum pname, void **params){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

// not support yet
// todo
	*params = nullptr;

}

void OpenGL::vkglPolygonOffset (GLfloat factor, GLfloat units){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->set_polygon_offset(   factor,
                                         units);

}

void OpenGL::vkglCopyTexImage1D (GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto internalformat_vkgl = OpenGL::Utils::get_internal_format_for_gl_enum(   internalformat);
    const auto target_vkgl         = OpenGL::Utils::get_texture_target_for_gl_enum (   target);

    in_context_p->copy_tex_image_1d(target_vkgl,
                                         level,
                                      internalformat_vkgl,
                                         x,
                                         y,
                                         width,
                                         border);

}

void OpenGL::vkglCopyTexImage2D (GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto internalformat_vkgl = OpenGL::Utils::get_internal_format_for_gl_enum(   internalformat);
    const auto target_vkgl         = OpenGL::Utils::get_texture_target_for_gl_enum (   target);

    in_context_p->copy_tex_image_2d(target_vkgl,
                                         level,
                                      internalformat_vkgl,
                                         x,
                                         y,
                                         width,
                                         height,
                                         border);

}

void OpenGL::vkglCopyTexSubImage1D (GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto target_vkgl = OpenGL::Utils::get_texture_target_for_gl_enum(   target);

    in_context_p->copy_tex_sub_image_1d(target_vkgl,
                                             level,
                                             xoffset,
                                             x,
                                             y,
                                             width);

}

void OpenGL::vkglCopyTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto target_vkgl = OpenGL::Utils::get_texture_target_for_gl_enum(   target);

    in_context_p->copy_tex_sub_image_2d(target_vkgl,
                                             level,
                                             xoffset,
                                             yoffset,
                                             x,
                                             y,
                                             width,
                                             height);

}

void OpenGL::vkglTexSubImage1D (GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void *pixels){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto target_vkgl = OpenGL::Utils::get_texture_target_for_gl_enum(   target);
    const auto format_vkgl = OpenGL::Utils::get_pixel_format_for_gl_enum  (   format);
    const auto type_vkgl   = OpenGL::Utils::get_pixel_type_for_gl_enum    (   type);

    in_context_p->tex_sub_image_1d(target_vkgl,
                                        level,
                                        xoffset,
                                        width,
                                     format_vkgl,
                                     type_vkgl,
                                        pixels);

}

void OpenGL::vkglTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void *pixels){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto format_vkgl = OpenGL::Utils::get_pixel_format_for_gl_enum  (   format);
    const auto target_vkgl = OpenGL::Utils::get_texture_target_for_gl_enum(   target);
    const auto type_vkgl   = OpenGL::Utils::get_pixel_type_for_gl_enum    (   type);

    in_context_p->tex_sub_image_2d(target_vkgl,
                                        level,
                                        xoffset,
                                        yoffset,
                                        width,
                                        height,
                                     format_vkgl,
                                     type_vkgl,
                                        pixels);

}

void OpenGL::vkglBindTexture (GLenum target, GLuint texture){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto target_vkgl = OpenGL::Utils::get_texture_target_for_gl_enum(   target);

    in_context_p->bind_texture(target_vkgl,
                                    texture);

}

void OpenGL::vkglDeleteTextures (GLsizei n, const GLuint *textures){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->delete_textures(   n,
                                       textures);

}

void OpenGL::vkglGenTextures (GLsizei n, GLuint *textures){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->gen_textures(   n,
                                    textures);

}

GLboolean OpenGL::vkglIsTexture (GLuint texture){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    return (in_context_p->is_texture(   texture) ) ? GL_TRUE : GL_FALSE;

}



// GL_VERSION_1_2
void OpenGL::vkglDrawRangeElements (GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void *indices){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto mode_vkgl = OpenGL::Utils::get_draw_call_mode_for_gl_enum      (   mode);
    const auto type_vkgl = OpenGL::Utils::get_draw_call_index_type_for_gl_enum(   type);

    in_context_p->draw_range_elements(mode_vkgl,
                                           start,
                                           end,
                                           count,
                                        type_vkgl,
                                           indices);

}

void OpenGL::vkglTexImage3D (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void *pixels){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto internalformat_vkgl = OpenGL::Utils::get_internal_format_for_gl_enum(   internalformat);
    const auto format_vkgl         = OpenGL::Utils::get_pixel_format_for_gl_enum   (   format);
    const auto target_vkgl         = OpenGL::Utils::get_texture_target_for_gl_enum (   target);
    const auto type_vkgl           = OpenGL::Utils::get_pixel_type_for_gl_enum     (   type);

    in_context_p->tex_image_3d(target_vkgl,
                                    level,
                                 internalformat_vkgl,
                                    width,
                                    height,
                                    depth,
                                    border,
                                 format_vkgl,
                                 type_vkgl,
                                    pixels);

}

void OpenGL::vkglTexSubImage3D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void *pixels){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto format_vkgl = OpenGL::Utils::get_pixel_format_for_gl_enum  (   format);
    const auto target_vkgl = OpenGL::Utils::get_texture_target_for_gl_enum(   target);
    const auto type_vkgl   = OpenGL::Utils::get_pixel_type_for_gl_enum    (   type);

    in_context_p->tex_sub_image_3d(target_vkgl,
                                        level,
                                        xoffset,
                                        yoffset,
                                        zoffset,
                                        width,
                                        height,
                                        depth,
                                     format_vkgl,
                                     type_vkgl,
                                        pixels);

}

void OpenGL::vkglCopyTexSubImage3D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

const auto target_vkgl = OpenGL::Utils::get_texture_target_for_gl_enum(   target);

    in_context_p->copy_tex_sub_image_3d(target_vkgl,
                                             level,
                                             xoffset,
                                             yoffset,
                                             zoffset,
                                             x,
                                             y,
                                             width,
                                             height);

}



// GL_VERSION_1_3
void OpenGL::vkglActiveTexture (GLenum texture){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto n_texture_unit =    texture - GL_TEXTURE0;

    in_context_p->set_active_texture(n_texture_unit);

}

void OpenGL::vkglSampleCoverage (GLfloat value, GLboolean invert){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->set_sample_coverage(   value,
                                           invert);

}

void OpenGL::vkglCompressedTexImage3D (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void *data){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto internalformat_vkgl = OpenGL::Utils::get_internal_format_for_gl_enum(   internalformat);
    const auto target_vkgl         = OpenGL::Utils::get_texture_target_for_gl_enum (   target);

    in_context_p->compressed_tex_image_3d(target_vkgl,
                                               level,
                                            internalformat_vkgl,
                                               width,
                                               height,
                                               depth,
                                               border,
                                               imageSize,
                                               data);

}

void OpenGL::vkglCompressedTexImage2D (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void *data){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto internalformat_vkgl = OpenGL::Utils::get_internal_format_for_gl_enum(   internalformat);
    const auto target_vkgl         = OpenGL::Utils::get_texture_target_for_gl_enum (   target);

    in_context_p->compressed_tex_image_2d(target_vkgl,
                                               level,
                                            internalformat_vkgl,
                                               width,
                                               height,
                                               border,
                                               imageSize,
                                               data);

}

void OpenGL::vkglCompressedTexImage1D (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const void *data){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto internalformat_vkgl = OpenGL::Utils::get_internal_format_for_gl_enum(   internalformat);
    const auto target_vkgl         = OpenGL::Utils::get_texture_target_for_gl_enum(    target);

    in_context_p->compressed_tex_image_1d(target_vkgl,
                                               level,
                                            internalformat_vkgl,
                                               width,
                                               border,
                                               imageSize,
                                               data);

}

void OpenGL::vkglCompressedTexSubImage3D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void *data){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto format_vkgl = OpenGL::Utils::get_pixel_format_for_gl_enum  (   format);
    const auto target_vkgl = OpenGL::Utils::get_texture_target_for_gl_enum(   target);

    in_context_p->compressed_tex_sub_image_3d(target_vkgl,
                                                   level,
                                                   xoffset,
                                                   yoffset,
                                                   zoffset,
                                                   width,
                                                   height,
                                                   depth,
                                                format_vkgl,
                                                   imageSize,
                                                   data);

}

void OpenGL::vkglCompressedTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void *data){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto format_vkgl = OpenGL::Utils::get_pixel_format_for_gl_enum  (   format);
    const auto target_vkgl = OpenGL::Utils::get_texture_target_for_gl_enum(   target);

    in_context_p->compressed_tex_sub_image_2d(target_vkgl,
                                                   level,
                                                   xoffset,
                                                   yoffset,
                                                   width,
                                                   height,
                                                format_vkgl,
                                                   imageSize,
                                                   data);

}

void OpenGL::vkglCompressedTexSubImage1D (GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void *data){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto format_vkgl = OpenGL::Utils::get_pixel_format_for_gl_enum  (   format);
    const auto target_vkgl = OpenGL::Utils::get_texture_target_for_gl_enum(   target);

    in_context_p->compressed_tex_sub_image_1d(target_vkgl,
                                                   level,
                                                   xoffset,
                                                   width,
                                                format_vkgl,
                                                   imageSize,
                                                   data);

}

void OpenGL::vkglGetCompressedTexImage (GLenum target, GLint level, void *img){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto target_vkgl = OpenGL::Utils::get_texture_target_for_gl_enum(   target);

    in_context_p->get_compressed_tex_image(target_vkgl,
                                                level,
                                                img);

}



// GL_VERSION_1_4
void OpenGL::vkglBlendFuncSeparate (GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto dfactor_alpha_vkgl = OpenGL::Utils::get_blend_function_for_gl_enum(   dfactorAlpha);
    const auto dfactor_rgb_vkgl   = OpenGL::Utils::get_blend_function_for_gl_enum(   dfactorRGB);
    const auto sfactor_alpha_vkgl = OpenGL::Utils::get_blend_function_for_gl_enum(   sfactorAlpha);
    const auto sfactor_rgb_vkgl   = OpenGL::Utils::get_blend_function_for_gl_enum(   sfactorRGB);

    in_context_p->set_blend_functions_separate(sfactor_rgb_vkgl,
                                                 dfactor_rgb_vkgl,
                                                 sfactor_alpha_vkgl,
                                                 dfactor_alpha_vkgl);

}

void OpenGL::vkglMultiDrawArrays (GLenum mode, const GLint *first, const GLsizei *count, GLsizei drawcount){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto mode_vkgl = OpenGL::Utils::get_draw_call_mode_for_gl_enum(   mode);

    in_context_p->multi_draw_arrays(mode_vkgl,
                                         first   ,
                                         count   ,
                                         drawcount);

}

void OpenGL::vkglMultiDrawElements (GLenum mode, const GLsizei *count, GLenum type, const void *const*indices, GLsizei drawcount){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto mode_vkgl = OpenGL::Utils::get_draw_call_mode_for_gl_enum      (   mode);
    const auto type_vkgl = OpenGL::Utils::get_draw_call_index_type_for_gl_enum(   type);

    in_context_p->multi_draw_elements(mode_vkgl,
                                           count   ,
                                        type_vkgl,
                                           indices   ,
                                           drawcount);

}

void OpenGL::vkglPointParameterf (GLenum pname, GLfloat param){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto pname_vkgl = OpenGL::Utils::get_point_property_for_gl_enum(   pname);

    in_context_p->set_point_property(pname_vkgl,
                                       OpenGL::GetSetArgumentType::Float,
                                      &   param);

}

void OpenGL::vkglPointParameterfv (GLenum pname, const GLfloat *params){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto pname_vkgl = OpenGL::Utils::get_point_property_for_gl_enum(   pname);

    in_context_p->set_point_property(pname_vkgl,
                                       OpenGL::GetSetArgumentType::Float,
                                          params);

}

void OpenGL::vkglPointParameteri (GLenum pname, GLint param){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto pname_vkgl = OpenGL::Utils::get_point_property_for_gl_enum(   pname);

    in_context_p->set_point_property(pname_vkgl,
                                       OpenGL::GetSetArgumentType::Int,
                                      &   param);

}

void OpenGL::vkglPointParameteriv (GLenum pname, const GLint *params){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto pname_vkgl = OpenGL::Utils::get_point_property_for_gl_enum(   pname);

    in_context_p->set_point_property(pname_vkgl,
                                       OpenGL::GetSetArgumentType::Int,
                                          params);

}

void OpenGL::vkglBlendColor (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->set_blend_color(   red,
                                       green,
                                       blue,
                                       alpha);

}

void OpenGL::vkglBlendEquation (GLenum mode){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto mode_vkgl = OpenGL::Utils::get_blend_equation_for_gl_enum(   mode);

    in_context_p->set_blend_equation(mode_vkgl);

}



// GL_VERSION_1_5
void OpenGL::vkglGenQueries (GLsizei n, GLuint *ids){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->gen_queries(   n,
                                   ids   );

}

void OpenGL::vkglDeleteQueries (GLsizei n, const GLuint *ids){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->delete_queries(   n,
                                      ids);

}

GLboolean OpenGL::vkglIsQuery (GLuint id){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    return in_context_p->is_query(   id);

}

void OpenGL::vkglBeginQuery (GLenum target, GLuint id){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto target_vkgl = OpenGL::Utils::get_query_target_for_gl_enum(   target);

    in_context_p->begin_query(target_vkgl,
                                   id);

}

void OpenGL::vkglEndQuery (GLenum target){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto target_vkgl = OpenGL::Utils::get_query_target_for_gl_enum(   target);

    in_context_p->end_query(target_vkgl);

}

void OpenGL::vkglGetQueryiv (GLenum target, GLenum pname, GLint *params){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto pname_vkgl  = OpenGL::Utils::get_query_target_property_for_gl_enum(   pname);
    const auto target_vkgl = OpenGL::Utils::get_query_target_for_gl_enum         (   target);

    in_context_p->get_query_target_property(target_vkgl,
                                              pname_vkgl,
                                                 params   );

}

void OpenGL::vkglGetQueryObjectiv (GLuint id, GLenum pname, GLint *params){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto pname_vkgl = OpenGL::Utils::get_query_property_for_gl_enum(   pname);

    in_context_p->get_query_property(   id,
                                       pname_vkgl,
                                       OpenGL::GetSetArgumentType::Int,
                                       1,
                                          params   );

}

void OpenGL::vkglGetQueryObjectuiv (GLuint id, GLenum pname, GLuint *params){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto pname_vkgl = OpenGL::Utils::get_query_property_for_gl_enum(   pname);

    in_context_p->get_query_property(   id,
                                       pname_vkgl,
                                       OpenGL::GetSetArgumentType::Unsigned_Int,
                                       1,
                                          params   );

}

void OpenGL::vkglBindBuffer (GLenum target, GLuint buffer){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto target_vkgl = OpenGL::Utils::get_buffer_target_for_gl_enum(   target);

    in_context_p->bind_buffer(target_vkgl,
                                   buffer);

}

void OpenGL::vkglDeleteBuffers (GLsizei n, const GLuint *buffers){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->delete_buffers(   n,
                                      buffers);

}

void OpenGL::vkglGenBuffers (GLsizei n, GLuint *buffers){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->gen_buffers(   n,
                                   buffers   );

}

GLboolean OpenGL::vkglIsBuffer (GLuint buffer){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    return in_context_p->is_buffer(   buffer);

}

void OpenGL::vkglBufferData (GLenum target, GLsizeiptr size, const void *data, GLenum usage){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto target_vkgl = OpenGL::Utils::get_buffer_target_for_gl_enum(   target);
    const auto usage_vkgl  = OpenGL::Utils::get_buffer_usage_for_gl_enum (   usage);

    in_context_p->buffer_data(target_vkgl,
                                   size,
                                   data,
                                usage_vkgl);

}

void OpenGL::vkglBufferSubData (GLenum target, GLintptr offset, GLsizeiptr size, const void *data){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto target_vkgl = OpenGL::Utils::get_buffer_target_for_gl_enum(   target);

    in_context_p->buffer_sub_data(target_vkgl,
                                       offset,
                                       size,
                                       data);

}

void OpenGL::vkglGetBufferSubData (GLenum target, GLintptr offset, GLsizeiptr size, void *data){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto target_vkgl = OpenGL::Utils::get_buffer_target_for_gl_enum(   target);

    in_context_p->get_buffer_sub_data(target_vkgl,
                                           offset,
                                           size,
                                           data);

}

void *OpenGL::vkglMapBuffer (GLenum target, GLenum access){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto access_vkgl = OpenGL::Utils::get_buffer_access_for_gl_enum(   access);
    const auto target_vkgl = OpenGL::Utils::get_buffer_target_for_gl_enum(   target);

    return in_context_p->map_buffer(target_vkgl,
                                      access_vkgl);

}

GLboolean OpenGL::vkglUnmapBuffer (GLenum target){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto target_vkgl = OpenGL::Utils::get_buffer_target_for_gl_enum(   target);

    return in_context_p->unmap_buffer(target_vkgl);

}

void OpenGL::vkglGetBufferParameteriv (GLenum target, GLenum pname, GLint *params){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto pname_vkgl  = OpenGL::Utils::get_buffer_property_for_gl_enum(   pname);
    const auto target_vkgl = OpenGL::Utils::get_buffer_target_for_gl_enum  (   target);

    in_context_p->get_buffer_property(target_vkgl,
                                        pname_vkgl,
                                        OpenGL::GetSetArgumentType::Int,
                                        1,
                                           params   );

}

void OpenGL::vkglGetBufferPointerv (GLenum target, GLenum pname, void **params){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto pname_vkgl  = OpenGL::Utils::get_buffer_pointer_property_for_gl_enum(   pname);
    const auto target_vkgl = OpenGL::Utils::get_buffer_target_for_gl_enum          (   target);

    in_context_p->get_buffer_pointerv(target_vkgl,
                                        pname_vkgl,
                                           params      );

}



// GL_VERSION_2_0
void OpenGL::vkglBlendEquationSeparate (GLenum modeRGB, GLenum modeAlpha){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto mode_alpha_vkgl = OpenGL::Utils::get_blend_equation_for_gl_enum(   modeAlpha);
    const auto mode_rgb_vkgl   = OpenGL::Utils::get_blend_equation_for_gl_enum(   modeRGB);

    in_context_p->set_blend_equation_separate(mode_rgb_vkgl,
                                                mode_alpha_vkgl);

}

void OpenGL::vkglDrawBuffers (GLsizei n, const GLenum *bufs){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    OpenGL::DrawBuffer bufs_vkgl[N_MAX_DRAW_BUFFERS];

    vkgl_assert(   n <= N_MAX_DRAW_BUFFERS);

    for (uint32_t t = 0;
                  t < static_cast<uint32_t>(   n);
                t++)
    {
        bufs_vkgl[t] = OpenGL::Utils::get_draw_buffer_for_gl_enum(   bufs[t]);
    }

    in_context_p->set_draw_buffers(   n,
                                     bufs_vkgl);

}

void OpenGL::vkglStencilOpSeparate (GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto dpfail_vkgl = OpenGL::Utils::get_stencil_operation_for_gl_enum (   dpfail);
    const auto dppass_vkgl = OpenGL::Utils::get_stencil_operation_for_gl_enum (   dppass);
    const auto face_vkgl   = OpenGL::Utils::get_stencil_state_face_for_gl_enum(   face);
    const auto sfail_vkgl  = OpenGL::Utils::get_stencil_operation_for_gl_enum (   sfail);

    in_context_p->set_stencil_operations_separate(face_vkgl,
                                                    sfail_vkgl,
                                                    dpfail_vkgl,
                                                    dppass_vkgl);

}

void OpenGL::vkglStencilFuncSeparate (GLenum face, GLenum func, GLint ref, GLuint mask){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto face_vkgl = OpenGL::Utils::get_stencil_state_face_for_gl_enum(   face);
    const auto func_vkgl = OpenGL::Utils::get_stencil_function_for_gl_enum  (   func);

    in_context_p->set_stencil_function_separate(face_vkgl,
                                                  func_vkgl,
                                                     ref,
                                                     mask);

}

void OpenGL::vkglStencilMaskSeparate (GLenum face, GLuint mask){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto face_vkgl = OpenGL::Utils::get_stencil_state_face_for_gl_enum(   face);

    in_context_p->set_stencil_mask_separate(face_vkgl,
                                                 mask);

}

void OpenGL::vkglAttachShader (GLuint program, GLuint shader){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->attach_shader(   program,
                                     shader);

}

void OpenGL::vkglBindAttribLocation (GLuint program, GLuint index, const GLchar *name){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->bind_attrib_location(   program,
                                            index,
                                            name);

}

void OpenGL::vkglCompileShader (GLuint shader){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->compile_shader(   shader);

}

GLuint OpenGL::vkglCreateProgram (void){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    return in_context_p->create_program();

}

GLuint OpenGL::vkglCreateShader (GLenum type){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto type_vkgl = OpenGL::Utils::get_shader_type_for_gl_enum(   type);

    return in_context_p->create_shader(type_vkgl);

}

void OpenGL::vkglDeleteProgram (GLuint program){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->delete_program(   program);

}

void OpenGL::vkglDeleteShader (GLuint shader){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->delete_shader(   shader);

}

void OpenGL::vkglDetachShader (GLuint program, GLuint shader){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->detach_shader(   program,
                                     shader);

}

void OpenGL::vkglDisableVertexAttribArray (GLuint index){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->disable_vertex_attrib_array(   index);

}

void OpenGL::vkglEnableVertexAttribArray (GLuint index){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->enable_vertex_attrib_array(   index);

}

void OpenGL::vkglGetActiveAttrib (GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    auto type_vkgl = OpenGL::VariableType::Unknown;

    in_context_p->get_active_attrib(   program,
                                         index,
                                         bufSize,
                                         length   ,
                                         size   ,
                                     &type_vkgl,
                                         name   );

    *   type    = OpenGL::Utils::get_gl_enum_for_variable_type(type_vkgl);

}

void OpenGL::vkglGetActiveUniform (GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    auto type_vkgl = OpenGL::VariableType::Unknown;

    in_context_p->get_active_uniform(   program,
                                          index,
                                          bufSize,
                                          length   ,
                                          size   ,
                                      &type_vkgl,
                                          name   );

    *   type    = OpenGL::Utils::get_gl_enum_for_variable_type(type_vkgl);

}

void OpenGL::vkglGetAttachedShaders (GLuint program, GLsizei maxCount, GLsizei *count, GLuint *shaders){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->get_attached_shaders(   program,
                                            maxCount,
                                            count   ,
                                            shaders   );

}

GLint OpenGL::vkglGetAttribLocation (GLuint program, const GLchar *name){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    return in_context_p->get_attrib_location(   program,
                                                  name);

}

void OpenGL::vkglGetProgramiv (GLuint program, GLenum pname, GLint *params){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto pname_vkgl = OpenGL::Utils::get_program_property_for_gl_enum(   pname);

    in_context_p->get_program_property(   program,
                                         pname_vkgl,
                                         OpenGL::GetSetArgumentType::Int,
                                         1,
                                            params   );

}

void OpenGL::vkglGetProgramInfoLog (GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->get_program_info_log(   program,
                                            bufSize,
                                            length   ,
                                            infoLog   );

}

void OpenGL::vkglGetShaderiv (GLuint shader, GLenum pname, GLint *params){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto pname_vkgl = OpenGL::Utils::get_shader_property_for_gl_enum(   pname);

    in_context_p->get_shader_property(   shader,
                                        pname_vkgl,
                                        OpenGL::GetSetArgumentType::Int,
                                        1,
                                           params   );

}

void OpenGL::vkglGetShaderInfoLog (GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->get_shader_info_log(   shader,
                                           bufSize,
                                           length   ,
                                           infoLog   );

}

void OpenGL::vkglGetShaderSource (GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *source){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->get_shader_source(   shader,
                                         bufSize,
                                         length   ,
                                         source   );

}

GLint OpenGL::vkglGetUniformLocation (GLuint program, const GLchar *name){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    return in_context_p->get_uniform_location(   program,
                                                   name);

}

void OpenGL::vkglGetUniformfv (GLuint program, GLint location, GLfloat *params){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->get_uniform_value(   program,
                                         location,
                                      OpenGL::GetSetArgumentType::Float,
                                         params   );

}

void OpenGL::vkglGetUniformiv (GLuint program, GLint location, GLint *params){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->get_uniform_value(   program,
                                         location,
                                      OpenGL::GetSetArgumentType::Int,
                                         params   );

}

void OpenGL::vkglGetVertexAttribdv (GLuint index, GLenum pname, GLdouble *params){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto pname_vkgl = OpenGL::Utils::get_vertex_attribute_property_for_gl_enum(   pname);

    in_context_p->get_vertex_attribute_property(   index,
                                                  pname_vkgl,
                                                  OpenGL::GetSetArgumentType::Float,
                                                  OpenGL::GetSetArgumentType::Double,
                                                     params   );

}

void OpenGL::vkglGetVertexAttribfv (GLuint index, GLenum pname, GLfloat *params){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto pname_vkgl = OpenGL::Utils::get_vertex_attribute_property_for_gl_enum(   pname);

    in_context_p->get_vertex_attribute_property(   index,
                                                  pname_vkgl,
                                                  OpenGL::GetSetArgumentType::Float,
                                                  OpenGL::GetSetArgumentType::Float,
                                                     params   );

}

void OpenGL::vkglGetVertexAttribiv (GLuint index, GLenum pname, GLint *params){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto pname_vkgl = OpenGL::Utils::get_vertex_attribute_property_for_gl_enum(   pname);

    in_context_p->get_vertex_attribute_property(   index,
                                                  pname_vkgl,
                                                  OpenGL::GetSetArgumentType::Float,
                                                  OpenGL::GetSetArgumentType::Int,
                                                     params   );

}

void OpenGL::vkglGetVertexAttribPointerv (GLuint index, GLenum pname, void **pointer){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto pname_vkgl = OpenGL::Utils::get_vertex_attribute_pointer_property_for_gl_enum(   pname);

    in_context_p->get_vertex_attrib_pointer_property(   index,
                                                       pname_vkgl,
                                                          pointer   );

}

GLboolean OpenGL::vkglIsProgram (GLuint program){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    return in_context_p->is_program(   program);

}

GLboolean OpenGL::vkglIsShader (GLuint shader){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    return in_context_p->is_shader(   shader);

}

void OpenGL::vkglLinkProgram (GLuint program){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->link_program(   program);

}

void OpenGL::vkglShaderSource (GLuint shader, GLsizei count, const GLchar *const*string, const GLint *length){
     GET_CONTEXT(in_context_p)

    in_context_p->set_shader_source(   shader,
                                         count,
                                         string      ,
                                         length   );

}

void OpenGL::vkglUseProgram (GLuint program){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->use_program(   program);

}

void OpenGL::vkglUniform1f (GLint location, GLfloat v0){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->set_uniform(   location,
                                OpenGL::GetSetArgumentType::Float,
                                1, /*    n_components  */
                                1, /*    n_array_items */
                               &   v0);

}

void OpenGL::vkglUniform2f (GLint location, GLfloat v0, GLfloat v1){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const GLfloat data[] =
    {
           v0,
           v1
    };

    in_context_p->set_uniform(   location,
                                OpenGL::GetSetArgumentType::Float,
                                2, /*    n_components  */
                                1, /*    n_array_items */
                                data);

}

void OpenGL::vkglUniform3f (GLint location, GLfloat v0, GLfloat v1, GLfloat v2){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const GLfloat data[] =
    {
           v0,
           v1,
           v2
    };

    in_context_p->set_uniform(   location,
                                OpenGL::GetSetArgumentType::Float,
                                3, /*    n_components  */
                                1, /*    n_array_items */
                                data);

}

void OpenGL::vkglUniform4f (GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const GLfloat data[] =
    {
           v0,
           v1,
           v2,
           v3
    };

    in_context_p->set_uniform(   location,
                                OpenGL::GetSetArgumentType::Float,
                                4, /*    n_components  */
                                1, /*    n_array_items */
                                data);

}

void OpenGL::vkglUniform1i (GLint location, GLint v0){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->set_uniform(   location,
                                OpenGL::GetSetArgumentType::Float,
                                1, /*    n_components  */
                                1, /*    n_array_items */
                               &   v0);

}

void OpenGL::vkglUniform2i (GLint location, GLint v0, GLint v1){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const GLint data[] =
    {
           v0,
           v1
    };

    in_context_p->set_uniform(   location,
                                OpenGL::GetSetArgumentType::Int,
                                2, /*    n_components  */
                                1, /*    n_array_items */
                                data);

}

void OpenGL::vkglUniform3i (GLint location, GLint v0, GLint v1, GLint v2){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const GLint data[] =
    {
           v0,
           v1,
           v2
    };

    in_context_p->set_uniform(   location,
                                OpenGL::GetSetArgumentType::Int,
                                3, /*    n_components  */
                                1, /*    n_array_items */
                                data);

}

void OpenGL::vkglUniform4i (GLint location, GLint v0, GLint v1, GLint v2, GLint v3){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const GLint data[] =
    {
           v0,
           v1,
           v2,
           v3
    };

    in_context_p->set_uniform(   location,
                                OpenGL::GetSetArgumentType::Int,
                                4, /*    n_components  */
                                1, /*    n_array_items */
                                data);

}

void OpenGL::vkglUniform1fv (GLint location, GLsizei count, const GLfloat *value){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->set_uniform(   location,
                                OpenGL::GetSetArgumentType::Float,
                                1, /*    n_components */
                                   count,
                                   value   );

}

void OpenGL::vkglUniform2fv (GLint location, GLsizei count, const GLfloat *value){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->set_uniform(   location,
                                OpenGL::GetSetArgumentType::Float,
                                2, /*    n_components */
                                   count,
                                   value   );

}

void OpenGL::vkglUniform3fv (GLint location, GLsizei count, const GLfloat *value){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->set_uniform(   location,
                                OpenGL::GetSetArgumentType::Float,
                                3, /*    n_components */
                                   count,
                                   value   );

}

void OpenGL::vkglUniform4fv (GLint location, GLsizei count, const GLfloat *value){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->set_uniform(   location,
                                OpenGL::GetSetArgumentType::Float,
                                4, /*    n_components */
                                   count,
                                   value   );

}

void OpenGL::vkglUniform1iv (GLint location, GLsizei count, const GLint *value){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->set_uniform(   location,
                                OpenGL::GetSetArgumentType::Int,
                                1, /*    n_components */
                                   count,
                                   value   );

}

void OpenGL::vkglUniform2iv (GLint location, GLsizei count, const GLint *value){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->set_uniform(   location,
                                OpenGL::GetSetArgumentType::Int,
                                2, /*    n_components */
                                   count,
                                   value   );

}

void OpenGL::vkglUniform3iv (GLint location, GLsizei count, const GLint *value){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->set_uniform(   location,
                                OpenGL::GetSetArgumentType::Int,
                                3, /*    n_components */
                                   count,
                                   value   );

}

void OpenGL::vkglUniform4iv (GLint location, GLsizei count, const GLint *value){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->set_uniform(   location,
                                OpenGL::GetSetArgumentType::Int,
                                4, /*    n_components */
                                   count,
                                   value   );

}

void OpenGL::vkglUniformMatrix2fv (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->set_matrix_uniform(   location,
                                       2, /*    n_columns */
                                       2, /*    n_rows    */
                                          count,
                                       (   transpose == GL_TRUE),
                                          value   );

}

void OpenGL::vkglUniformMatrix3fv (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->set_matrix_uniform(   location,
                                       3, /*    n_columns */
                                       3, /*    n_rows    */
                                          count,
                                       (   transpose == GL_TRUE),
                                          value   );

}

void OpenGL::vkglUniformMatrix4fv (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->set_matrix_uniform(   location,
                                       4, /*    n_columns */
                                       4, /*    n_rows    */
                                          count,
                                       (   transpose == GL_TRUE),
                                          value   );

}

void OpenGL::vkglValidateProgram (GLuint program){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->validate_program(   program);

}

void OpenGL::vkglVertexAttrib1d (GLuint index, GLdouble x){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->set_vertex_attribute(   index,
                                         OpenGL::GetSetArgumentType::Double,
                                         OpenGL::GetSetArgumentType::Float,
                                         1,     /*    n_components */
                                         false, /*    normalized   */
                                        &   x);

}

void OpenGL::vkglVertexAttrib1dv (GLuint index, const GLdouble *v){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->set_vertex_attribute(   index,
                                         OpenGL::GetSetArgumentType::Double,
                                         OpenGL::GetSetArgumentType::Float,
                                         1,     /*    n_components */
                                         false, /*    normalized   */
                                            v   );

}

void OpenGL::vkglVertexAttrib1f (GLuint index, GLfloat x){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->set_vertex_attribute(   index,
                                         OpenGL::GetSetArgumentType::Float,
                                         OpenGL::GetSetArgumentType::Float,
                                         1,     /*    n_components */
                                         false, /*    normalized   */
                                        &   x);

}

void OpenGL::vkglVertexAttrib1fv (GLuint index, const GLfloat *v){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->set_vertex_attribute(   index,
                                         OpenGL::GetSetArgumentType::Float,
                                         OpenGL::GetSetArgumentType::Float,
                                         1,     /*    n_components */
                                         false, /*    normalized   */
                                            v   );

}

void OpenGL::vkglVertexAttrib1s (GLuint index, GLshort x){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->set_vertex_attribute(   index,
                                         OpenGL::GetSetArgumentType::Short,
                                         OpenGL::GetSetArgumentType::Float,
                                         1,     /*    n_components */
                                         false, /*    normalized   */
                                        &   x);

}

void OpenGL::vkglVertexAttrib1sv (GLuint index, const GLshort *v){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->set_vertex_attribute(   index,
                                         OpenGL::GetSetArgumentType::Short,
                                         OpenGL::GetSetArgumentType::Float,
                                         1,     /*    n_components */
                                         false, /*    normalized   */
                                            v   );

}

void OpenGL::vkglVertexAttrib2d (GLuint index, GLdouble x, GLdouble y){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const double data[] =
    {
           x,
           y
    };

    in_context_p->set_vertex_attribute(   index,
                                         OpenGL::GetSetArgumentType::Double,
                                         OpenGL::GetSetArgumentType::Float,
                                         2,     /*    n_components */
                                         false, /*    normalized   */
                                         data);

}

void OpenGL::vkglVertexAttrib2dv (GLuint index, const GLdouble *v){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->set_vertex_attribute(   index,
                                         OpenGL::GetSetArgumentType::Double,
                                         OpenGL::GetSetArgumentType::Float,
                                         2,     /*    n_components */
                                         false, /*    normalized   */
                                            v   );

}

void OpenGL::vkglVertexAttrib2f (GLuint index, GLfloat x, GLfloat y){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const GLfloat data[] =
    {
           x,
           y
    };

    in_context_p->set_vertex_attribute(   index,
                                         OpenGL::GetSetArgumentType::Float,
                                         OpenGL::GetSetArgumentType::Float,
                                         2,     /*    n_components */
                                         false, /*    normalized   */
                                         data);

}

void OpenGL::vkglVertexAttrib2fv (GLuint index, const GLfloat *v){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->set_vertex_attribute(   index,
                                         OpenGL::GetSetArgumentType::Float,
                                         OpenGL::GetSetArgumentType::Float,
                                         2,     /*    n_components */
                                         false, /*    normalized   */
                                            v   );

}

void OpenGL::vkglVertexAttrib2s (GLuint index, GLshort x, GLshort y){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const GLshort data[] =
    {
           x,
           y
    };

    in_context_p->set_vertex_attribute(   index,
                                         OpenGL::GetSetArgumentType::Short,
                                         OpenGL::GetSetArgumentType::Float,
                                         2,     /*    n_components */
                                         false, /*    normalized   */
                                         data);

}

void OpenGL::vkglVertexAttrib2sv (GLuint index, const GLshort *v){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->set_vertex_attribute(   index,
                                         OpenGL::GetSetArgumentType::Short,
                                         OpenGL::GetSetArgumentType::Float,
                                         2,     /*    n_components */
                                         false, /*    normalized   */
                                            v   );

}

void OpenGL::vkglVertexAttrib3d (GLuint index, GLdouble x, GLdouble y, GLdouble z){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const double data[] =
    {
           x,
           y,
           z
    };

    in_context_p->set_vertex_attribute(   index,
                                         OpenGL::GetSetArgumentType::Double,
                                         OpenGL::GetSetArgumentType::Float,
                                         3,     /*    n_components */
                                         false, /*    normalized   */
                                         data);

}

void OpenGL::vkglVertexAttrib3dv (GLuint index, const GLdouble *v){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->set_vertex_attribute(   index,
                                         OpenGL::GetSetArgumentType::Double,
                                         OpenGL::GetSetArgumentType::Float,
                                         3,     /*    n_components */
                                         false, /*    normalized   */
                                            v   );

}

void OpenGL::vkglVertexAttrib3f (GLuint index, GLfloat x, GLfloat y, GLfloat z){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const GLfloat data[] =
    {
           x,
           y,
           z
    };

    in_context_p->set_vertex_attribute(   index,
                                         OpenGL::GetSetArgumentType::Float,
                                         OpenGL::GetSetArgumentType::Float,
                                         3,     /*    n_components */
                                         false, /*    normalized   */
                                         data);

}

void OpenGL::vkglVertexAttrib3fv (GLuint index, const GLfloat *v){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->set_vertex_attribute(   index,
                                         OpenGL::GetSetArgumentType::Float,
                                         OpenGL::GetSetArgumentType::Float,
                                         3,     /*    n_components */
                                         false, /*    normalized   */
                                            v   );

}

void OpenGL::vkglVertexAttrib3s (GLuint index, GLshort x, GLshort y, GLshort z){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const GLshort data[] =
    {
           x,
           y,
           z
    };

    in_context_p->set_vertex_attribute(   index,
                                         OpenGL::GetSetArgumentType::Short,
                                         OpenGL::GetSetArgumentType::Float,
                                         3,     /*    n_components */
                                         false, /*    normalized   */
                                         data);

}

void OpenGL::vkglVertexAttrib3sv (GLuint index, const GLshort *v){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->set_vertex_attribute(   index,
                                         OpenGL::GetSetArgumentType::Short,
                                         OpenGL::GetSetArgumentType::Float,
                                         3,     /*    n_components */
                                         false, /*    normalized   */
                                            v   );

}

void OpenGL::vkglVertexAttrib4Nbv (GLuint index, const GLbyte *v){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->set_vertex_attribute(   index,
                                         OpenGL::GetSetArgumentType::Byte,
                                         OpenGL::GetSetArgumentType::Float,
                                         4,     /*    n_components */
                                         true, /*    normalized   */
                                            v   );

}

void OpenGL::vkglVertexAttrib4Niv (GLuint index, const GLint *v){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->set_vertex_attribute(   index,
                                         OpenGL::GetSetArgumentType::Int,
                                         OpenGL::GetSetArgumentType::Float,
                                         4,     /*    n_components */
                                         true, /*    normalized   */
                                            v   );

}

void OpenGL::vkglVertexAttrib4Nsv (GLuint index, const GLshort *v){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->set_vertex_attribute(   index,
                                         OpenGL::GetSetArgumentType::Short,
                                         OpenGL::GetSetArgumentType::Float,
                                         4,     /*    n_components */
                                         true, /*    normalized   */
                                            v   );

}

void OpenGL::vkglVertexAttrib4Nub (GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const GLubyte data[] =
    {
           x,
           y,
           z,
           w
    };

    in_context_p->set_vertex_attribute(   index,
                                         OpenGL::GetSetArgumentType::Unsigned_Byte,
                                         OpenGL::GetSetArgumentType::Float,
                                         4,    /*    n_components */
                                         true, /*    normalized   */
                                         data);

}

void OpenGL::vkglVertexAttrib4Nubv (GLuint index, const GLubyte *v){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->set_vertex_attribute(   index,
                                         OpenGL::GetSetArgumentType::Unsigned_Byte,
                                         OpenGL::GetSetArgumentType::Float,
                                         4,     /*    n_components */
                                         true, /*    normalized   */
                                            v   );

}

void OpenGL::vkglVertexAttrib4Nuiv (GLuint index, const GLuint *v){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->set_vertex_attribute(   index,
                                         OpenGL::GetSetArgumentType::Unsigned_Int,
                                         OpenGL::GetSetArgumentType::Float,
                                         4,     /*    n_components */
                                         true, /*    normalized   */
                                            v   );

}

void OpenGL::vkglVertexAttrib4Nusv (GLuint index, const GLushort *v){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->set_vertex_attribute(   index,
                                         OpenGL::GetSetArgumentType::Unsigned_Short,
                                         OpenGL::GetSetArgumentType::Float,
                                         4,     /*    n_components */
                                         true, /*    normalized   */
                                            v   );

}

void OpenGL::vkglVertexAttrib4bv (GLuint index, const GLbyte *v){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->set_vertex_attribute(   index,
                                         OpenGL::GetSetArgumentType::Byte,
                                         OpenGL::GetSetArgumentType::Float,
                                         4,     /*    n_components */
                                         false, /*    normalized   */
                                            v   );

}

void OpenGL::vkglVertexAttrib4d (GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const double data[] =
    {
           x,
           y,
           z,
           w
    };

    in_context_p->set_vertex_attribute(   index,
                                         OpenGL::GetSetArgumentType::Double,
                                         OpenGL::GetSetArgumentType::Float,
                                         4,     /*    n_components */
                                         false, /*    normalized   */
                                         data);

}

void OpenGL::vkglVertexAttrib4dv (GLuint index, const GLdouble *v){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->set_vertex_attribute(   index,
                                         OpenGL::GetSetArgumentType::Double,
                                         OpenGL::GetSetArgumentType::Float,
                                         4,     /*    n_components */
                                         false, /*    normalized   */
                                            v   );

}

void OpenGL::vkglVertexAttrib4f (GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const GLfloat data[] =
    {
           x,
           y,
           z,
           w
    };

    in_context_p->set_vertex_attribute(   index,
                                         OpenGL::GetSetArgumentType::Float,
                                         OpenGL::GetSetArgumentType::Float,
                                         4,     /*    n_components */
                                         false, /*    normalized   */
                                         data);

}

void OpenGL::vkglVertexAttrib4fv (GLuint index, const GLfloat *v){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->set_vertex_attribute(   index,
                                         OpenGL::GetSetArgumentType::Float,
                                         OpenGL::GetSetArgumentType::Float,
                                         4,     /*    n_components */
                                         false, /*    normalized   */
                                            v   );

}

void OpenGL::vkglVertexAttrib4iv (GLuint index, const GLint *v){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->set_vertex_attribute(   index,
                                         OpenGL::GetSetArgumentType::Int,
                                         OpenGL::GetSetArgumentType::Float,
                                         4,     /*    n_components */
                                         false, /*    normalized   */
                                            v   );

}

void OpenGL::vkglVertexAttrib4s (GLuint index, GLshort x, GLshort y, GLshort z, GLshort w){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const GLshort data[] =
    {
           x,
           y,
           z,
           w
    };

    in_context_p->set_vertex_attribute(   index,
                                         OpenGL::GetSetArgumentType::Short,
                                         OpenGL::GetSetArgumentType::Float,
                                         4,     /*    n_components */
                                         false, /*    normalized   */
                                         data);

}

void OpenGL::vkglVertexAttrib4sv (GLuint index, const GLshort *v){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->set_vertex_attribute(   index,
                                         OpenGL::GetSetArgumentType::Short,
                                         OpenGL::GetSetArgumentType::Float,
                                         4,     /*    n_components */
                                         false, /*    normalized   */
                                            v   );

}

void OpenGL::vkglVertexAttrib4ubv (GLuint index, const GLubyte *v){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->set_vertex_attribute(   index,
                                         OpenGL::GetSetArgumentType::Unsigned_Byte,
                                         OpenGL::GetSetArgumentType::Float,
                                         4,     /*    n_components */
                                         false, /*    normalized   */
                                            v   );

}

void OpenGL::vkglVertexAttrib4uiv (GLuint index, const GLuint *v){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->set_vertex_attribute(   index,
                                         OpenGL::GetSetArgumentType::Unsigned_Int,
                                         OpenGL::GetSetArgumentType::Float,
                                         4,     /*    n_components */
                                         false, /*    normalized   */
                                            v   );

}

void OpenGL::vkglVertexAttrib4usv (GLuint index, const GLushort *v){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->set_vertex_attribute(   index,
                                         OpenGL::GetSetArgumentType::Unsigned_Short,
                                         OpenGL::GetSetArgumentType::Float,
                                         4,     /*    n_components */
                                         false, /*    normalized   */
                                            v   );

}

void OpenGL::vkglVertexAttribPointer (GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto type_vkgl = OpenGL::Utils::get_vertex_attribute_array_type_for_gl_enum(   type);

    in_context_p->set_vertex_attrib_pointer(   index,
                                                 size,
                                              type_vkgl,
                                              OpenGL::GetSetArgumentType::Float,
                                                 normalized == GL_TRUE,
                                                 stride,
                                                 pointer   );

}



// GL_VERSION_2_1
void OpenGL::vkglUniformMatrix2x3fv (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->set_matrix_uniform(   location,
                                       2, /*    n_columns */
                                       3, /*    n_rows    */
                                          count,
                                       (   transpose == GL_TRUE),
                                          value   );

}

void OpenGL::vkglUniformMatrix3x2fv (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->set_matrix_uniform(   location,
                                       3, /*    n_columns */
                                       2, /*    n_rows    */
                                          count,
                                       (   transpose == GL_TRUE),
                                          value   );

}

void OpenGL::vkglUniformMatrix2x4fv (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->set_matrix_uniform(   location,
                                       2, /*    n_columns */
                                       4, /*    n_rows    */
                                          count,
                                       (   transpose == GL_TRUE),
                                          value   );

}

void OpenGL::vkglUniformMatrix4x2fv (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->set_matrix_uniform(   location,
                                       4, /*    n_columns */
                                       2, /*    n_rows    */
                                          count,
                                       (   transpose == GL_TRUE),
                                          value   );

}

void OpenGL::vkglUniformMatrix3x4fv (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->set_matrix_uniform(   location,
                                       3, /*    n_columns */
                                       4, /*    n_rows    */
                                          count,
                                       (   transpose == GL_TRUE),
                                          value   );

}

void OpenGL::vkglUniformMatrix4x3fv (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->set_matrix_uniform(   location,
                                       4, /*    n_columns */
                                       3, /*    n_rows    */
                                          count,
                                       (   transpose == GL_TRUE),
                                          value   );

}



// GL_VERSION_3_0
void OpenGL::vkglColorMaski (GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->set_color_mask_indexed(   index,
                                           (   r == GL_TRUE) ? true : false,
                                           (   g == GL_TRUE) ? true : false,
                                           (   b == GL_TRUE) ? true : false,
                                           (   a == GL_TRUE) ? true : false);

}

void OpenGL::vkglGetBooleani_v (GLenum target, GLuint index, GLboolean *data){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const OpenGL::ContextProperty target_vkgl = OpenGL::Utils::get_context_property_for_gl_enum(   target);

    in_context_p->get_parameter_indexed(target_vkgl,
                                          OpenGL::GetSetArgumentType::Boolean,
                                             index,
                                              data    );

}

void OpenGL::vkglGetIntegeri_v (GLenum target, GLuint index, GLint *data){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto target_vkgl = OpenGL::Utils::get_context_property_for_gl_enum(   target);

    in_context_p->get_parameter_indexed(target_vkgl,
                                          OpenGL::GetSetArgumentType::Int,
                                             index,
                                              data    );

}

void OpenGL::vkglEnablei (GLenum target, GLuint index){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    vkgl_assert(   target == GL_BLEND);

    in_context_p->enable_indexed(OpenGL::Capability::Blend,
                                      index);

}

void OpenGL::vkglDisablei (GLenum target, GLuint index){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    vkgl_assert(   target == GL_BLEND);

    in_context_p->disable_indexed(OpenGL::Capability::Blend,
                                       index);

}

GLboolean OpenGL::vkglIsEnabledi (GLenum target, GLuint index){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    vkgl_assert(   target == GL_BLEND);

    return in_context_p->is_enabled_indexed(OpenGL::Capability::Blend,
                                                 index);

}

void OpenGL::vkglBeginTransformFeedback (GLenum primitiveMode){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto primitive_mode_vkgl = OpenGL::Utils::get_transform_feedback_primitive_mode_for_gl_enum(   primitiveMode);

    in_context_p->begin_transform_feedback(primitive_mode_vkgl);

}

void OpenGL::vkglEndTransformFeedback (void){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->end_transform_feedback();

}

void OpenGL::vkglBindBufferRange (GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto target_vkgl = OpenGL::Utils::get_buffer_target_for_gl_enum(   target);

    in_context_p->bind_buffer_range(target_vkgl,
                                         index,
                                         buffer,
                                         offset,
                                         size);

}

void OpenGL::vkglBindBufferBase (GLenum target, GLuint index, GLuint buffer){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto target_vkgl = OpenGL::Utils::get_buffer_target_for_gl_enum(   target);

    in_context_p->bind_buffer_base(target_vkgl,
                                        index,
                                        buffer);

}

void OpenGL::vkglTransformFeedbackVaryings (GLuint program, GLsizei count, const GLchar *const*varyings, GLenum bufferMode){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto buffer_mode_vkgl = OpenGL::Utils::get_transform_feedback_buffer_mode_for_gl_enum(   bufferMode);

    in_context_p->set_transform_feedback_varyings(   program,
                                                       count,
                                                       varyings        ,
                                                    buffer_mode_vkgl);

}

void OpenGL::vkglGetTransformFeedbackVarying (GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLsizei *size, GLenum *type, GLchar *name){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    OpenGL::VariableType type_vkgl = OpenGL::VariableType::Unknown;

    in_context_p->get_transform_feedback_varying(   program,
                                                      index,
                                                      bufSize,
                                                       length    ,
                                                       size    ,
                                                  &type_vkgl,
                                                       name    );

    *    type     = OpenGL::Utils::get_gl_enum_for_variable_type(type_vkgl);

}

void OpenGL::vkglClampColor (GLenum target, GLenum clamp){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    vkgl_assert(   target == GL_CLAMP_READ_COLOR);

    in_context_p->set_clamp_color( (   clamp == GL_TRUE) ? true : false);

}

void OpenGL::vkglBeginConditionalRender (GLuint id, GLenum mode){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto mode_vkgl = OpenGL::Utils::get_conditional_render_mode_for_gl_enum(   mode);

    in_context_p->begin_conditional_render(   id,
                                             mode_vkgl);

}

void OpenGL::vkglEndConditionalRender (void){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->end_conditional_render();

}

void OpenGL::vkglVertexAttribIPointer (GLuint index, GLint size, GLenum type, GLsizei stride, const void *pointer){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto type_vkgl = OpenGL::Utils::get_vertex_attribute_array_type_for_gl_enum(   type);

    in_context_p->set_vertex_attrib_pointer(   index,
                                                 size,
                                              type_vkgl,
                                              OpenGL::GetSetArgumentType::Int,
                                              false, /*    normalized */
                                                 stride,
                                                 pointer    );

}

void OpenGL::vkglGetVertexAttribIiv (GLuint index, GLenum pname, GLint *params){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto pname_vkgl = OpenGL::Utils::get_vertex_attribute_property_for_gl_enum(   pname);

    in_context_p->get_vertex_attribute_property(   index,
                                                  pname_vkgl,
                                                  OpenGL::GetSetArgumentType::Int,
                                                  OpenGL::GetSetArgumentType::Int,
                                                      params    );

}

void OpenGL::vkglGetVertexAttribIuiv (GLuint index, GLenum pname, GLuint *params){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto pname_vkgl = OpenGL::Utils::get_vertex_attribute_property_for_gl_enum(   pname);

    in_context_p->get_vertex_attribute_property(   index,
                                                  pname_vkgl,
                                                  OpenGL::GetSetArgumentType::Unsigned_Int,
                                                  OpenGL::GetSetArgumentType::Unsigned_Int,
                                                      params    );

}

void OpenGL::vkglVertexAttribI1i (GLuint index, GLint x){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->set_vertex_attribute(   index,
                                         OpenGL::GetSetArgumentType::Int,
                                         OpenGL::GetSetArgumentType::Int,
                                         1,     /*    n_components */
                                         false, /*    normalized   */
                                        &   x);

}

void OpenGL::vkglVertexAttribI2i (GLuint index, GLint x, GLint y){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const GLint data[] =
    {
           x,
           y,
    };

    in_context_p->set_vertex_attribute(   index,
                                         OpenGL::GetSetArgumentType::Int,
                                         OpenGL::GetSetArgumentType::Int,
                                         2,     /*    n_components */
                                         false, /*    normalized   */
                                         data);

}

void OpenGL::vkglVertexAttribI3i (GLuint index, GLint x, GLint y, GLint z){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const GLint data[] =
    {
           x,
           y,
           z,
    };

    in_context_p->set_vertex_attribute(   index,
                                         OpenGL::GetSetArgumentType::Int,
                                         OpenGL::GetSetArgumentType::Int,
                                         3,     /*    n_components */
                                         false, /*    normalized   */
                                         data);

}

void OpenGL::vkglVertexAttribI4i (GLuint index, GLint x, GLint y, GLint z, GLint w){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const GLint data[] =
    {
           x,
           y,
           z,
           w,
    };

    in_context_p->set_vertex_attribute(   index,
                                         OpenGL::GetSetArgumentType::Int,
                                         OpenGL::GetSetArgumentType::Int,
                                         4,     /*    n_components */
                                         false, /*    normalized   */
                                         data);

}

void OpenGL::vkglVertexAttribI1ui (GLuint index, GLuint x){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->set_vertex_attribute(   index,
                                         OpenGL::GetSetArgumentType::Unsigned_Int,
                                         OpenGL::GetSetArgumentType::Unsigned_Int,
                                         1,     /*    n_components */
                                         false, /*    normalized   */
                                        &   x);

}

void OpenGL::vkglVertexAttribI2ui (GLuint index, GLuint x, GLuint y){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const GLuint data[] =
    {
           x,
           y,
    };

    in_context_p->set_vertex_attribute(   index,
                                         OpenGL::GetSetArgumentType::Unsigned_Int,
                                         OpenGL::GetSetArgumentType::Unsigned_Int,
                                         2,     /*    n_components */
                                         false, /*    normalized   */
                                         data);

}

void OpenGL::vkglVertexAttribI3ui (GLuint index, GLuint x, GLuint y, GLuint z){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const GLuint data[] =
    {
           x,
           y,
           z,
    };

    in_context_p->set_vertex_attribute(   index,
                                         OpenGL::GetSetArgumentType::Unsigned_Int,
                                         OpenGL::GetSetArgumentType::Unsigned_Int,
                                         3,     /*    n_components */
                                         false, /*    normalized   */
                                         data);

}

void OpenGL::vkglVertexAttribI4ui (GLuint index, GLuint x, GLuint y, GLuint z, GLuint w){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const GLuint data[] =
    {
           x,
           y,
           z,
           w,
    };

    in_context_p->set_vertex_attribute(   index,
                                         OpenGL::GetSetArgumentType::Unsigned_Int,
                                         OpenGL::GetSetArgumentType::Unsigned_Int,
                                         4,     /*    n_components */
                                         false, /*    normalized   */
                                         data);

}

void OpenGL::vkglVertexAttribI1iv (GLuint index, const GLint *v){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->set_vertex_attribute(   index,
                                         OpenGL::GetSetArgumentType::Int,
                                         OpenGL::GetSetArgumentType::Int,
                                         1,     /*    n_components */
                                         false, /*    normalized   */
                                            v    );

}

void OpenGL::vkglVertexAttribI2iv (GLuint index, const GLint *v){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->set_vertex_attribute(   index,
                                         OpenGL::GetSetArgumentType::Int,
                                         OpenGL::GetSetArgumentType::Int,
                                         2,     /*    n_components */
                                         false, /*    normalized   */
                                            v    );

}

void OpenGL::vkglVertexAttribI3iv (GLuint index, const GLint *v){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->set_vertex_attribute(   index,
                                         OpenGL::GetSetArgumentType::Int,
                                         OpenGL::GetSetArgumentType::Int,
                                         3,     /*    n_components */
                                         false, /*    normalized   */
                                            v    );

}

void OpenGL::vkglVertexAttribI4iv (GLuint index, const GLint *v){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->set_vertex_attribute(   index,
                                         OpenGL::GetSetArgumentType::Int,
                                         OpenGL::GetSetArgumentType::Int,
                                         4,     /*    n_components */
                                         false, /*    normalized   */
                                            v    );

}

void OpenGL::vkglVertexAttribI1uiv (GLuint index, const GLuint *v){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->set_vertex_attribute(   index,
                                         OpenGL::GetSetArgumentType::Unsigned_Int,
                                         OpenGL::GetSetArgumentType::Unsigned_Int,
                                         1,     /*    n_components */
                                         false, /*    normalized   */
                                            v    );

}

void OpenGL::vkglVertexAttribI2uiv (GLuint index, const GLuint *v){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->set_vertex_attribute(   index,
                                         OpenGL::GetSetArgumentType::Unsigned_Int,
                                         OpenGL::GetSetArgumentType::Unsigned_Int,
                                         2,     /*    n_components */
                                         false, /*    normalized   */
                                            v    );

}

void OpenGL::vkglVertexAttribI3uiv (GLuint index, const GLuint *v){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->set_vertex_attribute(   index,
                                         OpenGL::GetSetArgumentType::Unsigned_Int,
                                         OpenGL::GetSetArgumentType::Unsigned_Int,
                                         3,     /*    n_components */
                                         false, /*    normalized   */
                                            v    );

}

void OpenGL::vkglVertexAttribI4uiv (GLuint index, const GLuint *v){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->set_vertex_attribute(   index,
                                         OpenGL::GetSetArgumentType::Unsigned_Int,
                                         OpenGL::GetSetArgumentType::Unsigned_Int,
                                         4,     /*    n_components */
                                         false, /*    normalized   */
                                            v    );

}

void OpenGL::vkglVertexAttribI4bv (GLuint index, const GLbyte *v){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->set_vertex_attribute(   index,
                                         OpenGL::GetSetArgumentType::Byte,
                                         OpenGL::GetSetArgumentType::Int,
                                         4,     /*    n_components */
                                         false, /*    normalized   */
                                            v    );

}

void OpenGL::vkglVertexAttribI4sv (GLuint index, const GLshort *v){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->set_vertex_attribute(   index,
                                         OpenGL::GetSetArgumentType::Short,
                                         OpenGL::GetSetArgumentType::Int,
                                         4,     /*    n_components */
                                         false, /*    normalized   */
                                            v    );

}

void OpenGL::vkglVertexAttribI4ubv (GLuint index, const GLubyte *v){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->set_vertex_attribute(   index,
                                         OpenGL::GetSetArgumentType::Unsigned_Byte,
                                         OpenGL::GetSetArgumentType::Int,
                                         4,     /*    n_components */
                                         false, /*    normalized   */
                                            v    );

}

void OpenGL::vkglVertexAttribI4usv (GLuint index, const GLushort *v){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->set_vertex_attribute(   index,
                                         OpenGL::GetSetArgumentType::Unsigned_Short,
                                         OpenGL::GetSetArgumentType::Int,
                                         4,     /*    n_components */
                                         false, /*    normalized   */
                                            v    );

}

void OpenGL::vkglGetUniformuiv (GLuint program, GLint location, GLuint *params){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->get_uniform_value(   program,
                                         location,
                                      OpenGL::GetSetArgumentType::Unsigned_Int,
                                          params    );

}

void OpenGL::vkglBindFragDataLocation (GLuint program, GLuint color, const GLchar *name){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->bind_frag_data_location(   program,
                                               color,
                                               name);

}

GLint OpenGL::vkglGetFragDataLocation (GLuint program, const GLchar *name){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    return in_context_p->get_frag_data_location(   program,
                                                     name    );

}

void OpenGL::vkglUniform1ui (GLint location, GLuint v0){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->set_uniform(   location,
                                OpenGL::GetSetArgumentType::Unsigned_Int,
                                1, /*    n_components  */
                                1, /*    n_array_items */
                               &   v0);

}

void OpenGL::vkglUniform2ui (GLint location, GLuint v0, GLuint v1){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const GLuint data[] =
    {
           v0,
           v1,
    };

    in_context_p->set_uniform(   location,
                                OpenGL::GetSetArgumentType::Unsigned_Int,
                                2, /*    n_components  */
                                1, /*    n_array_items */
                                data);

}

void OpenGL::vkglUniform3ui (GLint location, GLuint v0, GLuint v1, GLuint v2){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const GLuint data[] =
    {
           v0,
           v1,
           v2,
    };

    in_context_p->set_uniform(   location,
                                OpenGL::GetSetArgumentType::Unsigned_Int,
                                3, /*    n_components  */
                                1, /*    n_array_items */
                                data);

}

void OpenGL::vkglUniform4ui (GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const GLuint data[] =
    {
           v0,
           v1,
           v2,
           v3
    };

    in_context_p->set_uniform(   location,
                                OpenGL::GetSetArgumentType::Unsigned_Int,
                                4, /*    n_components  */
                                1, /*    n_array_items */
                                data);

}

void OpenGL::vkglUniform1uiv (GLint location, GLsizei count, const GLuint *value){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->set_uniform(   location,
                                OpenGL::GetSetArgumentType::Unsigned_Int,
                                1, /*    n_components */
                                   count,
                                   value    );

}

void OpenGL::vkglUniform2uiv (GLint location, GLsizei count, const GLuint *value){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->set_uniform(   location,
                                OpenGL::GetSetArgumentType::Unsigned_Int,
                                2, /*    n_components */
                                   count,
                                   value    );

}

void OpenGL::vkglUniform3uiv (GLint location, GLsizei count, const GLuint *value){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->set_uniform(   location,
                                OpenGL::GetSetArgumentType::Unsigned_Int,
                                3, /*    n_components */
                                   count,
                                   value    );

}

void OpenGL::vkglUniform4uiv (GLint location, GLsizei count, const GLuint *value){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->set_uniform(   location,
                                OpenGL::GetSetArgumentType::Unsigned_Int,
                                4, /*    n_components */
                                   count,
                                   value    );

}

void OpenGL::vkglTexParameterIiv (GLenum target, GLenum pname, const GLint *params){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto pname_vkgl  = OpenGL::Utils::get_texture_property_for_gl_enum(   pname);
    const auto target_vkgl = OpenGL::Utils::get_texture_target_for_gl_enum  (   target);

    in_context_p->set_texture_parameter(target_vkgl,
                                          pname_vkgl,
                                          OpenGL::GetSetArgumentType::Int,
                                             params    );

}

void OpenGL::vkglTexParameterIuiv (GLenum target, GLenum pname, const GLuint *params){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto pname_vkgl  = OpenGL::Utils::get_texture_property_for_gl_enum(   pname);
    const auto target_vkgl = OpenGL::Utils::get_texture_target_for_gl_enum  (   target);

    in_context_p->set_texture_parameter(target_vkgl,
                                          pname_vkgl,
                                          OpenGL::GetSetArgumentType::Unsigned_Int,
                                             params    );

}

void OpenGL::vkglGetTexParameterIiv (GLenum target, GLenum pname, GLint *params){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto pname_vkgl  = OpenGL::Utils::get_texture_property_for_gl_enum(   pname);
    const auto target_vkgl = OpenGL::Utils::get_texture_target_for_gl_enum (   target);

    in_context_p->get_texture_parameter(target_vkgl,
                                          pname_vkgl,
                                          OpenGL::GetSetArgumentType::Int,
                                              params    );

}

void OpenGL::vkglGetTexParameterIuiv (GLenum target, GLenum pname, GLuint *params){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto pname_vkgl  = OpenGL::Utils::get_texture_property_for_gl_enum(   pname);
    const auto target_vkgl = OpenGL::Utils::get_texture_target_for_gl_enum (   target);

    in_context_p->get_texture_parameter(target_vkgl,
                                          pname_vkgl,
                                          OpenGL::GetSetArgumentType::Unsigned_Int,
                                              params    );

}

void OpenGL::vkglClearBufferiv (GLenum buffer, GLint drawbuffer, const GLint *value){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto     buffer_vkgl   = OpenGL::Utils::get_clear_buffer_for_gl_enum(   buffer);
    const uint32_t n_components  = (   buffer == GL_STENCIL) ? 0             : 4;
    const auto     stencil_value = (   buffer == GL_STENCIL) ? *   value     : 0;

    in_context_p->clear_buffer(buffer_vkgl,
                                    drawbuffer,
                                 OpenGL::GetSetArgumentType::Int,
                                 n_components,
                                    value    ,
                                 0,
                                 stencil_value);

}

void OpenGL::vkglClearBufferuiv (GLenum buffer, GLint drawbuffer, const GLuint *value){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto     buffer_vkgl   = OpenGL::Utils::get_clear_buffer_for_gl_enum(   buffer);
    const uint32_t n_components  = (   buffer == GL_STENCIL) ? 0             : 4;
    const auto     stencil_value = (   buffer == GL_STENCIL) ? *   value     : 0;

    in_context_p->clear_buffer(buffer_vkgl,
                                    drawbuffer,
                                 OpenGL::GetSetArgumentType::Unsigned_Int,
                                 n_components,
                                    value    ,
                                 0,
                                 stencil_value);

}

void OpenGL::vkglClearBufferfv (GLenum buffer, GLint drawbuffer, const GLfloat *value){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto     buffer_vkgl  = OpenGL::Utils::get_clear_buffer_for_gl_enum(   buffer);
    const auto     depth_value  = (   buffer == GL_DEPTH) ? *   value     : 0.0f;
    const uint32_t n_components = (   buffer == GL_DEPTH) ? 0             : 4;

    in_context_p->clear_buffer(buffer_vkgl,
                                    drawbuffer,
                                 OpenGL::GetSetArgumentType::Float,
                                 n_components,
                                    value    ,
                                 depth_value,
                                 0);

}

void OpenGL::vkglClearBufferfi (GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto buffer_vkgl = OpenGL::Utils::get_clear_buffer_for_gl_enum(   buffer);

    in_context_p->clear_buffer(buffer_vkgl,
                                    drawbuffer,
                                 OpenGL::GetSetArgumentType::Unknown,
                                 0,
                                 nullptr,
                                    depth,
                                    stencil);

}

const GLubyte *OpenGL::vkglGetStringi (GLenum name, GLuint index){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto     name_vkgl  = OpenGL::Utils::get_context_property_for_gl_enum(   name);
    const GLubyte* result     = nullptr;

    in_context_p->get_parameter_indexed(name_vkgl,
                                          OpenGL::GetSetArgumentType::String,
                                             index,
                                         &result    );

    return result    ;

}

GLboolean OpenGL::vkglIsRenderbuffer (GLuint renderbuffer){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    return in_context_p->is_renderbuffer(   renderbuffer);

}

void OpenGL::vkglBindRenderbuffer (GLenum target, GLuint renderbuffer){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto target_vkgl = OpenGL::Utils::get_renderbuffer_target_for_gl_enum(   target);

    in_context_p->bind_renderbuffer(target_vkgl,
                                         renderbuffer);

}

void OpenGL::vkglDeleteRenderbuffers (GLsizei n, const GLuint *renderbuffers){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->delete_renderbuffers(   n,
                                            renderbuffers    );

}

void OpenGL::vkglGenRenderbuffers (GLsizei n, GLuint *renderbuffers){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->gen_renderbuffers(   n,
                                          renderbuffers    );

}

void OpenGL::vkglRenderbufferStorage (GLenum target, GLenum internalformat, GLsizei width, GLsizei height){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto internalformat_vkgl = OpenGL::Utils::get_internal_format_for_gl_enum    (   internalformat);
    const auto target_vkgl         = OpenGL::Utils::get_renderbuffer_target_for_gl_enum(   target);

    in_context_p->set_renderbuffer_storage(target_vkgl,
                                             internalformat_vkgl,
                                                width,
                                                height);

}

void OpenGL::vkglGetRenderbufferParameteriv (GLenum target, GLenum pname, GLint *params){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto pname_vkgl  = OpenGL::Utils::get_renderbuffer_property_for_gl_enum(   pname);
    const auto target_vkgl = OpenGL::Utils::get_renderbuffer_target_for_gl_enum  (   target);

    in_context_p->get_renderbuffer_property(target_vkgl,
                                              pname_vkgl,
                                              OpenGL::GetSetArgumentType::Int,
                                                  params    );

}

GLboolean OpenGL::vkglIsFramebuffer (GLuint framebuffer){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    return in_context_p->is_framebuffer(   framebuffer);

}

void OpenGL::vkglBindFramebuffer (GLenum target, GLuint framebuffer){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto target_vkgl = OpenGL::Utils::get_framebuffer_target_for_gl_enum(   target);

    in_context_p->bind_framebuffer(target_vkgl,
                                        framebuffer);

}

void OpenGL::vkglDeleteFramebuffers (GLsizei n, const GLuint *framebuffers){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->delete_framebuffers(   n,
                                           framebuffers    );

}

void OpenGL::vkglGenFramebuffers (GLsizei n, GLuint *framebuffers){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->gen_framebuffers(   n,
                                         framebuffers    );

}

GLenum OpenGL::vkglCheckFramebufferStatus (GLenum target){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    OpenGL::FramebufferStatus result = OpenGL::FramebufferStatus::Unknown;

    const auto target_vkgl = OpenGL::Utils::get_framebuffer_target_for_gl_enum(   target);

    result = in_context_p->check_framebuffer_status(target_vkgl);

    return OpenGL::Utils::get_gl_enum_for_framebuffer_status(result);

}

void OpenGL::vkglFramebufferTexture1D (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto attachment_vkgl = OpenGL::Utils::get_framebuffer_attachment_point_for_gl_enum(   attachment);
    const auto target_vkgl     = OpenGL::Utils::get_framebuffer_target_for_gl_enum          (   target);
    const auto textarget_vkgl  = OpenGL::Utils::get_texture_target_for_gl_enum              (   textarget);

    in_context_p->framebuffer_texture_1D(target_vkgl,
                                           attachment_vkgl,
                                           textarget_vkgl,
                                              texture,
                                              level);

}

void OpenGL::vkglFramebufferTexture2D (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto attachment_vkgl = OpenGL::Utils::get_framebuffer_attachment_point_for_gl_enum(   attachment);
    const auto target_vkgl     = OpenGL::Utils::get_framebuffer_target_for_gl_enum          (   target);
    const auto textarget_vkgl  = OpenGL::Utils::get_texture_target_for_gl_enum              (   textarget);

    in_context_p->framebuffer_texture_2D(target_vkgl,
                                           attachment_vkgl,
                                           textarget_vkgl,
                                              texture,
                                              level);

}

void OpenGL::vkglFramebufferTexture3D (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto attachment_vkgl = OpenGL::Utils::get_framebuffer_attachment_point_for_gl_enum(   attachment);
    const auto target_vkgl     = OpenGL::Utils::get_framebuffer_target_for_gl_enum          (   target);
    const auto textarget_vkgl  = OpenGL::Utils::get_texture_target_for_gl_enum              (   textarget);

    in_context_p->framebuffer_texture_3D(target_vkgl,
                                           attachment_vkgl,
                                           textarget_vkgl,
                                              texture,
                                              level,
                                              zoffset);

}

void OpenGL::vkglFramebufferRenderbuffer (GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto attachment_vkgl         = OpenGL::Utils::get_framebuffer_attachment_point_for_gl_enum(   attachment);
    const auto renderbuffertarget_vkgl = OpenGL::Utils::get_renderbuffer_target_for_gl_enum         (   renderbuffertarget);
    const auto target_vkgl             = OpenGL::Utils::get_framebuffer_target_for_gl_enum          (   target);

    in_context_p->framebuffer_renderbuffer(target_vkgl,
                                             attachment_vkgl,
                                             renderbuffertarget_vkgl,
                                                renderbuffer);

}

void OpenGL::vkglGetFramebufferAttachmentParameteriv (GLenum target, GLenum attachment, GLenum pname, GLint *params){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto attachment_vkgl = OpenGL::Utils::get_framebuffer_attachment_point_for_gl_enum   (   attachment);
    const auto pname_vkgl      = OpenGL::Utils::get_framebuffer_attachment_property_for_gl_enum(   pname);
    const auto target_vkgl     = OpenGL::Utils::get_framebuffer_target_for_gl_enum             (   target);

    in_context_p->get_framebuffer_attachment_property(target_vkgl,
                                                        attachment_vkgl,
                                                        pname_vkgl,
                                                        OpenGL::GetSetArgumentType::Int,
                                                            params    );

}

void OpenGL::vkglGenerateMipmap (GLenum target){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto target_vkgl = OpenGL::Utils::get_mipmap_generation_texture_target_for_gl_enum(   target);

    in_context_p->generate_mipmap(target_vkgl);

}

void OpenGL::vkglBlitFramebuffer (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto filter_vkgl = OpenGL::Utils::get_blit_filter_for_gl_enum   (   filter);
    const auto mask_vkgl   = OpenGL::Utils::get_blit_mask_bits_for_gl_enum(   mask);

    in_context_p->blit_framebuffer(   srcX0,
                                        srcY0,
                                        srcX1,
                                        srcY1,
                                        dstX0,
                                        dstY0,
                                        dstX1,
                                        dstY1,
                                     mask_vkgl,
                                     filter_vkgl);

}

void OpenGL::vkglRenderbufferStorageMultisample (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto internalformat_vkgl = OpenGL::Utils::get_internal_format_for_gl_enum    (   internalformat);
    const auto target_vkgl         = OpenGL::Utils::get_renderbuffer_target_for_gl_enum(   target);

    in_context_p->set_renderbuffer_storage_multisample(target_vkgl,
                                                            samples,
                                                         internalformat_vkgl,
                                                            width,
                                                            height);

}

void OpenGL::vkglFramebufferTextureLayer (GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto attachment_vkgl = OpenGL::Utils::get_framebuffer_attachment_point_for_gl_enum(   attachment);
    const auto target_vkgl     = OpenGL::Utils::get_framebuffer_target_for_gl_enum          (   target);

    in_context_p->framebuffer_texture_layer(target_vkgl,
                                              attachment_vkgl,
                                                 texture,
                                                 level,
                                                 layer);

}

void *OpenGL::vkglMapBufferRange (GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto access_vkgl = OpenGL::Utils::get_buffer_access_for_gl_enum(   access);
    const auto target_vkgl = OpenGL::Utils::get_buffer_target_for_gl_enum(   target);

    return in_context_p->map_buffer_range(target_vkgl,
                                               offset,
                                               length,
                                            access_vkgl);

}

void OpenGL::vkglFlushMappedBufferRange (GLenum target, GLintptr offset, GLsizeiptr length){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto target_vkgl = OpenGL::Utils::get_buffer_target_for_gl_enum(   target);

    in_context_p->flush_mapped_buffer_range(target_vkgl,
                                                 offset,
                                                 length);

}

void OpenGL::vkglBindVertexArray (GLuint array){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->bind_vertex_array(   array);

}

void OpenGL::vkglDeleteVertexArrays (GLsizei n, const GLuint *arrays){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->delete_vertex_arrays(   n,
                                            arrays    );

}

void OpenGL::vkglGenVertexArrays (GLsizei n, GLuint *arrays){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->gen_vertex_arrays(   n,
                                          arrays    );

}

GLboolean OpenGL::vkglIsVertexArray (GLuint array){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    return in_context_p->is_vertex_array(   array) == GL_TRUE;

}



// GL_VERSION_3_1
void OpenGL::vkglDrawArraysInstanced (GLenum mode, GLint first, GLsizei count, GLsizei instancecount){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto mode_vkgl = OpenGL::Utils::get_draw_call_mode_for_gl_enum(   mode);

    in_context_p->draw_arrays_instanced(mode_vkgl,
                                             first,
                                             count,
                                             instancecount);

}

void OpenGL::vkglDrawElementsInstanced (GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei instancecount){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto mode_vkgl = OpenGL::Utils::get_draw_call_mode_for_gl_enum      (   mode);
    const auto type_vkgl = OpenGL::Utils::get_draw_call_index_type_for_gl_enum(   type);

    in_context_p->draw_elements_instanced(mode_vkgl,
                                               count,
                                            type_vkgl,
                                               indices    ,
                                               instancecount);

}

void OpenGL::vkglTexBuffer (GLenum target, GLenum internalformat, GLuint buffer){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto internalformat_vkgl = OpenGL::Utils::get_internal_format_for_gl_enum(   internalformat);

    vkgl_assert(   target == GL_TEXTURE_BUFFER);

    in_context_p->tex_buffer(internalformat_vkgl,
                                  buffer);

}

void OpenGL::vkglPrimitiveRestartIndex (GLuint index){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->set_primitive_restart_index(   index);

}

void OpenGL::vkglCopyBufferSubData (GLenum readTarget, GLenum writeTarget, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto read_target_vkgl  = OpenGL::Utils::get_buffer_target_for_gl_enum(   readTarget);
    const auto write_target_vkgl = OpenGL::Utils::get_buffer_target_for_gl_enum(   writeTarget);

    in_context_p->copy_buffer_sub_data(read_target_vkgl,
                                         write_target_vkgl,
                                            readOffset,
                                            writeOffset,
                                            size);

}

void OpenGL::vkglGetUniformIndices (GLuint program, GLsizei uniformCount, const GLchar *const*uniformNames, GLuint *uniformIndices){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->get_uniform_indices(   program,
                                           uniformCount,
                                           uniformNames        ,
                                            uniformIndices    );

}

void OpenGL::vkglGetActiveUniformsiv (GLuint program, GLsizei uniformCount, const GLuint *uniformIndices, GLenum pname, GLint *params){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto pname_vkgl = OpenGL::Utils::get_uniform_property_for_gl_enum(   pname);

    in_context_p->get_active_uniforms(   program,
                                           uniformCount,
                                           uniformIndices    ,
                                        pname_vkgl,
                                            params    );

}

void OpenGL::vkglGetActiveUniformName (GLuint program, GLuint uniformIndex, GLsizei bufSize, GLsizei *length, GLchar *uniformName){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->get_active_uniform_name(   program,
                                               uniformIndex,
                                               bufSize,
                                                  length    ,
                                                uniformName    );

}

GLuint OpenGL::vkglGetUniformBlockIndex (GLuint program, const GLchar *uniformBlockName){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    return in_context_p->get_uniform_block_index(   program,
                                                      uniformBlockName);

}

void OpenGL::vkglGetActiveUniformBlockiv (GLuint program, GLuint uniformBlockIndex, GLenum pname, GLint *params){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto pname_vkgl = OpenGL::Utils::get_uniform_block_property_for_gl_enum(   pname);

    in_context_p->get_active_uniform_block_property(   program,
                                                         uniformBlockIndex,
                                                      pname_vkgl,
                                                      OpenGL::GetSetArgumentType::Int,
                                                          params    );

}

void OpenGL::vkglGetActiveUniformBlockName (GLuint program, GLuint uniformBlockIndex, GLsizei bufSize, GLsizei *length, GLchar *uniformBlockName){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->get_active_uniform_block_name(   program,
                                                     uniformBlockIndex,
                                                     bufSize    ,
                                                        length    ,
                                                      uniformBlockName    );

}

void OpenGL::vkglUniformBlockBinding (GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->set_uniform_block_binding(   program,
                                                 uniformBlockIndex,
                                                 uniformBlockBinding);

}




// GL_VERSION_3_2
void OpenGL::vkglDrawElementsBaseVertex (GLenum mode, GLsizei count, GLenum type, const void *indices, GLint basevertex){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto mode_vkgl = OpenGL::Utils::get_draw_call_mode_for_gl_enum      (   mode);
    const auto type_vkgl = OpenGL::Utils::get_draw_call_index_type_for_gl_enum(   type);

    in_context_p->draw_elements_base_vertex(mode_vkgl,
                                                count,
                                             type_vkgl,
                                                indices,
                                                basevertex);

}

void OpenGL::vkglDrawRangeElementsBaseVertex (GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void *indices, GLint basevertex){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto mode_vkgl = OpenGL::Utils::get_draw_call_mode_for_gl_enum      (   mode);
    const auto type_vkgl = OpenGL::Utils::get_draw_call_index_type_for_gl_enum(   type);

    in_context_p->draw_range_elements_base_vertex(mode_vkgl,
                                                       start,
                                                       end,
                                                       count,
                                                    type_vkgl,
                                                       indices,
                                                       basevertex);

}

void OpenGL::vkglDrawElementsInstancedBaseVertex (GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei instancecount, GLint basevertex){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto mode_vkgl = OpenGL::Utils::get_draw_call_mode_for_gl_enum      (   mode);
    const auto type_vkgl = OpenGL::Utils::get_draw_call_index_type_for_gl_enum(   type);

    in_context_p->draw_elements_instanced_base_vertex(mode_vkgl,
                                                           count,
                                                        type_vkgl,
                                                           indices    ,
                                                           instancecount,
                                                           basevertex);

}

void OpenGL::vkglMultiDrawElementsBaseVertex (GLenum mode, const GLsizei *count, GLenum type, const void *const*indices, GLsizei drawcount, const GLint *basevertex){

    GET_CONTEXT(in_context_p)

    const auto mode_vkgl = OpenGL::Utils::get_draw_call_mode_for_gl_enum      (   mode);
    const auto type_vkgl = OpenGL::Utils::get_draw_call_index_type_for_gl_enum(   type);

    in_context_p->multi_draw_elements_base_vertex(mode_vkgl,
                                                       count    ,
                                                    type_vkgl,
                                                       indices    ,
                                                       drawcount,
                                                       basevertex    );

}

void OpenGL::vkglProvokingVertex (GLenum mode){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto mode_vkgl = OpenGL::Utils::get_provoking_vertex_convention_for_gl_enum(   mode);

    in_context_p->set_provoking_vertex(mode_vkgl);

}

GLsync OpenGL::vkglFenceSync (GLenum condition, GLbitfield flags){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto condition_vkgl = OpenGL::Utils::get_sync_condition_for_gl_enum(   condition);

    vkgl_assert(   flags == 0);

    return in_context_p->fence_sync(condition_vkgl);

}

GLboolean OpenGL::vkglIsSync (GLsync sync){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    return in_context_p->is_sync(   sync) ? GL_TRUE : GL_FALSE;

}

void OpenGL::vkglDeleteSync (GLsync sync){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->delete_sync(   sync);

}

GLenum OpenGL::vkglClientWaitSync (GLsync sync, GLbitfield flags, GLuint64 timeout){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto flags_vkgl = OpenGL::Utils::get_wait_sync_bits_for_gl_enum(   flags);
    const auto result     = in_context_p->client_wait_sync             (   sync,
                                                                          flags_vkgl,
                                                                             timeout);

    return OpenGL::Utils::get_gl_enum_for_wait_result(result);

}

void OpenGL::vkglWaitSync (GLsync sync, GLbitfield flags, GLuint64 timeout){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    vkgl_assert(   flags == 0);

    in_context_p->wait_sync(   sync,
                                 timeout);

}

void OpenGL::vkglGetInteger64v (GLenum pname, GLint64 *data){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto pname_vkgl = OpenGL::Utils::get_context_property_for_gl_enum(   pname);

    in_context_p->get_parameter(pname_vkgl,
                                  OpenGL::GetSetArgumentType::Int64,
                                      data    );

}

void OpenGL::vkglGetSynciv (GLsync sync, GLenum pname, GLsizei bufSize, GLsizei *length, GLint *values){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto pname_vkgl = OpenGL::Utils::get_sync_property_for_gl_enum(   pname);

    in_context_p->get_sync_property(   sync,
                                         pname,
                                      OpenGL::GetSetArgumentType::Int,
                                         bufSize,
                                            length    ,
                                          values    );

}

void OpenGL::vkglGetInteger64i_v (GLenum target, GLuint index, GLint64 *data){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto target_vkgl = OpenGL::Utils::get_context_property_for_gl_enum(   target);

    in_context_p->get_parameter_indexed(target_vkgl,
                                          OpenGL::GetSetArgumentType::Int64,
                                             index,
                                              data    );

}

void OpenGL::vkglGetBufferParameteri64v (GLenum target, GLenum pname, GLint64 *params){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto pname_vkgl  = OpenGL::Utils::get_buffer_property_for_gl_enum(   pname);
    const auto target_vkgl = OpenGL::Utils::get_buffer_target_for_gl_enum  (   target);

    in_context_p->get_buffer_property(target_vkgl,
                                        pname_vkgl,
                                        OpenGL::GetSetArgumentType::Int64,
                                        1,
                                            params    );

}

void OpenGL::vkglFramebufferTexture (GLenum target, GLenum attachment, GLuint texture, GLint level){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto attachment_vkgl = OpenGL::Utils::get_framebuffer_attachment_point_for_gl_enum(   attachment);
    const auto target_vkgl     = OpenGL::Utils::get_framebuffer_target_for_gl_enum          (   target);

    in_context_p->framebuffer_texture(target_vkgl,
                                        attachment_vkgl,
                                           texture,
                                           level);

}

void OpenGL::vkglTexImage2DMultisample (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto internalformat_vkgl = OpenGL::Utils::get_internal_format_for_gl_enum(   internalformat);
    const auto target_vkgl         = OpenGL::Utils::get_texture_target_for_gl_enum (   target);

    in_context_p->tex_image_2d_multisample(target_vkgl,
                                                samples,
                                             internalformat_vkgl,
                                                width,
                                                height,
                                             (   fixedsamplelocations == GL_TRUE) );

}

void OpenGL::vkglTexImage3DMultisample (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    const auto internalformat_vkgl = OpenGL::Utils::get_internal_format_for_gl_enum(   internalformat);
    const auto target_vkgl         = OpenGL::Utils::get_texture_target_for_gl_enum (   target);

    in_context_p->tex_image_3d_multisample(target_vkgl,
                                                samples,
                                             internalformat_vkgl,
                                                width,
                                                height,
                                                depth,
                                             (   fixedsamplelocations == GL_TRUE) );

}

void OpenGL::vkglGetMultisamplefv (GLenum pname, GLuint index, GLfloat *val){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    vkgl_assert(   pname == GL_SAMPLE_POSITION);

    in_context_p->get_sample_position(   index,
                                            val    );

}

void OpenGL::vkglSampleMaski (GLuint maskNumber, GLbitfield mask){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

    in_context_p->set_sample_mask_indexed(   maskNumber,
                                               mask);

}



/*
// GL_VERSION_3_3
void OpenGL::vkglBindFragDataLocationIndexed (GLuint program, GLuint colorNumber, GLuint index, const GLchar *name){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

GLint OpenGL::vkglGetFragDataIndex (GLuint program, const GLchar *name){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglGenSamplers (GLsizei count, GLuint *samplers){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglDeleteSamplers (GLsizei count, const GLuint *samplers){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

GLboolean OpenGL::vkglIsSampler (GLuint sampler){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglBindSampler (GLuint unit, GLuint sampler){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglSamplerParameteri (GLuint sampler, GLenum pname, GLint param){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglSamplerParameteriv (GLuint sampler, GLenum pname, const GLint *param){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglSamplerParameterf (GLuint sampler, GLenum pname, GLfloat param){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglSamplerParameterfv (GLuint sampler, GLenum pname, const GLfloat *param){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglSamplerParameterIiv (GLuint sampler, GLenum pname, const GLint *param){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglSamplerParameterIuiv (GLuint sampler, GLenum pname, const GLuint *param){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglGetSamplerParameteriv (GLuint sampler, GLenum pname, GLint *params){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglGetSamplerParameterIiv (GLuint sampler, GLenum pname, GLint *params){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglGetSamplerParameterfv (GLuint sampler, GLenum pname, GLfloat *params){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglGetSamplerParameterIuiv (GLuint sampler, GLenum pname, GLuint *params){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglQueryCounter (GLuint id, GLenum target){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglGetQueryObjecti64v (GLuint id, GLenum pname, GLint64 *params){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglGetQueryObjectui64v (GLuint id, GLenum pname, GLuint64 *params){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglVertexAttribDivisor (GLuint index, GLuint divisor){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglVertexAttribP1ui (GLuint index, GLenum type, GLboolean normalized, GLuint value){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglVertexAttribP1uiv (GLuint index, GLenum type, GLboolean normalized, const GLuint *value){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglVertexAttribP2ui (GLuint index, GLenum type, GLboolean normalized, GLuint value){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglVertexAttribP2uiv (GLuint index, GLenum type, GLboolean normalized, const GLuint *value){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglVertexAttribP3ui (GLuint index, GLenum type, GLboolean normalized, GLuint value){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglVertexAttribP3uiv (GLuint index, GLenum type, GLboolean normalized, const GLuint *value){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglVertexAttribP4ui (GLuint index, GLenum type, GLboolean normalized, GLuint value){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglVertexAttribP4uiv (GLuint index, GLenum type, GLboolean normalized, const GLuint *value){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}




// GL_VERSION_4_0
void OpenGL::vkglMinSampleShading (GLfloat value){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglBlendEquationi (GLuint buf, GLenum mode){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglBlendEquationSeparatei (GLuint buf, GLenum modeRGB, GLenum modeAlpha){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglBlendFunci (GLuint buf, GLenum src, GLenum dst){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglBlendFuncSeparatei (GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglDrawArraysIndirect (GLenum mode, const void *indirect){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglDrawElementsIndirect (GLenum mode, GLenum type, const void *indirect){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglUniform1d (GLint location, GLdouble x){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglUniform2d (GLint location, GLdouble x, GLdouble y){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglUniform3d (GLint location, GLdouble x, GLdouble y, GLdouble z){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglUniform4d (GLint location, GLdouble x, GLdouble y, GLdouble z, GLdouble w){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglUniform1dv (GLint location, GLsizei count, const GLdouble *value){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglUniform2dv (GLint location, GLsizei count, const GLdouble *value){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglUniform3dv (GLint location, GLsizei count, const GLdouble *value){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglUniform4dv (GLint location, GLsizei count, const GLdouble *value){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglUniformMatrix2dv (GLint location, GLsizei count, GLboolean transpose, const GLdouble *value){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglUniformMatrix3dv (GLint location, GLsizei count, GLboolean transpose, const GLdouble *value){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglUniformMatrix4dv (GLint location, GLsizei count, GLboolean transpose, const GLdouble *value){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglUniformMatrix2x3dv (GLint location, GLsizei count, GLboolean transpose, const GLdouble *value){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglUniformMatrix2x4dv (GLint location, GLsizei count, GLboolean transpose, const GLdouble *value){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglUniformMatrix3x2dv (GLint location, GLsizei count, GLboolean transpose, const GLdouble *value){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglUniformMatrix3x4dv (GLint location, GLsizei count, GLboolean transpose, const GLdouble *value){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglUniformMatrix4x2dv (GLint location, GLsizei count, GLboolean transpose, const GLdouble *value){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglUniformMatrix4x3dv (GLint location, GLsizei count, GLboolean transpose, const GLdouble *value){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglGetUniformdv (GLuint program, GLint location, GLdouble *params){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

GLint OpenGL::vkglGetSubroutineUniformLocation (GLuint program, GLenum shadertype, const GLchar *name){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

GLuint FUNC_CONTEXT( _GetSubroutineIndex (GLuint program, GLenum shadertype, const GLchar *name){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglGetActiveSubroutineUniformiv (GLuint program, GLenum shadertype, GLuint index, GLenum pname, GLint *values){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglGetActiveSubroutineUniformName (GLuint program, GLenum shadertype, GLuint index, GLsizei bufsize, GLsizei *length, GLchar *name){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglGetActiveSubroutineName (GLuint program, GLenum shadertype, GLuint index, GLsizei bufsize, GLsizei *length, GLchar *name){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglUniformSubroutinesuiv (GLenum shadertype, GLsizei count, const GLuint *indices){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglGetUniformSubroutineuiv (GLenum shadertype, GLint location, GLuint *params){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglGetProgramStageiv (GLuint program, GLenum shadertype, GLenum pname, GLint *values){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglPatchParameteri (GLenum pname, GLint value){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglPatchParameterfv (GLenum pname, const GLfloat *values){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglBindTransformFeedback (GLenum target, GLuint id){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglDeleteTransformFeedbacks (GLsizei n, const GLuint *ids){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglGenTransformFeedbacks (GLsizei n, GLuint *ids){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

GLboolean OpenGL::vkglIsTransformFeedback (GLuint id){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglPauseTransformFeedback (void){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglResumeTransformFeedback (void){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglDrawTransformFeedback (GLenum mode, GLuint id){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglDrawTransformFeedbackStream (GLenum mode, GLuint id, GLuint stream){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglBeginQueryIndexed (GLenum target, GLuint index, GLuint id){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglEndQueryIndexed (GLenum target, GLuint index){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglGetQueryIndexediv (GLenum target, GLuint index, GLenum pname, GLint *params){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}




// GL_VERSION_4_1
void OpenGL::vkglReleaseShaderCompiler (void){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglShaderBinary (GLsizei count, const GLuint *shaders, GLenum binaryformat, const void *binary, GLsizei length){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglGetShaderPrecisionFormat (GLenum shadertype, GLenum precisiontype, GLint *range, GLint *precision){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglDepthRangef (GLfloat n, GLfloat f){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglClearDepthf (GLfloat d){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglGetProgramBinary (GLuint program, GLsizei bufSize, GLsizei *length, GLenum *binaryFormat, void *binary){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglProgramBinary (GLuint program, GLenum binaryFormat, const void *binary, GLsizei length){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglProgramParameteri (GLuint program, GLenum pname, GLint value){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglUseProgramStages (GLuint pipeline, GLbitfield stages, GLuint program){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglActiveShaderProgram (GLuint pipeline, GLuint program){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

GLuint OpenGL::vkglCreateShaderProgramv (GLenum type, GLsizei count, const GLchar *const*strings){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglBindProgramPipeline (GLuint pipeline){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglDeleteProgramPipelines (GLsizei n, const GLuint *pipelines){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglGenProgramPipelines (GLsizei n, GLuint *pipelines){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

GLboolean OpenGL::vkglIsProgramPipeline (GLuint pipeline){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglGetProgramPipelineiv (GLuint pipeline, GLenum pname, GLint *params){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglProgramUniform1i (GLuint program, GLint location, GLint v0){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglProgramUniform1iv (GLuint program, GLint location, GLsizei count, const GLint *value){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglProgramUniform1f (GLuint program, GLint location, GLfloat v0){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglProgramUniform1fv (GLuint program, GLint location, GLsizei count, const GLfloat *value){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglProgramUniform1d (GLuint program, GLint location, GLdouble v0){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglProgramUniform1dv (GLuint program, GLint location, GLsizei count, const GLdouble *value){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglProgramUniform1ui (GLuint program, GLint location, GLuint v0){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglProgramUniform1uiv (GLuint program, GLint location, GLsizei count, const GLuint *value){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglProgramUniform2i (GLuint program, GLint location, GLint v0, GLint v1){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglProgramUniform2iv (GLuint program, GLint location, GLsizei count, const GLint *value){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglProgramUniform2f (GLuint program, GLint location, GLfloat v0, GLfloat v1){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglProgramUniform2fv (GLuint program, GLint location, GLsizei count, const GLfloat *value){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglProgramUniform2d (GLuint program, GLint location, GLdouble v0, GLdouble v1){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglProgramUniform2dv (GLuint program, GLint location, GLsizei count, const GLdouble *value){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglProgramUniform2ui (GLuint program, GLint location, GLuint v0, GLuint v1){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglProgramUniform2uiv (GLuint program, GLint location, GLsizei count, const GLuint *value){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglProgramUniform3i (GLuint program, GLint location, GLint v0, GLint v1, GLint v2){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglProgramUniform3iv (GLuint program, GLint location, GLsizei count, const GLint *value){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglProgramUniform3f (GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglProgramUniform3fv (GLuint program, GLint location, GLsizei count, const GLfloat *value){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglProgramUniform3d (GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglProgramUniform3dv (GLuint program, GLint location, GLsizei count, const GLdouble *value){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglProgramUniform3ui (GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglProgramUniform3uiv (GLuint program, GLint location, GLsizei count, const GLuint *value){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglProgramUniform4i (GLuint program, GLint location, GLint v0, GLint v1, GLint v2, GLint v3){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglProgramUniform4iv (GLuint program, GLint location, GLsizei count, const GLint *value){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglProgramUniform4f (GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglProgramUniform4fv (GLuint program, GLint location, GLsizei count, const GLfloat *value){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglProgramUniform4d (GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2, GLdouble v3){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglProgramUniform4dv (GLuint program, GLint location, GLsizei count, const GLdouble *value){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglProgramUniform4ui (GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglProgramUniform4uiv (GLuint program, GLint location, GLsizei count, const GLuint *value){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglProgramUniformMatrix2fv (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglProgramUniformMatrix3fv (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglProgramUniformMatrix4fv (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglProgramUniformMatrix2dv (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglProgramUniformMatrix3dv (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglProgramUniformMatrix4dv (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglProgramUniformMatrix2x3fv (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglProgramUniformMatrix3x2fv (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglProgramUniformMatrix2x4fv (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglProgramUniformMatrix4x2fv (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglProgramUniformMatrix3x4fv (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglProgramUniformMatrix4x3fv (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglProgramUniformMatrix2x3dv (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglProgramUniformMatrix3x2dv (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglProgramUniformMatrix2x4dv (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglProgramUniformMatrix4x2dv (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglProgramUniformMatrix3x4dv (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglProgramUniformMatrix4x3dv (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglValidateProgramPipeline (GLuint pipeline){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglGetProgramPipelineInfoLog (GLuint pipeline, GLsizei bufSize, GLsizei *length, GLchar *infoLog){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglVertexAttribL1d (GLuint index, GLdouble x){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglVertexAttribL2d (GLuint index, GLdouble x, GLdouble y){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglVertexAttribL3d (GLuint index, GLdouble x, GLdouble y, GLdouble z){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglVertexAttribL4d (GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglVertexAttribL1dv (GLuint index, const GLdouble *v){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglVertexAttribL2dv (GLuint index, const GLdouble *v){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglVertexAttribL3dv (GLuint index, const GLdouble *v){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglVertexAttribL4dv (GLuint index, const GLdouble *v){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglVertexAttribLPointer (GLuint index, GLint size, GLenum type, GLsizei stride, const void *pointer){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglGetVertexAttribLdv (GLuint index, GLenum pname, GLdouble *params){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglViewportArrayv (GLuint first, GLsizei count, const GLfloat *v){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglViewportIndexedf (GLuint index, GLfloat x, GLfloat y, GLfloat w, GLfloat h){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglViewportIndexedfv (GLuint index, const GLfloat *v){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglScissorArrayv (GLuint first, GLsizei count, const GLint *v){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglScissorIndexed (GLuint index, GLint left, GLint bottom, GLsizei width, GLsizei height){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglScissorIndexedv (GLuint index, const GLint *v){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglDepthRangeArrayv (GLuint first, GLsizei count, const GLdouble *v){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglDepthRangeIndexed (GLuint index, GLdouble n, GLdouble f){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglGetFloati_v (GLenum target, GLuint index, GLfloat *data){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglGetDoublei_v (GLenum target, GLuint index, GLdouble *data){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}




// GL_VERSION_4_2
void OpenGL::vkglDrawArraysInstancedBaseInstance (GLenum mode, GLint first, GLsizei count, GLsizei instancecount, GLuint baseinstance){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglDrawElementsInstancedBaseInstance (GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei instancecount, GLuint baseinstance){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglDrawElementsInstancedBaseVertexBaseInstance (GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei instancecount, GLint basevertex, GLuint baseinstance){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglGetInternalformativ (GLenum target, GLenum internalformat, GLenum pname, GLsizei bufSize, GLint *params){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglGetActiveAtomicCounterBufferiv (GLuint program, GLuint bufferIndex, GLenum pname, GLint *params){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglBindImageTexture (GLuint unit, GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum access, GLenum format){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglMemoryBarrier (GLbitfield barriers){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglTexStorage1D (GLenum target, GLsizei levels, GLenum internalformat, GLsizei width){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglTexStorage2D (GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglTexStorage3D (GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglDrawTransformFeedbackInstanced (GLenum mode, GLuint id, GLsizei instancecount){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglDrawTransformFeedbackStreamInstanced (GLenum mode, GLuint id, GLuint stream, GLsizei instancecount){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}




// GL_VERSION_4_3
void OpenGL::vkglClearBufferData (GLenum target, GLenum internalformat, GLenum format, GLenum type, const void *data){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglClearBufferSubData (GLenum target, GLenum internalformat, GLintptr offset, GLsizeiptr size, GLenum format, GLenum type, const void *data){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglDispatchCompute (GLuint num_groups_x, GLuint num_groups_y, GLuint num_groups_z){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglDispatchComputeIndirect (GLintptr indirect){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglCopyImageSubData (GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei srcWidth, GLsizei srcHeight, GLsizei srcDepth){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglFramebufferParameteri (GLenum target, GLenum pname, GLint param){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglGetFramebufferParameteriv (GLenum target, GLenum pname, GLint *params){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglGetInternalformati64v (GLenum target, GLenum internalformat, GLenum pname, GLsizei bufSize, GLint64 *params){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglInvalidateTexSubImage (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglInvalidateTexImage (GLuint texture, GLint level){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglInvalidateBufferSubData (GLuint buffer, GLintptr offset, GLsizeiptr length){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglInvalidateBufferData (GLuint buffer){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglInvalidateFramebuffer (GLenum target, GLsizei numAttachments, const GLenum *attachments){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglInvalidateSubFramebuffer (GLenum target, GLsizei numAttachments, const GLenum *attachments, GLint x, GLint y, GLsizei width, GLsizei height){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglMultiDrawArraysIndirect (GLenum mode, const void *indirect, GLsizei drawcount, GLsizei stride){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglMultiDrawElementsIndirect (GLenum mode, GLenum type, const void *indirect, GLsizei drawcount, GLsizei stride){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglGetProgramInterfaceiv (GLuint program, GLenum programInterface, GLenum pname, GLint *params){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

GLuint OpenGL::vkglGetProgramResourceIndex (GLuint program, GLenum programInterface, const GLchar *name){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglGetProgramResourceName (GLuint program, GLenum programInterface, GLuint index, GLsizei bufSize, GLsizei *length, GLchar *name){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglGetProgramResourceiv (GLuint program, GLenum programInterface, GLuint index, GLsizei propCount, const GLenum *props, GLsizei bufSize, GLsizei *length, GLint *params){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

GLint OpenGL::vkglGetProgramResourceLocation (GLuint program, GLenum programInterface, const GLchar *name){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

GLint OpenGL::vkglGetProgramResourceLocationIndex (GLuint program, GLenum programInterface, const GLchar *name){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglShaderStorageBlockBinding (GLuint program, GLuint storageBlockIndex, GLuint storageBlockBinding){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglTexBufferRange (GLenum target, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglTexStorage2DMultisample (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglTexStorage3DMultisample (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglTextureView (GLuint texture, GLenum target, GLuint origtexture, GLenum internalformat, GLuint minlevel, GLuint numlevels, GLuint minlayer, GLuint numlayers){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglBindVertexBuffer (GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglVertexAttribFormat (GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglVertexAttribIFormat (GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglVertexAttribLFormat (GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglVertexAttribBinding (GLuint attribindex, GLuint bindingindex){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglVertexBindingDivisor (GLuint bindingindex, GLuint divisor){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglDebugMessageControl (GLenum source, GLenum type, GLenum severity, GLsizei count, const GLuint *ids, GLboolean enabled){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglDebugMessageInsert (GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *buf){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglDebugMessageCallback (GLDEBUGPROC callback, const void *userParam){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

GLuint OpenGL::vkglGetDebugMessageLog (GLuint count, GLsizei bufSize, GLenum *sources, GLenum *types, GLuint *ids, GLenum *severities, GLsizei *lengths, GLchar *messageLog){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglPushDebugGroup (GLenum source, GLuint id, GLsizei length, const GLchar *message){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglPopDebugGroup (void){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglObjectLabel (GLenum identifier, GLuint name, GLsizei length, const GLchar *label){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglGetObjectLabel (GLenum identifier, GLuint name, GLsizei bufSize, GLsizei *length, GLchar *label){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglObjectPtrLabel (const void *ptr, GLsizei length, const GLchar *label){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglGetObjectPtrLabel (const void *ptr, GLsizei bufSize, GLsizei *length, GLchar *label){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}




// GL_VERSION_4_4
void OpenGL::vkglBufferStorage (GLenum target, GLsizeiptr size, const void *data, GLbitfield flags){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglClearTexImage (GLuint texture, GLint level, GLenum format, GLenum type, const void *data){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglClearTexSubImage (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void *data){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglBindBuffersBase (GLenum target, GLuint first, GLsizei count, const GLuint *buffers){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglBindBuffersRange (GLenum target, GLuint first, GLsizei count, const GLuint *buffers, const GLintptr *offsets, const GLsizeiptr *sizes){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglBindTextures (GLuint first, GLsizei count, const GLuint *textures){

FUNC_CONTEXT( _glBindTextures (first, count, textures) )
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglBindSamplers (GLuint first, GLsizei count, const GLuint *samplers){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglBindImageTextures (GLuint first, GLsizei count, const GLuint *textures){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglBindVertexBuffers (GLuint first, GLsizei count, const GLuint *buffers, const GLintptr *offsets, const GLsizei *strides){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}




// GL_VERSION_4_5
void OpenGL::vkglClipControl (GLenum origin, GLenum depth){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglCreateTransformFeedbacks (GLsizei n, GLuint *ids){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglTransformFeedbackBufferBase (GLuint xfb, GLuint index, GLuint buffer){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglTransformFeedbackBufferRange (GLuint xfb, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglGetTransformFeedbackiv (GLuint xfb, GLenum pname, GLint *param){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglGetTransformFeedbacki_v (GLuint xfb, GLenum pname, GLuint index, GLint *param){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglGetTransformFeedbacki64_v (GLuint xfb, GLenum pname, GLuint index, GLint64 *param){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglCreateBuffers (GLsizei n, GLuint *buffers){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglNamedBufferStorage (GLuint buffer, GLsizeiptr size, const void *data, GLbitfield flags){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglNamedBufferData (GLuint buffer, GLsizeiptr size, const void *data, GLenum usage){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglNamedBufferSubData (GLuint buffer, GLintptr offset, GLsizeiptr size, const void *data){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglCopyNamedBufferSubData (GLuint readBuffer, GLuint writeBuffer, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglClearNamedBufferData (GLuint buffer, GLenum internalformat, GLenum format, GLenum type, const void *data){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglClearNamedBufferSubData (GLuint buffer, GLenum internalformat, GLintptr offset, GLsizeiptr size, GLenum format, GLenum type, const void *data){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void *OpenGL::vkglMapNamedBuffer (GLuint buffer, GLenum access){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void *OpenGL::vkglMapNamedBufferRange (GLuint buffer, GLintptr offset, GLsizeiptr length, GLbitfield access){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

GLboolean OpenGL::vkglUnmapNamedBuffer (GLuint buffer){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglFlushMappedNamedBufferRange (GLuint buffer, GLintptr offset, GLsizeiptr length){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglGetNamedBufferParameteriv (GLuint buffer, GLenum pname, GLint *params){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglGetNamedBufferParameteri64v (GLuint buffer, GLenum pname, GLint64 *params){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglGetNamedBufferPointerv (GLuint buffer, GLenum pname, void **params){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglGetNamedBufferSubData (GLuint buffer, GLintptr offset, GLsizeiptr size, void *data){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglCreateFramebuffers (GLsizei n, GLuint *framebuffers){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglNamedFramebufferRenderbuffer (GLuint framebuffer, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglNamedFramebufferParameteri (GLuint framebuffer, GLenum pname, GLint param){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglNamedFramebufferTexture (GLuint framebuffer, GLenum attachment, GLuint texture, GLint level){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglNamedFramebufferTextureLayer (GLuint framebuffer, GLenum attachment, GLuint texture, GLint level, GLint layer){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglNamedFramebufferDrawBuffer (GLuint framebuffer, GLenum buf){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglNamedFramebufferDrawBuffers (GLuint framebuffer, GLsizei n, const GLenum *bufs){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglNamedFramebufferReadBuffer (GLuint framebuffer, GLenum src){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglInvalidateNamedFramebufferData (GLuint framebuffer, GLsizei numAttachments, const GLenum *attachments){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglInvalidateNamedFramebufferSubData (GLuint framebuffer, GLsizei numAttachments, const GLenum *attachments, GLint x, GLint y, GLsizei width, GLsizei height){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglClearNamedFramebufferiv (GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLint *value){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglClearNamedFramebufferuiv (GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLuint *value){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglClearNamedFramebufferfv (GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLfloat *value){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglClearNamedFramebufferfi (GLuint framebuffer, GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglBlitNamedFramebuffer (GLuint readFramebuffer, GLuint drawFramebuffer, GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

GLenum OpenGL::vkglCheckNamedFramebufferStatus (GLuint framebuffer, GLenum target){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglGetNamedFramebufferParameteriv (GLuint framebuffer, GLenum pname, GLint *param){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglGetNamedFramebufferAttachmentParameteriv (GLuint framebuffer, GLenum attachment, GLenum pname, GLint *params){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglCreateRenderbuffers (GLsizei n, GLuint *renderbuffers){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglNamedRenderbufferStorage (GLuint renderbuffer, GLenum internalformat, GLsizei width, GLsizei height){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglNamedRenderbufferStorageMultisample (GLuint renderbuffer, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglGetNamedRenderbufferParameteriv (GLuint renderbuffer, GLenum pname, GLint *params){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglCreateTextures (GLenum target, GLsizei n, GLuint *textures){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglTextureBuffer (GLuint texture, GLenum internalformat, GLuint buffer){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglTextureBufferRange (GLuint texture, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglTextureStorage1D (GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglTextureStorage2D (GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglTextureStorage3D (GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglTextureStorage2DMultisample (GLuint texture, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglTextureStorage3DMultisample (GLuint texture, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglTextureSubImage1D (GLuint texture, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void *pixels){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglTextureSubImage2D (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void *pixels){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglTextureSubImage3D (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void *pixels){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglCompressedTextureSubImage1D (GLuint texture, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void *data){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglCompressedTextureSubImage2D (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void *data){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglCompressedTextureSubImage3D (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void *data){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglCopyTextureSubImage1D (GLuint texture, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglCopyTextureSubImage2D (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglCopyTextureSubImage3D (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglTextureParameterf (GLuint texture, GLenum pname, GLfloat param){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglTextureParameterfv (GLuint texture, GLenum pname, const GLfloat *param){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglTextureParameteri (GLuint texture, GLenum pname, GLint param){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglTextureParameterIiv (GLuint texture, GLenum pname, const GLint *params){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglTextureParameterIuiv (GLuint texture, GLenum pname, const GLuint *params){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglTextureParameteriv (GLuint texture, GLenum pname, const GLint *param){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglGenerateTextureMipmap (GLuint texture){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglBindTextureUnit (GLuint unit, GLuint texture){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglGetTextureImage (GLuint texture, GLint level, GLenum format, GLenum type, GLsizei bufSize, void *pixels){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglGetCompressedTextureImage (GLuint texture, GLint level, GLsizei bufSize, void *pixels){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglGetTextureLevelParameterfv (GLuint texture, GLint level, GLenum pname, GLfloat *params){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglGetTextureLevelParameteriv (GLuint texture, GLint level, GLenum pname, GLint *params){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglGetTextureParameterfv (GLuint texture, GLenum pname, GLfloat *params){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglGetTextureParameterIiv (GLuint texture, GLenum pname, GLint *params){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglGetTextureParameterIuiv (GLuint texture, GLenum pname, GLuint *params){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglGetTextureParameteriv (GLuint texture, GLenum pname, GLint *params){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglCreateVertexArrays (GLsizei n, GLuint *arrays){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglDisableVertexArrayAttrib (GLuint vaobj, GLuint index){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglEnableVertexArrayAttrib (GLuint vaobj, GLuint index){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglVertexArrayElementBuffer (GLuint vaobj, GLuint buffer){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglVertexArrayVertexBuffer (GLuint vaobj, GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglVertexArrayVertexBuffers (GLuint vaobj, GLuint first, GLsizei count, const GLuint *buffers, const GLintptr *offsets, const GLsizei *strides){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglVertexArrayAttribBinding (GLuint vaobj, GLuint attribindex, GLuint bindingindex){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglVertexArrayAttribFormat (GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglVertexArrayAttribIFormat (GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglVertexArrayAttribLFormat (GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglVertexArrayBindingDivisor (GLuint vaobj, GLuint bindingindex, GLuint divisor){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglGetVertexArrayiv (GLuint vaobj, GLenum pname, GLint *param){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglGetVertexArrayIndexediv (GLuint vaobj, GLuint index, GLenum pname, GLint *param){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglGetVertexArrayIndexed64iv (GLuint vaobj, GLuint index, GLenum pname, GLint64 *param){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglCreateSamplers (GLsizei n, GLuint *samplers){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglCreateProgramPipelines (GLsizei n, GLuint *pipelines){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglCreateQueries (GLenum target, GLsizei n, GLuint *ids){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglGetQueryBufferObjecti64v (GLuint id, GLuint buffer, GLenum pname, GLintptr offset){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglGetQueryBufferObjectiv (GLuint id, GLuint buffer, GLenum pname, GLintptr offset){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglGetQueryBufferObjectui64v (GLuint id, GLuint buffer, GLenum pname, GLintptr offset){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglGetQueryBufferObjectuiv (GLuint id, GLuint buffer, GLenum pname, GLintptr offset){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglMemoryBarrierByRegion (GLbitfield barriers){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglGetTextureSubImage (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, GLsizei bufSize, void *pixels){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglGetCompressedTextureSubImage (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLsizei bufSize, void *pixels){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

GLenum OpenGL::vkglGetGraphicsResetStatus (void){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglGetnCompressedTexImage (GLenum target, GLint lod, GLsizei bufSize, void *pixels){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglGetnTexImage (GLenum target, GLint level, GLenum format, GLenum type, GLsizei bufSize, void *pixels){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglGetnUniformdv (GLuint program, GLint location, GLsizei bufSize, GLdouble *params){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglGetnUniformfv (GLuint program, GLint location, GLsizei bufSize, GLfloat *params){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglGetnUniformiv (GLuint program, GLint location, GLsizei bufSize, GLint *params){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglGetnUniformuiv (GLuint program, GLint location, GLsizei bufSize, GLuint *params){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglReadnPixels (GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLsizei bufSize, void *data){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglTextureBarrier (void){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}




// GL_VERSION_4_6
void OpenGL::vkglSpecializeShader (GLuint shader, const GLchar *pEntryPoint, GLuint numSpecializationConstants, const GLuint *pConstantIndex, const GLuint *pConstantValue){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglMultiDrawArraysIndirectCount (GLenum mode, const void *indirect, GLintptr drawcount, GLsizei maxdrawcount, GLsizei stride){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglMultiDrawElementsIndirectCount (GLenum mode, GLenum type, const void *indirect, GLintptr drawcount, GLsizei maxdrawcount, GLsizei stride){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}

void OpenGL::vkglPolygonOffsetClamp (GLfloat factor, GLfloat units, GLfloat clamp){
    FUN_ENTRY(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)



}
*/


