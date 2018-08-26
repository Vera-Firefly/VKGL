/* VKGL (c) 2018 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.4/gl_multi_draw_elements.h"
#include "OpenGL/context.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"

static bool validate(VKGL::Context*     in_context_ptr,
                     const GLenum&      in_mode,
                     const GLsizei*     in_count_ptr,
                     const GLenum&      in_type,
                     const void* const* in_indices_ptr,
                     const GLsizei&     in_drawcount)
{
    bool result = false;

    // ..

    result = true;
    return result;
}

void VKGL_APIENTRY vkglMultiDrawElements(GLenum             mode,
                                         const GLsizei*     count,
                                         GLenum             type,
                                         const void* const* indices,
                                         GLsizei            drawcount)
{
    const auto dispatch_table_ptr = OpenGL::g_dispatch_table_ptr;

    dispatch_table_ptr->pGLMultiDrawElements(dispatch_table_ptr->bound_context_ptr,
                                             mode,
                                             count,
                                             type,
                                             indices,
                                             drawcount);
}

void vkglMultiDrawElements_execute(VKGL::Context*     in_context_ptr,
                                   const GLenum&      in_mode,
                                   const GLsizei*     in_count_ptr,
                                   const GLenum&      in_type,
                                   const void* const* in_indices_ptr,
                                   const GLsizei&     in_drawcount)
{
    const auto mode_vkgl = VKGL::Utils::get_draw_call_mode_for_gl_enum      (in_mode);
    const auto type_vkgl = VKGL::Utils::get_draw_call_index_type_for_gl_enum(in_type);

    in_context_ptr->multi_draw_elements(mode_vkgl,
                                        in_count_ptr,
                                        type_vkgl,
                                        in_indices_ptr,
                                        in_drawcount);
}

void vkglMultiDrawElements_with_validation(VKGL::Context*     in_context_ptr,
                                           const GLenum&      in_mode,
                                           const GLsizei*     in_count_ptr,
                                           const GLenum&      in_type,
                                           const void* const* in_indices_ptr,
                                           const GLsizei&     in_drawcount)
{
    if (validate(in_context_ptr,
                 in_mode,
                 in_count_ptr,
                 in_type,
                 in_indices_ptr,
                 in_drawcount) )
    {
        vkglMultiDrawElements_execute(in_context_ptr,
                                      in_mode,
                                      in_count_ptr,
                                      in_type,
                                      in_indices_ptr,
                                      in_drawcount);
    }
}
