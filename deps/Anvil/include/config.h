/* Under no circumstances include Vulkan func prototypes. For a variety of reasons,
 * these are NOT exposed by Anvil.
 */
#if !defined(ANVIL_VULKAN_CPP)
    #define VK_NO_PROTOTYPES
#endif

#define ANVIL_VULKAN_DYNAMIC_DLL "libvulkan.so"

/* Defined if Anvil links statically with a Vulkan library */
//#define ANVIL_LINK_STATICALLY_WITH_VULKAN_LIB

/* Defined if glslangvalidator is to be statically linked with Anvil */
#define ANVIL_LINK_WITH_GLSLANG

/* Defined if Windows window system support is to be included in Anvil */
//#define ANVIL_INCLUDE_WIN3264_WINDO,W_SYSTEM_SUPPORT

/* Defined if XCB window system support is to be included in Anvil */
//#define ANVIL_INCLUDE_XCB_WINDOW_SYSTEM_SUPPORT
