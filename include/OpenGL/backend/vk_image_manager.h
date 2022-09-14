/* VKGL (c) 2018 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef VKGL_VK_IMAGE_MANAGER_H
#define VKGL_VK_IMAGE_MANAGER_H

#include "Anvil/include/misc/types.h"
#include "OpenGL/backend/vk_reference.h"
#include "OpenGL/types.h"

namespace OpenGL
{
    typedef std::unique_ptr<VKImageManager> VKImageManagerUniquePtr;

    class VKImageManager : public IVKImageManager
    {
    public:
        /* Public functions */

        static VKImageManagerUniquePtr create(const OpenGL::IContextObjectManagers* in_frontend_ptr,
                                               IBackend*                             in_backend_ptr);

        ~VKImageManager();

        OpenGL::VKImageReferenceUniquePtr acquire_object(const GLuint&             in_id,
                                                          OpenGL::TimeMarker        in_frontend_object_creation_time,
                                                          OpenGL::TimeMarker        in_texture_marker);
        bool                               create_object (const GLuint&             in_id,
                                                          const OpenGL::TimeMarker& in_frontend_object_creation_time,
                                                          OpenGL::ObjectType		in_frontend_object_type);
        bool                               destroy_object(const GLuint&             in_id,
                                                          const OpenGL::TimeMarker& in_frontend_object_creation_time);

        OpenGL::TimeMarker get_tot_image_time_marker(const GLuint&             in_id,
                                                      const OpenGL::TimeMarker& in_frontend_object_creation_time) const;

    private:
        /* Private type definitions */
        typedef struct ImageProps
        {
            uint32_t 								n_mipmaps;
            uint32_t 								n_layers;
            TextureMipState							texture_mip_state;
            TextureState							texture_state;
            RenderbufferState						renderbuffer_state;
            
            Anvil::ImageUniquePtr                  image_ptr;
            Anvil::ImageViewUniquePtr                  image_view_ptr;
            Anvil::SamplerUniquePtr                  sampler_ptr;
            std::vector<OpenGL::VKImageReference*> reference_ptrs;

            ImageProps(Anvil::ImageUniquePtr 	in_image_ptr,
            			Anvil::ImageViewUniquePtr in_image_view_ptr,
            			Anvil::SamplerUniquePtr 	in_sampler_ptr,
            			const uint32_t*				in_n_mipmaps,
            			const uint32_t*				in_n_layers,
            			const TextureMipState*			in_texture_mip_state_ptr,
            			const TextureState*				in_texture_state_ptr)
                :n_mipmaps		(*in_n_mipmaps),
                n_layers		(*in_n_layers),
                texture_mip_state(*in_texture_mip_state_ptr),
                texture_state	(*in_texture_state_ptr),
                image_ptr		(std::move(in_image_ptr) ),
                image_view_ptr(std::move(in_image_view_ptr) ),
                sampler_ptr		(std::move(in_sampler_ptr) )
            {
                /* Stub */
            }
            
            ImageProps(Anvil::ImageUniquePtr 	in_image_ptr,
            			Anvil::ImageViewUniquePtr in_image_view_ptr,
            			const RenderbufferState*	in_renderbuffer_state_ptr)
                :renderbuffer_state	(*in_renderbuffer_state_ptr),
                image_ptr		(std::move(in_image_ptr) ),
                image_view_ptr(std::move(in_image_view_ptr) )
            {
                /* Stub */
            }
        } ImageProps;
        typedef std::unique_ptr<ImageProps> ImagePropsUniquePtr;

        typedef struct ImageData
        {
            /* Maintain "snapshots" of object instances until all references are destroyed.
             *
             * This is important because, even though an app requests object deletion, a VK object
             * might still be referenced by command images, image views, etc.
             */
            std::map<OpenGL::TimeMarker, ImagePropsUniquePtr> image_map;

            OpenGL::TimeMarker tot_image_time_marker;
            bool               		has_been_destroyed;
            OpenGL::ObjectType		frontend_object_type;

            ImageData(OpenGL::ObjectType in_frontend_object_type)
            	:frontend_object_type(in_frontend_object_type)
            {
                has_been_destroyed = false;
            }
        } ImageData;
        typedef std::unique_ptr<ImageData> ImageDataUniquePtr;

        typedef std::pair<GLuint, OpenGL::TimeMarker> ImageMapKey;

        /* Private functions */
        VKImageManager(const OpenGL::IContextObjectManagers* in_frontend_ptr,
                        IBackend*                             in_backend_ptr);

        bool                   can_image_handle_frontend_reqs(const Anvil::Image*        in_image_ptr,
                                                               const OpenGL::InternalFormat& in_internal_format,
                                                               const size_t&               in_width,
                                                               const size_t&               in_height,
                                                               const size_t&               in_depth) const;
        Anvil::ImageUniquePtr create_vk_image               (const GLuint&               in_id,
        														OpenGL::TimeMarker 			in_frontend_time_marker,
        														bool							in_is_texture);
        Anvil::ImageViewUniquePtr create_vk_image_view     (const GLuint&               in_id,
        														Anvil::Image*				in_image_ptr);
        Anvil::SamplerUniquePtr create_vk_sampler         (const GLuint&               in_id,
        														OpenGL::TimeMarker 		in_frontend_time_marker);

        uint32_t get_n_references      (const ImageData*          in_image_data_ptr) const;
        void     on_reference_created  (ImageData*                in_image_data_ptr,
                                        OpenGL::VKImageReference* in_reference_ptr);
        void     on_reference_destroyed(ImageData*                in_image_data_ptr,
                                        OpenGL::VKImageReference* in_reference_ptr);

        /* Private variables */
        std::map<ImageMapKey, ImageDataUniquePtr> m_images;
        mutable std::mutex                          m_mutex;

        OpenGL::IBackend* const                     m_backend_ptr;
        const OpenGL::IContextObjectManagers* const m_frontend_ptr;
    };
};

#endif /* VKGL_VK_IMAGE_MANAGER_H */