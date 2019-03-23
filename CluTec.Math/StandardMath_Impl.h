////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.Math
// file:      StandardMath_Impl.h
//
// summary:   Declares the standard mathematics implementation class
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
#include "StandardMath.h"

namespace Clu
{
	template<>
	__CUDA_HDI__ float Modulus(float tVal, float tMod)
	{
		return fmodf(tVal, tMod);
	}

	template<>
	__CUDA_HDI__ double Modulus(double tVal, double tMod)
	{
		return fmod(tVal, tMod);
	}


}