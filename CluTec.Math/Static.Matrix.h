////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.Math
// file:      Static.Matrix.h
//
// summary:   Declares the static. matrix class
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

#include <math.h>

#include "CluTec.Base/Defines.h"
#include "Static.Array.h"
#include "Static.Vector.h"


namespace Clu
{
#if defined(__NVCC__)
	// Need to use this extra class to implement a templated index calculation,
	// since the CUDA compiler generates an internal error with the alternative
	// that compiles fine with Visual Studio.

	template<uint32_t t_nRowMajor, uint32_t t_nDim>
	struct _SMatrixIndex
	{
		using TIdx = uint32_t;

		__CUDA_HDI__ static TIdx GetIdx(TIdx nRow, TIdx nCol);
	};

	template<uint32_t t_nDim>
	struct _SMatrixIndex<0, t_nDim>
	{
		using TIdx = uint32_t;
		__CUDA_HDI__ static TIdx GetIdx(TIdx nRow, TIdx nCol)
		{
			return nCol * t_nDim + nRow;
		}
	};

	template<uint32_t t_nDim>
	struct _SMatrixIndex<1, t_nDim>
	{
		using TIdx = uint32_t;
		__CUDA_HDI__ static TIdx GetIdx(TIdx nRow, TIdx nCol)
		{
			return nRow * t_nDim + nCol;
		}
	};
#endif


	template<class _TValue, uint32_t t_nDim, uint32_t t_nRowMajor = 1>
	struct _SMatrix : public _SArray<_TValue, t_nDim * t_nDim>
	{
		using TBase = _SArray<_TValue, t_nDim * t_nDim>;
		using TThis = _SMatrix<_TValue, t_nDim, t_nRowMajor>;

		static const TSize RowCount = t_nDim;
		static const TSize ColCount = t_nDim;
		static const TSize IsRowMajor = t_nRowMajor;
		static const TSize RowStride = (IsRowMajor ? t_nDim : 1);
		static const TSize ColStride = (IsRowMajor ? 1 : t_nDim);

	private:
#if defined(__NVCC__)
		template<int t_nRowMajor>
		__CUDA_HDI__ static TIdx _GetIdx(TIdx nRow, TIdx nCol)
		{
			return _SMatrixIndex<t_nRowMajor, t_nDim>::GetIdx(nRow, nCol);
		}

#else
		template<int t_nRowMajor>
		__CUDA_HDI__ static TIdx _GetIdx(TIdx nRow, TIdx nCol);

		template<>
		__CUDA_HDI__ static TIdx _GetIdx<0>(TIdx nRow, TIdx nCol)
		{
			return nCol * t_nDim + nRow;
		}

		template<>
		__CUDA_HDI__ static TIdx _GetIdx<1>(TIdx nRow, TIdx nCol)
		{
			return nRow * t_nDim + nCol;
		}
#endif

	public:

		__CUDA_HDI__ TThis& operator= (const TThis& xMat)
		{
			TBase::Assign(xMat);
			return *this;
		}

		__CUDA_HDI__ static TIdx GetIdx(TIdx nRow, TIdx nCol)
		{
			CLU_ASSERT(nRow < RowCount);
			CLU_ASSERT(nCol < ColCount);
			return _GetIdx<IsRowMajor>(nRow, nCol);
		}

		__CUDA_HDI__ TValueRef operator() (TIdx nRow, TIdx nCol)
		{
			return pData[GetIdx(nRow, nCol)];
		}

		__CUDA_HDI__ TConstValueRef operator() (TIdx nRow, TIdx nCol) const
		{
			return pData[GetIdx(nRow, nCol)];
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


		__CUDA_HDI__ void SetIdentity()
		{
			SetZero();

			TValuePtr pVal = pData;
			for (TIdx i = 0; i < t_nDim; ++i)
			{
				*pVal = TValue(1);
				pVal += t_nDim + 1;
			}
		}

		template<typename FuncOp>
		__CUDA_HDI__ void ForEachRow(TIdx iCol, FuncOp funcOp)
		{
			for (TIdx iRow = 0; iRow < RowCount; ++iRow)
			{
				funcOp(pData[GetIdx(iRow, iCol)]);
			}
		}

		template<typename FuncOp>
		__CUDA_HDI__ void ForEachRowPair(const TThis& mA, TIdx iCol, FuncOp funcOp)
		{
			for (TIdx iRow = 0; iRow < RowCount; ++iRow)
			{
				funcOp((*this)(iRow, iCol), mA(iRow, iCol));
			}
		}
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Implementation of matrix product with given strides for rows and columns. </summary>
	///
	/// <typeparam name="RowStrideA"> 	Type of the row stride a. </typeparam>
	/// <typeparam name="ColStrideA"> 	Type of the col stride a. </typeparam>
	/// <typeparam name="RowStrideB"> 	Type of the row stride b. </typeparam>
	/// <typeparam name="ColStrideB"> 	Type of the col stride b. </typeparam>
	/// <typeparam name="TValue">	  	Type of the value. </typeparam>
	/// <typeparam name="t_nDim">	  	Type of the dim. </typeparam>
	/// <typeparam name="t_nRowMajor">	Type of the row major. </typeparam>
	/// <param name="matC">	[in,out] The matrix c. </param>
	/// <param name="matA">	The matrix a. </param>
	/// <param name="matB">	The matrix b. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	template<uint32_t RowStrideA, uint32_t ColStrideA, uint32_t RowStrideB, uint32_t ColStrideB
		, typename TValue, uint32_t t_nDim, uint32_t t_nRowMajor>
		__CUDA_HDI__ void MatrixProduct_Impl(_SMatrix<TValue, t_nDim, t_nRowMajor>& matC
		, const _SMatrix<TValue, t_nDim, t_nRowMajor>& matA
		, const _SMatrix<TValue, t_nDim, t_nRowMajor>& matB)
	{
		using TIdx = typename _SArray<TValue, t_nDim>::TIdx;
		using TMat = _SMatrix<TValue, t_nDim, t_nRowMajor>;


#if defined(__NVCC__)
//#	define CLU_MATPROD_SINGLE_LOOP
#	if defined(CLU_MATPROD_SINGLE_LOOP)
		for (TIdx iEl = 0; iEl < TMat::ElementCount; ++iEl)
		{
			TValue xSum = TValue(0);
			for (TIdx iIdx = 0; iIdx < TMat::ColCount; ++iIdx)
			{
				xSum += matA[(iEl / TMat::ColCount) * RowStrideA + iIdx * ColStrideA]
					* matB[iIdx * RowStrideB + (iEl % TMat::ColCount) * ColStrideB];
			}
			matC(iEl / TMat::ColCount, iEl % TMat::ColCount) = xSum;
		}
#	else
		for (TIdx iRowA = 0; iRowA < TMat::RowCount; ++iRowA)
		{
			for (TIdx iColB = 0; iColB < TMat::ColCount; ++iColB)
			{
				TValue xSum = TValue(0);
				for (TIdx iIdx = 0; iIdx < TMat::ColCount; ++iIdx)
				{
					xSum += matA[iRowA * RowStrideA + iIdx * ColStrideA]
						* matB[iIdx * RowStrideB + iColB * ColStrideB];
				}
				matC(iRowA, iColB) = xSum;
			}
		}

#	endif
#else
		TMat::TConstValuePtr pA = matA.DataPointer();
		TMat::TConstValuePtr pB = matB.DataPointer();

		for (TIdx iRowA = 0; iRowA < TMat::RowCount; ++iRowA)
		{
			for (TIdx iColB = 0; iColB < TMat::ColCount; ++iColB)
			{

				TMat::TConstValuePtr _pA = pA;
				TMat::TConstValuePtr _pB = pB + iColB * ColStrideB;

				TValue xSum = TValue(0);
				for (TIdx iIdx = 0; iIdx < TMat::ColCount; ++iIdx)
				{
					xSum += (*_pA) * (*_pB);
					_pA += ColStrideA;
					_pB += RowStrideB;
				}
				matC(iRowA, iColB) = xSum;
			}

			pA += RowStrideA;
		}
#endif
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	The matrix product mC = mA * mB </summary>
	///
	/// <param name="matC">	[in,out] The matrix c. </param>
	/// <param name="matA">	The matrix a. </param>
	/// <param name="matB">	The matrix b. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	template<uint32_t t_nIsTransposedA, uint32_t t_nIsTransposedB, typename TValue, uint32_t t_nDim, uint32_t t_nRowMajor>
	__CUDA_HDI__ void MatrixProduct(_SMatrix<TValue, t_nDim, t_nRowMajor>& matC
		, const _SMatrix<TValue, t_nDim, t_nRowMajor>& matA
		, const _SMatrix<TValue, t_nDim, t_nRowMajor>& matB)
	{
		using TMat = _SMatrix<TValue, t_nDim, t_nRowMajor>;

		static const uint32_t RowStrideA = (t_nIsTransposedA ? TMat::ColStride : TMat::RowStride);
		static const uint32_t ColStrideA = (t_nIsTransposedA ? TMat::RowStride : TMat::ColStride);

		static const uint32_t RowStrideB = (t_nIsTransposedB ? TMat::ColStride : TMat::RowStride);
		static const uint32_t ColStrideB = (t_nIsTransposedB ? TMat::RowStride : TMat::ColStride);

		MatrixProduct_Impl<RowStrideA, ColStrideA, RowStrideB, ColStrideB>(matC, matA, matB);
	}


	template<typename TValue, uint32_t t_nDim, uint32_t t_nRowMajor>
	__CUDA_HDI__ _SMatrix<TValue, t_nDim, t_nRowMajor> operator* (
		const _SMatrix<TValue, t_nDim, t_nRowMajor>& matA
		, const _SMatrix<TValue, t_nDim, t_nRowMajor>& matB)
	{
		_SMatrix<TValue, t_nDim, t_nRowMajor> matC;

		MatrixProduct<0, 0>(matC, matA, matB);
		return matC;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Product implementation of matrix with vector. </summary>
	///
	/// <typeparam name="RowStrideA"> 	Type of the row stride a. </typeparam>
	/// <typeparam name="ColStrideA"> 	Type of the col stride a. </typeparam>
	/// <typeparam name="TValue">	  	Type of the value. </typeparam>
	/// <typeparam name="t_nDim">	  	Type of the dim. </typeparam>
	/// <typeparam name="t_nRowMajor">	Type of the row major. </typeparam>
	/// <param name="vC">  	[in,out] The v c. </param>
	/// <param name="matA">	The matrix a. </param>
	/// <param name="vB">  	The v b. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	template<uint32_t RowStrideA, uint32_t ColStrideA
		, typename TValue, uint32_t t_nDim, uint32_t t_nRowMajor>
		__CUDA_HDI__ void MatrixProduct_Impl(_SVector<TValue, t_nDim>& vC
		, const _SMatrix<TValue, t_nDim, t_nRowMajor>& matA
		, const _SVector<TValue, t_nDim>& vB)
	{
		using TIdx = typename _SArray<TValue, t_nDim>::TIdx;
		using TMat = _SMatrix<TValue, t_nDim, t_nRowMajor>;


#if defined(__NVCC__)
		for (TIdx iRowA = 0; iRowA < TMat::RowCount; ++iRowA)
		{
			TValue xSum = TValue(0);
			for (TIdx iIdx = 0; iIdx < TMat::ColCount; ++iIdx)
			{
				xSum += matA[iRowA * RowStrideA + iIdx * ColStrideA]
					* vB[iIdx];
			}
			vC[iRowA] = xSum;
		}
#else
		TMat::TConstValuePtr pA = matA.DataPointer();
		TMat::TConstValuePtr pB = vB.DataPointer();

		for (TIdx iRowA = 0; iRowA < TMat::RowCount; ++iRowA)
		{
			TMat::TConstValuePtr _pA = pA;
			TMat::TConstValuePtr _pB = pB;

			TValue xSum = TValue(0);
			for (TIdx iIdx = 0; iIdx < TMat::ColCount; ++iIdx)
			{
				xSum += (*_pA) * (*_pB);
				_pA += ColStrideA;
				++_pB;
			}
			vC[iRowA] = xSum;

			pA += RowStrideA;
		}
#endif
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Impements vC = matA * vB, where vB and vC are interpreted as column vectors. </summary>
	///
	/// <typeparam name="TValue">	  	Type of the value. </typeparam>
	/// <typeparam name="t_nDim">	  	Type of the dim. </typeparam>
	/// <typeparam name="t_nRowMajor">	Type of the row major. </typeparam>
	/// <param name="vC">  	[in,out] The v c. </param>
	/// <param name="matA">	The matrix a. </param>
	/// <param name="vB">  	The v b. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	template<typename TValue, uint32_t t_nDim, uint32_t t_nRowMajor>
	__CUDA_HDI__ void MatrixProduct(_SVector<TValue, t_nDim>& vC
		, const _SMatrix<TValue, t_nDim, t_nRowMajor>& matA
		, const _SVector<TValue, t_nDim>& vB)
	{
		using TMat = _SMatrix<TValue, t_nDim, t_nRowMajor>;

		MatrixProduct_Impl<TMat::RowStride, TMat::ColStride>(vC, matA, vB);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Implements vC = vB * matA, where vB and vC are interpreted as row vectors. </summary>
	///
	/// <typeparam name="TValue">	  	Type of the value. </typeparam>
	/// <typeparam name="t_nDim">	  	Type of the dim. </typeparam>
	/// <typeparam name="t_nRowMajor">	Type of the row major. </typeparam>
	/// <param name="vC">  	[in,out] The v c. </param>
	/// <param name="vB">  	The v b. </param>
	/// <param name="matA">	The matrix a. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	template<typename TValue, uint32_t t_nDim, uint32_t t_nRowMajor>
	__CUDA_HDI__ void MatrixProduct(_SVector<TValue, t_nDim>& vC
		, const _SVector<TValue, t_nDim>& vB
		, const _SMatrix<TValue, t_nDim, t_nRowMajor>& matA)
	{
		using TMat = _SMatrix<TValue, t_nDim, t_nRowMajor>;

		MatrixProduct_Impl<TMat::ColStride, TMat::RowStride>(vC, matA, vB);
	}


	template<typename TValue, uint32_t t_nDim, uint32_t t_nRowMajor>
	__CUDA_HDI__ _SVector<TValue, t_nDim> operator*(
		const _SMatrix<TValue, t_nDim, t_nRowMajor>& matA
		, const _SVector<TValue, t_nDim>& vB)
	{
		_SVector<TValue, t_nDim> vX;
		MatrixProduct(vX, matA, vB);
		return vX;
	}


	template<typename TValue, uint32_t t_nDim, uint32_t t_nRowMajor>
	__CUDA_HDI__ _SVector<TValue, t_nDim> operator*(
		const _SVector<TValue, t_nDim>& vB
		, const _SMatrix<TValue, t_nDim, t_nRowMajor>& matA)
	{
		_SVector<TValue, t_nDim> vX;
		MatrixProduct(vX, vB, matA);
		return vX;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	A matrix. </summary>
	///
	/// <typeparam name="T">		  	Generic type parameter. </typeparam>
	/// <typeparam name="t_nDim">	  	Type of the dim. </typeparam>
	/// <typeparam name="t_nRowMajor">	Type of the row major. </typeparam>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	template<class _TValue, int t_nDim, int t_nRowMajor = 1>
	struct SMatrix : public _SMatrix<_TValue, t_nDim, t_nRowMajor>
	{
		using TBase = _SMatrix<_TValue, t_nDim, t_nRowMajor>;
		using TThis = SMatrix<_TValue, t_nDim, t_nRowMajor>;

		SMatrix()
		{}

		SMatrix(const TValue pData[ElementCount])
		{
			TBase::Assign(pData);
		}

		SMatrix(const TBase& mA)
		{
			TBase::Assign(mA);
		}

		SMatrix(const TThis& mA)
		{
			*this = mA;
		}

		template<class TValue2>
		explicit SMatrix(const SMatrix<TValue2, t_nDim, t_nRowMajor>& mA)
		{
			TBase::CastFrom(mA);
		}

		TThis& operator=(const TThis& mA)
		{
			TBase::operator= (mA);
			return *this;
		}

	};


}	// namespace Clu
