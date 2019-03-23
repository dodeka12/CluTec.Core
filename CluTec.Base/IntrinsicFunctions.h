////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.Base
// file:      IntrinsicFunctions.h
//
// summary:   Declares the intrinsic functions class
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

#include <intrin.h>
#include <nmmintrin.h>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// namespace: Clu.Intrinsics
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace Clu
{
	namespace Intrinsics
	{
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// 	Calculate the number of bits set to 1 in the given value.
		/// </summary>
		///
		/// <param name="uValue"> The value. </param>
		///
		/// <returns> The total number of bits set to 1. </returns>
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		inline unsigned CountOneBits(const unsigned& uValue)
		{
			return _mm_popcnt_u32(uValue);
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \brief
		/// 	Product will overflow
		///
		/// \param	iA	Zero-based index of a.
		/// \param	iB	Zero-based index of the b.
		///
		/// \return True if it succeeds, false if it fails.
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		inline bool ProductWillOverflow(const __int32& iA, const __int32& iB)
		{
			unsigned __int32 uA = (unsigned __int32)(iA < 0 ? -iA : iA);
			unsigned __int32 uB = (unsigned __int32)(iB < 0 ? -iB : iB);

			unsigned long uMsbIdxA = 0, uMsbIdxB = 0;

			if (_BitScanReverse(&uMsbIdxA, uA) == 0 || _BitScanReverse(&uMsbIdxB, uB) == 0)
			{
				return false;
			}

			if (uMsbIdxA + uMsbIdxB >= 31)
			{
				return true;
			}

			return false;
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \brief
		/// 	Product will overflow
		///
		/// \param	iA	Zero-based index of a.
		/// \param	iB	Zero-based index of the b.
		///
		/// \return True if it succeeds, false if it fails.
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		inline bool ProductWillOverflow(const __int64& iA, const __int64& iB)
		{
#ifdef _M_AMD64__
			unsigned __int64 uA = (unsigned __int64)(iA < 0 ? -iA : iA);
			unsigned __int64 uB = (unsigned __int64)(iB < 0 ? -iB : iB);

			unsigned long uMsbIdxA = 0, uMsbIdxB = 0;

			if (_BitScanReverse64(&uMsbIdxA, uA) == 0 || _BitScanReverse64(&uMsbIdxB, uB) == 0)
			{
				return false;
			}

			if (uMsbIdxA + uMsbIdxB >= 63)
			{
				return true;
			}
#endif
			return false;
		}

		inline bool ProductWillOverflow(const float& fA, const float& iB)
		{
			// NOT IMPLEMENTED YET
			return false;
		}

		inline bool ProductWillOverflow(const double& fA, const double& iB)
		{
			// NOT IMPLEMENTED YET
			return false;
		}


		inline bool SumWillOverflow(const __int32& iA, const __int32& iB)
		{
#ifdef _M_AMD64__
			if ((iA < 0 && iB > 0) || (iA > 0 && iB < 0))
			{
				return false;
			}

			unsigned __int32 uA = (unsigned __int32)(iA < 0 ? -iA : iA);
			unsigned __int32 uB = (unsigned __int32)(iB < 0 ? -iB : iB);

			unsigned long uMsbIdxA = 0, uMsbIdxB = 0;

			if (_BitScanReverse64(&uMsbIdxA, uA) == 0 || _BitScanReverse64(&uMsbIdxB, uB) == 0)
			{
				return false;
			}

			if ((uMsbIdxA > uMsbIdxB ? uMsbIdxA : uMsbIdxB) >= 30)
			{
				return true;
			}
#endif
			return false;
		}


		inline bool SumWillOverflow(const __int64& iA, const __int64& iB)
		{
#ifdef _M_AMD64__
			if ((iA < 0 && iB > 0) || (iA > 0 && iB < 0))
			{
				return false;
			}

			unsigned __int64 uA = (unsigned __int64)(iA < 0 ? -iA : iA);
			unsigned __int64 uB = (unsigned __int64)(iB < 0 ? -iB : iB);

			unsigned long uMsbIdxA = 0, uMsbIdxB = 0;

			if (_BitScanReverse64(&uMsbIdxA, uA) == 0 || _BitScanReverse64(&uMsbIdxB, uB) == 0)
			{
				return false;
			}

			if ((uMsbIdxA > uMsbIdxB ? uMsbIdxA : uMsbIdxB) >= 62)
			{
				return true;
			}
#endif
			return false;
		}

		inline bool SumWillOverflow(const float& iA, const float& iB)
		{
			// NOT IMPLEMENTED
			return false;
		}

		inline bool SumWillOverflow(const double& iA, const double& iB)
		{
			// NOT IMPLEMENTED
			return false;
		}


	}
}
