#ifndef WINDOW_ANDROID_H
#define WINDOW_ANDROID_H

#include "misc/window.h"

namespace Anvil
{
    class WindowAndroid : public Window
    {
    public:
        /* Public functions */
        static Anvil::WindowUniquePtr create(
                                             unsigned int                   in_width,
                                             unsigned int                   in_height,
                                             WindowHandle      in_window_handle);

        virtual ~WindowAndroid();

        virtual void close();
        virtual void run();

        /* Returns window's platform */
        WindowPlatform get_platform() const
        {
            return WINDOW_PLATFORM_ANDROID;
        }

        /* Tells if it's a dummy window (offscreen rendering thus no WSI/swapchain involved) */
        virtual bool is_dummy()
        {
            return false;
        }

        /** Returns system XCB connection, should be used by linux only */
        virtual void* get_connection() const
        {
            return nullptr;
        }

    private:
        WindowAndroid(
                 unsigned int                   in_width,
                 unsigned int                   in_height,
                  WindowHandle                   in_window_handle);

        /** Creates a new system window and prepares it for usage. */
        bool init           (const bool& in_visible)
        {
        	return true;
        }

        /* Private variables */
    };
}; /* namespace Anvil */

#endif//WINDOW_ANDROID_H