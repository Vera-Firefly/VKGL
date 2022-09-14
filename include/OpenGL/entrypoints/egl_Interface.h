#ifndef OPENGL_EGL_INTERFACE_H
#define OPENGL_EGL_INTERFACE_H


#include <stdint.h>


typedef void* 	(* PTR_create_vk_surface_swapchain) 	(void *vk_backend, void *window);
typedef void 	(* PTR_recreate_vk_surface_swapchain) 	(void *vk_backend, void *window);
typedef void 	(* PTR_destroy_vk_surface_swapchain) (void *vk_backend, void *window);
typedef void* 	(* PTR_create_vk_backend) 				(void *IWSIcontext);
typedef void 	(* PTR_destroy_vk_backend) 				(void *vk_backend);
typedef void* 	(* PTR_create_gl_context) 				(void *IWSIcontext, void *vk_backend);
typedef void 	(* PTR_destroy_gl_context) 				(void *gl_context);
typedef void 	(* PTR_set_vk_backend_gl_context) 		(void *gl_context, void *vk_backend);
typedef void 	(* PTR_make_current) 				(void *gl_context);
typedef void 	(* PTR_swap_buffers) 				(void *gl_context);
typedef void 	(* PTR_flush) 						(void *gl_context);
typedef void 	(* PTR_finish) 						(void *gl_context);


typedef struct {
	PTR_create_vk_surface_swapchain 	p_create_vk_surface_swapchain;
	PTR_recreate_vk_surface_swapchain 	p_recreate_vk_surface_swapchain;
	PTR_destroy_vk_surface_swapchain p_destroy_vk_surface_swapchain;
	PTR_create_vk_backend			p_create_vk_backend;
	PTR_destroy_vk_backend			p_destroy_vk_backend;
	PTR_create_gl_context 			p_create_gl_context;
	PTR_destroy_gl_context 			p_destroy_gl_context;
	PTR_set_vk_backend_gl_context		p_set_vk_backend_gl_context;
	PTR_make_current 				p_make_current;
	PTR_swap_buffers 				p_swap_buffers;
	PTR_flush 						p_flush;
	PTR_finish 						p_finish;
} egl_Interface_t;

#endif //OPENGL_EGL_INTERFACE_H