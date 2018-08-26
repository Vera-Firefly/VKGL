/* VKGL (c) 2018 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.3/gl_compressed_tex_sub_image_3d.h"
#include "OpenGL/context.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"

static bool validate(VKGL::Context* in_context_ptr,
                     const GLenum&  in_target,
                     const GLint&   in_level,
                     const GLint&   in_xoffset,
                     const GLint&   in_yoffset,
                     const GLint&   in_zoffset,
                     const GLsizei& in_width,
                     const GLsizei& in_height,
                     const GLsizei& in_depth,
                     const GLenum&  in_format,
                     const GLsizei& in_image_size,
                     const void*    in_data)
{
    bool result = false;

    // ..

    result = true;
    return result;
}

void VKGL_APIENTRY vkglCompressedTexSubImage3D(GLenum      target,
                                               GLint       level,
                                               GLint       xoffset,
                                               GLint       yoffset,
                                               GLint       zoffset,
                                               GLsizei     width,
                                               GLsizei     height,
                                               GLsizei     depth,
                                               GLenum      format,
                                               GLsizei     imageSize,
                                               const void* data)
{
    const auto dispatch_table_ptr = OpenGL::g_dispatch_table_ptr;

    dispatch_table_ptr->pGLCompressedTexSubImage3D(dispatch_table_ptr->bound_context_ptr,
                                                   target,
                                                   level,
                                                   xoffset,
                                                   yoffset,
                                                   zoffset,
                                                   width,
                                                   height,
                                                   depth,
                                                   format,
                                                   imageSize,
                                                   data);
}

void vkglCompressedTexSubImage3D_execute(VKGL::Context* in_context_ptr,
                                         const GLenum&  in_target,
                                         const GLint&   in_level,
                                         const GLint&   in_xoffset,
                                         const GLint&   in_yoffset,
                                         const GLint&   in_zoffset,
                                         const GLsizei& in_width,
                                         const GLsizei& in_height,
                                         const GLsizei& in_depth,
                                         const GLenum&  in_format,
                                         const GLsizei& in_image_size,
                                         const void*    in_data)
{
    const auto format_vkgl = VKGL::Utils::get_pixel_format_for_gl_enum  (in_format);
    const auto target_vkgl = VKGL::Utils::get_texture_target_for_gl_enum(in_target);

    in_context_ptr->compressed_tex_sub_image_3d(target_vkgl,
                                                in_level,
                                                in_xoffset,
                                                in_yoffset,
                                                in_zoffset,
                                                in_width,
                                                in_height,
                                                in_depth,
                                                format_vkgl,
                                                in_image_size,
                                                in_data);
}

void vkglCompressedTexSubImage3D_with_validation(VKGL::Context* in_context_ptr,
                                                 const GLenum&  in_target,
                                                 const GLint&   in_level,
                                                 const GLint&   in_xoffset,
                                                 const GLint&   in_yoffset,
                                                 const GLint&   in_zoffset,
                                                 const GLsizei& in_width,
                                                 const GLsizei& in_height,
                                                 const GLsizei& in_depth,
                                                 const GLenum&  in_format,
                                                 const GLsizei& in_image_size,
                                                 const void*    in_data)
{
    if (validate(in_context_ptr,
                 in_target,
                 in_level,
                 in_xoffset,
                 in_yoffset,
                 in_zoffset,
                 in_width,
                 in_height,
                 in_depth,
                 in_format,
                 in_image_size,
                 in_data) )
    {
        vkglCompressedTexSubImage3D_execute(in_context_ptr,
                                            in_target,
                                            in_level,
                                            in_xoffset,
                                            in_yoffset,
                                            in_zoffset,
                                            in_width,
                                            in_height,
                                            in_depth,
                                            in_format,
                                            in_image_size,
                                            in_data);
    }
}