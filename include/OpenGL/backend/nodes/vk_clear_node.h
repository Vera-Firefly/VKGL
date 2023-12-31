/* VKGL (c) 2018 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef VKGL_VK_CLEAR_NODE_H
#define VKGL_VK_CLEAR_NODE_H

#include "OpenGL/backend/vk_backend.h"
#include "OpenGL/backend/vk_frame_graph_node.h"

namespace OpenGL
{
    namespace VKNodes
    {
        class Clear : public OpenGL::IVKFrameGraphNode
        {
        public:
            /* Public functions */
            static VKFrameGraphNodeUniquePtr create(const IContextObjectManagers*            in_frontend_ptr,
                                                    IBackend*                                in_backend_ptr,
                                                    OpenGL::GLContextStateReferenceUniquePtr in_context_state_ptr,
                                                    const OpenGL::ClearBufferBits&           in_buffers_to_clear);

            ~Clear();

        private:
            /* IVKFrameGraphNode */
            void do_cpu_prepass(IVKFrameGraphNodeCallback*) final
            {
                /* Should never be called */
                vkgl_assert_fail();
            }

            void execute_cpu_side(IVKFrameGraphNodeCallback*) final
            {
                /* Should never be called */
                vkgl_assert_fail();
            }

            void get_gl_context_state(const OpenGL::ContextState**                    out_context_state_ptr_ptr,
                                      const OpenGL::GLContextStateBindingReferences** out_context_state_binding_references_ptr_ptr) const final
            {
                /* Should never be called */
                vkgl_assert_fail();
            }

            const VKFrameGraphNodeInfo* get_info_ptr() const final
            {
                return m_info_ptr.get();
            }

            RenderpassSupportScope get_renderpass_support_scope() const final
            {
                /* TODO: We do not support leaking clear ops into renderpasses YET. Yes, this is suboptimal. */
                return RenderpassSupportScope::Not_Supported;
            }

            void get_supported_queue_families(uint32_t*                          out_n_queue_fams_ptr,
                                              const Anvil::QueueFamilyFlagBits** out_queue_fams_ptr_ptr) const final;

            FrameGraphNodeType get_type() const final
            {
                return FrameGraphNodeType::Clear;
            }

            void record_commands(Anvil::CommandBufferBase*  in_cmd_buffer_ptr,
                                 const bool&                in_inside_renderpass,
                                 IVKFrameGraphNodeCallback* in_graph_callback_ptr) const final;

            bool requires_cpu_side_execution() const final
            {
                return false;
            }

            bool requires_cpu_prepass() const final
            {
                return false;
            }

            bool requires_gpu_side_execution() const final
            {
                return true;
            }

            bool requires_manual_wait_sem_sync() const final
            {
                return false;
            }

            bool supports_primary_command_buffers() const final
            {
                return true;
            }

            bool supports_secondary_command_buffers() const final
            {
                return true;
            }

            /* Private functions */

            Clear(const IContextObjectManagers*            in_frontend_ptr,
                  OpenGL::IBackend*                        in_backend_ptr,
                  OpenGL::GLContextStateReferenceUniquePtr in_context_state_ptr,
                  const OpenGL::ClearBufferBits&           in_buffers_to_clear);

            void init_info();

            /* Private variables */
            IBackend*                                m_backend_ptr;
            OpenGL::GLContextStateReferenceUniquePtr m_context_state_ptr;
            const IContextObjectManagers*            m_frontend_ptr;
            OpenGL::VKFrameGraphNodeInfoUniquePtr    m_info_ptr;

            const OpenGL::ClearBufferBits& m_buffers_to_clear;

            std::vector<OpenGL::VKImageReferenceUniquePtr> m_backend_image_reference_ptrs;
        };
    };
};

#endif /* VKGL_VK_CLEAR_NODE_H */