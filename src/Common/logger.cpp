/* VKGL (c) 2018 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Anvil/include/misc/io.h"
#include "Common/globals.h"
#include "Common/logger.h"
#include "Common/macros.h"

#include <cstdarg>

#define LOG_FILE_NAME "VKGL_log.txt"


/* TODO: Writes must be flushed asynchronously, every once in a while. Right now,
 *       cached trace data is only written at dll detach time!
 */
VKGL::Logger* VKGL::g_logger_ptr = nullptr;


VKGL::Logger::Logger()
{
    //Anvil::IO::delete_file(LOG_FILE_NAME);
}

VKGL::Logger::~Logger()
{
   /*Anvil::IO::write_text_file(LOG_FILE_NAME,
                               g_logger_ptr->m_log_data_sstream.str() );
   */
}

void VKGL::Logger::deinit()
{
    vkgl_assert(g_logger_ptr != nullptr);

    if (g_logger_ptr != nullptr)
    {
        delete g_logger_ptr;
        g_logger_ptr = nullptr;
    }
}

void VKGL::Logger::init()
{
    vkgl_assert(g_logger_ptr == nullptr);

    g_logger_ptr = new VKGL::Logger();

    vkgl_assert(g_logger_ptr != nullptr);
}

void VKGL::Logger::log(const LogLevel& in_log_level,
                       const char*     in_message_template,
                       ...)
{
    va_list args;
    char    temp[MAX_PER_FUNC_LOCAL_HELPER_STORAGE_SIZE];

    va_start(args,
             in_message_template);
    {
        //vsprintf<sizeof(temp)>(temp,
        vsprintf				 (temp,
                                 in_message_template,
                                 args);
    }
    va_end(args);
    
    vkgl_printf("%s", temp);

}

