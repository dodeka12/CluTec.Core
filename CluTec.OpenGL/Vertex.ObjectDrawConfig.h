////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.OpenGL
// file:      Vertex.ObjectDrawConfig.h
//
// summary:   Declares the vertex. object draw configuration class
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

#include "Buffer.h"
#include "Vertex.DrawMode.h"

namespace Clu
{
	namespace OpenGL
	{
		namespace Vertex
		{

			class CObjectDrawConfig
			{
			public:
				using TIndexBuffer = CBuffer<EBufferType::Element, unsigned>;

			protected:
				EDrawMode m_eMode;
				unsigned m_uInstanceCount;
				size_t m_nElementCount;

				TIndexBuffer m_bufIndex;

			public:
				CObjectDrawConfig();

				bool IsValid() const;
				unsigned BufferId() const;
				size_t ElementCount() const;
				unsigned InstanceCount() const;
				EDrawMode Mode() const;

				void Create(EDrawMode eMode, unsigned uInstanceCount, size_t nElementCount);
				void Create(EDrawMode eMode, unsigned uInstanceCount, const std::vector<unsigned>& vecIndex);
				void Destroy();

				void Bind();
				void Unbind();

				void Draw();
			};
		}
	}
}
