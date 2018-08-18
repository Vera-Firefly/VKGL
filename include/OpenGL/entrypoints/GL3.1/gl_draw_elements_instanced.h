/* VKGL (c) 2018 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef VKGL_GL_DRAW_ELEMENTS_INSTANCED_H
#define VKGL_GL_DRAW_ELEMENTS_INSTANCED_H

#include "OpenGL/types.h"

VKGL_API void VKGL_APIENTRY glDrawElementsInstanced(GLenum      mode,
                                                    GLsizei     count,
                                                    GLenum      type,
                                                    const void* indices,
                                                    GLsizei     instancecount);

#endif /* VKGL_GL_DRAW_ELEMENTS_INSTANCED_H */