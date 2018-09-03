/* VKGL (c) 2018 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.3/gl_compressed_tex_image_2d.h"
#include "OpenGL/context.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"

static bool validate(OpenGL::Context* in_context_ptr,
                     const GLenum&    in_target,
                     const GLint&     in_level,
                     const GLenum&    in_internalformat,
                     const GLsizei&   in_width,
                     const GLsizei&   in_height,
                     const GLint&     in_border,
                     const GLsizei&   in_image_size,
                     const void*      in_data)
{
    bool result = false;

    // ..

    result = true;
    return result;
}

void VKGL_APIENTRY OpenGL::vkglCompressedTexImage2D(GLenum      target,
                                                    GLint       level,
                                                    GLenum      internalformat,
                                                    GLsizei     width,
                                                    GLsizei     height,
                                                    GLint       border,
                                                    GLsizei     imageSize,
                                                    const void* data)
{
    const auto dispatch_table_ptr = OpenGL::g_dispatch_table_ptr;

    dispatch_table_ptr->pGLCompressedTexImage2D(dispatch_table_ptr->bound_context_ptr,
                                                target,
                                                level,
                                                internalformat,
                                                width,
                                                height,
                                                border,
                                                imageSize,
                                                data);
}

static void vkglCompressedTexImage2D_execute(OpenGL::Context* in_context_ptr,
                                             const GLenum&    in_target,
                                             const GLint&     in_level,
                                             const GLenum&    in_internalformat,
                                             const GLsizei&   in_width,
                                             const GLsizei&   in_height,
                                             const GLint&     in_border,
                                             const GLsizei&   in_image_size,
                                             const void*      in_data)
{
    const auto internalformat_vkgl = OpenGL::Utils::get_internal_format_for_gl_enum(in_internalformat);
    const auto target_vkgl         = OpenGL::Utils::get_texture_target_for_gl_enum (in_target);

    in_context_ptr->compressed_tex_image_2d(target_vkgl,
                                            in_level,
                                            internalformat_vkgl,
                                            in_width,
                                            in_height,
                                            in_border,
                                            in_image_size,
                                            in_data);
}

void OpenGL::vkglCompressedTexImage2D_with_validation(OpenGL::Context* in_context_ptr,
                                                      const GLenum&    in_target,
                                                      const GLint&     in_level,
                                                      const GLenum&    in_internalformat,
                                                      const GLsizei&   in_width,
                                                      const GLsizei&   in_height,
                                                      const GLint&     in_border,
                                                      const GLsizei&   in_image_size,
                                                      const void*      in_data)
{
    if (validate(in_context_ptr,
                 in_target,
                 in_level,
                 in_internalformat,
                 in_width,
                 in_height,
                 in_border,
                 in_image_size,
                 in_data) )
    {
        vkglCompressedTexImage2D_execute(in_context_ptr,
                                         in_target,
                                         in_level,
                                         in_internalformat,
                                         in_width,
                                         in_height,
                                         in_border,
                                         in_image_size,
                                         in_data);
    }
}
