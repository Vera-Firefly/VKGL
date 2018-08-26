/* VKGL (c) 2018 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.5/gl_get_buffer_sub_data.h"
#include "OpenGL/context.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"

static bool validate(VKGL::Context*    in_context_ptr,
                     const GLenum&     in_target,
                     const GLintptr&   in_offset,
                     const GLsizeiptr& in_size,
                     void*             in_data)
{
    bool result = false;

    // ..

    result = true;
    return result;
}

void VKGL_APIENTRY vkglGetBufferSubData(GLenum     target,
                                        GLintptr   offset,
                                        GLsizeiptr size,
                                        void*      data)
{
    const auto& dispatch_table_ptr = OpenGL::g_dispatch_table_ptr;

    dispatch_table_ptr->pGLGetBufferSubData(dispatch_table_ptr->bound_context_ptr,
                                            target,
                                            offset,
                                            size,
                                            data);
}

void vkglGetBufferSubData_execute(VKGL::Context*    in_context_ptr,
                                  const GLenum&     in_target,
                                  const GLintptr&   in_offset,
                                  const GLsizeiptr& in_size,
                                  void*             in_data)
{
    const auto target_vkgl = VKGL::Utils::get_buffer_target_for_gl_enum(in_target);

    in_context_ptr->get_buffer_sub_data(target_vkgl,
                                        in_offset,
                                        in_size,
                                        in_data);
}

void vkglGetBufferSubData_with_validation(VKGL::Context*    in_context_ptr,
                                          const GLenum&     in_target,
                                          const GLintptr&   in_offset,
                                          const GLsizeiptr& in_size,
                                          void*             in_data)
{
    if (validate(in_context_ptr,
                 in_target,
                 in_offset,
                 in_size,
                 in_data) )
    {
        vkglGetBufferSubData_execute(in_context_ptr,
                                     in_target,
                                     in_offset,
                                     in_size,
                                     in_data);
    }
}
