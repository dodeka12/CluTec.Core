////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.OpenGL
// file:      Vertex.DrawMode.h
//
// summary:   Declares the vertex. draw mode class
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

namespace Clu
{
	namespace OpenGL
	{
		namespace Vertex
		{
			enum class EDrawMode
			{
				Points = 0x0000,
				Lines = 0x0001,
				LineLoop = 0x0002,
				LineStrip = 0x0003,
				Triangles = 0x0004,
				TriangleStrip = 0x0005,
				TriangleFan = 0x0006,
				Quads = 0x0007,
				QuadStrip = 0x0008,
				Polygon = 0x0009,
				LineAdjacency = 0x000A,
				LineStripAdjacency = 0x000B,
				TrianglesAdjacency = 0x000C,
				TriangleStripAdjacency = 0x000D,
			};
		}
	}
}