////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.OpenGL
// file:      Vertex.Data.h
//
// summary:   Declares the vertex. data class
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

#include "CluTec.Types1/Defines.h"

namespace Clu
{
	namespace OpenGL
	{
		namespace Vertex
		{

			enum class EType
			{
				Standard = 0,
			};


			template<EType t_eType>
			struct _SData
			{
			};

			template<>
			struct _SData<EType::Standard>
			{
			public:
				static const EType Type = EType::Standard;

				// Vertex array offsets for different data types.
				// Can be used in calls to glVertexPointer(), glColorPointer() etc.
				static const int iOffsetPos = 0;
				static const int iOffsetTex = 12;
				static const int iOffsetNorm = 24;
				static const int iOffsetCol = 36;
				static const int iOffsetFog = 52;
				static const int iOffsetPartId = 56;
				static const int iOffsetEdge = 60;

			public:
				/// <summary> Position coordinate vector. </summary>
				float pfPos[3];
				/// <summary> Texture coordinate vector. </summary>
				float pfTex[3];
				/// <summary> Normal coordinate vector. </summary>
				float pfNorm[3];
				/// <summary> RGBA color value. </summary>
				float pfCol[4];
				/// <summary> Fog z-component. </summary>
				float fFogZ;
				/// <summary> Part ID for picking of object parts. </summary>
				unsigned uPartId;
				/// <summary> Edge flag. </summary>
				char bEdge;
				/// <summary> Padding (reserved for future use). </summary>
				char pbPad[3];

			public:
				__CUDA_HDI__ float& Position(unsigned uIdx)
				{
					return pfPos[uIdx];
				}

				__CUDA_HDI__ float& Texture(unsigned uIdx)
				{
					return pfTex[uIdx];
				}

				__CUDA_HDI__ float& Normal(unsigned uIdx)
				{
					return pfNorm[uIdx];
				}

				__CUDA_HDI__ float& Color(unsigned uIdx)
				{
					return pfCol[uIdx];
				}
			};

		}

	}
}