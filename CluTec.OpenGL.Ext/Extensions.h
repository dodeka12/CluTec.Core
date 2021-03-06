////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.OpenGL.Ext.rtl
// file:      Extensions.h
//
// summary:   Declares the extensions class
//
//            Copyright (c) 2019 by Christian Perwass.
//
//            This file is part of the CluTecLib library.
//
//            The CluTecLib library is free software: you can redistribute it and / or modify
//            it under the terms of the GNU Lesser General Public License as published by
//            the Free Software Foundation, either version 3 of the License, or
//            (at your option) any later version.
//
//            The CluTecLib library is distributed in the hope that it will be useful,
//            but WITHOUT ANY WARRANTY; without even the implied warranty of
//            MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
//            GNU Lesser General Public License for more details.
//
//            You should have received a copy of the GNU Lesser General Public License
//            along with the CluTecLib library.
//            If not, see <http://www.gnu.org/licenses/>.
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#ifdef CT_GLEXT_API_EXPORTS
	#define CLU_GLEXT_API __declspec(dllexport)
#else
	#define CLU_GLEXT_API __declspec(dllimport)
#endif

#ifndef WIN32_LEAN_AND_MEAN
#	define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
#endif

#include "windows.h"

#include "Gl/GL.h"

#ifndef WGL_NV_gpu_affinity
	#define WGL_NV_gpu_affinity
#endif

#include "glext.h"
#include "wglext.h"

// namespace: Clu.OpenGL.Extensions
namespace Clu
{
	namespace OpenGL
	{
		namespace Extensions
		{
			CLU_GLEXT_API bool Init();

			CLU_GLEXT_API bool IsInitialized();

			CLU_GLEXT_API bool GetGLVersion(int* piMajor, int* piMinor);

			CLU_GLEXT_API bool GetGLSLVersion(int* piMajor, int* piMinor);

			CLU_GLEXT_API bool IsShaderAvailable();
		}
	}
}

// WGL ARB
CLU_GLEXT_API PFNWGLGETPIXELFORMATATTRIBIVARBPROC wglGetPixelFormatAttribivARB;
CLU_GLEXT_API PFNWGLGETPIXELFORMATATTRIBFVARBPROC wglGetPixelFormatAttribfvARB;
CLU_GLEXT_API PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB;

CLU_GLEXT_API PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT;
CLU_GLEXT_API PFNWGLGETSWAPINTERVALEXTPROC wglGetSwapIntervalEXT;

CLU_GLEXT_API PFNWGLCOPYIMAGESUBDATANVPROC wglCopyImageSubDataNV;

// OpenGL 1.2
CLU_GLEXT_API PFNGLBLENDCOLORPROC glBlendColor;
CLU_GLEXT_API PFNGLBLENDEQUATIONPROC glBlendEquation;
CLU_GLEXT_API PFNGLDRAWRANGEELEMENTSPROC glDrawRangeElements;
CLU_GLEXT_API PFNGLCOLORTABLEPROC glColorTable;
CLU_GLEXT_API PFNGLCOLORTABLEPARAMETERFVPROC glColorTableParameterfv;
CLU_GLEXT_API PFNGLCOLORTABLEPARAMETERIVPROC glColorTableParameteriv;
CLU_GLEXT_API PFNGLCOPYCOLORTABLEPROC glCopyColorTable;
CLU_GLEXT_API PFNGLGETCOLORTABLEPROC glGetColorTable;
CLU_GLEXT_API PFNGLGETCOLORTABLEPARAMETERFVPROC glGetColorTableParameterfv;
CLU_GLEXT_API PFNGLGETCOLORTABLEPARAMETERIVPROC glGetColorTableParameteriv;
CLU_GLEXT_API PFNGLCOLORSUBTABLEPROC glColorSubTable;
CLU_GLEXT_API PFNGLCOPYCOLORSUBTABLEPROC glCopyColorSubTable;
CLU_GLEXT_API PFNGLCONVOLUTIONFILTER1DPROC glConvolutionFilter1D;
CLU_GLEXT_API PFNGLCONVOLUTIONFILTER2DPROC glConvolutionFilter2D;
CLU_GLEXT_API PFNGLCONVOLUTIONPARAMETERFPROC glConvolutionParameterf;
CLU_GLEXT_API PFNGLCONVOLUTIONPARAMETERFVPROC glConvolutionParameterfv;
CLU_GLEXT_API PFNGLCONVOLUTIONPARAMETERIPROC glConvolutionParameteri;
CLU_GLEXT_API PFNGLCONVOLUTIONPARAMETERIVPROC glConvolutionParameteriv;
CLU_GLEXT_API PFNGLCOPYCONVOLUTIONFILTER1DPROC glCopyConvolutionFilter1D;
CLU_GLEXT_API PFNGLCOPYCONVOLUTIONFILTER2DPROC glCopyConvolutionFilter2D;
CLU_GLEXT_API PFNGLGETCONVOLUTIONFILTERPROC glGetConvolutionFilter;
CLU_GLEXT_API PFNGLGETCONVOLUTIONPARAMETERFVPROC glGetConvolutionParameterfv;
CLU_GLEXT_API PFNGLGETCONVOLUTIONPARAMETERIVPROC glGetConvolutionParameteriv;
CLU_GLEXT_API PFNGLGETSEPARABLEFILTERPROC glGetSeparableFilter;
CLU_GLEXT_API PFNGLSEPARABLEFILTER2DPROC glSeparableFilter2D;
CLU_GLEXT_API PFNGLGETHISTOGRAMPROC glGetHistogram;
CLU_GLEXT_API PFNGLGETHISTOGRAMPARAMETERFVPROC glGetHistogramParameterfv;
CLU_GLEXT_API PFNGLGETHISTOGRAMPARAMETERIVPROC glGetHistogramParameteriv;
CLU_GLEXT_API PFNGLGETMINMAXPROC glGetMinmax;
CLU_GLEXT_API PFNGLGETMINMAXPARAMETERFVPROC glGetMinmaxParameterfv;
CLU_GLEXT_API PFNGLGETMINMAXPARAMETERIVPROC glGetMinmaxParameteriv;
CLU_GLEXT_API PFNGLHISTOGRAMPROC glHistogram;
CLU_GLEXT_API PFNGLMINMAXPROC glMinmax;
CLU_GLEXT_API PFNGLRESETHISTOGRAMPROC glResetHistogram;
CLU_GLEXT_API PFNGLRESETMINMAXPROC glResetMinmax;
CLU_GLEXT_API PFNGLTEXIMAGE3DPROC glTexImage3D;
CLU_GLEXT_API PFNGLTEXSUBIMAGE3DPROC glTexSubImage3D;
CLU_GLEXT_API PFNGLCOPYTEXSUBIMAGE3DPROC glCopyTexSubImage3D;

// OpenGL 1.3
CLU_GLEXT_API PFNGLACTIVETEXTUREPROC glActiveTexture;
CLU_GLEXT_API PFNGLCLIENTACTIVETEXTUREPROC glClientActiveTexture;
CLU_GLEXT_API PFNGLMULTITEXCOORD1DPROC glMultiTexCoord1d;
CLU_GLEXT_API PFNGLMULTITEXCOORD1DVPROC glMultiTexCoord1dv;
CLU_GLEXT_API PFNGLMULTITEXCOORD1FPROC glMultiTexCoord1f;
CLU_GLEXT_API PFNGLMULTITEXCOORD1FVPROC glMultiTexCoord1fv;
CLU_GLEXT_API PFNGLMULTITEXCOORD1IPROC glMultiTexCoord1i;
CLU_GLEXT_API PFNGLMULTITEXCOORD1IVPROC glMultiTexCoord1iv;
CLU_GLEXT_API PFNGLMULTITEXCOORD1SPROC glMultiTexCoord1s;
CLU_GLEXT_API PFNGLMULTITEXCOORD1SVPROC glMultiTexCoord1sv;
CLU_GLEXT_API PFNGLMULTITEXCOORD2DPROC glMultiTexCoord2d;
CLU_GLEXT_API PFNGLMULTITEXCOORD2DVPROC glMultiTexCoord2dv;
CLU_GLEXT_API PFNGLMULTITEXCOORD2FPROC glMultiTexCoord2f;
CLU_GLEXT_API PFNGLMULTITEXCOORD2FVPROC glMultiTexCoord2fv;
CLU_GLEXT_API PFNGLMULTITEXCOORD2IPROC glMultiTexCoord2i;
CLU_GLEXT_API PFNGLMULTITEXCOORD2IVPROC glMultiTexCoord2iv;
CLU_GLEXT_API PFNGLMULTITEXCOORD2SPROC glMultiTexCoord2s;
CLU_GLEXT_API PFNGLMULTITEXCOORD2SVPROC glMultiTexCoord2sv;
CLU_GLEXT_API PFNGLMULTITEXCOORD3DPROC glMultiTexCoord3d;
CLU_GLEXT_API PFNGLMULTITEXCOORD3DVPROC glMultiTexCoord3dv;
CLU_GLEXT_API PFNGLMULTITEXCOORD3FPROC glMultiTexCoord3f;
CLU_GLEXT_API PFNGLMULTITEXCOORD3FVPROC glMultiTexCoord3fv;
CLU_GLEXT_API PFNGLMULTITEXCOORD3IPROC glMultiTexCoord3i;
CLU_GLEXT_API PFNGLMULTITEXCOORD3IVPROC glMultiTexCoord3iv;
CLU_GLEXT_API PFNGLMULTITEXCOORD3SPROC glMultiTexCoord3s;
CLU_GLEXT_API PFNGLMULTITEXCOORD3SVPROC glMultiTexCoord3sv;
CLU_GLEXT_API PFNGLMULTITEXCOORD4DPROC glMultiTexCoord4d;
CLU_GLEXT_API PFNGLMULTITEXCOORD4DVPROC glMultiTexCoord4dv;
CLU_GLEXT_API PFNGLMULTITEXCOORD4FPROC glMultiTexCoord4f;
CLU_GLEXT_API PFNGLMULTITEXCOORD4FVPROC glMultiTexCoord4fv;
CLU_GLEXT_API PFNGLMULTITEXCOORD4IPROC glMultiTexCoord4i;
CLU_GLEXT_API PFNGLMULTITEXCOORD4IVPROC glMultiTexCoord4iv;
CLU_GLEXT_API PFNGLMULTITEXCOORD4SPROC glMultiTexCoord4s;
CLU_GLEXT_API PFNGLMULTITEXCOORD4SVPROC glMultiTexCoord4sv;
CLU_GLEXT_API PFNGLLOADTRANSPOSEMATRIXFPROC glLoadTransposeMatrixf;
CLU_GLEXT_API PFNGLLOADTRANSPOSEMATRIXDPROC glLoadTransposeMatrixd;
CLU_GLEXT_API PFNGLMULTTRANSPOSEMATRIXFPROC glMultTransposeMatrixf;
CLU_GLEXT_API PFNGLMULTTRANSPOSEMATRIXDPROC glMultTransposeMatrixd;
CLU_GLEXT_API PFNGLSAMPLECOVERAGEPROC glSampleCoverage;
CLU_GLEXT_API PFNGLCOMPRESSEDTEXIMAGE3DPROC glCompressedTexImage3D;
CLU_GLEXT_API PFNGLCOMPRESSEDTEXIMAGE2DPROC glCompressedTexImage2D;
CLU_GLEXT_API PFNGLCOMPRESSEDTEXIMAGE1DPROC glCompressedTexImage1D;
CLU_GLEXT_API PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC glCompressedTexSubImage3D;
CLU_GLEXT_API PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC glCompressedTexSubImage2D;
CLU_GLEXT_API PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC glCompressedTexSubImage1D;
CLU_GLEXT_API PFNGLGETCOMPRESSEDTEXIMAGEPROC glGetCompressedTexImage;

// OpenGL 1.4
CLU_GLEXT_API PFNGLBLENDFUNCSEPARATEPROC glBlendFuncSeparate;
CLU_GLEXT_API PFNGLFOGCOORDFPROC glFogCoordf;
CLU_GLEXT_API PFNGLFOGCOORDFVPROC glFogCoordfv;
CLU_GLEXT_API PFNGLFOGCOORDDPROC glFogCoordd;
CLU_GLEXT_API PFNGLFOGCOORDDVPROC glFogCoorddv;
CLU_GLEXT_API PFNGLFOGCOORDPOINTERPROC glFogCoordPointer;
CLU_GLEXT_API PFNGLMULTIDRAWARRAYSPROC glMultiDrawArrays;
CLU_GLEXT_API PFNGLMULTIDRAWELEMENTSPROC glMultiDrawElements;
CLU_GLEXT_API PFNGLPOINTPARAMETERFPROC glPointParameterf;
CLU_GLEXT_API PFNGLPOINTPARAMETERFVPROC glPointParameterfv;
CLU_GLEXT_API PFNGLPOINTPARAMETERIPROC glPointParameteri;
CLU_GLEXT_API PFNGLPOINTPARAMETERIVPROC glPointParameteriv;
CLU_GLEXT_API PFNGLSECONDARYCOLOR3BPROC glSecondaryColor3b;
CLU_GLEXT_API PFNGLSECONDARYCOLOR3BVPROC glSecondaryColor3bv;
CLU_GLEXT_API PFNGLSECONDARYCOLOR3DPROC glSecondaryColor3d;
CLU_GLEXT_API PFNGLSECONDARYCOLOR3DVPROC glSecondaryColor3dv;
CLU_GLEXT_API PFNGLSECONDARYCOLOR3FPROC glSecondaryColor3f;
CLU_GLEXT_API PFNGLSECONDARYCOLOR3FVPROC glSecondaryColor3fv;
CLU_GLEXT_API PFNGLSECONDARYCOLOR3IPROC glSecondaryColor3i;
CLU_GLEXT_API PFNGLSECONDARYCOLOR3IVPROC glSecondaryColor3iv;
CLU_GLEXT_API PFNGLSECONDARYCOLOR3SPROC glSecondaryColor3s;
CLU_GLEXT_API PFNGLSECONDARYCOLOR3SVPROC glSecondaryColor3sv;
CLU_GLEXT_API PFNGLSECONDARYCOLOR3UBPROC glSecondaryColor3ub;
CLU_GLEXT_API PFNGLSECONDARYCOLOR3UBVPROC glSecondaryColor3ubv;
CLU_GLEXT_API PFNGLSECONDARYCOLOR3UIPROC glSecondaryColor3ui;
CLU_GLEXT_API PFNGLSECONDARYCOLOR3UIVPROC glSecondaryColor3uiv;
CLU_GLEXT_API PFNGLSECONDARYCOLOR3USPROC glSecondaryColor3us;
CLU_GLEXT_API PFNGLSECONDARYCOLOR3USVPROC glSecondaryColor3usv;
CLU_GLEXT_API PFNGLSECONDARYCOLORPOINTERPROC glSecondaryColorPointer;
CLU_GLEXT_API PFNGLWINDOWPOS2DPROC glWindowPos2d;
CLU_GLEXT_API PFNGLWINDOWPOS2DVPROC glWindowPos2dv;
CLU_GLEXT_API PFNGLWINDOWPOS2FPROC glWindowPos2f;
CLU_GLEXT_API PFNGLWINDOWPOS2FVPROC glWindowPos2fv;
CLU_GLEXT_API PFNGLWINDOWPOS2IPROC glWindowPos2i;
CLU_GLEXT_API PFNGLWINDOWPOS2IVPROC glWindowPos2iv;
CLU_GLEXT_API PFNGLWINDOWPOS2SPROC glWindowPos2s;
CLU_GLEXT_API PFNGLWINDOWPOS2SVPROC glWindowPos2sv;
CLU_GLEXT_API PFNGLWINDOWPOS3DPROC glWindowPos3d;
CLU_GLEXT_API PFNGLWINDOWPOS3DVPROC glWindowPos3dv;
CLU_GLEXT_API PFNGLWINDOWPOS3FPROC glWindowPos3f;
CLU_GLEXT_API PFNGLWINDOWPOS3FVPROC glWindowPos3fv;
CLU_GLEXT_API PFNGLWINDOWPOS3IPROC glWindowPos3i;
CLU_GLEXT_API PFNGLWINDOWPOS3IVPROC glWindowPos3iv;
CLU_GLEXT_API PFNGLWINDOWPOS3SPROC glWindowPos3s;
CLU_GLEXT_API PFNGLWINDOWPOS3SVPROC glWindowPos3sv;

// OpenGL 1.5
CLU_GLEXT_API PFNGLGENQUERIESPROC glGenQueries;
CLU_GLEXT_API PFNGLDELETEQUERIESPROC glDeleteQueries;
CLU_GLEXT_API PFNGLISQUERYPROC glIsQuery;
CLU_GLEXT_API PFNGLBEGINQUERYPROC glBeginQuery;
CLU_GLEXT_API PFNGLENDQUERYPROC glEndQuery;
CLU_GLEXT_API PFNGLGETQUERYIVPROC glGetQueryiv;
CLU_GLEXT_API PFNGLGETQUERYOBJECTIVPROC glGetQueryObjectiv;
CLU_GLEXT_API PFNGLGETQUERYOBJECTUIVPROC glGetQueryObjectuiv;
CLU_GLEXT_API PFNGLBINDBUFFERPROC glBindBuffer;
CLU_GLEXT_API PFNGLDELETEBUFFERSPROC glDeleteBuffers;
CLU_GLEXT_API PFNGLGENBUFFERSPROC glGenBuffers;
CLU_GLEXT_API PFNGLISBUFFERPROC glIsBuffer;
CLU_GLEXT_API PFNGLBUFFERDATAPROC glBufferData;
CLU_GLEXT_API PFNGLBUFFERSUBDATAPROC glBufferSubData;
CLU_GLEXT_API PFNGLGETBUFFERSUBDATAPROC glGetBufferSubData;
CLU_GLEXT_API PFNGLMAPBUFFERPROC glMapBuffer;
CLU_GLEXT_API PFNGLUNMAPBUFFERPROC glUnmapBuffer;
CLU_GLEXT_API PFNGLGETBUFFERPARAMETERIVPROC glGetBufferParameteriv;
CLU_GLEXT_API PFNGLGETBUFFERPOINTERVPROC glGetBufferPointerv;

// OpenGL 2.0
CLU_GLEXT_API PFNGLBLENDEQUATIONSEPARATEPROC glBlendEquationSeparate;
CLU_GLEXT_API PFNGLDRAWBUFFERSPROC glDrawBuffers;
CLU_GLEXT_API PFNGLSTENCILOPSEPARATEPROC glStencilOpSeparate;
CLU_GLEXT_API PFNGLSTENCILFUNCSEPARATEPROC glStencilFuncSeparate;
CLU_GLEXT_API PFNGLSTENCILMASKSEPARATEPROC glStencilMaskSeparate;
CLU_GLEXT_API PFNGLATTACHSHADERPROC glAttachShader;
CLU_GLEXT_API PFNGLBINDATTRIBLOCATIONPROC glBindAttribLocation;
CLU_GLEXT_API PFNGLCOMPILESHADERPROC glCompileShader;
CLU_GLEXT_API PFNGLCREATEPROGRAMPROC glCreateProgram;
CLU_GLEXT_API PFNGLCREATESHADERPROC glCreateShader;
CLU_GLEXT_API PFNGLDELETEPROGRAMPROC glDeleteProgram;
CLU_GLEXT_API PFNGLDELETESHADERPROC glDeleteShader;
CLU_GLEXT_API PFNGLDETACHSHADERPROC glDetachShader;
CLU_GLEXT_API PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray;
CLU_GLEXT_API PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
CLU_GLEXT_API PFNGLGETACTIVEATTRIBPROC glGetActiveAttrib;
CLU_GLEXT_API PFNGLGETACTIVEUNIFORMPROC glGetActiveUniform;
CLU_GLEXT_API PFNGLGETATTACHEDSHADERSPROC glGetAttachedShaders;
CLU_GLEXT_API PFNGLGETATTRIBLOCATIONPROC glGetAttribLocation;
CLU_GLEXT_API PFNGLGETPROGRAMIVPROC glGetProgramiv;
CLU_GLEXT_API PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
CLU_GLEXT_API PFNGLGETSHADERIVPROC glGetShaderiv;
CLU_GLEXT_API PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
CLU_GLEXT_API PFNGLGETSHADERSOURCEPROC glGetShaderSource;
CLU_GLEXT_API PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
CLU_GLEXT_API PFNGLGETUNIFORMFVPROC glGetUniformfv;
CLU_GLEXT_API PFNGLGETUNIFORMIVPROC glGetUniformiv;
CLU_GLEXT_API PFNGLGETVERTEXATTRIBDVPROC glGetVertexAttribdv;
CLU_GLEXT_API PFNGLGETVERTEXATTRIBFVPROC glGetVertexAttribfv;
CLU_GLEXT_API PFNGLGETVERTEXATTRIBIVPROC glGetVertexAttribiv;
CLU_GLEXT_API PFNGLGETVERTEXATTRIBPOINTERVPROC glGetVertexAttribPointerv;
CLU_GLEXT_API PFNGLISPROGRAMPROC glIsProgram;
CLU_GLEXT_API PFNGLISSHADERPROC glIsShader;
CLU_GLEXT_API PFNGLLINKPROGRAMPROC glLinkProgram;
CLU_GLEXT_API PFNGLSHADERSOURCEPROC glShaderSource;
CLU_GLEXT_API PFNGLUSEPROGRAMPROC glUseProgram;
CLU_GLEXT_API PFNGLUNIFORM1FPROC glUniform1f;
CLU_GLEXT_API PFNGLUNIFORM2FPROC glUniform2f;
CLU_GLEXT_API PFNGLUNIFORM3FPROC glUniform3f;
CLU_GLEXT_API PFNGLUNIFORM4FPROC glUniform4f;
CLU_GLEXT_API PFNGLUNIFORM1IPROC glUniform1i;
CLU_GLEXT_API PFNGLUNIFORM2IPROC glUniform2i;
CLU_GLEXT_API PFNGLUNIFORM3IPROC glUniform3i;
CLU_GLEXT_API PFNGLUNIFORM4IPROC glUniform4i;
CLU_GLEXT_API PFNGLUNIFORM1FVPROC glUniform1fv;
CLU_GLEXT_API PFNGLUNIFORM2FVPROC glUniform2fv;
CLU_GLEXT_API PFNGLUNIFORM3FVPROC glUniform3fv;
CLU_GLEXT_API PFNGLUNIFORM4FVPROC glUniform4fv;
CLU_GLEXT_API PFNGLUNIFORM1IVPROC glUniform1iv;
CLU_GLEXT_API PFNGLUNIFORM2IVPROC glUniform2iv;
CLU_GLEXT_API PFNGLUNIFORM3IVPROC glUniform3iv;
CLU_GLEXT_API PFNGLUNIFORM4IVPROC glUniform4iv;
CLU_GLEXT_API PFNGLUNIFORMMATRIX2FVPROC glUniformMatrix2fv;
CLU_GLEXT_API PFNGLUNIFORMMATRIX3FVPROC glUniformMatrix3fv;
CLU_GLEXT_API PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv;
CLU_GLEXT_API PFNGLVALIDATEPROGRAMPROC glValidateProgram;
CLU_GLEXT_API PFNGLVERTEXATTRIB1DPROC glVertexAttrib1d;
CLU_GLEXT_API PFNGLVERTEXATTRIB1DVPROC glVertexAttrib1dv;
CLU_GLEXT_API PFNGLVERTEXATTRIB1FPROC glVertexAttrib1f;
CLU_GLEXT_API PFNGLVERTEXATTRIB1FVPROC glVertexAttrib1fv;
CLU_GLEXT_API PFNGLVERTEXATTRIB1SPROC glVertexAttrib1s;
CLU_GLEXT_API PFNGLVERTEXATTRIB1SVPROC glVertexAttrib1sv;
CLU_GLEXT_API PFNGLVERTEXATTRIB2DPROC glVertexAttrib2d;
CLU_GLEXT_API PFNGLVERTEXATTRIB2DVPROC glVertexAttrib2dv;
CLU_GLEXT_API PFNGLVERTEXATTRIB2FPROC glVertexAttrib2f;
CLU_GLEXT_API PFNGLVERTEXATTRIB2FVPROC glVertexAttrib2fv;
CLU_GLEXT_API PFNGLVERTEXATTRIB2SPROC glVertexAttrib2s;
CLU_GLEXT_API PFNGLVERTEXATTRIB2SVPROC glVertexAttrib2sv;
CLU_GLEXT_API PFNGLVERTEXATTRIB3DPROC glVertexAttrib3d;
CLU_GLEXT_API PFNGLVERTEXATTRIB3DVPROC glVertexAttrib3dv;
CLU_GLEXT_API PFNGLVERTEXATTRIB3FPROC glVertexAttrib3f;
CLU_GLEXT_API PFNGLVERTEXATTRIB3FVPROC glVertexAttrib3fv;
CLU_GLEXT_API PFNGLVERTEXATTRIB3SPROC glVertexAttrib3s;
CLU_GLEXT_API PFNGLVERTEXATTRIB3SVPROC glVertexAttrib3sv;
CLU_GLEXT_API PFNGLVERTEXATTRIB4NBVPROC glVertexAttrib4Nbv;
CLU_GLEXT_API PFNGLVERTEXATTRIB4NIVPROC glVertexAttrib4Niv;
CLU_GLEXT_API PFNGLVERTEXATTRIB4NSVPROC glVertexAttrib4Nsv;
CLU_GLEXT_API PFNGLVERTEXATTRIB4NUBPROC glVertexAttrib4Nub;
CLU_GLEXT_API PFNGLVERTEXATTRIB4NUBVPROC glVertexAttrib4Nubv;
CLU_GLEXT_API PFNGLVERTEXATTRIB4NUIVPROC glVertexAttrib4Nuiv;
CLU_GLEXT_API PFNGLVERTEXATTRIB4NUSVPROC glVertexAttrib4Nusv;
CLU_GLEXT_API PFNGLVERTEXATTRIB4BVPROC glVertexAttrib4bv;
CLU_GLEXT_API PFNGLVERTEXATTRIB4DPROC glVertexAttrib4d;
CLU_GLEXT_API PFNGLVERTEXATTRIB4DVPROC glVertexAttrib4dv;
CLU_GLEXT_API PFNGLVERTEXATTRIB4FPROC glVertexAttrib4f;
CLU_GLEXT_API PFNGLVERTEXATTRIB4FVPROC glVertexAttrib4fv;
CLU_GLEXT_API PFNGLVERTEXATTRIB4IVPROC glVertexAttrib4iv;
CLU_GLEXT_API PFNGLVERTEXATTRIB4SPROC glVertexAttrib4s;
CLU_GLEXT_API PFNGLVERTEXATTRIB4SVPROC glVertexAttrib4sv;
CLU_GLEXT_API PFNGLVERTEXATTRIB4UBVPROC glVertexAttrib4ubv;
CLU_GLEXT_API PFNGLVERTEXATTRIB4UIVPROC glVertexAttrib4uiv;
CLU_GLEXT_API PFNGLVERTEXATTRIB4USVPROC glVertexAttrib4usv;
CLU_GLEXT_API PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;

// OpenGL 2.1
CLU_GLEXT_API PFNGLUNIFORMMATRIX2X3FVPROC glUniformMatrix2x3fv;
CLU_GLEXT_API PFNGLUNIFORMMATRIX3X2FVPROC glUniformMatrix3x2fv;
CLU_GLEXT_API PFNGLUNIFORMMATRIX2X4FVPROC glUniformMatrix2x4fv;
CLU_GLEXT_API PFNGLUNIFORMMATRIX4X2FVPROC glUniformMatrix4x2fv;
CLU_GLEXT_API PFNGLUNIFORMMATRIX3X4FVPROC glUniformMatrix3x4fv;
CLU_GLEXT_API PFNGLUNIFORMMATRIX4X3FVPROC glUniformMatrix4x3fv;

// ///////////////////////////////////////////////////////////////////////////////////////
// OpenGL 3.0
CLU_GLEXT_API PFNGLCOLORMASKIPROC glColorMaski;
CLU_GLEXT_API PFNGLGETBOOLEANI_VPROC glGetBooleani_v;
CLU_GLEXT_API PFNGLGETINTEGERI_VPROC glGetIntegeri_v;
CLU_GLEXT_API PFNGLENABLEIPROC glEnablei;
CLU_GLEXT_API PFNGLDISABLEIPROC glDisablei;
CLU_GLEXT_API PFNGLISENABLEDIPROC glIsEnabledi;


CLU_GLEXT_API PFNGLBEGINTRANSFORMFEEDBACKPROC glBeginTransformFeedback;


CLU_GLEXT_API PFNGLENDTRANSFORMFEEDBACKPROC glEndTransformFeedback;


CLU_GLEXT_API PFNGLBINDBUFFERRANGEPROC glBindBufferRange;


CLU_GLEXT_API PFNGLBINDBUFFERBASEPROC glBindBufferBase;


CLU_GLEXT_API PFNGLTRANSFORMFEEDBACKVARYINGSPROC glTransformFeedbackVaryings;


CLU_GLEXT_API PFNGLGETTRANSFORMFEEDBACKVARYINGPROC glGetTransformFeedbackVarying;


CLU_GLEXT_API PFNGLCLAMPCOLORPROC glClampColor;


CLU_GLEXT_API PFNGLBEGINCONDITIONALRENDERPROC glBeginConditionalRender;


CLU_GLEXT_API PFNGLENDCONDITIONALRENDERPROC glEndConditionalRender;


CLU_GLEXT_API PFNGLVERTEXATTRIBIPOINTERPROC glVertexAttribIPointer;


CLU_GLEXT_API PFNGLGETVERTEXATTRIBIIVPROC glGetVertexAttribIiv;


CLU_GLEXT_API PFNGLGETVERTEXATTRIBIUIVPROC glGetVertexAttribIuiv;


CLU_GLEXT_API PFNGLVERTEXATTRIBI1IPROC glVertexAttribI1i;


CLU_GLEXT_API PFNGLVERTEXATTRIBI2IPROC glVertexAttribI2i;


CLU_GLEXT_API PFNGLVERTEXATTRIBI3IPROC glVertexAttribI3i;


CLU_GLEXT_API PFNGLVERTEXATTRIBI4IPROC glVertexAttribI4i;


CLU_GLEXT_API PFNGLVERTEXATTRIBI1UIPROC glVertexAttribI1ui;


CLU_GLEXT_API PFNGLVERTEXATTRIBI2UIPROC glVertexAttribI2ui;


CLU_GLEXT_API PFNGLVERTEXATTRIBI3UIPROC glVertexAttribI3ui;


CLU_GLEXT_API PFNGLVERTEXATTRIBI4UIPROC glVertexAttribI4ui;


CLU_GLEXT_API PFNGLVERTEXATTRIBI1IVPROC glVertexAttribI1iv;


CLU_GLEXT_API PFNGLVERTEXATTRIBI2IVPROC glVertexAttribI2iv;


CLU_GLEXT_API PFNGLVERTEXATTRIBI3IVPROC glVertexAttribI3iv;


CLU_GLEXT_API PFNGLVERTEXATTRIBI4IVPROC glVertexAttribI4iv;


CLU_GLEXT_API PFNGLVERTEXATTRIBI1UIVPROC glVertexAttribI1uiv;


CLU_GLEXT_API PFNGLVERTEXATTRIBI2UIVPROC glVertexAttribI2uiv;


CLU_GLEXT_API PFNGLVERTEXATTRIBI3UIVPROC glVertexAttribI3uiv;


CLU_GLEXT_API PFNGLVERTEXATTRIBI4UIVPROC glVertexAttribI4uiv;


CLU_GLEXT_API PFNGLVERTEXATTRIBI4BVPROC glVertexAttribI4bv;


CLU_GLEXT_API PFNGLVERTEXATTRIBI4SVPROC glVertexAttribI4sv;


CLU_GLEXT_API PFNGLVERTEXATTRIBI4UBVPROC glVertexAttribI4ubv;


CLU_GLEXT_API PFNGLVERTEXATTRIBI4USVPROC glVertexAttribI4usv;


CLU_GLEXT_API PFNGLGETUNIFORMUIVPROC glGetUniformuiv;


CLU_GLEXT_API PFNGLBINDFRAGDATALOCATIONPROC glBindFragDataLocation;


CLU_GLEXT_API PFNGLGETFRAGDATALOCATIONPROC glGetFragDataLocation;


CLU_GLEXT_API PFNGLUNIFORM1UIPROC glUniform1ui;


CLU_GLEXT_API PFNGLUNIFORM2UIPROC glUniform2ui;


CLU_GLEXT_API PFNGLUNIFORM3UIPROC glUniform3ui;


CLU_GLEXT_API PFNGLUNIFORM4UIPROC glUniform4ui;


CLU_GLEXT_API PFNGLUNIFORM1UIVPROC glUniform1uiv;


CLU_GLEXT_API PFNGLUNIFORM2UIVPROC glUniform2uiv;


CLU_GLEXT_API PFNGLUNIFORM3UIVPROC glUniform3uiv;


CLU_GLEXT_API PFNGLUNIFORM4UIVPROC glUniform4uiv;


CLU_GLEXT_API PFNGLTEXPARAMETERIIVPROC glTexParameterIiv;


CLU_GLEXT_API PFNGLTEXPARAMETERIUIVPROC glTexParameterIuiv;


CLU_GLEXT_API PFNGLGETTEXPARAMETERIIVPROC glGetTexParameterIiv;


CLU_GLEXT_API PFNGLGETTEXPARAMETERIUIVPROC glGetTexParameterIuiv;


CLU_GLEXT_API PFNGLCLEARBUFFERIVPROC glClearBufferiv;


CLU_GLEXT_API PFNGLCLEARBUFFERUIVPROC glClearBufferuiv;


CLU_GLEXT_API PFNGLCLEARBUFFERFVPROC glClearBufferfv;


CLU_GLEXT_API PFNGLCLEARBUFFERFIPROC glClearBufferfi;


CLU_GLEXT_API PFNGLGETSTRINGIPROC glGetStringi;


CLU_GLEXT_API PFNGLISRENDERBUFFERPROC glIsRenderbuffer;


CLU_GLEXT_API PFNGLBINDRENDERBUFFERPROC glBindRenderbuffer;


CLU_GLEXT_API PFNGLDELETERENDERBUFFERSPROC glDeleteRenderbuffers;


CLU_GLEXT_API PFNGLGENRENDERBUFFERSPROC glGenRenderbuffers;


CLU_GLEXT_API PFNGLRENDERBUFFERSTORAGEPROC glRenderbufferStorage;


CLU_GLEXT_API PFNGLGETRENDERBUFFERPARAMETERIVPROC glGetRenderbufferParameteriv;


CLU_GLEXT_API PFNGLISFRAMEBUFFERPROC glIsFramebuffer;


CLU_GLEXT_API PFNGLBINDFRAMEBUFFERPROC glBindFramebuffer;


CLU_GLEXT_API PFNGLDELETEFRAMEBUFFERSPROC glDeleteFramebuffers;


CLU_GLEXT_API PFNGLGENFRAMEBUFFERSPROC glGenFramebuffers;


CLU_GLEXT_API PFNGLCHECKFRAMEBUFFERSTATUSPROC glCheckFramebufferStatus;


CLU_GLEXT_API PFNGLFRAMEBUFFERTEXTURE1DPROC glFramebufferTexture1D;


CLU_GLEXT_API PFNGLFRAMEBUFFERTEXTURE2DPROC glFramebufferTexture2D;


CLU_GLEXT_API PFNGLFRAMEBUFFERTEXTURE3DPROC glFramebufferTexture3D;


CLU_GLEXT_API PFNGLFRAMEBUFFERRENDERBUFFERPROC glFramebufferRenderbuffer;


CLU_GLEXT_API PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC glGetFramebufferAttachmentParameteriv;


CLU_GLEXT_API PFNGLGENERATEMIPMAPPROC glGenerateMipmap;


CLU_GLEXT_API PFNGLBLITFRAMEBUFFERPROC glBlitFramebuffer;


CLU_GLEXT_API PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC glRenderbufferStorageMultisample;


CLU_GLEXT_API PFNGLFRAMEBUFFERTEXTURELAYERPROC glFramebufferTextureLayer;


CLU_GLEXT_API PFNGLDRAWARRAYSINSTANCEDPROC glDrawArraysInstanced;


CLU_GLEXT_API PFNGLDRAWELEMENTSINSTANCEDPROC glDrawElementsInstanced;


CLU_GLEXT_API PFNGLTEXBUFFERPROC glTexBuffer;


CLU_GLEXT_API PFNGLPRIMITIVERESTARTINDEXPROC glPrimitiveRestartIndex;


// ///////////////////////////////////////////////////////////////////////////////////////
// OpenGL 4.1


