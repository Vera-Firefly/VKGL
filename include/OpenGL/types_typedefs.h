/* VKGL (c) 2018 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef VKGL_TYPES_TYPEDEFS_H
#define VKGL_TYPES_TYPEDEFS_H

namespace VKGL
{
    /* Bitfield type definitions */
    typedef uint32_t ClearBufferBits;

    /* VKGL GL entrypoints : GL 1.0 */
    typedef void           (*PFNVKGLBLENDFUNCPROC)              (Context* context_ptr, const GLenum& in_sfactor, const GLenum& in_dfactor);
    typedef void           (*PFNVKGLCLEARPROC)                  (Context* context_ptr, const GLbitfield& in_mask);
    typedef void           (*PFNVKGLCLEARCOLORPROC)             (Context* context_ptr, const GLfloat& in_red, const GLfloat& in_green, const GLfloat& in_blue, const GLfloat& in_alpha);
    typedef void           (*PFNVKGLCLEARDEPTHPROC)             (Context* context_ptr, const GLdouble& in_depth);
    typedef void           (*PFNVKGLCLEARSTENCILPROC)           (Context* context_ptr, const GLint& in_s);
    typedef void           (*PFNVKGLCOLORMASKPROC)              (Context* context_ptr, const GLboolean& in_red, const GLboolean& in_green, const GLboolean& in_blue, const GLboolean& in_alpha);
    typedef void           (*PFNVKGLCULLFACEPROC)               (Context* context_ptr, const GLenum& in_mode);
    typedef void           (*PFNVKGLDEPTHFUNCPROC)              (Context* context_ptr, const GLenum& in_func);
    typedef void           (*PFNVKGLDEPTHMASKPROC)              (Context* context_ptr, const GLboolean& in_flag);
    typedef void           (*PFNVKGLDEPTHRANGEPROC)             (Context* context_ptr, const GLdouble& in_n, const GLdouble& in_f);
    typedef void           (*PFNVKGLDISABLEPROC)                (Context* context_ptr, const GLenum& in_cap);
    typedef void           (*PFNVKGLDRAWBUFFERPROC)             (Context* context_ptr, const GLenum& in_buf);
    typedef void           (*PFNVKGLENABLEPROC)                 (Context* context_ptr, const GLenum& in_cap);
    typedef void           (*PFNVKGLFINISHPROC)                 (Context* context_ptr);
    typedef void           (*PFNVKGLFLUSHPROC)                  (Context* context_ptr);
    typedef void           (*PFNVKGLFRONTFACEPROC)              (Context* context_ptr, const GLenum& in_mode);
    typedef void           (*PFNVKGLGETBOOLEANVPROC)            (Context* context_ptr, const GLenum& in_pname, GLboolean* out_data_ptr);
    typedef void           (*PFNVKGLGETDOUBLEVPROC)             (Context* context_ptr, const GLenum& in_pname, GLdouble* out_data_ptr);
    typedef GLenum         (*PFNVKGLGETERRORPROC)               (Context* context_ptr);
    typedef void           (*PFNVKGLGETFLOATVPROC)              (Context* context_ptr, const GLenum& in_pname, GLfloat* out_data_ptr);
    typedef void           (*PFNVKGLGETINTEGERVPROC)            (Context* context_ptr, const GLenum& in_pname, GLint* out_data_ptr);
    typedef const GLubyte* (*PFNVKGLGETSTRINGPROC)              (Context* context_ptr, const GLenum& in_name);
    typedef void           (*PFNVKGLGETTEXIMAGEPROC)            (Context* context_ptr, const GLenum& in_target, const GLint& in_level, const GLenum& in_format, const GLenum& in_type, void* out_pixels_ptr);
    typedef void           (*PFNVKGLGETTEXLEVELPARAMETERFVPROC) (Context* context_ptr, const GLenum& in_target, const GLint& in_level, const GLenum& in_pname, GLfloat* out_params_ptr);
    typedef void           (*PFNVKGLGETTEXLEVELPARAMETERIVPROC) (Context* context_ptr, const GLenum& in_target, const GLint& in_level, const GLenum& in_pname, GLint* out_params_ptr);
    typedef void           (*PFNVKGLGETTEXPARAMETERFVPROC)      (Context* context_ptr, const GLenum& in_target, const GLenum& in_pname, GLfloat* out_params_ptr);
    typedef void           (*PFNVKGLGETTEXPARAMETERIVPROC)      (Context* context_ptr, const GLenum& in_target, const GLenum& in_pname, GLint* out_params_ptr);
    typedef void           (*PFNVKGLHINTPROC)                   (Context* context_ptr, const GLenum& in_target, const GLenum& in_mode);
    typedef GLboolean      (*PFNVKGLISENABLEDPROC)              (Context* context_ptr, const GLenum& in_cap);
    typedef void           (*PFNVKGLLINEWIDTHPROC)              (Context* context_ptr, const GLfloat& in_width);
    typedef void           (*PFNVKGLLOGICOPPROC)                (Context* context_ptr, const GLenum& in_opcode);
    typedef void           (*PFNVKGLPIXELSTOREFPROC)            (Context* context_ptr, const GLenum& in_pname, const GLfloat& in_param);
    typedef void           (*PFNVKGLPIXELSTOREIPROC)            (Context* context_ptr, const GLenum& in_pname, const GLint& in_param);
    typedef void           (*PFNVKGLPOINTSIZEPROC)              (Context* context_ptr, const GLfloat& in_size);
    typedef void           (*PFNVKGLPOLYGONMODEPROC)            (Context* context_ptr, const GLenum& in_face, const GLenum& in_mode);
    typedef void           (*PFNVKGLREADBUFFERPROC)             (Context* context_ptr, const GLenum& in_src);
    typedef void           (*PFNVKGLREADPIXELSPROC)             (Context* context_ptr, const GLint& in_x, const GLint& in_y, const GLsizei& in_width, const GLsizei& in_height, const GLenum& in_format, const GLenum& in_type, void* out_pixels_ptr);
    typedef void           (*PFNVKGLSCISSORPROC)                (Context* context_ptr, const GLint& in_x, const GLint& in_y, const GLsizei& in_width, const GLsizei& in_height);
    typedef void           (*PFNVKGLSTENCILFUNCPROC)            (Context* context_ptr, const GLenum& in_func, const GLint& in_ref, const GLuint& in_mask);
    typedef void           (*PFNVKGLSTENCILOPPROC)              (Context* context_ptr, const GLenum& in_fail, const GLenum& in_zfail, const GLenum& in_zpass);
    typedef void           (*PFNVKGLSTENCILMASKPROC)            (Context* context_ptr, const GLuint& in_mask);
    typedef void           (*PFNVKGLTEXIMAGE1DPROC)             (Context* context_ptr, const GLenum& in_target, const GLint& in_level, const GLint& in_internalformat, const GLsizei& in_width, const GLint& in_border, const GLenum& in_format, const GLenum& in_type, const void* in_pixels_ptr);
    typedef void           (*PFNVKGLTEXIMAGE2DPROC)             (Context* context_ptr, const GLenum& in_target, const GLint& in_level, const GLint& in_internalformat, const GLsizei& in_width, const GLsizei& in_height, const GLint& in_border, const GLenum& in_format, const GLenum& in_type, const void* in_pixels_ptr);
    typedef void           (*PFNVKGLTEXPARAMETERFPROC)          (Context* context_ptr, const GLenum& in_target, const GLenum& in_pname, const GLfloat& in_param);
    typedef void           (*PFNVKGLTEXPARAMETERFVPROC)         (Context* context_ptr, const GLenum& in_target, const GLenum& in_pname, const GLfloat* in_params_ptr);
    typedef void           (*PFNVKGLTEXPARAMETERIPROC)          (Context* context_ptr, const GLenum& in_target, const GLenum& in_pname, const GLint& in_param);
    typedef void           (*PFNVKGLTEXPARAMETERIVPROC)         (Context* context_ptr, const GLenum& in_target, const GLenum& in_pname, const GLint* in_params_ptr);
    typedef void           (*PFNVKGLVIEWPORTPROC)               (Context* context_ptr, const GLint& in_x, const GLint& in_y, const GLsizei& in_width, const GLsizei& in_height);

    /* VKGL GL entrypoints : GL 1.1 */
    typedef void      (*PFNVKGLBINDTEXTUREPROC)      (VKGL::Context* in_context_ptr, const GLenum& in_target, const GLuint& in_texture);
    typedef void      (*PFNVKGLCOPYTEXIMAGE1DPROC)   (VKGL::Context* in_context_ptr, const GLenum& in_target, const GLint& in_level, const GLenum&  in_internalformat, const GLint& in_x, const GLint& in_y, const GLsizei& in_width, const GLint& in_border);
    typedef void      (*PFNVKGLCOPYTEXIMAGE2DPROC)   (VKGL::Context* in_context_ptr, const GLenum& in_target, const GLint& in_level, const GLenum&  in_internalformat, const GLint& in_x, const GLint& in_y, const GLsizei& in_width, const GLsizei& in_height, const GLint& in_border);
    typedef void      (*PFNVKGLCOPYTEXSUBIMAGE1DPROC)(VKGL::Context* in_context_ptr, const GLenum& in_target, const GLint& in_level, const GLint& in_xoffset, const GLint& in_x, const GLint& in_y, const GLsizei& in_width);
    typedef void      (*PFNVKGLCOPYTEXSUBIMAGE2DPROC)(VKGL::Context* in_context_ptr, const GLenum& in_target, const GLint& in_level, const GLint& in_xoffset, const GLint& in_yoffset, const GLint& in_x, const GLint& in_y, const GLsizei& in_width, const GLsizei& in_height);
    typedef void      (*PFNVKGLDELETETEXTURESPROC)   (VKGL::Context* in_context_ptr, const GLsizei& in_n, const GLuint* in_textures);
    typedef void      (*PFNVKGLDRAWARRAYSPROC)       (VKGL::Context* in_context_ptr, const GLenum& in_mode, const GLint&  in_first, const GLsizei& in_count);
    typedef void      (*PFNVKGLDRAWELEMENTSPROC)     (VKGL::Context* in_context_ptr, const GLenum& in_mode, const GLsizei& in_count, const GLenum& in_type, const void* in_indices);
    typedef void      (*PFNVKGLGENTEXTURESPROC)      (VKGL::Context* in_context_ptr, const GLsizei& in_n, GLuint* in_textures);
    typedef GLboolean (*PFNVKGLISTEXTUREPROC)        (VKGL::Context* in_context_ptr, const GLuint& in_texture);
    typedef void      (*PFNVKGLPOLYGONOFFSETPROC)    (VKGL::Context* in_context_ptr, const GLfloat& in_factor, const GLfloat& in_units);
    typedef void      (*PFNVKGLTEXSUBIMAGE1DPROC)    (VKGL::Context* in_context_ptr, const GLenum& in_target, const GLint& in_level, const GLint& in_xoffset, const GLsizei& in_width, const GLenum& in_format, const GLenum& in_type, const void* in_pixels);
    typedef void      (*PFNVKGLTEXSUBIMAGE2DPROC)    (VKGL::Context* in_context_ptr, const GLenum& in_target, const GLint& in_level, const GLint& in_xoffset, const GLint& in_yoffset, const GLsizei& in_width, const GLsizei& in_height, const GLenum& in_format, const GLenum& in_type, const void* in_pixels);

    /* VKG GL entrypoints : GL 1.2 */
    typedef void (*PFNVKGLCOPYTEXSUBIMAGE3DPROC)(VKGL::Context* in_context_ptr, const GLenum& in_target, const GLint& in_level, const GLint& in_xoffset, const GLint& in_yoffset, const GLint& in_zoffset, const GLint& in_x, const GLint& in_y, const GLsizei& in_width, const GLsizei& in_height);
    typedef void (*PFNVKGLDRAWRANGEELEMENTSPROC)(VKGL::Context* in_context_ptr, const GLenum& in_mode, const GLuint& in_start, const GLuint& in_end, const GLsizei& in_count, const GLenum& in_type, const void* in_indices);
    typedef void (*PFNVKGLTEXIMAGE3DPROC)       (VKGL::Context* in_context_ptr, const GLenum& in_target, const GLint& in_level, const GLint& in_internalformat, const GLsizei& in_width, const GLsizei& in_height, const GLsizei& in_depth, const GLint& in_border, const GLenum& in_format, const GLenum& in_type, const void* in_pixels);
    typedef void (*PFNVKGLTEXSUBIMAGE3DPROC)    (VKGL::Context* in_context_ptr, const GLenum& in_target, const GLint& in_level, const GLint& in_xoffset, const GLint& in_yoffset, const GLint& in_zoffset, const GLsizei& in_width, const GLsizei& in_height, const GLsizei& in_depth, const GLenum& in_format, const GLenum& in_type, const void* in_pixels);

    /* VKG GL entrypoints : GL 1.3 */
    typedef void (*PFNVKGLACTIVETEXTUREPROC)          (VKGL::Context* in_context_ptr, const GLenum& in_texture);
    typedef void (*PFNVKGLCOMPRESSEDTEXIMAGE1DPROC)   (VKGL::Context* in_context_ptr, const GLenum& in_target, const GLint& in_level, const GLenum& in_internalformat, const GLsizei& in_width, const GLint& in_border, const GLsizei& in_image_size, const void* in_data);
    typedef void (*PFNVKGLCOMPRESSEDTEXIMAGE2DPROC)   (VKGL::Context* in_context_ptr, const GLenum& in_target, const GLint& in_level, const GLenum& in_internalformat, const GLsizei& in_width, const GLsizei& in_height, const GLint& in_border, const GLsizei& in_image_size, const void* in_data);
    typedef void (*PFNVKGLCOMPRESSEDTEXIMAGE3DPROC)   (VKGL::Context* in_context_ptr, const GLenum& in_target, const GLint& in_level, const GLenum& in_internalformat, const GLsizei& in_width, const GLsizei& in_height, const GLsizei& in_depth, const GLint& in_border, const GLsizei& in_image_size, const void* in_data);
    typedef void (*PFNVKGLCOMPRESSEDTEXSUBIMAGE1DPROC)(VKGL::Context* in_context_ptr, const GLenum& in_target, const GLint& in_level, const GLint& in_xoffset, const GLsizei& in_width, const GLenum& in_format, const GLsizei& in_image_size, const void* in_data);
    typedef void (*PFNVKGLCOMPRESSEDTEXSUBIMAGE2DPROC)(VKGL::Context* in_context_ptr, const GLenum& in_target, const GLint& in_level, const GLint& in_xoffset, const GLint& in_yoffset, const GLsizei& in_width, const GLsizei& in_height, const GLenum& in_format, const GLsizei& in_image_size, const void* in_data);
    typedef void (*PFNVKGLCOMPRESSEDTEXSUBIMAGE3DPROC)(VKGL::Context* in_context_ptr, const GLenum& in_target, const GLint& in_level, const GLint& in_xoffset, const GLint& in_yoffset, const GLint& in_zoffset, const GLsizei& in_width, const GLsizei& in_height, const GLsizei& in_depth, const GLenum& in_format, const GLsizei& in_image_size, const void* in_data);
    typedef void (*PFNVKGLGETCOMPRESSEDTEXIMAGEPROC)  (VKGL::Context* in_context_ptr, const GLenum& in_target, const GLint& in_level, void* in_img);
    typedef void (*PFNVKGLSAMPLECOVERAGEPROC)         (VKGL::Context* in_context_ptr, const GLfloat& in_value, const GLboolean& in_invert);

    /* VKGL GL entrypoints : GL 1.4 */
    typedef void (*PFNVKGLBLENDCOLORPROC)       (VKGL::Context* in_context_ptr, const GLfloat& red, const GLfloat& green, const GLfloat& blue, const GLfloat& alpha);
    typedef void (*PFNVKGLBLENDEQUATIONPROC)    (VKGL::Context* in_context_ptr, const GLenum& mode);
    typedef void (*PFNVKGLBLENDFUNCSEPARATEPROC)(VKGL::Context* in_context_ptr, const GLenum& sfactorRGB, const GLenum& dfactorRGB, const GLenum& sfactorAlpha, const GLenum& dfactorAlpha);
    typedef void (*PFNVKGLMULTIDRAWARRAYSPROC)  (VKGL::Context* in_context_ptr, const GLenum& mode, const GLint* first, const GLsizei* count, const GLsizei& drawcount);
    typedef void (*PFNVKGLMULTIDRAWELEMENTSPROC)(VKGL::Context* in_context_ptr, const GLenum& mode, const GLsizei* count, const GLenum& type, const void* const* indices, const GLsizei& drawcount);
    typedef void (*PFNVKGLPOINTPARAMETERFPROC)  (VKGL::Context* in_context_ptr, const GLenum& pname, const GLfloat& param);
    typedef void (*PFNVKGLPOINTPARAMETERFVPROC) (VKGL::Context* in_context_ptr, const GLenum& pname, const GLfloat* params);
    typedef void (*PFNVKGLPOINTPARAMETERIPROC)  (VKGL::Context* in_context_ptr, const GLenum& pname, const GLint&  param);
    typedef void (*PFNVKGLPOINTPARAMETERIVPROC) (VKGL::Context* in_context_ptr, const GLenum& pname, const GLint* params);

}

#endif /* VKGL_TYPES_TYPEDEFS_H */