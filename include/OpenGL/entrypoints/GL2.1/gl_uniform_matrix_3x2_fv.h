/* VKGL (c) 2018 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef VKGL_GL_UNIFORM_MATRIX_3X2_FV_H
#define VKGL_GL_UNIFORM_MATRIX_3X2_FV_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void VKGL_APIENTRY vkglUniformMatrix3x2fv(GLint          location,
                                              GLsizei        count,
                                              GLboolean      transpose,
                                              const GLfloat* value);

    void vkglUniformMatrix3x2fv_with_validation(OpenGL::Context* in_context_ptr,
                                                const GLint&     in_location,
                                                const GLsizei&   in_count,
                                                const GLboolean& in_transpose,
                                                const GLfloat*   in_value_ptr);
}

#endif /* VKGL_GL_UNIFORM_MATRIX_3X2_FV_H */