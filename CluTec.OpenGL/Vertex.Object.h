////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.OpenGL
// file:      Vertex.Object.h
//
// summary:   Declares the vertex. object class
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

#include "CluTec.Base/Exception.h"

#include "Vertex.Data.h"
#include "Vertex.ObjectData.h"
#include "Vertex.ObjectDrawConfig.h"

namespace Clu
{
	namespace OpenGL
	{
		namespace Vertex
		{
			template<EType t_eType>
			class CObject
			{
			public:
				using TObjectData = CObjectData<t_eType>;
				using TDrawConfig = CObjectDrawConfig;

				using TVertex = typename TObjectData::TVertex;

			public:
				static const EType Type = t_eType;

			protected:
				TObjectData m_objData;
				CObjectDrawConfig m_objDrawCfg;

			public:
				CObject()
				{}

				bool IsValid()
				{
					return m_objData.IsValid() && m_objDrawCfg.IsValid();
				}

				const TObjectData& Data() const
				{
					return m_objData;
				}

				const CObjectDrawConfig& DrawConfig() const
				{
					return m_objDrawCfg;
				}

				void Create(EDrawMode eMode, size_t nElementCount, unsigned uInstanceCount, EBufferUsage eUsage)
				{
					try
					{
						m_objData.Create(nElementCount, eUsage);
						m_objDrawCfg.Create(eMode, uInstanceCount, nElementCount);
					}
					CLU_CATCH_RETHROW_ALL("Error creating vertex object")
				}

				void Create(EDrawMode eMode, size_t nElementCount, unsigned uInstanceCount, EBufferUsage eUsage, const TVertex* pData)
				{
					try
					{
						m_objData.Create(nElementCount, eUsage, pData);
						m_objDrawCfg.Create(eMode, uInstanceCount, nElementCount);
					}
					CLU_CATCH_RETHROW_ALL("Error creating vertex object")
				}

				void Create(EDrawMode eMode, size_t nElementCount, unsigned uInstanceCount, EBufferUsage eUsage
					, const TVertex* pData, const std::vector<unsigned>& vecIndexList)
				{
					try
					{
						m_objData.Create(nElementCount, eUsage, pData);
						m_objDrawCfg.Create(eMode, uInstanceCount, vecIndexList);
					}
					CLU_CATCH_RETHROW_ALL("Error creating vertex object")
				}

				void Destroy()
				{
					try
					{
						m_objData.Destroy();
						m_objDrawCfg.Destroy();
					}
					CLU_CATCH_RETHROW_ALL("Error destroying vertex object")
				}

				void UdpateData(const TVertex* pData)
				{
					try
					{
						m_objData.Update(pData);
					}
					CLU_CATCH_RETHROW_ALL("Error updating vertex object data")
				}

				void SetDrawConfig(EDrawMode eMode, unsigned uInstanceCount, const std::vector<unsigned>& vecIndexList)
				{
					try
					{
						m_objDrawCfg.Create(eMode, uInstanceCount, vecIndexList);
					}
					CLU_CATCH_RETHROW_ALL("Error setting draw configuration")
				}

				void SetDrawConfig(EDrawMode eMode, unsigned uInstanceCount, size_t nElementCount)
				{
					try
					{
						m_objDrawCfg.Create(eMode, uInstanceCount, nElementCount);
					}
					CLU_CATCH_RETHROW_ALL("Error setting draw configuration")
				}

				template<typename... TPars>
				void SetDataBindPars(TPars&&... xPars)
				{
					m_objData.SetBindPars(xPars...);
				}

				void Draw()
				{
					try
					{
						if (!IsValid())
						{
							throw CLU_EXCEPTION("Invalid vertex object");
						}
						
						m_objData.Bind();
						m_objDrawCfg.Draw();
						m_objData.Unbind();
					}
					CLU_CATCH_RETHROW_ALL("Error darwing vertex object draw configuration")
				}

			};


		}
	}
}

