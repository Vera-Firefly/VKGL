/* VKGL (c) 2018 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.4/gl_blend_color.h"
#include "OpenGL/context.h"
#include "OpenGL/globals.h"

static bool validate(OpenGL::Context* in_context_ptr,
                     const GLfloat&   in_red,
                     const GLfloat&   in_green,
                     const GLfloat&   in_blue,
                     const GLfloat&   in_alpha)
{
    bool result = false;

    // ..

    result = true;
    return result;
}

void VKGL_APIENTRY OpenGL::vkglBlendColor(GLfloat red,
                                          GLfloat green,
                                          GLfloat blue,
                                          GLfloat alpha)
{
    const auto& dispatch_table_ptr = OpenGL::g_dispatch_table_ptr;

    dispatch_table_ptr->pGLBlendColor(dispatch_table_ptr->bound_context_ptr,
                                      red,
                                      green,
                                      blue,
                                      alpha);
}

static void vkglBlendColor_execute(OpenGL::Context* in_context_ptr,
                                   const GLfloat&   in_red,
                                   const GLfloat&   in_green,
                                   const GLfloat&   in_blue,
                                   const GLfloat&   in_alpha)
{
    in_context_ptr->set_blend_color(in_red,
                                    in_green,
                                    in_blue,
                                    in_alpha);
}

void OpenGL::vkglBlendColor_with_validation(OpenGL::Context* in_context_ptr,
                                            const GLfloat&   in_red,
                                            const GLfloat&   in_green,
                                            const GLfloat&   in_blue,
                                            const GLfloat&   in_alpha)
{
    if (validate(in_context_ptr,
                 in_red,
                 in_green,
                 in_blue,
                 in_alpha) )
    {
        vkglBlendColor_execute(in_context_ptr,
                               in_red,
                               in_green,
                               in_blue,
                               in_alpha);
    }
}
