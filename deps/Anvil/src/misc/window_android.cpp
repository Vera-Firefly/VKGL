#include "misc/window_android.h"


Anvil::WindowUniquePtr Anvil::WindowAndroid::create(
                        								unsigned int                   in_width,
                                                        unsigned int                   in_height,
                                                WindowHandle      in_window_handle)
{
    WindowUniquePtr result_ptr(nullptr,
                               std::default_delete<Window>() );

    result_ptr.reset(
        new Anvil::WindowAndroid(
        						in_width,
                                in_height,
                             in_window_handle)
    );

    if (result_ptr)
    {
        if (!dynamic_cast<WindowAndroid*>(result_ptr.get() )->init(true /* in_visible */) )
        {
            result_ptr.reset();
        }
    }

    return result_ptr;
}


/** Please see header for specification */
Anvil::WindowAndroid::WindowAndroid(
								unsigned int                   in_width,
                                unsigned int                   in_height,
                            WindowHandle       in_window_handle)
    :Window("",
            in_width,        /* in_width                 */
            in_height,        /* in_height                */
            true,     /* in_closable              */
            nullptr)  /* in_present_callback_func */
{
    /* NOTE: Window title/size info is extracted at init time */
    m_window         = in_window_handle;
    m_window_owned   = false;
}

Anvil::WindowAndroid::~WindowAndroid()
{
}

/** Please see header for specification */
void Anvil::WindowAndroid::close()
{
}


/* Please see header for specification */
void Anvil::WindowAndroid::run()
{
}
