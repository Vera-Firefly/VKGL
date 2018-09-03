/* VKGL (c) 2018 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef VKGL_GL_VERTEX_ATTRIB_1DV_H
#define VKGL_GL_VERTEX_ATTRIB_1DV_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void VKGL_APIENTRY vkglVertexAttrib1dv(GLuint          index,
                                           const GLdouble* v);

    void vkglVertexAttrib1dv_with_validation(OpenGL::Context* in_context_ptr,
                                             const GLuint&    in_index,
                                             const GLdouble*  in_v_ptr);
}

#endif /* VKGL_GL_VERTEX_ATTRIB_1DV_H */