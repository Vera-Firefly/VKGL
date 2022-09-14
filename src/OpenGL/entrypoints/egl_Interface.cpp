
#include "OpenGL/entrypoints/egl_Interface.h"

#include "Common/tls.h"
#include "Common/types.h"
#include "Common/logger.h"

#include "OpenGL/context.h"
#include "OpenGL/globals.h"
#include "OpenGL/backend/vk_backend.h"


void* 	create_vk_surface_swapchain 	(void *vk_backend, void *window);
void 	recreate_vk_surface_swapchain 	(void *vk_backend, void *window);
void 	destroy_vk_surface_swapchain (void *vk_backend, void *window);
void* 	create_vk_backend 				(void *wsi_context);
void 	destroy_vk_backend 				(void *vk_backend);
void* 	create_gl_context 				(void *wsi_context, void *vk_backend);
void 	destroy_gl_context 				(void *gl_context);
void 	set_vk_backend_gl_context 		(void *gl_context, void *vk_backend);
void 	make_current 				(void *gl_context);
void 	swap_buffers 				(void *gl_context);
void 	flush 						(void *gl_context);
void 	finish 						(void *gl_context);


__attribute__((visibility("default")))
egl_Interface_t EGLInterface = {
	create_vk_surface_swapchain,
	recreate_vk_surface_swapchain,
	destroy_vk_surface_swapchain,
	create_vk_backend,
	destroy_vk_backend,
	create_gl_context,
	destroy_gl_context,
	set_vk_backend_gl_context,
	make_current,
	swap_buffers,
	flush,
	finish,
};



#define CONV_GL_CONTEXT(object, in_gl_context)		\
	OpenGL::Context* object = static_cast<OpenGL::Context*>(in_gl_context);
	
#define CONV_VK_BACKEND(object, in_vk_backend)		\
	OpenGL::VKBackend* object = static_cast<OpenGL::VKBackend*>(in_vk_backend);
	
#define CONV_IWSI_CONTEXT(object, in_wsi_context)		\
	VKGL::IWSIContext* object = static_cast<VKGL::IWSIContext*>(in_wsi_context);


void* 	create_vk_surface_swapchain  	(void *vk_backend, void *window)
{
    FUN_ENTRY(DEBUG_DEPTH);
    
	CONV_VK_BACKEND(vk_backend_p, vk_backend)
	
	auto vk_swapchain_manager_ptr = static_cast<OpenGL::IBackend*>(vk_backend_p)->get_swapchain_manager_ptr();
	
	vk_swapchain_manager_ptr->set_target_window(window);
	
	auto tot_time_marker = vk_swapchain_manager_ptr->get_tot_time_marker();
	
	auto result = vk_swapchain_manager_ptr->acquire_swapchain(tot_time_marker);
	
	return nullptr;
}

void 	recreate_vk_surface_swapchain  	(void *vk_backend, void *window)
{
    FUN_ENTRY(DEBUG_DEPTH);
    
	CONV_VK_BACKEND(vk_backend_p, vk_backend)
	
	auto vk_swapchain_manager_ptr = static_cast<OpenGL::IBackend*>(vk_backend_p)->get_swapchain_manager_ptr();
	
	vk_swapchain_manager_ptr->set_target_window(window);
	
	vk_swapchain_manager_ptr->recreate_swapchain(false);
	
}

void 	destroy_vk_surface_swapchain  (void *vk_backend, void *window)
{
    FUN_ENTRY(DEBUG_DEPTH);
    
	CONV_VK_BACKEND(vk_backend_p, vk_backend)
	
	auto vk_swapchain_manager_ptr = static_cast<OpenGL::IBackend*>(vk_backend_p)->get_swapchain_manager_ptr();
	
}

void* 	create_vk_backend  		(void *wsi_context)
{
    FUN_ENTRY(DEBUG_DEPTH);
    
	CONV_IWSI_CONTEXT(wsi_context_p, wsi_context)
	
	OpenGL::VKBackendUniquePtr m_vk_backend_p = OpenGL::VKBackend::create(wsi_context_p);
	
	return m_vk_backend_p.release();
}

void 	destroy_vk_backend  		(void *vk_backend)
{
    FUN_ENTRY(DEBUG_DEPTH);
    
	CONV_VK_BACKEND(vk_backend_p, vk_backend)
	
	OpenGL::VKBackendUniquePtr m_vk_backend_p(vk_backend_p);
	
	m_vk_backend_p.reset();
}

void* 	create_gl_context  		(void *wsi_context, void *vk_backend)
{
    FUN_ENTRY(DEBUG_DEPTH);
    
	CONV_IWSI_CONTEXT(wsi_context_p, wsi_context)
	CONV_VK_BACKEND(vk_backend_p, vk_backend)
	
	OpenGL::ContextUniquePtr m_gl_context_p = OpenGL::Context::create(reinterpret_cast<VKGL::IWSIContext*>             (wsi_context_p),
                                              					 		dynamic_cast<const OpenGL::IBackend*>       	  (vk_backend_p),
                                              					 		dynamic_cast<OpenGL::IBackendGLCallbacks*>       (vk_backend_p),
                                               							dynamic_cast<const OpenGL::IBackendCapabilities*>(vk_backend_p));
    
	return m_gl_context_p.release();
}

void 	destroy_gl_context  		(void *gl_context)
{
    FUN_ENTRY(DEBUG_DEPTH);
    
	CONV_GL_CONTEXT(gl_context_p, gl_context)
	
	OpenGL::ContextUniquePtr m_gl_context_p(gl_context_p);
	
	m_gl_context_p.reset();
}

void	set_vk_backend_gl_context		(void *gl_context, void *vk_backend)
{
    FUN_ENTRY(DEBUG_DEPTH);
    
	CONV_GL_CONTEXT(gl_context_p, gl_context)
	CONV_VK_BACKEND(vk_backend_p, vk_backend)
	
	vk_backend_p->set_frontend_callback(dynamic_cast<const OpenGL::IContextObjectManagers*>(gl_context_p));
}

void 	make_current  			(void *gl_context)
{
    FUN_ENTRY(DEBUG_DEPTH);
    
	CONV_GL_CONTEXT(gl_context_p, gl_context)
	
	setGlThreadSpecific(gl_context_p);
	/*
	OpenGL::g_dispatch_table_ptr = gl_context_p->get_dispatch_table();
	
	vkgl_assert(OpenGL::g_dispatch_table_ptr != nullptr);
	vkgl_assert(OpenGL::g_dispatch_table_ptr->bound_context_ptr != nullptr);
	*/
}

void 	swap_buffers  			(void *gl_context)
{
    FUN_ENTRY(DEBUG_DEPTH);
    
	CONV_GL_CONTEXT(gl_context_p, gl_context)
	
	gl_context_p->present();
}

void 	flush  					(void *gl_context)
{
    FUN_ENTRY(DEBUG_DEPTH);
    
	CONV_GL_CONTEXT(gl_context_p, gl_context)
	
	gl_context_p->flush();
}

void 	finish  					(void *gl_context)
{
    FUN_ENTRY(DEBUG_DEPTH);
    
	CONV_GL_CONTEXT(gl_context_p, gl_context)
	
	gl_context_p->finish();
}