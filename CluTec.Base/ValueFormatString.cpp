////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.Base
// file:      ValueFormatString.cpp
//
// summary:   Implements the value format string class
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

#include <stdint.h>
#include <string>
#include "ValueFormatString.h"

namespace Clu
{
	template<> std::string ValueFormatString<int>()
	{
		return std::string("%d");
	}

	template<> std::string ValueFormatString<unsigned int>()
	{
		return std::string("%u");
	}

	template<> std::string ValueFormatString<float>()
	{
		return std::string("%g");
	}

	template<> std::string ValueFormatString<double>()
	{
		return std::string("%g");
	}

	template<> std::string ValueFormatString<int64_t>()
	{
		return std::string("%I64d");
	}

	template<> std::string ValueFormatString<uint64_t>()
	{
		return std::string("%I64u");
	}
}	// namespace Clu
