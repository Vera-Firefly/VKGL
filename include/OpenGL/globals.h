/* VKGL (c) 2018 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef OPENGL_GLOBALS_H
#define OPENGL_GLOBALS_H

#include "Common/globals.h"
#include "OpenGL/types.h"

namespace OpenGL
{
    extern VKGL_THREADLOCAL const OpenGL::DispatchTable* g_dispatch_table_ptr;
}

#endif /* OPENGL_GLOBALS_H */