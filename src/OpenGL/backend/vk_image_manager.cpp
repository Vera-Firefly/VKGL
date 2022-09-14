/* VKGL (c) 2018 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/macros.h"
#include "OpenGL/backend/vk_image_manager.h"
#include "OpenGL/backend/vk_format_manager.h"
#include "OpenGL/backend/vk_reference.h"
#include "OpenGL/backend/vk_utils.h"
#include "OpenGL/frontend/gl_texture_manager.h"
#include "OpenGL/frontend/gl_renderbuffer_manager.h"
#include "Anvil/include/misc/formats.h"
#include "Anvil/include/misc/memory_allocator.h"
#include "Anvil/include/misc/image_create_info.h"
#include "Anvil/include/misc/image_view_create_info.h"
#include "Anvil/include/misc/sampler_create_info.h"
#include "Anvil/include/wrappers/image.h"
#include "Anvil/include/wrappers/image_view.h"
#include "Anvil/include/wrappers/sampler.h"

OpenGL::VKImageManager::VKImageManager(const OpenGL::IContextObjectManagers* in_frontend_ptr,
                                         IBackend*                             in_backend_ptr)
    :m_backend_ptr (in_backend_ptr),
     m_frontend_ptr(in_frontend_ptr)
{
    FUN_ENTRY(DEBUG_DEPTH);
    
    vkgl_assert(m_backend_ptr  != nullptr);
    vkgl_assert(m_frontend_ptr != nullptr);
}

OpenGL::VKImageManager::~VKImageManager()
{
    FUN_ENTRY(DEBUG_DEPTH);
    
    /*  Stub */
}

OpenGL::VKImageReferenceUniquePtr OpenGL::VKImageManager::acquire_object(const GLuint&      in_id,
                                                                           OpenGL::TimeMarker in_frontend_object_creation_time,
                                                                           OpenGL::TimeMarker in_frontend_time_marker)
{
    FUN_ENTRY(DEBUG_DEPTH);
    
    std::lock_guard<std::mutex>        lock                 (m_mutex);
    ImageData*                        image_data_ptr      (nullptr);
    const auto                         image_map_key       (ImageMapKey(in_id, in_frontend_object_creation_time) );
    auto                               image_props_iterator(m_images.find(image_map_key) );
    OpenGL::VKImageReferenceUniquePtr new_reference_ptr    (nullptr,
                                                             [](OpenGL::VKImageReference* in_ref_ptr){ delete in_ref_ptr; });
    Anvil::Image*                     ref_image_ptr       	(nullptr);
    Anvil::ImageView*                 ref_image_view_ptr    (nullptr);
    Anvil::Sampler*                     ref_sampler_ptr       (nullptr);

    vkgl_assert(image_props_iterator != m_images.end() );
    vkgl_assert(in_frontend_time_marker != OpenGL::LATEST_SNAPSHOT_AVAILABLE); /* This special value is only allowed for frontend managers ! */

    image_data_ptr = image_props_iterator->second.get();

    {
        auto image_iterator 			= image_data_ptr->image_map.find(in_frontend_time_marker);
        auto frontend_object_type		= image_data_ptr->frontend_object_type;
        
        switch (frontend_object_type)
        {
            case OpenGL::ObjectType::Texture:
            {
                if (image_iterator != image_data_ptr->image_map.end() )
                {
                    ref_image_ptr 		= image_iterator->second->image_ptr.get();
                    ref_image_view_ptr = image_iterator->second->image_view_ptr.get();
                    ref_sampler_ptr 	= image_iterator->second->sampler_ptr.get();
                    
                    vkgl_assert(ref_image_ptr 		!= nullptr);
                    vkgl_assert(ref_image_view_ptr != nullptr);
                    vkgl_assert(ref_sampler_ptr 	!= nullptr);
                }
                else
                {
                    auto tot_image_iterator = image_data_ptr->image_map.find(image_data_ptr->tot_image_time_marker);
                    
                    uint32_t n_mipmaps													= 0;
                    uint32_t n_layers													= 0;
                    const OpenGL::TextureMipState* texture_mip_state_ptr = nullptr;
                    const OpenGL::TextureState* 	texture_state_ptr					= nullptr;
                    uint32_t tot_n_mipmaps													= 0;
                    uint32_t tot_n_layers													= 0;
                    const OpenGL::TextureMipState* tot_texture_mip_state_ptr				= nullptr;
                    const OpenGL::TextureState* 	tot_texture_state_ptr					= nullptr;
                    {
                        const std::vector<OpenGL::TextureMipStateUniquePtr>* texture_mip_states_ptr = nullptr;
                        
                        m_frontend_ptr->get_texture_manager_ptr()->get_texture_mip_state_ptr(in_id,
                                            												&in_frontend_time_marker,
                                            												&n_layers,
                                            												&texture_mip_states_ptr);
                        m_frontend_ptr->get_texture_manager_ptr()->get_texture_state_ptr(in_id,
                    																	&in_frontend_time_marker,
                    																	&texture_state_ptr);
                        
                        vkgl_assert(texture_mip_states_ptr != nullptr);
                        
                        {
                        	texture_mip_state_ptr = texture_mip_states_ptr->at(0).get();
                        }
                        
                        vkgl_assert(texture_mip_state_ptr != nullptr);
                        vkgl_assert(texture_state_ptr 		!= nullptr);
                        
                        {
                            if (texture_mip_states_ptr->size() > 1)
                            {
                                const auto max_dimension = std::max(std::max(texture_mip_state_ptr->depth,
                                                                             texture_mip_state_ptr->height),
                                                                    texture_mip_state_ptr->width);
                        
                                n_mipmaps = static_cast<uint32_t>(1 + log2(max_dimension) );
                            }
                            else
                            {
                                n_mipmaps = texture_mip_states_ptr->size();
                            }
                        }
                        
                        vkgl_assert(n_mipmaps 			!= 0);
                        vkgl_assert(n_layers 			!= 0);
                        
                        if (tot_image_iterator != image_data_ptr->image_map.end() )
                        {
                            tot_n_mipmaps 				= tot_image_iterator->second->n_mipmaps;
                            tot_n_layers 				= tot_image_iterator->second->n_layers;
                            tot_texture_mip_state_ptr = &tot_image_iterator->second->texture_mip_state;
                            tot_texture_state_ptr 		= &tot_image_iterator->second->texture_state;
                        }
                    }
                    
                    Anvil::ImageUniquePtr 		new_image_ptr;
                    Anvil::ImageViewUniquePtr new_image_view_ptr;
                    Anvil::SamplerUniquePtr 	new_sampler_ptr;
                    
                    new_image_ptr 		= create_vk_image(in_id,
                    											in_frontend_time_marker,
                    											true);		/* in_is_texture */
                    
                    if (tot_texture_mip_state_ptr == nullptr 					||
                    	//*tot_texture_mip_state_ptr != *texture_mip_state_ptr) ||
                    	memcmp(tot_texture_mip_state_ptr,
                    			texture_mip_state_ptr,
                    			sizeof(OpenGL::TextureMipState) ) != 0 		||
                    	tot_n_layers != n_layers								||
                    	tot_n_mipmaps != n_mipmaps							)
                    {
                        auto memory_feature_flags = (new_image_ptr->get_create_info_ptr()->get_tiling() == Anvil::ImageTiling::OPTIMAL) ? Anvil::MemoryFeatureFlagBits::DEVICE_LOCAL_BIT
                    																													: Anvil::MemoryFeatureFlagBits::HOST_COHERENT_BIT | Anvil::MemoryFeatureFlagBits::MAPPABLE_BIT;
                    	
                    	m_backend_ptr->get_memory_allocator_ptr()->add_image_whole(new_image_ptr.get(),
    																					memory_feature_flags);
                		auto shared_memory_block_ptr = new_image_ptr->get_memory_block();
                		vkgl_assert(shared_memory_block_ptr != nullptr);
                	}
                	else
                	{
                		auto tot_image_ptr				= tot_image_iterator->second->image_ptr.get();
                		auto shared_memory_block_ptr = tot_image_ptr->get_memory_block();
                		vkgl_assert(shared_memory_block_ptr != nullptr);
                		
                		new_image_ptr->set_memory(shared_memory_block_ptr);
                		
                		{
                			const_cast<Anvil::ImageCreateInfo*>(new_image_ptr->get_create_info_ptr() )->set_mipmaps_to_upload(const_cast<Anvil::ImageCreateInfo*>(tot_image_ptr->get_create_info_ptr() )->get_mipmaps_to_upload() );
                		}
                	}
                	
                	new_image_view_ptr = create_vk_image_view(in_id,
                													new_image_ptr.get() );
                	
                	if (tot_texture_state_ptr == nullptr 				||
                		//*tot_texture_state_ptr != *texture_state_ptr) ||
                		memcmp(tot_texture_state_ptr,
                				texture_state_ptr,
                				sizeof(OpenGL::TextureState) ) != 0)
                	{
                        new_sampler_ptr 	= create_vk_sampler(in_id,
                    												in_frontend_time_marker);
                    }
                    else
                    {
                        new_sampler_ptr 	= create_vk_sampler(in_id,
                    												in_frontend_time_marker);
                    }
                    
                    vkgl_assert(new_image_ptr 		!= nullptr);
                    vkgl_assert(new_image_view_ptr != nullptr);
                    vkgl_assert(new_sampler_ptr 	!= nullptr);
                    
                    ref_image_ptr 		= new_image_ptr.get();
                    ref_image_view_ptr = new_image_view_ptr.get();
                    ref_sampler_ptr 	= new_sampler_ptr.get();
        
                    image_data_ptr->image_map[in_frontend_time_marker].reset(
                        new ImageProps(std::move(new_image_ptr),
                    					std::move(new_image_view_ptr),
                    					std::move(new_sampler_ptr),
                    					&n_mipmaps,
                    					&n_layers,
                    					texture_mip_state_ptr,
                    					texture_state_ptr)
                    );
                    vkgl_assert(image_data_ptr->image_map[in_frontend_time_marker] != nullptr);
        
                    image_data_ptr->tot_image_time_marker = in_frontend_time_marker;
                }
                
                break;
            }
            
            case OpenGL::ObjectType::Renderbuffer:
            {
                if (image_iterator != image_data_ptr->image_map.end() )
                {
                    ref_image_ptr 		= image_iterator->second->image_ptr.get();
                    ref_image_view_ptr = image_iterator->second->image_view_ptr.get();
                    
                    vkgl_assert(ref_image_ptr 		!= nullptr);
                    vkgl_assert(ref_image_view_ptr != nullptr);
                }
                else
                {
                    auto tot_image_iterator = image_data_ptr->image_map.find(image_data_ptr->tot_image_time_marker);
                    
                    const OpenGL::RenderbufferState* renderbuffer_state_ptr			= nullptr;
                    const OpenGL::RenderbufferState* tot_renderbuffer_state_ptr		= nullptr;
                    {
                        m_frontend_ptr->get_renderbuffer_manager_ptr()->get_renderbuffer_state_ptr(in_id,
                                                    												&in_frontend_time_marker,
                                                    												&renderbuffer_state_ptr);
                        if (tot_image_iterator != image_data_ptr->image_map.end() )
                        {
                            tot_renderbuffer_state_ptr = &tot_image_iterator->second->renderbuffer_state;
                        }
                        vkgl_assert(renderbuffer_state_ptr != nullptr);
                    }
                    
                    Anvil::ImageUniquePtr 		new_image_ptr;
                    Anvil::ImageViewUniquePtr new_image_view_ptr;
                    
                    new_image_ptr 		= create_vk_image(in_id,
                    											in_frontend_time_marker,
                    											false);		/* in_is_texture */
                    
                    if (tot_renderbuffer_state_ptr == nullptr 						||
                    	//*tot_renderbuffer_state_ptr != *renderbuffer_state_ptr) ||
                    	memcmp(tot_renderbuffer_state_ptr,
                    			renderbuffer_state_ptr,
                    			sizeof(OpenGL::RenderbufferState) ) != 0		)
                    {
                    	auto memory_feature_flags = (new_image_ptr->get_create_info_ptr()->get_tiling() == Anvil::ImageTiling::OPTIMAL) ? Anvil::MemoryFeatureFlagBits::DEVICE_LOCAL_BIT
                    																													: Anvil::MemoryFeatureFlagBits::HOST_COHERENT_BIT | Anvil::MemoryFeatureFlagBits::MAPPABLE_BIT;
                    	
                    	m_backend_ptr->get_memory_allocator_ptr()->add_image_whole(new_image_ptr.get(),
    																					memory_feature_flags);
                		auto shared_memory_block_ptr = new_image_ptr->get_memory_block();
                		vkgl_assert(shared_memory_block_ptr != nullptr);
                	}
                	else
                	{
                	    auto tot_image_ptr				= tot_image_iterator->second->image_ptr.get();
                		auto shared_memory_block_ptr = tot_image_ptr->get_memory_block();
                		vkgl_assert(shared_memory_block_ptr != nullptr);
                		
                		new_image_ptr->set_memory(shared_memory_block_ptr);
                		
                		{
                			const_cast<Anvil::ImageCreateInfo*>(new_image_ptr->get_create_info_ptr() )->set_mipmaps_to_upload(const_cast<Anvil::ImageCreateInfo*>(tot_image_ptr->get_create_info_ptr() )->get_mipmaps_to_upload() );
                		}
                	}
                	
                	new_image_view_ptr = create_vk_image_view(in_id,
                													new_image_ptr.get() );
                	
                    vkgl_assert(new_image_ptr 		!= nullptr);
                    vkgl_assert(new_image_view_ptr != nullptr);
                    
                    ref_image_ptr 		= new_image_ptr.get();
                    ref_image_view_ptr = new_image_view_ptr.get();
        
                    image_data_ptr->image_map[in_frontend_time_marker].reset(
                        new ImageProps(std::move(new_image_ptr),
                    					std::move(new_image_view_ptr),
                    					renderbuffer_state_ptr)
                    );
                    vkgl_assert(image_data_ptr->image_map[in_frontend_time_marker] != nullptr);
        
                    image_data_ptr->tot_image_time_marker = in_frontend_time_marker;
                }
                
                break;
            }
            
            default:
            {
            	vkgl_assert_fail();
        	}
    	}
    }

    new_reference_ptr.reset(
        new OpenGL::VKImageReference(OpenGL::VKImagePayload(in_id,
                                                              in_frontend_object_creation_time,
                                                              ref_image_ptr,
                                                              ref_image_view_ptr,
                                                              ref_sampler_ptr,
                                                              in_frontend_time_marker),
                                      std::bind(&OpenGL::VKImageManager::on_reference_created,
                                                this,
                                                image_data_ptr,
                                                std::placeholders::_1),
                                      std::bind(&OpenGL::VKImageManager::on_reference_destroyed,
                                                this,
                                                image_data_ptr,
                                                std::placeholders::_1),
                                      std::bind(&OpenGL::VKImageManager::acquire_object,
                                                this,
                                                in_id,
                                                in_frontend_object_creation_time,
                                                in_frontend_time_marker) )
    );
    vkgl_assert(new_reference_ptr != nullptr);

    return new_reference_ptr;
}

bool OpenGL::VKImageManager::can_image_handle_frontend_reqs(const Anvil::Image*        in_image_ptr,
                                                              const OpenGL::InternalFormat& in_internal_format,
                                                              const size_t&               in_width,
                                                              const size_t&               in_height,
                                                              const size_t&               in_depth) const
{
    FUN_ENTRY(DEBUG_DEPTH);
    
    const auto image_create_info_ptr = in_image_ptr->get_create_info_ptr                   ();
    const auto required_usage_flags   = OpenGL::VKUtils::get_image_usage_flags_for_gl_internal_format(in_internal_format);
    bool       result                 = true;

    if ((image_create_info_ptr->get_usage_flags() & required_usage_flags) != required_usage_flags)
    {
        /* Specified image's usage flags are a subset of what's required. */
        result = false;

        goto end;
    }

    if (image_create_info_ptr->get_base_mip_width() < in_width	||
    	image_create_info_ptr->get_base_mip_height() < in_height ||
    	image_create_info_ptr->get_base_mip_depth() < in_depth)
    {
        /* Too little space available .. */
        result = false;

        goto end;
    }

end:
    return result;
}

OpenGL::VKImageManagerUniquePtr OpenGL::VKImageManager::create(const OpenGL::IContextObjectManagers* in_frontend_ptr,
                                                                 OpenGL::IBackend*                     in_backend_ptr)
{
    FUN_ENTRY(DEBUG_DEPTH);
    
    OpenGL::VKImageManagerUniquePtr result_ptr;

    result_ptr.reset(
        new VKImageManager(in_frontend_ptr,
                            in_backend_ptr)
    );

    vkgl_assert(result_ptr != nullptr);
    return result_ptr;
}

bool OpenGL::VKImageManager::create_object(const GLuint&             in_id,
                                            const OpenGL::TimeMarker& in_frontend_object_creation_time,
                                            OpenGL::ObjectType			in_frontend_object_type)
{
    FUN_ENTRY(DEBUG_DEPTH);
    
    /* NOTE: This function is only called from within the rendering context thread */
    ImageDataUniquePtr         image_data_ptr(nullptr);
    const auto                  image_map_key (ImageMapKey(in_id, in_frontend_object_creation_time) );
    std::lock_guard<std::mutex> lock           (m_mutex);
    bool                        result         (false);

    vkgl_assert(m_images.find(image_map_key) == m_images.end() );

    /* Only instantiate the structure for now. We're going to create the image instance, as well as the corresponding
     * memory instance, later on when the application actually specifies storage details.
     */
    image_data_ptr.reset(
        new ImageData(in_frontend_object_type)
    );

    if (image_data_ptr == nullptr)
    {
        goto end;
    }

    m_images[image_map_key] = std::move(image_data_ptr);
    result                    = true;
end:
    return result;
}

Anvil::ImageUniquePtr OpenGL::VKImageManager::create_vk_image(const GLuint&              in_id,
																	OpenGL::TimeMarker 			in_frontend_time_marker,
																	bool							in_is_texture)
{
    FUN_ENTRY(DEBUG_DEPTH);
    
    OpenGL::InternalFormat 			gl_internal_format		= OpenGL::InternalFormat::Unknown;
    Anvil::Format 					vk_format				= Anvil::Format::UNKNOWN;
    uint32_t						width					= 0;
    uint32_t						height					= 0;
    uint32_t						depth					= 0;
    uint32_t						n_layers				= 0;
    uint32_t						n_mipmaps				= 0;
    uint32_t						n_samples				= 0;
    Anvil::ImageCreateInfoUniquePtr create_info_ptr;
    auto                             device_ptr            = m_backend_ptr->get_device_ptr();
    Anvil::ImageUniquePtr           result_ptr;
    Anvil::SampleCountFlagBits 		sample_count 		= Anvil::SampleCountFlagBits::_1_BIT;
    Anvil::ImageTiling 				tiliing_flag 				= Anvil::ImageTiling::UNKNOWN;
    Anvil::ImageType				vk_image_type			= Anvil::ImageType::_2D; /* TODO */
    Anvil::ImageUsageFlags    		usage_flags           = Anvil::ImageUsageFlagBits::NONE;
    
    {
        auto frontend_texture_ptr 									= m_frontend_ptr->get_texture_manager_ptr();
        auto frontend_renderbuffer_ptr 								= m_frontend_ptr->get_renderbuffer_manager_ptr();
        
        if (in_is_texture)
        {
            uint32_t 										layers								= 0;
            OpenGL::TextureTarget 							texture_target						= OpenGL::TextureTarget::Unknown;
            const std::vector<TextureMipStateUniquePtr>* texture_mip_states_ptr				= nullptr;
            const OpenGL::TextureState* 					texture_state_ptr					= nullptr;
            {
                frontend_texture_ptr->get_texture_target(in_id,
            											&texture_target);
                frontend_texture_ptr->get_texture_mip_state_ptr(in_id,
                												&in_frontend_time_marker,
                												&layers,
                												&texture_mip_states_ptr);
                frontend_texture_ptr->get_texture_state_ptr(in_id,
            												&in_frontend_time_marker,
            												&texture_state_ptr);
                
                vkgl_assert(texture_target 			!= OpenGL::TextureTarget::Unknown);
                vkgl_assert(texture_mip_states_ptr != nullptr);
                vkgl_assert(texture_state_ptr 		!= nullptr);
            }
            
            gl_internal_format = texture_mip_states_ptr->at(0)->internal_format;
            width 				= texture_mip_states_ptr->at(0)->width;
            height 				= texture_mip_states_ptr->at(0)->height;
            depth 				= texture_mip_states_ptr->at(0)->depth;
            n_layers 			= layers;
            n_mipmaps 				= texture_mip_states_ptr->size();
            n_samples 			= texture_mip_states_ptr->at(0)->samples;
            usage_flags			= OpenGL::VKUtils::get_image_usage_flags_for_gl_internal_format(gl_internal_format);
        
        }
        else
        {
            //OpenGL::TextureTarget 			texture_target						= OpenGL::TextureTarget::_2D;
            const OpenGL::RenderbufferState* renderbuffer_state_ptr				= nullptr;
            {
                frontend_renderbuffer_ptr->get_renderbuffer_state_ptr(in_id,
                        												&in_frontend_time_marker,
                        												&renderbuffer_state_ptr);
                
                vkgl_assert(renderbuffer_state_ptr != nullptr);
            }
            
            gl_internal_format = renderbuffer_state_ptr->internal_format;
            width 				= renderbuffer_state_ptr->width;
            height 				= renderbuffer_state_ptr->height;
            depth 				= 1;
            n_layers 			= 1;
            n_mipmaps 			= 1;
            n_samples 			= renderbuffer_state_ptr->samples;
            usage_flags			= OpenGL::VKUtils::get_image_usage_flags_for_gl_internal_format(gl_internal_format);
        
        }
        
        Anvil::FormatFeatureFlags vk_format_feature_flags = Anvil::FormatFeatureFlagBits::NONE;
        {
    		//vk_format_feature_flags |= Anvil::FormatFeatureFlagBits::BLIT_DST_BIT;
    		//vk_format_feature_flags |= Anvil::FormatFeatureFlagBits::BLIT_SRC_BIT;
    		
    		if ((usage_flags & Anvil::ImageUsageFlagBits::COLOR_ATTACHMENT_BIT) == Anvil::ImageUsageFlagBits::COLOR_ATTACHMENT_BIT)
    		{
    			vk_format_feature_flags |= Anvil::FormatFeatureFlagBits::COLOR_ATTACHMENT_BIT;
        		//vk_format_feature_flags |= Anvil::FormatFeatureFlagBits::COLOR_ATTACHMENT_BLEND_BIT;
        	}
        	else if ((usage_flags & Anvil::ImageUsageFlagBits::DEPTH_STENCIL_ATTACHMENT_BIT) == Anvil::ImageUsageFlagBits::DEPTH_STENCIL_ATTACHMENT_BIT)
        	{
        		vk_format_feature_flags |= Anvil::FormatFeatureFlagBits::DEPTH_STENCIL_ATTACHMENT_BIT;
        	}
        	
    		vk_format_feature_flags |= Anvil::FormatFeatureFlagBits::SAMPLED_IMAGE_BIT;
    		//vk_format_feature_flags |= Anvil::FormatFeatureFlagBits::SAMPLED_IMAGE_FILTER_LINEAR_BIT;
    		//vk_format_feature_flags |= Anvil::FormatFeatureFlagBits::STORAGE_IMAGE_BIT;
        }
        
        sample_count = static_cast<Anvil::SampleCountFlagBits>(static_cast<int32_t>(sample_count) + std::floor(std::log2(n_samples) ) );
        vk_format = m_backend_ptr->get_format_manager_ptr()->get_best_fit_anvil_format(gl_internal_format,
        																					vk_format_feature_flags);
    	tiliing_flag = (Anvil::Formats::has_depth_aspect(vk_format) || Anvil::Formats::has_stencil_aspect(vk_format) ) ? Anvil::ImageTiling::OPTIMAL
    																													: Anvil::ImageTiling::LINEAR;
    }
    
    create_info_ptr = Anvil::ImageCreateInfo::create_no_alloc(device_ptr, 					/* in_device_ptr */
                                                            vk_image_type,/*OpenGL::VKUtils::get_image_type_for_gl_texture_target(&texture_target),*/								/* in_type */
                                                            vk_format,								/* in_format */
                                                            tiliing_flag,                /* in_tiling */
                                                            usage_flags,                   /* in_usage */
                                                            width,                          /* in_base_mipmap_width */
                                                            height,                          /* in_base_mipmap_height */
                                                            depth,                          /* in_base_mipmap_depth */
                                                            n_layers,                          /* in_n_layers */
                                                            sample_count,        /* in_sample_count */
                                                            Anvil::QueueFamilyFlagBits::COMPUTE_BIT | Anvil::QueueFamilyFlagBits::DMA_BIT | Anvil::QueueFamilyFlagBits::GRAPHICS_BIT,           /* in_queue_families */
                                                            Anvil::SharingMode::EXCLUSIVE,                /* in_sharing_mode */
                                                            (n_mipmaps > 1 ? true
                                                            				: false),                              /* in_use_full_mipmap_chain */
                                                            Anvil::ImageCreateFlagBits::NONE,           /* in_create_flags */
                                                            Anvil::ImageLayout::UNDEFINED,    /* in_post_alloc_image_layout */
                                                            nullptr);								/* in_opt_mipmaps_ptr */

    vkgl_assert(create_info_ptr != nullptr);

    result_ptr = Anvil::Image::create(std::move(create_info_ptr) );
    vkgl_assert(result_ptr != nullptr);

    #if defined(_DEBUG)
    {
        result_ptr->set_name_formatted("GL texture %d",
                                       in_id);
    }
    #endif

    return result_ptr;
}

Anvil::ImageViewUniquePtr OpenGL::VKImageManager::create_vk_image_view(const GLuint&              in_id,
																				Anvil::Image*		in_image_ptr)
{
    FUN_ENTRY(DEBUG_DEPTH);
    
    Anvil::ImageViewCreateInfoUniquePtr create_info_ptr;
    Anvil::ImageViewUniquePtr           result_ptr;
    auto                             		device_ptr            = m_backend_ptr->get_device_ptr();
    Anvil::ImageAspectFlags 			format_aspects 		= Anvil::ImageAspectFlagBits::NONE;
    auto 									format 				= in_image_ptr->get_create_info_ptr()->get_format();
    std::vector<Anvil::ImageAspectFlags> format_aspects_vec;
    
    Anvil::Formats::get_format_aspects(format,
    									&format_aspects_vec);
    for (auto current_format_aspect : format_aspects_vec)
    {
    	format_aspects |= current_format_aspect;
    }
    
    create_info_ptr = Anvil::ImageViewCreateInfo::create_2D(device_ptr,
                                                             in_image_ptr,
                                                             0,                 /*in_n_base_layer*/
                                                             0,                 /*in_n_base_mipmap_level*/
                                                             in_image_ptr->get_n_mipmaps(),                 /*in_n_mipmaps*/
                                                             format_aspects,
                                                             format,
                                                             Anvil::ComponentSwizzle::IDENTITY,
                                                             Anvil::ComponentSwizzle::IDENTITY,
                                                             Anvil::ComponentSwizzle::IDENTITY,
                                                             Anvil::ComponentSwizzle::IDENTITY);

    vkgl_assert(create_info_ptr != nullptr);

    result_ptr = Anvil::ImageView::create(std::move(create_info_ptr) );
    vkgl_assert(result_ptr != nullptr);

    #if defined(_DEBUG)
    {
        result_ptr->set_name_formatted("GL texture %d",
                                       in_id);
    }
    #endif

    return result_ptr;
}

Anvil::SamplerUniquePtr OpenGL::VKImageManager::create_vk_sampler(const GLuint&              in_id,
																			OpenGL::TimeMarker 		in_frontend_time_marker)
{
    FUN_ENTRY(DEBUG_DEPTH);
    
    auto frontend_texture_ptr = m_frontend_ptr->get_texture_manager_ptr();
    
    OpenGL::TextureTarget 									texture_target			= OpenGL::TextureTarget::Unknown;
	const std::vector<OpenGL::TextureMipStateUniquePtr>* texture_mip_states_ptr = nullptr;
    const OpenGL::TextureState* 							texture_state_ptr		= nullptr;
    {
        frontend_texture_ptr->get_texture_target(in_id,
    											&texture_target);
        frontend_texture_ptr->get_texture_mip_state_ptr(in_id,
        												&in_frontend_time_marker,
        												nullptr, /* out_layers_ptr */
        												&texture_mip_states_ptr);
        frontend_texture_ptr->get_texture_state_ptr(in_id,
    												&in_frontend_time_marker,
    												&texture_state_ptr);
        
        vkgl_assert(texture_target 			!= OpenGL::TextureTarget::Unknown);
        vkgl_assert(texture_mip_states_ptr != nullptr);
        vkgl_assert(texture_state_ptr 		!= nullptr);
    }
    
    Anvil::SamplerCreateInfoUniquePtr create_info_ptr;
    auto                             device_ptr            = m_backend_ptr->get_device_ptr();
    Anvil::SamplerUniquePtr           result_ptr;
	
    create_info_ptr = Anvil::SamplerCreateInfo::create(device_ptr,
                                                 OpenGL::VKUtils::get_anvil_filter_for_mag_filter			(texture_state_ptr->mag_filter),
                                                 OpenGL::VKUtils::get_anvil_filter_for_min_filter			(texture_state_ptr->min_filter),
                                                 OpenGL::VKUtils::get_anvil_mipmap_mode_for_min_filter(texture_state_ptr->min_filter),
                                                 OpenGL::VKUtils::get_anvil_sampler_address_mode_for_texture_wrap_mode(texture_state_ptr->wrap_s),
                                                 OpenGL::VKUtils::get_anvil_sampler_address_mode_for_texture_wrap_mode(texture_state_ptr->wrap_t),
                                                 OpenGL::VKUtils::get_anvil_sampler_address_mode_for_texture_wrap_mode(texture_state_ptr->wrap_r),
                                                 texture_state_ptr->lod_bias,
                                                 0.0,				/*max_anisotropy*/
                                                 texture_state_ptr->compare_mode == OpenGL::TextureCompareMode::None ? false : true,
                                                 OpenGL::VKUtils::get_anvil_compare_op_for_compare_function(texture_state_ptr->compare_function),
                                                 texture_state_ptr->min_lod,
                                                 texture_state_ptr->max_lod,
                                                 texture_state_ptr->border_color[0] == 0.0 ? Anvil::BorderColor::FLOAT_OPAQUE_BLACK : Anvil::BorderColor::FLOAT_OPAQUE_WHITE,
                                                 false,				/*use_unnormalized_coordinates*/
                                                 Anvil::MTSafety::INHERIT_FROM_PARENT_DEVICE);

    vkgl_assert(create_info_ptr != nullptr);

    result_ptr = Anvil::Sampler::create(std::move(create_info_ptr) );
    vkgl_assert(result_ptr != nullptr);

    #if defined(_DEBUG)
    {
        result_ptr->set_name_formatted("GL texture %d",
                                       in_id);
    }
    #endif

    return result_ptr;
}

bool OpenGL::VKImageManager::destroy_object(const GLuint&             in_id,
                                             const OpenGL::TimeMarker& in_frontend_object_creation_time)
{
    FUN_ENTRY(DEBUG_DEPTH);
    
    /* NOTE: This function is only called from within the rendering context thread */
    std::lock_guard<std::mutex> lock           (m_mutex);
    const auto                  image_map_key (ImageMapKey(in_id, in_frontend_object_creation_time) );
    auto                        image_iterator(m_images.find(image_map_key) );
    bool                        result         (false);

    vkgl_assert(image_iterator != m_images.end() );
    if (image_iterator != m_images.end() )
    {
        /* Mark the image instance as destroyed. */
        auto image_data_ptr = image_iterator->second.get();

        vkgl_assert(!image_data_ptr->has_been_destroyed);
        image_data_ptr->has_been_destroyed = true;

        /* Check if no further references for the instance exist. If none do, go ahead and free the descriptor. */
        if (get_n_references(image_data_ptr) == 0)
        {
            m_images.erase(image_iterator);

            /* NOTE: image_data_ptr at this point is dead. */
        }
        else
        {
            /* Wait till the reference counter drops to 0. */
        }

        result = true;
    }

    return result;
}

uint32_t OpenGL::VKImageManager::get_n_references(const ImageData* in_image_data_ptr) const
{
    FUN_ENTRY(DEBUG_DEPTH);
    
    /* NOTE: This function assumes m_mutex is locked! */
    uint32_t result = 0;

    for (const auto& current_image_props : in_image_data_ptr->image_map)
    {
        result += static_cast<uint32_t>(current_image_props.second->reference_ptrs.size() );
    }

    return result;
}

OpenGL::TimeMarker OpenGL::VKImageManager::get_tot_image_time_marker(const GLuint&             in_id,
                                                                       const OpenGL::TimeMarker& in_frontend_object_creation_time) const
{
    FUN_ENTRY(DEBUG_DEPTH);
    
    std::lock_guard<std::mutex> lock                 (m_mutex);
    const auto                  image_map_key       (ImageMapKey(in_id, in_frontend_object_creation_time) );
    auto                        image_props_iterator(m_images.find(image_map_key) );

    vkgl_assert(image_props_iterator != m_images.end() );

    return image_props_iterator->second->tot_image_time_marker;
}

void OpenGL::VKImageManager::on_reference_created(ImageData*                in_image_data_ptr,
                                                   OpenGL::VKImageReference* in_reference_ptr)
{
    FUN_ENTRY(DEBUG_DEPTH);
    
    /* NOTE: m_mutex is assumed to be locked when this func is called */
    auto image_iterator = in_image_data_ptr->image_map.find(in_reference_ptr->get_payload().backend_image_creation_time_marker);

    if (image_iterator != in_image_data_ptr->image_map.end() )
    {
        image_iterator->second->reference_ptrs.push_back(in_reference_ptr);
    }
}

void OpenGL::VKImageManager::on_reference_destroyed(ImageData*                in_image_data_ptr,
                                                     OpenGL::VKImageReference* in_reference_ptr)
{
    FUN_ENTRY(DEBUG_DEPTH);
    
    std::lock_guard<std::mutex> lock           (m_mutex);
    auto                        image_iterator(in_image_data_ptr->image_map.find(in_reference_ptr->get_payload().backend_image_creation_time_marker) );

    if (image_iterator != in_image_data_ptr->image_map.end() )
    {
        auto ref_iterator = std::find(image_iterator->second->reference_ptrs.begin(),
                                      image_iterator->second->reference_ptrs.end(),
                                      in_reference_ptr);

        if (ref_iterator != image_iterator->second->reference_ptrs.end() )
        {
            image_iterator->second->reference_ptrs.erase(ref_iterator);
        }
    }

	{
    	auto current_image_iterator = in_image_data_ptr->image_map.begin();
    	
    	while (current_image_iterator->first != in_image_data_ptr->image_map.rbegin()->first)
    	{
    		if (current_image_iterator->second->reference_ptrs.size() == 0)
    		{
    			in_image_data_ptr->image_map.erase(current_image_iterator);
    		}
    		
        	current_image_iterator = in_image_data_ptr->image_map.begin();
    	}
	}

    if (get_n_references(in_image_data_ptr)   == 0 &&
        in_image_data_ptr->has_been_destroyed)
    {
        /* This image can be safely released. */
        const auto key             = ImageMapKey  (in_reference_ptr->get_payload().id,
                                                    in_reference_ptr->get_payload().frontend_object_creation_time_marker);
        auto       object_iterator = m_images.find(key);

        vkgl_assert(object_iterator != m_images.end() );
        if (object_iterator != m_images.end() )
        {
            m_images.erase(object_iterator);
        }

        /* NOTE: in_image_data_ptr is dead at this point. */
    }
}

