////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.Math
// file:      StandardMath.h
//
// summary:   Declares the standard mathematics class
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

#include <stdlib.h>
#include <cmath>

#include "CluTec.Base/Defines.h"

namespace Clu
{

#if defined(__NVCC__)
	template<typename TValue>
	__CUDA_HDI__ TValue Min(TValue tA, TValue tB)
	{
		return min(tA, tB);
	}
#else
	template<typename TValue>
	TValue Min(TValue tA, TValue tB)
	{
		return (tA < tB ? tA : tB);
	}
#endif

#if defined(__NVCC__)
	template<typename TValue>
	__CUDA_HDI__ TValue Max(TValue tA, TValue tB)
	{
		return max(tA, tB);
	}
#else
	template<typename TValue>
	TValue Max(TValue tA, TValue tB)
	{
		return (tA > tB ? tA : tB);
	}
#endif


	/**
	        \brief Round to nearest integer.
	**/
	template<class T>
	__CUDA_HDI__ int ToInt(T fVal)
	{
		static_assert(std::is_floating_point<T>::value, "Parameter is not floating point type.");

		return int(::floor(fVal));
	}

	template<class T>
	__CUDA_HDI__ int ToIntSup(T fVal)
	{
		static_assert(std::is_floating_point<T>::value, "Parameter is not floating point type.");

		return int(::ceil(fVal));
	}


	template<class T>
	__CUDA_HDI__ int ToIntRound(T fVal)
	{
		static_assert(std::is_floating_point<T>::value, "Parameter is not floating point type.");

		return int(::floor(fVal + T(0.5)));
	}


	/**
	        \brief Round to given number of decimal places.
	**/
	template<class T>
	__CUDA_HDI__ T Round(T fVal, int iDec)
	{
		static_assert(std::is_floating_point<T>::value, "Parameter is not floating point type.");

		T fFac = T(::pow(T(10), T(iDec)));
		return ::floor(fVal * fFac + T(0.5)) / fFac;
	}

	/**
	        \brief Clamp value tVal to range [tMin, tMax].
	**/
	template<class T>
	__CUDA_HDI__ T Clamp(T tVal, T tMin, T tMax)
	{
		return Max(Min(tMax, tVal), tMin);
	}

	/**
	        \brief Modulus.
	**/
	template<class T>
	__CUDA_HDI__ T Modulus(T tVal, T tMod)
	{
		return tVal % tMod;
	}

	template<>
	__CUDA_HDI__ float Modulus(float tVal, float tMod);

	template<>
	__CUDA_HDI__ double Modulus(double tVal, double tMod);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \brief
	/// 	Positive modulus. Always returns a positive value.
	///
	/// \tparam	T Generic type parameter.
	/// \param	tVal	The value.
	/// \param	tMod	The modulo value.
	///
	/// \return The positive modulus.
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template<class T>
	__CUDA_HDI__ T PosMod(T tVal, T tMod)
	{
		tMod  = (tMod < T(0) ? -tMod : tMod);
		tVal %= tMod;
		if (tVal < T(0))
		{
			tVal += tMod;
		}

		return tVal;
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \brief
	/// 	Half-space modulus. For a modulus N it maps values to the range [floor(N/2)-N+1, floor(N/2)].
	/// 	For example, -4 hmod 7 = 2 and 4 hmod 7 = -2.
	///
	/// \tparam	T Generic type parameter.
	/// \param	tVal	The value.
	/// \param	tMod	The modulo value.
	///
	/// \return The modulus.
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template<class T>
	__CUDA_HDI__ T HalfMod(T tVal, T tMod)
	{
		tMod = (tMod < T(0) ? -tMod : tMod);
		//tVal -= tMod * (tVal / tMod);
		tVal %= tMod;

		if (tVal < T(0))
		{
			tVal += tMod;
		}

		if (tVal > tMod / T(2))
		{
			tVal -= tMod;
		}

		return tVal;
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \brief
	/// 	Greatest Common Divider.
	///
	/// \tparam	T Generic type parameter.
	/// \param	tValA	The value a.
	/// \param	tValB	The value b.
	///
	/// \return The GCD of tValA and tValB.
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template<class T>
	T Gcd(T tValA, T tValB)
	{
		unsigned uShiftCnt;

		tValA = abs(tValA);
		tValB = abs(tValB);

		/* GCD(0,v) == v; GCD(u,0) == u, GCD(0,0) == 0 */
		if (tValA == 0) { return tValB; }
		if (tValB == 0) { return tValA; }

		/* Let shift := lg K, where K is the greatest power of 2
		dividing both tValA and tValB. */
		for (uShiftCnt = 0; ((tValA | tValB) & 1) == 0; ++uShiftCnt)
		{
			tValA >>= 1;
			tValB >>= 1;
		}

		while ((tValA & 1) == 0)
		{
			tValA >>= 1;
		}

		/* From here on, tValA is always odd. */
		do
		{
			/* remove all factors of 2 in tValB -- they are not common */
			/*   note: tValB is not zero, so while will terminate */
			while ((tValB & 1) == 0)	/* Loop X */
			{
				tValB >>= 1;
			}

			/* Now tValA and tValB are both odd. Swap if necessary so tValA <= tValB,
			then set tValB = tValB - tValA (which is even). For bignums, the
			swapping is just pointer movement, and the subtraction
			can be done in-place. */
			if (tValA > tValB)
			{
				T t = tValB;
				tValB = tValA;
				tValA = t;
			}	// Swap tValA and tValB.

			tValB = tValB - tValA;				// Here tValB >= tValA.
		}
		while (tValB != 0);

		/* restore common factors of 2 */
		return tValA << uShiftCnt;
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \brief
	/// 	Extent Euclidean Algorithm. For given values A and B it computes the values X, Y, such that A X + B Y = gcd(A,B).
	/// 	If the gcd(A,B) == 1, then A and B are co-prime.
	///
	/// \tparam	T Generic type parameter.
	/// \param [out]	tX	The value X.
	/// \param [out]	tY	The value Y.
	/// \param [out]	tR	The GCD.
	/// \param	tValA	  	The value A. This has to be greater than B.
	/// \param	tValB	  	The value B.
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template<class T>
	bool ExtEucAlgo(T& tX, T& tY, T& tR, T tValA, T tValB)
	{
		T tX0, tX1, tX2;
		T tY0, tY1, tY2;
		T tR0, tR1, tR2;

		if (tValA <= tValB)
		{
			return false;
		}

		if (tValA % tValB == 0)
		{
			return false;
		}

		tX0 = T(0);
		tX1 = T(1);

		tY0 = T(-1);
		tY1 = tValA / tValB;

		tR0 = tValA;
		tR1 = tValB;

		while (true)
		{
			tR2 = tX1 * tValA - tY1 * tValB;

			if ((tR2 >= T(-1)) && (tR2 <= T(1)))
			{
				break;
			}

			T tQ = tR1 / tR2;
			tR0 = tR1;
			tR1 = tR2;

			tX2 = tX0 - tQ * tX1;
			tY2 = tY0 - tQ * tY1;

			tX0 = tX1;
			tX1 = tX2;

			tY0 = tY1;
			tY1 = tY2;
		}

		if (tR2 == 0)
		{
			tX = tX0;
			tY = -tY0;
			tR = tR1;
		}
		else
		{
			tX = tX1;
			tY = -tY1;
			tR = tR2;
		}

		return true;
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \brief
	/// 	Calculates the inverse of a value A with respect to modulus N. That is, if An := ModInv(A, N), then (A An) mod N = 1.
	///
	/// \tparam	T Generic type parameter.
	/// \param	tValA	The value A.
	/// \param	tMod 	The modulus.
	///
	/// \return The value An such that (A An) mod tMod = 1.
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template<class T, typename FuncMod >
	T ModInv(T tValA, T tMod, FuncMod funcMod)
	{
		tValA = funcMod(tValA, tMod);

		if (tValA == T(0))
		{
			return T(0);
		}
		else if (tValA == T(1))
		{
			return T(1);
		}
		else if (tValA == T(-1))
		{
			return T(-1);
		}

		T tX, tY, tR;
		if (!ExtEucAlgo(tX, tY, tR, tMod, tValA))
		{
			return T(0);
		}

		if ((tR != T(1)) && (tR != T(-1)))
		{
			return T(0);
		}
		else
		{
			if (tR < T(0))
			{
				tY = -tY;
			}

			return funcMod(tY, tMod);
		}
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \brief
	/// 	Positive modulus inverse
	///
	/// \param	T Generic type parameter.
	/// \param	tValA	The value A.
	/// \param	tMod 	The modulus value N.
	///
	/// \return The inverse of A w.r.t. modulus N using the positive modulus.
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template<class T >
	T PosModInv(T tValA, T tMod)
	{
		return ModInv<T>(tValA, tMod, [](T tVal, T tMod) -> T
				{
					return PosMod(tVal, tMod);
				});
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \brief
	/// 	Half-space modulus inverse
	///
	/// \param	T Generic type parameter.
	/// \param	tValA	The value A.
	/// \param	tMod 	The modulus value N.
	///
	/// \return The inverse of A w.r.t. modulus N using the half-space modulus.
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template<class T >
	T HalfModInv(T tValA, T tMod)
	{
		return ModInv<T>(tValA, tMod, [](T tVal, T tMod) -> T
				{
					return HalfMod(tVal, tMod);
				});
	}


}	// namespace Clu

// Include the implementation of some template specializations only if a CUDA file is compiled.
#if defined(__CUDACC__)
#include "StandardMath_Impl.h"
#endif