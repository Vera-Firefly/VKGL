/* VKGL (c) 2018 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/macros.h"
#include "OpenGL/entrypoints/gl_entry_points_pack.h"
#include "OpenGL/frontend/gl_compatibility_manager.h"
#include "OpenGL/types.h"
#include "Anvil/include/misc/types.h"

OpenGL::GLCompatibilityManager::GLCompatibilityManager(const IContextObjectManagers* in_context_ptr)
	:m_object_managers_ptr(in_context_ptr)
{
    FUN_ENTRY(DEBUG_DEPTH);
    
	bool result = init_fpe_state();
	
	vkgl_assert(result != false);
	
}

OpenGL::GLCompatibilityManager::~GLCompatibilityManager()
{
    FUN_ENTRY(DEBUG_DEPTH);
    
    {
    	for (auto& program_info_to_id_iterator : m_program_info_to_program_id_map)
    	{
    		auto fpe_program = program_info_to_id_iterator.second;
    		
    		glDeleteProgram(fpe_program);
    	}
	}
}

bool OpenGL::GLCompatibilityManager::FpeProgramInfo::operator==(const FpeProgramInfo& in_obj) const
{
	bool result = false;
	result = (EnableAlphaTest 	== in_obj.EnableAlphaTest 		&&
			EnableLighting 		== in_obj.EnableLighting 			&&
			EnableFogCoord 		== in_obj.EnableFogCoord 		&&
			EnableTexCoord 		== in_obj.EnableTexCoord 		&&
			EnableFog 			== in_obj.EnableFog 			&&
			EnableNormal 		== in_obj.EnableNormal 		&&
			EnableColor 		== in_obj.EnableColor);
	
	{
        for (int n = 0;
        		n < in_obj.EnableTexCoord.size();
        		n++)
        {
        	if (result && in_obj.EnableTexCoord[n] )
        	{
            	if (result && in_obj.EnableTextureUnit[n] )
            	{
            		result = ( EnableTextureUnit[n] == in_obj.EnableTextureUnit[n] );
            		
                	if (result && in_obj.TextureEnvMode[n] )
                	{
                		result = ( TextureEnvMode[n] == in_obj.TextureEnvMode[n] );
                	}
            	}
            	if (result && in_obj.EnableTexMatrix[n] )
            	{
            		result = ( EnableTexMatrix[n] == in_obj.EnableTexMatrix[n] );
            	}
        	}
        }
        if (result && in_obj.EnableAlphaTest)
        {
            result = ( AlphaFunc == in_obj.AlphaFunc );
        }
        if (result && in_obj.EnableFog)
        {
            result = ( FogMode == in_obj.FogMode );
        }
        if (result && in_obj.EnableLighting)
        {
            result = (( EnableLight 		== in_obj.EnableLight ) 		&&
            		( EnableColorMaterial == in_obj.EnableColorMaterial ) &&
            		( LightModelMode 	== in_obj.LightModelMode ) 	);
            
            if (result && in_obj.EnableColorMaterial)
            {
                result = (( FrontMaterialMode == in_obj.FrontMaterialMode ) &&
                		( BackMaterialMode == in_obj.BackMaterialMode ) );
            }
        }
        if (result && in_obj.EnableNormal)
        {
            result = (( EnableRescaleNormal == in_obj.EnableRescaleNormal ) &&
            		( EnableNormalize 		== in_obj.EnableNormalize ) 		);
        }
	}
	
	return result;
}

std::size_t OpenGL::GLCompatibilityManager::FpeProgramInfo::operator()(const FpeProgramInfo& in_obj) const noexcept
{
	std::size_t result_hash = 17;
	
	{
    	{
            result_hash = result_hash * 31 + std::hash<bool>()				( in_obj.EnableAlphaTest );
            result_hash = result_hash * 31 + std::hash<bool>()				( in_obj.EnableLighting );
            result_hash = result_hash * 31 + std::hash<bool>()				( in_obj.EnableFogCoord );
            result_hash = result_hash * 31 + std::hash<std::vector<bool> >()( in_obj.EnableTexCoord );
            result_hash = result_hash * 31 + std::hash<bool>()				( in_obj.EnableFog );
            result_hash = result_hash * 31 + std::hash<bool>()				( in_obj.EnableNormal );
            result_hash = result_hash * 31 + std::hash<bool>()				( in_obj.EnableColor );
        }
        for (int n = 0;
        		n < in_obj.EnableTexCoord.size();
        		n++)
        {
        	if (in_obj.EnableTexCoord[n] )
        	{
            	if (in_obj.EnableTextureUnit[n] )
            	{
            		result_hash = result_hash * 31 + std::hash<bool>()				( in_obj.EnableTextureUnit[n] );
            		
                	if (in_obj.TextureEnvMode[n] )
                	{
                		result_hash = result_hash * 31 + std::hash<GLint>()				( in_obj.TextureEnvMode[n] );
                	}
            	}
            	if (in_obj.EnableTexMatrix[n] )
            	{
            		result_hash = result_hash * 31 + std::hash<bool>()				( in_obj.EnableTexMatrix[n] );
            	}
        	}
        }
        if (in_obj.EnableAlphaTest)
        {
            result_hash = result_hash * 31 + std::hash<int>()				( in_obj.AlphaFunc );
        }
        if (in_obj.EnableFog)
        {
            result_hash = result_hash * 31 + std::hash<int>()				( in_obj.FogMode );
        }
        if (in_obj.EnableLighting)
        {
            result_hash = result_hash * 31 + std::hash<std::vector<bool> >()( in_obj.EnableLight );
            result_hash = result_hash * 31 + std::hash<bool>()				( in_obj.EnableColorMaterial );
            result_hash = result_hash * 31 + std::hash<int>()				( in_obj.LightModelMode );
            
            if (in_obj.EnableColorMaterial)
            {
                result_hash = result_hash * 31 + std::hash<int>()				( in_obj.FrontMaterialMode );
                result_hash = result_hash * 31 + std::hash<int>()				( in_obj.BackMaterialMode );
            }
        }
        if (in_obj.EnableNormal)
        {
            result_hash = result_hash * 31 + std::hash<int>()				( in_obj.EnableRescaleNormal );
            result_hash = result_hash * 31 + std::hash<int>()				( in_obj.EnableNormalize );
        }
    }
	vkgl_printf("line = %d file = %s", __LINE__, __FILE__);
	{
    	uint32_t temp_value;
    	
    	vkgl_printf("line = %d", in_obj.EnableAlphaTest);
    	vkgl_printf("line = %d", in_obj.EnableLighting);
    	vkgl_printf("line = %d", in_obj.EnableFogCoord);
    	vkgl_printf("line = %d", in_obj.EnableColorMaterial);
    	vkgl_printf("line = %d", in_obj.EnableFog);
    	vkgl_printf("line = %d", in_obj.EnableNormal);
    	vkgl_printf("line = %d", in_obj.EnableColor);
    	vkgl_printf("line = %d", in_obj.AlphaFunc);
    	vkgl_printf("line = %d", in_obj.FogMode);
    	vkgl_printf("line = %d", in_obj.LightModelMode);
    	vkgl_printf("line = %d", in_obj.FrontMaterialMode);
    	vkgl_printf("line = %d", in_obj.BackMaterialMode);
    	vkgl_printf("line = %d", in_obj.EnableRescaleNormal);
    	vkgl_printf("line = %d", in_obj.EnableNormalize);
    	for (int n = 0; n < in_obj.EnableTextureUnit.size(); n++) vkgl_printf("in_obj.EnableTextureUnit[%d] = %d", n, temp_value = in_obj.EnableTextureUnit[n] );
    	for (int n = 0; n < in_obj.TextureEnvMode.size(); n++) vkgl_printf("in_obj.TextureEnvMode[%d] = %d", n, temp_value = in_obj.TextureEnvMode[n] );
    	for (int n = 0; n < in_obj.EnableLight.size(); n++) vkgl_printf("in_obj.EnableLight[%d] = %d", n, temp_value = in_obj.EnableLight[n] );
    	for (int n = 0; n < in_obj.EnableTexCoord.size(); n++) vkgl_printf("in_obj.EnableTexCoord[%d] = %d", n, temp_value = in_obj.EnableTexCoord[n] );
    	for (int n = 0; n < in_obj.EnableTexMatrix.size(); n++) vkgl_printf("in_obj.EnableTexMatrix[%d] = %d", n, temp_value = in_obj.EnableTexMatrix[n] );
	}
	return result_hash;
}

OpenGL::FpeState* OpenGL::GLCompatibilityManager::get_fpe_state(void)
{
    FUN_ENTRY(DEBUG_DEPTH);
    
	return &m_fpe_state;
}

uint32_t OpenGL::GLCompatibilityManager::get_fpe_program(void)
{
    FUN_ENTRY(DEBUG_DEPTH);
    
	uint32_t result_program = 0;
	
	/*
        //
        // Matrix state. p. 31, 32, 37, 39, 40.
        //
            "uniform mat4  gl_ModelViewMatrix;"
            "uniform mat4  gl_ProjectionMatrix;"
            "uniform mat4  gl_ModelViewProjectionMatrix;"

            //
            // Derived matrix state that provides inverse and transposed versions
            // of the matrices above.
            //
            "uniform mat3  gl_NormalMatrix;"

            "uniform mat4  gl_ModelViewMatrixInverse;"
            "uniform mat4  gl_ProjectionMatrixInverse;"
            "uniform mat4  gl_ModelViewProjectionMatrixInverse;"

            "uniform mat4  gl_ModelViewMatrixTranspose;"
            "uniform mat4  gl_ProjectionMatrixTranspose;"
            "uniform mat4  gl_ModelViewProjectionMatrixTranspose;"

            "uniform mat4  gl_ModelViewMatrixInverseTranspose;"
            "uniform mat4  gl_ProjectionMatrixInverseTranspose;"
            "uniform mat4  gl_ModelViewProjectionMatrixInverseTranspose;"

            //
            // Normal scaling p. 39.
            //
            "uniform float gl_NormalScale;"

            //
            // Material State p. 50, 55.
            //
            "struct gl_MaterialParameters {"
                "vec4  emission;"    // Ecm
                "vec4  ambient;"     // Acm
                "vec4  diffuse;"     // Dcm
                "vec4  specular;"    // Scm
                "float shininess;"   // Srm
            "};"
            "uniform gl_MaterialParameters  gl_FrontMaterial;"
            "uniform gl_MaterialParameters  gl_BackMaterial;"

            //
            // Light State p 50, 53, 55.
            //
            "struct gl_LightSourceParameters {"
                "vec4  ambient;"             // Acli
                "vec4  diffuse;"             // Dcli
                "vec4  specular;"            // Scli
                "vec4  position;"            // Ppli
                "vec4  halfVector;"          // Derived: Hi
                "vec3  spotDirection;"       // Sdli
                "float spotExponent;"        // Srli
                "float spotCutoff;"          // Crli
                                                        // (range: [0.0,90.0], 180.0)
                "float spotCosCutoff;"       // Derived: cos(Crli)
                                                        // (range: [1.0,0.0],-1.0)
                "float constantAttenuation;" // K0
                "float linearAttenuation;"   // K1
                "float quadraticAttenuation;"// K2
            "};"

            "struct gl_LightModelParameters {"
                "vec4  ambient;"       // Acs
            "};"

            "uniform gl_LightModelParameters  gl_LightModel;"

            //
            // Derived state from products of light and material.
            //
            "struct gl_LightModelProducts {"
                "vec4  sceneColor;"     // Derived. Ecm + Acm * Acs
            "};"

            "uniform gl_LightModelProducts gl_FrontLightModelProduct;"
            "uniform gl_LightModelProducts gl_BackLightModelProduct;"

            "struct gl_LightProducts {"
                "vec4  ambient;"        // Acm * Acli
                "vec4  diffuse;"        // Dcm * Dcli
                "vec4  specular;"       // Scm * Scli
            "};"

            //
            // Fog p. 161
            //
            "struct gl_FogParameters {"
                "vec4  color;"
                "float density;"
                "float start;"
                "float end;"
                "float scale;"   //  1 / (gl_FogEnd - gl_FogStart)
            "};"

            "uniform gl_FogParameters gl_Fog;"
            
            //
            // Matrix state. p. 31, 32, 37, 39, 40.
            //
                        "uniform mat4  gl_TextureMatrix[gl_MaxTextureCoords];"

            //
            // Derived matrix state that provides inverse and transposed versions
            // of the matrices above.
            //
                        "uniform mat4  gl_TextureMatrixInverse[gl_MaxTextureCoords];"

                        "uniform mat4  gl_TextureMatrixTranspose[gl_MaxTextureCoords];"

                        "uniform mat4  gl_TextureMatrixInverseTranspose[gl_MaxTextureCoords];"

            //
            // Light State p 50, 53, 55.
            //
                        "uniform gl_LightSourceParameters  gl_LightSource[gl_MaxLights];"

            //
            // Derived state from products of light.
            //
                        "uniform gl_LightProducts gl_FrontLightProduct[gl_MaxLights];"
                        "uniform gl_LightProducts gl_BackLightProduct[gl_MaxLights];"
	*/
	
	
	m_temp_fpe_program_info.EnableTextureUnit.resize(m_fpe_state.state.texture_unit_enabled.size	(), false);
	m_temp_fpe_program_info.TextureEnvMode.resize(m_fpe_state.texture_env.texture_env_mode.size(), 0);
	m_temp_fpe_program_info.EnableLight.resize		(m_fpe_state.state.light_enabled.size			(), false);
	m_temp_fpe_program_info.EnableTexMatrix.resize(m_fpe_state.state.tex_matrix_enabled.size	(), false);
	m_temp_fpe_program_info.EnableTexCoord.resize(m_fpe_state.vertex_arrays.tex_coord_arrays.size(), false);
	
	
	{
			m_temp_fpe_program_info.EnableAlphaTest 	= m_fpe_state.state.alpha_test_enabled;
			m_temp_fpe_program_info.EnableRescaleNormal = m_fpe_state.state.rescale_normal_enabled;
			m_temp_fpe_program_info.EnableNormalize 	= m_fpe_state.state.normalize_enabled;
			m_temp_fpe_program_info.EnableTextureUnit 	= m_fpe_state.state.texture_unit_enabled;
			m_temp_fpe_program_info.TextureEnvMode 	= m_fpe_state.texture_env.texture_env_mode;
			m_temp_fpe_program_info.EnableLighting 		= m_fpe_state.state.lighting_enabled;
			m_temp_fpe_program_info.EnableFogCoord 		= m_fpe_state.vertex_arrays.fog_coord_array.enabled;
			m_temp_fpe_program_info.EnableLight 		= m_fpe_state.state.light_enabled;
			m_temp_fpe_program_info.EnableColorMaterial = m_fpe_state.state.color_material_enabled;
			m_temp_fpe_program_info.EnableFog 			= m_fpe_state.state.fog_enabled;
			m_temp_fpe_program_info.EnableTexMatrix 	= m_fpe_state.state.tex_matrix_enabled;
			m_temp_fpe_program_info.EnableNormal 		= m_fpe_state.vertex_arrays.normal_array.enabled;
			m_temp_fpe_program_info.EnableColor 		= m_fpe_state.vertex_arrays.color_array.enabled;
	
			m_temp_fpe_program_info.AlphaFunc 			= m_fpe_state.alpha_test.alpha_func;
			m_temp_fpe_program_info.FogMode 			= m_fpe_state.fog.mode;
			m_temp_fpe_program_info.LightModelMode 		= m_fpe_state.light.light_model_state.two_side;
			m_temp_fpe_program_info.FrontMaterialMode 	= m_fpe_state.light.front_material_state.mode;
			m_temp_fpe_program_info.BackMaterialMode 	= m_fpe_state.light.back_material_state.mode;
			
			for (int i = 0;
					i < m_fpe_state.vertex_arrays.tex_coord_arrays.size();
					++i)
			{
				m_temp_fpe_program_info.EnableTexCoord[i] 		= m_fpe_state.vertex_arrays.tex_coord_arrays[i].enabled;
			}
	}
	
	auto program_info_to_id_iterator = m_program_info_to_program_id_map.find(m_temp_fpe_program_info);
	
	if (program_info_to_id_iterator != m_program_info_to_program_id_map.end() )
	{
		result_program = program_info_to_id_iterator->second;
	}
	else
	{
		GLuint vertex_shader_id;
		GLuint fragment_shader_id;
		GLuint program_id;
		
		
		
		
		
		/* process Vertex Shader Code */
		{
    		std::string VertexShaderFramework = 
    
    "#version 120" "\n"
    "" "\n"
    "//Varyings:" "\n"
    "varying lowp vec4 	vColor;" "\n"
    "varying lowp vec2	vFactor;" "\n"
    "" "\n"
    "//local variables:" "\n"
    "highp vec4		lColor;" "\n"
    "highp vec4		lEye;" "\n"
    "highp vec3		lNormal;" "\n"
    "lowp vec4		lMaterialAmbient;" "\n"
    "lowp vec4		lMaterialDiffuse;" "\n"
    "lowp vec4		lMaterialSpecular;" "\n"
    "lowp vec4		lMaterialEmissive;" "\n"
    "float			lMaterialSpecExponent;" "\n"
    "" "\n"
    "//functions:" "\n"
    "////POINT_A////" "\n"
    "////POINT_B////" "\n"
    "" "\n"
    "//main function" "\n"
    "void main(){" "\n"
    "	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;" "\n"
    "	lEye = gl_ModelViewMatrix * gl_Vertex;" "\n"
    "	" "\n"
    "	////POINT_G////" "\n"
    "	" "\n"
    "	//Normal" "\n"
    "	////POINT_C////" "\n"
    "	" "\n"
    "	//Lighting" "\n"
    "	////POINT_D////" "\n"
    "	" "\n"
    "	//Fog" "\n"
    "	////POINT_E////" "\n"
    "	" "\n"
    "	//TexCoord" "\n"
    "	////POINT_F////" "\n"
    "	" "\n"
    "}" "\n"
    
        	;
        	
        	std::string VertexShaderComputeFogFunction =
    
    "void ComputeFog(float dist){" "\n"
    "	////POINT_A////" "\n"
    "	clamp(vFactor.x, 0.0, 1.0);" "\n"
    "}" "\n"
    
    		;
    		
    		/* process VertexShaderComputeFogFunction */
    		{
    			std::string POINT_A = "";
    			
    			auto& FogMode = m_temp_fpe_program_info.FogMode;
    			
    				if(FogMode == GL_LINEAR){
                		POINT_A = "vFactor.x = (gl_Fog.end - dist) * gl_Fog.scale;";
                	} else if(FogMode == GL_EXP){
                		POINT_A = "vFactor.x = exp(-(dist * gl_Fog.density));";
                	} else {
                		POINT_A = "vFactor.x = dist * gl_Fog.density;"
                					"vFactor.x = exp(-(vFactor.x * vFactor.x));";
                	}
            	
            	auto F_A = VertexShaderComputeFogFunction.find("////POINT_A////");
            	VertexShaderComputeFogFunction.replace(F_A, std::string("////POINT_A////").size(), POINT_A);
    		}
    
    
    
    
        	std::string VertexShaderComputeLightFunction =
    
    "vec4 ComputeLightFrom(int i){" "\n"
    "	highp vec3 	dpos;" "\n"
    "	highp vec4	col;" "\n"
    "	float 	dist, dist2, spot;" "\n"
    "	float 	att;" "\n"
    "	float 	ndoth, ndotl;" "\n"
    "	" "\n"
    "	dpos = gl_LightSource[i].position.xyz;" "\n"
    "	att = 1.0;	" "\n"
    "" "\n"
    "	if (gl_LightSource[i].position.w != 0.0){" "\n"
    "		dpos -= lEye.xyz;" "\n"
    "		" "\n"
    "		if (gl_LightSource[i].constantAttenuation != 1.0 || gl_LightSource[i].linearAttenuation != 0.0 ||" "\n"
    "			gl_LightSource[i].quadraticAttenuation != 0.0){" "\n"
    "			dist2 = dot(dpos, dpos);" "\n"
    "			dist = sqrt(dist2);" "\n"
    "			att = 1.0 / dot(vec3(gl_LightSource[i].constantAttenuation, gl_LightSource[i].linearAttenuation, gl_LightSource[i].quadraticAttenuation), vec3(1.0, dist, dist2));" "\n"
    "		}" "\n"
    "		" "\n"
    "		dpos = normalize(dpos);" "\n"
    "		if(gl_LightSource[i].spotCutoff < 180.0){" "\n"
    "			spot = dot(-dpos, gl_LightSource[i].spotDirection);" "\n"
    "			if(spot >= cos(radians(gl_LightSource[i].spotCutoff))){" "\n"
    "				att *= pow(spot, gl_LightSource[i].spotExponent);" "\n"
    "			} else {" "\n"
    "				return vec4(0,0,0,0);" "\n"
    "			}" "\n"
    "		}" "\n"
    "	}" "\n"
    "	" "\n"
    "	col = (gl_LightSource[i].ambient * lMaterialAmbient);" "\n"
    "	ndotl = dot(lNormal, dpos);" "\n"
    "	if (ndotl > 0.0){" "\n"
    "		col += ndotl * (gl_LightSource[i].diffuse * lMaterialDiffuse);" "\n"
    "	}" "\n"
    "	" "\n"
    "	dpos.z += 1.0;" "\n"
    "	dpos = normalize(dpos);" "\n"
    "	ndoth = dot(lNormal, dpos);" "\n"
    "	if (ndoth > 0.0){ " "\n"
    "		col += pow(ndoth, lMaterialSpecExponent) * (lMaterialSpecular * gl_LightSource[i].specular);" "\n"
    "	}" "\n"
    "	" "\n"
    "	return att * col;" "\n"
    "}" "\n"
    "" "\n"
    "void ComputeLighting(){" "\n"
    "" "\n"
    "	if (lNormal.z <= 0.0 && ////POINT_A////){" "\n"
    "    	lMaterialAmbient = gl_FrontMaterial.ambient;" "\n"
    "    	lMaterialDiffuse = gl_FrontMaterial.diffuse;" "\n"
    "    	lMaterialSpecular = gl_FrontMaterial.specular;" "\n"
    "    	lMaterialEmissive = gl_FrontMaterial.emission;" "\n"
    "    	lMaterialSpecExponent = gl_FrontMaterial.shininess;" "\n"
    "    	////POINT_B////" "\n"
    "	} else {" "\n"
    "		lNormal = -lNormal;" "\n"
    "    	lMaterialAmbient = gl_BackMaterial.ambient;" "\n"
    "    	lMaterialDiffuse = gl_BackMaterial.diffuse;" "\n"
    "    	lMaterialSpecular = gl_BackMaterial.specular;" "\n"
    "    	lMaterialEmissive = gl_BackMaterial.emission;" "\n"
    "    	lMaterialSpecExponent = gl_BackMaterial.shininess;" "\n"
    "    	////POINT_C////" "\n"
    "	}	" "\n"
    "		" "\n"
    "	vColor = lMaterialEmissive + lMaterialAmbient * gl_LightModel.ambient;" "\n"
    "	////POINT_D////" "\n"
    "	vColor.w = lMaterialDiffuse.w;" "\n"
    "}" "\n"
    
    		;
    
        	/* process VertexShaderComputeLightFunction */
    		{
    			std::string POINT_A = "";
    			std::string POINT_B = "";
    			std::string POINT_C = "";
    			std::string POINT_D = "";
    			
    			auto& LightModel_mode = m_temp_fpe_program_info.LightModelMode;
    			auto& EnableColorMaterial = m_temp_fpe_program_info.EnableColorMaterial;
    			auto& FrontMaterial_mode = m_temp_fpe_program_info.FrontMaterialMode;
    			auto& BackMaterial_mode = m_temp_fpe_program_info.BackMaterialMode;
    			auto& EnableLight = m_temp_fpe_program_info.EnableLight;
    			
    			
    			
    				if(LightModel_mode == GL_TRUE){
                		POINT_A = "true";
                	} else {
                		POINT_A = "false";
                	}
                	
                	if (EnableColorMaterial){
                		if (FrontMaterial_mode == GL_AMBIENT){
                			POINT_B = "lMaterialAmbient = lColor;";
                		} else if (FrontMaterial_mode == GL_DIFFUSE){
                			POINT_B = "lMaterialDiffuse = lColor;";
                		} else if (FrontMaterial_mode == GL_AMBIENT_AND_DIFFUSE){
                			POINT_B = "lMaterialAmbient = lColor;"
                						"lMaterialDiffuse = lColor;";
                		} else if (FrontMaterial_mode == GL_SPECULAR){
                			POINT_B = "lMaterialSpecular = lColor;";
                		} else {
                			POINT_B = "lMaterialEmissive =  lColor;";
                		}
                	}
                	
                	if (EnableColorMaterial){
                		if (BackMaterial_mode == GL_AMBIENT){
                			POINT_C = "lMaterialAmbient = lColor;";
                		} else if (BackMaterial_mode == GL_DIFFUSE){
                			POINT_C = "lMaterialDiffuse = lColor;";
                		} else if (BackMaterial_mode == GL_AMBIENT_AND_DIFFUSE){
                			POINT_C = "lMaterialAmbient = lColor;"
                						"MaterialDiffuse = lColor;";
                		} else if (BackMaterial_mode == GL_SPECULAR){
                			POINT_C = "lMaterialSpecular = lColor;";
                		} else {
                			POINT_C = "lMaterialEmissive =  lColor;";
                		}
                	}
                	
                	for(int i = 0; i < EnableLight.size(); i++){
                		if (EnableLight[i]){
                			POINT_D += string_format("vColor += ComputeLightFrom(%d);\n", i);
                		}
                	}
                	
            	
            	auto F_A = VertexShaderComputeLightFunction.find("////POINT_A////");
            	VertexShaderComputeLightFunction.replace(F_A, std::string("////POINT_A////").size(), POINT_A);
            	auto F_B = VertexShaderComputeLightFunction.find("////POINT_B////");
            	VertexShaderComputeLightFunction.replace(F_B, std::string("////POINT_B////").size(), POINT_B);
            	auto F_C = VertexShaderComputeLightFunction.find("////POINT_C////");
            	VertexShaderComputeLightFunction.replace(F_C, std::string("////POINT_C////").size(), POINT_C);
            	auto F_D = VertexShaderComputeLightFunction.find("////POINT_D////");
            	VertexShaderComputeLightFunction.replace(F_D, std::string("////POINT_D////").size(), POINT_D);
    		}
        	
        	/* process VertexShaderFramework */
    		{
    			std::string POINT_A = "";
    			std::string POINT_B = "";
    			std::string POINT_C = "";
    			std::string POINT_D = "";
    			std::string POINT_E = "";
    			std::string POINT_F = "";
    			std::string POINT_G = "";
    			
    			auto& EnableNormal 			= m_temp_fpe_program_info.EnableNormal;
    			auto& EnableRescaleNormal = m_temp_fpe_program_info.EnableRescaleNormal;
    			auto& EnableNormalize 		= m_temp_fpe_program_info.EnableNormalize;
    			auto& EnableLighting 		= m_temp_fpe_program_info.EnableLighting;
    			auto& EnableColor 			= m_temp_fpe_program_info.EnableColor;
    			auto& EnableFog 			= m_temp_fpe_program_info.EnableFog;
    			auto& EnableFogCoord 		= m_temp_fpe_program_info.EnableFogCoord;
    			auto& EnableTexCoord 		= m_temp_fpe_program_info.EnableTexCoord;
    			auto& EnableTexMatrix 		= m_temp_fpe_program_info.EnableTexMatrix;
    			
    			
    			
                	if (EnableColor){
                		POINT_G += string_format("lColor = gl_Color;");
                	} else {
                		POINT_G += string_format("lColor = vec4(0.0);");
                	}
                	
                	if (EnableNormal){
                		POINT_C += string_format("lNormal = gl_NormalMatrix * gl_Normal;");
                    	if (EnableRescaleNormal){
                    		POINT_C += string_format("lNormal = gl_NormalScale * lNormal;");
                    	}
                    	if (EnableNormalize){
                    		POINT_C += string_format("lNormal = normalize(lNormal);");
                    	}
                	}
                	
                	if (EnableLighting){
                		POINT_B += VertexShaderComputeLightFunction;
                		POINT_D += string_format("ComputeLighting();");
                	} else {
                		POINT_D += string_format("vColor = lColor;");
                	}
                	
                	POINT_E += string_format("vFactor.x = 1.0;");
                	if (EnableFog){
                		POINT_A += VertexShaderComputeFogFunction;
                		if (EnableFogCoord){
                			POINT_E += string_format("ComputeFog(gl_FogCoord);");
                		}else{
                			POINT_E += string_format("ComputeFog(-lEye.z);");
                		}	
                	}
                	
                	for(int i = 0; i < EnableTexCoord.size(); i++){
                		if (EnableTexCoord[i]){
                			POINT_F += string_format("gl_TexCoord[%d] = gl_MultiTexCoord%d", i, i);
                			if (EnableTexMatrix[i]){
                				POINT_F += string_format(" * gl_TextureMatrix[%d]", i);
            				}
            				POINT_F += string_format(";\n");
                		}
                	}
            	
            	
            	
            	auto F_A = VertexShaderFramework.find("////POINT_A////");
            	VertexShaderFramework.replace(F_A, std::string("////POINT_A////").size(), POINT_A);
            	auto F_B = VertexShaderFramework.find("////POINT_B////");
            	VertexShaderFramework.replace(F_B, std::string("////POINT_B////").size(), POINT_B);
            	auto F_C = VertexShaderFramework.find("////POINT_C////");
            	VertexShaderFramework.replace(F_C, std::string("////POINT_C////").size(), POINT_C);
            	auto F_D = VertexShaderFramework.find("////POINT_D////");
            	VertexShaderFramework.replace(F_D, std::string("////POINT_D////").size(), POINT_D);
            	auto F_E = VertexShaderFramework.find("////POINT_E////");
            	VertexShaderFramework.replace(F_E, std::string("////POINT_E////").size(), POINT_E);
            	auto F_F = VertexShaderFramework.find("////POINT_F////");
            	VertexShaderFramework.replace(F_F, std::string("////POINT_F////").size(), POINT_F);
            	auto F_G = VertexShaderFramework.find("////POINT_G////");
            	VertexShaderFramework.replace(F_G, std::string("////POINT_G////").size(), POINT_G);
    		}
        	
        	const char* vsh_str = VertexShaderFramework.c_str();
        	
        	vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
        	
        	glShaderSource(vertex_shader_id, 1, &vsh_str, NULL);
			
			glCompileShader(vertex_shader_id);
			
			{
    			int success;
                glGetShaderiv(vertex_shader_id, GL_COMPILE_STATUS, &success);
                
                vkgl_assert(success);
                if (!success)
                {
                    char infoLog[1024];
                    glGetShaderInfoLog(vertex_shader_id, 1024, NULL, infoLog);
                    vkgl_printf("ERROR: failed to complie fpe vertex shader:\n>>>>INFO>>>>\n%s\n>>>>>>>>", infoLog);
                }
        	}
        	
        	
    	}
    	
		/* process Fragment Shader Code */
		{
    		std::string FragmentShaderFramework = 
    
    "#version 120" "\n"
    "" "\n"
    "//Uniforms:" "\n"
    "uniform sampler2D _gl_TexSampler[gl_MaxTextureUnits];" "\n"
    "uniform float _gl_AlphaRef;" "\n"
    "" "\n"
    "//Varyings:" "\n"
    "varying lowp vec4 	vColor;" "\n"
    "varying lowp vec2	vFactor;" "\n"
    "" "\n"
    "//local variables:" "\n"
    "vec4 lFragColor;" "\n"
    "" "\n"
    "//main function" "\n"
    "void main(){" "\n"
    "	////POINT_D////" "\n"
    "	" "\n"
    "	//Texture" "\n"
    "	////POINT_A////" "\n"
    "	" "\n"
    "	//Fog" "\n"
    "	////POINT_B////" "\n"
    "	" "\n"
    "	//AlphaTest" "\n"
    "	////POINT_C////" "\n"
    "	" "\n"
    "	////POINT_E////" "\n"
    "}" "\n"
    
        	;
        	
        	
        	/* process FragmentShaderFramework */
    		{
    			std::string POINT_A = "";
    			std::string POINT_B = "";
    			std::string POINT_C = "";
    			std::string POINT_D = "lFragColor = vColor;";
    			std::string POINT_E = "gl_FragColor = lFragColor;";
    			
    			auto& EnableAlphaTest 		= m_temp_fpe_program_info.EnableAlphaTest;
    			auto& AlphaFunc 			= m_temp_fpe_program_info.AlphaFunc;
    			auto& EnableFog 			= m_temp_fpe_program_info.EnableFog;
    			auto& TextureEnvMode 			= m_temp_fpe_program_info.TextureEnvMode;
    			auto& EnableTextureUnit 	= m_temp_fpe_program_info.EnableTextureUnit;
    			auto& EnableTexCoord 		= m_temp_fpe_program_info.EnableTexCoord;
    			
    			
    			
                    if (EnableAlphaTest){
                        switch(AlphaFunc){
                            case GL_NEVER:
                                POINT_C += string_format("%s", "discard;");
                                break;
                
                            case GL_LESS:
                                POINT_C += string_format("%s", "if (lFragColor.w >= _gl_AlphaRef) discard;");
                                break;
                
                            case GL_EQUAL:
                                POINT_C += string_format("%s", "if (lFragColor.w != _gl_AlphaRef) discard;");
                                break;
                
                            case GL_LEQUAL:
                                POINT_C += string_format("%s", "if (lFragColor.w > _gl_AlphaRef) discard;");
                                break;
                
                            case GL_GREATER:
                                POINT_C += string_format("%s", "if (lFragColor.w <= _gl_AlphaRef) discard;");
                                break;
                
                            case GL_NOTEQUAL:
                                POINT_C += string_format("%s", "if (lFragColor.w == _gl_AlphaRef) discard;");
                                break;
                
                            case GL_GEQUAL:
                                POINT_C += string_format("%s", "if (lFragColor.w < _gl_AlphaRef) discard;");
                                break;
                
                            default:
                                vkgl_assert_fail();
                
                        }
                    }
                	
                	if (EnableFog){
        				POINT_B += string_format("lFragColor = mix(gl_Fog.color, lFragColor, vFactor.x);");
                	}
                	
                	for(int i = 0; i < EnableTexCoord.size(); i++){
                		if (EnableTexCoord[i] && EnableTextureUnit[i]){
                			POINT_A += string_format("vec4 TexColor%d = texture2DProj(_gl_TexSampler[%d], gl_TexCoord[%d]);", i, i, i);
                			POINT_A += string_format("\n");
            			}
        			}
                	for(int i = 0; i < EnableTexCoord.size(); i++){
                		if (EnableTexCoord[i] && EnableTextureUnit[i]){
                            switch(TextureEnvMode[i])
                            {
                                case GL_REPLACE:
                                    POINT_A += string_format("lFragColor = TexColor%d;", i);
                                    break;
                
                                case GL_MODULATE:
                                    POINT_A += string_format("lFragColor *= TexColor%d;", i);
                                    break;
                
                                case GL_DECAL:
                                    POINT_A += string_format("lFragColor.rgb = mix(lFragColor.rgb, TexColor%d.rgb, TexColor%d.a);", i, i);
                                    break;
                
                                case GL_BLEND:
                                    POINT_A += string_format("lFragColor.rgb = mix(lFragColor.rgb, gl_TextureEnvColor[%d].rgb, TexColor%d.rgb);", i, i);
                                    POINT_A += string_format("lFragColor.a *= TexColor%d.a;", i);
                                    break;
                
                                case GL_ADD:
                                    POINT_A += string_format("lFragColor.rgb += TexColor%d.rgb;", i);
                                    POINT_A += string_format("lFragColor.a *= TexColor%d.a;", i);
                                    break;
                
                                case GL_COMBINE:
                                    vkgl_not_implemented();
                                    break;
                
                            	default:
                            		vkgl_assert_fail();
                            
                            }
                            POINT_A += string_format("\n");
                        }
                	}
                	
            	
            	
            	
            	auto F_A = FragmentShaderFramework.find("////POINT_A////");
            	FragmentShaderFramework.replace(F_A, std::string("////POINT_A////").size(), POINT_A);
            	auto F_B = FragmentShaderFramework.find("////POINT_B////");
            	FragmentShaderFramework.replace(F_B, std::string("////POINT_B////").size(), POINT_B);
            	auto F_C = FragmentShaderFramework.find("////POINT_C////");
            	FragmentShaderFramework.replace(F_C, std::string("////POINT_C////").size(), POINT_C);
            	auto F_D = FragmentShaderFramework.find("////POINT_D////");
            	FragmentShaderFramework.replace(F_D, std::string("////POINT_D////").size(), POINT_D);
            	auto F_E = FragmentShaderFramework.find("////POINT_E////");
            	FragmentShaderFramework.replace(F_E, std::string("////POINT_E////").size(), POINT_E);
    		}
        	
        	const char* fsh_str = FragmentShaderFramework.c_str();
        	
        	fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
        	
        	glShaderSource(fragment_shader_id, 1, &fsh_str, NULL);
			
			glCompileShader(fragment_shader_id);
			
			{
    			int success;
                glGetShaderiv(fragment_shader_id, GL_COMPILE_STATUS, &success);
                
                vkgl_assert(success);
                if (!success)
                {
                    char infoLog[1024];
                    glGetShaderInfoLog(fragment_shader_id, 1024, NULL, infoLog);
                    vkgl_printf("ERROR: failed to complie fpe fragment shader:\n>>>>INFO>>>>\n%s\n>>>>>>>>", infoLog);
                }
        	}
    	}
    	
    	
    	
    	
    	program_id = glCreateProgram();
    	
    	glAttachShader(program_id, vertex_shader_id);
        glAttachShader(program_id, fragment_shader_id);
        
        glLinkProgram(program_id);
        
		{
			int success;
            glGetProgramiv(program_id, GL_LINK_STATUS, &success);
            
            vkgl_assert(success);
            if (!success)
            {
                char infoLog[1024];
                glGetProgramInfoLog(program_id, 1024, NULL, infoLog);
                vkgl_printf("ERROR: failed to link fpe program:\n>>>>INFO>>>>\n%s\n>>>>>>>>", infoLog);
            }
    	}
    	
    	m_program_info_to_program_id_map[m_temp_fpe_program_info] = program_id;
    	
    	result_program = program_id;
    	
	}
	
	
	
	return result_program;
}

bool OpenGL::GLCompatibilityManager::update_fpe_vertex_buffers(GLsizei in_vertex_num)
{
    FUN_ENTRY(DEBUG_DEPTH);
    
	bool result = false;
	
	const auto 														previous_current_bound_buffer = m_fpe_state.state.current_bound_buffer;
	std::vector<OpenGL::FpeState::FpeVertexArrays::FpeClientArray*> fpe_enabled_client_array_ptrs;
	std::vector<GLsizei> 											new_fpe_buffer_sizes;
	
	{
    	for (int i = 0;
    			i < 7 + m_fpe_state.vertex_arrays.tex_coord_arrays.size();
    			i++)
    	{
    		auto fpe_client_array_ptr = get_fpe_client_array_ptr(i);
    		if (fpe_client_array_ptr == nullptr)
    		{
    			break;
    		}
    		
    		bool&			enabled 	= fpe_client_array_ptr->enabled;
            if (enabled == false)
            {
            	continue;
            }
            
    		uint32_t&		bound_buffer 	= fpe_client_array_ptr->bound_buffer;
    		uint32_t&		fpe_buffer 		= fpe_client_array_ptr->fpe_buffer;
            if (bound_buffer != 0)
            {
            	if (fpe_buffer != 0)
            	{
            		glDeleteBuffers(1,
            					&fpe_buffer);
            		
            		fpe_buffer = 0;
            	}
            	
            	continue;
            }
            
    		GLint			size 			= fpe_client_array_ptr->size;
            GLenum		  type 			= fpe_client_array_ptr->type;
            GLsizei			stride 			= fpe_client_array_ptr->stride;
            const GLvoid* pointer 			= fpe_client_array_ptr->pointer;
            
            GLsizei			n_bytes_of_type	= OpenGL::Utils::get_n_bytes_for_vertex_attribute_array_type(OpenGL::Utils::get_vertex_attribute_array_type_for_gl_enum(type) );
        	GLsizei 		new_fpe_buffer_size = in_vertex_num * ((stride == 0) ? size * n_bytes_of_type
        																			: stride);
        	
        	fpe_enabled_client_array_ptrs.push_back(fpe_client_array_ptr);
        	new_fpe_buffer_sizes.push_back        (new_fpe_buffer_size);
        }
        
        vkgl_assert(fpe_enabled_client_array_ptrs.size() == new_fpe_buffer_sizes.size() );
    }
    
    /* Merges some interleaved client vertex arrays into a single VBO if possible.. */
    {
    	std::vector<uint32_t> index_to_fpe_merged_client_array_ptr_map;
        
        for (int i = 0;
        		i < fpe_enabled_client_array_ptrs.size();
        		i++)
        {
            const uint8_t* start_ptr 			= nullptr;
            const uint8_t* end_ptr 				= nullptr;
            GLsizei        final_fpe_buffer_size = 0;
            
            auto fpe_client_array_ptr = fpe_enabled_client_array_ptrs.at(i);
            auto new_fpe_buffer_size = new_fpe_buffer_sizes.at		  (i);
            
    		uint32_t		fpe_buffer 		= fpe_client_array_ptr->fpe_buffer;
    		GLsizei			fpe_buffer_size = fpe_client_array_ptr->fpe_buffer_size;
    		
            const uint8_t* pointer 			= (const uint8_t*)fpe_client_array_ptr->pointer;
            
            start_ptr = pointer;
            end_ptr  = pointer + new_fpe_buffer_size;
            
            /* Iterate through each vertex array and find the one that can be merged. */
            for (int n = 0;
            		n < fpe_enabled_client_array_ptrs.size();
            		n++)
            {
    	        auto next_fpe_client_array_ptr = fpe_enabled_client_array_ptrs.at(n);
                auto next_new_fpe_buffer_size = new_fpe_buffer_sizes.at		  (n);
                
                const uint8_t* next_pointer 	= (const uint8_t*)next_fpe_client_array_ptr->pointer;
                
                /* Ensure that two vertex arrays are adjacent or have shared parts. */
                if (start_ptr <= next_pointer + next_new_fpe_buffer_size &&
                	end_ptr >= next_pointer									)
                {
                    /* Update the final scope of the arrays to be merged */
                    if (next_pointer < start_ptr)
                    {
                    	start_ptr = next_pointer;
                    }
                    if (next_pointer + next_new_fpe_buffer_size > end_ptr)
                    {
                    	end_ptr = next_pointer + next_new_fpe_buffer_size;
                    }
                    
                    index_to_fpe_merged_client_array_ptr_map.push_back(n);
                }
            }
            
            final_fpe_buffer_size = end_ptr - start_ptr;
            
            /* Update the data of the merged arrays. */
            {
            	if (final_fpe_buffer_size > fpe_buffer_size)
            	{
    	        	if (fpe_buffer != 0)
                	{
                		glDeleteBuffers(1,
                						&fpe_buffer);
                	}
                	
            		glGenBuffers(1,
            					&fpe_buffer);
            		
            		glBindBuffer(GL_ARRAY_BUFFER,
            					fpe_buffer);
            		
            		glBufferData(GL_ARRAY_BUFFER,
            					final_fpe_buffer_size,
            					start_ptr,
            					GL_DYNAMIC_DRAW);
            		
            		glBindBuffer(GL_ARRAY_BUFFER,
            					0);
            	}
            	else
            	{
            		glBindBuffer(GL_ARRAY_BUFFER,
            					fpe_buffer);
            		
            		glBufferSubData(GL_ARRAY_BUFFER,
            						0,
            						final_fpe_buffer_size,
            						start_ptr);
            		
            		glBindBuffer(GL_ARRAY_BUFFER,
            					0);
            	}
        	}
            
            /* Also update the same info to each merged array. */
            {
            	for (auto& index : index_to_fpe_merged_client_array_ptr_map)
            	{
            		auto current_fpe_client_array_ptr				= fpe_enabled_client_array_ptrs.at(index);
            		
            		current_fpe_client_array_ptr->fpe_buffer 		= fpe_buffer;
            		current_fpe_client_array_ptr->fpe_buffer_size 	= final_fpe_buffer_size;
            		/* The pointer is updated to a specific offset of the merged vertex buffer
            		 * and used by subsequent glVertexAttribPointer() calls.
            		 */
            		current_fpe_client_array_ptr->pointer 			= (const GLvoid*)((const uint8_t*)current_fpe_client_array_ptr->pointer - start_ptr);
            		
            	}
            	
            	for (auto& index : index_to_fpe_merged_client_array_ptr_map)
            	{
            		/* Remove the merged vertex arrays. */
            		fpe_enabled_client_array_ptrs.erase(fpe_enabled_client_array_ptrs.begin() + index);
            	}
            	
            	index_to_fpe_merged_client_array_ptr_map.clear();
            }
            
            /* All done.
             * Reset it to start processing the next set of vertex arrays to be merged.
             */
            i = 0;
        }
    }
    
	glBindBuffer(GL_ARRAY_BUFFER,
				previous_current_bound_buffer);
	
	result = true;
	return result;
}

bool OpenGL::GLCompatibilityManager::update_fpe_uniform_resources(uint32_t in_program)
{
    FUN_ENTRY(DEBUG_DEPTH);
    
	bool result = false;
	
	auto program_iterator = m_program_id_to_program_state_map.find(in_program);
	vkgl_assert(program_iterator != m_program_id_to_program_state_map.end() );
	
	auto& program_state = program_iterator->second;
	auto& uniform_locations = program_state.uniform_locations;
	
	
	auto& state = m_fpe_state.state;
	
	
	{
		
	// gl_ModelViewMatrix
		if (uniform_locations.gl_ModelViewMatrix != UINT_MAX)
        {
        	glUniformMatrix4fv(uniform_locations.gl_ModelViewMatrix,
        						1,
        						false,
        						glm::value_ptr(m_fpe_state.matrices.gl_ModelViewMatrix)
        						);
        }
	
	// gl_ProjectionMatrix
		if (uniform_locations.gl_ProjectionMatrix != UINT_MAX)
        {
        	glUniformMatrix4fv(uniform_locations.gl_ProjectionMatrix,
        						1,
        						false,
        						glm::value_ptr(m_fpe_state.matrices.gl_ProjectionMatrix)
        						);
        }
	
	// gl_ModelViewProjectionMatrix
		if (uniform_locations.gl_ModelViewProjectionMatrix != UINT_MAX)
        {
        	{
        		auto& gl_ModelViewMatrix 		= m_fpe_state.matrices.gl_ModelViewMatrix;
        		auto& gl_ProjectionMatrix 			= m_fpe_state.matrices.gl_ProjectionMatrix;
        		auto& gl_ModelViewProjectionMatrix = m_fpe_state.matrices.gl_ModelViewProjectionMatrix;
        		
        		gl_ModelViewProjectionMatrix = gl_ModelViewMatrix * gl_ProjectionMatrix;
        	}
        	
        	glUniformMatrix4fv(uniform_locations.gl_ModelViewProjectionMatrix,
        						1,
        						false,
        						glm::value_ptr(m_fpe_state.matrices.gl_ModelViewProjectionMatrix)
        						);
        }
	
	// gl_NormalMatrix
		if (uniform_locations.gl_NormalMatrix != UINT_MAX)
        {
        	{
        		auto& gl_ModelViewMatrix 		= m_fpe_state.matrices.gl_ModelViewMatrix;
        		auto& gl_NormalMatrix = m_fpe_state.matrices.gl_NormalMatrix;
        		
        		gl_NormalMatrix = glm::transpose(glm::inverse(gl_ModelViewMatrix) );
        	}
        	
        	glUniformMatrix4fv(uniform_locations.gl_NormalMatrix,
        						1,
        						false,
        						glm::value_ptr(m_fpe_state.matrices.gl_NormalMatrix)
        						);
        }
	
	// gl_ModelViewMatrixInverse
		if (uniform_locations.gl_ModelViewMatrixInverse != UINT_MAX)
        {
        	{
        		auto& gl_ModelViewMatrix 		= m_fpe_state.matrices.gl_ModelViewMatrix;
        		auto& gl_ModelViewMatrixInverse = m_fpe_state.matrices.gl_ModelViewMatrixInverse;
        		
        		gl_ModelViewMatrixInverse = glm::inverse(gl_ModelViewMatrix);
        	}
        	
        	glUniformMatrix4fv(uniform_locations.gl_ModelViewMatrixInverse,
        						1,
        						false,
        						glm::value_ptr(m_fpe_state.matrices.gl_ModelViewMatrixInverse)
        						);
        }
	
	// gl_ProjectionMatrixInverse
		if (uniform_locations.gl_ProjectionMatrixInverse != UINT_MAX)
        {
        	{
        		auto& gl_ProjectionMatrix 			= m_fpe_state.matrices.gl_ProjectionMatrix;
        		auto& gl_ProjectionMatrixInverse = m_fpe_state.matrices.gl_ProjectionMatrixInverse;
        		
        		gl_ProjectionMatrixInverse = glm::inverse(gl_ProjectionMatrix);
        	}
        	
        	glUniformMatrix4fv(uniform_locations.gl_ProjectionMatrixInverse,
        						1,
        						false,
        						glm::value_ptr(m_fpe_state.matrices.gl_ProjectionMatrixInverse)
        						);
        }
	
	// gl_ModelViewProjectionMatrixInverse
		if (uniform_locations.gl_ModelViewProjectionMatrixInverse != UINT_MAX)
        {
        	{
        		auto& gl_ModelViewMatrix 		= m_fpe_state.matrices.gl_ModelViewMatrix;
        		auto& gl_ProjectionMatrix 			= m_fpe_state.matrices.gl_ProjectionMatrix;
        		auto& gl_ModelViewProjectionMatrixInverse = m_fpe_state.matrices.gl_ModelViewProjectionMatrixInverse;
        		
        		gl_ModelViewProjectionMatrixInverse = glm::inverse(gl_ModelViewMatrix * gl_ProjectionMatrix);
        	}
        	
        	glUniformMatrix4fv(uniform_locations.gl_ModelViewProjectionMatrixInverse,
        						1,
        						false,
        						glm::value_ptr(m_fpe_state.matrices.gl_ModelViewProjectionMatrixInverse)
        						);
        }
	
	// gl_ModelViewMatrixTranspose
		if (uniform_locations.gl_ModelViewMatrixTranspose != UINT_MAX)
        {
        	{
        		auto& gl_ModelViewMatrix 		= m_fpe_state.matrices.gl_ModelViewMatrix;
        		auto& gl_ModelViewMatrixTranspose = m_fpe_state.matrices.gl_ModelViewMatrixInverse;
        		
        		gl_ModelViewMatrixTranspose = glm::transpose(gl_ModelViewMatrix);
        	}
        	
        	glUniformMatrix4fv(uniform_locations.gl_ModelViewMatrixTranspose,
        						1,
        						false,
        						glm::value_ptr(m_fpe_state.matrices.gl_ModelViewMatrixTranspose)
        						);
        }
	
	// gl_ProjectionMatrixTranspose
		if (uniform_locations.gl_ProjectionMatrixTranspose != UINT_MAX)
        {
        	{
        		auto& gl_ProjectionMatrix 			= m_fpe_state.matrices.gl_ProjectionMatrix;
        		auto& gl_ProjectionMatrixTranspose = m_fpe_state.matrices.gl_ProjectionMatrixInverse;
        		
        		gl_ProjectionMatrixTranspose = glm::transpose(gl_ProjectionMatrix);
        	}
        	
        	glUniformMatrix4fv(uniform_locations.gl_ProjectionMatrixTranspose,
        						1,
        						false,
        						glm::value_ptr(m_fpe_state.matrices.gl_ProjectionMatrixTranspose)
        						);
        }
	
	// gl_ModelViewProjectionMatrixTranspose
		if (uniform_locations.gl_ModelViewProjectionMatrixTranspose != UINT_MAX)
        {
        	{
        		auto& gl_ModelViewMatrix 		= m_fpe_state.matrices.gl_ModelViewMatrix;
        		auto& gl_ProjectionMatrix 			= m_fpe_state.matrices.gl_ProjectionMatrix;
        		auto& gl_ModelViewProjectionMatrixTranspose = m_fpe_state.matrices.gl_ModelViewProjectionMatrixTranspose;
        		
        		gl_ModelViewProjectionMatrixTranspose = glm::transpose(gl_ModelViewMatrix * gl_ProjectionMatrix);
        	}
        	
        	glUniformMatrix4fv(uniform_locations.gl_ModelViewProjectionMatrixTranspose,
        						1,
        						false,
        						glm::value_ptr(m_fpe_state.matrices.gl_ModelViewProjectionMatrixTranspose)
        						);
        }
	
	// gl_ModelViewMatrixInverseTranspose
		if (uniform_locations.gl_ModelViewMatrixInverseTranspose != UINT_MAX)
        {
        	{
        		auto& gl_ModelViewMatrix 		= m_fpe_state.matrices.gl_ModelViewMatrix;
        		auto& gl_ModelViewMatrixInverseTranspose = m_fpe_state.matrices.gl_ModelViewMatrixInverseTranspose;
        		
        		gl_ModelViewMatrixInverseTranspose = glm::transpose(glm::inverse(gl_ModelViewMatrix) );
        	}
        	
        	glUniformMatrix4fv(uniform_locations.gl_ModelViewMatrixInverseTranspose,
        						1,
        						false,
        						glm::value_ptr(m_fpe_state.matrices.gl_ModelViewMatrixInverseTranspose)
        						);
        }
	
	// gl_ProjectionMatrixInverseTranspose
		if (uniform_locations.gl_ProjectionMatrixInverseTranspose != UINT_MAX)
        {
        	{
        		auto& gl_ProjectionMatrix 			= m_fpe_state.matrices.gl_ProjectionMatrix;
        		auto& gl_ProjectionMatrixInverseTranspose = m_fpe_state.matrices.gl_ProjectionMatrixInverseTranspose;
        		
        		gl_ProjectionMatrixInverseTranspose = glm::transpose(glm::inverse(gl_ProjectionMatrix) );
        	}
        	
        	glUniformMatrix4fv(uniform_locations.gl_ProjectionMatrixInverseTranspose,
        						1,
        						false,
        						glm::value_ptr(m_fpe_state.matrices.gl_ProjectionMatrixInverseTranspose)
        						);
        }
	
	// gl_ModelViewProjectionMatrixInverseTranspose
		if (uniform_locations.gl_ModelViewProjectionMatrixInverseTranspose != UINT_MAX)
        {
        	{
        		auto& gl_ModelViewMatrix 		= m_fpe_state.matrices.gl_ModelViewMatrix;
        		auto& gl_ProjectionMatrix 			= m_fpe_state.matrices.gl_ProjectionMatrix;
        		auto& gl_ModelViewProjectionMatrixInverseTranspose = m_fpe_state.matrices.gl_ModelViewProjectionMatrixInverseTranspose;
        		
        		gl_ModelViewProjectionMatrixInverseTranspose = glm::transpose(glm::inverse(gl_ModelViewMatrix * gl_ProjectionMatrix) );
        	}
        	
        	glUniformMatrix4fv(uniform_locations.gl_ModelViewProjectionMatrixInverseTranspose,
        						1,
        						false,
        						glm::value_ptr(m_fpe_state.matrices.gl_ModelViewProjectionMatrixInverseTranspose)
        						);
        }
	
	
    	for (int i = 0;
    			i < uniform_locations.gl_TextureMatrix.size();
    			i++)
    	{
    		if (state.tex_matrix_enabled[i] == true)
    		{
	// gl_TextureMatrix[]
        		if (uniform_locations.gl_TextureMatrix[i] != UINT_MAX)
                {
                	glUniformMatrix4fv(uniform_locations.gl_TextureMatrix[i],
                						1,
                						false,
                						glm::value_ptr(m_fpe_state.matrices.gl_TextureMatrix[i])
                						);
                }
        	
	// gl_TextureMatrixInverse[]
        		if (uniform_locations.gl_TextureMatrixInverse[i] != UINT_MAX)
                {
                	{
                		auto& gl_TextureMatrix 		= m_fpe_state.matrices.gl_TextureMatrix[i];
                		auto& gl_TextureMatrixInverse = m_fpe_state.matrices.gl_TextureMatrixInverse[i];
                		
                		gl_TextureMatrixInverse = glm::inverse(gl_TextureMatrix);
                	}
                	
                	glUniformMatrix4fv(uniform_locations.gl_TextureMatrixInverse[i],
                						1,
                						false,
                						glm::value_ptr(m_fpe_state.matrices.gl_TextureMatrixInverse[i])
                						);
                }
        	
	// gl_TextureMatrixTranspose[]
        		if (uniform_locations.gl_TextureMatrixTranspose[i] != UINT_MAX)
                {
                	{
                		auto& gl_TextureMatrix 		= m_fpe_state.matrices.gl_TextureMatrix[i];
                		auto& gl_TextureMatrixTranspose = m_fpe_state.matrices.gl_TextureMatrixTranspose[i];
                		
                		gl_TextureMatrixTranspose = glm::transpose(gl_TextureMatrix);
                	}
                	
                	glUniformMatrix4fv(uniform_locations.gl_TextureMatrixTranspose[i],
                						1,
                						false,
                						glm::value_ptr(m_fpe_state.matrices.gl_TextureMatrixTranspose[i])
                						);
                }
        	
	// gl_TextureMatrixInverseTranspose[]
        		if (uniform_locations.gl_TextureMatrixInverseTranspose[i] != UINT_MAX)
                {
                	{
                		auto& gl_TextureMatrix 		= m_fpe_state.matrices.gl_TextureMatrix[i];
                		auto& gl_TextureMatrixInverseTranspose = m_fpe_state.matrices.gl_TextureMatrixInverseTranspose[i];
                		
                		gl_TextureMatrixInverseTranspose = glm::transpose(glm::inverse(gl_TextureMatrix) );
                	}
                	
                	glUniformMatrix4fv(uniform_locations.gl_TextureMatrixInverseTranspose[i],
                						1,
                						false,
                						glm::value_ptr(m_fpe_state.matrices.gl_TextureMatrixInverseTranspose[i])
                						);
                }
    		}
    	}
	
	
	
	
	
	// gl_NormalScale
		if (state.rescale_normal_enabled == true &&
			uniform_locations.gl_NormalScale != UINT_MAX)
        {
        	glUniform1f(uniform_locations.gl_NormalScale,
        				m_fpe_state.matrices.gl_NormalScale
        				);
        }
		
		
		
		
	// gl_Fog
    		if (state.fog_enabled == true &&
    			uniform_locations.gl_Fog.color != UINT_MAX)
    		{
    			{
    				m_fpe_state.fog.scale = 1.0f / (m_fpe_state.fog.end - m_fpe_state.fog.start);
    			}
    			
    			glUniform4fv(uniform_locations.gl_Fog.color,
    						1,
    						glm::value_ptr(m_fpe_state.fog.color)
    						);
    			glUniform1f(uniform_locations.gl_Fog.density,
    						m_fpe_state.fog.density
    						);
    			glUniform1f(uniform_locations.gl_Fog.start,
    						m_fpe_state.fog.start
    						);
    			glUniform1f(uniform_locations.gl_Fog.end,
    						m_fpe_state.fog.end
    						);
    			glUniform1f(uniform_locations.gl_Fog.scale,
    						m_fpe_state.fog.scale
    						);
    		}
	
	
	
    	if (state.lighting_enabled == true)
    	{
	// gl_FrontMaterial
    		if (uniform_locations.gl_FrontMaterial.emission != UINT_MAX)
    		{
    			glUniform4fv(uniform_locations.gl_FrontMaterial.emission,
    						1,
    						glm::value_ptr(m_fpe_state.light.gl_FrontMaterial.emission)
    						);
    			glUniform4fv(uniform_locations.gl_FrontMaterial.ambient,
    						1,
    						glm::value_ptr(m_fpe_state.light.gl_FrontMaterial.ambient)
    						);
    			glUniform4fv(uniform_locations.gl_FrontMaterial.diffuse,
    						1,
    						glm::value_ptr(m_fpe_state.light.gl_FrontMaterial.diffuse)
    						);
    			glUniform4fv(uniform_locations.gl_FrontMaterial.specular,
    						1,
    						glm::value_ptr(m_fpe_state.light.gl_FrontMaterial.specular)
    						);
    			glUniform1f(uniform_locations.gl_FrontMaterial.shininess,
    						m_fpe_state.light.gl_FrontMaterial.shininess
    						);
    		}
	
	// gl_BackMaterial
    		if (uniform_locations.gl_BackMaterial.emission != UINT_MAX)
    		{
    			glUniform4fv(uniform_locations.gl_BackMaterial.emission,
    						1,
    						glm::value_ptr(m_fpe_state.light.gl_BackMaterial.emission)
    						);
    			glUniform4fv(uniform_locations.gl_BackMaterial.ambient,
    						1,
    						glm::value_ptr(m_fpe_state.light.gl_BackMaterial.ambient)
    						);
    			glUniform4fv(uniform_locations.gl_BackMaterial.diffuse,
    						1,
    						glm::value_ptr(m_fpe_state.light.gl_BackMaterial.diffuse)
    						);
    			glUniform4fv(uniform_locations.gl_BackMaterial.specular,
    						1,
    						glm::value_ptr(m_fpe_state.light.gl_BackMaterial.specular)
    						);
    			glUniform1f(uniform_locations.gl_BackMaterial.shininess,
    						m_fpe_state.light.gl_BackMaterial.shininess
    						);
    		}
	
	// gl_FrontLightModelProduct
    		if (uniform_locations.gl_FrontLightModelProduct.sceneColor != UINT_MAX)
    		{
    			{
    				auto& Acs = m_fpe_state.light.gl_LightModel.ambient;
    				auto& Acm = m_fpe_state.light.gl_FrontMaterial.ambient;
    				auto& Ecm = m_fpe_state.light.gl_FrontMaterial.emission;
    				auto& sceneColor = m_fpe_state.light.gl_FrontLightModelProduct.sceneColor;
    				
    				sceneColor = Ecm + Acm * Acs;
    			}
    			
    			glUniform4fv(uniform_locations.gl_FrontLightModelProduct.sceneColor,
    						1,
    						glm::value_ptr(m_fpe_state.light.gl_FrontLightModelProduct.sceneColor)
    						);
    		}
	
	// gl_BackLightModelProduct
    		if (uniform_locations.gl_BackLightModelProduct.sceneColor != UINT_MAX)
    		{
    			{
    				auto& Acs = m_fpe_state.light.gl_LightModel.ambient;
    				auto& Acm = m_fpe_state.light.gl_BackMaterial.ambient;
    				auto& Ecm = m_fpe_state.light.gl_BackMaterial.emission;
    				auto& sceneColor = m_fpe_state.light.gl_BackLightModelProduct.sceneColor;
    				
    				sceneColor = Ecm + Acm * Acs;
    			}
    			
    			glUniform4fv(uniform_locations.gl_BackLightModelProduct.sceneColor,
    						1,
    						glm::value_ptr(m_fpe_state.light.gl_BackLightModelProduct.sceneColor)
    						);
    		}
	
	// gl_LightModel
    		if (uniform_locations.gl_LightModel.ambient != UINT_MAX)
    		{
    			glUniform4fv(uniform_locations.gl_LightModel.ambient,
    						1,
    						glm::value_ptr(m_fpe_state.light.gl_LightModel.ambient)
    						);
    		}
	
	
	
	// gl_LightSource[]
        	for (int i = 0;
        			i < uniform_locations.gl_LightSource.size();
        			i++)
        	{
        		if (state.light_enabled[i] == true &&
        			uniform_locations.gl_LightSource[i].ambient != UINT_MAX)
        		{
        			{
        				m_fpe_state.light.gl_LightSource[i].spotCosCutoff = std::cos(m_fpe_state.light.gl_LightSource[i].spotCutoff);
        			}
        			
        			glUniform4fv(uniform_locations.gl_LightSource[i].ambient,
        						1,
        						glm::value_ptr(m_fpe_state.light.gl_LightSource[i].ambient)
        						);
        			glUniform4fv(uniform_locations.gl_LightSource[i].diffuse,
        						1,
        						glm::value_ptr(m_fpe_state.light.gl_LightSource[i].diffuse)
        						);
        			glUniform4fv(uniform_locations.gl_LightSource[i].specular,
        						1,
        						glm::value_ptr(m_fpe_state.light.gl_LightSource[i].specular)
        						);
        			glUniform4fv(uniform_locations.gl_LightSource[i].position,
        						1,
        						glm::value_ptr(m_fpe_state.light.gl_LightSource[i].position)
        						);
        			glUniform4fv(uniform_locations.gl_LightSource[i].halfVector,
        						1,
        						glm::value_ptr(m_fpe_state.light.gl_LightSource[i].halfVector)
        						);
        			glUniform3fv(uniform_locations.gl_LightSource[i].spotDirection,
        						1,
        						glm::value_ptr(m_fpe_state.light.gl_LightSource[i].spotDirection)
        						);
        			glUniform1f(uniform_locations.gl_LightSource[i].spotExponent,
        						m_fpe_state.light.gl_LightSource[i].spotExponent
        						);
        			glUniform1f(uniform_locations.gl_LightSource[i].spotCutoff,
        						m_fpe_state.light.gl_LightSource[i].spotCutoff
        						);
        			glUniform1f(uniform_locations.gl_LightSource[i].spotCosCutoff,
        						m_fpe_state.light.gl_LightSource[i].spotCosCutoff
        						);
        			glUniform1f(uniform_locations.gl_LightSource[i].constantAttenuation,
        						m_fpe_state.light.gl_LightSource[i].constantAttenuation
        						);
        			glUniform1f(uniform_locations.gl_LightSource[i].linearAttenuation,
        						m_fpe_state.light.gl_LightSource[i].linearAttenuation
        						);
        			glUniform1f(uniform_locations.gl_LightSource[i].quadraticAttenuation,
        						m_fpe_state.light.gl_LightSource[i].quadraticAttenuation
        						);
        		}
    		}
    	
    	
	// gl_FrontLightProduct[]
        	for (int i = 0;
        			i < uniform_locations.gl_FrontLightProduct.size();
    			i++)
        	{
        		if (state.light_enabled[i] == true &&
        			uniform_locations.gl_FrontLightProduct[i].ambient != UINT_MAX)
        		{
        			{
        				m_fpe_state.light.gl_FrontLightProduct[i].ambient = m_fpe_state.light.gl_FrontMaterial.ambient * m_fpe_state.light.gl_LightSource[i].ambient;
        				m_fpe_state.light.gl_FrontLightProduct[i].diffuse = m_fpe_state.light.gl_FrontMaterial.diffuse * m_fpe_state.light.gl_LightSource[i].diffuse;
        				m_fpe_state.light.gl_FrontLightProduct[i].specular = m_fpe_state.light.gl_FrontMaterial.specular * m_fpe_state.light.gl_LightSource[i].specular;
        			}
        			
        			glUniform4fv(uniform_locations.gl_FrontLightProduct[i].ambient,
        						1,
        						glm::value_ptr(m_fpe_state.light.gl_FrontLightProduct[i].ambient)
        						);
        			glUniform4fv(uniform_locations.gl_FrontLightProduct[i].diffuse,
        						1,
        						glm::value_ptr(m_fpe_state.light.gl_FrontLightProduct[i].diffuse)
        						);
        			glUniform4fv(uniform_locations.gl_FrontLightProduct[i].specular,
        						1,
        						glm::value_ptr(m_fpe_state.light.gl_FrontLightProduct[i].specular)
        						);
        		}
    		}
    	
	// gl_BackLightProduct[]
        	for (int i = 0;
        			i < uniform_locations.gl_BackLightProduct.size();
        			i++)
        	{
        		if (state.light_enabled[i] == true &&
        			uniform_locations.gl_BackLightProduct[i].ambient != UINT_MAX)
        		{
        			{
        				m_fpe_state.light.gl_BackLightProduct[i].ambient = m_fpe_state.light.gl_BackMaterial.ambient * m_fpe_state.light.gl_LightSource[i].ambient;
        				m_fpe_state.light.gl_BackLightProduct[i].diffuse = m_fpe_state.light.gl_BackMaterial.diffuse * m_fpe_state.light.gl_LightSource[i].diffuse;
        				m_fpe_state.light.gl_BackLightProduct[i].specular = m_fpe_state.light.gl_BackMaterial.specular * m_fpe_state.light.gl_LightSource[i].specular;
        			}
        			
        			glUniform4fv(uniform_locations.gl_BackLightProduct[i].ambient,
        						1,
        						glm::value_ptr(m_fpe_state.light.gl_BackLightProduct[i].ambient)
        						);
        			glUniform4fv(uniform_locations.gl_BackLightProduct[i].diffuse,
        						1,
        						glm::value_ptr(m_fpe_state.light.gl_BackLightProduct[i].diffuse)
        						);
        			glUniform4fv(uniform_locations.gl_BackLightProduct[i].specular,
        						1,
        						glm::value_ptr(m_fpe_state.light.gl_BackLightProduct[i].specular)
        						);
        		}
    		}
    	}
	
	
	
	
	// _gl_AlphaRef
		if (state.alpha_test_enabled == true &&
			uniform_locations._gl_AlphaRef != UINT_MAX)
        {
        	glUniform1f(uniform_locations._gl_AlphaRef,
        				m_fpe_state.alpha_test.alpha_ref
        				);
        }
	
	// gl_TextureEnvColor[]
    	for (int i = 0;
    			i < uniform_locations.gl_TextureEnvColor.size();
    			i++)
    	{
    		if (state.texture_unit_enabled[i] == true &&
    			uniform_locations.gl_TextureEnvColor[i] != UINT_MAX)
    		{
    			glUniform4fv(uniform_locations.gl_TextureEnvColor[i],
    						1,
    						glm::value_ptr(m_fpe_state.texture_env.texture_env_color[i])
    						);
    		}
		}
	
	// _gl_TexSampler[]
    	for (int i = 0;
    			i < uniform_locations._gl_TexSampler.size();
    			i++)
    	{
    		if (state.texture_unit_enabled[i] == true &&
    			uniform_locations._gl_TexSampler[i] != UINT_MAX)
    		{
    			glUniform1i(uniform_locations._gl_TexSampler[i],
    						i
    						);
    		}
		}
	
	
	
	
	}
	
	result = true;
	return result;
}

bool OpenGL::GLCompatibilityManager::begin_fpe_vao(uint32_t in_program)
{
    FUN_ENTRY(DEBUG_DEPTH);
    
	bool result = false;
	
	auto program_iterator = m_program_id_to_program_state_map.find(in_program);
	vkgl_assert(program_iterator != m_program_id_to_program_state_map.end() );
	
	auto& program_state = program_iterator->second;
	auto& attribute_locations = program_state.attribute_locations;
	
	
	auto& vertex_arrays = m_fpe_state.vertex_arrays;
	
	
	{
    		const auto previous_current_bound_buffer = m_fpe_state.state.current_bound_buffer;
		
    		if (vertex_arrays.color_array.enabled == true &&
    			attribute_locations.color != UINT_MAX)
    		{
            	glBindBuffer(GL_ARRAY_BUFFER,
            				(vertex_arrays.color_array.bound_buffer != 0) ? vertex_arrays.color_array.bound_buffer
            															: vertex_arrays.color_array.fpe_buffer);
    			
    			glVertexAttribPointer(attribute_locations.color,
    								vertex_arrays.color_array.size,
    								vertex_arrays.color_array.type,
    								GL_FALSE,
    								vertex_arrays.color_array.stride,
    								vertex_arrays.color_array.pointer);
    			
    			glEnableVertexAttribArray(attribute_locations.color);
    		}
    	
    		if (vertex_arrays.vertex_array.enabled == true &&
    			attribute_locations.vertex != UINT_MAX)
    		{
            	glBindBuffer(GL_ARRAY_BUFFER,
            				(vertex_arrays.vertex_array.bound_buffer != 0) ? vertex_arrays.vertex_array.bound_buffer
            															: vertex_arrays.vertex_array.fpe_buffer);
    			
    			glVertexAttribPointer(attribute_locations.vertex,
    								vertex_arrays.vertex_array.size,
    								vertex_arrays.vertex_array.type,
    								GL_FALSE,
    								vertex_arrays.vertex_array.stride,
    								vertex_arrays.vertex_array.pointer);
    			
    			glEnableVertexAttribArray(attribute_locations.vertex);
    		}
    	
    		if (vertex_arrays.normal_array.enabled == true &&
    			attribute_locations.normal != UINT_MAX)
    		{
            	glBindBuffer(GL_ARRAY_BUFFER,
            				(vertex_arrays.normal_array.bound_buffer != 0) ? vertex_arrays.normal_array.bound_buffer
            															: vertex_arrays.normal_array.fpe_buffer);
    			
    			glVertexAttribPointer(attribute_locations.normal,
    								vertex_arrays.normal_array.size,
    								vertex_arrays.normal_array.type,
    								GL_FALSE,
    								vertex_arrays.normal_array.stride,
    								vertex_arrays.normal_array.pointer);
    			
    			glEnableVertexAttribArray(attribute_locations.normal);
    		}
    	
    		if (vertex_arrays.fog_coord_array.enabled == true &&
    			attribute_locations.fog_coord != UINT_MAX)
    		{
            	glBindBuffer(GL_ARRAY_BUFFER,
            				(vertex_arrays.fog_coord_array.bound_buffer != 0) ? vertex_arrays.fog_coord_array.bound_buffer
            															: vertex_arrays.fog_coord_array.fpe_buffer);
    			
    			glVertexAttribPointer(attribute_locations.fog_coord,
    								vertex_arrays.fog_coord_array.size,
    								vertex_arrays.fog_coord_array.type,
    								GL_FALSE,
    								vertex_arrays.fog_coord_array.stride,
    								vertex_arrays.fog_coord_array.pointer);
    			
    			glEnableVertexAttribArray(attribute_locations.fog_coord);
    		}
    	
    		if (vertex_arrays.secondary_color_array.enabled == true &&
    			attribute_locations.secondary_color != UINT_MAX)
    		{
            	glBindBuffer(GL_ARRAY_BUFFER,
            				(vertex_arrays.secondary_color_array.bound_buffer != 0) ? vertex_arrays.secondary_color_array.bound_buffer
            															: vertex_arrays.secondary_color_array.fpe_buffer);
    			
    			glVertexAttribPointer(attribute_locations.secondary_color,
    								vertex_arrays.secondary_color_array.size,
    								vertex_arrays.secondary_color_array.type,
    								GL_FALSE,
    								vertex_arrays.secondary_color_array.stride,
    								vertex_arrays.secondary_color_array.pointer);
    			
    			glEnableVertexAttribArray(attribute_locations.secondary_color);
    		}
    	
    	for (int i = 0;
    			i < vertex_arrays.tex_coord_arrays.size();
    			i++)
    	{
    		if (vertex_arrays.tex_coord_arrays[i].enabled == true &&
    			attribute_locations.tex_coords[i] != UINT_MAX)
    		{
            	glBindBuffer(GL_ARRAY_BUFFER,
            				(vertex_arrays.tex_coord_arrays[i].bound_buffer != 0) ? vertex_arrays.tex_coord_arrays[i].bound_buffer
            															: vertex_arrays.tex_coord_arrays[i].fpe_buffer);
    			
    			glVertexAttribPointer(attribute_locations.tex_coords[i],
    								vertex_arrays.tex_coord_arrays[i].size,
    								vertex_arrays.tex_coord_arrays[i].type,
    								GL_FALSE,
    								vertex_arrays.tex_coord_arrays[i].stride,
    								vertex_arrays.tex_coord_arrays[i].pointer);
    			
    			glEnableVertexAttribArray(attribute_locations.tex_coords[i]);
    		}
    	}
    	
    	glBindBuffer(GL_ARRAY_BUFFER,
    				previous_current_bound_buffer);
	}
	
	
	result = true;
	return result;
}

bool OpenGL::GLCompatibilityManager::end_fpe_vao(uint32_t in_program)
{
    FUN_ENTRY(DEBUG_DEPTH);
    
	bool result = false;
	
	auto program_iterator = m_program_id_to_program_state_map.find(in_program);
	vkgl_assert(program_iterator != m_program_id_to_program_state_map.end() );
	
	auto& program_state = program_iterator->second;
	auto& attribute_locations = program_state.attribute_locations;
	
	
	auto& vertex_arrays = m_fpe_state.vertex_arrays;
	
	
	{
    		if (vertex_arrays.color_array.enabled == true &&
    			attribute_locations.color != UINT_MAX)
    		{
    			glDisableVertexAttribArray(attribute_locations.color);
    		}
    	
    		if (vertex_arrays.vertex_array.enabled == true &&
    			attribute_locations.vertex != UINT_MAX)
    		{
    			glDisableVertexAttribArray(attribute_locations.vertex);
    		}
    	
    		if (vertex_arrays.normal_array.enabled == true &&
    			attribute_locations.normal != UINT_MAX)
    		{
    			glDisableVertexAttribArray(attribute_locations.normal);
    		}
    	
    		if (vertex_arrays.fog_coord_array.enabled == true &&
    			attribute_locations.fog_coord != UINT_MAX)
    		{
    			glDisableVertexAttribArray(attribute_locations.fog_coord);
    		}
    	
    		if (vertex_arrays.secondary_color_array.enabled == true &&
    			attribute_locations.secondary_color != UINT_MAX)
    		{
    			glDisableVertexAttribArray(attribute_locations.secondary_color);
    		}
    	
    	for (int i = 0;
    			i < vertex_arrays.tex_coord_arrays.size();
    			i++)
    	{
    		if (vertex_arrays.tex_coord_arrays[i].enabled == true &&
    			attribute_locations.tex_coords[i] != UINT_MAX)
    		{
    			glDisableVertexAttribArray(attribute_locations.tex_coords[i]);
    		}
    	}
	}
	
	
	result = true;
	return result;
}

bool OpenGL::GLCompatibilityManager::create_program_state(uint32_t in_program)
{
    FUN_ENTRY(DEBUG_DEPTH);
    
	bool result = false;
	
	GLint max_lights = 0;
	GLint max_tex_coords = 0;
	glGetIntegerv(GL_MAX_LIGHTS, &max_lights);
	glGetIntegerv(GL_MAX_TEXTURE_COORDS, &max_tex_coords);
	
    const OpenGL::PostLinkData* post_link_data_ptr;
    
	{
    	auto gl_program_manager_ptr = m_object_managers_ptr->get_program_manager_ptr();
        vkgl_assert(gl_program_manager_ptr != nullptr);
        
        auto program_reference_ptr = gl_program_manager_ptr->acquire_current_latest_snapshot_reference(in_program);
        vkgl_assert(program_reference_ptr != nullptr);
        
        gl_program_manager_ptr->get_program_post_link_data_ptr(program_reference_ptr->get_payload().id,
        																&program_reference_ptr->get_payload().time_marker,
        																&post_link_data_ptr);
    	vkgl_assert(post_link_data_ptr != nullptr);
	}
	
	auto& active_attributes 						= post_link_data_ptr->active_attributes;
	auto& active_attribute_name_to_location_map = post_link_data_ptr->active_attribute_name_to_location_map;
	auto& active_uniforms 							= post_link_data_ptr->active_uniforms;
	auto& active_uniform_by_name_map 			= post_link_data_ptr->active_uniform_by_name_map;
	
	
	
	OpenGL::GLCompatibilityManager::FpeProgramState new_program_state;
	
	
	
	auto& attribute_locations = new_program_state.attribute_locations;
	auto& uniform_locations = new_program_state.uniform_locations;
	
	{
		// attribute
		{
    	    attribute_locations.tex_coords.resize(max_tex_coords, UINT_MAX);
    	}
    	
    	// uniform
    	{
        	uniform_locations.gl_TextureMatrix.resize				(max_tex_coords, UINT_MAX);
        	uniform_locations.gl_TextureMatrixInverse.resize		(max_tex_coords, UINT_MAX);
        	uniform_locations.gl_TextureMatrixTranspose.resize		(max_tex_coords, UINT_MAX);
        	uniform_locations.gl_TextureMatrixInverseTranspose.resize(max_tex_coords, UINT_MAX);
        	
        	uniform_locations.gl_LightSource.resize		(max_lights);
        	uniform_locations.gl_FrontLightProduct.resize(max_lights);
        	uniform_locations.gl_BackLightProduct.resize(max_lights);
        	
        	uniform_locations.gl_TextureEnvColor.resize(max_tex_coords, UINT_MAX);
        	uniform_locations._gl_TexSampler.resize(max_tex_coords, UINT_MAX);
		}
	}
	
	
	
	
	
	
	
	
	
	//// Attributes
	{
	
    		attribute_locations.color = active_attribute_name_to_location_map.find(std::string("gl_Color") ) != active_attribute_name_to_location_map.end() ?
    									active_attribute_name_to_location_map.at(std::string("gl_Color") ) : UINT_MAX;
    	
    		attribute_locations.normal = active_attribute_name_to_location_map.find(std::string("gl_Normal") ) != active_attribute_name_to_location_map.end() ?
    									active_attribute_name_to_location_map.at(std::string("gl_Normal") ) : UINT_MAX;
    	
    		attribute_locations.secondary_color = active_attribute_name_to_location_map.find(std::string("gl_SecondaryColor") ) != active_attribute_name_to_location_map.end() ?
    									active_attribute_name_to_location_map.at(std::string("gl_SecondaryColor") ) : UINT_MAX;
    	
    		attribute_locations.vertex = active_attribute_name_to_location_map.find(std::string("gl_Vertex") ) != active_attribute_name_to_location_map.end() ?
    									active_attribute_name_to_location_map.at(std::string("gl_Vertex") ) : UINT_MAX;
    	
    		attribute_locations.fog_coord = active_attribute_name_to_location_map.find(std::string("gl_FogCoord") ) != active_attribute_name_to_location_map.end() ?
    									active_attribute_name_to_location_map.at(std::string("gl_FogCoord") ) : UINT_MAX;
    	
    	for (int i = 0;
    			i < attribute_locations.tex_coords.size();
    			i++)
    	{
    		attribute_locations.tex_coords.at(i) = active_attribute_name_to_location_map.find(string_format("gl_MultiTexCoord%d", i) ) != active_attribute_name_to_location_map.end() ?
    									active_attribute_name_to_location_map.at(string_format("gl_MultiTexCoord%d", i) ) : UINT_MAX;
    	}
    	
	
	
	}
	
	
	
	
	
	
	
	//// Uniforms
	{
	
	// gl_ModelViewMatrix
		uniform_locations.gl_ModelViewMatrix = active_uniform_by_name_map.find(std::string("gl_ModelViewMatrix") ) != active_uniform_by_name_map.end() ?
												active_uniform_by_name_map.at(std::string("gl_ModelViewMatrix") )->index : UINT_MAX;
	// gl_ProjectionMatrix
		uniform_locations.gl_ProjectionMatrix = active_uniform_by_name_map.find(std::string("gl_ProjectionMatrix") ) != active_uniform_by_name_map.end() ?
												active_uniform_by_name_map.at(std::string("gl_ProjectionMatrix") )->index : UINT_MAX;
	// gl_ModelViewProjectionMatrix
		uniform_locations.gl_ModelViewProjectionMatrix = active_uniform_by_name_map.find(std::string("gl_ModelViewProjectionMatrix") ) != active_uniform_by_name_map.end() ?
												active_uniform_by_name_map.at(std::string("gl_ModelViewProjectionMatrix") )->index : UINT_MAX;
	// gl_NormalMatrix
		uniform_locations.gl_NormalMatrix = active_uniform_by_name_map.find(std::string("gl_NormalMatrix") ) != active_uniform_by_name_map.end() ?
												active_uniform_by_name_map.at(std::string("gl_NormalMatrix") )->index : UINT_MAX;
	// gl_ModelViewMatrixInverse
		uniform_locations.gl_ModelViewMatrixInverse = active_uniform_by_name_map.find(std::string("gl_ModelViewMatrixInverse") ) != active_uniform_by_name_map.end() ?
												active_uniform_by_name_map.at(std::string("gl_ModelViewMatrixInverse") )->index : UINT_MAX;
	// gl_ProjectionMatrixInverse
		uniform_locations.gl_ProjectionMatrixInverse = active_uniform_by_name_map.find(std::string("gl_ProjectionMatrixInverse") ) != active_uniform_by_name_map.end() ?
												active_uniform_by_name_map.at(std::string("gl_ProjectionMatrixInverse") )->index : UINT_MAX;
	// gl_ModelViewProjectionMatrixInverse
		uniform_locations.gl_ModelViewProjectionMatrixInverse = active_uniform_by_name_map.find(std::string("gl_ModelViewProjectionMatrixInverse") ) != active_uniform_by_name_map.end() ?
												active_uniform_by_name_map.at(std::string("gl_ModelViewProjectionMatrixInverse") )->index : UINT_MAX;
	// gl_ModelViewMatrixTranspose
		uniform_locations.gl_ModelViewMatrixTranspose = active_uniform_by_name_map.find(std::string("gl_ModelViewMatrixTranspose") ) != active_uniform_by_name_map.end() ?
												active_uniform_by_name_map.at(std::string("gl_ModelViewMatrixTranspose") )->index : UINT_MAX;
	// gl_ProjectionMatrixTranspose
		uniform_locations.gl_ProjectionMatrixTranspose = active_uniform_by_name_map.find(std::string("gl_ProjectionMatrixTranspose") ) != active_uniform_by_name_map.end() ?
												active_uniform_by_name_map.at(std::string("gl_ProjectionMatrixTranspose") )->index : UINT_MAX;
	// gl_ModelViewProjectionMatrixTranspose
		uniform_locations.gl_ModelViewProjectionMatrixTranspose = active_uniform_by_name_map.find(std::string("gl_ModelViewProjectionMatrixTranspose") ) != active_uniform_by_name_map.end() ?
												active_uniform_by_name_map.at(std::string("gl_ModelViewProjectionMatrixTranspose") )->index : UINT_MAX;
	// gl_ModelViewMatrixInverseTranspose
		uniform_locations.gl_ModelViewMatrixInverseTranspose = active_uniform_by_name_map.find(std::string("gl_ModelViewMatrixInverseTranspose") ) != active_uniform_by_name_map.end() ?
												active_uniform_by_name_map.at(std::string("gl_ModelViewMatrixInverseTranspose") )->index : UINT_MAX;
	// gl_ProjectionMatrixInverseTranspose
		uniform_locations.gl_ProjectionMatrixInverseTranspose = active_uniform_by_name_map.find(std::string("gl_ProjectionMatrixInverseTranspose") ) != active_uniform_by_name_map.end() ?
												active_uniform_by_name_map.at(std::string("gl_ProjectionMatrixInverseTranspose") )->index : UINT_MAX;
	// gl_ModelViewProjectionMatrixInverseTranspose
		uniform_locations.gl_ModelViewProjectionMatrixInverseTranspose = active_uniform_by_name_map.find(std::string("gl_ModelViewProjectionMatrixInverseTranspose") ) != active_uniform_by_name_map.end() ?
												active_uniform_by_name_map.at(std::string("gl_ModelViewProjectionMatrixInverseTranspose") )->index : UINT_MAX;
	// gl_NormalScale
		uniform_locations.gl_NormalScale = active_uniform_by_name_map.find(std::string("gl_NormalScale") ) != active_uniform_by_name_map.end() ?
												active_uniform_by_name_map.at(std::string("gl_NormalScale") )->index : UINT_MAX;
	
	
	
	
	// gl_Fog
			uniform_locations.gl_Fog.color = active_uniform_by_name_map.find(std::string("gl_Fog.color") ) != active_uniform_by_name_map.end() ?
												active_uniform_by_name_map.at(std::string("gl_Fog.color") )->index : UINT_MAX;
			uniform_locations.gl_Fog.density = active_uniform_by_name_map.find(std::string("gl_Fog.density") ) != active_uniform_by_name_map.end() ?
												active_uniform_by_name_map.at(std::string("gl_Fog.density") )->index : UINT_MAX;
			uniform_locations.gl_Fog.start = active_uniform_by_name_map.find(std::string("gl_Fog.start") ) != active_uniform_by_name_map.end() ?
												active_uniform_by_name_map.at(std::string("gl_Fog.start") )->index : UINT_MAX;
			uniform_locations.gl_Fog.end = active_uniform_by_name_map.find(std::string("gl_Fog.end") ) != active_uniform_by_name_map.end() ?
												active_uniform_by_name_map.at(std::string("gl_Fog.end") )->index : UINT_MAX;
			uniform_locations.gl_Fog.scale = active_uniform_by_name_map.find(std::string("gl_Fog.scale") ) != active_uniform_by_name_map.end() ?
												active_uniform_by_name_map.at(std::string("gl_Fog.scale") )->index : UINT_MAX;
			
			
			
			
			
	// gl_FrontMaterial
			uniform_locations.gl_FrontMaterial.emission = active_uniform_by_name_map.find(std::string("gl_FrontMaterial.emission") ) != active_uniform_by_name_map.end() ?
												active_uniform_by_name_map.at(std::string("gl_FrontMaterial.emission") )->index : UINT_MAX;
			uniform_locations.gl_FrontMaterial.ambient = active_uniform_by_name_map.find(std::string("gl_FrontMaterial.ambient") ) != active_uniform_by_name_map.end() ?
												active_uniform_by_name_map.at(std::string("gl_FrontMaterial.ambient") )->index : UINT_MAX;
			uniform_locations.gl_FrontMaterial.diffuse = active_uniform_by_name_map.find(std::string("gl_FrontMaterial.diffuse") ) != active_uniform_by_name_map.end() ?
												active_uniform_by_name_map.at(std::string("gl_FrontMaterial.diffuse") )->index : UINT_MAX;
			uniform_locations.gl_FrontMaterial.specular = active_uniform_by_name_map.find(std::string("gl_FrontMaterial.specular") ) != active_uniform_by_name_map.end() ?
												active_uniform_by_name_map.at(std::string("gl_FrontMaterial.specular") )->index : UINT_MAX;
			uniform_locations.gl_FrontMaterial.shininess = active_uniform_by_name_map.find(std::string("gl_FrontMaterial.shininess") ) != active_uniform_by_name_map.end() ?
												active_uniform_by_name_map.at(std::string("gl_FrontMaterial.shininess") )->index : UINT_MAX;
	
	// gl_BackMaterial
			uniform_locations.gl_BackMaterial.emission = active_uniform_by_name_map.find(std::string("gl_BackMaterial.emission") ) != active_uniform_by_name_map.end() ?
												active_uniform_by_name_map.at(std::string("gl_BackMaterial.emission") )->index : UINT_MAX;
			uniform_locations.gl_BackMaterial.ambient = active_uniform_by_name_map.find(std::string("gl_BackMaterial.ambient") ) != active_uniform_by_name_map.end() ?
												active_uniform_by_name_map.at(std::string("gl_BackMaterial.ambient") )->index : UINT_MAX;
			uniform_locations.gl_BackMaterial.diffuse = active_uniform_by_name_map.find(std::string("gl_BackMaterial.diffuse") ) != active_uniform_by_name_map.end() ?
												active_uniform_by_name_map.at(std::string("gl_BackMaterial.diffuse") )->index : UINT_MAX;
			uniform_locations.gl_BackMaterial.specular = active_uniform_by_name_map.find(std::string("gl_BackMaterial.specular") ) != active_uniform_by_name_map.end() ?
												active_uniform_by_name_map.at(std::string("gl_BackMaterial.specular") )->index : UINT_MAX;
			uniform_locations.gl_BackMaterial.shininess = active_uniform_by_name_map.find(std::string("gl_BackMaterial.shininess") ) != active_uniform_by_name_map.end() ?
												active_uniform_by_name_map.at(std::string("gl_BackMaterial.shininess") )->index : UINT_MAX;
	
	
	
	
	
	
	// gl_FrontLightModelProduct
			uniform_locations.gl_FrontLightModelProduct.sceneColor = active_uniform_by_name_map.find(std::string("gl_FrontLightModelProduct.sceneColor") ) != active_uniform_by_name_map.end() ?
															active_uniform_by_name_map.at(std::string("gl_FrontLightModelProduct.sceneColor") )->index : UINT_MAX;
	// gl_BackLightModelProduct
			uniform_locations.gl_BackLightModelProduct.sceneColor = active_uniform_by_name_map.find(std::string("gl_BackLightModelProduct.sceneColor") ) != active_uniform_by_name_map.end() ?
															active_uniform_by_name_map.at(std::string("gl_BackLightModelProduct.sceneColor") )->index : UINT_MAX;
	
	
	
	// gl_LightModel
			uniform_locations.gl_LightModel.ambient = active_uniform_by_name_map.find(std::string("gl_LightModel.ambient") ) != active_uniform_by_name_map.end() ?
															active_uniform_by_name_map.at(std::string("gl_LightModel.ambient") )->index : UINT_MAX;
	
	
	
	
	// gl_TextureMatrix[]
	{
		uniform_locations.gl_TextureMatrix.at(0) = active_uniform_by_name_map.find(std::string("gl_TextureMatrix") ) != active_uniform_by_name_map.end() ?
													active_uniform_by_name_map.at(std::string("gl_TextureMatrix") )->index : UINT_MAX;
		auto start_index = uniform_locations.gl_TextureMatrix.at(0);
		if (start_index != UINT_MAX)
		{
			auto size = active_uniforms.at(start_index).size;
			for (int i = 0;
					i < size && i < uniform_locations.gl_TextureMatrix.size();
					i++)
			{
				uniform_locations.gl_TextureMatrix.at(i) = start_index + i;
			}
		}
	}
	
	// gl_TextureMatrixInverse[]
	{
		uniform_locations.gl_TextureMatrixInverse.at(0) = active_uniform_by_name_map.find(std::string("gl_TextureMatrixInverse") ) != active_uniform_by_name_map.end() ?
													active_uniform_by_name_map.at(std::string("gl_TextureMatrixInverse") )->index : UINT_MAX;
		auto start_index = uniform_locations.gl_TextureMatrixInverse.at(0);
		if (start_index != UINT_MAX)
		{
			auto size = active_uniforms.at(start_index).size;
			for (int i = 0;
					i < size && i < uniform_locations.gl_TextureMatrixInverse.size();
					i++)
			{
				uniform_locations.gl_TextureMatrixInverse.at(i) = start_index + i;
			}
		}
	}
	
	// gl_TextureMatrixTranspose[]
	{
		uniform_locations.gl_TextureMatrixTranspose.at(0) = active_uniform_by_name_map.find(std::string("gl_TextureMatrixTranspose") ) != active_uniform_by_name_map.end() ?
													active_uniform_by_name_map.at(std::string("gl_TextureMatrixTranspose") )->index : UINT_MAX;
		auto start_index = uniform_locations.gl_TextureMatrixTranspose.at(0);
		if (start_index != UINT_MAX)
		{
			auto size = active_uniforms.at(start_index).size;
			for (int i = 0;
					i < size && i < uniform_locations.gl_TextureMatrixTranspose.size();
					i++)
			{
				uniform_locations.gl_TextureMatrixTranspose.at(i) = start_index + i;
			}
		}
	}
	
	// gl_TextureMatrixInverseTranspose[]
	{
		uniform_locations.gl_TextureMatrixInverseTranspose.at(0) = active_uniform_by_name_map.find(std::string("gl_TextureMatrixInverseTranspose") ) != active_uniform_by_name_map.end() ?
													active_uniform_by_name_map.at(std::string("gl_TextureMatrixInverseTranspose") )->index : UINT_MAX;
		auto start_index = uniform_locations.gl_TextureMatrixInverseTranspose.at(0);
		if (start_index != UINT_MAX)
		{
			auto size = active_uniforms.at(start_index).size;
			for (int i = 0;
					i < size && i < uniform_locations.gl_TextureMatrixInverseTranspose.size();
					i++)
			{
				uniform_locations.gl_TextureMatrixInverseTranspose.at(i) = start_index + i;
			}
		}
	}
	
	
	
	
	// gl_LightSource[]
	{
    	for (int i = 0;
    			i < uniform_locations.gl_LightSource.size();
    			i++)
    	{
    		uniform_locations.gl_LightSource[i].ambient = active_uniform_by_name_map.find(string_format("gl_LightSource[%d].ambient", i) ) != active_uniform_by_name_map.end() ?
    														active_uniform_by_name_map.at(string_format("gl_LightSource[%d].ambient", i) )->index : UINT_MAX;
    		uniform_locations.gl_LightSource[i].diffuse = active_uniform_by_name_map.find(string_format("gl_LightSource[%d].diffuse", i) ) != active_uniform_by_name_map.end() ?
    														active_uniform_by_name_map.at(string_format("gl_LightSource[%d].diffuse", i) )->index : UINT_MAX;
    		uniform_locations.gl_LightSource[i].specular = active_uniform_by_name_map.find(string_format("gl_LightSource[%d].specular", i) ) != active_uniform_by_name_map.end() ?
    														active_uniform_by_name_map.at(string_format("gl_LightSource[%d].specular", i) )->index : UINT_MAX;
    		uniform_locations.gl_LightSource[i].position = active_uniform_by_name_map.find(string_format("gl_LightSource[%d].position", i) ) != active_uniform_by_name_map.end() ?
    														active_uniform_by_name_map.at(string_format("gl_LightSource[%d].position", i) )->index : UINT_MAX;
    		uniform_locations.gl_LightSource[i].halfVector = active_uniform_by_name_map.find(string_format("gl_LightSource[%d].halfVector", i) ) != active_uniform_by_name_map.end() ?
    														active_uniform_by_name_map.at(string_format("gl_LightSource[%d].halfVector", i) )->index : UINT_MAX;
    		uniform_locations.gl_LightSource[i].spotDirection = active_uniform_by_name_map.find(string_format("gl_LightSource[%d].spotDirection", i) ) != active_uniform_by_name_map.end() ?
    														active_uniform_by_name_map.at(string_format("gl_LightSource[%d].spotDirection", i) )->index : UINT_MAX;
    		uniform_locations.gl_LightSource[i].spotExponent = active_uniform_by_name_map.find(string_format("gl_LightSource[%d].spotExponent", i) ) != active_uniform_by_name_map.end() ?
    														active_uniform_by_name_map.at(string_format("gl_LightSource[%d].spotExponent", i) )->index : UINT_MAX;
    		uniform_locations.gl_LightSource[i].spotCutoff = active_uniform_by_name_map.find(string_format("gl_LightSource[%d].spotCutoff", i) ) != active_uniform_by_name_map.end() ?
    														active_uniform_by_name_map.at(string_format("gl_LightSource[%d].spotCutoff", i) )->index : UINT_MAX;
    		uniform_locations.gl_LightSource[i].spotCosCutoff = active_uniform_by_name_map.find(string_format("gl_LightSource[%d].spotCosCutoff", i) ) != active_uniform_by_name_map.end() ?
    														active_uniform_by_name_map.at(string_format("gl_LightSource[%d].spotCosCutoff", i) )->index : UINT_MAX;
    		uniform_locations.gl_LightSource[i].constantAttenuation = active_uniform_by_name_map.find(string_format("gl_LightSource[%d].constantAttenuation", i) ) != active_uniform_by_name_map.end() ?
    														active_uniform_by_name_map.at(string_format("gl_LightSource[%d].constantAttenuation", i) )->index : UINT_MAX;
    		uniform_locations.gl_LightSource[i].linearAttenuation = active_uniform_by_name_map.find(string_format("gl_LightSource[%d].linearAttenuation", i) ) != active_uniform_by_name_map.end() ?
    														active_uniform_by_name_map.at(string_format("gl_LightSource[%d].linearAttenuation", i) )->index : UINT_MAX;
    		uniform_locations.gl_LightSource[i].quadraticAttenuation = active_uniform_by_name_map.find(string_format("gl_LightSource[%d].quadraticAttenuation", i) ) != active_uniform_by_name_map.end() ?
    														active_uniform_by_name_map.at(string_format("gl_LightSource[%d].quadraticAttenuation", i) )->index : UINT_MAX;
    	}
	}
	
	
	// gl_FrontLightProduct[]
	{
    	for (int i = 0;
    			i < uniform_locations.gl_FrontLightProduct.size();
    			i++)
    	{
    		uniform_locations.gl_FrontLightProduct[i].ambient = active_uniform_by_name_map.find(string_format("gl_FrontLightProduct[%d].ambient", i) ) != active_uniform_by_name_map.end() ?
    														active_uniform_by_name_map.at(string_format("gl_FrontLightProduct[%d].ambient", i) )->index : UINT_MAX;
    		uniform_locations.gl_FrontLightProduct[i].diffuse = active_uniform_by_name_map.find(string_format("gl_FrontLightProduct[%d].diffuse", i) ) != active_uniform_by_name_map.end() ?
    														active_uniform_by_name_map.at(string_format("gl_FrontLightProduct[%d].diffuse", i) )->index : UINT_MAX;
    		uniform_locations.gl_FrontLightProduct[i].specular = active_uniform_by_name_map.find(string_format("gl_FrontLightProduct[%d].specular", i) ) != active_uniform_by_name_map.end() ?
    														active_uniform_by_name_map.at(string_format("gl_FrontLightProduct[%d].specular", i) )->index : UINT_MAX;
    	}
	}
	
	
	// gl_BackLightProduct[]
	{
    	for (int i = 0;
    			i < uniform_locations.gl_BackLightProduct.size();
    			i++)
    	{
    		uniform_locations.gl_BackLightProduct[i].ambient = active_uniform_by_name_map.find(string_format("gl_BackLightProduct[%d].ambient", i) ) != active_uniform_by_name_map.end() ?
    														active_uniform_by_name_map.at(string_format("gl_BackLightProduct[%d].ambient", i) )->index : UINT_MAX;
    		uniform_locations.gl_BackLightProduct[i].diffuse = active_uniform_by_name_map.find(string_format("gl_BackLightProduct[%d].diffuse", i) ) != active_uniform_by_name_map.end() ?
    														active_uniform_by_name_map.at(string_format("gl_BackLightProduct[%d].diffuse", i) )->index : UINT_MAX;
    		uniform_locations.gl_BackLightProduct[i].specular = active_uniform_by_name_map.find(string_format("gl_BackLightProduct[%d].specular", i) ) != active_uniform_by_name_map.end() ?
    														active_uniform_by_name_map.at(string_format("gl_BackLightProduct[%d].specular", i) )->index : UINT_MAX;
    	}
	}
	
	
	
	
	// _gl_AlphaRef
		uniform_locations._gl_AlphaRef = active_uniform_by_name_map.find(std::string("_gl_AlphaRef") ) != active_uniform_by_name_map.end() ?
												active_uniform_by_name_map.at(std::string("_gl_AlphaRef") )->index : UINT_MAX;
	
	
	
	// gl_TextureEnvColor[]
	{
		uniform_locations.gl_TextureEnvColor.at(0) = active_uniform_by_name_map.find(std::string("gl_TextureEnvColor") ) != active_uniform_by_name_map.end() ?
													active_uniform_by_name_map.at(std::string("gl_TextureEnvColor") )->index : UINT_MAX;
		auto start_index = uniform_locations.gl_TextureEnvColor.at(0);
		if (start_index != UINT_MAX)
		{
			auto size = active_uniforms.at(start_index).size;
			for (int i = 0;
					i < size && i < uniform_locations.gl_TextureEnvColor.size();
					i++)
			{
				uniform_locations.gl_TextureEnvColor.at(i) = start_index + i;
			}
		}
	}
	
	// _gl_TexSampler[]
	{
		uniform_locations._gl_TexSampler.at(0) = active_uniform_by_name_map.find(std::string("_gl_TexSampler") ) != active_uniform_by_name_map.end() ?
													active_uniform_by_name_map.at(std::string("_gl_TexSampler") )->index : UINT_MAX;
		auto start_index = uniform_locations._gl_TexSampler.at(0);
		if (start_index != UINT_MAX)
		{
			auto size = active_uniforms.at(start_index).size;
			for (int i = 0;
					i < size && i < uniform_locations._gl_TexSampler.size();
					i++)
			{
				uniform_locations._gl_TexSampler.at(i) = start_index + i;
			}
		}
	}
	
	
	}
	
	/* All done. */
	
	m_program_id_to_program_state_map[in_program] = new_program_state;
	
	
	
	
	result = true;
	return result;
}

bool OpenGL::GLCompatibilityManager::delete_program_state(uint32_t in_program)
{
    FUN_ENTRY(DEBUG_DEPTH);
    
	bool result = false;
	
	m_program_id_to_program_state_map.erase(in_program);
	
	result = true;
	return result;
}

bool OpenGL::GLCompatibilityManager::init_fpe_state(void)
{
    FUN_ENTRY(DEBUG_DEPTH);
    
	bool result = false;
	
	GLint max_lights = 0;
	GLint max_tex_coords = 0;
	
	glGetIntegerv(GL_MAX_LIGHTS, &max_lights);
	glGetIntegerv(GL_MAX_TEXTURE_COORDS, &max_tex_coords);
	
	vkgl_assert(max_lights != 0);
	vkgl_assert(max_tex_coords != 0);
	
	m_fpe_state = OpenGL::FpeState(max_lights,
										max_tex_coords);
	
	
	result = true;
	return result;
}

OpenGL::FpeState::FpeVertexArrays::FpeClientArray* OpenGL::GLCompatibilityManager::get_fpe_client_array_ptr(uint32_t in_index)
{
	OpenGL::FpeState::FpeVertexArrays::FpeClientArray* result = nullptr;
	
	if (in_index >= 0 &&
		in_index < 7)
	{
		switch (in_index)
		{
			case 0:
			{
				result = &m_fpe_state.vertex_arrays.color_array;
				break;
			}
			case 1:
			{
				result = &m_fpe_state.vertex_arrays.edge_flag_array;
				break;
			}
			case 2:
			{
				result = &m_fpe_state.vertex_arrays.fog_coord_array;
				break;
			}
			case 3:
			{
				result = &m_fpe_state.vertex_arrays.index_array;
				break;
			}
			case 4:
			{
				result = &m_fpe_state.vertex_arrays.normal_array;
				break;
			}
			case 5:
			{
				result = &m_fpe_state.vertex_arrays.secondary_color_array;
				break;
			}
			case 6:
			{
				result = &m_fpe_state.vertex_arrays.vertex_array;
				break;
			}
		}
	}
	else
	{
		in_index -= 7;
		
		if (in_index >= 0 &&
			in_index < m_fpe_state.vertex_arrays.tex_coord_arrays.size() )
		{
			result = &m_fpe_state.vertex_arrays.tex_coord_arrays.at(in_index);
		}
	}
	
	return result;
	
}

std::string string_format(const std::string fmt_str, ...)
{
    size_t str_len = fmt_str.size();
    std::string str;

    va_list ap;
    va_start(ap, fmt_str);

    while (true) {
        str.resize(str_len);

        const int final_n = vsnprintf(const_cast<char *>(str.data()), str_len, fmt_str.c_str(), ap);

        if (final_n < 0 || final_n >= int(str_len))
            str_len += (std::abs)(final_n - int(str_len) + 1);
        else {
            str.resize(final_n);
            break;
        }
    }

    va_end(ap);

    return str;
}
