////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.Math
// file:      Static.Vector.Math.h
//
// summary:   Declares the static. vector. mathematics class
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

// Include definition of sqrt if standard C compiler compiles this code
#if !defined(__NVCC__)
	#include <math.h>
#endif

#include "CluTec.Base/Defines.h"
#include "StandardMath.h"
#include "Static.Vector.h"

namespace Clu
{
	template<class T>
	__CUDA_HDI__ _SVector<T, 3> operator^(const _SVector<T, 3>& vA, const _SVector<T, 3>& vB)
	{
		_SVector<T, 3> vX;
		
		vX.SetElements(
			vA[1] * vB[2] - vA[2] * vB[1]
			, vA[2] * vB[0] - vA[0] * vB[2]
			, vA[0] * vB[1] - vA[1] * vB[0]
			);
		return vX;
	}


	///////////////////////////////////////////////////////////////////////
	/// Scalar Product

	template<class T>
	__CUDA_HDI__ T Dot(const _SVector1<T>& vA, const _SVector1<T>& vB)
	{
		return vA.x() * vB.x();
	}

	template<class T>
	__CUDA_HDI__ T Dot(const _SVector2<T>& vA, const _SVector2<T>& vB)
	{
		return vA.x() * vB.x() + vA.y() * vB.y();
	}

	template<class T>
	__CUDA_HDI__ T Dot(const _SVector3<T>& vA, const _SVector3<T>& vB)
	{
		return vA.x() * vB.x() + vA.y() * vB.y() + vA.z() * vB.z();
	}

	template<class T>
	__CUDA_HDI__ T Dot(const _SVector4<T>& vA, const _SVector4<T>& vB)
	{
		return vA.x() * vB.x() + vA.y() * vB.y() + vA.z() * vB.z() + vA.w() * vB.w();
	}

	template<class T, uint32_t t_nDim>
	__CUDA_HDI__ T Dot(const _SVector<T, t_nDim>& vA, const _SVector<T, t_nDim>& vB)
	{
		return Sum(vA * vB);
	}

	///////////////////////////
#if defined(__NVCC__)

	template<class T>
	__CUDA_HDI__ T Dot(const float1& vA, const _SVector1<T>& vB)
	{
		return vA.x * vB.x();
	}

	template<class T>
	__CUDA_HDI__ T Dot(const float2& vA, const _SVector2<T>& vB)
	{
		return vA.x * vB.x() + vA.y * vB.y();
	}

	template<class T>
	__CUDA_HDI__ T Dot(const float3& vA, const _SVector3<T>& vB)
	{
		return vA.x * vB.x() + vA.y * vB.y() + vA.z * vB.z();
	}

	template<class T>
	__CUDA_HDI__ T Dot(const float4& vA, const _SVector4<T>& vB)
	{
		return vA.x * vB.x() + vA.y * vB.y() + vA.z * vB.z() + vA.w * vB.w();
	}
	///////////////////////////

	template<class T>
	__CUDA_HDI__ T Dot(const _SVector1<T>& vA, const float1& vB)
	{
		return vA.x() * vB.x;
	}

	template<class T>
	__CUDA_HDI__ T Dot(const _SVector2<T>& vA, const float2& vB)
	{
		return vA.x() * vB.x + vA.y() * vB.y;
	}

	template<class T>
	__CUDA_HDI__ T Dot(const _SVector3<T>& vA, const float3& vB)
	{
		return vA.x() * vB.x + vA.y() * vB.y + vA.z() * vB.z;
	}

	template<class T>
	__CUDA_HDI__ T Dot(const _SVector4<T>& vA, const float4& vB)
	{
		return vA.x() * vB.x + vA.y() * vB.y + vA.z() * vB.z + vA.w() * vB.w;
	}

	///////////////////////////

	template<class T>
	__CUDA_HDI__ T Dot(const float1& vA, const float1& vB)
	{
		return vA.x * vB.x;
	}

	template<class T>
	__CUDA_HDI__ T Dot(const float2& vA, const float2& vB)
	{
		return vA.x * vB.x + vA.y * vB.y;
	}

	template<class T>
	__CUDA_HDI__ T Dot(const float3& vA, const float3& vB)
	{
		return vA.x * vB.x + vA.y * vB.y + vA.z * vB.z;
	}

	template<class T>
	__CUDA_HDI__ T Dot(const float4& vA, const float4& vB)
	{
		return vA.x * vB.x + vA.y * vB.y + vA.z * vB.z + vA.w * vB.w;
	}
#endif

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// 	Squares the given value.
	/// </summary>
	///
	/// <typeparam name="T">	Generic type parameter. </typeparam>
	/// <param name="tA">	The value. </param>
	///
	/// <returns>	The squared value. </returns>
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template<class T>
	__CUDA_HDI__ T Square(const T& tA)
	{
		return tA * tA;
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// 	Calculates square of each component of given vector (SVector1). This is a simple multiplication.
	/// </summary>
	///
	/// <typeparam name="T">	Generic type parameter. </typeparam>
	/// <param name="vA">  	The vector. </param>
	///
	/// <returns>	Square vector. </returns>
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template<class T>
	__CUDA_HDI__ _SVector1<T> Square(const _SVector1<T>& vA)
	{
		_SVector1<T> vX; vX.SetElements(vA.x() * vA.x()); return vX;
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// 	Calculates square of each component of given vector (SVector2). This is a simple multiplication.
	/// </summary>
	///
	/// <typeparam name="T">	Generic type parameter. </typeparam>
	/// <param name="vA">  	The vector. </param>
	///
	/// <returns>	Square vector. </returns>
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template<class T>
	__CUDA_HDI__ _SVector2<T> Square(const _SVector2<T>& vA)
	{
		_SVector2<T> vX; vX.SetElements(vA.x() * vA.x(), vA.y() * vA.y()); return vX;
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// 	Calculates square of each component of given vector (SVector3). This is a simple multiplication.
	/// </summary>
	///
	/// <typeparam name="T">	Generic type parameter. </typeparam>
	/// <param name="vA">  	The vector. </param>
	///
	/// <returns>	Square vector. </returns>
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template<class T>
	__CUDA_HDI__ _SVector3<T> Square(const _SVector3<T>& vA)
	{
		_SVector3<T> vX; vX.SetElements(vA.x() * vA.x(), vA.y() * vA.y(), vA.z() * vA.z()); return vX;
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// 	Calculates square of each component of given vector (SVector4). This is a simple multiplication.
	/// </summary>
	///
	/// <typeparam name="T">	Generic type parameter. </typeparam>
	/// <param name="vA">  	The vector. </param>
	///
	/// <returns>	Square vector. </returns>
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template<class T>
	__CUDA_HDI__ _SVector4<T> Square(const _SVector4<T>& vA)
	{
		_SVector4<T> vX; vX.SetElements(vA.x() * vA.x(), vA.y() * vA.y(), vA.z() * vA.z(), vA.w() * vA.w()); return vX;
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// 	Calculates square of each component of given vector (SVector). This is a simple multiplication.
	/// </summary>
	///
	/// <typeparam name="T">	Generic type parameter. </typeparam>
	/// <param name="vA">  	The vector. </param>
	///
	/// <returns>	Square vector. </returns>
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template<class T, uint32_t t_nDim>
	__CUDA_HDI__ _SVector<T, t_nDim> Square(const _SVector<T, t_nDim>& vA)
	{
		_SVector<T, t_nDim> vX;
		vX.ForEachElementPair(vA, [](T& xValue, const T& xValA)
		{
			xValue = xValA * xValA;
		});

		return vX;
	}

	/////////////////////////////////////////////////////////////////////
	// SQRT

	template<class T>
	__CUDA_HDI__ _SVector1<T> Sqrt(const _SVector1<T>& vA)
	{
		_SVector1<T> vX; vX.SetElements(::sqrt(vA.x())); return vX;
	}

	template<class T>
	__CUDA_HDI__ _SVector2<T> Sqrt(const _SVector2<T>& vA)
	{
		_SVector2<T> vX; vX.SetElements(::sqrt(vA.x()), ::sqrt(vA.y())); return vX;
	}

	template<class T>
	__CUDA_HDI__ _SVector3<T> Sqrt(const _SVector3<T>& vA)
	{
		_SVector3<T> vX; vX.SetElements(::sqrt(vA.x()), ::sqrt(vA.y()), ::sqrt(vA.z())); return vX;
	}

	template<class T>
	__CUDA_HDI__ _SVector4<T> Sqrt(const _SVector4<T>& vA)
	{
		_SVector4<T> vX; vX.SetElements(::sqrt(vA.x()), ::sqrt(vA.y()), ::sqrt(vA.z()), ::sqrt(vA.w())); return vX;
	}

	template<class T, uint32_t t_nDim>
	__CUDA_HDI__ _SVector<T, t_nDim> Sqrt(const _SVector<T, t_nDim>& vA)
	{
		SVector<T, t_nDim> vX;
		vX.ForEachElementPair(vA, [](T& xValue, const T& xValA)
		{
			xValue = ::sqrt(xValA);
		});

		return vX;
	}

	///////////////////////////////////////////////////////////////////////
	// Length Square

	template<class T>
	__CUDA_HDI__ T LengthSquare(const _SVector1<T>& vA)
	{
		return vA.x() * vA.x();
	}

	template<class T>
	__CUDA_HDI__ T LengthSquare(const _SVector2<T>& vA)
	{
		return vA.x() * vA.x() + vA.y() * vA.y();
	}

	template<class T>
	__CUDA_HDI__ T LengthSquare(const _SVector3<T>& vA)
	{
		return vA.x() * vA.x() + vA.y() * vA.y() + vA.z() * vA.z();
	}

	template<class T>
	__CUDA_HDI__ T LengthSquare(const _SVector4<T>& vA)
	{
		return vA.x() * vA.x() + vA.y() * vA.y() + vA.z() * vA.z() + vA.w() * vA.w();
	}

	template<class T, uint32_t t_nDim>
	__CUDA_HDI__ T LengthSquare(const _SVector<T, t_nDim>& vA)
	{
		return Dot(vA, vA);
	}

	///////////////////////////////////////////////////////////////////////
	// Length

	template<class T>
	__CUDA_HDI__ T Length(const _SVector1<T>& vA)
	{
		return vA.x();
	}

	template<class T>
	__CUDA_HDI__ T Length(const _SVector2<T>& vA)
	{
		return ::sqrt(vA.x() * vA.x() + vA.y() * vA.y());
	}

	template<class T>
	__CUDA_HDI__ T Length(const _SVector3<T>& vA)
	{
		return ::sqrt(vA.x() * vA.x() + vA.y() * vA.y() + vA.z() * vA.z());
	}

	template<class T>
	__CUDA_HDI__ T Length(const _SVector4<T>& vA)
	{
		return ::sqrt(vA.x() * vA.x() + vA.y() * vA.y() + vA.z() * vA.z() + vA.w() * vA.w());
	}

	template<class T, uint32_t t_nDim>
	__CUDA_HDI__ T Length(const _SVector<T, t_nDim>& vA)
	{
		return ::sqrt(Dot(vA, vA));
	}


#if defined(__NVCC__)

	__CUDA_HDI__ float Length(const float1& vA)
	{
		return vA.x;
	}

	__CUDA_HDI__ float Length(const float2& vA)
	{
		return ::sqrt(vA.x * vA.x + vA.y * vA.y);
	}

	__CUDA_HDI__ float Length(const float3& vA)
	{
		return ::sqrt(vA.x * vA.x + vA.y * vA.y + vA.z * vA.z);
	}

	__CUDA_HDI__ float Length(const float4& vA)
	{
		return ::sqrt(vA.x * vA.x + vA.y * vA.y + vA.z * vA.z + vA.w * vA.w);
	}

#endif
	///////////////////////////////////////////////////////////////////////
	// CrossRatio

	// get cross ratio of points A->B->C->D

	template<class T>
	__CUDA_HDI__ T CrossRatio(const _SVector2<T>& vecA, const _SVector2<T>& vecB, const _SVector2<T>& vecC, const _SVector2<T>& vecD)
	{
		const float fAC = Length(vecC - vecA);
		const float fBD = Length(vecD - vecB);
		const float fBC = Length(vecC - vecB);
		const float fAD = Length(vecD - vecA);

		return fAC * fBD / (fBC * fAD);
	}

	///////////////////////////////////////////////////////////////////////
	// Distance

	//template<class T>
	//__CUDA_HDI__ T Distance(const _SVector1<T>& vA, const _SVector1<T>& vB)
	//{
	//	return Length(vA - vB);
	//}

	//template<class T>
	//__CUDA_HDI__ T Distance(const _SVector2<T>& vA, const _SVector2<T>& vB)
	//{
	//	return Length(vA - vB);
	//}

	//template<class T>
	//__CUDA_HDI__ T Distance(const _SVector3<T>& vA, const _SVector3<T>& vB)
	//{
	//	return Length(vA - vB);
	//}

	//template<class T>
	//__CUDA_HDI__ T Distance(const _SVector4<T>& vA, const _SVector4<T>& vB)
	//{
	//	return Length(vA - vB);
	//}

	template<class T, uint32_t t_nDim>
	__CUDA_HDI__ T Distance(const _SVector<T, t_nDim>& vA, const _SVector<T, t_nDim>& vB)
	{
		return Length(vA - vB);
	}

	///////////////////////////////////////////////////////////////////////
	// Distance Square

	//template<class T>
	//__CUDA_HDI__ T DistanceSquare(const _SVector1<T>& vA, const _SVector1<T>& vB)
	//{
	//	return Sum(Square(vA - vB));
	//}

	//template<class T>
	//__CUDA_HDI__ T DistanceSquare(const _SVector2<T>& vA, const _SVector2<T>& vB)
	//{
	//	return Sum(Square(vA - vB));
	//}

	//template<class T>
	//__CUDA_HDI__ T DistanceSquare(const _SVector3<T>& vA, const _SVector3<T>& vB)
	//{
	//	return Sum(Square(vA - vB));
	//}

	//template<class T>
	//__CUDA_HDI__ T DistanceSquare(const _SVector4<T>& vA, const _SVector4<T>& vB)
	//{
	//	return Sum(Square(vA - vB));
	//}

	template<class T, uint32_t t_nDim>
	__CUDA_HDI__ T DistanceSquare(const _SVector<T, t_nDim>& vA, const _SVector<T, t_nDim>& vB)
	{
		return Sum(Square(vA - vB));
	}

	/////////////////////////////////////////////////////////////////////
	// Determinant of matrix created from a number of vectors

	template<class T>
	__CUDA_HDI__ T Determinant(const _SVector<T, 1>& vA)
	{
		return vA[0];
	}

	template<class T>
	__CUDA_HDI__ T Determinant(const _SVector<T, 2>& vA, const _SVector<T, 2>& vB)
	{
		return vA[0] * vB[1] - vA[1] * vB[0];
	}

	template<class T>
	__CUDA_HDI__ T Determinant(const _SVector<T, 3>& vA, const _SVector<T, 3>& vB, const _SVector<T, 3>& vC)
	{
		return vA[0] * (vB[1] * vC[2] - vB[2] * vA[1])
			   + vA[1] * (vB[2] * vC[0] - vB[0] * vC[2])
			   + vA[2] * (vB[0] * vC[1] - vB[1] * vC[0]);
	}

	/////////////////////////////////////////////////////////////////////
	// Normalize

	template<class TVec>
	__CUDA_HDI__ TVec Normalize(const TVec& vA)
	{
		return vA / Length(vA);
	}

	/////////////////////////////////////////////////////////////////////
	// POW

	template<class T>
	__CUDA_HDI__ _SVector1<T> Pow(const _SVector1<T>& vA, T tPow)
	{
		_SVector1<T> vX; vX.SetElements(::pow(vA.x(), tPow)); return vX;
	}

	template<class T>
	__CUDA_HDI__ _SVector2<T> Pow(const _SVector2<T>& vA, T tPow)
	{
		_SVector2<T> vX; vX.SetElements(::pow(vA.x(), tPow), ::pow(vA.y(), tPow)); return vX;
	}

	template<class T>
	__CUDA_HDI__ _SVector3<T> Pow(const _SVector3<T>& vA, T tPow)
	{
		_SVector3<T> vX; vX.SetElements(::pow(vA.x(), tPow), ::pow(vA.y(), tPow), ::pow(vA.z(), tPow)); return vX;
	}

	template<class T>
	__CUDA_HDI__ _SVector4<T> Pow(const _SVector4<T>& vA, T tPow)
	{
		_SVector4<T> vX; vX.SetElements(::pow(vA.x(), tPow), ::pow(vA.y(), tPow), ::pow(vA.z(), tPow), ::pow(vA.w(), tPow)); return vX;
	}

	template<class T, uint32_t t_nDim>
	__CUDA_HDI__ _SVector<T, t_nDim> Pow(const _SVector<T, t_nDim>& vA, T tPow)
	{
		SVector<T, t_nDim> vX;

		vX.ForEachElementPair(vA, [&tPow](T& xValue, const T& xValA)
		{
			xValue = ::pow(xValA, tPow);
		});

		return vX;
	}

	/////////////////////////////////////////////////////////////////////
	/// Floor

	template<class T>
	__CUDA_HDI__ _SVector1<T> Floor(const _SVector1<T>& vA)
	{
		_SVector1<T> vX; vX.SetElements(T(::floor(vA.x()))); return vX;
	}

	template<class T>
	__CUDA_HDI__ _SVector2<T> Floor(const _SVector2<T>& vA)
	{
		_SVector2<T> vX; vX.SetElements(T(::floor(vA.x())), T(::floor(vA.y()))); return vX;
	}

	template<class T>
	__CUDA_HDI__ _SVector3<T> Floor(const _SVector3<T>& vA)
	{
		_SVector3<T> vX; vX.SetElements(T(::floor(vA.x())), T(::floor(vA.y())), T(::floor(vA.z()))); return vX;
	}

	template<class T>
	__CUDA_HDI__ _SVector4<T> Floor(const _SVector4<T>& vA)
	{
		_SVector4<T> vX; vX.SetElements(T(::floor(vA.x())), T(::floor(vA.y())), T(::floor(vA.z())), T(::floor(vA.w()))); return vX;
	}

	template<class T, uint32_t t_nDim>
	__CUDA_HDI__ _SVector<T, t_nDim> Floor(const _SVector<T, t_nDim>& vA)
	{
		_SVector<T, t_nDim> vX;

		vX.ForEachElementPair(vA, [](T& xValue, const T& xValA)
		{
			xValue = (T)::floor(xValA);
		});

		return vX;
	}

	/////////////////////////////////////////////////////////////////////
	/// Ceiling

	template<class T>
	__CUDA_HDI__ _SVector1<T> Ceil(const _SVector1<T>& vA)
	{
		_SVector1<T> vX; vX.SetElements(T(::ceil(vA.x()))); return vX;
	}

	template<class T>
	__CUDA_HDI__ _SVector2<T> Ceil(const _SVector2<T>& vA)
	{
		_SVector2<T> vX; vX.SetElements(T(::ceil(vA.x())), T(::ceil(vA.y()))); return vX;
	}

	template<class T>
	__CUDA_HDI__ _SVector3<T> Ceil(const _SVector3<T>& vA)
	{
		_SVector3<T> vX; vX.SetElements(T(::ceil(vA.x())), T(::ceil(vA.y())), T(::ceil(vA.z()))); return vX;
	}

	template<class T>
	__CUDA_HDI__ _SVector4<T> Ceil(const _SVector4<T>& vA)
	{
		_SVector4<T> vX; vX.SetElements(T(::ceil(vA.x())), T(::ceil(vA.y())), T(::ceil(vA.z())), T(::ceil(vA.w()))); return vX;
	}

	template<class T, uint32_t t_nDim>
	__CUDA_HDI__ _SVector<T, t_nDim> Ceil(const _SVector<T, t_nDim>& vA)
	{
		_SVector<T, t_nDim> vX;

		vX.ForEachElementPair(vA, [](T& xValue, const T& xValA)
		{
			xValue = (T)::ceil(xValA);
		});

		return vX;
	}

	/////////////////////////////////////////////////////////////////////
	/// Abs
	template<class T>
	__CUDA_HDI__ T Abs(const T& dA)
	{
		return T(::abs(dA));
	}


	template<class T>
	__CUDA_HDI__ _SVector1<T> Abs(const _SVector1<T>& vA)
	{
		_SVector1<T> vX; vX.SetElements(T(::abs(vA.x()))); return vX;
	}

	template<class T>
	__CUDA_HDI__ _SVector2<T> Abs(const _SVector2<T>& vA)
	{
		_SVector2<T> vX; vX.SetElements(T(::abs(vA.x())), T(::abs(vA.y()))); return vX;
	}

	template<class T>
	__CUDA_HDI__ _SVector3<T> Abs(const _SVector3<T>& vA)
	{
		_SVector3<T> vX; vX.SetElements(T(::abs(vA.x())), T(::abs(vA.y())), T(::abs(vA.z()))); return vX;
	}

	template<class T>
	__CUDA_HDI__ _SVector4<T> Abs(const _SVector4<T>& vA)
	{
		_SVector4<T> vX; vX.SetElements(T(::abs(vA.x())), T(::abs(vA.y())), T(::abs(vA.z())), T(::abs(vA.w()))); return vX;
	}

	template<class T, uint32_t t_nDim>
	__CUDA_HDI__ _SVector<T, t_nDim> Abs(const _SVector<T, t_nDim>& vA)
	{
		SVector<T, t_nDim> vX;

		vX.ForEachElementPair(vA, [](T& xValue, const T& xValA)
		{
			xValue = (T)::abs(xValA);
		});

		return vX;
	}

	/////////////////////////////////////////////////////////////////////
	/// Round vector to given number of decimal places

	template<class T>
	__CUDA_HDI__ _SVector1<T> Round(const _SVector1<T>& vA, int iDec)
	{
		_SVector1<T> vX; vX.SetElements(T(Round(vA.x(), iDec))); return vX;
	}

	template<class T>
	__CUDA_HDI__ _SVector2<T> Round(const _SVector2<T>& vA, int iDec)
	{
		_SVector2<T> vX; vX.SetElements(T(Round(vA.x(), iDec)), T(Round(vA.y(), iDec))); return vX;
	}

	template<class T>
	__CUDA_HDI__ _SVector3<T> Round(const _SVector3<T>& vA, int iDec)
	{
		_SVector3<T> vX; vX.SetElements(T(Round(vA.x(), iDec)), T(Round(vA.y(), iDec)), T(Round(vA.z(), iDec))); return vX;
	}

	template<class T>
	__CUDA_HDI__ _SVector4<T> Round(const _SVector4<T>& vA, int iDec)
	{
		_SVector4<T> vX; vX.SetElements(T(Round(vA.x(), iDec)), T(Round(vA.y(), iDec)), T(Round(vA.z(), iDec)), T(Round(vA.w(), iDec))); return vX;
	}

	template<class T, uint32_t t_nDim>
	__CUDA_HDI__ _SVector<T, t_nDim> Round(const _SVector<T, t_nDim>& vA, int iDec)
	{
		SVector<T, t_nDim> vX;

		vX.ForEachElementPair(vA, [&iDec](T& xValue, const T& xValA)
		{
			xValue = Round(xValA, iDec);
		});

		return vX;
	}

	/////////////////////////////////////////////////////////////////////
	/// Round floating point to integer

	template<class T>
	__CUDA_HDI__ _SVector1<int> ToInt(const _SVector1<T>& vA)
	{
		_SVector1<int> vX; vX.SetElements(ToInt(vA.x())); return vX;
	}

	template<class T>
	__CUDA_HDI__ _SVector2<int> ToInt(const _SVector2<T>& vA)
	{
		_SVector2<int> vX; vX.SetElements(ToInt(vA.x()), ToInt(vA.y())); return vX;
	}

	template<class T>
	__CUDA_HDI__ _SVector3<int> ToInt(const _SVector3<T>& vA)
	{
		_SVector3<int> vX; vX.SetElements(ToInt(vA.x()), ToInt(vA.y()), ToInt(vA.z())); return vX;
	}

	template<class T>
	__CUDA_HDI__ _SVector4<int> ToInt(const _SVector4<T>& vA)
	{
		_SVector4<int> vX; vX.SetElements(ToInt(vA.x()), ToInt(vA.y()), ToInt(vA.z()), ToInt(vA.w())); return vX;
	}

	template<class T, uint32_t t_nDim>
	__CUDA_HDI__ _SVector<int, t_nDim> ToInt(const _SVector<T, t_nDim>& vA)
	{
		SVector<int, t_nDim> vX;

		vX.ForEachElementPair(vA, [](T& xValue, const T& xValA)
		{
			xValue = ToInt(xValA);
		});
		return vX;
	}

	/////////////////////////////////////////////////////////////////////
	/// Clamp vector to given range

	template<class T>
	__CUDA_HDI__ _SVector1<T> Clamp(const _SVector1<T>& vA, T tMin, T tMax)
	{
		_SVector1<T> vX; vX.SetElements(Clamp(vA.x(), tMin, tMax)); return vX;
	}

	template<class T>
	__CUDA_HDI__ _SVector2<T> Clamp(const _SVector2<T>& vA, T tMin, T tMax)
	{
		_SVector2<T> vX; vX.SetElements(Clamp(vA.x(), tMin, tMax), Clamp(vA.y(), tMin, tMax)); return vX;
	}

	template<class T>
	__CUDA_HDI__ _SVector3<T> Clamp(const _SVector3<T>& vA, T tMin, T tMax)
	{
		_SVector3<T> vX; vX.SetElements(Clamp(vA.x(), tMin, tMax), Clamp(vA.y(), tMin, tMax), Clamp(vA.z(), tMin, tMax)); return vX;
	}

	template<class T>
	__CUDA_HDI__ _SVector4<T> Clamp(const _SVector4<T>& vA, T tMin, T tMax)
	{
		_SVector4<T> vX; vX.SetElements(Clamp(vA.x(), tMin, tMax), Clamp(vA.y(), tMin, tMax), Clamp(vA.z(), tMin, tMax), Clamp(vA.w(), tMin, tMax)); return vX;
	}

	template<class T, uint32_t t_nDim>
	__CUDA_HDI__ _SVector<T, t_nDim> Clamp(const _SVector<T, t_nDim>& vA, T tMin, T tMax)
	{
		SVector<T, t_nDim> vX;

		vX.ForEachElementPair(vA, [&tMin, &tMax](T& xValue, const T& xValA)
		{
			xValue = Clamp(xValA, tMin, tMax);
		});

		return vX;
	}

	template<class T>
	__CUDA_HDI__ _SVector1<T> Clamp(const _SVector1<T>& vA, const _SVector1<T>& vMin, const _SVector1<T>& vMax)
	{
		_SVector1<T> vX; vX.SetElements(Clamp(vA.x(), vMin.x(), vMax.x())); return vX;
	}

	template<class T>
	__CUDA_HDI__ _SVector2<T> Clamp(const _SVector2<T>& vA, const _SVector2<T>& vMin, const _SVector2<T>& vMax)
	{
		_SVector2<T> vX; vX.SetElements(Clamp(vA.x(), vMin.x(), vMax.x()), Clamp(vA.y(), vMin.y(), vMax.y())); return vX;
	}

	template<class T>
	__CUDA_HDI__ _SVector3<T> Clamp(const _SVector3<T>& vA, const _SVector3<T>& vMin, const _SVector3<T>& vMax)
	{
		_SVector3<T> vX; vX.SetElements(Clamp(vA.x(), vMin.x(), vMax.x()), Clamp(vA.y(), vMin.y(), vMax.y()), Clamp(vA.z(), vMin.z(), vMax.z())); return vX;
	}

	template<class T>
	__CUDA_HDI__ _SVector4<T> Clamp(const _SVector4<T>& vA, const _SVector4<T>& vMin, const _SVector4<T>& vMax)
	{
		_SVector4<T> vX; vX.SetElements(Clamp(vA.x(), vMin.x(), vMax.x()), Clamp(vA.y(), vMin.y(), vMax.y()), Clamp(vA.z(), vMin.z(), vMax.z()), Clamp(vA.w(), vMin.w(), vMax.w())); return vX;
	}

	template<class T, uint32_t t_nDim>
	__CUDA_HDI__ _SVector<T, t_nDim> Clamp(const _SVector<T, t_nDim>& vA, const _SVector<T, t_nDim>& vMin, const _SVector<T, t_nDim>& vMax)
	{
		using TIdx = typename SVector<T, t_nDim>::TIdx;

		SVector<T, t_nDim> vX;

		vX.ForEachElementIdx([&vA, &vMin, &vMax](T& xValue, TIdx iIdx)
		{
			xValue = Clamp(vA[i], vMin[i], vMax[i]);
		});

		return vX;
	}



	template<class T, uint32_t t_nDim>
	__CUDA_HDI__ _SVector<T, t_nDim> Min(const _SVector<T, t_nDim>& vA, const _SVector<T, t_nDim>& vB)
	{
		_SVector<T, t_nDim> vX;

		vX.ForEachElementTriplet(vA, vB, [](T& dValX, const T& dValA, const T& dValB)
		{
			dValX = Clu::Min(dValA, dValB);
		});

		return vX;
	}

	template<class T, uint32_t t_nDim>
	__CUDA_HDI__ _SVector<T, t_nDim> Max(const _SVector<T, t_nDim>& vA, const _SVector<T, t_nDim>& vB)
	{
		_SVector<T, t_nDim> vX;

		vX.ForEachElementTriplet(vA, vB, [](T& dValX, const T& dValA, const T& dValB)
		{
			dValX = Clu::Max(dValA, dValB);
		});

		return vX;
	}

	//template<class T>
	//__CUDA_HDI__ double point_to_line_distance(const _SVector2<T>& vPnt, const _SVector2<double>& vLinePnt1, const _SVector2<double>& vLinePnt2)
	//{
	//	SVector2<double> vVecToLine, vDirLine;

	//	// Vector from point to point 1 on line
	//	vVecToLine = vPnt - vLinePnt1;

	//	// Direction of line
	//	vDirLine  = vLinePnt2 - vLinePnt1;
	//	vDirLine /= length(vDirLine);

	//	// Vector from point to line in direction perpendicular to line
	//	vVecToLine -= dot(vVecToLine, vDirLine) * vDirLine;

	//	return length(vVecToLine);
	//}

	/// @}
}	// namespace Clu
