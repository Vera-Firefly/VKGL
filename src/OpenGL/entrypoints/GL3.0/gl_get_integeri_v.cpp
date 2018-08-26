/* VKGL (c) 2018 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL3.0/gl_get_integeri_v.h"
#include "OpenGL/context.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"

static bool validate(VKGL::Context* in_context_ptr,
                     const GLenum&  in_target,
                     const GLuint&  in_index,
                     GLint*         out_data_ptr)
{
    bool result = false;

    // ..

    result = true;
    return result;
}


void VKGL_APIENTRY vkglGetIntegeri_v(GLenum target,
                                     GLuint index,
                                     GLint* data)
{
    const auto dispatch_table_ptr = OpenGL::g_dispatch_table_ptr;

    dispatch_table_ptr->pGLGetIntegeri_v(dispatch_table_ptr->bound_context_ptr,
                                         target,
                                         index,
                                         data);
}

void vkglGetIntegeri_v_execute(VKGL::Context* in_context_ptr,
                               const GLenum&  in_target,
                               const GLuint&  in_index,
                               GLint*         out_data_ptr)
{
    const auto target_vkgl = VKGL::Utils::get_context_property_for_gl_enum(in_target);

    in_context_ptr->get_parameter_indexed(target_vkgl,
                                          in_index,
                                          VKGL::GetSetArgumentType::Int,
                                          out_data_ptr);
}

void vkglGetIntegeri_v_with_validation(VKGL::Context* in_context_ptr,
                                       const GLenum&  in_target,
                                       const GLuint&  in_index,
                                       GLint*         out_data_ptr)
{
    if (validate(in_context_ptr,
                 in_target,
                 in_index,
                 out_data_ptr) )
    {
        vkglGetIntegeri_v_execute(in_context_ptr,
                                  in_target,
                                  in_index,
                                  out_data_ptr);
    }
}