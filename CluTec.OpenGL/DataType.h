////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.OpenGL
// file:      DataType.h
//
// summary:   Declares the data type class
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
		enum class EDataType
		{
			Unknown = 0,
			// Data types. Same IDs as OpenGL.
			Int8 = 0x1400,
			UInt8 = 0x1401,
			Int16 = 0x1402,
			UInt16 = 0x1403,
			Int32 = 0x1404,
			UInt32 = 0x1405,
			Single = 0x1406,
			Double = 0x140A
		};
	}
}