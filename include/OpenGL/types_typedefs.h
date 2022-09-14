/* VKGL (c) 2018 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef VKGL_TYPES_TYPEDEFS_H
#define VKGL_TYPES_TYPEDEFS_H

namespace OpenGL
{
    /* Bitfield type definitions */
    typedef uint32_t BlitMaskBits;
    typedef uint32_t ClearBufferBits;
    typedef uint32_t WaitSyncBits;

    /* VKGL GL entrypoints : GL 1.0 */
    typedef void (* PFNVKGLCULLFACEPROC) (GLenum mode);
    typedef void (* PFNVKGLFRONTFACEPROC) (GLenum mode);
    typedef void (* PFNVKGLHINTPROC) (GLenum target, GLenum mode);
    typedef void (* PFNVKGLLINEWIDTHPROC) (GLfloat width);
    typedef void (* PFNVKGLPOINTSIZEPROC) (GLfloat size);
    typedef void (* PFNVKGLPOLYGONMODEPROC) (GLenum face, GLenum mode);
    typedef void (* PFNVKGLSCISSORPROC) (GLint x, GLint y, GLsizei width, GLsizei height);
    typedef void (* PFNVKGLTEXPARAMETERFPROC) (GLenum target, GLenum pname, GLfloat param);
    typedef void (* PFNVKGLTEXPARAMETERFVPROC) (GLenum target, GLenum pname, const GLfloat *params);
    typedef void (* PFNVKGLTEXPARAMETERIPROC) (GLenum target, GLenum pname, GLint param);
    typedef void (* PFNVKGLTEXPARAMETERIVPROC) (GLenum target, GLenum pname, const GLint *params);
    typedef void (* PFNVKGLTEXIMAGE1DPROC) (GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const void *pixels);
    typedef void (* PFNVKGLTEXIMAGE2DPROC) (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void *pixels);
    typedef void (* PFNVKGLDRAWBUFFERPROC) (GLenum buf);
    typedef void (* PFNVKGLCLEARPROC) (GLbitfield mask);
    typedef void (* PFNVKGLCLEARCOLORPROC) (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
    typedef void (* PFNVKGLCLEARSTENCILPROC) (GLint s);
    typedef void (* PFNVKGLCLEARDEPTHPROC) (GLdouble depth);
    typedef void (* PFNVKGLSTENCILMASKPROC) (GLuint mask);
    typedef void (* PFNVKGLCOLORMASKPROC) (GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
    typedef void (* PFNVKGLDEPTHMASKPROC) (GLboolean flag);
    typedef void (* PFNVKGLDISABLEPROC) (GLenum cap);
    typedef void (* PFNVKGLENABLEPROC) (GLenum cap);
    typedef void (* PFNVKGLFINISHPROC) (void);
    typedef void (* PFNVKGLFLUSHPROC) (void);
    typedef void (* PFNVKGLBLENDFUNCPROC) (GLenum sfactor, GLenum dfactor);
    typedef void (* PFNVKGLLOGICOPPROC) (GLenum opcode);
    typedef void (* PFNVKGLSTENCILFUNCPROC) (GLenum func, GLint ref, GLuint mask);
    typedef void (* PFNVKGLSTENCILOPPROC) (GLenum fail, GLenum zfail, GLenum zpass);
    typedef void (* PFNVKGLDEPTHFUNCPROC) (GLenum func);
    typedef void (* PFNVKGLPIXELSTOREFPROC) (GLenum pname, GLfloat param);
    typedef void (* PFNVKGLPIXELSTOREIPROC) (GLenum pname, GLint param);
    typedef void (* PFNVKGLREADBUFFERPROC) (GLenum src);
    typedef void (* PFNVKGLREADPIXELSPROC) (GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void *pixels);
    typedef void (* PFNVKGLGETBOOLEANVPROC) (GLenum pname, GLboolean *data);
    typedef void (* PFNVKGLGETDOUBLEVPROC) (GLenum pname, GLdouble *data);
    typedef GLenum (* PFNVKGLGETERRORPROC) (void);
    typedef void (* PFNVKGLGETFLOATVPROC) (GLenum pname, GLfloat *data);
    typedef void (* PFNVKGLGETINTEGERVPROC) (GLenum pname, GLint *data);
    typedef const GLubyte *(* PFNVKGLGETSTRINGPROC) (GLenum name);
    typedef void (* PFNVKGLGETTEXIMAGEPROC) (GLenum target, GLint level, GLenum format, GLenum type, void *pixels);
    typedef void (* PFNVKGLGETTEXPARAMETERFVPROC) (GLenum target, GLenum pname, GLfloat *params);
    typedef void (* PFNVKGLGETTEXPARAMETERIVPROC) (GLenum target, GLenum pname, GLint *params);
    typedef void (* PFNVKGLGETTEXLEVELPARAMETERFVPROC) (GLenum target, GLint level, GLenum pname, GLfloat *params);
    typedef void (* PFNVKGLGETTEXLEVELPARAMETERIVPROC) (GLenum target, GLint level, GLenum pname, GLint *params);
    typedef GLboolean (* PFNVKGLISENABLEDPROC) (GLenum cap);
    typedef void (* PFNVKGLDEPTHRANGEPROC) (GLdouble n, GLdouble f);
    typedef void (* PFNVKGLVIEWPORTPROC) (GLint x, GLint y, GLsizei width, GLsizei height);

    /* VKGL GL entrypoints : GL 1.1 */
    typedef void (* PFNVKGLDRAWARRAYSPROC) (GLenum mode, GLint first, GLsizei count);
    typedef void (* PFNVKGLDRAWELEMENTSPROC) (GLenum mode, GLsizei count, GLenum type, const void *indices);
    typedef void (* PFNVKGLGETPOINTERVPROC) (GLenum pname, void **params);
    typedef void (* PFNVKGLPOLYGONOFFSETPROC) (GLfloat factor, GLfloat units);
    typedef void (* PFNVKGLCOPYTEXIMAGE1DPROC) (GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border);
    typedef void (* PFNVKGLCOPYTEXIMAGE2DPROC) (GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border);
    typedef void (* PFNVKGLCOPYTEXSUBIMAGE1DPROC) (GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width);
    typedef void (* PFNVKGLCOPYTEXSUBIMAGE2DPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
    typedef void (* PFNVKGLTEXSUBIMAGE1DPROC) (GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void *pixels);
    typedef void (* PFNVKGLTEXSUBIMAGE2DPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void *pixels);
    typedef void (* PFNVKGLBINDTEXTUREPROC) (GLenum target, GLuint texture);
    typedef void (* PFNVKGLDELETETEXTURESPROC) (GLsizei n, const GLuint *textures);
    typedef void (* PFNVKGLGENTEXTURESPROC) (GLsizei n, GLuint *textures);
    typedef GLboolean (* PFNVKGLISTEXTUREPROC) (GLuint texture);

    /* VKG GL entrypoints : GL 1.2 */
    typedef void (* PFNVKGLDRAWRANGEELEMENTSPROC) (GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void *indices);
    typedef void (* PFNVKGLTEXIMAGE3DPROC) (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void *pixels);
    typedef void (* PFNVKGLTEXSUBIMAGE3DPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void *pixels);
    typedef void (* PFNVKGLCOPYTEXSUBIMAGE3DPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height);

    /* VKG GL entrypoints : GL 1.3 */
    typedef void (* PFNVKGLACTIVETEXTUREPROC) (GLenum texture);
    typedef void (* PFNVKGLSAMPLECOVERAGEPROC) (GLfloat value, GLboolean invert);
    typedef void (* PFNVKGLCOMPRESSEDTEXIMAGE3DPROC) (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void *data);
    typedef void (* PFNVKGLCOMPRESSEDTEXIMAGE2DPROC) (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void *data);
    typedef void (* PFNVKGLCOMPRESSEDTEXIMAGE1DPROC) (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const void *data);
    typedef void (* PFNVKGLCOMPRESSEDTEXSUBIMAGE3DPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void *data);
    typedef void (* PFNVKGLCOMPRESSEDTEXSUBIMAGE2DPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void *data);
    typedef void (* PFNVKGLCOMPRESSEDTEXSUBIMAGE1DPROC) (GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void *data);
    typedef void (* PFNVKGLGETCOMPRESSEDTEXIMAGEPROC) (GLenum target, GLint level, void *img);

    /* VKGL GL entrypoints : GL 1.4 */
    typedef void (* PFNVKGLBLENDFUNCSEPARATEPROC) (GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha);
    typedef void (* PFNVKGLMULTIDRAWARRAYSPROC) (GLenum mode, const GLint *first, const GLsizei *count, GLsizei drawcount);
    typedef void (* PFNVKGLMULTIDRAWELEMENTSPROC) (GLenum mode, const GLsizei *count, GLenum type, const void *const*indices, GLsizei drawcount);
    typedef void (* PFNVKGLPOINTPARAMETERFPROC) (GLenum pname, GLfloat param);
    typedef void (* PFNVKGLPOINTPARAMETERFVPROC) (GLenum pname, const GLfloat *params);
    typedef void (* PFNVKGLPOINTPARAMETERIPROC) (GLenum pname, GLint param);
    typedef void (* PFNVKGLPOINTPARAMETERIVPROC) (GLenum pname, const GLint *params);
    typedef void (* PFNVKGLBLENDCOLORPROC) (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
    typedef void (* PFNVKGLBLENDEQUATIONPROC) (GLenum mode);

    /* VKGL GL entrypoints: GL 1.5 */
    typedef void (* PFNVKGLGENQUERIESPROC) (GLsizei n, GLuint *ids);
    typedef void (* PFNVKGLDELETEQUERIESPROC) (GLsizei n, const GLuint *ids);
    typedef GLboolean (* PFNVKGLISQUERYPROC) (GLuint id);
    typedef void (* PFNVKGLBEGINQUERYPROC) (GLenum target, GLuint id);
    typedef void (* PFNVKGLENDQUERYPROC) (GLenum target);
    typedef void (* PFNVKGLGETQUERYIVPROC) (GLenum target, GLenum pname, GLint *params);
    typedef void (* PFNVKGLGETQUERYOBJECTIVPROC) (GLuint id, GLenum pname, GLint *params);
    typedef void (* PFNVKGLGETQUERYOBJECTUIVPROC) (GLuint id, GLenum pname, GLuint *params);
    typedef void (* PFNVKGLBINDBUFFERPROC) (GLenum target, GLuint buffer);
    typedef void (* PFNVKGLDELETEBUFFERSPROC) (GLsizei n, const GLuint *buffers);
    typedef void (* PFNVKGLGENBUFFERSPROC) (GLsizei n, GLuint *buffers);
    typedef GLboolean (* PFNVKGLISBUFFERPROC) (GLuint buffer);
    typedef void (* PFNVKGLBUFFERDATAPROC) (GLenum target, GLsizeiptr size, const void *data, GLenum usage);
    typedef void (* PFNVKGLBUFFERSUBDATAPROC) (GLenum target, GLintptr offset, GLsizeiptr size, const void *data);
    typedef void (* PFNVKGLGETBUFFERSUBDATAPROC) (GLenum target, GLintptr offset, GLsizeiptr size, void *data);
    typedef void *(* PFNVKGLMAPBUFFERPROC) (GLenum target, GLenum access);
    typedef GLboolean (* PFNVKGLUNMAPBUFFERPROC) (GLenum target);
    typedef void (* PFNVKGLGETBUFFERPARAMETERIVPROC) (GLenum target, GLenum pname, GLint *params);
    typedef void (* PFNVKGLGETBUFFERPOINTERVPROC) (GLenum target, GLenum pname, void **params);

    /* VKGL GL entrypoints: GL 2.0 */
    typedef void (* PFNVKGLBLENDEQUATIONSEPARATEPROC) (GLenum modeRGB, GLenum modeAlpha);
    typedef void (* PFNVKGLDRAWBUFFERSPROC) (GLsizei n, const GLenum *bufs);
    typedef void (* PFNVKGLSTENCILOPSEPARATEPROC) (GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass);
    typedef void (* PFNVKGLSTENCILFUNCSEPARATEPROC) (GLenum face, GLenum func, GLint ref, GLuint mask);
    typedef void (* PFNVKGLSTENCILMASKSEPARATEPROC) (GLenum face, GLuint mask);
    typedef void (* PFNVKGLATTACHSHADERPROC) (GLuint program, GLuint shader);
    typedef void (* PFNVKGLBINDATTRIBLOCATIONPROC) (GLuint program, GLuint index, const GLchar *name);
    typedef void (* PFNVKGLCOMPILESHADERPROC) (GLuint shader);
    typedef GLuint (* PFNVKGLCREATEPROGRAMPROC) (void);
    typedef GLuint (* PFNVKGLCREATESHADERPROC) (GLenum type);
    typedef void (* PFNVKGLDELETEPROGRAMPROC) (GLuint program);
    typedef void (* PFNVKGLDELETESHADERPROC) (GLuint shader);
    typedef void (* PFNVKGLDETACHSHADERPROC) (GLuint program, GLuint shader);
    typedef void (* PFNVKGLDISABLEVERTEXATTRIBARRAYPROC) (GLuint index);
    typedef void (* PFNVKGLENABLEVERTEXATTRIBARRAYPROC) (GLuint index);
    typedef void (* PFNVKGLGETACTIVEATTRIBPROC) (GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name);
    typedef void (* PFNVKGLGETACTIVEUNIFORMPROC) (GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name);
    typedef void (* PFNVKGLGETATTACHEDSHADERSPROC) (GLuint program, GLsizei maxCount, GLsizei *count, GLuint *shaders);
    typedef GLint (* PFNVKGLGETATTRIBLOCATIONPROC) (GLuint program, const GLchar *name);
    typedef void (* PFNVKGLGETPROGRAMIVPROC) (GLuint program, GLenum pname, GLint *params);
    typedef void (* PFNVKGLGETPROGRAMINFOLOGPROC) (GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
    typedef void (* PFNVKGLGETSHADERIVPROC) (GLuint shader, GLenum pname, GLint *params);
    typedef void (* PFNVKGLGETSHADERINFOLOGPROC) (GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
    typedef void (* PFNVKGLGETSHADERSOURCEPROC) (GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *source);
    typedef GLint (* PFNVKGLGETUNIFORMLOCATIONPROC) (GLuint program, const GLchar *name);
    typedef void (* PFNVKGLGETUNIFORMFVPROC) (GLuint program, GLint location, GLfloat *params);
    typedef void (* PFNVKGLGETUNIFORMIVPROC) (GLuint program, GLint location, GLint *params);
    typedef void (* PFNVKGLGETVERTEXATTRIBDVPROC) (GLuint index, GLenum pname, GLdouble *params);
    typedef void (* PFNVKGLGETVERTEXATTRIBFVPROC) (GLuint index, GLenum pname, GLfloat *params);
    typedef void (* PFNVKGLGETVERTEXATTRIBIVPROC) (GLuint index, GLenum pname, GLint *params);
    typedef void (* PFNVKGLGETVERTEXATTRIBPOINTERVPROC) (GLuint index, GLenum pname, void **pointer);
    typedef GLboolean (* PFNVKGLISPROGRAMPROC) (GLuint program);
    typedef GLboolean (* PFNVKGLISSHADERPROC) (GLuint shader);
    typedef void (* PFNVKGLLINKPROGRAMPROC) (GLuint program);
    typedef void (* PFNVKGLSHADERSOURCEPROC) (GLuint shader, GLsizei count, const GLchar *const*string, const GLint *length);
    typedef void (* PFNVKGLUSEPROGRAMPROC) (GLuint program);
    typedef void (* PFNVKGLUNIFORM1FPROC) (GLint location, GLfloat v0);
    typedef void (* PFNVKGLUNIFORM2FPROC) (GLint location, GLfloat v0, GLfloat v1);
    typedef void (* PFNVKGLUNIFORM3FPROC) (GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
    typedef void (* PFNVKGLUNIFORM4FPROC) (GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
    typedef void (* PFNVKGLUNIFORM1IPROC) (GLint location, GLint v0);
    typedef void (* PFNVKGLUNIFORM2IPROC) (GLint location, GLint v0, GLint v1);
    typedef void (* PFNVKGLUNIFORM3IPROC) (GLint location, GLint v0, GLint v1, GLint v2);
    typedef void (* PFNVKGLUNIFORM4IPROC) (GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
    typedef void (* PFNVKGLUNIFORM1FVPROC) (GLint location, GLsizei count, const GLfloat *value);
    typedef void (* PFNVKGLUNIFORM2FVPROC) (GLint location, GLsizei count, const GLfloat *value);
    typedef void (* PFNVKGLUNIFORM3FVPROC) (GLint location, GLsizei count, const GLfloat *value);
    typedef void (* PFNVKGLUNIFORM4FVPROC) (GLint location, GLsizei count, const GLfloat *value);
    typedef void (* PFNVKGLUNIFORM1IVPROC) (GLint location, GLsizei count, const GLint *value);
    typedef void (* PFNVKGLUNIFORM2IVPROC) (GLint location, GLsizei count, const GLint *value);
    typedef void (* PFNVKGLUNIFORM3IVPROC) (GLint location, GLsizei count, const GLint *value);
    typedef void (* PFNVKGLUNIFORM4IVPROC) (GLint location, GLsizei count, const GLint *value);
    typedef void (* PFNVKGLUNIFORMMATRIX2FVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
    typedef void (* PFNVKGLUNIFORMMATRIX3FVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
    typedef void (* PFNVKGLUNIFORMMATRIX4FVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
    typedef void (* PFNVKGLVALIDATEPROGRAMPROC) (GLuint program);
    typedef void (* PFNVKGLVERTEXATTRIB1DPROC) (GLuint index, GLdouble x);
    typedef void (* PFNVKGLVERTEXATTRIB1DVPROC) (GLuint index, const GLdouble *v);
    typedef void (* PFNVKGLVERTEXATTRIB1FPROC) (GLuint index, GLfloat x);
    typedef void (* PFNVKGLVERTEXATTRIB1FVPROC) (GLuint index, const GLfloat *v);
    typedef void (* PFNVKGLVERTEXATTRIB1SPROC) (GLuint index, GLshort x);
    typedef void (* PFNVKGLVERTEXATTRIB1SVPROC) (GLuint index, const GLshort *v);
    typedef void (* PFNVKGLVERTEXATTRIB2DPROC) (GLuint index, GLdouble x, GLdouble y);
    typedef void (* PFNVKGLVERTEXATTRIB2DVPROC) (GLuint index, const GLdouble *v);
    typedef void (* PFNVKGLVERTEXATTRIB2FPROC) (GLuint index, GLfloat x, GLfloat y);
    typedef void (* PFNVKGLVERTEXATTRIB2FVPROC) (GLuint index, const GLfloat *v);
    typedef void (* PFNVKGLVERTEXATTRIB2SPROC) (GLuint index, GLshort x, GLshort y);
    typedef void (* PFNVKGLVERTEXATTRIB2SVPROC) (GLuint index, const GLshort *v);
    typedef void (* PFNVKGLVERTEXATTRIB3DPROC) (GLuint index, GLdouble x, GLdouble y, GLdouble z);
    typedef void (* PFNVKGLVERTEXATTRIB3DVPROC) (GLuint index, const GLdouble *v);
    typedef void (* PFNVKGLVERTEXATTRIB3FPROC) (GLuint index, GLfloat x, GLfloat y, GLfloat z);
    typedef void (* PFNVKGLVERTEXATTRIB3FVPROC) (GLuint index, const GLfloat *v);
    typedef void (* PFNVKGLVERTEXATTRIB3SPROC) (GLuint index, GLshort x, GLshort y, GLshort z);
    typedef void (* PFNVKGLVERTEXATTRIB3SVPROC) (GLuint index, const GLshort *v);
    typedef void (* PFNVKGLVERTEXATTRIB4NBVPROC) (GLuint index, const GLbyte *v);
    typedef void (* PFNVKGLVERTEXATTRIB4NIVPROC) (GLuint index, const GLint *v);
    typedef void (* PFNVKGLVERTEXATTRIB4NSVPROC) (GLuint index, const GLshort *v);
    typedef void (* PFNVKGLVERTEXATTRIB4NUBPROC) (GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w);
    typedef void (* PFNVKGLVERTEXATTRIB4NUBVPROC) (GLuint index, const GLubyte *v);
    typedef void (* PFNVKGLVERTEXATTRIB4NUIVPROC) (GLuint index, const GLuint *v);
    typedef void (* PFNVKGLVERTEXATTRIB4NUSVPROC) (GLuint index, const GLushort *v);
    typedef void (* PFNVKGLVERTEXATTRIB4BVPROC) (GLuint index, const GLbyte *v);
    typedef void (* PFNVKGLVERTEXATTRIB4DPROC) (GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
    typedef void (* PFNVKGLVERTEXATTRIB4DVPROC) (GLuint index, const GLdouble *v);
    typedef void (* PFNVKGLVERTEXATTRIB4FPROC) (GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
    typedef void (* PFNVKGLVERTEXATTRIB4FVPROC) (GLuint index, const GLfloat *v);
    typedef void (* PFNVKGLVERTEXATTRIB4IVPROC) (GLuint index, const GLint *v);
    typedef void (* PFNVKGLVERTEXATTRIB4SPROC) (GLuint index, GLshort x, GLshort y, GLshort z, GLshort w);
    typedef void (* PFNVKGLVERTEXATTRIB4SVPROC) (GLuint index, const GLshort *v);
    typedef void (* PFNVKGLVERTEXATTRIB4UBVPROC) (GLuint index, const GLubyte *v);
    typedef void (* PFNVKGLVERTEXATTRIB4UIVPROC) (GLuint index, const GLuint *v);
    typedef void (* PFNVKGLVERTEXATTRIB4USVPROC) (GLuint index, const GLushort *v);
    typedef void (* PFNVKGLVERTEXATTRIBPOINTERPROC) (GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer);
    
    /* VKGL GL entrypoints : GL 2.1 */
    typedef void (* PFNVKGLUNIFORMMATRIX2X3FVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
    typedef void (* PFNVKGLUNIFORMMATRIX3X2FVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
    typedef void (* PFNVKGLUNIFORMMATRIX2X4FVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
    typedef void (* PFNVKGLUNIFORMMATRIX4X2FVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
    typedef void (* PFNVKGLUNIFORMMATRIX3X4FVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
    typedef void (* PFNVKGLUNIFORMMATRIX4X3FVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
    
    /* VKGL GL entrypoints : GL 3.0 */
    typedef void (* PFNVKGLCOLORMASKIPROC) (GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a);
    typedef void (* PFNVKGLGETBOOLEANI_VPROC) (GLenum target, GLuint index, GLboolean *data);
    typedef void (* PFNVKGLGETINTEGERI_VPROC) (GLenum target, GLuint index, GLint *data);
    typedef void (* PFNVKGLENABLEIPROC) (GLenum target, GLuint index);
    typedef void (* PFNVKGLDISABLEIPROC) (GLenum target, GLuint index);
    typedef GLboolean (* PFNVKGLISENABLEDIPROC) (GLenum target, GLuint index);
    typedef void (* PFNVKGLBEGINTRANSFORMFEEDBACKPROC) (GLenum primitiveMode);
    typedef void (* PFNVKGLENDTRANSFORMFEEDBACKPROC) (void);
    typedef void (* PFNVKGLBINDBUFFERRANGEPROC) (GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size);
    typedef void (* PFNVKGLBINDBUFFERBASEPROC) (GLenum target, GLuint index, GLuint buffer);
    typedef void (* PFNVKGLTRANSFORMFEEDBACKVARYINGSPROC) (GLuint program, GLsizei count, const GLchar *const*varyings, GLenum bufferMode);
    typedef void (* PFNVKGLGETTRANSFORMFEEDBACKVARYINGPROC) (GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLsizei *size, GLenum *type, GLchar *name);
    typedef void (* PFNVKGLCLAMPCOLORPROC) (GLenum target, GLenum clamp);
    typedef void (* PFNVKGLBEGINCONDITIONALRENDERPROC) (GLuint id, GLenum mode);
    typedef void (* PFNVKGLENDCONDITIONALRENDERPROC) (void);
    typedef void (* PFNVKGLVERTEXATTRIBIPOINTERPROC) (GLuint index, GLint size, GLenum type, GLsizei stride, const void *pointer);
    typedef void (* PFNVKGLGETVERTEXATTRIBIIVPROC) (GLuint index, GLenum pname, GLint *params);
    typedef void (* PFNVKGLGETVERTEXATTRIBIUIVPROC) (GLuint index, GLenum pname, GLuint *params);
    typedef void (* PFNVKGLVERTEXATTRIBI1IPROC) (GLuint index, GLint x);
    typedef void (* PFNVKGLVERTEXATTRIBI2IPROC) (GLuint index, GLint x, GLint y);
    typedef void (* PFNVKGLVERTEXATTRIBI3IPROC) (GLuint index, GLint x, GLint y, GLint z);
    typedef void (* PFNVKGLVERTEXATTRIBI4IPROC) (GLuint index, GLint x, GLint y, GLint z, GLint w);
    typedef void (* PFNVKGLVERTEXATTRIBI1UIPROC) (GLuint index, GLuint x);
    typedef void (* PFNVKGLVERTEXATTRIBI2UIPROC) (GLuint index, GLuint x, GLuint y);
    typedef void (* PFNVKGLVERTEXATTRIBI3UIPROC) (GLuint index, GLuint x, GLuint y, GLuint z);
    typedef void (* PFNVKGLVERTEXATTRIBI4UIPROC) (GLuint index, GLuint x, GLuint y, GLuint z, GLuint w);
    typedef void (* PFNVKGLVERTEXATTRIBI1IVPROC) (GLuint index, const GLint *v);
    typedef void (* PFNVKGLVERTEXATTRIBI2IVPROC) (GLuint index, const GLint *v);
    typedef void (* PFNVKGLVERTEXATTRIBI3IVPROC) (GLuint index, const GLint *v);
    typedef void (* PFNVKGLVERTEXATTRIBI4IVPROC) (GLuint index, const GLint *v);
    typedef void (* PFNVKGLVERTEXATTRIBI1UIVPROC) (GLuint index, const GLuint *v);
    typedef void (* PFNVKGLVERTEXATTRIBI2UIVPROC) (GLuint index, const GLuint *v);
    typedef void (* PFNVKGLVERTEXATTRIBI3UIVPROC) (GLuint index, const GLuint *v);
    typedef void (* PFNVKGLVERTEXATTRIBI4UIVPROC) (GLuint index, const GLuint *v);
    typedef void (* PFNVKGLVERTEXATTRIBI4BVPROC) (GLuint index, const GLbyte *v);
    typedef void (* PFNVKGLVERTEXATTRIBI4SVPROC) (GLuint index, const GLshort *v);
    typedef void (* PFNVKGLVERTEXATTRIBI4UBVPROC) (GLuint index, const GLubyte *v);
    typedef void (* PFNVKGLVERTEXATTRIBI4USVPROC) (GLuint index, const GLushort *v);
    typedef void (* PFNVKGLGETUNIFORMUIVPROC) (GLuint program, GLint location, GLuint *params);
    typedef void (* PFNVKGLBINDFRAGDATALOCATIONPROC) (GLuint program, GLuint color, const GLchar *name);
    typedef GLint (* PFNVKGLGETFRAGDATALOCATIONPROC) (GLuint program, const GLchar *name);
    typedef void (* PFNVKGLUNIFORM1UIPROC) (GLint location, GLuint v0);
    typedef void (* PFNVKGLUNIFORM2UIPROC) (GLint location, GLuint v0, GLuint v1);
    typedef void (* PFNVKGLUNIFORM3UIPROC) (GLint location, GLuint v0, GLuint v1, GLuint v2);
    typedef void (* PFNVKGLUNIFORM4UIPROC) (GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
    typedef void (* PFNVKGLUNIFORM1UIVPROC) (GLint location, GLsizei count, const GLuint *value);
    typedef void (* PFNVKGLUNIFORM2UIVPROC) (GLint location, GLsizei count, const GLuint *value);
    typedef void (* PFNVKGLUNIFORM3UIVPROC) (GLint location, GLsizei count, const GLuint *value);
    typedef void (* PFNVKGLUNIFORM4UIVPROC) (GLint location, GLsizei count, const GLuint *value);
    typedef void (* PFNVKGLTEXPARAMETERIIVPROC) (GLenum target, GLenum pname, const GLint *params);
    typedef void (* PFNVKGLTEXPARAMETERIUIVPROC) (GLenum target, GLenum pname, const GLuint *params);
    typedef void (* PFNVKGLGETTEXPARAMETERIIVPROC) (GLenum target, GLenum pname, GLint *params);
    typedef void (* PFNVKGLGETTEXPARAMETERIUIVPROC) (GLenum target, GLenum pname, GLuint *params);
    typedef void (* PFNVKGLCLEARBUFFERIVPROC) (GLenum buffer, GLint drawbuffer, const GLint *value);
    typedef void (* PFNVKGLCLEARBUFFERUIVPROC) (GLenum buffer, GLint drawbuffer, const GLuint *value);
    typedef void (* PFNVKGLCLEARBUFFERFVPROC) (GLenum buffer, GLint drawbuffer, const GLfloat *value);
    typedef void (* PFNVKGLCLEARBUFFERFIPROC) (GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil);
    typedef const GLubyte *(* PFNVKGLGETSTRINGIPROC) (GLenum name, GLuint index);
    typedef GLboolean (* PFNVKGLISRENDERBUFFERPROC) (GLuint renderbuffer);
    typedef void (* PFNVKGLBINDRENDERBUFFERPROC) (GLenum target, GLuint renderbuffer);
    typedef void (* PFNVKGLDELETERENDERBUFFERSPROC) (GLsizei n, const GLuint *renderbuffers);
    typedef void (* PFNVKGLGENRENDERBUFFERSPROC) (GLsizei n, GLuint *renderbuffers);
    typedef void (* PFNVKGLRENDERBUFFERSTORAGEPROC) (GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
    typedef void (* PFNVKGLGETRENDERBUFFERPARAMETERIVPROC) (GLenum target, GLenum pname, GLint *params);
    typedef GLboolean (* PFNVKGLISFRAMEBUFFERPROC) (GLuint framebuffer);
    typedef void (* PFNVKGLBINDFRAMEBUFFERPROC) (GLenum target, GLuint framebuffer);
    typedef void (* PFNVKGLDELETEFRAMEBUFFERSPROC) (GLsizei n, const GLuint *framebuffers);
    typedef void (* PFNVKGLGENFRAMEBUFFERSPROC) (GLsizei n, GLuint *framebuffers);
    typedef GLenum (* PFNVKGLCHECKFRAMEBUFFERSTATUSPROC) (GLenum target);
    typedef void (* PFNVKGLFRAMEBUFFERTEXTURE1DPROC) (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
    typedef void (* PFNVKGLFRAMEBUFFERTEXTURE2DPROC) (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
    typedef void (* PFNVKGLFRAMEBUFFERTEXTURE3DPROC) (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset);
    typedef void (* PFNVKGLFRAMEBUFFERRENDERBUFFERPROC) (GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
    typedef void (* PFNVKGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC) (GLenum target, GLenum attachment, GLenum pname, GLint *params);
    typedef void (* PFNVKGLGENERATEMIPMAPPROC) (GLenum target);
    typedef void (* PFNVKGLBLITFRAMEBUFFERPROC) (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter);
    typedef void (* PFNVKGLRENDERBUFFERSTORAGEMULTISAMPLEPROC) (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
    typedef void (* PFNVKGLFRAMEBUFFERTEXTURELAYERPROC) (GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer);
    typedef void *(* PFNVKGLMAPBUFFERRANGEPROC) (GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access);
    typedef void (* PFNVKGLFLUSHMAPPEDBUFFERRANGEPROC) (GLenum target, GLintptr offset, GLsizeiptr length);
    typedef void (* PFNVKGLBINDVERTEXARRAYPROC) (GLuint array);
    typedef void (* PFNVKGLDELETEVERTEXARRAYSPROC) (GLsizei n, const GLuint *arrays);
    typedef void (* PFNVKGLGENVERTEXARRAYSPROC) (GLsizei n, GLuint *arrays);
    typedef GLboolean (* PFNVKGLISVERTEXARRAYPROC) (GLuint array);
    
    /* VKGL GL entrypoints : GL 3.1 */
    typedef void (* PFNVKGLDRAWARRAYSINSTANCEDPROC) (GLenum mode, GLint first, GLsizei count, GLsizei instancecount);
    typedef void (* PFNVKGLDRAWELEMENTSINSTANCEDPROC) (GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei instancecount);
    typedef void (* PFNVKGLTEXBUFFERPROC) (GLenum target, GLenum internalformat, GLuint buffer);
    typedef void (* PFNVKGLPRIMITIVERESTARTINDEXPROC) (GLuint index);
    typedef void (* PFNVKGLCOPYBUFFERSUBDATAPROC) (GLenum readTarget, GLenum writeTarget, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size);
    typedef void (* PFNVKGLGETUNIFORMINDICESPROC) (GLuint program, GLsizei uniformCount, const GLchar *const*uniformNames, GLuint *uniformIndices);
    typedef void (* PFNVKGLGETACTIVEUNIFORMSIVPROC) (GLuint program, GLsizei uniformCount, const GLuint *uniformIndices, GLenum pname, GLint *params);
    typedef void (* PFNVKGLGETACTIVEUNIFORMNAMEPROC) (GLuint program, GLuint uniformIndex, GLsizei bufSize, GLsizei *length, GLchar *uniformName);
    typedef GLuint (* PFNVKGLGETUNIFORMBLOCKINDEXPROC) (GLuint program, const GLchar *uniformBlockName);
    typedef void (* PFNVKGLGETACTIVEUNIFORMBLOCKIVPROC) (GLuint program, GLuint uniformBlockIndex, GLenum pname, GLint *params);
    typedef void (* PFNVKGLGETACTIVEUNIFORMBLOCKNAMEPROC) (GLuint program, GLuint uniformBlockIndex, GLsizei bufSize, GLsizei *length, GLchar *uniformBlockName);
    typedef void (* PFNVKGLUNIFORMBLOCKBINDINGPROC) (GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding);
    
    /* VKGL GL entrypoints : GL 3.2 */
    typedef void (* PFNVKGLDRAWELEMENTSBASEVERTEXPROC) (GLenum mode, GLsizei count, GLenum type, const void *indices, GLint basevertex);
    typedef void (* PFNVKGLDRAWRANGEELEMENTSBASEVERTEXPROC) (GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void *indices, GLint basevertex);
    typedef void (* PFNVKGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC) (GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei instancecount, GLint basevertex);
    typedef void (* PFNVKGLMULTIDRAWELEMENTSBASEVERTEXPROC) (GLenum mode, const GLsizei *count, GLenum type, const void *const*indices, GLsizei drawcount, const GLint *basevertex);
    typedef void (* PFNVKGLPROVOKINGVERTEXPROC) (GLenum mode);
    typedef GLsync (* PFNVKGLFENCESYNCPROC) (GLenum condition, GLbitfield flags);
    typedef GLboolean (* PFNVKGLISSYNCPROC) (GLsync sync);
    typedef void (* PFNVKGLDELETESYNCPROC) (GLsync sync);
    typedef GLenum (* PFNVKGLCLIENTWAITSYNCPROC) (GLsync sync, GLbitfield flags, GLuint64 timeout);
    typedef void (* PFNVKGLWAITSYNCPROC) (GLsync sync, GLbitfield flags, GLuint64 timeout);
    typedef void (* PFNVKGLGETINTEGER64VPROC) (GLenum pname, GLint64 *data);
    typedef void (* PFNVKGLGETSYNCIVPROC) (GLsync sync, GLenum pname, GLsizei bufSize, GLsizei *length, GLint *values);
    typedef void (* PFNVKGLGETINTEGER64I_VPROC) (GLenum target, GLuint index, GLint64 *data);
    typedef void (* PFNVKGLGETBUFFERPARAMETERI64VPROC) (GLenum target, GLenum pname, GLint64 *params);
    typedef void (* PFNVKGLFRAMEBUFFERTEXTUREPROC) (GLenum target, GLenum attachment, GLuint texture, GLint level);
    typedef void (* PFNVKGLTEXIMAGE2DMULTISAMPLEPROC) (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations);
    typedef void (* PFNVKGLTEXIMAGE3DMULTISAMPLEPROC) (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations);
    typedef void (* PFNVKGLGETMULTISAMPLEFVPROC) (GLenum pname, GLuint index, GLfloat *val);
    typedef void (* PFNVKGLSAMPLEMASKIPROC) (GLuint maskNumber, GLbitfield mask);

    typedef uint32_t TextureUnit;
}

#endif /* VKGL_TYPES_TYPEDEFS_H */