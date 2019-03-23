////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.OpenGL
// file:      Vertex.MeshObject.h
//
// summary:   Declares the vertex. mesh object class
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

#include "CluTec.Types1/Guid.h"

#include "Vertex.Object.h"


namespace Clu
{
	namespace OpenGL
	{
		namespace Vertex
		{
			template<EType t_eType>
			class CMeshObject : public CObject<t_eType>
			{
			public:
				using TBase = CObject<t_eType>;

			public:
				static const CGuid TypeId;

			protected:
				unsigned m_uVertexCountX, m_uVertexCountY;

			public:
				CMeshObject()
				{
					m_uVertexCountX = 0;
					m_uVertexCountY = 0;
				}

				unsigned VertexCountX()
				{
					return m_uVertexCountX;
				}

				unsigned VertexCountY()
				{
					return m_uVertexCountY;
				}


				void GetVertexCount(unsigned& uCountX, unsigned& uCountY)
				{
					uCountX = m_uVertexCountX;
					uCountY = m_uVertexCountY;
				}

				void CreateTriangleStrip(float fSegSize, unsigned uSegCntX, unsigned uSegCntY, unsigned uIdxX, unsigned uIdxY, unsigned uIdxZ
					, EBufferUsage eUsage)
				{
					m_uVertexCountX = uSegCntX + 1;
					m_uVertexCountY = uSegCntY + 1;

					unsigned uVexCnt = m_uVertexCountX * m_uVertexCountY;

					std::vector<TVertex> vecData;
					vecData.resize(uVexCnt);

					unsigned uVexIdx = 0;

					float fSizeX = fSegSize * float(uSegCntX);
					float fSizeY = fSegSize * float(uSegCntY);

					float fHalfSizeX = fSizeX / 2.0f;
					float fHalfSizeY = fSizeY / 2.0f;

					float fY = -fHalfSizeY;
					for (unsigned uY = 0; uY <= uSegCntY; ++uY, fY += fSegSize)
					{
						float fX = -fHalfSizeX;
						for (unsigned uX = 0; uX <= uSegCntX; ++uX, fX += fSegSize, ++uVexIdx)
						{
							TVertex& xVex = vecData[uVexIdx];
							xVex.Position(uIdxX) = fX;
							xVex.Position(uIdxY) = fY;
							xVex.Position(uIdxZ) = 0;

							xVex.Texture(uIdxX) = float(uX) / float(uSegCntX);
							xVex.Texture(uIdxY) = float(uY) / float(uSegCntY);
							xVex.Texture(uIdxZ) = 0.0f;

							xVex.Normal(uIdxX) = 0.0f;
							xVex.Normal(uIdxY) = 0.0f;
							xVex.Normal(uIdxZ) = 1.0f;
						}
					}

					unsigned uIdxListLen = uSegCntY * 2 * (uSegCntX + 1) + (uSegCntY - 1);
					std::vector<unsigned> vecIndex(uIdxListLen);
					int iRowLen = uSegCntX + 1;

					unsigned uPos;
					unsigned uX, uY;
					auto itIndex = vecIndex.begin();

					uPos = 0;
					for (uY = 0; uY < uSegCntY; uY++)
					{
						for (uX = 0; uX < uSegCntX + 1; uX++, uPos++)
						{
							*(itIndex++) = uPos;
							*(itIndex++) = uPos + m_uVertexCountX;
						}

						if (++uY >= m_uVertexCountY - 1)
						{
							break;
						}

						uPos += m_uVertexCountX - 1;
						*(itIndex++) = uPos;

						for (uX = m_uVertexCountX; uX > 0; uX--, uPos--)
						{
							*(itIndex++) = uPos;
							*(itIndex++) = uPos + m_uVertexCountX;
						}

						if (uY + 1 >= m_uVertexCountY - 1)
						{
							break;
						}

						uPos += m_uVertexCountX + 1;
						*(itIndex++) = uPos;
					}


					m_objData.EnableAttribute(EAttribute::Position, true);
					m_objData.EnableAttribute(EAttribute::Tex0, true);
					m_objData.EnableAttribute(EAttribute::Normal, true);

					Create(EDrawMode::TriangleStrip, uVexCnt, 1, eUsage, vecData.data(), vecIndex);

				}

			};

			// {E52F3F68-B8E2-46C2-ADE3-98A3B8547B42}
			template<> const Clu::CGuid CMeshObject<EType::Standard>::TypeId = CGuid(0xe52f3f68, 0xb8e2, 0x46c2, 0xad, 0xe3, 0x98, 0xa3, 0xb8, 0x54, 0x7b, 0x42);
		}
	}
}
