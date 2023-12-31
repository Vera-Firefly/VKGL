/* VKGL (c) 2018 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Anvil/include/misc/buffer_create_info.h"
#include "Anvil/include/misc/memory_allocator.h"
#include "Anvil/include/misc/memory_block_create_info.h"
#include "Anvil/include/wrappers/buffer.h"
#include "Anvil/include/wrappers/command_buffer.h"
#include "Anvil/include/wrappers/memory_block.h"
#include "Common/macros.h"
#include "OpenGL/backend/nodes/vk_buffer_data_node.h"
#include "OpenGL/backend/vk_utils.h"
#include "OpenGL/frontend/gl_buffer_manager.h"


OpenGL::VKNodes::BufferData::BufferData(const IContextObjectManagers*      in_frontend_ptr,
                                        IBackend*                          in_backend_ptr,
                                        OpenGL::VKBufferReferenceUniquePtr in_backend_buffer_reference_ptr,
                                        OpenGL::GLBufferReferenceUniquePtr in_frontend_buffer_reference_ptr,
                                        OpenGL::DataUniquePtr              in_opt_data_ptr)
    :m_backend_ptr                  (in_backend_ptr),
     m_backend_buffer_reference_ptr (std::move(in_backend_buffer_reference_ptr) ),
     m_data_ptr                     ((in_opt_data_ptr != nullptr) ? std::move(in_opt_data_ptr) : nullptr),
     m_frontend_ptr                 (in_frontend_ptr),
     m_frontend_buffer_reference_ptr(std::move(in_frontend_buffer_reference_ptr) )
{
    FUN_ENTRY(DEBUG_DEPTH);
    
    const auto size = m_frontend_ptr->get_buffer_manager_ptr()->get_buffer_size(m_frontend_buffer_reference_ptr->get_payload().id,
                                                                               &m_frontend_buffer_reference_ptr->get_payload().time_marker);

    vkgl_assert(m_backend_ptr  != nullptr);
    vkgl_assert(m_frontend_ptr != nullptr);
    vkgl_assert(size           != 0);

    m_info_ptr = decltype(m_info_ptr)(nullptr,
                                      std::default_delete<OpenGL::VKFrameGraphNodeInfo>() );

    m_info_ptr.reset(new OpenGL::VKFrameGraphNodeInfo() );
    vkgl_assert(m_info_ptr != nullptr);

    {
        const Anvil::AccessFlags        input_access          = (m_data_ptr != nullptr) ? Anvil::AccessFlagBits::TRANSFER_WRITE_BIT  : Anvil::AccessFlagBits::NONE;
        const Anvil::PipelineStageFlags input_pipeline_stages = (m_data_ptr != nullptr) ? Anvil::PipelineStageFlagBits::TRANSFER_BIT : Anvil::PipelineStageFlagBits::NONE;

        m_info_ptr->inputs.push_back(
            OpenGL::NodeIO(m_backend_buffer_reference_ptr.get(),
                           0, /* in_start_offset */
                           size,
                           input_pipeline_stages,
                           input_access)
        );
    }

    {
        const Anvil::AccessFlags        output_access          = (m_data_ptr != nullptr) ? Anvil::AccessFlagBits::TRANSFER_WRITE_BIT  : Anvil::AccessFlagBits::NONE;
        const Anvil::PipelineStageFlags output_pipeline_stages = (m_data_ptr != nullptr) ? Anvil::PipelineStageFlagBits::TRANSFER_BIT : Anvil::PipelineStageFlagBits::NONE;

        m_info_ptr->outputs.push_back(
            OpenGL::NodeIO(m_backend_buffer_reference_ptr.get(),
                           0, /* in_start_offset */
                           size,
                           output_pipeline_stages,
                           output_access)
        );
    }
}

OpenGL::VKNodes::BufferData::~BufferData()
{
    FUN_ENTRY(DEBUG_DEPTH);
    
    m_backend_buffer_reference_ptr.reset ();
    m_data_ptr.reset                     ();
    m_frontend_buffer_reference_ptr.reset();
    m_info_ptr.reset                     ();
    m_staging_buffer_ptr.reset           ();
}

bool OpenGL::VKNodes::BufferData::can_memory_block_handle_frontend_reqs(const Anvil::MemoryBlock*   in_mem_block_ptr,
                                                                        const size_t&               in_size,
                                                                        const OpenGL::BufferUsage&  in_buffer_usage) const
{
    FUN_ENTRY(DEBUG_DEPTH);
    
    auto       mem_block_create_info_ptr     = in_mem_block_ptr->get_create_info_ptr();
    const auto required_memory_feature_flags = OpenGL::VKUtils::get_memory_feature_flags_for_gl_buffer(in_buffer_usage);
    bool       result                        = true;

    if ((mem_block_create_info_ptr->get_memory_features() & required_memory_feature_flags) != required_memory_feature_flags)
    {
        /* Memory block's mem features are a subset of what is required */
        result = false;

        goto end;
    }

    if (mem_block_create_info_ptr->get_size() < in_size)
    {
        /* Too little space available .. */
        result = false;

        goto end;
    }

end:
    return result;
}

OpenGL::VKFrameGraphNodeUniquePtr OpenGL::VKNodes::BufferData::create(const IContextObjectManagers*      in_frontend_ptr,
                                                                      OpenGL::IBackend*                  in_backend_ptr,
                                                                      OpenGL::VKBufferReferenceUniquePtr in_backend_buffer_reference_ptr,
                                                                      OpenGL::GLBufferReferenceUniquePtr in_frontend_buffer_reference_ptr,
                                                                      OpenGL::DataUniquePtr              in_opt_data_ptr)
{
    FUN_ENTRY(DEBUG_DEPTH);
    
    OpenGL::VKFrameGraphNodeUniquePtr result_ptr(nullptr,
                                                 std::default_delete<OpenGL::IVKFrameGraphNode>() );

    result_ptr.reset(
        new OpenGL::VKNodes::BufferData(in_frontend_ptr,
                                        in_backend_ptr,
                                        std::move(in_backend_buffer_reference_ptr),
                                        std::move(in_frontend_buffer_reference_ptr),
                                        std::move(in_opt_data_ptr) )
    );

    vkgl_assert(result_ptr != nullptr);
    return result_ptr;
}

void OpenGL::VKNodes::BufferData::do_cpu_prepass(IVKFrameGraphNodeCallback*)
{
    FUN_ENTRY(DEBUG_DEPTH);
    
    /* NOTE: "Buffer data" command drops existing memory storage. For perf reasons, we can skip this step IF
     *
     *       1) the new storage size and usage property matches the former one's.
     *       2) the buffer has already been created, and has been bound actual storage.
     *
     *       If both hold, we can proceed directly with a data copy, granted new data has been provided. Otherwise, we're also going
     *       to need to make sure both buffer and mem block objects have been created.
     */
    auto                        backend_buffer_ptr                      = m_info_ptr->outputs.at(0).buffer_reference_ptr->get_payload().buffer_ptr;
    const auto                  frontend_buffer_creation_time           = m_frontend_buffer_reference_ptr->get_payload().object_creation_time;
    const auto&                 frontend_buffer_id                      = m_frontend_buffer_reference_ptr->get_payload().id;
    uint32_t                    frontend_buffer_n_used_buffer_targets   = 0;
    size_t                      frontend_buffer_size                    = 0;
    const auto&                 frontend_buffer_snapshot_time           = m_frontend_buffer_reference_ptr->get_payload().time_marker;
    OpenGL::BufferUsage         frontend_buffer_usage                   = OpenGL::BufferUsage::Unknown;
    const OpenGL::BufferTarget* frontend_buffer_used_buffer_targets_ptr = nullptr;
    auto                        mem_allocator_ptr                       = m_backend_ptr->get_memory_allocator_ptr();

    vkgl_assert(*m_info_ptr->inputs.at(0).buffer_reference_ptr == *m_info_ptr->outputs.at(0).buffer_reference_ptr);

    /* 1. Retrieve frontend buffer's properties */
    {
        auto gl_buffer_manager_ptr = m_frontend_ptr->get_buffer_manager_ptr();

        frontend_buffer_size  = gl_buffer_manager_ptr->get_buffer_size (frontend_buffer_id,
                                                                       &frontend_buffer_snapshot_time);
        frontend_buffer_usage = gl_buffer_manager_ptr->get_buffer_usage(frontend_buffer_id,
                                                                       &frontend_buffer_snapshot_time);

        gl_buffer_manager_ptr->get_buffer_used_buffer_targets(frontend_buffer_id,
                                                             &frontend_buffer_snapshot_time,
                                                             &frontend_buffer_n_used_buffer_targets,
                                                             &frontend_buffer_used_buffer_targets_ptr);
    }

    /* 2. Do we need a new VK mem block instance? */
    {
        auto backend_mem_block_ptr      = backend_buffer_ptr->get_memory_block(0);
        bool need_new_backend_mem_block = true;

        if (backend_mem_block_ptr != nullptr)
        {
            need_new_backend_mem_block = !can_memory_block_handle_frontend_reqs(backend_mem_block_ptr,
                                                                                frontend_buffer_size,
                                                                                frontend_buffer_usage);
        }

        if (need_new_backend_mem_block)
        {
            const auto required_memory_features = OpenGL::VKUtils::get_memory_feature_flags_for_gl_buffer(frontend_buffer_usage);

            if (!mem_allocator_ptr->add_buffer(backend_buffer_ptr,
                                               required_memory_features) )
            {
                vkgl_assert_fail();
            }

        }
    }

    /* 3. Create a staging buffer, bind memory to it, move the user-specified data there.
     *
     * TODO: Backend should host a pool of staging buffers to reuse. We should not be re-creating these buffers here
     *       all the time.
     */
    if (m_data_ptr != nullptr)
    {
        {
            auto create_info_ptr = Anvil::BufferCreateInfo::create_no_alloc(m_backend_ptr->get_device_ptr(),
                                                                            m_info_ptr->outputs.at(0).buffer_props.size,
                                                                            Anvil::QueueFamilyFlagBits::COMPUTE_BIT | Anvil::QueueFamilyFlagBits::DMA_BIT | Anvil::QueueFamilyFlagBits::GRAPHICS_BIT,
                                                                            Anvil::SharingMode::EXCLUSIVE,
                                                                            Anvil::BufferCreateFlagBits::NONE,
                                                                            Anvil::BufferUsageFlagBits::TRANSFER_SRC_BIT);

            vkgl_assert(create_info_ptr != nullptr);

            m_staging_buffer_ptr = Anvil::Buffer::create(std::move(create_info_ptr) );
            vkgl_assert(m_staging_buffer_ptr != nullptr);

            #ifdef _DEBUG
            {
                m_staging_buffer_ptr->set_name_formatted("Staging buffer for a staging->%p copy op (GL buffer ID: %d)",
                                                         backend_buffer_ptr->get_buffer(),
                                                         frontend_buffer_id);
            }
            #endif
        }

        if (!mem_allocator_ptr->add_buffer(m_staging_buffer_ptr.get(),
                                           Anvil::MemoryFeatureFlagBits::HOST_COHERENT_BIT | Anvil::MemoryFeatureFlagBits::MAPPABLE_BIT) )
        {
            vkgl_assert_fail();
        }
    }

    /* NOTE: Invocation below automagically binds the mem alloc to added objects. */
    if (!mem_allocator_ptr->bake() )
    {
        vkgl_assert_fail();
    }

    if (m_data_ptr != nullptr)
    {
        auto  staging_buffer_mem_block_ptr = m_staging_buffer_ptr->get_memory_block(0);
        void* staging_buffer_raw_ptr       = nullptr;

        vkgl_assert(staging_buffer_mem_block_ptr != nullptr);

        if (!staging_buffer_mem_block_ptr->map(0, /* in_start_offset */
                                               m_info_ptr->outputs.at(0).buffer_props.size,
                                              &staging_buffer_raw_ptr) )
        {
            vkgl_assert_fail();
        }

        memcpy(staging_buffer_raw_ptr,
               m_data_ptr.get(),
               static_cast<size_t>(m_staging_buffer_ptr->get_create_info_ptr()->get_size()) );

        if (!staging_buffer_mem_block_ptr->unmap() )
        {
            vkgl_assert_fail();
        }
    }
}

void OpenGL::VKNodes::BufferData::get_supported_queue_families(uint32_t*                          out_n_queue_fams_ptr,
                                                               const Anvil::QueueFamilyFlagBits** out_queue_fams_ptr_ptr) const
{
    FUN_ENTRY(DEBUG_DEPTH);
    
    static const Anvil::QueueFamilyFlagBits compatible_queue_fams[] =
    {
        Anvil::QueueFamilyFlagBits::DMA_BIT,
        Anvil::QueueFamilyFlagBits::COMPUTE_BIT,
        Anvil::QueueFamilyFlagBits::GRAPHICS_BIT,
    };

    *out_n_queue_fams_ptr   = sizeof(compatible_queue_fams) / sizeof(compatible_queue_fams[0]);
    *out_queue_fams_ptr_ptr = compatible_queue_fams;
}

void OpenGL::VKNodes::BufferData::record_commands(Anvil::CommandBufferBase*  in_cmd_buffer_ptr,
                                                  const bool&                in_inside_renderpass,
                                                  IVKFrameGraphNodeCallback* in_graph_callback_ptr) const
{
    FUN_ENTRY(DEBUG_DEPTH);
    
    if (m_staging_buffer_ptr != nullptr)
    {
        auto              backend_buffer_ptr = m_info_ptr->inputs.at(0).buffer_reference_ptr->get_payload().buffer_ptr;
        Anvil::BufferCopy copy_region;

        {
            auto cpu_write_to_copy_op_barrier = Anvil::MemoryBarrier(Anvil::AccessFlagBits::TRANSFER_READ_BIT, /* in_dst_access_mask */
                                                                     Anvil::AccessFlagBits::HOST_WRITE_BIT);   /* in_src_access_mask */

            in_cmd_buffer_ptr->record_pipeline_barrier(Anvil::PipelineStageFlagBits::HOST_BIT,
                                                       Anvil::PipelineStageFlagBits::TRANSFER_BIT, /* in_dst_stage_mask */
                                                       Anvil::DependencyFlagBits::NONE,
                                                       1, /* in_memory_barrier_count */
                                                      &cpu_write_to_copy_op_barrier,
                                                       0,                             /* in_buffer_memory_barrier_count */
                                                       nullptr,                       /* in_buffer_memory_barriers_ptr */
                                                       0,                             /* in_image_memory_barrier_count */
                                                       nullptr);                      /* in_image_memory_barriers_ptr */
        }

        copy_region.dst_offset = 0;
        copy_region.size       = m_staging_buffer_ptr->get_create_info_ptr()->get_size();
        copy_region.src_offset = 0;

        in_cmd_buffer_ptr->record_copy_buffer(m_staging_buffer_ptr.get(),
                                              backend_buffer_ptr,
                                              1, /* in_region_count */
                                             &copy_region);
    }
}

bool OpenGL::VKNodes::BufferData::requires_gpu_side_execution() const
{
    FUN_ENTRY(DEBUG_DEPTH);
    
    return m_data_ptr != nullptr;
}

OpenGL::RenderpassSupportScope OpenGL::VKNodes::BufferData::get_renderpass_support_scope() const
{
    FUN_ENTRY(DEBUG_DEPTH);
    
    return (m_data_ptr == nullptr) ? OpenGL::RenderpassSupportScope::Supported      //< No commands will be recorded in this case.
                                   : OpenGL::RenderpassSupportScope::Not_Supported; //< Buffer->buffer copy ops are NOT supported for renderpass usage.
}
