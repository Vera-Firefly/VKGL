/* VKGL (c) 2018 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/globals.h"

const VKGL_THREADLOCAL OpenGL::DispatchTable* OpenGL::g_dispatch_table_ptr = nullptr;


__attribute__((constructor))
static void load_vkgl_library_func(void)
{
	vkgl_printf("%s", __func__);
}