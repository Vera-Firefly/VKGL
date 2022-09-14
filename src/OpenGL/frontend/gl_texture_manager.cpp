/* VKGL (c) 2018 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/macros.h"
#include "OpenGL/frontend/gl_texture_manager.h"
#include "OpenGL/converters.h"
#include "OpenGL/utils_enum.h"

OpenGL::GLTextureManager::Texture::Texture()
{
    texture_target = OpenGL::TextureTarget::Unknown;
    
    state_ptr.reset(new TextureState(OpenGL::TextureMinFilter::Nearest_Mipmap_Linear,
    									OpenGL::TextureWrapMode::Repeat,
    									OpenGL::TextureWrapMode::Repeat,
    									OpenGL::TextureWrapMode::Repeat) );
	
	vkgl_assert(state_ptr != nullptr);
	
	{
    	layer_data[0].reset(
            new std::vector<TextureMipStateUniquePtr>()
        );
        
        vkgl_assert(layer_data[0] != nullptr);
        
    	{
            layer_data.at(0)->resize(state_ptr->max_level + 1);
            
            for (auto& current_texture_mip_state_ptr : *layer_data.at(0) )
            {
                if (current_texture_mip_state_ptr == nullptr)
                {
                    TextureMipStateUniquePtr new_texture_mip_state_ptr
                    	(new OpenGL::TextureMipState(OpenGL::InternalFormat::Unknown,
                                                        0,
                                                        0,
                                                        0,
                                                        0,
                                                        false)
                    	);
                	
                	current_texture_mip_state_ptr = std::move(new_texture_mip_state_ptr);
            	}
        	}
    	}
    }
}

OpenGL::GLTextureManager::Texture::Texture(const OpenGL::GLTextureManager::Texture& in_texture)
{
    set_from_texture_ptr(&in_texture);
}

OpenGL::GLTextureManager::Texture& OpenGL::GLTextureManager::Texture::operator=(const OpenGL::GLTextureManager::Texture& in_texture)
{
    set_from_texture_ptr(&in_texture);

    return *this;
}

void OpenGL::GLTextureManager::Texture::set_from_texture_ptr(const Texture* in_texture_ptr)
{
    texture_target = in_texture_ptr->texture_target;

	if (in_texture_ptr->state_ptr == nullptr)
    {
    	vkgl_assert(in_texture_ptr->state_ptr != nullptr);
    	
    	state_ptr.reset(new TextureState(OpenGL::TextureMinFilter::Nearest_Mipmap_Linear,
    									OpenGL::TextureWrapMode::Repeat,
    									OpenGL::TextureWrapMode::Repeat,
    									OpenGL::TextureWrapMode::Repeat) );
    }
    else
    {
    	state_ptr.reset(new TextureState(*in_texture_ptr->state_ptr) );
    }
    
    for (const auto& layer_index_to_mips : in_texture_ptr->layer_data)
    {
        if (layer_index_to_mips.second != nullptr)
        {
            layer_data[layer_index_to_mips.first].reset(
                new std::vector<TextureMipStateUniquePtr>()
            );
    
            auto& current_mip_state_vec_ptr = layer_data.at(layer_index_to_mips.first);
    
            for (const auto& current_mip_ptr : *layer_index_to_mips.second)
            {
                current_mip_state_vec_ptr->push_back(
                    OpenGL::TextureMipStateUniquePtr(new OpenGL::TextureMipState(*current_mip_ptr) )
                );
            }
        }
        else
        {
            layer_data[layer_index_to_mips.first].reset();
        }
    }
}

OpenGL::GLTextureManager::GLTextureManager(const IGLLimits* in_limits_ptr)
    :GLObjectManager(1,    /* in_first_valid_nondefault_id */
                     true /* in_expose_default_object     */),
     m_limits_ptr   (in_limits_ptr)
{
    FUN_ENTRY(DEBUG_DEPTH);
    
    vkgl_assert(in_limits_ptr != nullptr);

    m_property_to_base_type =
    {
        {OpenGL::TextureProperty::Depth_Stencil_Texture_Mode, OpenGL::GetSetArgumentType::DepthStencilTextureModeVKGL},
        {OpenGL::TextureProperty::Texture_Base_Level,         OpenGL::GetSetArgumentType::Int},
        {OpenGL::TextureProperty::Texture_Compare_Func,       OpenGL::GetSetArgumentType::TextureCompareFunctionVKGL},
        {OpenGL::TextureProperty::Texture_Compare_Mode,       OpenGL::GetSetArgumentType::TextureCompareModeVKGL},
        {OpenGL::TextureProperty::Texture_Lod_Bias,           OpenGL::GetSetArgumentType::Float},
        {OpenGL::TextureProperty::Texture_Mag_Filter,         OpenGL::GetSetArgumentType::TextureMagFilterVKGL},
        {OpenGL::TextureProperty::Texture_Max_Level,          OpenGL::GetSetArgumentType::Int},
        {OpenGL::TextureProperty::Texture_Max_Lod,            OpenGL::GetSetArgumentType::Float},
        {OpenGL::TextureProperty::Texture_Min_Filter,         OpenGL::GetSetArgumentType::TextureMinFilterVKGL},
        {OpenGL::TextureProperty::Texture_Min_Lod,            OpenGL::GetSetArgumentType::Float},
        {OpenGL::TextureProperty::Texture_Swizzle_A,          OpenGL::GetSetArgumentType::TextureSwizzleVKGL},
        {OpenGL::TextureProperty::Texture_Swizzle_B,          OpenGL::GetSetArgumentType::TextureSwizzleVKGL},
        {OpenGL::TextureProperty::Texture_Swizzle_G,          OpenGL::GetSetArgumentType::TextureSwizzleVKGL},
        {OpenGL::TextureProperty::Texture_Swizzle_R,          OpenGL::GetSetArgumentType::TextureSwizzleVKGL},
        {OpenGL::TextureProperty::Texture_Wrap_R,             OpenGL::GetSetArgumentType::TextureWrapModeVKGL},
        {OpenGL::TextureProperty::Texture_Wrap_S,             OpenGL::GetSetArgumentType::TextureWrapModeVKGL},
        {OpenGL::TextureProperty::Texture_Wrap_T,             OpenGL::GetSetArgumentType::TextureWrapModeVKGL}
    };
}

OpenGL::GLTextureManager::~GLTextureManager()
{
    FUN_ENTRY(DEBUG_DEPTH);
    
    /* Stub - everything is handled by the base class. */
}

std::unique_ptr<void, std::function<void(void*)> > OpenGL::GLTextureManager::clone_internal_data_object(const void* in_ptr,
                                                                                                        const bool& in_convert_from_proxy_to_nonproxy)
{
    std::unique_ptr<void, std::function<void(void*)> > result_ptr(nullptr,
                                                                  [](void* in_ptr){delete reinterpret_cast<Texture*>(in_ptr); });

    /* NOTE: Proxy->non-proxy conversion has no meaning for GL textures, as we only cache texture state properties,
     *       not actual object references */
    ANVIL_REDUNDANT_ARGUMENT_CONST(in_convert_from_proxy_to_nonproxy);

    result_ptr.reset(
        new Texture(*reinterpret_cast<const Texture*>(in_ptr) )
    );
    vkgl_assert(result_ptr != nullptr);

    return result_ptr;
}

void OpenGL::GLTextureManager::copy_internal_data_object(const void* in_src_ptr,
                                                         void*       in_dst_ptr)
{
    *reinterpret_cast<Texture*>(in_dst_ptr) = *reinterpret_cast<const Texture*>(in_src_ptr);
}

OpenGL::GLTextureManagerUniquePtr OpenGL::GLTextureManager::create(const OpenGL::IGLLimits* in_limits_ptr)
{
    FUN_ENTRY(DEBUG_DEPTH);
    
    OpenGL::GLTextureManagerUniquePtr result_ptr;

    result_ptr.reset(
        new GLTextureManager(in_limits_ptr)
    );

    vkgl_assert(result_ptr != nullptr);
    if (result_ptr != nullptr)
    {
        if (!result_ptr->init() )
        {
            result_ptr.reset();
        }
        
        if (!result_ptr->mark_id_as_alive(0) )
        {
            result_ptr.reset();
        }
        
        vkgl_assert(result_ptr != nullptr);
        result_ptr->on_texture_bound_to_target(0,
        										OpenGL::TextureTarget::_3D);
    }

    return result_ptr;
}

std::unique_ptr<void, std::function<void(void*)> > OpenGL::GLTextureManager::create_internal_data_object()
{
    std::unique_ptr<void, std::function<void(void*)> > result_ptr(nullptr,
                                                                  [](void* in_ptr){delete reinterpret_cast<Texture*>(in_ptr); });

    result_ptr.reset(
        new Texture()
    );

    vkgl_assert(result_ptr != nullptr);
    return result_ptr;
}

void OpenGL::GLTextureManager::get_texture_level_parameter(const GLuint&                       in_id,
                                                           const int32_t&                      in_level,
                                                           const OpenGL::TextureLevelProperty& in_pname,
                                                           const OpenGL::GetSetArgumentType&   in_arg_type,
                                                           void*                               out_params_ptr) const
{
    FUN_ENTRY(DEBUG_DEPTH);
    
    {
        std::unique_lock<std::mutex> lock                      (m_mutex);
        uint32_t 					current_layer				(0);
        auto                         texture_props_ptr         (get_texture_ptr(in_id,
                                                                                nullptr /* in_opt_time_marker_ptr */) );
    
        if (texture_props_ptr == nullptr)
        {
            vkgl_assert(texture_props_ptr != nullptr);
    
            goto end;
        }
    
        vkgl_assert(reinterpret_cast<const GLTextureManager*>(this)->get_general_object_props_ptr(in_id)->status == Status::Alive);
        vkgl_assert(texture_props_ptr->layer_data.size()                                                                 != 0);
        vkgl_assert(texture_props_ptr->layer_data.at(current_layer)->size()                                              > in_level);
        
        auto texture_mip_state_ptr(texture_props_ptr->layer_data.at(current_layer)->at(in_level).get() );
        
        GLint result_gl = 0;
        void* result_ptr = &result_gl;
    
        switch (in_pname)
        {
            case OpenGL::TextureLevelProperty::Texture_Internal_Format:		result_gl = OpenGL::Utils::get_gl_enum_for_internal_format(texture_mip_state_ptr->internal_format);	break;
            case OpenGL::TextureLevelProperty::Texture_Width:				result_gl = texture_mip_state_ptr->width;																break;
            case OpenGL::TextureLevelProperty::Texture_Height:				result_gl = texture_mip_state_ptr->height;																break;
            case OpenGL::TextureLevelProperty::Texture_Depth:				result_gl = texture_mip_state_ptr->depth;																break;
            
            default:
            {
                vkgl_assert_fail();
            }
        }
    
        OpenGL::Converters::convert(OpenGL::GetSetArgumentType::Int,
                                    result_ptr,
                                    1, /* in_n_vals */
                                    in_arg_type,
                                    out_params_ptr);
	}

end:
	;
}

void OpenGL::GLTextureManager::get_texture_parameter(const GLuint&                     in_id,
                                                     const OpenGL::TextureProperty&    in_property,
                                                     const OpenGL::GetSetArgumentType& in_arg_type,
                                                     void*                             out_arg_value_ptr) const
{
    FUN_ENTRY(DEBUG_DEPTH);
    
    {
        std::unique_lock<std::mutex> lock                      (m_mutex);
        const auto                   property_type_map_iterator(m_property_to_base_type.find(in_property) );
        auto                         texture_props_ptr         (get_texture_ptr(in_id,
                                                                                nullptr /* in_opt_time_marker_ptr */) );
    
        if (texture_props_ptr == nullptr)
        {
            vkgl_assert(texture_props_ptr != nullptr);
    
            goto end;
        }
    
        vkgl_assert(reinterpret_cast<const GLTextureManager*>(this)->get_general_object_props_ptr(in_id)->status == Status::Alive);
        vkgl_assert(texture_props_ptr->state_ptr                                                                 != nullptr);
        vkgl_assert(property_type_map_iterator                                                                   != m_property_to_base_type.end() );
        
        void* result_ptr = nullptr;
    
        switch (in_property)
        {
            case OpenGL::TextureProperty::Depth_Stencil_Texture_Mode: result_ptr = &texture_props_ptr->state_ptr->depth_stencil_texture_mode; break;
            case OpenGL::TextureProperty::Texture_Base_Level:         result_ptr = &texture_props_ptr->state_ptr->base_level;                 break;
            case OpenGL::TextureProperty::Texture_Compare_Func:       result_ptr = &texture_props_ptr->state_ptr->compare_function;           break;
            case OpenGL::TextureProperty::Texture_Compare_Mode:       result_ptr = &texture_props_ptr->state_ptr->compare_mode;               break;
            case OpenGL::TextureProperty::Texture_Lod_Bias:           result_ptr = &texture_props_ptr->state_ptr->lod_bias;                   break;
            case OpenGL::TextureProperty::Texture_Mag_Filter:         result_ptr = &texture_props_ptr->state_ptr->mag_filter;                 break;
            case OpenGL::TextureProperty::Texture_Max_Level:          result_ptr = &texture_props_ptr->state_ptr->max_level;                  break;
            case OpenGL::TextureProperty::Texture_Max_Lod:            result_ptr = &texture_props_ptr->state_ptr->max_lod;                    break;
            case OpenGL::TextureProperty::Texture_Min_Filter:         result_ptr = &texture_props_ptr->state_ptr->min_filter;                 break;
            case OpenGL::TextureProperty::Texture_Min_Lod:            result_ptr = &texture_props_ptr->state_ptr->min_lod;                    break;
            case OpenGL::TextureProperty::Texture_Swizzle_A:          result_ptr = &texture_props_ptr->state_ptr->swizzle_a;                  break;
            case OpenGL::TextureProperty::Texture_Swizzle_B:          result_ptr = &texture_props_ptr->state_ptr->swizzle_b;                  break;
            case OpenGL::TextureProperty::Texture_Swizzle_G:          result_ptr = &texture_props_ptr->state_ptr->swizzle_g;                  break;
            case OpenGL::TextureProperty::Texture_Swizzle_R:          result_ptr = &texture_props_ptr->state_ptr->swizzle_r;                  break;
            case OpenGL::TextureProperty::Texture_Wrap_R:             result_ptr = &texture_props_ptr->state_ptr->wrap_r;                     break;
            case OpenGL::TextureProperty::Texture_Wrap_S:             result_ptr = &texture_props_ptr->state_ptr->wrap_s;                     break;
            case OpenGL::TextureProperty::Texture_Wrap_T:             result_ptr = &texture_props_ptr->state_ptr->wrap_t;                     break;
    
            default:
            {
                vkgl_assert_fail();
            }
        }
    
        OpenGL::Converters::convert(property_type_map_iterator->second,
                                    result_ptr,
                                    1, /* in_n_vals */
                                    in_arg_type,
                                    out_arg_value_ptr);
	}

end:
	;
}

bool OpenGL::GLTextureManager::get_texture_target(const GLuint&                     in_id,
													OpenGL::TextureTarget*		out_target_ptr) const
{
    FUN_ENTRY(DEBUG_DEPTH);
    
	auto texture_ptr = get_texture_ptr(in_id,
                                     nullptr /* in_opt_time_marker_ptr */);
    bool result     = false;

    vkgl_assert(texture_ptr != nullptr);
    if (texture_ptr != nullptr)
    {
        *out_target_ptr = texture_ptr->texture_target;
        result         = true;
    }

    return result;
}

bool OpenGL::GLTextureManager::get_texture_state_ptr(const GLuint&                     in_id,
                                                       const OpenGL::TimeMarker*         in_opt_time_marker_ptr,
                                                       const OpenGL::TextureState**       out_state_ptr) const
{
    auto texture_ptr = get_texture_ptr(in_id,
                                     in_opt_time_marker_ptr);
    bool result     = false;

    vkgl_assert(texture_ptr != nullptr);
    if (texture_ptr != nullptr)
    {
        *out_state_ptr = texture_ptr->state_ptr.get();
        result         = true;
    }

    return result;
}

bool OpenGL::GLTextureManager::get_texture_mip_state_ptr(const GLuint&                     in_id,
                                                       const OpenGL::TimeMarker*         in_opt_time_marker_ptr,
                                                       uint32_t*         					out_n_layers_ptr,
                                                       const std::vector<TextureMipStateUniquePtr>** out_states_ptr) const
{
    auto texture_ptr = get_texture_ptr(in_id,
                                     in_opt_time_marker_ptr);
    bool result     = false;

    vkgl_assert(texture_ptr != nullptr);
    if (texture_ptr != nullptr)
    {
        if (out_n_layers_ptr != 0)
        {
            *out_n_layers_ptr = texture_ptr->layer_data.rbegin()->first;
        }
        
        if (out_states_ptr != 0)
        {
            *out_states_ptr = texture_ptr->layer_data.at(0).get();
        }
        
        result         = true;
    }

    return result;
}

const OpenGL::GLTextureManager::Texture* OpenGL::GLTextureManager::get_texture_ptr(const GLuint&             in_id,
                                                                                   const OpenGL::TimeMarker* in_opt_time_marker_ptr) const
{
    return reinterpret_cast<const OpenGL::GLTextureManager::Texture*>(get_internal_object_props_ptr(in_id,
                                                                                                    in_opt_time_marker_ptr) );
}

OpenGL::GLTextureManager::Texture* OpenGL::GLTextureManager::get_texture_ptr(const GLuint&             in_id,
                                                             const OpenGL::TimeMarker* in_opt_time_marker_ptr)
{
    return reinterpret_cast<OpenGL::GLTextureManager::Texture*>(get_internal_object_props_ptr(in_id,
                                                                                              in_opt_time_marker_ptr) );
}

void OpenGL::GLTextureManager::on_texture_bound_to_target(const GLuint&                in_id,
                                                          const OpenGL::TextureTarget& in_target)
{
    FUN_ENTRY(DEBUG_DEPTH);
    
    {
        std::unique_lock<std::mutex> lock             (m_mutex);
        auto                         texture_props_ptr(get_texture_ptr(in_id,
                                                                       nullptr /* in_opt_time_marker_ptr */) );

        if (texture_props_ptr == nullptr)
        {
            vkgl_assert(texture_props_ptr != nullptr);

            goto end;
        }

        if (texture_props_ptr->texture_target == OpenGL::TextureTarget::Unknown)
        {
            texture_props_ptr->texture_target = in_target;

            update_last_modified_time(in_id);
        }
        else
        {
            vkgl_assert(texture_props_ptr->texture_target == in_target);
        }
    }

end:
    ;
}

void OpenGL::GLTextureManager::set_texture_parameter(const GLuint&                     in_id,
                                                     const OpenGL::TextureProperty&    in_property,
                                                     const OpenGL::GetSetArgumentType& in_arg_type,
                                                     const void*                       in_arg_value_ptr)
{
    FUN_ENTRY(DEBUG_DEPTH);
    
    vkgl_assert(m_property_to_base_type.find(in_property) != m_property_to_base_type.end() );

    {
        bool                         is_redundant_call         (false);
        std::unique_lock<std::mutex> lock                      (m_mutex);
        const auto                   property_type_map_iterator(m_property_to_base_type.find(in_property) );
        auto                         texture_props_ptr         (get_texture_ptr(in_id,
                                                                                nullptr /* in_opt_time_marker_ptr */) );

        if (texture_props_ptr == nullptr)
        {
            vkgl_assert(texture_props_ptr != nullptr);

            goto end;
        }

        vkgl_assert(reinterpret_cast<const GLTextureManager*>(this)->get_general_object_props_ptr(in_id)->status == Status::Alive);
        vkgl_assert(texture_props_ptr->state_ptr                                                                 != nullptr);
        vkgl_assert(property_type_map_iterator                                                                   != m_property_to_base_type.end() );

        /* Determine redundancy status of this call */

        if (in_arg_type == property_type_map_iterator->second)
        {
            switch (in_property)
            {
                case OpenGL::TextureProperty::Depth_Stencil_Texture_Mode: is_redundant_call = (*reinterpret_cast<const OpenGL::DepthStencilTextureMode*>(in_arg_value_ptr) == texture_props_ptr->state_ptr->depth_stencil_texture_mode); break;
                case OpenGL::TextureProperty::Texture_Base_Level:         is_redundant_call = (*reinterpret_cast<const int32_t*>                        (in_arg_value_ptr) == texture_props_ptr->state_ptr->base_level);                 break;
                case OpenGL::TextureProperty::Texture_Compare_Func:       is_redundant_call = (*reinterpret_cast<const OpenGL::TextureCompareFunction*> (in_arg_value_ptr) == texture_props_ptr->state_ptr->compare_function);           break;
                case OpenGL::TextureProperty::Texture_Compare_Mode:       is_redundant_call = (*reinterpret_cast<const OpenGL::TextureCompareMode*>     (in_arg_value_ptr) == texture_props_ptr->state_ptr->compare_mode);               break;
                case OpenGL::TextureProperty::Texture_Mag_Filter:         is_redundant_call = (*reinterpret_cast<const OpenGL::TextureMagFilter*>       (in_arg_value_ptr) == texture_props_ptr->state_ptr->mag_filter);                 break;
                case OpenGL::TextureProperty::Texture_Max_Level:          is_redundant_call = (*reinterpret_cast<const int32_t*>                        (in_arg_value_ptr) == texture_props_ptr->state_ptr->max_level);                  break;
                case OpenGL::TextureProperty::Texture_Min_Filter:         is_redundant_call = (*reinterpret_cast<const OpenGL::TextureMinFilter*>       (in_arg_value_ptr) == texture_props_ptr->state_ptr->min_filter);                 break;
                case OpenGL::TextureProperty::Texture_Swizzle_A:          is_redundant_call = (*reinterpret_cast<const OpenGL::TextureSwizzle*>         (in_arg_value_ptr) == texture_props_ptr->state_ptr->swizzle_a);                  break;
                case OpenGL::TextureProperty::Texture_Swizzle_B:          is_redundant_call = (*reinterpret_cast<const OpenGL::TextureSwizzle*>         (in_arg_value_ptr) == texture_props_ptr->state_ptr->swizzle_b);                  break;
                case OpenGL::TextureProperty::Texture_Swizzle_G:          is_redundant_call = (*reinterpret_cast<const OpenGL::TextureSwizzle*>         (in_arg_value_ptr) == texture_props_ptr->state_ptr->swizzle_g);                  break;
                case OpenGL::TextureProperty::Texture_Swizzle_R:          is_redundant_call = (*reinterpret_cast<const OpenGL::TextureSwizzle*>         (in_arg_value_ptr) == texture_props_ptr->state_ptr->swizzle_r);                  break;
                case OpenGL::TextureProperty::Texture_Wrap_R:             is_redundant_call = (*reinterpret_cast<const OpenGL::TextureWrapMode*>        (in_arg_value_ptr) == texture_props_ptr->state_ptr->wrap_r);                     break;
                case OpenGL::TextureProperty::Texture_Wrap_S:             is_redundant_call = (*reinterpret_cast<const OpenGL::TextureWrapMode*>        (in_arg_value_ptr) == texture_props_ptr->state_ptr->wrap_s);                     break;
                case OpenGL::TextureProperty::Texture_Wrap_T:             is_redundant_call = (*reinterpret_cast<const OpenGL::TextureWrapMode*>        (in_arg_value_ptr) == texture_props_ptr->state_ptr->wrap_t);                     break;

                case OpenGL::TextureProperty::Texture_Lod_Bias:           is_redundant_call = fabs(*reinterpret_cast<const float*>(in_arg_value_ptr) - texture_props_ptr->state_ptr->lod_bias) < 1e-5f; break;
                case OpenGL::TextureProperty::Texture_Max_Lod:            is_redundant_call = fabs(*reinterpret_cast<const float*>(in_arg_value_ptr) - texture_props_ptr->state_ptr->max_lod)  < 1e-5f; break;
                case OpenGL::TextureProperty::Texture_Min_Lod:            is_redundant_call = fabs(*reinterpret_cast<const float*>(in_arg_value_ptr) - texture_props_ptr->state_ptr->min_lod)  < 1e-5f; break;

                default:
                {
                    vkgl_assert_fail();
                }
            }
        }
        else
        {
            /* Types differ.. Take the slow path in order to avoid performing the data type conversion */
        }

        if (!is_redundant_call)
        {
            void* result_ptr = nullptr;

            switch (in_property)
            {
                case OpenGL::TextureProperty::Depth_Stencil_Texture_Mode: result_ptr = &texture_props_ptr->state_ptr->depth_stencil_texture_mode; break;
                case OpenGL::TextureProperty::Texture_Base_Level:         result_ptr = &texture_props_ptr->state_ptr->base_level;                 break;
                case OpenGL::TextureProperty::Texture_Compare_Func:       result_ptr = &texture_props_ptr->state_ptr->compare_function;           break;
                case OpenGL::TextureProperty::Texture_Compare_Mode:       result_ptr = &texture_props_ptr->state_ptr->compare_mode;               break;
                case OpenGL::TextureProperty::Texture_Lod_Bias:           result_ptr = &texture_props_ptr->state_ptr->lod_bias;                   break;
                case OpenGL::TextureProperty::Texture_Mag_Filter:         result_ptr = &texture_props_ptr->state_ptr->mag_filter;                 break;
                case OpenGL::TextureProperty::Texture_Max_Level:          result_ptr = &texture_props_ptr->state_ptr->max_level;                  break;
                case OpenGL::TextureProperty::Texture_Max_Lod:            result_ptr = &texture_props_ptr->state_ptr->max_lod;                    break;
                case OpenGL::TextureProperty::Texture_Min_Filter:         result_ptr = &texture_props_ptr->state_ptr->min_filter;                 break;
                case OpenGL::TextureProperty::Texture_Min_Lod:            result_ptr = &texture_props_ptr->state_ptr->min_lod;                    break;
                case OpenGL::TextureProperty::Texture_Swizzle_A:          result_ptr = &texture_props_ptr->state_ptr->swizzle_a;                  break;
                case OpenGL::TextureProperty::Texture_Swizzle_B:          result_ptr = &texture_props_ptr->state_ptr->swizzle_b;                  break;
                case OpenGL::TextureProperty::Texture_Swizzle_G:          result_ptr = &texture_props_ptr->state_ptr->swizzle_g;                  break;
                case OpenGL::TextureProperty::Texture_Swizzle_R:          result_ptr = &texture_props_ptr->state_ptr->swizzle_r;                  break;
                case OpenGL::TextureProperty::Texture_Wrap_R:             result_ptr = &texture_props_ptr->state_ptr->wrap_r;                     break;
                case OpenGL::TextureProperty::Texture_Wrap_S:             result_ptr = &texture_props_ptr->state_ptr->wrap_s;                     break;
                case OpenGL::TextureProperty::Texture_Wrap_T:             result_ptr = &texture_props_ptr->state_ptr->wrap_t;                     break;

                default:
                {
                    vkgl_assert_fail();
                }
            }

            OpenGL::Converters::convert(in_arg_type,
                                        in_arg_value_ptr,
                                        1, /* in_n_vals */
                                        property_type_map_iterator->second,
                                        result_ptr);

            {
            	if (in_property == OpenGL::TextureProperty::Texture_Max_Level)
            	{
                    texture_props_ptr->layer_data.at(0)->resize(texture_props_ptr->state_ptr->max_level + 1);
                    
                    for (auto& current_texture_mip_state_ptr : *texture_props_ptr->layer_data.at(0) )
                    {
                        if (current_texture_mip_state_ptr == nullptr)
                        {
                            TextureMipStateUniquePtr new_texture_mip_state_ptr
                            	(new OpenGL::TextureMipState(OpenGL::InternalFormat::Unknown,
                                                                0,
                                                                0,
                                                                0,
                                                                0,
                                                                false)
                            	);
                        	
                        	current_texture_mip_state_ptr = std::move(new_texture_mip_state_ptr);
                    	}
                	}
            	}
            }
            
            update_last_modified_time(in_id);
        }
    }

end:
    ;
}

void OpenGL::GLTextureManager::set_texture_mip_properties(const GLuint&                 in_id,
                                                          const int32_t&                in_level,
                                                          const OpenGL::InternalFormat& in_internalformat,
                                                          const uint32_t&               in_width,
                                                          const uint32_t&               in_height,
                                                          const uint32_t&               in_depth,
                                                          const int32_t&                in_border,
                                                          const uint32_t&               in_n_samples,
                                                          const bool&                   in_fixed_sample_locations)
{
    FUN_ENTRY(DEBUG_DEPTH);
    
    {
        std::unique_lock<std::mutex> lock             (m_mutex);
        uint32_t                     n_layers          (1);
        auto                         texture_props_ptr(get_texture_ptr(in_id,
                                                                       nullptr /* in_opt_time_marker_ptr */) );

        if (texture_props_ptr == nullptr)
        {
            vkgl_assert(texture_props_ptr != nullptr);

            goto end;
        }

        if (OpenGL::Utils::is_texture_target_arrayed(texture_props_ptr->texture_target) )
        {
            /* Determine index of the layer whose mip storage is being specified */
            const auto n_texture_target_dims = OpenGL::Utils::get_n_dimensions_for_texture_target(texture_props_ptr->texture_target);

            vkgl_assert(n_texture_target_dims > 1);

            switch (n_texture_target_dims)
            {
                case 2:
                {
                    n_layers      = in_height;

                    break;
                }

                case 3:
                {
                    n_layers     = in_depth;

                    break;
                }

                default:
                {
                    vkgl_assert_fail();
                }
            }
        }

        vkgl_assert(texture_props_ptr->texture_target                                                            != OpenGL::TextureTarget::Unknown);
        vkgl_assert(reinterpret_cast<const GLTextureManager*>(this)->get_general_object_props_ptr(in_id)->status == Status::Alive);

        {
            vkgl_assert(n_layers > 0);
        	
        	while (texture_props_ptr->layer_data.rbegin()->first != 0)
        	{
        		texture_props_ptr->layer_data.erase(texture_props_ptr->layer_data.rbegin()->first);
        	}
        	
        	texture_props_ptr->layer_data[n_layers].reset();
        }
        
        vkgl_assert(texture_props_ptr->layer_data.size()              > 0);
        vkgl_assert(texture_props_ptr->layer_data.at(0)->size() > static_cast<size_t>(in_level) );
        
        {
            bool is_redundant_call = false;

            vkgl_assert(texture_props_ptr->layer_data.at(0) != nullptr)
            if (texture_props_ptr->layer_data.at(0) != nullptr)
            {
                const auto& existing_mip_state_ptr = texture_props_ptr->layer_data.at(0)->at(in_level);

                is_redundant_call = (existing_mip_state_ptr->internal_format        == in_internalformat         &&
                                     existing_mip_state_ptr->width                  == in_width                  &&
                                     existing_mip_state_ptr->height                 == in_height              &&
                                     existing_mip_state_ptr->depth                  == in_depth               &&
                                     existing_mip_state_ptr->samples                == in_n_samples              &&
                                     existing_mip_state_ptr->fixed_sample_locations == in_fixed_sample_locations);
            }

            if (texture_props_ptr->layer_data.at(0) != nullptr)
            {
                const auto& existing_mip_state_ptr = texture_props_ptr->layer_data.at(0)->at(in_level);

                existing_mip_state_ptr->internal_format        = in_internalformat,
                existing_mip_state_ptr->width                  = in_width;
                existing_mip_state_ptr->height                 = in_height;
                existing_mip_state_ptr->depth                  = in_depth;
                existing_mip_state_ptr->samples                = in_n_samples;
                existing_mip_state_ptr->fixed_sample_locations = in_fixed_sample_locations;
            }

            if (!is_redundant_call)
            {
                update_last_modified_time(in_id);
            }
        }
    }

end:
    ;
}

