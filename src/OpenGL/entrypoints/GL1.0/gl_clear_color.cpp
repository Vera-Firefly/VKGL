#include "OpenGL/entrypoints/GL1.0/gl_clear_color.h"
#include "OpenGL/globals.h"

static bool validate(VKGL::Context* in_context_ptr,
                     const GLfloat& in_red,
                     const GLfloat& in_green,
                     const GLfloat& in_blue,
                     const GLfloat& in_alpha)
{
    bool result = false;

    // ..

    result = true;
end:
    return result;
}

VKGL_API void VKGL_APIENTRY glClearColor(GLfloat red,
                                         GLfloat green,
                                         GLfloat blue,
                                         GLfloat alpha)
{
    const auto dispatch_table_ptr = g_dispatch_table_ptr;

    dispatch_table_ptr->pGLClearColor(dispatch_table_ptr->bound_context_ptr,
                                      red,
                                      green,
                                      blue,
                                      alpha);
}

void vkglClearColor_with_validation(VKGL::Context* in_context_ptr,
                                    const GLfloat& in_red,
                                    const GLfloat& in_green,
                                    const GLfloat& in_blue,
                                    const GLfloat& in_alpha)
{
    if (validate(in_context_ptr,
                 in_red,
                 in_green,
                 in_blue,
                 in_alpha) )
    {
        todo;
    }
}