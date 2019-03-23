////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.Math
// file:      Conversion.h
//
// summary:   Declares the conversion class
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
#include <cstdint>
#include <cfloat>

#include "CluTec.Types1/Defines.h"
#include "Constants.h"
#include "StandardMath.h"

namespace Clu
{

	// ////////////////////////////////////////////////////////////////////////////////////////////////
	// ////////////////////////////////////////////////////////////////////////////////////////////////
	// ////////////////////////////////////////////////////////////////////////////////////////////////

#pragma region Numeric Limits

#define STATIC_FUNC(theName, theValue) \
	__CUDA_HDI__ static T theName() { return T(theValue); }

#define STATIC_CUDA_FUNC(theName, theValue) \
	__CUDA_DI__ static T theName() { return T(theValue); }


	template<typename T>
	class NumericLimits
	{
	public:
		static const bool IsSigned = false;
		STATIC_FUNC(Min, 0)
		STATIC_FUNC(Max, 0)
		STATIC_FUNC(Infinity, 0)
	};



	template<>
	class NumericLimits<int8_t>
	{
	public:
		using T = int8_t;

		static const bool IsSigned = true;
		STATIC_FUNC(Min, INT8_MIN)
		STATIC_FUNC(Max, INT8_MAX)
		STATIC_FUNC(Infinity, 0)
	};

	template<>
	class NumericLimits<char>
	{
	public:
		using T = char;

		static const bool IsSigned = true;
		STATIC_FUNC(Min, CHAR_MIN)
		STATIC_FUNC(Max, CHAR_MAX)
		STATIC_FUNC(Infinity, 0)
	};

	template<>
	class NumericLimits<int16_t>
	{
	public:
		using T = int16_t;

		static const bool IsSigned = true;
		STATIC_FUNC(Min, INT16_MIN)
		STATIC_FUNC(Max, INT16_MAX)
		STATIC_FUNC(Infinity, 0)
	};


	template<>
	class NumericLimits<int32_t>
	{
	public:
		using T = int32_t;

		static const bool IsSigned = true;
		STATIC_FUNC(Min, INT32_MIN)
		STATIC_FUNC(Max, INT32_MAX)
		STATIC_FUNC(Infinity, 0)
	};

	template<>
	class NumericLimits<int64_t>
	{
	public:
		using T = int64_t;

		static const bool IsSigned = true;
		STATIC_FUNC(Min, INT64_MIN)
		STATIC_FUNC(Max, INT64_MAX)
		STATIC_FUNC(Infinity, 0)
	};


	template<>
	class NumericLimits<uint8_t>
	{
	public:
		using T = uint8_t;

		static const bool IsSigned = false;
		STATIC_FUNC(Min, 0)
		STATIC_FUNC(Max, UINT8_MAX)
		STATIC_FUNC(Infinity, 0)
	};

	template<>
	class NumericLimits<uint16_t>
	{
	public:
		using T = uint16_t;

		static const bool IsSigned = false;
		STATIC_FUNC(Min, 0)
		STATIC_FUNC(Max, UINT16_MAX)
		STATIC_FUNC(Infinity, 0)
	};

	template<>
	class NumericLimits<uint32_t>
	{
	public:
		using T = uint32_t;

		static const bool IsSigned = false;
		STATIC_FUNC(Min, 0)
		STATIC_FUNC(Max, UINT32_MAX)
		STATIC_FUNC(Infinity, 0)
	};


	template<>
	class NumericLimits<uint64_t>
	{
	public:
		using T = uint64_t;

		static const bool IsSigned = false;
		STATIC_FUNC(Min, 0)
		STATIC_FUNC(Max, UINT64_MAX)
		STATIC_FUNC(Infinity, 0)
	};

	template<>
	class NumericLimits<float>
	{
	public:
		using T = float;

		static const bool IsSigned = true;
		STATIC_FUNC(Min, FLT_MIN)
		STATIC_FUNC(Max, FLT_MAX)
#if defined(__CUDACC__)
		STATIC_CUDA_FUNC(Infinity, __int_as_float(0x7f800000))
#else
		STATIC_FUNC(Infinity, __builtin_huge_valf())
#endif
	};

	template<>
	class NumericLimits<double>
	{
	public:
		using T = double;

		static const bool IsSigned = true;
		STATIC_FUNC(Min, DBL_MIN)
		STATIC_FUNC(Max, DBL_MAX)
#if defined(__CUDACC__)
		STATIC_CUDA_FUNC(Infinity, __longlong_as_double(0x7ff0000000000000ULL))
#else
		STATIC_FUNC(Infinity, __builtin_huge_val())
#endif
	};

#undef STATIC_FUNC

#pragma endregion


	// ////////////////////////////////////////////////////////////////////////////////////////////////
	// ////////////////////////////////////////////////////////////////////////////////////////////////
	// ////////////////////////////////////////////////////////////////////////////////////////////////

#pragma region To Normalized Float
	template<typename TResult, typename TValue>
	__CUDA_HDI__ TResult ToNormFloat_impl(TValue xValue, std::true_type, std::true_type)
	{
		static_assert(std::numeric_limits<TResult>::is_integer == false,
			"Result type has to be a floating point type");

		using TLim = Clu::NumericLimits<TValue>;

		return TResult(2) * ((TResult(xValue) - TResult(TLim::Min())) / (TResult(TLim::Max()) - TResult(TLim::Min())) - TResult(0.5));
	}

	template<typename TResult, typename TValue>
	__CUDA_HDI__ TResult ToNormFloat_impl(TValue xValue, std::true_type, std::false_type)
	{
		static_assert(std::numeric_limits<TResult>::is_integer == false,
			"Result type has to be a floating point type");

		using TLim = Clu::NumericLimits<TValue>;

		return TResult(xValue) / TResult(TLim::Max());
	}

	template<typename TResult, typename TValue>
	__CUDA_HDI__ TResult ToNormFloat_impl(TValue xValue, std::false_type, std::true_type)
	{
		static_assert(std::numeric_limits<TResult>::is_integer == false,
			"Result type has to be a floating point type");

		return TResult(xValue);
	}

	template<typename TResult, typename TValue>
	__CUDA_HDI__ TResult ToNormFloat(TValue xValue)
	{
		return ToNormFloat_impl<TResult>(xValue, std::is_integral<TValue>(), std::is_signed<TValue>());
	}

#pragma endregion


	// ////////////////////////////////////////////////////////////////////////////////////////////////
	// ////////////////////////////////////////////////////////////////////////////////////////////////
	// ////////////////////////////////////////////////////////////////////////////////////////////////

#pragma region Normalized Float to ...


	template<typename TResult, typename TValue>
	__CUDA_HDI__ TResult NormFloatTo_impl(TValue xValue, std::true_type, std::true_type)
	{
		static_assert(std::numeric_limits<TValue>::is_integer == false,
			"Value type has to be a floating point type");

		using TLim = Clu::NumericLimits<TResult>;

		TValue xVal;

		xVal = (xValue / TValue(2) + TValue(0.5)) *  (TValue(TLim::Max()) - TValue(TLim::Min())) + TValue(TLim::Min());

		xVal = floor(xVal + TValue(0.5));

#if !defined(__NVCC__)
		if (xVal >= TValue(TLim::Max()))
		{
			return TLim::Max();
		}
		else if (xVal <= TValue(TLim::Min()))
		{
			return TLim::Min();
		}
		else
		{
			return TResult(xVal);
		}
#else
		return TResult(Clamp(floor(xVal + TValue(0.5)), TValue(TLim::Min()), TValue(TLim::Max())));
#endif
	}

	template<typename TResult, typename TValue>
	__CUDA_HDI__ TResult NormFloatTo_impl(TValue xValue, std::true_type, std::false_type)
	{
		static_assert(std::numeric_limits<TValue>::is_integer == false,
			"Value type has to be a floating point type");

		using TLim = Clu::NumericLimits<TResult>;

		TValue xVal;

		xVal = xValue * TValue(TLim::Max());

		xVal = floor(xVal + TValue(0.5));

#if !defined(__NVCC__)
		if (xVal >= TValue(TLim::Max()))
		{
			return TLim::Max();
		}
		else if (xVal <= TValue(TLim::Min()))
		{
			return TLim::Min();
		}
		else
		{
			return TResult(xVal);
		}
#else
		return TResult(Clamp(floor(xVal + TValue(0.5)), TValue(TLim::Min()), TValue(TLim::Max())));
#endif
	}

	template<typename TResult, typename TValue>
	__CUDA_HDI__ TResult NormFloatTo_impl(TValue xValue, std::false_type, std::true_type)
	{
		static_assert(std::numeric_limits<TValue>::is_integer == false,
			"Value type has to be a floating point type");

		return TResult(xValue);
	}

	template<typename TResult, typename TValue>
	__CUDA_HDI__ TResult NormFloatTo(TValue xValue)
	{
		return NormFloatTo_impl<TResult>(xValue, std::is_integral<TResult>(), std::is_signed<TResult>());
	}

#pragma endregion

	// ////////////////////////////////////////////////////////////////////////////////////////////////
	// ////////////////////////////////////////////////////////////////////////////////////////////////
	// ////////////////////////////////////////////////////////////////////////////////////////////////

#pragma region Cast Float To...
	template<typename TResult, typename TValue>
	__CUDA_HDI__ TResult CastFloatTo_impl(TValue xValue, std::false_type)
	{
		static_assert(std::numeric_limits<TValue>::is_integer == false,
			"Value type has to be a floating point type");

		return TResult(xValue);
	}

	template<typename TResult, typename TValue>
	__CUDA_HDI__ TResult CastFloatTo_impl(TValue xValue, std::true_type)
	{
		static_assert(std::numeric_limits<TValue>::is_integer == false,
			"Value type has to be a floating point type");

		using TLim = Clu::NumericLimits<TResult>;

		return TResult(Clamp(xValue, TValue(TLim::Min()), TValue(TLim::Max())));
	}


	template<typename TResult, typename TValue>
	__CUDA_HDI__ TResult CastFloatTo(TValue xValue)
	{
		return CastFloatTo_impl<TResult>(xValue, std::is_integral<TResult>());
	}
#pragma endregion

	// ////////////////////////////////////////////////////////////////////////////////////////////////
	// ////////////////////////////////////////////////////////////////////////////////////////////////
	// ////////////////////////////////////////////////////////////////////////////////////////////////

#pragma region Unit Conversions
	template <typename TValue>
	__CUDA_HDI__ TValue DegToRad(TValue dDeg)
	{
		return dDeg * Clu::Math::Constants<TValue>::RadPerDeg();
	}

	template <typename TValue>
	__CUDA_HDI__ TValue RadToDeg(TValue dRad)
	{
		return dRad * Clu::Math::Constants<TValue>::DegPerRad();
	}

#pragma endregion

} // namespace Clu
