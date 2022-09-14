/* VKGL (c) 2018 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/macros.h"
#include "OpenGL/backend/vk_utils.h"
#include "OpenGL/frontend/gl_program_manager.h"
#include "OpenGL/frontend/gl_state_manager.h"
#include "OpenGL/frontend/gl_vao_manager.h"
#include "OpenGL/frontend/gl_formats.h"

OpenGL::GLContextStateBindingReferencesUniquePtr OpenGL::VKUtils::create_gl_context_state_binding_references(const OpenGL::IContextObjectManagers*  in_frontend_managers_ptr,
                                                                                                             const OpenGL::GLContextStateReference* in_context_state_reference_ptr)
{
    FUN_ENTRY(DEBUG_DEPTH);
    
    OpenGL::GLContextStateBindingReferencesUniquePtr result_ptr          = OpenGL::GLContextStateBindingReferencesUniquePtr (nullptr,
                                                                                                                             std::default_delete<OpenGL::GLContextStateBindingReferences>() );
    auto                                             framebuffer_manager_ptr = in_frontend_managers_ptr->get_framebuffer_manager_ptr();
    auto                                             renderbuffer_manager_ptr = in_frontend_managers_ptr->get_renderbuffer_manager_ptr();
    auto                                             program_manager_ptr = in_frontend_managers_ptr->get_program_manager_ptr();
    auto                                             state_manager_ptr   = in_frontend_managers_ptr->get_state_manager_ptr  ();
    const auto                                       state_ptr           = state_manager_ptr->get_state                     (in_context_state_reference_ptr->get_payload().time_marker);
    auto                                             vao_manager_ptr     = in_frontend_managers_ptr->get_vao_manager_ptr    ();

    if (state_ptr == nullptr)
    {
        vkgl_assert(state_ptr != nullptr);

        goto end;
    }

    {
        vkgl_assert(state_ptr->program_proxy_reference_ptr 		!= nullptr);
        vkgl_assert(state_ptr->vao_proxy_reference_ptr 			!= nullptr);
        
        auto program_reference_ptr = program_manager_ptr->acquire_current_latest_snapshot_reference(state_ptr->program_proxy_reference_ptr->get_payload().id);
        auto vao_reference_ptr     = vao_manager_ptr->acquire_current_latest_snapshot_reference    (state_ptr->vao_proxy_reference_ptr->get_payload().id);

        vkgl_assert(program_reference_ptr 			!= nullptr);
        vkgl_assert(vao_reference_ptr     			!= nullptr);

        result_ptr.reset(
            new OpenGL::GLContextStateBindingReferences(std::move(program_reference_ptr),
                                                        std::move(vao_reference_ptr) )
        );
        vkgl_assert(result_ptr != nullptr);
    }

end:
    return result_ptr;
}

Anvil::CompareOp OpenGL::VKUtils::get_anvil_compare_op_for_depth_function(const OpenGL::DepthFunction& in_depth_func)
{
    FUN_ENTRY(DEBUG_DEPTH);
    
    Anvil::CompareOp result = Anvil::CompareOp::UNKNOWN;

    switch (in_depth_func)
    {
        case OpenGL::DepthFunction::Always:   result = Anvil::CompareOp::ALWAYS;           break;
        case OpenGL::DepthFunction::Equal:    result = Anvil::CompareOp::EQUAL;            break;
        case OpenGL::DepthFunction::GEqual:   result = Anvil::CompareOp::GREATER_OR_EQUAL; break;
        case OpenGL::DepthFunction::Greater:  result = Anvil::CompareOp::GREATER;          break;
        case OpenGL::DepthFunction::LEqual:   result = Anvil::CompareOp::LESS_OR_EQUAL;    break;
        case OpenGL::DepthFunction::Less:     result = Anvil::CompareOp::LESS;             break;
        case OpenGL::DepthFunction::Never:    result = Anvil::CompareOp::NEVER;            break;
        case OpenGL::DepthFunction::NotEqual: result = Anvil::CompareOp::NOT_EQUAL;        break;

        default:
        {
            vkgl_assert_fail();
        }
    }

    return result;
}

Anvil::CompareOp OpenGL::VKUtils::get_anvil_compare_op_for_stencil_function(const OpenGL::StencilFunction& in_stencil_func)
{
    FUN_ENTRY(DEBUG_DEPTH);
    
    Anvil::CompareOp result = Anvil::CompareOp::UNKNOWN;

    switch (in_stencil_func)
    {
        case OpenGL::StencilFunction::Always:   result = Anvil::CompareOp::ALWAYS;           break;
        case OpenGL::StencilFunction::Equal:    result = Anvil::CompareOp::EQUAL;            break;
        case OpenGL::StencilFunction::GEqual:   result = Anvil::CompareOp::GREATER_OR_EQUAL; break;
        case OpenGL::StencilFunction::Greater:  result = Anvil::CompareOp::GREATER;          break;
        case OpenGL::StencilFunction::LEqual:   result = Anvil::CompareOp::LESS_OR_EQUAL;    break;
        case OpenGL::StencilFunction::Less:     result = Anvil::CompareOp::LESS;             break;
        case OpenGL::StencilFunction::Never:    result = Anvil::CompareOp::NEVER;            break;
        case OpenGL::StencilFunction::NotEqual: result = Anvil::CompareOp::NOT_EQUAL;        break;

        default:
        {
            vkgl_assert_fail();
        }
    }

    return result;
}

Anvil::CullModeFlags OpenGL::VKUtils::get_anvil_cull_mode_flags_for_cull_face_mode(const OpenGL::CullMode& in_cull_face_mode)
{
    FUN_ENTRY(DEBUG_DEPTH);
    
    Anvil::CullModeFlags result = Anvil::CullModeFlagBits::NONE;

    switch (in_cull_face_mode)
    {
        case OpenGL::CullMode::Back:       result = Anvil::CullModeFlagBits::BACK_BIT;       break;
        case OpenGL::CullMode::Front:      result = Anvil::CullModeFlagBits::FRONT_AND_BACK; break;
        case OpenGL::CullMode::Front_Back: result = Anvil::CullModeFlagBits::FRONT_BIT;      break;

        default:
        {
            vkgl_assert_fail();
        }
    }

    return result;
}

Anvil::FrontFace OpenGL::VKUtils::get_anvil_front_face_for_front_face_orientation(const OpenGL::FrontFaceOrientation& in_front_face_orientation)
{
    FUN_ENTRY(DEBUG_DEPTH);
    
    Anvil::FrontFace result = Anvil::FrontFace::UNKNOWN;

    switch (in_front_face_orientation)
    {
        case OpenGL::FrontFaceOrientation::Clockwise:         result = Anvil::FrontFace::CLOCKWISE;         break;
        case OpenGL::FrontFaceOrientation::Counter_Clockwise: result = Anvil::FrontFace::COUNTER_CLOCKWISE; break;

        default:
        {
            vkgl_assert_fail();
        }
    }

    return result;
}

Anvil::LogicOp OpenGL::VKUtils::get_anvil_logic_op_for_logic_op_mode(const OpenGL::LogicOpMode& in_logic_op_mode)
{
    FUN_ENTRY(DEBUG_DEPTH);
    
    Anvil::LogicOp result = Anvil::LogicOp::UNKNOWN;

    switch (in_logic_op_mode)
    {
        case OpenGL::LogicOpMode::And:           result = Anvil::LogicOp::AND;           break;
        case OpenGL::LogicOpMode::And_Inverted:  result = Anvil::LogicOp::AND_INVERTED;  break;
        case OpenGL::LogicOpMode::And_Reverse:   result = Anvil::LogicOp::AND_REVERSE;   break;
        case OpenGL::LogicOpMode::Clear:         result = Anvil::LogicOp::CLEAR;         break;
        case OpenGL::LogicOpMode::Copy:          result = Anvil::LogicOp::COPY;          break;
        case OpenGL::LogicOpMode::Copy_Inverted: result = Anvil::LogicOp::COPY_INVERTED; break;
        case OpenGL::LogicOpMode::Equiv:         result = Anvil::LogicOp::EQUIVALENT;    break;
        case OpenGL::LogicOpMode::Invert:        result = Anvil::LogicOp::INVERT;        break;
        case OpenGL::LogicOpMode::Nand:          result = Anvil::LogicOp::NAND;          break;
        case OpenGL::LogicOpMode::Noop:          result = Anvil::LogicOp::NO_OP;         break;
        case OpenGL::LogicOpMode::Nor:           result = Anvil::LogicOp::NOR;           break;
        case OpenGL::LogicOpMode::Or:            result = Anvil::LogicOp::OR;            break;
        case OpenGL::LogicOpMode::Or_Inverted:   result = Anvil::LogicOp::OR_INVERTED;   break;
        case OpenGL::LogicOpMode::Or_Reverse:    result = Anvil::LogicOp::OR_REVERSE;    break;
        case OpenGL::LogicOpMode::Set:           result = Anvil::LogicOp::SET;           break;
        case OpenGL::LogicOpMode::Xor:           result = Anvil::LogicOp::XOR;           break;

        default:
        {
            vkgl_assert_fail();
        }
    }

    return result;
}

Anvil::PolygonMode OpenGL::VKUtils::get_anvil_polygon_mode_for_polygon_mode(const OpenGL::PolygonMode& in_polygon_mode)
{
    FUN_ENTRY(DEBUG_DEPTH);
    
    Anvil::PolygonMode result = Anvil::PolygonMode::UNKNOWN;

    switch (in_polygon_mode)
    {
        case OpenGL::PolygonMode::Fill:  result = Anvil::PolygonMode::FILL;  break;
        case OpenGL::PolygonMode::Line:  result = Anvil::PolygonMode::LINE;  break;
        case OpenGL::PolygonMode::Point: result = Anvil::PolygonMode::POINT; break;

        default:
        {
            vkgl_assert_fail();
        }
    }

    return result;
}

Anvil::PrimitiveTopology OpenGL::VKUtils::get_anvil_primitive_topology_for_draw_call_mode(const OpenGL::DrawCallMode& in_draw_call_mode)
{
    FUN_ENTRY(DEBUG_DEPTH);
    
    Anvil::PrimitiveTopology result = Anvil::PrimitiveTopology::UNKNOWN;

    switch (in_draw_call_mode)
    {
        case OpenGL::DrawCallMode::Lines:                    result = Anvil::PrimitiveTopology::LINE_LIST;                     break;
        case OpenGL::DrawCallMode::Lines_Adjacency:          result = Anvil::PrimitiveTopology::LINE_LIST_WITH_ADJACENCY;      break;
        case OpenGL::DrawCallMode::Line_Strip:               result = Anvil::PrimitiveTopology::LINE_STRIP;                    break;
        case OpenGL::DrawCallMode::Line_Strip_Adjacency:     result = Anvil::PrimitiveTopology::LINE_STRIP_WITH_ADJACENCY;     break;
        case OpenGL::DrawCallMode::Patches:                  result = Anvil::PrimitiveTopology::PATCH_LIST;                    break;
        case OpenGL::DrawCallMode::Points:                   result = Anvil::PrimitiveTopology::POINT_LIST;                    break;
        case OpenGL::DrawCallMode::Triangle_Fan:             result = Anvil::PrimitiveTopology::TRIANGLE_FAN;                  break;
        case OpenGL::DrawCallMode::Triangle_Strip:           result = Anvil::PrimitiveTopology::TRIANGLE_STRIP;                break;
        case OpenGL::DrawCallMode::Triangle_Strip_Adjacency: result = Anvil::PrimitiveTopology::TRIANGLE_STRIP_WITH_ADJACENCY; break;
        case OpenGL::DrawCallMode::Triangles:                result = Anvil::PrimitiveTopology::TRIANGLE_LIST;                 break;
        case OpenGL::DrawCallMode::Triangles_Adjacency:      result = Anvil::PrimitiveTopology::TRIANGLE_LIST_WITH_ADJACENCY;  break;

        case OpenGL::DrawCallMode::Line_Loop:
        {
            /* Not available in Vulkan. This will require some coding muscles to get to work. Deferring. */
            vkgl_not_implemented();

            break;
        }

        default:
        {
            vkgl_assert_fail();
        }
    }

    return result;
}

Anvil::StencilOp OpenGL::VKUtils::get_anvil_stencil_op_for_stencil_operation(const OpenGL::StencilOperation& in_stencil_op)
{
    FUN_ENTRY(DEBUG_DEPTH);
    
    Anvil::StencilOp result = Anvil::StencilOp::UNKNOWN;

    switch (in_stencil_op)
    {
        case OpenGL::StencilOperation::Decr:      result = Anvil::StencilOp::DECREMENT_AND_CLAMP; break;
        case OpenGL::StencilOperation::Decr_Wrap: result = Anvil::StencilOp::DECREMENT_AND_WRAP;  break;
        case OpenGL::StencilOperation::Incr:      result = Anvil::StencilOp::INCREMENT_AND_CLAMP; break;
        case OpenGL::StencilOperation::Incr_Wrap: result = Anvil::StencilOp::INCREMENT_AND_WRAP;  break;
        case OpenGL::StencilOperation::Invert:    result = Anvil::StencilOp::INVERT;              break;
        case OpenGL::StencilOperation::Keep:      result = Anvil::StencilOp::KEEP;                break;
        case OpenGL::StencilOperation::Replace:   result = Anvil::StencilOp::REPLACE;             break;
        case OpenGL::StencilOperation::Zero:      result = Anvil::StencilOp::ZERO;                break;

        default:
        {
            vkgl_assert_fail();
        }
    }

    return result;
}

Anvil::ImageUsageFlags OpenGL::VKUtils::get_image_usage_flags_for_gl_internal_format(const OpenGL::InternalFormat& in_internal_format_const)
{
    FUN_ENTRY(DEBUG_DEPTH);
    
    Anvil::ImageUsageFlags result 					(Anvil::ImageUsageFlagBits::NONE);
    OpenGL::InternalFormat in_internal_format 		(in_internal_format_const);
    bool 					is_color_internal_format(false);
    
    if (OpenGL::GLFormats::is_base_internal_format(in_internal_format) )
    {
    	in_internal_format = OpenGL::GLFormats::choose_sized_internal_format_for_base_internal_format(in_internal_format);
    }
    
    
    
    {
        uint32_t                   internal_format_size_ds    [2]  = {0, 0};
        uint32_t                   internal_format_size_rgba  [4]  = {0, 0, 0, 0};
        uint32_t                   internal_format_size_shared     = 0;
    
        if (!OpenGL::GLFormats::get_per_component_bit_size_for_sized_internal_format(in_internal_format,
                                                                                     internal_format_size_rgba,
                                                                                     internal_format_size_ds,
                                                                                    &internal_format_size_shared) )
        {
            vkgl_assert_fail();

            goto end;
        }
        
        if (internal_format_size_ds[0] == 0 &&
            internal_format_size_ds[1] == 0)
        {
            /* Internal format is a color format */
            vkgl_assert(internal_format_size_rgba[0] != 0 ||
                        internal_format_size_rgba[1] != 0 ||
                        internal_format_size_rgba[2] != 0 ||
                        internal_format_size_rgba[3] != 0);
			
			is_color_internal_format = true;
        }
        else
        {
            /* Internal format is a D/DS/S format */
            vkgl_assert(internal_format_size_ds[0] != 0 ||
                        internal_format_size_ds[1] != 0);
			
			is_color_internal_format = false;
        }
    }
    
    {
        result |= Anvil::ImageUsageFlagBits::TRANSFER_SRC_BIT;
        result |= Anvil::ImageUsageFlagBits::TRANSFER_DST_BIT;
        result |= Anvil::ImageUsageFlagBits::SAMPLED_BIT;
        //result |= Anvil::ImageUsageFlagBits::STORAGE_BIT;
        
        if (is_color_internal_format)
        {
            result |= Anvil::ImageUsageFlagBits::COLOR_ATTACHMENT_BIT;
        }
        else
        {
            result |= Anvil::ImageUsageFlagBits::DEPTH_STENCIL_ATTACHMENT_BIT;
        }
    }

end:
    return result;
}

Anvil::BufferUsageFlags OpenGL::VKUtils::get_buffer_usage_flags_for_gl_buffer(const uint32_t&             in_n_buffer_targets,
                                                                              const OpenGL::BufferTarget* in_buffer_targets_ptr)
{
    FUN_ENTRY(DEBUG_DEPTH);
    
    Anvil::BufferUsageFlags result = Anvil::BufferUsageFlagBits::NONE;

    vkgl_assert(in_buffer_targets_ptr != nullptr);

    for (uint32_t n_buffer_target = 0;
                  n_buffer_target < in_n_buffer_targets;
                ++n_buffer_target)
    {
        const auto& current_target = in_buffer_targets_ptr[n_buffer_target];

        switch (current_target)
        {
            case OpenGL::BufferTarget::Array_Buffer:         result |= Anvil::BufferUsageFlagBits::VERTEX_BUFFER_BIT;        break;
            case OpenGL::BufferTarget::Copy_Read_Buffer:     result |= Anvil::BufferUsageFlagBits::TRANSFER_SRC_BIT;         break;
            case OpenGL::BufferTarget::Copy_Write_Buffer:    result |= Anvil::BufferUsageFlagBits::TRANSFER_DST_BIT;         break;
            case OpenGL::BufferTarget::Element_Array_Buffer: result |= Anvil::BufferUsageFlagBits::INDEX_BUFFER_BIT;         break;
            case OpenGL::BufferTarget::Pixel_Pack_Buffer:    result |= Anvil::BufferUsageFlagBits::TRANSFER_DST_BIT;         break;
            case OpenGL::BufferTarget::Pixel_Unpack_Buffer:  result |= Anvil::BufferUsageFlagBits::TRANSFER_SRC_BIT;         break;
            case OpenGL::BufferTarget::Texture_Buffer:       result |= Anvil::BufferUsageFlagBits::UNIFORM_TEXEL_BUFFER_BIT; break;
            case OpenGL::BufferTarget::Uniform_Buffer:       result |= Anvil::BufferUsageFlagBits::UNIFORM_BUFFER_BIT;       break;

            case OpenGL::BufferTarget::Transform_Feedback_Buffer:
            {
                vkgl_not_implemented();

                break;
            }

            default:
            {
                vkgl_assert_fail();
            }
        }
    }

    return result;
}

Anvil::MemoryFeatureFlags OpenGL::VKUtils::get_memory_feature_flags_for_gl_buffer(const OpenGL::BufferUsage& in_buffer_usage)
{
    FUN_ENTRY(DEBUG_DEPTH);
    
    const bool is_dynamic = (in_buffer_usage == OpenGL::BufferUsage::Dynamic_Copy ||
                             in_buffer_usage == OpenGL::BufferUsage::Dynamic_Draw ||
                             in_buffer_usage == OpenGL::BufferUsage::Dynamic_Read);
    const bool is_static  = (in_buffer_usage == OpenGL::BufferUsage::Static_Copy  ||
                             in_buffer_usage == OpenGL::BufferUsage::Static_Draw  ||
                             in_buffer_usage == OpenGL::BufferUsage::Static_Read);
    const bool is_stream  = (in_buffer_usage == OpenGL::BufferUsage::Stream_Copy  ||
                             in_buffer_usage == OpenGL::BufferUsage::Stream_Draw  ||
                             in_buffer_usage == OpenGL::BufferUsage::Stream_Read);

    const bool is_copy = (in_buffer_usage == OpenGL::BufferUsage::Dynamic_Copy ||
                          in_buffer_usage == OpenGL::BufferUsage::Static_Copy  ||
                          in_buffer_usage == OpenGL::BufferUsage::Stream_Copy);
    const bool is_draw = (in_buffer_usage == OpenGL::BufferUsage::Dynamic_Draw ||
                          in_buffer_usage == OpenGL::BufferUsage::Static_Draw  ||
                          in_buffer_usage == OpenGL::BufferUsage::Stream_Draw);
    const bool is_read = (in_buffer_usage == OpenGL::BufferUsage::Dynamic_Read ||
                          in_buffer_usage == OpenGL::BufferUsage::Static_Read  ||
                          in_buffer_usage == OpenGL::BufferUsage::Stream_Read);

    Anvil::MemoryFeatureFlags result = Anvil::MemoryFeatureFlagBits::NONE;


    if (is_static)
    {
        /* Data is specified once by the app .. */
        if (is_draw)
        {
            /* ..and used many times for draw + image transfer ops */
            result = Anvil::MemoryFeatureFlagBits::DEVICE_LOCAL_BIT;
        }
        else
        if (is_read)
        {
            /* ..data is generated on-device, contents will be polled many times by the app  */
            result = Anvil::MemoryFeatureFlagBits::DEVICE_LOCAL_BIT | Anvil::MemoryFeatureFlagBits::MAPPABLE_BIT;
        }
        else
        if (is_copy)
        {
            /* ..data is generated on-device, and used for copy + image transfer ops for many times */
            result = Anvil::MemoryFeatureFlagBits::DEVICE_LOCAL_BIT;
        }
        else
        {
            vkgl_assert_fail();
        }
    }
    else
    if (is_stream)
    {
        /* Data is specified once by the app */
        if (is_draw)
        {
            /* ..and used for a few times for draw + image transfer ops */
            result = Anvil::MemoryFeatureFlagBits::DEVICE_LOCAL_BIT;
        }
        else
        if (is_read)
        {
            /* ..data is generated on-device, contents will be polled for a number of times by the app  */
            result = Anvil::MemoryFeatureFlagBits::DEVICE_LOCAL_BIT | Anvil::MemoryFeatureFlagBits::MAPPABLE_BIT;
        }
        else
        if (is_copy)
        {
            /* ..data is generated on-device, and used for a number of times for copy + image transfer ops */
            result = Anvil::MemoryFeatureFlagBits::DEVICE_LOCAL_BIT;
        }
        else
        {
            vkgl_assert_fail();
        }
    }
    else
    if (is_dynamic)
    {
        /* Data is specified many times */
        if (is_draw)
        {
            /* ..and used many times for draw + image transfer ops */
            result = Anvil::MemoryFeatureFlagBits::DEVICE_LOCAL_BIT | Anvil::MemoryFeatureFlagBits::MAPPABLE_BIT;
        }
        else
        if (is_read)
        {
            /* ..data is generated on-device, contents will be polled many times by the app  */
            result = Anvil::MemoryFeatureFlagBits::DEVICE_LOCAL_BIT | Anvil::MemoryFeatureFlagBits::MAPPABLE_BIT;
        }
        else
        if (is_copy)
        {
            /* ..data is generated on-device, and used many times for copy + image transfer ops */
            result = Anvil::MemoryFeatureFlagBits::DEVICE_LOCAL_BIT | Anvil::MemoryFeatureFlagBits::MAPPABLE_BIT;
        }
        else
        {
            vkgl_assert_fail();
        }
    }
    else
    {
        vkgl_assert_fail();
    }

    return result;
}

Anvil::Filter OpenGL::VKUtils::get_anvil_filter_for_mag_filter(const OpenGL::TextureMagFilter& in_mag_filter)
{
    FUN_ENTRY(DEBUG_DEPTH);
    
	auto result = Anvil::Filter::UNKNOWN;
	
	switch (in_mag_filter)
	{
		case OpenGL::TextureMagFilter::Nearest:		result = Anvil::Filter::NEAREST;		break;
		case OpenGL::TextureMagFilter::Linear:		result = Anvil::Filter::LINEAR;			break;
		
		default:
        {
            vkgl_assert_fail();
        }
    }
    
    return result;
}

Anvil::Filter OpenGL::VKUtils::get_anvil_filter_for_min_filter(const OpenGL::TextureMinFilter& in_min_filter)
{
    FUN_ENTRY(DEBUG_DEPTH);
    
	auto result = Anvil::Filter::UNKNOWN;
	
	switch (in_min_filter)
	{
		case OpenGL::TextureMinFilter::Nearest:
		case OpenGL::TextureMinFilter::Nearest_Mipmap_Nearest:
		case OpenGL::TextureMinFilter::Linear_Mipmap_Nearest:
																		result = Anvil::Filter::NEAREST;		break;
		case OpenGL::TextureMinFilter::Linear:
		case OpenGL::TextureMinFilter::Nearest_Mipmap_Linear:
		case OpenGL::TextureMinFilter::Linear_Mipmap_Linear:
																		result = Anvil::Filter::LINEAR;		break;
		
		default:
        {
            vkgl_assert_fail();
        }
    }
    
    return result;
}

Anvil::SamplerMipmapMode OpenGL::VKUtils::get_anvil_mipmap_mode_for_min_filter(const OpenGL::TextureMinFilter& in_min_filter)
{
    FUN_ENTRY(DEBUG_DEPTH);
    
	auto result = Anvil::SamplerMipmapMode::UNKNOWN;
	
	switch (in_min_filter)
	{
		case OpenGL::TextureMinFilter::Nearest:
		case OpenGL::TextureMinFilter::Nearest_Mipmap_Nearest:
		case OpenGL::TextureMinFilter::Nearest_Mipmap_Linear:
																		result = Anvil::SamplerMipmapMode::NEAREST;		break;
		case OpenGL::TextureMinFilter::Linear:
		case OpenGL::TextureMinFilter::Linear_Mipmap_Nearest:
		case OpenGL::TextureMinFilter::Linear_Mipmap_Linear:
																		result = Anvil::SamplerMipmapMode::LINEAR;		break;
		
		default:
        {
            vkgl_assert_fail();
        }
    }
    
    return result;
}

Anvil::SamplerAddressMode OpenGL::VKUtils::get_anvil_sampler_address_mode_for_texture_wrap_mode(const OpenGL::TextureWrapMode& in_wrap_mode)
{
    FUN_ENTRY(DEBUG_DEPTH);
    
	auto result = Anvil::SamplerAddressMode::UNKNOWN;
	
	switch (in_wrap_mode)
	{
		case OpenGL::TextureWrapMode::Clamp_To_Border:		result = Anvil::SamplerAddressMode::CLAMP_TO_BORDER;		break;
		case OpenGL::TextureWrapMode::Clamp_To_Edge:		result = Anvil::SamplerAddressMode::CLAMP_TO_EDGE;		break;
		case OpenGL::TextureWrapMode::Mirror_Clamp_to_Edge:		result = Anvil::SamplerAddressMode::MIRROR_CLAMP_TO_EDGE;		break;
		case OpenGL::TextureWrapMode::Mirrored_Repeat:		result = Anvil::SamplerAddressMode::MIRRORED_REPEAT;		break;
		case OpenGL::TextureWrapMode::Repeat:		result = Anvil::SamplerAddressMode::REPEAT;		break;
		
		default:
        {
            vkgl_assert_fail();
        }
    }
    
    return result;
}

Anvil::CompareOp OpenGL::VKUtils::get_anvil_compare_op_for_compare_function(const OpenGL::TextureCompareFunction& in_compare_function)
{
    FUN_ENTRY(DEBUG_DEPTH);
    
	auto result = Anvil::CompareOp::UNKNOWN;
	
	switch (in_compare_function)
	{
		case OpenGL::TextureCompareFunction::Always:		result = Anvil::CompareOp::ALWAYS;		break;
		case OpenGL::TextureCompareFunction::Equal:		result = Anvil::CompareOp::EQUAL;		break;
		case OpenGL::TextureCompareFunction::GEqual:		result = Anvil::CompareOp::EQUAL;		break;
		case OpenGL::TextureCompareFunction::Greater:		result = Anvil::CompareOp::GREATER;		break;
		case OpenGL::TextureCompareFunction::LEqual:		result = Anvil::CompareOp::EQUAL;		break;
		case OpenGL::TextureCompareFunction::Less:		result = Anvil::CompareOp::LESS;		break;
		case OpenGL::TextureCompareFunction::Never:		result = Anvil::CompareOp::NEVER;		break;
		case OpenGL::TextureCompareFunction::NotEqual:		result = Anvil::CompareOp::NOT_EQUAL;		break;
		
		default:
        {
            vkgl_assert_fail();
        }
    }
    
    return result;
}

