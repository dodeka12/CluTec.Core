////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.OpenGL
// file:      Vertex.ObjectAttribConfig.h
//
// summary:   Declares the vertex. object attribute configuration class
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

#include <map>

#include "DataType.h"
#include "Vertex.Data.h"
#include "Vertex.Attribute.h"

namespace Clu
{
	namespace OpenGL
	{
		namespace Vertex
		{


			enum class EStorageType
			{
				Single = 0,
				Double,
				Integer,
			};

			struct SAttribute
			{
				EAttribute eType;
				EStorageType eStorageType;
				EDataType eDataType;

				bool bEnabled;
				bool bNormalize;
				int iElementCount;
				int iOffset;

				SAttribute()
				{
					eType = EAttribute::Position;
					eStorageType = EStorageType::Single;
					eDataType = EDataType::Single;
					bEnabled = false;
					bNormalize = false;
					iElementCount = 0;
					iOffset = 0;
				}

				SAttribute(EAttribute _eType, EStorageType _eStorageType, EDataType _eDataType
					, bool _bNormalize, int _iElementCount, int _iOffset, bool _bEnabled)
				{
					eType = _eType;
					eStorageType = _eStorageType;
					eDataType = _eDataType;
					bNormalize = _bNormalize;
					iElementCount = _iElementCount;
					iOffset = _iOffset;
					bEnabled = _bEnabled;
				}
			};

			class CObjectAttribConfig
			{
			public:
				using TAttributeMap = std::map<EAttribute, SAttribute>;
			
			protected:
				 TAttributeMap m_mapAttribute;
				 unsigned m_uElementSize;

			public:
				CObjectAttribConfig();

				void SetElementSize(unsigned uElSize);

				void SetAttribute(EAttribute eType, const SAttribute& xAttribute);
				const SAttribute& GetAttribute(EAttribute);

				void EnableAttribute(EAttribute eType, bool bEnable);
				bool IsEnabled(EAttribute eType) const;

				void Bind(bool bUseAttributeArrays);
				void Unbind(bool bUseAttributeArrays);
			};



		}
	}
}