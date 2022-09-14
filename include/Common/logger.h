/* VKGL (c) 2018 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef VKGL_LOGGER_H
#define VKGL_LOGGER_H

#include "vkgl_config.h"
#include "Common/macros.h"
#include <mutex>
#include <sstream>
#include <stdio.h>


#ifdef DEBUG_DEPTH
#   undef DEBUG_DEPTH
#endif // DEBUG_DEPTH
#define DEBUG_DEPTH


#if defined(FUNC_DEBUG_GLAPI_CALL) && defined(_DEBUG)
	#define FUN_ENTRY_GLAPI_CALL(level) \
		printf("[VKGL][FUNC_DEBUG_GLAPI_CALL]: %s()" "\n", __func__)
#else
	#define FUN_ENTRY_GLAPI_CALL(level)
#endif


#if defined(FUNC_DEBUG) && defined(_DEBUG)
	#define FUN_ENTRY(level) \
		printf("[VKGL][FUNC_DEBUG]: %s()  [ %s: %d ]" "\n", __func__, __FILE__, __LINE__)
#else
	#define FUN_ENTRY(leve)
#endif


#if defined(MSG_PRINTF) && defined(_DEBUG)
	#define vkgl_printf(massage, ...) \
		printf("[VKGL][MSG_PRINTF]" " " massage "\n", __VA_ARGS__)
#else
	#define vkgl_printf(massage, ...)
#endif


namespace VKGL
{
    enum class LogLevel
    {
        APIDump,
        Error,
        Info,
        Warning,

        Unknown
    };

    class Logger
    {
    public:
         Logger();
        ~Logger();

        static void deinit();
        static void init  ();

        void log(const LogLevel& in_log_level,
                 const char*     in_message_template,
                 ...);

    private:
        std::stringstream m_log_data_sstream;
        std::mutex        m_mutex;
    };

    extern Logger* g_logger_ptr;
}

#define VKGL_LOG(level, message_template, ...) \
    VKGL::g_logger_ptr->log(level, message_template, __VA_ARGS__)

#if defined(VKGL_DUMP_API_CALLS)
    #define VKGL_TRACE(message_template, ...) \
        VKGL::g_logger_ptr->log(VKGL::LogLevel::APIDump, message_template, __VA_ARGS__)
#else
    #define VKGL_TRACE(message_template, ...)
#endif

#endif /* VKGL_LOGGER_H */