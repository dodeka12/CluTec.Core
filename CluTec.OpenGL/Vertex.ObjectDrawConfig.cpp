////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.OpenGL
// file:      Vertex.ObjectDrawConfig.cpp
//
// summary:   Implements the vertex. object draw configuration class
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

#include "CluTec.Base/Exception.h"

#include "Api.h"
#include "DataType.h"
#include "Vertex.ObjectDrawConfig.h"


namespace Clu
{
	namespace OpenGL
	{
		namespace Vertex
		{


			CObjectDrawConfig::CObjectDrawConfig()
			{
				m_eMode = EDrawMode::Points;
				m_uInstanceCount = 0;
				m_nElementCount = 0;
			}

			bool CObjectDrawConfig::IsValid() const
			{
				return (m_uInstanceCount > 0) && (m_nElementCount > 0);
			}

			unsigned CObjectDrawConfig::BufferId() const
			{
				return m_bufIndex.Id();
			}

			size_t CObjectDrawConfig::ElementCount() const
			{
				return m_nElementCount;
			}

			unsigned CObjectDrawConfig::InstanceCount() const
			{
				return m_uInstanceCount;
			}

			EDrawMode CObjectDrawConfig::Mode() const
			{
				return m_eMode;
			}


			void CObjectDrawConfig::Create(EDrawMode eMode, unsigned uInstanceCount, size_t nElementCount)
			{
				try
				{
					Destroy();

					m_eMode = eMode;
					m_uInstanceCount = uInstanceCount;
					m_nElementCount = nElementCount;
				}
				CLU_CATCH_RETHROW_ALL("Error creating vertex object draw configuration")
			}

			void CObjectDrawConfig::Create(EDrawMode eMode, unsigned uInstanceCount, const std::vector<unsigned>& vecIndex)
			{
				try
				{
					Destroy();

					m_eMode = eMode;
					m_uInstanceCount = uInstanceCount;
					m_nElementCount = vecIndex.size();

					m_bufIndex.Create(m_nElementCount, EBufferUsage::StaticDraw, vecIndex.data());
				}
				CLU_CATCH_RETHROW_ALL("Error creating vertex object draw configuration with indices")
			}

			void CObjectDrawConfig::Destroy()
			{
				try
				{
					m_bufIndex.Destroy();
					m_eMode = EDrawMode::Points;
					m_uInstanceCount = 0;
					m_nElementCount = 0;
				}
				CLU_CATCH_RETHROW_ALL("Error destroying vertex object draw configuration")
			}



			void CObjectDrawConfig::Bind()
			{
				if (m_bufIndex.IsValid())
				{
					m_bufIndex.Bind();
				}
			}

			void CObjectDrawConfig::Unbind()
			{
				if (m_bufIndex.IsValid())
				{
					m_bufIndex.Unbind();
				}
			}


			void CObjectDrawConfig::Draw()
			{
				try
				{
					if (!IsValid())
					{
						throw CLU_EXCEPTION("Invalid vertex object draw configuration");
					}

					if (m_bufIndex.IsValid())
					{
						m_bufIndex.Bind();

						if (m_uInstanceCount == 1)
						{
							CLU_OGL_CALL(glDrawElements((GLenum)m_eMode, (GLsizei)m_nElementCount, (GLenum)EDataType::UInt32, nullptr));
						}
						else
						{
							CLU_OGL_CALL(glDrawElementsInstanced((GLenum)m_eMode, (GLsizei)m_nElementCount, (GLenum)EDataType::UInt32, nullptr, m_uInstanceCount));
						}

						m_bufIndex.Unbind();
					}
					else
					{
						if (m_uInstanceCount == 1)
						{
							CLU_OGL_CALL(glDrawArrays((GLenum)m_eMode, 0, (GLsizei)m_nElementCount));
						}
						else
						{
							CLU_OGL_CALL(glDrawArraysInstanced((GLenum)m_eMode, 0, (GLsizei)m_nElementCount, m_uInstanceCount));
						}
					}
				}
				CLU_CATCH_RETHROW_ALL("Error darwing vertex object draw configuration")
			}

		}
	}
}
