/* VKGL (c) 2018 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef VKGL_GL_COMPATIBILITY_MANAGER_H
#define VKGL_GL_COMPATIBILITY_MANAGER_H

#include "OpenGL/types.h"

namespace OpenGL
{
    class GLCompatibilityManager
    {
    public:
         GLCompatibilityManager(const IContextObjectManagers* in_context_ptr);
        ~GLCompatibilityManager();

		OpenGL::FpeState*		get_fpe_state(void);
		
		uint32_t 					get_fpe_program				(void);
		bool 						update_fpe_vertex_buffers    (GLsizei in_vertex_num);
		bool 						update_fpe_uniform_resources(uint32_t in_program);
		bool 						begin_fpe_vao				(uint32_t in_program);
		bool 						end_fpe_vao					(uint32_t in_program);
		
		bool 						create_program_state			(uint32_t in_program);
		bool 						delete_program_state			(uint32_t in_program);



    private:
        /* Private type definitions */
        struct FpeProgramInfo
        {
    	    bool   EnableAlphaTest;
			GLint  AlphaFunc;
    
        
            bool    EnableRescaleNormal;
            bool    EnableNormalize;
            std::vector<bool>    EnableTextureUnit;
            std::vector<GLint>    TextureEnvMode;
            bool    EnableLighting;
            GLint	LightModelMode;
            std::vector<bool>    EnableLight;
            bool    EnableColorMaterial;
            GLint	FrontMaterialMode;
            GLint	BackMaterialMode;
            bool    EnableFog;
            GLint   FogMode;
            bool    EnableFogCoord;
            std::vector<bool>    EnableTexCoord;
            std::vector<bool>    EnableTexMatrix;
            bool    EnableNormal;
            bool    EnableColor;
            
            
        	bool 		operator==(const FpeProgramInfo& in_obj) const;
        	std::size_t operator()(const FpeProgramInfo& in_obj) const noexcept;
        };
        
        
        struct FpeProgramState
		{
			struct AttributeLocations
			{
				uint32_t color;
				uint32_t edge_flag;
				uint32_t fog_coord;
				uint32_t index;
				uint32_t normal;
				std::vector<uint32_t> tex_coords;
				uint32_t secondary_color;
				uint32_t vertex;
			};
			
			struct UniformLocations
			{
			//
            // Matrix state. p. 31, 32, 37, 39, 40.
            //
                uint32_t  gl_ModelViewMatrix;
                uint32_t  gl_ProjectionMatrix;
                uint32_t  gl_ModelViewProjectionMatrix;
    
                //
                // Derived matrix state that provides inverse and transposed versions
                // of the matrices above.
                //
                uint32_t  gl_NormalMatrix;
    
                uint32_t  gl_ModelViewMatrixInverse;
                uint32_t  gl_ProjectionMatrixInverse;
                uint32_t  gl_ModelViewProjectionMatrixInverse;
    
                uint32_t  gl_ModelViewMatrixTranspose;
                uint32_t  gl_ProjectionMatrixTranspose;
                uint32_t  gl_ModelViewProjectionMatrixTranspose;
    
                uint32_t  gl_ModelViewMatrixInverseTranspose;
                uint32_t  gl_ProjectionMatrixInverseTranspose;
                uint32_t  gl_ModelViewProjectionMatrixInverseTranspose;
    
                //
                // Normal scaling p. 39.
                //
                uint32_t gl_NormalScale;
    
                //
                // Material State p. 50, 55.
                //
                struct gl_MaterialParameters {
                    uint32_t  emission;    // Ecm
                    uint32_t  ambient;     // Acm
                    uint32_t  diffuse;     // Dcm
                    uint32_t  specular;    // Scm
                    uint32_t shininess;   // Srm
                };
                gl_MaterialParameters  gl_FrontMaterial;
                gl_MaterialParameters  gl_BackMaterial;
    
                //
                // Light State p 50, 53, 55.
                //
                struct gl_LightSourceParameters {
                    uint32_t  ambient;             // Acli
                    uint32_t  diffuse;             // Dcli
                    uint32_t  specular;            // Scli
                    uint32_t  position;            // Ppli
                    uint32_t  halfVector;          // Derived: Hi
                    uint32_t  spotDirection;       // Sdli
                    uint32_t spotExponent;        // Srli
                    uint32_t spotCutoff;          // Crli
                                                            // (range: [0.0,90.0], 180.0)
                    uint32_t spotCosCutoff;       // Derived: cos(Crli)
                                                            // (range: [1.0,0.0],-1.0)
                    uint32_t constantAttenuation; // K0
                    uint32_t linearAttenuation;   // K1
                    uint32_t quadraticAttenuation;// K2
                };
    
                struct gl_LightModelParameters {
                    uint32_t  ambient;       // Acs
                };
    
                gl_LightModelParameters  gl_LightModel;
    
                //
                // Derived state from products of light and material.
                //
                struct gl_LightModelProducts {
                    uint32_t  sceneColor;     // Derived. Ecm + Acm * Acs
                };
    
                gl_LightModelProducts gl_FrontLightModelProduct;
                gl_LightModelProducts gl_BackLightModelProduct;
    
                struct gl_LightProducts {
                    uint32_t  ambient;        // Acm * Acli
                    uint32_t  diffuse;        // Dcm * Dcli
                    uint32_t  specular;       // Scm * Scli
                };
    
                //
                // Fog p. 161
                //
                struct gl_FogParameters {
                    uint32_t  color;
                    uint32_t density;
                    uint32_t start;
                    uint32_t end;
                    uint32_t scale;   //  1 / (gl_FogEnd - gl_FogStart)
                };
    
                gl_FogParameters gl_Fog;
                
                //
                // Matrix state. p. 31, 32, 37, 39, 40.
                //
                            std::vector<uint32_t>  gl_TextureMatrix;
    
                //
                // Derived matrix state that provides inverse and transposed versions
                // of the matrices above.
                //
                            std::vector<uint32_t>  gl_TextureMatrixInverse;
    
                            std::vector<uint32_t>  gl_TextureMatrixTranspose;
    
                            std::vector<uint32_t>  gl_TextureMatrixInverseTranspose;
    
                //
                // Light State p 50, 53, 55.
                //
                            std::vector<gl_LightSourceParameters>  gl_LightSource;
    
                //
                // Derived state from products of light.
                //
                            std::vector<gl_LightProducts> gl_FrontLightProduct;
                            std::vector<gl_LightProducts> gl_BackLightProduct;
			
			
			uint32_t _gl_AlphaRef;
			
			std::vector<uint32_t>  gl_TextureEnvColor;
			std::vector<uint32_t>  _gl_TexSampler;
			
			};
			
			AttributeLocations attribute_locations;
			UniformLocations uniform_locations;
		
		};

        /* Private functions */

        bool init_fpe_state();
        
        OpenGL::FpeState::FpeVertexArrays::FpeClientArray* get_fpe_client_array_ptr(uint32_t in_index);

        /* Private variables */
        
        OpenGL::FpeState					m_fpe_state;
        FpeProgramInfo						m_temp_fpe_program_info;
        
        std::unordered_map<FpeProgramInfo, uint32_t, FpeProgramInfo> 	m_program_info_to_program_id_map;
        std::unordered_map<uint32_t, FpeProgramState> 					m_program_id_to_program_state_map;

        const IContextObjectManagers*		m_object_managers_ptr;
    };

    typedef std::unique_ptr<GLCompatibilityManager> GLCompatibilityManagerUniquePtr;
}

extern std::string string_format(const std::string fmt_str, ...);

#endif /* VKGL_GL_COMPATIBILITY_MANAGER_H */