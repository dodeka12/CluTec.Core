////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.Math
// file:      MapPixelValue.h
//
// summary:   Declares the map pixel value class
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

#include <type_traits>
#include "Conversion.h"

namespace Clu
{
	template<int iFlag>
	struct is_set;

	template<> struct is_set<0> : std::false_type {};
	template<> struct is_set<1> : std::true_type {};

	template<typename U, typename V>
	struct is_greater : is_set<(sizeof(U) > sizeof(V) ? 1 : 0)> {};


	template<typename TResult, typename TValue>
	__CUDA_HDI__ TResult MapPixelValue_Level3_IntToInt(TValue xValue
		, std::false_type /* result unsigned */
		, std::false_type /* value  unsigned */
		, std::false_type  /* result type not greater */)
	{
		static const unsigned uShift = unsigned(sizeof(TValue) - sizeof(TResult)) * 8;

		return (xValue >> uShift);
	}

	template<typename TResult, typename TValue>
	__CUDA_HDI__ TResult MapPixelValue_Level3_IntToInt(TValue xValue
		, std::true_type /* result signed */
		, std::true_type /* value  signed */
		, std::false_type  /* result type not greater */)
	{
		static const unsigned uShift = unsigned(sizeof(TValue) - sizeof(TResult)) * 8;

		return (xValue >> uShift);
	}

	template<typename TResult, typename TValue>
	__CUDA_HDI__ TResult MapPixelValue_Level3_IntToInt(TValue xValue
		, std::false_type /* result unsigned */
		, std::true_type  /* value  signed */
		, std::false_type  /* result type not greater */)
	{
		static const unsigned uShift = unsigned(sizeof(TValue) - sizeof(TResult)) * 8;
		using TUValue = typename std::make_unsigned<TValue>::type;

		TUValue xUValue = TUValue(xValue);
		xUValue += (Clu::NumericLimits<TUValue>::Max() >> 1) + 1;
		xUValue >>= uShift;

		return TResult(xUValue);
	}

	template<typename TResult, typename TValue>
	__CUDA_HDI__ TResult MapPixelValue_Level3_IntToInt(TValue xValue
		, std::true_type   /* result signed */
		, std::false_type  /* value  unsigned */
		, std::false_type  /* result type not greater */)
	{
		static const unsigned uShift = unsigned(sizeof(TValue) - sizeof(TResult)) * 8;

		TResult xResult = TResult(xValue >> uShift);
		xResult += Clu::NumericLimits<TResult>::Min();

		return xResult;
	}




	template<typename TResult, typename TValue>
	__CUDA_HDI__ TResult MapPixelValue_Level3_IntToInt(TValue xValue
		, std::false_type /* result unsigned */
		, std::false_type /* value  unsigned */
		, std::true_type  /* result type greater */)
	{
		static const unsigned uShift = unsigned(sizeof(TResult) - sizeof(TValue)) * 8;

		TResult xAdd = (1 << uShift) - 1;
		TResult xResult = TResult(xValue) << uShift;
		if (xResult != TResult(0))
		{
			xResult |= xAdd;
		}

		return xResult;
	}

	template<typename TResult, typename TValue>
	__CUDA_HDI__ TResult MapPixelValue_Level3_IntToInt(TValue xValue
		, std::true_type /* result signed */
		, std::true_type /* value  signed */
		, std::true_type  /* result type greater */)
	{
		static const unsigned uShift = unsigned(sizeof(TResult) - sizeof(TValue)) * 8;
		if (xValue > 0)
		{
			return (TResult(xValue + 1) * (1 << uShift)) - 1;
		}
		else
		{
			return (TResult(xValue) * (1 << uShift));
		}
	}

	template<typename TResult, typename TValue>
	__CUDA_HDI__ TResult MapPixelValue_Level3_IntToInt(TValue xValue
		, std::false_type /* result unsigned */
		, std::true_type  /* value  signed */
		, std::true_type  /* result type greater */)
	{
		static const unsigned uShift = unsigned(sizeof(TResult) - sizeof(TValue)) * 8;
		using TUValue = typename std::make_unsigned<TValue>::type;

		TResult xAdd = (1 << uShift) - 1;
		TUValue xUValue = TUValue(xValue);
		xUValue += (Clu::NumericLimits<TUValue>::Max() >> 1) + 1;

		TResult xResult = TResult(xUValue) << uShift;
		if (xResult != TResult(0))
		{
			xResult |= xAdd;
		}

		return xResult;
	}

	template<typename TResult, typename TValue>
	__CUDA_HDI__ TResult MapPixelValue_Level3_IntToInt(TValue xValue
		, std::true_type   /* result signed */
		, std::false_type  /* value  unsigned */
		, std::true_type  /* result type greater */)
	{
		static const unsigned uShift = unsigned(sizeof(TResult) - sizeof(TValue)) * 8;
		using TUResult = typename std::make_unsigned<TResult>::type;

		TUResult xAdd = (1 << uShift) - 1;
		TUResult xUResult = TUResult(xValue) << uShift;

		if (xUResult != TUResult(0))
		{
			xUResult |= xAdd;
		}

		xUResult += Clu::NumericLimits<TResult>::Min();

		return TResult(xUResult);
	}




	template<typename TResult, typename TValue>
	__CUDA_HDI__ TResult MapPixelValue_Level2(TValue xValue
		, std::true_type /* result integral */
		, std::true_type /* value  integral */)
	{
		return MapPixelValue_Level3_IntToInt<TResult>(xValue
			, std::is_signed<TResult>()
			, std::is_signed<TValue>()
			, is_greater<TResult, TValue>());
	}



	template<typename TResult, typename TValue>
	__CUDA_HDI__ TResult MapPixelValue_Level3_ToFloat(TValue xValue)
	{
		return ToNormFloat<TResult>(xValue);
	}

	template<typename TResult, typename TValue>
	__CUDA_HDI__ TResult MapPixelValue_Level3_FromFloat(TValue xValue)
	{
		return NormFloatTo<TResult>(xValue);
	}

	template<typename TResult, typename TValue>
	__CUDA_HDI__ TResult MapPixelValue_Level3_FloatToFloat(TValue xValue)
	{
		return TResult(xValue);
	}


	template<typename TResult, typename TValue>
	__CUDA_HDI__ TResult MapPixelValue_Level2(TValue xValue
		, std::false_type /* result float */
		, std::true_type /* value  integral */)
	{
		return MapPixelValue_Level3_ToFloat<TResult>(xValue);
	}

	template<typename TResult, typename TValue>
	__CUDA_HDI__ TResult MapPixelValue_Level2(TValue xValue
		, std::true_type /* result integral */
		, std::false_type /* value float */)
	{
		return MapPixelValue_Level3_FromFloat<TResult>(xValue);
	}

	template<typename TResult, typename TValue>
	__CUDA_HDI__ TResult MapPixelValue_Level2(TValue xValue
		, std::false_type /* result float */
		, std::false_type /* value  float */)
	{
		return MapPixelValue_Level3_FloatToFloat<TResult>(xValue);
	}


	template<typename TResult, typename TValue>
	__CUDA_HDI__ TResult MapPixelValue_Level1(TValue xValue, std::false_type /* NOT same type */)
	{
		return MapPixelValue_Level2<TResult>(xValue
			, std::is_integral<TResult>(), std::is_integral<TValue>() );
	}

	template<typename TResult, typename TValue>
	__CUDA_HDI__ TResult MapPixelValue_Level1(TValue xValue, std::true_type /* same type */)
	{
		return xValue;
	}

	template<typename TResult, typename TValue>
	__CUDA_HDI__ TResult MapPixelValue(TValue xValue)
	{
		return MapPixelValue_Level1<TResult>(xValue, std::is_same<TResult, TValue>());
	}

}