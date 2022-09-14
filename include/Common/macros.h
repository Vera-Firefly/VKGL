/* VKGL (c) 2018 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef COMMON_MACROS_H
#define COMMON_MACROS_H

#include "vkgl_config.h"
#include "Common/logger.h"
#include "Common/debug.h"

#if defined(ERROR_TRACE) && defined(_DEBUG)
    #define vkgl_assert(assertion)                  \
        if (!(assertion))                           \
        {                                           \
            VKGL::Debug::assert_failed(__FILE__,    \
                                       __LINE__,    \
                                       #assertion); \
        }

    #define vkgl_assert_fail()                                      \
        VKGL::Debug::assert_failed(__FILE__,                        \
                                   __LINE__,                        \
                                   "Unexpected condition detected");

	#define vkgl_not_implemented() \
    	printf("[VKGL][ERROR_TRACE] %s(): Functionality not implemented!  [ %s: %d ]" "\n", __func__, __FILE__, __LINE__)

#else
    #define vkgl_assert(assertion)
    #define vkgl_assert_fail()
	#define vkgl_not_implemented()
#endif


#endif /* COMMON_MACROS_H */