/* VKGL (c) 2018 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/macros.h"
#include "OpenGL/converters.h"
#include "OpenGL/backend/vk_spirv_manager.h"
#include "OpenGL/frontend/gl_program_manager.h"
#include "OpenGL/frontend/gl_reference.h"
#include "OpenGL/frontend/gl_shader_manager.h"
#include <algorithm>

OpenGL::GLProgramManager::Program::Program(OpenGL::GLShaderManager*                 in_frontend_shader_manager_ptr,
                                           const OpenGL::GLProgramManager::Program& in_program,
                                           const bool&                              in_should_convert_proxy_refs_to_nonproxy)
{
    FUN_ENTRY(DEBUG_DEPTH);
    
    /* The two members need extra handling .. */

    for (auto& current_attached_shader_reference_ptr : in_program.attached_shaders)
    {
        OpenGL::GLProgramReferenceUniquePtr new_reference_ptr;

        if (in_should_convert_proxy_refs_to_nonproxy)
        {
            new_reference_ptr = in_frontend_shader_manager_ptr->acquire_current_latest_snapshot_reference(current_attached_shader_reference_ptr->get_payload().id);
        }
        else
        {
            new_reference_ptr = current_attached_shader_reference_ptr->clone();
        }

        vkgl_assert(new_reference_ptr != nullptr);

        attached_shaders.push_back(
            std::move(new_reference_ptr)
        );
    }

    if (in_program.post_link_data_ptr != nullptr)
    {
        post_link_data_ptr.reset(new PostLinkData(*in_program.post_link_data_ptr) );
        vkgl_assert(post_link_data_ptr != nullptr);
    }

    /* Rest of the stuff is trivial. */
    cached_attribute_location_bindings = in_program.cached_attribute_location_bindings;
    cached_frag_data_locations         = in_program.cached_frag_data_locations;

    tf_buffer_mode        = in_program.tf_buffer_mode;
    tf_varyings           = in_program.tf_varyings;
    tf_varying_max_length = in_program.tf_varying_max_length;

    ub_index_to_ub_binding = in_program.ub_index_to_ub_binding;

    delete_status   = in_program.delete_status;
    validate_status = in_program.validate_status;

    spirv_blob_id = in_program.spirv_blob_id;
}

OpenGL::GLProgramManager::Program& OpenGL::GLProgramManager::Program::operator=(const OpenGL::GLProgramManager::Program& in_program)
{
    /* The two members need extra handling .. */
    attached_shaders.clear();

    for (auto& current_attached_shader_reference_ptr : in_program.attached_shaders)
    {
        auto new_reference_ptr = current_attached_shader_reference_ptr->clone();

        vkgl_assert(new_reference_ptr != nullptr);

        attached_shaders.push_back(
            std::move(new_reference_ptr)
        );
    }

    if (in_program.post_link_data_ptr != nullptr)
    {
        if (post_link_data_ptr == nullptr)
        {
            post_link_data_ptr.reset(new PostLinkData(*in_program.post_link_data_ptr) );
            vkgl_assert(post_link_data_ptr != nullptr);
        }
        else
        {
            *post_link_data_ptr = *in_program.post_link_data_ptr;
        }
    }
    else
    {
        post_link_data_ptr.reset();
    }

    /* Rest of the stuff is trivial. */
    cached_attribute_location_bindings = in_program.cached_attribute_location_bindings;
    cached_frag_data_locations         = in_program.cached_frag_data_locations;

    tf_buffer_mode        = in_program.tf_buffer_mode;
    tf_varyings           = in_program.tf_varyings;
    tf_varying_max_length = in_program.tf_varying_max_length;

    ub_index_to_ub_binding = in_program.ub_index_to_ub_binding;

    delete_status   = in_program.delete_status;
    validate_status = in_program.validate_status;

    spirv_blob_id = in_program.spirv_blob_id;

    return *this;
}

const OpenGL::PostLinkData* OpenGL::GLProgramManager::Program::get_post_link_data(IBackendGLCallbacks* in_backend_ptr) const
{
    FUN_ENTRY(DEBUG_DEPTH);
    
    if (spirv_blob_id      != UINT32_MAX &&
        post_link_data_ptr == nullptr)
    {
        /* Program is being linked in one of the worker threads. Block until the process finishes and we are assigned post-link struct instance */
        auto spirv_manager_ptr = in_backend_ptr->get_spirv_manager_ptr();

        spirv_manager_ptr->get_program_link_status(spirv_blob_id,
                                                   nullptr,  /* out_status_ptr   */
                                                   nullptr); /* out_link_log_ptr */

        vkgl_assert(post_link_data_ptr != nullptr);
    }

    return post_link_data_ptr.get();
}

OpenGL::GLProgramManager::GLProgramManager(OpenGL::IContextObjectManagers* in_frontend_object_managers_ptr,
                                           IBackendGLCallbacks*            in_backend_ptr)
    :GLObjectManager               (1,              /* in_first_valid_nondefault_id */
                                    true),          /* in_expose_default_object     */
     m_backend_ptr                 (in_backend_ptr),
     m_frontend_object_managers_ptr(in_frontend_object_managers_ptr)
{
    FUN_ENTRY(DEBUG_DEPTH);
    
    /*  Stub */
}

OpenGL::GLProgramManager::~GLProgramManager()
{
    FUN_ENTRY(DEBUG_DEPTH);
    
    /* Stub - everything is handled by the base class. */
}

bool OpenGL::GLProgramManager::attach_shader(const GLuint&              in_program,
                                             GLShaderReferenceUniquePtr in_shader_reference_ptr)
{
    FUN_ENTRY(DEBUG_DEPTH);
    
    auto program_ptr = get_program_ptr(in_program,
                                       nullptr); /* in_opt_time_marker_ptr */
    bool result      = false;

    if (program_ptr == nullptr)
    {
        vkgl_assert(program_ptr != nullptr);

        goto end;
    }

    program_ptr->attached_shaders.push_back( std::move(in_shader_reference_ptr) );

    update_last_modified_time(in_program);
    result = true;
end:
    return result;
}

bool OpenGL::GLProgramManager::cache_attribute_location_binding(const GLuint&   in_program,
                                                                const char*     in_name,
                                                                const uint32_t& in_index)
{
    FUN_ENTRY(DEBUG_DEPTH);
    
    auto program_ptr = get_program_ptr(in_program,
                                       nullptr); /* in_opt_time_marker_ptr */
    bool result      = false;

    if (program_ptr == nullptr)
    {
        vkgl_assert(program_ptr != nullptr);

        goto end;
    }

    if (program_ptr->cached_attribute_location_bindings.find(in_name) == program_ptr->cached_attribute_location_bindings.end() ||
        program_ptr->cached_attribute_location_bindings[in_name]      != in_index)
    {
        program_ptr->cached_attribute_location_bindings[in_name] = in_index;

        update_last_modified_time(in_program);
    }

    result = true;
end:
    return result;
}

bool OpenGL::GLProgramManager::cache_frag_data_location(const GLuint&   in_program,
                                                        const char*     in_name,
                                                        const uint32_t& in_fragment_color_output)
{
    FUN_ENTRY(DEBUG_DEPTH);
    
    auto program_ptr = get_program_ptr(in_program,
                                       nullptr); /* in_opt_time_marker_ptr */
    bool result      = false;

    if (program_ptr == nullptr)
    {
        vkgl_assert(program_ptr != nullptr);

        goto end;
    }

    if (program_ptr->cached_frag_data_locations.find(in_name) == program_ptr->cached_frag_data_locations.end() ||
        program_ptr->cached_frag_data_locations[in_name]      != in_fragment_color_output)
    {
        program_ptr->cached_frag_data_locations[in_name] = in_fragment_color_output;

        update_last_modified_time(in_program);
    }

    result = true;
end:
    return result;
}

std::unique_ptr<void, std::function<void(void*)> > OpenGL::GLProgramManager::clone_internal_data_object(const void* in_ptr,
                                                                                                        const bool& in_convert_from_proxy_to_nonproxy)
{
    std::unique_ptr<void, std::function<void(void*)> > result_ptr(nullptr,
                                                                  [](void* in_ptr){delete reinterpret_cast<Program*>(in_ptr); });

    result_ptr.reset(
        new Program(m_frontend_object_managers_ptr->get_shader_manager_ptr(),
                    *reinterpret_cast<const Program*>(in_ptr),
                    in_convert_from_proxy_to_nonproxy)
    );
    vkgl_assert(result_ptr != nullptr);

    return result_ptr;
}

void OpenGL::GLProgramManager::copy_internal_data_object(const void* in_src_ptr,
                                                         void*       in_dst_ptr)
{
    *reinterpret_cast<Program*>(in_dst_ptr) = *reinterpret_cast<const Program*>(in_src_ptr);
}

OpenGL::GLProgramManagerUniquePtr OpenGL::GLProgramManager::create(OpenGL::IContextObjectManagers* in_frontend_object_managers_ptr,
                                                                   IBackendGLCallbacks*            in_backend_ptr)
{
    FUN_ENTRY(DEBUG_DEPTH);
    
    OpenGL::GLProgramManagerUniquePtr result_ptr;

    result_ptr.reset(new GLProgramManager(in_frontend_object_managers_ptr,
                                          in_backend_ptr) );

    if (result_ptr == nullptr)
    {
        vkgl_assert(result_ptr != nullptr);

        goto end;
    }

    if (!result_ptr->init() )
    {
        vkgl_assert_fail();

        result_ptr.reset();
    }

end:
    return result_ptr;
}

std::unique_ptr<void, std::function<void(void*)> > OpenGL::GLProgramManager::create_internal_data_object()
{
    std::unique_ptr<void, std::function<void(void*)> > result_ptr(nullptr,
                                                                  [](void* in_ptr){delete reinterpret_cast<Program*>(in_ptr); });

    result_ptr.reset(
        new Program()
    );

    vkgl_assert(result_ptr != nullptr);
    return result_ptr;
}

bool OpenGL::GLProgramManager::detach_shader(const GLuint& in_program,
                                             const GLuint& in_shader_id)
{
    FUN_ENTRY(DEBUG_DEPTH);
    
    auto                                          program_ptr      = get_program_ptr(in_program,
                                                                                     nullptr); /* in_opt_time_marker_ptr */
    bool                                          result           = false;
    decltype(Program::attached_shaders)::iterator shader_iterator;

    if (program_ptr == nullptr)
    {
        vkgl_assert(program_ptr != nullptr);

        goto end;
    }

    shader_iterator = std::find_if(program_ptr->attached_shaders.begin(),
                                   program_ptr->attached_shaders.end  (),
                                   [=](const OpenGL::GLShaderReferenceUniquePtr& in_reference_ptr)
                                   {
                                       return (in_shader_id == in_reference_ptr->get_payload().id);
                                   });

    if (shader_iterator == program_ptr->attached_shaders.end() )
    {
        vkgl_assert(shader_iterator != program_ptr->attached_shaders.end() );

        goto end;
    }

    program_ptr->attached_shaders.erase(shader_iterator);

    update_last_modified_time(in_program);
    result = true;
end:
    return result;
}

bool OpenGL::GLProgramManager::get_active_attribute(const GLuint&             in_program,
                                                    const OpenGL::TimeMarker* in_opt_time_marker_ptr,
                                                    const GLuint&             in_index,
                                                    const char**              out_opt_name_ptr_ptr,
                                                    uint32_t*                 out_opt_size_ptr,
                                                    VariableType*             out_opt_variable_ptr) const
{
    FUN_ENTRY(DEBUG_DEPTH);
    
    const ActiveAttributeProperties* attribute_props_ptr = nullptr;
    const PostLinkData*              post_link_data_ptr  = nullptr;
    auto                             program_ptr         = const_cast<OpenGL::GLProgramManager*>(this)->get_program_ptr(in_program,
                                                                           														in_opt_time_marker_ptr);
    bool                             result              = false;

    if (program_ptr == nullptr)
    {
        vkgl_assert(program_ptr != nullptr);

        goto end;
    }

    post_link_data_ptr = program_ptr->get_post_link_data(m_backend_ptr);

    if (post_link_data_ptr == nullptr)
    {
        goto end;
    }

    if (post_link_data_ptr->active_attributes.size() < in_index)
    {
        vkgl_assert(post_link_data_ptr->active_attributes.size() >= in_index);

        goto end;
    }

    attribute_props_ptr = &post_link_data_ptr->active_attributes.at(in_index);

    if (out_opt_name_ptr_ptr != nullptr)
    {
        *out_opt_name_ptr_ptr = attribute_props_ptr->name.c_str();
    }

    if (out_opt_size_ptr != nullptr)
    {
        *out_opt_size_ptr  = attribute_props_ptr->size;
    }

    if (out_opt_variable_ptr != nullptr)
    {
        *out_opt_variable_ptr = attribute_props_ptr->type;
    }

    result = true;
end:
    return result;
}

bool OpenGL::GLProgramManager::get_active_attribute_location(const GLuint&             in_program,
                                                             const OpenGL::TimeMarker* in_opt_time_marker_ptr,
                                                             const char*               in_name,
                                                             GLint*                    out_result_ptr) const
{
    FUN_ENTRY(DEBUG_DEPTH);
    
    decltype(PostLinkData::active_attribute_name_to_location_map)::const_iterator attribute_iterator;
    const PostLinkData*                                                           post_link_data_ptr = nullptr;
    auto                                                                          program_ptr        = const_cast<OpenGL::GLProgramManager*>(this)->get_program_ptr(in_program,
                                                                                                                       														in_opt_time_marker_ptr);
    bool                                                                          result             = false;

    if (program_ptr == nullptr)
    {
        vkgl_assert(program_ptr != nullptr);

        goto end;
    }

    post_link_data_ptr = program_ptr->get_post_link_data(m_backend_ptr);

    if (post_link_data_ptr == nullptr)
    {
        goto end;
    }

    attribute_iterator = post_link_data_ptr->active_attribute_name_to_location_map.find(in_name);

    if (attribute_iterator == post_link_data_ptr->active_attribute_name_to_location_map.end() )
    {
        vkgl_assert(attribute_iterator != post_link_data_ptr->active_attribute_name_to_location_map.end() );

        goto end;
    }

    *out_result_ptr = attribute_iterator->second;
    result          = true;
end:
    return result;
}

bool OpenGL::GLProgramManager::get_active_uniform(const GLuint&             in_program,
                                                  const OpenGL::TimeMarker* in_opt_time_marker_ptr,
                                                  const GLuint&             in_index,
                                                  const uint32_t            in_uniform_block_index,
                                                  const char**              out_opt_name_ptr_ptr,
                                                  uint32_t*                 out_opt_size_ptr,
                                                  VariableType*             out_opt_variable_ptr) const
{
    FUN_ENTRY(DEBUG_DEPTH);
    
    const PostLinkData*            post_link_data_ptr  = nullptr;
    auto                           program_ptr         = const_cast<OpenGL::GLProgramManager*>(this)->get_program_ptr(in_program,
                                                                         													in_opt_time_marker_ptr);
    bool                           result              = false;
    const ActiveUniformProperties* uniform_props_ptr   = nullptr;

    if (program_ptr == nullptr)
    {
        vkgl_assert(program_ptr != nullptr);

        goto end;
    }

    post_link_data_ptr = program_ptr->get_post_link_data(m_backend_ptr);

    if (post_link_data_ptr == nullptr)
    {
        goto end;
    }

    if (post_link_data_ptr->active_uniforms.size() < in_index)
    {
        vkgl_assert(post_link_data_ptr->active_uniforms.size() >= in_index);

        goto end;
    }

    uniform_props_ptr = &post_link_data_ptr->active_uniforms.at(in_index);

    if (out_opt_name_ptr_ptr != nullptr)
    {
        *out_opt_name_ptr_ptr = uniform_props_ptr->name.c_str();
    }

    if (out_opt_size_ptr != nullptr)
    {
        *out_opt_size_ptr  = uniform_props_ptr->size;
    }

    if (out_opt_variable_ptr != nullptr)
    {
        *out_opt_variable_ptr = uniform_props_ptr->type;
    }

    result = true;
end:
    return result;
}

bool OpenGL::GLProgramManager::get_active_uniform_block_name(const GLuint&             in_program,
                                                             const OpenGL::TimeMarker* in_opt_time_marker_ptr,
                                                             const GLuint&             in_index,
                                                             const char**              out_opt_name_ptr_ptr) const
{
    FUN_ENTRY(DEBUG_DEPTH);
    
    const PostLinkData* post_link_data_ptr = nullptr;
    auto                program_ptr        = const_cast<OpenGL::GLProgramManager*>(this)->get_program_ptr(in_program,
                                                             														in_opt_time_marker_ptr);
    bool                result             = false;

    if (program_ptr == nullptr)
    {
        vkgl_assert(program_ptr != nullptr);

        goto end;
    }

    post_link_data_ptr = program_ptr->get_post_link_data(m_backend_ptr);

    if (post_link_data_ptr == nullptr)
    {
        goto end;
    }

    if (post_link_data_ptr->active_uniform_blocks.size() < in_index)
    {
        vkgl_assert(post_link_data_ptr->active_uniform_blocks.size() >= in_index);

        goto end;
    }

    if (out_opt_name_ptr_ptr != nullptr)
    {
        *out_opt_name_ptr_ptr = post_link_data_ptr->active_uniform_blocks.at(in_index).name.c_str();
    }

    result = true;
end:
    return result;
}

bool OpenGL::GLProgramManager::get_active_uniform_block_property(const GLuint&                       in_program,
                                                                 const OpenGL::TimeMarker*           in_opt_time_marker_ptr,
                                                                 const GLuint&                       in_uniform_block_index,
                                                                 const OpenGL::UniformBlockProperty& in_pname,
                                                                 const OpenGL::GetSetArgumentType&   in_params_type,
                                                                 void*                               out_params_ptr) const
{
    FUN_ENTRY(DEBUG_DEPTH);
    
    const PostLinkData*       post_link_data_ptr = nullptr;
    auto                      program_ptr        = const_cast<OpenGL::GLProgramManager*>(this)->get_program_ptr(in_program,
                                                                   														in_opt_time_marker_ptr);
    bool                      result             = false;
    const void*               src_data_ptr       = nullptr;
    auto                      src_data_type      = OpenGL::GetSetArgumentType::Unknown;
    const ActiveUniformBlock* ub_ptr             = nullptr;

    union
    {
        uint32_t uint32;
    } helper_data;

    if (program_ptr == nullptr)
    {
        vkgl_assert(program_ptr != nullptr);

        goto end;
    }

    post_link_data_ptr = program_ptr->get_post_link_data(m_backend_ptr);

    if (post_link_data_ptr == nullptr)
    {
        goto end;
    }

    if (post_link_data_ptr->active_uniform_blocks.size() < in_uniform_block_index)
    {
        vkgl_assert(post_link_data_ptr->active_uniform_blocks.size() >= in_uniform_block_index);

        goto end;
    }

    ub_ptr = &post_link_data_ptr->active_uniform_blocks.at(in_uniform_block_index);

    switch (in_pname)
    {
        case OpenGL::UniformBlockProperty::Binding:                       src_data_type = OpenGL::GetSetArgumentType::Unsigned_Int; src_data_ptr = &ub_ptr->binding_point;    break;
        case OpenGL::UniformBlockProperty::Block_Data_Size:               src_data_type = OpenGL::GetSetArgumentType::Unsigned_Int; src_data_ptr = &ub_ptr->data_size;        break;
        case OpenGL::UniformBlockProperty::Referenced_By_Fragment_Shader: src_data_type = OpenGL::GetSetArgumentType::Boolean;      src_data_ptr = &ub_ptr->referenced_by_fs; break;
        case OpenGL::UniformBlockProperty::Referenced_By_Geometry_Shader: src_data_type = OpenGL::GetSetArgumentType::Boolean;      src_data_ptr = &ub_ptr->referenced_by_gs; break;
        case OpenGL::UniformBlockProperty::Referenced_By_Vertex_Shader:   src_data_type = OpenGL::GetSetArgumentType::Boolean;      src_data_ptr = &ub_ptr->referenced_by_vs; break;

        case OpenGL::UniformBlockProperty::Block_Active_Uniforms:
        {
            helper_data.uint32 = static_cast<uint32_t>(ub_ptr->active_uniforms.size() );
            src_data_type      = OpenGL::GetSetArgumentType::Unsigned_Int;
            src_data_ptr       = &helper_data.uint32;

            break;
        }

        case OpenGL::UniformBlockProperty::Block_Active_Uniform_Indices:
        {
            /* TODO: Improve if this assertion check blows. */
            vkgl_assert(in_params_type == OpenGL::GetSetArgumentType::Unsigned_Int);

            uint32_t* result_ptr = reinterpret_cast<uint32_t*>(out_params_ptr);

            for (uint32_t n_uniform = 0;
                          n_uniform < static_cast<const uint32_t>(ub_ptr->active_uniforms.size() );
                        ++n_uniform)
            {
                result_ptr[n_uniform] = ub_ptr->active_uniforms.at(n_uniform).index;
            }

            result = true;
            goto end;
        }

        case OpenGL::UniformBlockProperty::Block_Name_Length:
        {
            helper_data.uint32 = static_cast<uint32_t>(ub_ptr->name.length() + 1);

            src_data_type = OpenGL::GetSetArgumentType::Unsigned_Int;
            src_data_ptr  = &helper_data.uint32;

            break;
        }

        default:
        {
            vkgl_assert_fail();

            goto end;
        }
    }

    OpenGL::Converters::convert(src_data_type,
                                src_data_ptr,
                                1, /* in_n_vals */
                                in_params_type,
                                out_params_ptr);

    result = true;
end:
    return result;
}

bool OpenGL::GLProgramManager::get_active_uniform_by_name(const GLuint&             in_program,
                                                          const OpenGL::TimeMarker* in_opt_time_marker_ptr,
                                                          const char*               in_name_ptr,
                                                          GLint*                    out_opt_location_ptr) const
{
    FUN_ENTRY(DEBUG_DEPTH);
    
    const PostLinkData*                                                post_link_data_ptr = nullptr;
    auto                                                               program_ptr        = const_cast<OpenGL::GLProgramManager*>(this)->get_program_ptr(in_program,
                                                                                                            													in_opt_time_marker_ptr);
    bool                                                               result             = false;
    decltype(PostLinkData::active_uniform_by_name_map)::const_iterator uniform_iterator;

    if (program_ptr == nullptr)
    {
        vkgl_assert(program_ptr != nullptr);

        goto end;
    }

    post_link_data_ptr = program_ptr->get_post_link_data(m_backend_ptr);

    if (post_link_data_ptr == nullptr)
    {
        goto end;
    }

    uniform_iterator = post_link_data_ptr->active_uniform_by_name_map.find(in_name_ptr);

    if (uniform_iterator == post_link_data_ptr->active_uniform_by_name_map.end() )
    {
        vkgl_assert(uniform_iterator != post_link_data_ptr->active_uniform_by_name_map.end() )

        goto end;
    }

    if (out_opt_location_ptr != nullptr)
    {
        *out_opt_location_ptr = uniform_iterator->second->location;
    }

    result = true;
end:
    return result;
}

bool OpenGL::GLProgramManager::get_active_uniform_indices(const GLuint&             in_program,
                                                          const OpenGL::TimeMarker* in_opt_time_marker_ptr,
                                                          const uint32_t&           in_uniform_count,
                                                          const char* const*        in_uniform_names_ptr_ptr,
                                                          GLuint*                   out_uniform_indices_ptr) const
{
    FUN_ENTRY(DEBUG_DEPTH);
    
    const PostLinkData*                                                post_link_data_ptr = nullptr;
    auto                                                               program_ptr        = const_cast<OpenGL::GLProgramManager*>(this)->get_program_ptr(in_program,
                                                                                                            													in_opt_time_marker_ptr);
    bool                                                               result             = false;
    decltype(PostLinkData::active_uniform_by_name_map)::const_iterator uniform_iterator;

    if (program_ptr == nullptr)
    {
        vkgl_assert(program_ptr != nullptr);

        goto end;
    }

    post_link_data_ptr = program_ptr->get_post_link_data(m_backend_ptr);

    if (post_link_data_ptr == nullptr)
    {
        goto end;
    }

    for (uint32_t n_uniform = 0;
                  n_uniform < in_uniform_count;
                ++n_uniform)
    {
        GLuint result_index = GL_INVALID_INDEX;

        uniform_iterator = post_link_data_ptr->active_uniform_by_name_map.find(in_uniform_names_ptr_ptr[n_uniform]);

        if (uniform_iterator != post_link_data_ptr->active_uniform_by_name_map.end() )
        {
            result_index = uniform_iterator->second->index;
        }

        out_uniform_indices_ptr[n_uniform] = result_index;
    }

    result = true;
end:
    return result;
}

bool OpenGL::GLProgramManager::get_active_uniforms_property(const GLuint&                  in_program,
                                                            const OpenGL::TimeMarker*      in_opt_time_marker_ptr,
                                                            const GLsizei&                 in_uniform_count,
                                                            const GLuint*                  in_uniform_indices_ptr,
                                                            const OpenGL::UniformProperty& in_pname,
                                                            GLint*                         out_params_ptr) const
{
    FUN_ENTRY(DEBUG_DEPTH);
    
    const PostLinkData*        post_link_data_ptr = nullptr;
    auto                       program_ptr        = const_cast<OpenGL::GLProgramManager*>(this)->get_program_ptr(in_program,
                                                                    													in_opt_time_marker_ptr);
    bool                       result             = false;
    const void*                src_data_ptr       = nullptr;
    OpenGL::GetSetArgumentType src_data_type      = OpenGL::GetSetArgumentType::Unknown;

    union
    {
        uint32_t uint32;
    } helper_data;

    if (program_ptr == nullptr)
    {
        vkgl_assert(program_ptr != nullptr);

        goto end;
    }

    post_link_data_ptr = program_ptr->get_post_link_data(m_backend_ptr);

    if (post_link_data_ptr == nullptr)
    {
        goto end;
    }

    for (uint32_t n_uniform = 0;
                  n_uniform < static_cast<uint32_t>(in_uniform_count);
                ++n_uniform)
    {
        const auto                     uniform_index = in_uniform_indices_ptr[n_uniform];
        const ActiveUniformProperties* uniform_props_ptr = nullptr;

        if (post_link_data_ptr->active_uniforms.size() <= uniform_index)
        {
            vkgl_assert(post_link_data_ptr->active_uniforms.size() > uniform_index);

            goto end;
        }

        uniform_props_ptr = &post_link_data_ptr->active_uniforms.at(uniform_index);

        switch (in_pname)
        {
            case OpenGL::UniformProperty::Array_Stride:  src_data_ptr = &uniform_props_ptr->array_stride;        src_data_type = OpenGL::GetSetArgumentType::Int;          break;
            case OpenGL::UniformProperty::Block_Index:   src_data_ptr = &uniform_props_ptr->uniform_block_index; src_data_type = OpenGL::GetSetArgumentType::Int;          break;
            case OpenGL::UniformProperty::Is_Row_Major:  src_data_ptr = &uniform_props_ptr->is_row_major;        src_data_type = OpenGL::GetSetArgumentType::Boolean;      break;
            case OpenGL::UniformProperty::Location:      src_data_ptr = &uniform_props_ptr->location;            src_data_type = OpenGL::GetSetArgumentType::Int;          break;
            case OpenGL::UniformProperty::Matrix_Stride: src_data_ptr = &uniform_props_ptr->matrix_stride;       src_data_type = OpenGL::GetSetArgumentType::Int;          break;
            case OpenGL::UniformProperty::Offset:        src_data_ptr = &uniform_props_ptr->offset;              src_data_type = OpenGL::GetSetArgumentType::Int;          break;
            case OpenGL::UniformProperty::Size:          src_data_ptr = &uniform_props_ptr->size;                src_data_type = OpenGL::GetSetArgumentType::Unsigned_Int; break;

            case OpenGL::UniformProperty::Name_Length:
            {
                helper_data.uint32 = static_cast<uint32_t>(uniform_props_ptr->name.length() );

                src_data_ptr  = &helper_data.uint32;
                src_data_type = OpenGL::GetSetArgumentType::Unsigned_Int;

                break;
            }

            default:
            {
                vkgl_assert_fail();

                goto end;
            }
        }

        OpenGL::Converters::convert(src_data_type,
                                    src_data_ptr,
                                    1, /* in_n_vals */
                                    OpenGL::GetSetArgumentType::Int,
                                    out_params_ptr);
    }

    result = true;
end:
    return result;
}

bool OpenGL::GLProgramManager::get_frag_data_location(const GLuint&             in_program,
                                                      const OpenGL::TimeMarker* in_opt_time_marker_ptr,
                                                      const char*               in_name_ptr,
                                                      GLint*                    out_result_ptr) const
{
    FUN_ENTRY(DEBUG_DEPTH);
    
    decltype(PostLinkData::frag_data_locations)::const_iterator iterator;
    const PostLinkData*                                         post_link_data_ptr = nullptr;
    auto                                                        program_ptr        = const_cast<OpenGL::GLProgramManager*>(this)->get_program_ptr(in_program,
                                                                                                     													in_opt_time_marker_ptr);
    bool                                                        result             = false;

    if (program_ptr == nullptr)
    {
        vkgl_assert(program_ptr != nullptr);

        goto end;
    }

    post_link_data_ptr = program_ptr->get_post_link_data(m_backend_ptr);

    if (post_link_data_ptr == nullptr)
    {
        goto end;
    }

    iterator = post_link_data_ptr->frag_data_locations.find(in_name_ptr);

    if (iterator == post_link_data_ptr->frag_data_locations.end() )
    {
        vkgl_assert(iterator != post_link_data_ptr->frag_data_locations.end() );

        goto end;
    }

    *out_result_ptr = iterator->second;
    result          = true;
end:
    return result;
}

bool OpenGL::GLProgramManager::get_program_info_log(const GLuint&             in_program,
                                                    const OpenGL::TimeMarker* in_opt_time_marker_ptr,
                                                    const char**              out_result_ptr) const
{
    FUN_ENTRY(DEBUG_DEPTH);
    
    const PostLinkData* post_link_data_ptr = nullptr;
    auto                program_ptr        = const_cast<OpenGL::GLProgramManager*>(this)->get_program_ptr(in_program,
                                                             													in_opt_time_marker_ptr);
    bool                result             = false;

    if (program_ptr == nullptr)
    {
        vkgl_assert(program_ptr != nullptr);

        goto end;
    }

    post_link_data_ptr = program_ptr->get_post_link_data(m_backend_ptr);

    *out_result_ptr = (post_link_data_ptr != nullptr && post_link_data_ptr->link_log.size() > 0) ? &post_link_data_ptr->link_log.at(0)
                                                                                                 : "";

    result = true;
end:
    return result;
}

bool OpenGL::GLProgramManager::get_program_link_time_properties(const GLuint&                                  in_program,
                                                                const OpenGL::TimeMarker*                      in_opt_time_marker_ptr,
                                                                const AttributeLocationBindingMap**            out_attribute_location_bindings_ptr_ptr,
                                                                const FragDataLocationMap**                    out_frag_data_locations_ptr_ptr,
                                                                const std::unordered_map<uint32_t, uint32_t>** out_ub_index_to_ub_binding_map_ptr_ptr) const
{
    FUN_ENTRY(DEBUG_DEPTH);
    
    auto program_ptr = const_cast<OpenGL::GLProgramManager*>(this)->get_program_ptr(in_program,
                                       														in_opt_time_marker_ptr);
    bool result      = false;

    if (program_ptr == nullptr)
    {
        vkgl_assert(program_ptr != nullptr);

        goto end;
    }

    *out_attribute_location_bindings_ptr_ptr = &program_ptr->cached_attribute_location_bindings;
    *out_frag_data_locations_ptr_ptr         = &program_ptr->cached_frag_data_locations;
    *out_ub_index_to_ub_binding_map_ptr_ptr  = &program_ptr->ub_index_to_ub_binding;

    result = true;
end:
    return result;
}

bool OpenGL::GLProgramManager::get_program_property(const GLuint&                     in_program,
                                                    const OpenGL::TimeMarker*         in_opt_time_marker_ptr,
                                                    const OpenGL::ProgramProperty&    in_pname,
                                                    const OpenGL::GetSetArgumentType& in_params_type,
                                                    const uint32_t&                   in_n_params_components,
                                                    void*                             out_params_ptr) const
{
    FUN_ENTRY(DEBUG_DEPTH);
    
    const PostLinkData*        post_link_data_ptr = nullptr;
    auto                       program_ptr        = const_cast<OpenGL::GLProgramManager*>(this)->get_program_ptr(in_program,
                                                                    													in_opt_time_marker_ptr);
    bool                       result             = false;
    const void*                src_data_ptr       = nullptr;
    OpenGL::GetSetArgumentType src_data_type      = OpenGL::GetSetArgumentType::Unknown;

    union
    {
        uint32_t uint32;
    } helper_data;

    if (program_ptr == nullptr)
    {
        vkgl_assert(program_ptr != nullptr);

        goto end;
    }

    /* NOTE: post-link data ptr will be null if linking has not been initiated! */
    post_link_data_ptr = program_ptr->get_post_link_data(m_backend_ptr);

    switch (in_pname)
    {
        case OpenGL::ProgramProperty::Delete_Status:                         src_data_ptr = &program_ptr->delete_status;                      src_data_type = OpenGL::GetSetArgumentType::Boolean;                         break;
        case OpenGL::ProgramProperty::Geometry_Input_Type:                   src_data_ptr = &post_link_data_ptr->gs_input_type;               src_data_type = OpenGL::GetSetArgumentType::GeometryInputTypeVKGL;           break;
        case OpenGL::ProgramProperty::Geometry_Output_Type:                  src_data_ptr = &post_link_data_ptr->gs_output_type;              src_data_type = OpenGL::GetSetArgumentType::GeometryOutputTypeVKGL;          break;
        case OpenGL::ProgramProperty::Geometry_Vertices_Out:                 src_data_ptr = &post_link_data_ptr->n_max_gs_vertices_generated; src_data_type = OpenGL::GetSetArgumentType::Unsigned_Int;                    break;
        case OpenGL::ProgramProperty::Transform_Feedback_Buffer_Mode:        src_data_ptr = &program_ptr->tf_buffer_mode;                     src_data_type = OpenGL::GetSetArgumentType::TransformFeedbackBufferModeVKGL; break;
        case OpenGL::ProgramProperty::Transform_Feedback_Varying_Max_Length: src_data_ptr = &program_ptr->tf_varying_max_length;              src_data_type = OpenGL::GetSetArgumentType::Unsigned_Int;                    break;
        case OpenGL::ProgramProperty::Validate_Status:                       src_data_ptr = &program_ptr->validate_status;                    src_data_type = OpenGL::GetSetArgumentType::Boolean;                         break;

        case OpenGL::ProgramProperty::Active_Attribute_Max_Length:
        {
            helper_data.uint32 = 0;

            src_data_ptr  = (post_link_data_ptr != nullptr) ? &post_link_data_ptr->active_attribute_max_length
                                                            : &helper_data.uint32;
            src_data_type = OpenGL::GetSetArgumentType::Unsigned_Int;

            break;
        }

        case OpenGL::ProgramProperty::Active_Attributes:
        {
            helper_data.uint32 = (post_link_data_ptr != nullptr) ? static_cast<uint32_t>(post_link_data_ptr->active_attributes.size() )
                                                                 : 0;

            src_data_ptr  = &helper_data.uint32;
            src_data_type = OpenGL::GetSetArgumentType::Unsigned_Int;

            break;
        }

        case OpenGL::ProgramProperty::Active_Uniform_Block_Max_Name_Length:
        {
            helper_data.uint32 = (post_link_data_ptr != nullptr) ? post_link_data_ptr->active_uniform_block_max_name_length
                                                                 : 0;

            src_data_ptr  = &helper_data.uint32;
            src_data_type = OpenGL::GetSetArgumentType::Unsigned_Int;

            break;
        }

        case OpenGL::ProgramProperty::Active_Uniform_Blocks:
        {
            helper_data.uint32 = (post_link_data_ptr != nullptr) ? static_cast<uint32_t>(post_link_data_ptr->active_uniform_blocks.size() )
                                                                 : 0;

            src_data_ptr  = &helper_data.uint32;
            src_data_type = OpenGL::GetSetArgumentType::Unsigned_Int;

            break;
        }

        case OpenGL::ProgramProperty::Active_Uniform_Max_Length:
        {
            helper_data.uint32 = (post_link_data_ptr != nullptr) ? post_link_data_ptr->active_uniform_max_length
                                                                 : 0;

            src_data_ptr  = &helper_data.uint32;
            src_data_type = OpenGL::GetSetArgumentType::Unsigned_Int;

            break;
        }

        case OpenGL::ProgramProperty::Active_Uniforms:
        {
            helper_data.uint32 = (post_link_data_ptr != nullptr) ? static_cast<uint32_t>(post_link_data_ptr->active_uniforms.size() )
                                                                 : 0;

            src_data_ptr  = &helper_data.uint32;
            src_data_type = OpenGL::GetSetArgumentType::Unsigned_Int;

            break;
        }

        case OpenGL::ProgramProperty::Attached_Shaders:
        {
            helper_data.uint32 = static_cast<uint32_t>(program_ptr->attached_shaders.size() );

            src_data_ptr  = &helper_data.uint32;
            src_data_type = OpenGL::GetSetArgumentType::Unsigned_Int;

            break;
        }

        case OpenGL::ProgramProperty::Info_Log_Length:
        {
            helper_data.uint32 = (post_link_data_ptr != nullptr) ? static_cast<uint32_t>(post_link_data_ptr->link_log.length() + 1 /* terminator */)
                                                                 : 0;

            src_data_ptr  = (helper_data.uint32 > 1) ? &helper_data.uint32
                                                     : nullptr;
            src_data_type = OpenGL::GetSetArgumentType::Unsigned_Int;

            break;
        }

        case OpenGL::ProgramProperty::Link_Status:
        {
            helper_data.uint32 = false;

            if (program_ptr->spirv_blob_id != UINT32_MAX)
            {
                bool link_status = false;

                m_backend_ptr->get_spirv_manager_ptr()->get_program_link_status(program_ptr->spirv_blob_id,
                                                                               &link_status,
                                                                                nullptr); /* out_link_log_ptr */

                helper_data.uint32 = static_cast<uint32_t>(link_status);
            }

            src_data_ptr  = &helper_data.uint32;
            src_data_type = OpenGL::GetSetArgumentType::Unsigned_Int;

            break;
        }

        case OpenGL::ProgramProperty::Transform_Feedback_Varyings:
        {
            helper_data.uint32 = (post_link_data_ptr != nullptr) ? static_cast<uint32_t>(program_ptr->tf_varyings.size() )
                                                                 : 0;

            src_data_ptr  = &helper_data.uint32;
            src_data_type = OpenGL::GetSetArgumentType::Unsigned_Int;

            break;
        }

        default:
        {
            vkgl_assert_fail();

            goto end;
        }
    }

    OpenGL::Converters::convert(src_data_type,
                                src_data_ptr,
                                1, /* in_n_vals */
                                in_params_type,
                                out_params_ptr);

    result = true;
end:
    return result;
}

const OpenGL::GLProgramManager::Program* OpenGL::GLProgramManager::get_program_ptr(const GLuint&             in_id,
                                                                                   const OpenGL::TimeMarker* in_opt_time_marker_ptr) const
{
    return reinterpret_cast<const OpenGL::GLProgramManager::Program*>(get_internal_object_props_ptr(in_id,
                                                                                                    in_opt_time_marker_ptr) );
}

OpenGL::GLProgramManager::Program* OpenGL::GLProgramManager::get_program_ptr(const GLuint&             in_id,
                                                                             const OpenGL::TimeMarker* in_opt_time_marker_ptr)
{
    return reinterpret_cast<OpenGL::GLProgramManager::Program*>(get_internal_object_props_ptr(in_id,
                                                                                              in_opt_time_marker_ptr) );
}

bool OpenGL::GLProgramManager::get_uniform_block_index(const GLuint&             in_program,
                                                       const OpenGL::TimeMarker* in_opt_time_marker_ptr,
                                                       const char*               in_uniform_block_name,
                                                       uint32_t*                 out_result_ptr) const
{
    FUN_ENTRY(DEBUG_DEPTH);
    
    decltype(PostLinkData::active_uniform_block_by_name_map)::const_iterator iterator;
    const PostLinkData*                                                      post_link_data_ptr = nullptr;
    auto                                                                     program_ptr        = const_cast<OpenGL::GLProgramManager*>(this)->get_program_ptr(in_program,
                                                                                                                  														in_opt_time_marker_ptr);
    bool                                                                     result             = false;

    if (program_ptr == nullptr)
    {
        vkgl_assert(program_ptr != nullptr);

        goto end;
    }

    post_link_data_ptr = program_ptr->get_post_link_data(m_backend_ptr);

    if (post_link_data_ptr == nullptr)
    {
        goto end;
    }

    iterator = post_link_data_ptr->active_uniform_block_by_name_map.find(in_uniform_block_name);

    if (iterator == post_link_data_ptr->active_uniform_block_by_name_map.end() )
    {
        vkgl_assert(iterator != post_link_data_ptr->active_uniform_block_by_name_map.end() );

        goto end;
    }

    *out_result_ptr = iterator->second->index;
    result          = true;
end:
    return result;
}


const std::vector<OpenGL::GLShaderReferenceUniquePtr>* OpenGL::GLProgramManager::get_attached_shaders(const GLuint&             in_program,
                                                                                                      const OpenGL::TimeMarker* in_opt_time_marker_ptr) const
{
    FUN_ENTRY(DEBUG_DEPTH);
    
    auto                                                   program_ptr = const_cast<OpenGL::GLProgramManager*>(this)->get_program_ptr(in_program,
                                                                                       														in_opt_time_marker_ptr);
    const std::vector<OpenGL::GLShaderReferenceUniquePtr>* result_ptr  = nullptr;

    if (program_ptr == nullptr)
    {
        vkgl_assert(program_ptr != nullptr);

        goto end;
    }

    result_ptr = &program_ptr->attached_shaders;
end:
    return result_ptr;
}

bool OpenGL::GLProgramManager::map_global_uniform_index_to_uniform_and_ub_indices(const GLuint&             in_program,
                                                                                  const OpenGL::TimeMarker* in_opt_time_marker_ptr,
                                                                                  const GLuint&             in_global_uniform_index,
                                                                                  GLuint*                   out_uniform_block_index_ptr,
                                                                                  GLuint*                   out_uniform_index_ptr) const
{
    FUN_ENTRY(DEBUG_DEPTH);
    
    decltype(PostLinkData::index_to_ub_and_uniform_index_pair)::const_iterator iterator;
    const PostLinkData*                                                        post_link_data_ptr = nullptr;
    auto                                                                       program_ptr        = const_cast<OpenGL::GLProgramManager*>(this)->get_program_ptr(in_program,
                                                                                                                    													in_opt_time_marker_ptr);
    bool                                                                       result             = false;

    if (program_ptr == nullptr)
    {
        vkgl_assert(program_ptr != nullptr);

        goto end;
    }

    post_link_data_ptr = program_ptr->get_post_link_data(m_backend_ptr);

    if (post_link_data_ptr == nullptr)
    {
        goto end;
    }

    iterator = post_link_data_ptr->index_to_ub_and_uniform_index_pair.find(in_global_uniform_index);

    if (iterator == post_link_data_ptr->index_to_ub_and_uniform_index_pair.end() )
    {
        vkgl_assert(iterator != post_link_data_ptr->index_to_ub_and_uniform_index_pair.end() );

        goto end;
    }

    *out_uniform_block_index_ptr = iterator->second.first;
    *out_uniform_index_ptr       = iterator->second.second;

    result = true;
end:
    return result;
}

void OpenGL::GLProgramManager::set_program_backend_spirv_blob_id(const GLuint&              in_program,
                                                                 const OpenGL::TimeMarker*  in_opt_time_marker_ptr,
                                                                 const OpenGL::SPIRVBlobID& in_spirv_blob_id)
{
    FUN_ENTRY(DEBUG_DEPTH);
    
    auto program_ptr = get_program_ptr(in_program,
                                       in_opt_time_marker_ptr);

    if (program_ptr == nullptr)
    {
        vkgl_assert(program_ptr != nullptr);

        goto end;
    }

    /* NOTE: No need for a snapshot bump here because SPIR-V blob ID is an INTERNAL state. */
    vkgl_assert(program_ptr->spirv_blob_id == UINT32_MAX);
    program_ptr->spirv_blob_id = in_spirv_blob_id;

end:
    ;
}

void OpenGL::GLProgramManager::get_program_post_link_data_ptr(const GLuint&             in_program,
                                                              const OpenGL::TimeMarker* in_opt_time_marker_ptr,
                                                              const PostLinkData**      out_post_link_data_ptr_ptr) const
{
    FUN_ENTRY(DEBUG_DEPTH);
    
    auto program_ptr = const_cast<OpenGL::GLProgramManager*>(this)->get_program_ptr(in_program,
                                                                                    in_opt_time_marker_ptr);

    if (program_ptr == nullptr)
    {
        vkgl_assert(program_ptr != nullptr);

        *out_post_link_data_ptr_ptr = nullptr;
        goto end;
    }

    *out_post_link_data_ptr_ptr = program_ptr->get_post_link_data(m_backend_ptr);

end:
    ;
}

void OpenGL::GLProgramManager::set_program_post_link_data_ptr(const GLuint&                 in_program,
                                                              const OpenGL::TimeMarker*     in_opt_time_marker_ptr,
                                                              OpenGL::PostLinkDataUniquePtr in_post_link_data_ptr)
{
    FUN_ENTRY(DEBUG_DEPTH);
    
    auto program_ptr = get_program_ptr(in_program,
                                       in_opt_time_marker_ptr);

    if (program_ptr == nullptr)
    {
        vkgl_assert(program_ptr != nullptr);

        goto end;
    }

    /* NOTE: No need for a snapshot bump here because post-link data is an INTERNAL state. */
    vkgl_assert(program_ptr->spirv_blob_id != UINT32_MAX);
    vkgl_assert(in_post_link_data_ptr      != nullptr);

    program_ptr->set_post_link_data(std::move(in_post_link_data_ptr) );

end:
    ;
}

void OpenGL::GLProgramManager::set_uniform_block_binding(const GLuint& in_program,
                                                         const GLuint& in_uniform_block_index,
                                                         const GLuint& in_uniform_block_binding)
{
    FUN_ENTRY(DEBUG_DEPTH);
    
    auto program_ptr = get_program_ptr(in_program,
                                       nullptr); /* in_opt_time_marker_ptr */

    if (program_ptr == nullptr)
    {
        vkgl_assert(program_ptr != nullptr);

        goto end;
    }

    if (program_ptr->ub_index_to_ub_binding.find(in_uniform_block_index) == program_ptr->ub_index_to_ub_binding.end() ||
        program_ptr->ub_index_to_ub_binding[in_uniform_block_index]      != in_uniform_block_binding)
    {
        program_ptr->ub_index_to_ub_binding[in_uniform_block_index] = in_uniform_block_binding;

        update_last_modified_time(in_program);
    }

end:
    ;
}
