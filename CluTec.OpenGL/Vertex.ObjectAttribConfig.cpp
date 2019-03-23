////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.OpenGL
// file:      Vertex.ObjectAttribConfig.cpp
//
// summary:   Implements the vertex. object attribute configuration class
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
#include "Vertex.ObjectAttribConfig.h"

#define BUFFER_OFFSET(i) ((char*) nullptr + (i))


namespace Clu
{
	namespace OpenGL
	{
		namespace Vertex
		{
			CObjectAttribConfig::CObjectAttribConfig()
			{

			}


			void CObjectAttribConfig::SetElementSize(unsigned uElSize)
			{
				m_uElementSize = uElSize;
			}

			void CObjectAttribConfig::SetAttribute(EAttribute eType, const SAttribute& xAttribute)
			{
				try
				{
					m_mapAttribute[eType] = xAttribute;
				}
				CLU_CATCH_RETHROW_ALL("Error setting attribute");
			}

			const Clu::OpenGL::Vertex::SAttribute& CObjectAttribConfig::GetAttribute(EAttribute eType)
			{
				try
				{
					auto itEl = m_mapAttribute.end();
					if ((itEl = m_mapAttribute.find(eType)) == m_mapAttribute.end())
					{
						throw CLU_EXCEPTION("Attribute not found");
					}

					return itEl->second;
				}
				CLU_CATCH_RETHROW_ALL("Error getting attribute")
			}


			void CObjectAttribConfig::EnableAttribute(EAttribute eType, bool bEnable)
			{
				try
				{
					auto itEl = m_mapAttribute.end();
					if ((itEl = m_mapAttribute.find(eType)) == m_mapAttribute.end())
					{
						throw CLU_EXCEPTION("Attribute not found");
					}

					itEl->second.bEnabled = bEnable;
				}
				CLU_CATCH_RETHROW_ALL("Attribute not found")
			}


			bool CObjectAttribConfig::IsEnabled(EAttribute eType) const
			{
				try
				{
					auto itEl = m_mapAttribute.end();
					if ((itEl = m_mapAttribute.find(eType)) == m_mapAttribute.end())
					{
						throw CLU_EXCEPTION("Attribute not found");
					}

					return itEl->second.bEnabled;
				}
				CLU_CATCH_RETHROW_ALL("Attribute not found")
			}


			void CObjectAttribConfig::Bind(bool bUseAttributeArrays)
			{
				try
				{
					if (bUseAttributeArrays)
					{
						for (auto pairEl : m_mapAttribute)
						{
							SAttribute& xAttrib = pairEl.second;

							if (!xAttrib.bEnabled)
							{
								continue;
							}

							CLU_OGL_CALL(glEnableVertexAttribArray(GLuint(xAttrib.eType)));

							switch (xAttrib.eStorageType)
							{
							case EStorageType::Single:
								CLU_OGL_CALL(glVertexAttribPointer(GLuint(xAttrib.eType), xAttrib.iElementCount
									, (GLenum)xAttrib.eDataType, (GLboolean)(xAttrib.bNormalize ? GL_TRUE : GL_FALSE)
									, m_uElementSize, BUFFER_OFFSET(xAttrib.iOffset)));
								break;

							case EStorageType::Double:
								//CLU_OGL_CALL(glVertexAttribLPointer(GLuint(xAttrib.eType), xAttrib.iElementCount
								//	, (GLenum)xAttrib.eDataType)
								//	, m_uElementSize, BUFFER_OFFSET(xAttrib.iOffset)));
								throw CLU_EXCEPTION("Not implemented in OpenGL extension map, yet");
								break;

							case EStorageType::Integer:
								CLU_OGL_CALL(glVertexAttribIPointer(GLuint(xAttrib.eType), xAttrib.iElementCount
									, (GLenum)xAttrib.eDataType
									, m_uElementSize, BUFFER_OFFSET(xAttrib.iOffset)));
								break;
							}
						}
					}
					else
					{
						for (auto pairEl : m_mapAttribute)
						{
							SAttribute& xAttrib = pairEl.second;

							if (!xAttrib.bEnabled)
							{
								continue;
							}

							if (xAttrib.eType == EAttribute::Position)
							{
								CLU_OGL_CALL(glEnableClientState(GL_VERTEX_ARRAY));
								CLU_OGL_CALL(glVertexPointer(xAttrib.iElementCount, (GLenum)xAttrib.eDataType, m_uElementSize, BUFFER_OFFSET(xAttrib.iOffset)));
							}
							else if (xAttrib.eType == EAttribute::Color)
							{
								CLU_OGL_CALL(glEnableClientState(GL_COLOR_ARRAY));
								CLU_OGL_CALL(glColorPointer(xAttrib.iElementCount, (GLenum)xAttrib.eDataType, m_uElementSize, BUFFER_OFFSET(xAttrib.iOffset)));
							}
							else if (xAttrib.eType == EAttribute::Normal)
							{
								CLU_OGL_CALL(glEnableClientState(GL_NORMAL_ARRAY));
								CLU_OGL_CALL(glNormalPointer((GLenum)xAttrib.eDataType, m_uElementSize, BUFFER_OFFSET(xAttrib.iOffset)));
							}
							else if (int(xAttrib.eType) >= int(EAttribute::Tex0)
								&& int(xAttrib.eType) <= int(EAttribute::Tex7))
							{
								int iTexUnit = int(xAttrib.eType) - int(EAttribute::Tex0);
								CLU_OGL_CALL(glClientActiveTexture(GL_TEXTURE0 + iTexUnit));
								CLU_OGL_CALL(glEnableClientState(GL_TEXTURE_COORD_ARRAY));
								CLU_OGL_CALL(glTexCoordPointer(xAttrib.iElementCount, (GLenum)xAttrib.eDataType, m_uElementSize, BUFFER_OFFSET(xAttrib.iOffset)));
							}
						}
					}
				
				}
				CLU_CATCH_RETHROW_ALL("Error binding vertex attribute arrays")
			}


			void CObjectAttribConfig::Unbind(bool bUseAttributeArrays)
			{
				try
				{
					if (bUseAttributeArrays)
					{
						for (auto pairEl : m_mapAttribute)
						{
							SAttribute& xAttrib = pairEl.second;

							if (!xAttrib.bEnabled)
							{
								continue;
							}

							CLU_OGL_CALL(glDisableVertexAttribArray(GLuint(xAttrib.eType)));
						}
					}
					else
					{
						for (auto pairEl : m_mapAttribute)
						{
							SAttribute& xAttrib = pairEl.second;

							if (!xAttrib.bEnabled)
							{
								continue;
							}

							if (xAttrib.eType == EAttribute::Position)
							{
								CLU_OGL_CALL(glDisableClientState(GL_VERTEX_ARRAY));
							}
							else if (xAttrib.eType == EAttribute::Color)
							{
								CLU_OGL_CALL(glDisableClientState(GL_COLOR_ARRAY));
							}
							else if (xAttrib.eType == EAttribute::Normal)
							{
								CLU_OGL_CALL(glDisableClientState(GL_NORMAL_ARRAY));
							}
							else if (int(xAttrib.eType) >= int(EAttribute::Tex0)
								&& int(xAttrib.eType) <= int(EAttribute::Tex7))
							{
								int iTexUnit = int(xAttrib.eType) - int(EAttribute::Tex0);
								CLU_OGL_CALL(glClientActiveTexture(GL_TEXTURE0 + iTexUnit));
								CLU_OGL_CALL(glDisableClientState(GL_TEXTURE_COORD_ARRAY));
							}
						}
					}
				}
				CLU_CATCH_RETHROW_ALL("Error unbinding vertex attribute arrays")
			}

		}
	}
}
