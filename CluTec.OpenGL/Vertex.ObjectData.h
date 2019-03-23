////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.OpenGL
// file:      Vertex.ObjectData.h
//
// summary:   Declares the vertex. object data class
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

#include <vector>

#include "CluTec.Base/Exception.h"

#include "Buffer.h"
#include "Vertex.Data.h"
#include "Vertex.ObjectAttribConfig.h"

namespace Clu
{
	namespace OpenGL
	{
		namespace Vertex
		{


			template<EType t_eType>
			class CObjectData
			{};


			template<>
			class CObjectData<EType::Standard>
			{
			public:
				using TVertex = Vertex::_SData<Vertex::EType::Standard>;
				using TVertexBuffer = CBuffer<EBufferType::Vertex, TVertex>;

			public:
				static const EType Type = EType::Standard;


			protected:

				/// <summary>	The configuration for drawing. </summary>
				CObjectAttribConfig m_cfgDraw;

				/// <summary>	The configuration for picking. This sets the part id as color.</summary>
				CObjectAttribConfig m_cfgPick;

				TVertexBuffer m_bufVertex;

				bool m_bUsePickCfg;
				bool m_bUseVertexAttribArrays;

			protected:
				void _InitConfigs()
				{
					try
					{
						m_bUsePickCfg = false;
						m_bUseVertexAttribArrays = true;

						m_cfgDraw.SetElementSize(sizeof(TVertex));
						m_cfgPick.SetElementSize(sizeof(TVertex));

						// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
						m_cfgDraw.SetAttribute(EAttribute::Position
							, SAttribute(EAttribute::Position, EStorageType::Single, EDataType::Single, false, 3, TVertex::iOffsetPos, false));

						m_cfgPick.SetAttribute(EAttribute::Position
							, SAttribute(EAttribute::Position, EStorageType::Single, EDataType::Single, false, 3, TVertex::iOffsetPos, false));

						// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
						m_cfgDraw.SetAttribute(EAttribute::Color
							, SAttribute(EAttribute::Color, EStorageType::Single, EDataType::Single, false, 4, TVertex::iOffsetCol, false));

						m_cfgPick.SetAttribute(EAttribute::Color
							, SAttribute(EAttribute::Color, EStorageType::Single, EDataType::UInt8, true, 4, TVertex::iOffsetPartId, false));

						// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
						m_cfgDraw.SetAttribute(EAttribute::Normal
							, SAttribute(EAttribute::Normal, EStorageType::Single, EDataType::Single, false, 3, TVertex::iOffsetNorm, false));

						m_cfgPick.SetAttribute(EAttribute::Normal
							, SAttribute(EAttribute::Normal, EStorageType::Single, EDataType::Single, false, 3, TVertex::iOffsetNorm, false));

						// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
						for (int i = 0; i < 8; ++i)
						{
							EAttribute eTex = EAttribute(int(EAttribute::Tex0) + i);

							m_cfgDraw.SetAttribute(eTex
								, SAttribute(eTex, EStorageType::Single, EDataType::Single, false, 3, TVertex::iOffsetTex, false));

							m_cfgPick.SetAttribute(eTex
								, SAttribute(eTex, EStorageType::Single, EDataType::Single, false, 3, TVertex::iOffsetTex, false));
						}

						// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
						m_cfgDraw.SetAttribute(EAttribute::PartId
							, SAttribute(EAttribute::PartId, EStorageType::Integer, EDataType::UInt32, false, 1, TVertex::iOffsetPartId, false));

						m_cfgPick.SetAttribute(EAttribute::PartId
							, SAttribute(EAttribute::PartId, EStorageType::Integer, EDataType::UInt32, false, 1, TVertex::iOffsetPartId, false));
					}
					CLU_CATCH_RETHROW_ALL("Error initializing configurations")
				}

			public:
				CObjectData()
				{
					try
					{
						_InitConfigs();
					}
					CLU_CATCH_RETHROW_ALL("Error constructing object")
				}

				CObjectData(std::initializer_list<std::pair<EAttribute, bool>> ilEnable)
				{
					try
					{
						_InitConfigs();

						for (auto pairEl : ilEnable)
						{
							EnableAttribute(pairEl.first, pairEl.second);
						}
					}
					CLU_CATCH_RETHROW_ALL("Error initializing object")
				}

				bool IsValid() const
				{
					return m_bufVertex.IsValid();
				}

				unsigned BufferId() const
				{
					return m_bufVertex.Id();
				}

				size_t ElementCount() const
				{
					return m_bufVertex.Count();
				}

				void EnableAttribute(EAttribute eType, bool bEnable)
				{
					try
					{
						m_cfgDraw.EnableAttribute(eType, bEnable);

						if (eType == EAttribute::PartId)
						{
							m_cfgPick.EnableAttribute(EAttribute::PartId, bEnable);
							m_cfgPick.EnableAttribute(EAttribute::Color, bEnable);
						}
						else if (eType != EAttribute::Color)
						{
							m_cfgPick.EnableAttribute(eType, bEnable);
						}
					}
					CLU_CATCH_RETHROW_ALL("Error enabling attribute")
				}

				bool IsEnabled(EAttribute eType) const
				{
					try
					{
						return m_cfgDraw.IsEnabled(eType);
					}
					CLU_CATCH_RETHROW_ALL("Error enabling attribute")
				}

				void Create(size_t nElementCount, EBufferUsage eUsage)
				{
					try
					{
						m_bufVertex.Create(nElementCount, eUsage);
					}
					CLU_CATCH_RETHROW_ALL("Error creating vertex object")
				}

				void Create(size_t nElementCount, EBufferUsage eUsage, const TVertex* pData)
				{
					try
					{
						m_bufVertex.Create(nElementCount, eUsage, pData);
					}
					CLU_CATCH_RETHROW_ALL("Error creating vertex object")
				}

				void Destroy()
				{
					try
					{
						m_bufVertex.Destroy();
					}
					CLU_CATCH_RETHROW_ALL("Error destroying vertex object data")

				}


				void SetBindPars(bool bUseVertexAttribArrays, bool bUsePickCfg)
				{
					m_bUseVertexAttribArrays = bUseVertexAttribArrays;
					m_bUsePickCfg = bUsePickCfg;
				}

				void Bind()
				{
					try
					{
						m_bufVertex.Bind();

						if (m_bUsePickCfg)
						{
							m_cfgPick.Bind(m_bUseVertexAttribArrays);
						}
						else
						{
							m_cfgDraw.Bind(m_bUseVertexAttribArrays);
						}
						
					}
					CLU_CATCH_RETHROW_ALL("Error binding vertex object data")
				}

				void Unbind()
				{
					try
					{
						if (m_bUsePickCfg)
						{
							m_cfgPick.Unbind(m_bUseVertexAttribArrays);
						}
						else
						{
							m_cfgDraw.Unbind(m_bUseVertexAttribArrays);
						}

						m_bufVertex.Unbind();
					}
					CLU_CATCH_RETHROW_ALL("Error unbinding vertex object data")
				}
			};

		}
	}
}

