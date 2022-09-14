/* VKGL (c) 2018 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef COMMON_GLOBALS_H
#define COMMON_GLOBALS_H

#include "vkgl_config.h"
#include "Common/logger.h"
#include "Common/types.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PER_FUNC_LOCAL_HELPER_STORAGE_SIZE (4096)

#if defined(_WIN32)
    #define VKGL_THREADLOCAL __declspec(thread)
#else
    #define VKGL_THREADLOCAL thread_local
    //#error todo
#endif

#endif /* COMMON_GLOBALS_H */