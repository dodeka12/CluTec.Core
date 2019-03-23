////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.Math
// file:      ValuePrecision_Impl.h
//
// summary:   Declares the value precision implementation class
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

#include "CluTec.Base/Defines.h"

#include "ValuePrecision.h"
#include <stdint.h>

namespace Clu
{
	template<> __CUDA_HDI__ float CValuePrecision<float>::DefaultPrecision()
	{
		return 1e-6f;
	}

	template<> __CUDA_HDI__ double CValuePrecision<double>::DefaultPrecision()
	{
		return 1e-12;
	}

	template<> __CUDA_HDI__ int CValuePrecision<int>::DefaultPrecision()
	{
		return 0;
	}

	template<> __CUDA_HDI__ uint32_t CValuePrecision<uint32_t>::DefaultPrecision()
	{
		return 0U;
	}

	template<> __CUDA_HDI__ uint64_t CValuePrecision<uint64_t>::DefaultPrecision()
	{
		return 0;
	}

	template<> __CUDA_HDI__ int64_t CValuePrecision<int64_t>::DefaultPrecision()
	{
		return 0;
	}
}	// namespace Clu
