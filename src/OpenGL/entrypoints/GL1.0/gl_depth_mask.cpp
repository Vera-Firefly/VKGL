#include "OpenGL/entrypoints/GL1.0/gl_depth_mask.h"
#include "OpenGL/globals.h"

static bool validate(VKGL::Context*   in_context_ptr,
                     const GLboolean& in_flag)
{
    bool result = false;

    // ..

    result = true;
end:
    return result;
}


VKGL_API void VKGL_APIENTRY glDepthMask(GLboolean flag)
{
    const auto dispatch_table_ptr = g_dispatch_table_ptr;

    dispatch_table_ptr->pGLDepthMask(dispatch_table_ptr->bound_context_ptr,
                                     flag);
}

void vkglDepthMask_with_validation(VKGL::Context*   in_context_ptr,
                                   const GLboolean& in_flag)
{
    if (validate(in_context_ptr,
                 in_flag) )
    {
        todo;
    }
}
