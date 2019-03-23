////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.Types1.rtl
// file:      ExceptionTypes.cpp
//
// summary:   Implements the exception types class
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

#include "stdafx.h"
#include "ExceptionTypes.h"

namespace Clu
{
	namespace ExceptionType
	{

		// {3921E1CD-BB34-45AE-94E8-61072537BA07}
		const CGuid Standard::Guid = CGuid(0x3921e1cd, 0xbb34, 0x45ae, 0x94, 0xe8, 0x61, 0x7, 0x25, 0x37, 0xba, 0x7);
		const char* Standard::TypeName = "Exception";

		// {8F7094E3-7C55-4018-AF8E-0D7E4FBAFE26}
		const CGuid OutOfMemory::Guid = CGuid(0x8f7094e3, 0x7c55, 0x4018, 0xaf, 0x8e, 0xd, 0x7e, 0x4f, 0xba, 0xfe, 0x26);
		const char* OutOfMemory::TypeName = "Out of Memory";

		// {449A95DA-79F0-456D-8705-1491846B4DF4}
		const CGuid RuntimeError::Guid = CGuid(0x449a95da, 0x79f0, 0x456d, 0x87, 0x5, 0x14, 0x91, 0x84, 0x6b, 0x4d, 0xf4);
		const char* RuntimeError::TypeName = "Runtime Error";

		// {B869A778-B33F-4F4E-97B5-3A1373294C94}
		const CGuid FileNotFound::Guid = CGuid(0xb869a778, 0xb33f, 0x4f4e, 0x97, 0xb5, 0x3a, 0x13, 0x73, 0x29, 0x4c, 0x94);
		const char* FileNotFound::TypeName = "File Not Found";

	} // namespace Exception

} // namespace Clu


