/* VKGL (c) 2018 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#if defined(_WIN32)
    #define _WIN32_WINNT 0x0501

    #include <Windows.h>
#endif

#include "Common/debug.h"
#include "Common/logger.h"

#include <assert.h>
#include <stdio.h>

void VKGL::Debug::assert_failed(const char*  in_filename,
                                unsigned int in_line,
                                const char*  in_message)
{
    /*VKGL_LOG(VKGL::LogLevel::Error,
             "[!] Assertion failure in %s at %d: [%s]",
            in_filename,
            in_line,
            in_message);
    */
    printf(  "[VKGL][ERROR_TRACE]: [%s] Assertion failure  [ %s: %d ]" "\n",
            in_message,
            in_filename,
            in_line);

    #if defined(_DEBUG)
    {
        #if defined(_WIN32)
        {
            if (::IsDebuggerPresent() )
            {
                _CrtDbgBreak();
            }
        }
        #else
        {
            //#error TODO
        }
        #endif
    }
    #endif
    
    //abort();
    
}