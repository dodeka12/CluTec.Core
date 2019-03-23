////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.Math
// file:      Static.Vector.h
//
// summary:   Declares the static. vector class
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

//#define CLU_STATIC_DEBUG
#include "CluTec.Types1/IString.h"
#include "CluTec.Base/Defines.h"
#include "CluTec.Base/StaticDebug.h"

#include "Static.Array.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// namespace: Clu
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace Clu
{

////////////////////////////////////////////////////////////////////////////////////////////
//// Vector N

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// N-D Vector class. While the types SVector1&lt;T&gt;, SVector2&lt;T&gt;, SVector3&lt;T&gt; and SVector4&lt;
	/// T&gt; can also be replaced by this vector type, it is not possible to access the components
	/// of a SVector&lt;T, iDim&gt; via \c x, \c y, \c z and \c w.
	/// < / summary>
	/// </summary>
	///
	/// <remarks>	Perwass. </remarks>
	///
	/// <typeparam name="T">	 	Generic type parameter. </typeparam>
	/// <typeparam name="t_iDim">	Type of the dim. </typeparam>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	template<class _TValue, uint32_t t_nDim>
	struct _SVector : public _SArray<_TValue, t_nDim>
	{
		using TBase = _SArray<_TValue, t_nDim>;
		using TThis = _SVector<_TValue, t_nDim>;

	private:
		template<TIdx t_nIdx> 
		__CUDA_HDI__ const TValue& _GetElement(TIdx nIdx) const
		{
			static_assert(t_nIdx < t_nDim, "Template index has to be smaller than dimension");

#ifdef CLU_STATIC_DEBUG
#pragma message("_GetElement t_nIdx: ")
			STATIC_DEBUG<>::PRINT_size_t<t_nIdx>();

#endif

			if (t_nIdx == nIdx)
			{
				return pData[t_nIdx];
			}
			else
			{
				return _GetElement<t_nIdx - 1>(nIdx);
			}
		}

		template<>
		__CUDA_HDI__ const TValue& _GetElement<0>(TIdx nIdx) const
		{
			return pData[0];
		}

	public:
		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Gets an element of the vector by testing the given index against every possible
		/// 			index in the vector with an if-clause. This can speed up CUDA Kernel and
		/// 			reduce the number of registers needed. Is probably slower on CPUs compared
		/// 			to operator[]. </summary>
		///
		/// <param name="nIdx">	The index. </param>
		///
		/// <returns>	The element. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		__CUDA_HDI__ const TValue& GetElement(TIdx nIdx) const
		{
			return _GetElement<t_nDim - 1>(nIdx);
		}

		__CUDA_HDI__ TThis& operator= (const TThis& xVec)
		{
			TBase::Assign(xVec);
			return *this;
		}

		__CUDA_HDI__ TThis operator- ()
		{
			TThis vX;
			vX.ForEachElementPair(*this, [](TValue &xValue, const TValue& xThis)
			{
				xValue = -xThis;
			});
			return vX;
		}



#pragma region CUDA Types Assignment
#if defined(__NVCC__)

#define _CLU_DEF_ASSIGN_1(theType) \
		__CUDA_HDI__ TThis& operator=(const theType& vX) \
		{ \
			SetElements(TValue(vX.x)); \
			return *this; \
		}

#define _CLU_DEF_ASSIGN_2(theType) \
		__CUDA_HDI__ TThis& operator=(const theType& vX) \
		{ \
			SetElements(TValue(vX.x), TValue(vX.y)); \
			return *this; \
		}

#define _CLU_DEF_ASSIGN_3(theType) \
		__CUDA_HDI__ TThis& operator=(const theType& vX) \
		{ \
			SetElements(TValue(vX.x), TValue(vX.y), TValue(vX.z)); \
			return *this; \
		}

#define _CLU_DEF_ASSIGN_4(theType) \
		__CUDA_HDI__ TThis& operator=(const theType& vX) \
		{ \
			SetElements(TValue(vX.x), TValue(vX.y), TValue(vX.z), TValue(vX.w)); \
			return *this; \
		}

		_CLU_DEF_ASSIGN_1(char1);
		_CLU_DEF_ASSIGN_1(uchar1);
		_CLU_DEF_ASSIGN_1(short1);
		_CLU_DEF_ASSIGN_1(ushort1);
		_CLU_DEF_ASSIGN_1(int1);
		_CLU_DEF_ASSIGN_1(uint1);
		_CLU_DEF_ASSIGN_1(float1);
		_CLU_DEF_ASSIGN_1(double1);

		_CLU_DEF_ASSIGN_2(char2);
		_CLU_DEF_ASSIGN_2(uchar2);
		_CLU_DEF_ASSIGN_2(short2);
		_CLU_DEF_ASSIGN_2(ushort2);
		_CLU_DEF_ASSIGN_2(int2);
		_CLU_DEF_ASSIGN_2(uint2);
		_CLU_DEF_ASSIGN_2(float2);
		_CLU_DEF_ASSIGN_2(double2);

		_CLU_DEF_ASSIGN_3(char3);
		_CLU_DEF_ASSIGN_3(uchar3);
		_CLU_DEF_ASSIGN_3(short3);
		_CLU_DEF_ASSIGN_3(ushort3);
		_CLU_DEF_ASSIGN_3(int3);
		_CLU_DEF_ASSIGN_3(uint3);
		_CLU_DEF_ASSIGN_3(float3);
		_CLU_DEF_ASSIGN_3(double3);

		_CLU_DEF_ASSIGN_4(char4);
		_CLU_DEF_ASSIGN_4(uchar4);
		_CLU_DEF_ASSIGN_4(short4);
		_CLU_DEF_ASSIGN_4(ushort4);
		_CLU_DEF_ASSIGN_4(int4);
		_CLU_DEF_ASSIGN_4(uint4);
		_CLU_DEF_ASSIGN_4(float4);
		_CLU_DEF_ASSIGN_4(double4);

#undef _CLU_DEF_ASSIGN_1
#undef _CLU_DEF_ASSIGN_2
#undef _CLU_DEF_ASSIGN_3
#undef _CLU_DEF_ASSIGN_4

#endif
#pragma endregion
	};

#pragma region CUDA Types Make from Vector
#if defined(__NVCC__)

#define _CLU_DEF_MAKE_1(theType, theCompType) \
	template<typename TValue, uint32_t t_nDim> \
	__CUDA_HDI__ theType make_##theType(const _SVector<TValue, t_nDim>& vA) \
	{ \
		using TVec = _SVector<TValue, t_nDim>; \
		static_assert(TVec::ElementCount >= 1, "Given vector has not enough components"); \
		return ::make_##theType((theCompType)vA[0]); \
	}

#define _CLU_DEF_MAKE_2(theType, theCompType) \
	template<typename TValue, uint32_t t_nDim> \
	__CUDA_HDI__ theType make_##theType(const _SVector<TValue, t_nDim>& vA) \
	{ \
		using TVec = _SVector<TValue, t_nDim>; \
		static_assert(TVec::ElementCount >= 2, "Given vector has not enough components"); \
		return ::make_##theType((theCompType)vA[0], (theCompType)vA[1]); \
	}

#define _CLU_DEF_MAKE_3(theType, theCompType) \
	template<typename TValue, uint32_t t_nDim> \
	__CUDA_HDI__ theType make_##theType(const _SVector<TValue, t_nDim>& vA) \
	{ \
		using TVec = _SVector<TValue, t_nDim>; \
		static_assert(TVec::ElementCount >= 3, "Given vector has not enough components"); \
		return ::make_##theType((theCompType)vA[0], (theCompType)vA[1], (theCompType)vA[2]); \
	}

#define _CLU_DEF_MAKE_4(theType, theCompType) \
	template<typename TValue, uint32_t t_nDim> \
	__CUDA_HDI__ theType make_##theType(const _SVector<TValue, t_nDim>& vA) \
	{ \
		using TVec = _SVector<TValue, t_nDim>; \
		static_assert(TVec::ElementCount >= 4, "Given vector has not enough components"); \
		return ::make_##theType((theCompType)vA[0], (theCompType)vA[1], (theCompType)vA[2], (theCompType)vA[3]); \
	}

	_CLU_DEF_MAKE_1(char1	, char);
	_CLU_DEF_MAKE_1(uchar1	, unsigned char);
	_CLU_DEF_MAKE_1(short1	, short);
	_CLU_DEF_MAKE_1(ushort1	, unsigned short);
	_CLU_DEF_MAKE_1(int1	, int);
	_CLU_DEF_MAKE_1(uint1	, unsigned int);
	_CLU_DEF_MAKE_1(float1	, float);
	_CLU_DEF_MAKE_1(double1	, double);

	_CLU_DEF_MAKE_2(char2, char);
	_CLU_DEF_MAKE_2(uchar2, unsigned char);
	_CLU_DEF_MAKE_2(short2, short);
	_CLU_DEF_MAKE_2(ushort2, unsigned short);
	_CLU_DEF_MAKE_2(int2, int);
	_CLU_DEF_MAKE_2(uint2, unsigned int);
	_CLU_DEF_MAKE_2(float2, float);
	_CLU_DEF_MAKE_2(double2, double);

	_CLU_DEF_MAKE_3(char3, char);
	_CLU_DEF_MAKE_3(uchar3, unsigned char);
	_CLU_DEF_MAKE_3(short3, short);
	_CLU_DEF_MAKE_3(ushort3, unsigned short);
	_CLU_DEF_MAKE_3(int3, int);
	_CLU_DEF_MAKE_3(uint3, unsigned int);
	_CLU_DEF_MAKE_3(float3, float);
	_CLU_DEF_MAKE_3(double3, double);

	_CLU_DEF_MAKE_4(char4, char);
	_CLU_DEF_MAKE_4(uchar4, unsigned char);
	_CLU_DEF_MAKE_4(short4, short);
	_CLU_DEF_MAKE_4(ushort4, unsigned short);
	_CLU_DEF_MAKE_4(int4, int);
	_CLU_DEF_MAKE_4(uint4, unsigned int);
	_CLU_DEF_MAKE_4(float4, float);
	_CLU_DEF_MAKE_4(double4, double);

#undef _CLU_DEF_MAKE_1
#undef _CLU_DEF_MAKE_2
#undef _CLU_DEF_MAKE_3
#undef _CLU_DEF_MAKE_4


#endif
#pragma endregion

#pragma region Arithmetics

	template<class T, uint32_t t_nDim>
	__CUDA_HDI__ _SVector<T, t_nDim> operator+(const _SVector<T, t_nDim>& vA, const _SVector<T, t_nDim>& vB)
	{
		using TIdx = typename _SArray<T, t_nDim>::TIdx;

		_SVector<T, t_nDim> vX;
		vX.ForEachElementIdx([&vA, &vB](T& xValue, TIdx i)
		{
			xValue = vA[i] + vB[i];
		});
		return vX;
	}

	template<class T, uint32_t t_nDim>
	__CUDA_HDI__ _SVector<T, t_nDim> operator-(const _SVector<T, t_nDim>& vA, const _SVector<T, t_nDim>& vB)
	{
		using TIdx = typename _SArray<T, t_nDim>::TIdx;

		_SVector<T, t_nDim> vX;
		vX.ForEachElementIdx([&vA, &vB](T& xValue, TIdx i)
		{
			xValue = vA[i] - vB[i];
		});
		return vX;
	}

	template<class T, uint32_t t_nDim>
	__CUDA_HDI__ _SVector<T, t_nDim> operator*(const _SVector<T, t_nDim>& vA, const _SVector<T, t_nDim>& vB)
	{
		using TIdx = typename _SArray<T, t_nDim>::TIdx;

		_SVector<T, t_nDim> vX;
		vX.ForEachElementIdx([&vA, &vB](T& xValue, TIdx i)
		{
			xValue = vA[i] * vB[i];
		});
		return vX;
	}

	template<class T, uint32_t t_nDim>
	__CUDA_HDI__ _SVector<T, t_nDim> operator/(const _SVector<T, t_nDim>& vA, const _SVector<T, t_nDim>& vB)
	{
		using TIdx = typename _SArray<T, t_nDim>::TIdx;

		_SVector<T, t_nDim> vX;
		vX.ForEachElementIdx([&vA, &vB](T& xValue, TIdx i)
		{
			xValue = vA[i] / vB[i];
		});
		return vX;
	}


	template<class T, uint32_t t_nDim>
	__CUDA_HDI__ _SVector<T, t_nDim> operator+(const _SVector<T, t_nDim>& vA, T xB)
	{
		using TIdx = typename _SArray<T, t_nDim>::TIdx;

		_SVector<T, t_nDim> vX;
		vX.ForEachElementIdx([&vA, &xB](T& xValue, TIdx i)
		{
			xValue = vA[i] + xB;
		});
		return vX;
	}

	template<class T, uint32_t t_nDim>
	__CUDA_HDI__ _SVector<T, t_nDim> operator+(T xB, const _SVector<T, t_nDim>& vA)
	{
		using TIdx = typename _SArray<T, t_nDim>::TIdx;

		_SVector<T, t_nDim> vX;
		vX.ForEachElementIdx([&vA, &xB](T& xValue, TIdx i)
		{
			xValue = vA[i] + xB;
		});
		return vX;
	}


	template<class T, uint32_t t_nDim>
	__CUDA_HDI__ _SVector<T, t_nDim> operator*(const _SVector<T, t_nDim>& vA, T xB)
	{
		using TIdx = typename _SArray<T, t_nDim>::TIdx;

		_SVector<T, t_nDim> vX;
		vX.ForEachElementIdx([&vA, &xB](T& xValue, TIdx i)
		{
			xValue = vA[i] * xB;
		});
		return vX;
	}

	template<class T, uint32_t t_nDim>
	__CUDA_HDI__ _SVector<T, t_nDim> operator*(T xB, const _SVector<T, t_nDim>& vA)
	{
		using TIdx = typename _SArray<T, t_nDim>::TIdx;

		_SVector<T, t_nDim> vX;
		vX.ForEachElementIdx([&vA, &xB](T& xValue, TIdx i)
		{
			xValue = vA[i] * xB;
		});
		return vX;
	}


	template<class T, uint32_t t_nDim>
	__CUDA_HDI__ _SVector<T, t_nDim> operator-(const _SVector<T, t_nDim>& vA, T xB)
	{
		using TIdx = typename _SArray<T, t_nDim>::TIdx;

		_SVector<T, t_nDim> vX;
		vX.ForEachElementIdx([&vA, &xB](T& xValue, TIdx i)
		{
			xValue = vA[i] - xB;
		});
		return vX;
	}

	template<class T, uint32_t t_nDim>
	__CUDA_HDI__ _SVector<T, t_nDim> operator-(T xB, const _SVector<T, t_nDim>& vA)
	{
		using TIdx = typename _SArray<T, t_nDim>::TIdx;

		_SVector<T, t_nDim> vX;
		vX.ForEachElementIdx([&vA, &xB](T& xValue, TIdx i)
		{
			xValue = xB - vA[i];
		});
		return vX;
	}

	template<class T, uint32_t t_nDim>
	__CUDA_HDI__ _SVector<T, t_nDim> operator/(const _SVector<T, t_nDim>& vA, T xB)
	{
		using TIdx = typename _SArray<T, t_nDim>::TIdx;

		_SVector<T, t_nDim> vX;
		vX.ForEachElementIdx([&vA, &xB](T& xValue, TIdx i)
		{
			xValue = vA[i] / xB;
		});
		return vX;
	}

	template<class T, uint32_t t_nDim>
	__CUDA_HDI__ _SVector<T, t_nDim> operator/(T xB, const _SVector<T, t_nDim>& vA)
	{
		using TIdx = typename _SArray<T, t_nDim>::TIdx;

		_SVector<T, t_nDim> vX;
		vX.ForEachElementIdx([&vA, &xB](T& xValue, TIdx i)
		{
			xValue = xB / vA[i];
		});
		return vX;
	}



	template<class T, uint32_t t_nDim>
	__CUDA_HDI__ T Sum(const _SVector<T, t_nDim>& vA)
	{
		T tVal = T(0);

		vA.ForEachElement([&tVal](const T& xValue)
		{
			tVal += xValue;
		});

		return tVal;
	}

	template<class T, uint32_t t_nDim>
	__CUDA_HDI__ T SumOfSquares(const _SVector<T, t_nDim>& vA)
	{
		T tVal = T(0);

		vA.ForEachElement([&tVal](const T& xValue)
		{
			tVal += xValue * xValue;
		});

		return tVal;
	}


	template<class T, uint32_t t_nDim>
	bool IsNumber(const _SVector<T, t_nDim>& vA)
	{
		return vA.ForEachElementTest([](const T& tValue) -> bool
				{
					return IsNumber(tValue);
				});
	}

	template<class T, uint32_t t_nDim>
	bool IsFiniteNumber(const _SVector<T, t_nDim>& vA)
	{
		return vA.ForEachElementTest([](const T& tValue) -> bool
				{
					return IsFiniteNumber(tValue);
				});
	}
#pragma endregion



	// /////////////////////////////////////////////////////////////////////////////////////////////
	// /////////////////////////////////////////////////////////////////////////////////////////////
	// /////////////////////////////////////////////////////////////////////////////////////////////

#pragma region Specialized Vectors

	template<typename _TValue>
	struct _SVector1 : public _SVector<_TValue, 1>
	{
		__CUDA_HDI__ TValue& x()
		{
			return pData[0];
		}

		__CUDA_HDI__ const TValue& x() const
		{
			return pData[0];
		}

		__CUDA_HDI__ TThis& operator= (const TBase& vA)
		{
			TBase::Assign(vA);
			return *this;
		}
	};

	template<typename _TValue>
	struct _SVector2 : public _SVector<_TValue, 2>
	{
		__CUDA_HDI__ TValue& x()
		{
			return pData[0];
		}

		__CUDA_HDI__ const TValue& x() const
		{
			return pData[0];
		}

		__CUDA_HDI__ TValue& y()
		{
			return pData[1];
		}

		__CUDA_HDI__ const TValue& y() const
		{
			return pData[1];
		}

		__CUDA_HDI__ TThis& operator= (const TBase& vA)
		{
			TBase::Assign(vA);
			return *this;
		}
	};

	template<typename _TValue>
	struct _SVector3 : public _SVector<_TValue, 3>
	{
		__CUDA_HDI__ TValue& x()
		{
			return pData[0];
		}

		__CUDA_HDI__ const TValue& x() const
		{
			return pData[0];
		}

		__CUDA_HDI__ TValue& y()
		{
			return pData[1];
		}

		__CUDA_HDI__ const TValue& y() const
		{
			return pData[1];
		}

		__CUDA_HDI__ TValue& z()
		{
			return pData[2];
		}

		__CUDA_HDI__ const TValue& z() const
		{
			return pData[2];
		}

		__CUDA_HDI__ _SVector2<TValue> xy() const
		{
			_SVector2<TValue> vX;
			vX.SetElements(pData[0], pData[1]);
			return vX;
		}

		__CUDA_HDI__ _SVector2<TValue> xz() const
		{
			_SVector2<TValue> vX;
			vX.SetElements(pData[0], pData[2]);
			return vX;
		}

		__CUDA_HDI__ _SVector2<TValue> yz() const
		{
			_SVector2<TValue> vX;
			vX.SetElements(pData[1], pData[2]);
			return vX;
		}

		__CUDA_HDI__ TThis& operator= (const TBase& vA)
		{
			TBase::Assign(vA);
			return *this;
		}
	};

	template<typename _TValue>
	struct _SVector4 : public _SVector<_TValue, 4>
	{
		__CUDA_HDI__ TValue& x()
		{
			return pData[0];
		}

		__CUDA_HDI__ const TValue& x() const
		{
			return pData[0];
		}

		__CUDA_HDI__ TValue& y()
		{
			return pData[1];
		}

		__CUDA_HDI__ const TValue& y() const
		{
			return pData[1];
		}

		__CUDA_HDI__ TValue& z()
		{
			return pData[2];
		}

		__CUDA_HDI__ const TValue& z() const
		{
			return pData[2];
		}

		__CUDA_HDI__ TValue& w()
		{
			return pData[3];
		}

		__CUDA_HDI__ const TValue& w() const
		{
			return pData[3];
		}

		__CUDA_HDI__ _SVector2<TValue> xy() const
		{
			_SVector2<TValue> vX;
			vX.SetElements(pData[0], pData[1]);
			return vX;
		}

		__CUDA_HDI__ _SVector2<TValue> xz() const
		{
			_SVector2<TValue> vX;
			vX.SetElements(pData[0], pData[2]);
			return vX;
		}

		__CUDA_HDI__ _SVector2<TValue> xw() const
		{
			_SVector2<TValue> vX;
			vX.SetElements(pData[0], pData[3]);
			return vX;
		}

		__CUDA_HDI__ _SVector2<TValue> yz() const
		{
			_SVector2<TValue> vX;
			vX.SetElements(pData[1], pData[2]);
			return vX;
		}

		__CUDA_HDI__ _SVector2<TValue> yw() const
		{
			_SVector2<TValue> vX;
			vX.SetElements(pData[1], pData[3]);
			return vX;
		}

		__CUDA_HDI__ _SVector2<TValue> zw() const
		{
			_SVector2<TValue> vX;
			vX.SetElements(pData[2], pData[3]);
			return vX;
		}

		__CUDA_HDI__ _SVector3<TValue> xyz() const
		{
			_SVector3<TValue> vX;
			vX.SetElements(pData[0], pData[1], pData[2]);
			return vX;
		}

		__CUDA_HDI__ _SVector3<TValue> xyw() const
		{
			_SVector3<TValue> vX;
			vX.SetElements(pData[0], pData[1], pData[3]);
			return vX;
		}

		__CUDA_HDI__ _SVector3<TValue> xzw() const
		{
			_SVector3<TValue> vX;
			vX.SetElements(pData[0], pData[2], pData[3]);
			return vX;
		}

		__CUDA_HDI__ _SVector3<TValue> yzw() const
		{
			_SVector3<TValue> vX;
			vX.SetElements(pData[1], pData[2], pData[3]);
			return vX;
		}


		__CUDA_HDI__ TThis& operator= (const TBase& vA)
		{
			TBase::Assign(vA);
			return *this;
		}
};
#pragma endregion


	// /////////////////////////////////////////////////////////////////////////////////////////////
	// /////////////////////////////////////////////////////////////////////////////////////////////
	// /////////////////////////////////////////////////////////////////////////////////////////////

#pragma region Vector classes with Constructors


	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	A vector. </summary>
	///
	/// <remarks>	Perwass </remarks>
	///
	/// <typeparam name="T">	 	Generic type parameter. </typeparam>
	/// <typeparam name="t_nDim">	Type of the dim. </typeparam>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	template<class _TValue, uint32_t t_nDim>
	struct SVector : public _SVector<_TValue, t_nDim>
	{
		using TThis = SVector<_TValue, t_nDim>;
		using TBase = _SVector<_TValue, t_nDim>;

		__CUDA_HDI__ SVector()
		{}

		__CUDA_HDI__ SVector(const TThis& vA)
		{
			*this = vA;
		}

		__CUDA_HDI__ SVector(const TBase& vA)
		{
			TBase::Assign(vA);
		}

		__CUDA_HDI__ SVector(TValue(&pData)[t_nDim])
		{
			TBase::Assign(pData);
		}

		template<typename... TPars>
		__CUDA_HDI__ SVector(TValue xValue, TPars&&... xPars)
		{
			SetZero();
			TBase::SetElements(xValue, xPars...);
		}

		__CUDA_HDI__ TThis& operator= (const TThis& vA)
		{
			TBase::Assign(vA);
			return *this;
		}
	};


	template<class _TValue>
	struct SVector1 : public _SVector1<_TValue>
	{
		using TThis = SVector1<_TValue>;
		using TBase = _SVector1<_TValue>;

		__CUDA_HDI__ SVector1()
		{}

		__CUDA_HDI__ SVector1(const TThis& vA)
		{
			*this = vA;
		}

		__CUDA_HDI__ SVector1(const TBase& vA)
		{
			TBase::Assign(vA);
		}

		__CUDA_HDI__ SVector1(TValue xVal1)
		{
			SetElements(xVal1);
		}

		__CUDA_HDI__ TThis& operator= (const TThis& vA)
		{
			TBase::Assign(vA);
			return *this;
		}

		__CUDA_HDI__ TThis& operator= (const TBase& vA)
		{
			TBase::Assign(vA);
			return *this;
		}
	};

	template<class _TValue>
	struct SVector2 : public _SVector2<_TValue>
	{
		__CUDA_HDI__ SVector2()
		{}

		__CUDA_HDI__ SVector2(const TThis& vA)
		{
			*this = vA;
		}

		__CUDA_HDI__ SVector2(const TBase& vA)
		{
			TBase::Assign(vA);
		}

		__CUDA_HDI__ SVector2(TValue xVal1, TValue xVal2)
		{
			SetElements(xVal1, xVal2);
		}

		__CUDA_HDI__ TThis& operator= (const TThis& vA)
		{
			TBase::Assign(vA);
			return *this;
		}

		__CUDA_HDI__ TThis& operator= (const TBase& vA)
		{
			TBase::Assign(vA);
			return *this;
		}
	};

	template<class _TValue>
	struct SVector3 : public _SVector3<_TValue>
	{
		__CUDA_HDI__ SVector3()
		{}

		__CUDA_HDI__ SVector3(const TThis& vA)
		{
			*this = vA;
		}

		__CUDA_HDI__ SVector3(const TBase& vA)
		{
			TBase::Assign(vA);
		}

		__CUDA_HDI__ SVector3(TValue xVal1, TValue xVal2, TValue xVal3)
		{
			SetElements(xVal1, xVal2, xVal3);
		}

		__CUDA_HDI__ TThis& operator= (const TThis& vA)
		{
			TBase::Assign(vA);
			return *this;
		}

		__CUDA_HDI__ TThis& operator= (const TBase& vA)
		{
			TBase::Assign(vA);
			return *this;
		}
	};

	template<class _TValue>
	struct SVector4 : public _SVector4<_TValue>
	{
		__CUDA_HDI__ SVector4()
		{}

		__CUDA_HDI__ SVector4(const TThis& vA)
		{
			*this = vA;
		}

		__CUDA_HDI__ SVector4(const TBase& vA)
		{
			TBase::Assign(vA);
		}

		__CUDA_HDI__ SVector4(TValue xVal1, TValue xVal2, TValue xVal3, TValue xVal4)
		{
			SetElements(xVal1, xVal2, xVal3, xVal4);
		}

		__CUDA_HDI__ TThis& operator= (const TThis& vA)
		{
			TBase::Assign(vA);
			return *this;
		}

		__CUDA_HDI__ TThis& operator= (const TBase& vA)
		{
			TBase::Assign(vA);
			return *this;
		}
	};


#pragma endregion

} // namespace Clu

