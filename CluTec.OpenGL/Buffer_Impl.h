////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.OpenGL
// file:      Buffer_Impl.h
//
// summary:   Declares the buffer implementation class
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

#include "CluTec.Types1/ExceptionTypes.h"

#include "Api.h"
#include "Buffer.h"

namespace Clu
{
	namespace OpenGL
	{
		template<EBufferType t_eType, typename TElement>
		CBuffer<t_eType, TElement>::CBuffer()
		{
			m_uId = 0;
			m_nCount = 0;
			m_bIsBound = false;
			m_eUsage = EBufferUsage::StaticDraw;
		}

		template<EBufferType t_eType, typename TElement>
		CBuffer<t_eType, TElement>::~CBuffer()
		{
			try
			{
				Destroy();
			}
			CLU_LOG_DTOR_CATCH_ALL(CBuffer)
		}


		template<EBufferType t_eType, typename TElement>
		void CBuffer<t_eType, TElement>::Create(size_t nCount, EBufferUsage eUsage, const TElement* pData)
		{
			try
			{
				Destroy();

				if (nCount > 0)
				{
					GLuint uId = 0;
					HGLRC hGLRC = wglGetCurrentContext();
					CLU_OGL_CALL(glGenBuffers(1, &uId));
					CLU_OGL_CALL(glBindBuffer((GLenum)Type, uId));
					try
					{
						CLU_OGL_CALL(glBufferData((GLenum)Type, nCount * sizeof(TElement), pData, (GLenum)eUsage));
					}
					catch (Clu::CIException& xEx)
					{
						glDeleteBuffers(1, &uId);
						throw CLU_EXCEPT_TYPE_NEST(OutOfMemory, "Out of memory while creating OpenGL vertex buffer", std::move(xEx));
					}

					m_uId = uId;
					m_nCount = nCount;
					m_eUsage = eUsage;

					CLU_OGL_CALL(glBindBuffer((GLenum)Type, 0));
				}
			}
			CLU_CATCH_RETHROW_ALL("Error creating vertex buffer")
		}

		template<EBufferType t_eType, typename TElement>
		void CBuffer<t_eType, TElement>::Create(size_t nCount, EBufferUsage eUsage)
		{
			Create(nCount, eUsage, nullptr);
		}


		template<EBufferType t_eType, typename _TElement>
		void CBuffer<t_eType, _TElement>::Update(const TElement* pData)
		{
			try
			{
				if (!IsValid())
				{
					throw CLU_EXCEPTION("Vertex buffer is invalid");
				}

				CLU_OGL_CALL(glBindBuffer((GLenum)Type, m_uId));
				CLU_OGL_CALL(glBufferData((GLenum)Type, m_nCount * sizeof(TElement), pData, (GLenum)m_eUsage));
				CLU_OGL_CALL(glBindBuffer((GLenum)Type, 0));
			}
			CLU_CATCH_RETHROW_ALL("Error updating vertex buffer data")
		}


		template<EBufferType t_eType, typename TElement>
		void CBuffer<t_eType, TElement>::Destroy()
		{
			try
			{
				if (IsBound())
				{
					Unbind();
				}

				if (IsValid())
				{
					CLU_OGL_CALL(glDeleteBuffers(1, &m_uId));
					m_uId = 0;
					m_nCount = 0;
					m_eUsage = EBufferUsage::StaticDraw;
				}
			}
			CLU_CATCH_RETHROW_ALL("Error deleting vertex buffer")
		}


		template<EBufferType t_eType, typename TElement>
		void CBuffer<t_eType, TElement>::Bind()
		{
			try
			{
				if (!IsValid())
				{
					throw CLU_EXCEPTION("Invalid vertex buffer");
				}

				if (!IsBound())
				{
					CLU_OGL_CALL(glBindBuffer((GLenum)Type, m_uId));
					m_bIsBound = true;
				}
			}
			CLU_CATCH_RETHROW_ALL("Error binding vertex buffer")
		}

		template<EBufferType t_eType, typename TElement>
		void CBuffer<t_eType, TElement>::Unbind()
		{
			try
			{
				if (!IsValid())
				{
					throw CLU_EXCEPTION("Invalid vertex buffer");
				}

				if (IsBound())
				{
					CLU_OGL_CALL(glBindBuffer((GLenum)Type, 0));
					m_bIsBound = false;
				}
			}
			CLU_CATCH_RETHROW_ALL("Error un-binding vertex buffer")
		}


	}
}