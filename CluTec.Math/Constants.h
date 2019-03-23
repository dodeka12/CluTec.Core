////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.Math
// file:      Constants.h
//
// summary:   Declares the constants class
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
	namespace Math
	{
		template<typename TValue>
		struct Constants
		{
			__CUDA_HDI__ static TValue Pi()
			{
				return  TValue(3.14159265358979323846264338327950288419716939937510582);
			}

			__CUDA_HDI__ static TValue RadPerDeg()
			{
				return Pi() / TValue(180);
			}

			__CUDA_HDI__ static TValue DegPerRad()
			{
				return TValue(180) / Pi();
			}

			__CUDA_HDI__ static TValue PiHalf()
			{
				return TValue(0.5) * Pi();
			}

			__CUDA_HDI__ static TValue Tau()
			{
				return TValue(2) * Pi();
			}

			__CUDA_HDI__ static TValue Sqrt2()
			{
				return TValue(1.4142135623730950488016887242097);
			}

			__CUDA_HDI__ static TValue InvSqrt2()
			{
				return TValue(0.70710678118654752440084436210485);
			}
		};

	}

}