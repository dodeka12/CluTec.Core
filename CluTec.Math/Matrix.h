////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.Math
// file:      Matrix.h
//
// summary:   Declares the matrix class
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

#define _USE_MATH_DEFINES
#include <math.h>
#include <algorithm>
#include <iostream>
#include <vector>

#include "CluTec.Base/Defines.h"
#include "CluTec.Base/Array.h"

#include "Static.Matrix.h"
#include "Static.Vector.h"

#include "ValuePrecision.h"

namespace Clu
{
	template<class _TValue>
	class CMatrix : public CArray<_TValue>, public CValuePrecision<_TValue>
	{
	public:

		typedef _TValue TValue;
		typedef CMatrix<TValue> TMatrix;
		typedef CArray<TValue> TArray;
		typedef TArray::TIterator TIterator;
		typedef TArray::TConstIterator TConstIterator;
		typedef TArray::TIdx TIdx;

	protected:
		TIdx m_nRowDimIdx;
		TIdx m_nColDimIdx;

	public:
		CMatrix()
		{
			m_nRowDimIdx = 0;
			m_nColDimIdx = 1;
		}

		CMatrix(TValue fPrec) : CValuePrecision(fPrec)
		{
			SetValuePrecision(fPrec);

			m_nRowDimIdx = 0;
			m_nColDimIdx = 1;
		}

		CMatrix(const CMatrix<TValue>&) = default;
		CMatrix<TValue>& operator=(const CMatrix<TValue>&) = default;

		CMatrix(CMatrix<TValue>&& matA) : CArray<TValue>(std::move(matA))
		{
			SetValuePrecision(matA.GetValuePrecision());

			m_nRowDimIdx = matA.m_nRowDimIdx;
			m_nColDimIdx = matA.m_nColDimIdx;
		}

		CMatrix<TValue>& operator=(CMatrix<TValue>&& matA)
		{
			CArray::operator =(std::move(matA));
			
			SetValuePrecision(matA.GetValuePrecision());

			m_nRowDimIdx = matA.m_nRowDimIdx;
			m_nColDimIdx = matA.m_nColDimIdx;

			return *this;
		}

		CMatrix(size_t nRowCnt, size_t nColCnt) : CArray<TValue>({nRowCnt, nColCnt})
		{
			m_nRowDimIdx = 0;
			m_nColDimIdx = 1;
		}

		CMatrix(size_t nRowCnt, size_t nColCnt, const std::initializer_list<TValue>& xData)
			: CArray<TValue>({nRowCnt, nColCnt}, xData)
		{
			m_nRowDimIdx = 0;
			m_nColDimIdx = 1;
		}

		template<uint32_t t_nDim, uint32_t t_nRowMajor>
		CMatrix(const _SMatrix<TValue, t_nDim, t_nRowMajor>& mA)
			: CArray<TValue>({t_nDim, t_nDim})
		{
			m_nRowDimIdx = (t_nRowMajor > 0 ? 0 : 1);
			m_nColDimIdx = (t_nRowMajor > 0 ? 1 : 0);

			memcpy(GetDataPtr(), mA.DataPointer(), mA.ElementCount * sizeof(TValue));
		}

		template<uint32_t t_nDim, uint32_t t_nRowMajor>
		void ToMatrix(_SMatrix<TValue, t_nDim, t_nRowMajor>& mA)
		{
			if (GetRowCount() != t_nDim || GetColCount() != t_nDim)
			{
				throw CLU_EXCEPTION("Matrix dimension does not match target static matrix");
			}

			for (unsigned uRow = 0; uRow < t_nDim; ++uRow)
			{
				for (unsigned uCol = 0; uCol < t_nDim; ++uCol)
				{
					mA(uRow, uCol) = (*this)(uRow, uCol);
				}
			}
		}


		// ////////////////////////////////////////////////////////////
		// ////////////////////////////////////////////////////////////
		void Resize(size_t nRowCnt, size_t nColCnt)
		{
			try
			{
				std::initializer_list<size_t> lSize;

				if (IsTranspose())
				{
					lSize = { nColCnt, nRowCnt };
				}
				else
				{
					lSize = { nRowCnt, nColCnt };
				}

				if (GetTotalSize() == 0)
				{
					TArray::SetSize(lSize);
				}
				else
				{
					TArray::Resize(lSize);
				}
			}
			catch (std::exception &xEx)
			{
				std::string sMsg = "Error resizing matrix:";
				sMsg += xEx.what();

				throw CLU_EXCEPTION(sMsg.c_str());
			}
		}

		// ////////////////////////////////////////////////////////////
		void SetSize(size_t nRowCnt, size_t nColCnt)
		{
			try
			{
				std::initializer_list<size_t> lSize;

				if (IsTranspose())
				{
					lSize = { nColCnt, nRowCnt };
				}
				else
				{
					lSize = { nRowCnt, nColCnt };
				}

				TArray::SetSize(lSize);
			}
			catch (std::exception &xEx)
			{
				std::string sMsg = "Error resizing matrix:";
				sMsg += xEx.what();

				throw CLU_EXCEPTION(sMsg.c_str());
			}
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \brief Set Size of matrix and data.
		///
		/// \author Perwass
		/// \date 11.02.2016
		///
		/// \param	nRowCnt Number of rows.
		/// \param	nColCnt Number of cols.
		/// \param	xData   The data.
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		void SetSize(size_t nRowCnt, size_t nColCnt, const std::initializer_list<TValue>& xData)
		{
			try
			{
				SetSize(nRowCnt, nColCnt);
				SetData(xData);
			}
			catch (std::exception &xEx)
			{
				std::string sMsg = "Error resizing matrix and setting data: ";
				sMsg += xEx.what();

				throw CLU_EXCEPTION(sMsg.c_str());
			}
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \brief Sets data of matrix
		///
		/// \author Perwass
		/// \date 11.02.2016
		///
		/// \param	xData The data.
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		void SetData(const std::initializer_list<TValue>& xData)
		{
			try
			{
				TArray::SetData(xData);
			}
			catch (std::exception &xEx)
			{
				std::string sMsg = "Error setting matrix data: ";
				sMsg += xEx.what();

				throw CLU_EXCEPTION(sMsg.c_str());
			}
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Gets row count. </summary>
		///
		/// <remarks>	Perwass, 10.02.2016. </remarks>
		///
		/// <returns>	The row count. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		size_t GetRowCount() const
		{
			if (IsEmpty())
			{
				return 0;
			}

			return GetSize(m_nRowDimIdx);
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Gets col count. </summary>
		///
		/// <remarks>	Perwass, 10.02.2016. </remarks>
		///
		/// <returns>	The col count. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		size_t GetColCount() const
		{
			if (IsEmpty())
			{
				return 0;
			}

			return GetSize(m_nColDimIdx);
		}



		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Access matrix component. </summary>
		///
		/// <remarks>	Perwass, 10.02.2016. </remarks>
		///
		/// <param name="nRow">	The row. </param>
		/// <param name="nCol">	The col. </param>
		///
		/// <returns>	The result of the operation. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		const TValue& operator()(const size_t nRow, const size_t nCol) const
		{
			CLU_ASSERT(nRow < GetRowCount() && nCol < GetColCount());

			if (IsTranspose())
			{
				return *(GetDataPtr() + (nCol * GetRowCount() + nRow));
			}
			else
			{
				return *(GetDataPtr() + (nRow * GetColCount() + nCol));
			}
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Access matrix component. </summary>
		///
		/// <remarks>	Perwass, 10.02.2016. </remarks>
		///
		/// <param name="nRow">	The row. </param>
		/// <param name="nCol">	The col. </param>
		///
		/// <returns>	The result of the operation. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		TValue& operator()(const size_t nRow, const size_t nCol)
		{
			CLU_ASSERT(nRow < GetRowCount() && nCol < GetColCount());

			if (IsTranspose())
			{
				return *(GetDataPtr() + (nCol * GetRowCount() + nRow));
			}
			else
			{
				return *(GetDataPtr() + (nRow * GetColCount() + nCol));
			}
		}

		// /////////////////////////////////////////////////////////////////////////////////////
		// Iterating functions
		template<typename FuncOp>
		void ForEachComp(FuncOp xFunc)
		{
			// The data is row-ordered in memory, so we need to take the 
			// iterator that walks along a row.
			TIterator itEl = TArray::Begin(1);
			TIterator itEnd = itEl + GetTotalSize();

			for (; itEl != itEnd; ++itEl)
			{
				xFunc(*itEl);
			}
		}

		template<typename FuncOp>
		void ForEachComp(FuncOp xFunc) const
		{
			TConstIterator itEl = TArray::ConstBegin(1);
			TConstIterator itEnd = itEl + GetTotalSize();

			for (; itEl != itEnd; ++itEl)
			{
				xFunc(*itEl);
			}
		}


		template<typename FuncOp>
		bool ForEachCompTest(FuncOp xFunc)
		{
			TIterator itEl = TArray::Begin(1);
			TIterator itEnd = itEl + GetTotalSize();

			for (; itEl != itEnd; ++itEl)
			{
				if (!xFunc(*itEl))
				{
					return false;
				}
			}

			return true;
		}

		template<typename FuncOp>
		bool ForEachCompTest(FuncOp xFunc) const
		{
			TConstIterator itEl = TArray::ConstBegin(1);
			TConstIterator itEnd = itEl + GetTotalSize();

			for (; itEl != itEnd; ++itEl)
			{
				if (!xFunc(*itEl))
				{
					return false;
				}
			}

			return true;
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \brief For each component pair of this matrix and the given matrix. The function iterates row-wise over both matrices and calls
		/// 	   the given function for each component pair at the same (row, col) position in both matrices.
		///
		/// \author Perwass
		/// \date 11.02.2016
		///
		/// \tparam	TValueB Type of the value b.
		/// \tparam	FuncOp  Type of the function operation.
		/// \param	matB  The matrix b.
		/// \param	xFunc The function.
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		template<typename TValueB, typename FuncOp>
		void ForEachCompPair(const CMatrix<TValueB>& matB, FuncOp xFunc)
		{
			if (!IsEqualSize(matB))
			{
				throw CLU_EXCEPTION("Matrices are not of same size");
			}

			typedef CMatrix<TValueB> TMatrixB;

			TIterator itRowA = BeginRows();
			TIterator itRowEndA = itRowA + GetRowCount();

			TMatrixB::TConstIterator itRowB = ConstBeginRows();

			for (; itRowA != itRowEndA; ++itRowA, ++itRowB)
			{
				TIterator itRowColA = BeginCols(itRowA);
				TIterator itRowColEndA = itRowColA + GetColCount();

				TMatrixB::TConstIterator itRowColB = ConstBeginCols(itRowB);
				for (; itRowColA != itRowColEndA; ++itRowColA, ++itRowColB)
				{
					xFunc(*itRowColA, *itRowColB);
				}
			}
		}

		template<typename TValueB, typename FuncOp>
		void ForEachCompPair(const CMatrix<TValueB>& matB, FuncOp xFunc) const
		{
			if (!IsEqualSize(matB))
			{
				throw CLU_EXCEPTION("Matrices are not of same size");
			}

			typedef CMatrix<TValueB> TMatrixB;

			TConstIterator itRowA = ConstBeginRows();
			TConstIterator itRowEndA = itRowA + GetRowCount();

			TMatrixB::TConstIterator itRowB = ConstBeginRows();

			for (; itRowA != itRowEndA; ++itRowA, ++itRowB)
			{
				TConstIterator itRowColA = ConstBeginCols(itRowA);
				TConstIterator itRowColEndA = itRowColA + GetColCount();

				TMatrixB::TConstIterator itRowColB = ConstBeginCols(itRowB);
				for (; itRowColA != itRowColEndA; ++itRowColA, ++itRowColB)
				{
					xFunc(*itRowColA, *itRowColB);
				}
			}
		}

		template<typename TValueB, typename FuncOp>
		bool ForEachCompPairTest(const CMatrix<TValueB>& matB, FuncOp xFunc)
		{
			if (!IsEqualSize(matB))
			{
				throw CLU_EXCEPTION("Matrices are not of same size");
			}

			typedef CMatrix<TValueB> TMatrixB;

			TIterator itRowA = BeginRows();
			TIterator itRowEndA = itRowA + GetRowCount();

			TMatrixB::TConstIterator itRowB = ConstBeginRows();

			for (; itRowA != itRowEndA; ++itRowA, ++itRowB)
			{
				TIterator itRowColA = BeginCols(itRowA);
				TIterator itRowColEndA = itRowColA + GetColCount();

				TMatrixB::TConstIterator itRowColB = ConstBeginCols(itRowB);
				for (; itRowColA != itRowColEndA; ++itRowColA, ++itRowColB)
				{
					if (!xFunc(*itRowColA, *itRowColB))
					{
						return false;
					}
				}
			}

			return true;
		}

		template<typename TValueB, typename FuncOp>
		bool ForEachCompPairTest(const CMatrix<TValueB>& matB, FuncOp xFunc) const
		{
			if (!IsEqualSize(matB))
			{
				throw CLU_EXCEPTION("Matrices are not of same size");
			}

			typedef CMatrix<TValueB> TMatrixB;

			TConstIterator itRowA = ConstBeginRows();
			TConstIterator itRowEndA = itRowA + GetRowCount();

			TMatrixB::TConstIterator itRowB = ConstBeginRows();

			for (; itRowA != itRowEndA; ++itRowA, ++itRowB)
			{
				TConstIterator itRowColA = ConstBeginCols(itRowA);
				TConstIterator itRowColEndA = itRowColA + GetColCount();

				TMatrixB::TConstIterator itRowColB = ConstBeginCols(itRowB);
				for (; itRowColA != itRowColEndA; ++itRowColA, ++itRowColB)
				{
					if (!xFunc(*itRowColA, *itRowColB))
					{
						return false;
					}
				}
			}

			return true;
		}


		template<typename FuncOp>
		void ForEachRow(FuncOp xFunc)
		{
			TIterator itEl = BeginRows();
			TIterator itEnd = itEl + GetRowCount();

			for (; itEl != itEnd; ++itEl)
			{
				xFunc(itEl);
			}
		}

		template<typename FuncOp>
		void ForEachCol(FuncOp xFunc)
		{
			TIterator itEl = BeginCols();
			TIterator itEnd = itEl + GetColCount();

			for (; itEl != itEnd; ++itEl)
			{
				xFunc(itEl);
			}
		}

		template<typename FuncOp>
		void ForEachRow(FuncOp xFunc) const
		{
			TConstIterator itEl = ConstBeginRows();
			TConstIterator itEnd = itEl + GetRowCount();

			for (; itEl != itEnd; ++itEl)
			{
				xFunc(itEl);
			}
		}

		template<typename FuncOp>
		void ForEachCol(FuncOp xFunc) const
		{
			TConstIterator itEl = ConstBeginCols();
			TConstIterator itEnd = itEl + GetColCount();

			for (; itEl != itEnd; ++itEl)
			{
				xFunc(itEl);
			}
		}


		template<typename FuncOp>
		void ForEachRow(TIterator& itStart, TIdx nRowCnt, FuncOp xFunc)
		{
			TIterator itEl = BeginRows(itStart);
			TIterator itEnd = itEl + nRowCnt;

			for (; itEl != itEnd; ++itEl)
			{
				xFunc(itEl);
			}
		}

		template<typename FuncOp>
		void ForEachCol(TIterator& itStart, TIdx nColCnt, FuncOp xFunc)
		{
			TIterator itEl = BeginCols(itStart);
			TIterator itEnd = itEl + nColCnt;

			for (; itEl != itEnd; ++itEl)
			{
				xFunc(itEl);
			}
		}

		template<typename FuncOp>
		void ForEachRow(TConstIterator& itStart, TIdx nRowCnt, FuncOp xFunc) const
		{
			TConstIterator itEl = ConstBeginRows(itStart);
			TConstIterator itEnd = itEl + nRowCnt;

			for (; itEl != itEnd; ++itEl)
			{
				xFunc(itEl);
			}
		}

		template<typename FuncOp>
		void ForEachCol(TConstIterator& itStart, TIdx nColCnt, FuncOp xFunc) const
		{
			TConstIterator itEl = ConstBeginCols(itStart);
			TConstIterator itEnd = itEl + nColCnt;

			for (; itEl != itEnd; ++itEl)
			{
				xFunc(itEl);
			}
		}


		TIterator BeginRows()
		{
			return TArray::Begin(m_nRowDimIdx);
		}

		TIterator BeginCols()
		{
			return TArray::Begin(m_nColDimIdx);
		}

		TConstIterator ConstBeginRows() const
		{
			return TArray::ConstBegin(m_nRowDimIdx);
		}

		TConstIterator ConstBeginCols() const
		{
			return TArray::ConstBegin(m_nColDimIdx);
		}


		TIterator BeginRows(TIterator& itEl)
		{
			return TArray::Begin(itEl, m_nRowDimIdx);
		}

		TIterator BeginCols(TIterator& itEl)
		{
			return TArray::Begin(itEl, m_nColDimIdx);
		}

		TConstIterator ConstBeginRows(TConstIterator& itEl) const
		{
			return TArray::ConstBegin(itEl, m_nRowDimIdx);
		}

		TConstIterator ConstBeginCols(TConstIterator& itEl) const
		{
			return TArray::ConstBegin(itEl, m_nColDimIdx);
		}


		TIterator BeginRows(TIdx nRowIdx, TIdx nColIdx)
		{
			return TArray::Begin(_GetIndexVector(nRowIdx, nColIdx), m_nRowDimIdx);
		}

		TIterator BeginCols(TIdx nRowIdx, TIdx nColIdx)
		{
			return TArray::Begin(_GetIndexVector(nRowIdx, nColIdx), m_nColDimIdx);
		}

		TConstIterator ConstBeginRows(TIdx nRowIdx, TIdx nColIdx) const
		{
			return TArray::ConstBegin(_GetIndexVector(nRowIdx, nColIdx), m_nRowDimIdx);
		}

		TConstIterator ConstBeginCols(TIdx nRowIdx, TIdx nColIdx) const
		{
			return TArray::ConstBegin(_GetIndexVector(nRowIdx, nColIdx), m_nColDimIdx);
		}

		TIterator BeginRowBlock(TIdx nRowCnt)
		{
			if (IsTranspose())
			{
				return TIterator(GetDataPtr(), nRowCnt);
			}
			else
			{
				return TIterator(GetDataPtr(), nRowCnt * GetColCount());
			}
		}

		TIterator BeginColBlock(TIdx nColCnt)
		{
			if (IsTranspose())
			{
				return TIterator(GetDataPtr(), nColCnt * GetRowCount());
			}
			else
			{
				return TIterator(GetDataPtr(), nColCnt);
			}
		}

		TConstIterator ConstBeginRowBlock(TIdx nRowCnt) const
		{
			if (IsTranspose())
			{
				return TConstIterator(GetDataPtr(), nRowCnt);
			}
			else
			{
				return TConstIterator(GetDataPtr(), nRowCnt * GetColCount());
			}
		}

		TConstIterator ConstBeginColBlock(TIdx nColCnt) const
		{
			if (IsTranspose())
			{
				return TConstIterator(GetDataPtr(), nColCnt * GetRowCount());
			}
			else
			{
				return TConstIterator(GetDataPtr(), nColCnt);
			}
		}


		TIterator BeginDiagonal()
		{
			return TIterator(GetDataPtr(), GetSize(1)+1);
		}

		TIterator EndDiagonal()
		{
			return TIterator(GetDataPtr() + (GetSize(1) + 1) * std::min(GetRowCount(), GetColCount()), GetSize(1) + 1);
		}

		TConstIterator ConstBeginDiagonal() const
		{
			return TConstIterator(GetDataPtr(), GetSize(1) + 1);
		}

		TConstIterator ConstEndDiagonal() const
		{
			return TConstIterator(GetDataPtr(), (GetSize(1) + 1) * std::min(GetRowCount(), GetColCount()));
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// 	Sets matrix to identity matrix, if non-quadratic, then upper left is identity.
		/// </summary>
		///
		/// <remarks>	Perwass, 10.02.2016. </remarks>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		void SetIdentity()
		{
			Zero();
			TIterator itEl = BeginDiagonal();
			TIterator itEnd = EndDiagonal();

			for (; itEl != itEnd; ++itEl)
			{
				*itEl = TValue(1);
			}
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Gets the trace of the matrix. </summary>
		///
		/// <remarks>	Perwass, 10.02.2016. </remarks>
		///
		/// <returns>	A TValue. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		TValue Trace() const
		{
			TConstIterator itEl = ConstBeginDiagonal();
			TConstIterator itEnd = ConstEndDiagonal();

			TValue tTrace = TValue(0);
			for (; itEl != itEnd; ++itEl)
			{
				tTrace += *itEl;
			}

			return tTrace;
		}

		// /////////////////////////////////////////////////////////////////////////////////////
		// Set all components to zero
		void Zero()
		{
			CLU_ASSERT(GetDataPtr() != nullptr);

			if (GetTotalByteSize() == 0)
			{
				return;
			}

			memset((void*) GetDataPtr(), 0, GetTotalByteSize());
		}



		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Negates this object. </summary>
		///
		/// <remarks>	Perwass, 10.02.2016. </remarks>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		void Negate()
		{
			ForEachComp([](TValue &tValue)
			{
				tValue = -tValue;
			});
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \brief Query if this matrix is transposed with respect to its memory representation. When applying the Transpose() function to the matrix
		/// 	   only the m_nRowDimIdx and m_nColDimIdx variables swap their values. When accessing the matrix components via the
		/// 	   iterators the matrix is effectively transposed without changing its representation in memory.
		///
		/// \author Perwass
		/// \date 11.02.2016
		///
		/// \return true if transpose, false if not.
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		bool IsTranspose() const
		{
			return m_nRowDimIdx == 1;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Query if this object is zero. </summary>
		///
		/// <remarks>	Perwass, 10.02.2016. </remarks>
		///
		/// <returns>	true if zero, false if not. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		bool IsZero() const
		{
			ForEachCompTest([this](const TValue& tValue)
			{
				if (!CValuePrecision<TValue>::IsZero(tValue))
				{
					return false;
				}

				return true;
			});

			return true;
		}


		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \brief Query if all components of matrix are numbers.
		///
		/// \author Perwass
		/// \date 11.02.2016
		///
		/// \tparam	TValue Type of the value.
		///
		/// \return true if number, false if not.
		///
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		template<typename TValue>
		bool IsNumber() const
		{
			return ForEachCompTest([](const TValue& tValue)
			{
				if (!IsNumber(tValue))
				{
					return false;
				}
				return true;

			});
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \brief Query if all components of the matrix are finite numbers.
		///
		/// \author Perwass
		/// \date 11.02.2016
		///
		/// \tparam	TValue Type of the value.
		///
		/// \return true if finite number, false if not.
		///
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		template<typename TValue>
		bool IsFiniteNumber() const
		{
			return ForEachCompTest([](const TValue& tValue)
			{
				if (!IsFiniteNumber(tValue))
				{
					return false;
				}
				return true;

			});
		}



		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Query if 'matB' is equal size. </summary>
		///
		/// <remarks>	Perwass, 10.02.2016. </remarks>
		///
		/// <param name="matB">	The matrix b. </param>
		///
		/// <returns>	true if equal size, false if not. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		bool IsEqualSize(const TMatrix& matB) const
		{
			return (GetRowCount() == matB.GetRowCount() && GetColCount() == matB.GetColCount());
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Magnitude squared. </summary>
		///
		/// <remarks>	Perwass, 10.02.2016. </remarks>
		///
		/// <returns>	A TValue. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		TValue MagnitudeSquared() const
		{
			TValue tMagSq = 0;

			ForEachComp([&tMagSq](const TValue &tValue)
			{
				tMagSq += tValue * tValue;
			});

			return tMagSq;
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \brief Performs transpose of this matrix in memory and returns result.
		///
		/// \author Perwass
		/// \date 11.02.2016
		///
		/// \return The transpose.
		///
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		CMatrix<TValue> GetTranspose() const
		{
			CMatrix<TValue> matB(GetColCount(), GetRowCount());

			TIterator itColB = matB.BeginCols();
			ForEachRow([&](TConstIterator& itRowA)
			{
				TIterator itColRowB = matB.BeginRows(itColB);
				TConstIterator itRowColA = ConstBeginCols(itRowA);
				TConstIterator itRowColEndA = itRowColA + GetColCount();

				for (; itRowColA != itRowColEndA; ++itRowColA, ++itColRowB)
				{
					*itColRowB = *itRowColA;
				}

				++itColB;
			});

			return matB;
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \brief Transposes this matrix. This function only indicates that the matrix is transposed but does not change its
		/// 	   representation in memory. Use the function ApplyToMemory() to actually represent transposition in memory.
		///
		/// \author Perwass
		/// \date 11.02.2016
		///
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		TMatrix& Transpose()
		{
			if (IsTranspose())
			{
				m_nRowDimIdx = 0;
				m_nColDimIdx = 1;
			}
			else
			{
				m_nRowDimIdx = 1;
				m_nColDimIdx = 0;
			}

			return *this;
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \brief Applies a transposition of this matrix that is only represented by iterators to memory.
		///
		/// \author Perwass
		/// \date 11.02.2016
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		void ApplyToMemory()
		{
			if (!IsTranspose())
			{
				return;
			}

			// transpose back
			Transpose();

			// Now get the transpose in memory
			*this = GetTranspose();
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// 	Set all vecValues A(ij) smaller than fPrec*max( abs(A(ij)) ) to zero. 100*fPrec gives
		/// 	relative threshold in percent.
		/// </summary>
		///
		/// <remarks>	Perwass, 10.02.2016. </remarks>
		///
		/// <param name="tPrec">	The prec. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		void TinyToZero(TValue tPrec = TValue(0))
		{
			CLU_ASSERT(GetTotalSize() > 0);

			if (tPrec <= TValue(0))
			{
				tPrec = Clu::CValuePrecision<TValue>::DefaultPrecision();
			}

			TValue tBig = TValue(0);
			TValue tH;

			ForEachComp([&](TValue& tValue)
			{
				if ((tH = _Abs(tValue)) > tBig)
				{
					tBig = tH;
				}
			});

			tBig *= tPrec;
			ForEachComp([&](TValue& tValue)
			{
				if (_Abs(tValue) <= tBig)
				{
					tValue = TValue(0);
				}
			});

		}


		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Invert components of matrix. Zero vecValues are set to inf. </summary>
		///
		/// <remarks>	Perwass, 10.02.2016. </remarks>
		///
		/// <param name="tInf"> 	The inf. </param>
		/// <param name="tPrec">	The prec. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		CMatrix<TValue>& CompInvert(TValue tInf, TValue tPrec = TValue(0))
		{
			CLU_ASSERT(GetTotalSize() > 0);

			if (tPrec <= TValue(0))
			{
				tPrec = CValuePrecision<TValue>::GetValuePrecision();
			}

			ForEachComp([&](TValue& tValue)
			{
				if (!_IsZero(tValue, tPrec))
				{
					tValue = TValue(1) / tValue;
				}
				else
				{
					tValue = tInf;
				}

			});

			return *this;
		}


		// /////////////////////////////////////////////////////////////////////////////////////
		// returns the componentwise product

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Component multiply. </summary>
		///
		/// <remarks>	Perwass, 10.02.2016. </remarks>
		///
		/// <param name="matB">	The matrix b. </param>
		///
		/// <returns>	A CMatrix&lt;TValue&gt; </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		TMatrix& CompMultiply(const TMatrix& matB) 
		{
			if (!IsEqualSize(matB))
			{
				throw CLU_EXCEPTION("Matrix dimensions do not agree");
			}

			ForEachCompPair(matB, [](TValue& tValA, const TValue& tValB)
			{
				tValA *= tValB;
			});

			return *this;
		}


		//////////////////////////// Arithmetic ////////////////////

		TMatrix& operator+=(const TMatrix& matB)
		{
			if (!IsEqualSize(matB))
			{
				throw CLU_EXCEPTION("Matrix dimensions do not agree");
			}

			ForEachCompPair(matB, [](TValue& tValA, const TValue& tValB)
			{
				tValA += tValB;
			});

			return *this;
		}

		TMatrix& operator+=(const TValue& tScalar)
		{
			ForEachComp([&tScalar](TValue& tValue)
			{
				tValue += tScalar;
			});

			return *this;
		}


		TMatrix& operator-=(const CMatrix<TValue>& matB)
		{
			if (!IsEqualSize(matB))
			{
				throw CLU_EXCEPTION("Matrix dimensions do not agree");
			}

			ForEachCompPair(matB, [](TValue& tValA, const TValue& tValB)
			{
				tValA -= tValB;
			});

			return *this;
		}

		TMatrix& operator-=(const TValue& tScalar)
		{
			ForEachComp([&tScalar](TValue& tValue)
			{
				tValue -= tScalar;
			});

			return *this;
		}


		TMatrix& operator*=(const TValue& tScalar)
		{
			ForEachComp([&tScalar](TValue& tValue)
			{
				tValue *= tScalar;
			});

			return *this;
		}


		TMatrix& operator/=(const TValue& tScalar)
		{
			ForEachComp([&tScalar](TValue& tValue)
			{
				tValue /= tScalar;
			});

			return *this;
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \brief Transpose of matrix. Indicates that the matrix is transposed and the returns a copy.
		///
		/// \author Perwass
		/// \date 11.02.2016
		///
		/// \return The result of the operation.
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		TMatrix operator~()
		{
			TMatrix matA(*this);

			matA.Transpose();
			return matA;
		}

		///////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \brief Applies the given congruence map to each component.
		///
		/// \author Perwass
		/// \date 11.02.2016
		///
		/// \tparam	TCongruence Type of the congruence.
		/// \param	xCongruence The congruence.
		///
		/// \return Reference to this.
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		template<typename TCongruence>
		TMatrix& CompCongruence(const TCongruence& xCongruence)
		{
			ForEachComp([&xCongruence](TValue& tValue)
			{
				TValue _tValue = tValue;
				if (!xCongruence.Map(tValue, _tValue))
				{
					throw CLU_EXCEPTION("Error applying congruence map to matrix component");
				}
			});

			return *this;
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \brief Attempts to apply the given inverse congruence map to each component.
		///
		/// \author Perwass
		/// \date 11.02.2016
		///
		/// \tparam	TCongruence Type of the congruence.
		/// \param	xCongruence The congruence.
		///
		/// \return true if it succeeds, false if it fails.
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		template<typename TCongruence>
		bool TryCompInverseCongruence(const TCongruence& xCongruence)
		{
			return ForEachCompTest([&xCongruence](TValue& tValue)
			{
				TValue _tValue = tValue;
				if (!xCongruence.InvMap(tValue, _tValue))
				{
					return false;
				}

				return true;
			});
		}


		///////////////////////////////////////////////////////////////////
		template<class TValueB>
		CMatrix<TValue>& CastMemberType(const CMatrix<TValueB>& matB)
		{
			try
			{
				if (matB.GetTotalSize() == 0)
				{
					Reset();
				}
				else
				{
					SetSize(matB.GetRowCount(), matB.GetColCount());
					ForEachCompPair(matB, [](TValue& tValA, const TValueB& tValB)
					{
						tValA = TValue(tValB);
					});
				}
			}
			catch (std::exception &xEx)
			{
				throw CLU_EXCEPTION_NEST("Error casting matrix component types", std::move(xEx));
			}

			return *this;
		}



		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Makes a diagonal matrix out of a single row or single column matrix. </summary>
		///
		/// <remarks>	Perwass, 10.02.2016. </remarks>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		TMatrix& VectorToDiagonal()
		{
			try
			{
				CLU_ASSERT(GetTotalSize() > 0);

				TIdx nRowCnt = GetRowCount();
				TIdx nColCnt = GetColCount();

				if ((nRowCnt > 1) && (nColCnt > 1))
				{
					throw CLU_EXCEPTION("Invalid matrix size");
				}

				CMatrix<TValue> matB(*this);

				TIdx nSize = (nRowCnt == 1 ? nColCnt : nRowCnt);
				SetSize(nSize, nSize);
				Zero();

				TIterator itEl = BeginDiagonal();
				TIterator itEnd = EndDiagonal();

				TIterator itElB = (nRowCnt == 1 ? matB.BeginCols() : matB.BeginRows());
				for (; itEl != itEnd; ++itEl, ++itElB)
				{
					*itEl = *itElB;
				}
			}
			catch (std::exception &xEx)
			{
				throw CLU_EXCEPTION_NEST("Error transforming vector to diagonal matrix: ", std::move(xEx));
			}

			return *this;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Makes a column vector out of the diagonal. </summary>
		///
		/// <remarks>	Perwass, 10.02.2016. </remarks>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		TMatrix& DiagonalToVector()
		{
			CLU_ASSERT(GetTotalSize() > 0);

			TIdx nRowCnt = GetRowCount();
			TIdx nColCnt = GetColCount();

			TIdx nSize = std::min(nRowCnt, nColCnt);

			TMatrix matB(nSize, 1);

			TIterator itEl = BeginDiagonal();
			TIterator itEnd = EndDiagonal();

			TIterator itElB = matB.BeginRows();

			for (; itEl != itEnd; ++itEl, ++itElB)
			{
				*itEl = *itElB;
			}

			*this = matB;

			return *this;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Swap cols. </summary>
		///
		/// <remarks>	Perwass, 10.02.2016. </remarks>
		///
		/// <param name="nColA">	The col a. </param>
		/// <param name="nColB">	The col b. </param>
		///
		/// <returns>	A TMatrix&amp; </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		TMatrix& SwapCols(TIdx nColA, TIdx nColB)
		{
			if (nColA == nColB)
			{
				return *this;
			}

			CLU_ASSERT(nColA < GetColCount());
			CLU_ASSERT(nColB < GetColCount());

			std::initializer_list<TIdx> lSizeA, lSizeB;

			if (IsTranspose())
			{
				lSizeA = { nColA, 0 };
				lSizeB = { nColB, 0 };
			}
			else
			{
				lSizeA = { 0, nColA };
				lSizeB = { 0, nColB };
			}

			TIterator itColA = Begin(lSizeA, m_nRowDimIdx);
			TIterator itColB = Begin(lSizeB, m_nRowDimIdx);
			TIterator itColEndA = itColA + GetRowCount();

			TValue tValue;
			for (; itColA != itColEndA; ++itColA, ++itColB)
			{
				tValue = *itColA;
				*itColA = *itColB;
				*itColB = tValue;
			}

			return *this;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Swap rows. </summary>
		///
		/// <remarks>	Perwass, 10.02.2016. </remarks>
		///
		/// <param name="nRowA">	The row a. </param>
		/// <param name="nRowB">	The row b. </param>
		///
		/// <returns>	A TMatrix&amp; </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		TMatrix& SwapRows(TIdx nRowA, TIdx nRowB)
		{
			if (nRowA == nRowB)
			{
				return *this;
			}

			CLU_ASSERT(nRowA < GetRowCount());
			CLU_ASSERT(nRowB < GetRowCount());

			std::initializer_list<TIdx> lSizeA, lSizeB;

			if (IsTranspose())
			{
				lSizeA = { 0, nRowA };
				lSizeB = { 0, nRowB };
			}
			else
			{
				lSizeA = { nRowA, 0 };
				lSizeB = { nRowB, 0 };
			}

			TIterator itRowA = Begin(lSizeA, m_nColDimIdx);
			TIterator itRowB = Begin(lSizeB, m_nColDimIdx);
			TIterator itRowEndA = itRowA + GetColCount();

			TValue tValue;
			for (; itRowA != itRowEndA; ++itRowA, ++itRowB)
			{
				tValue = *itRowA;
				*itRowA = *itRowB;
				*itRowB = tValue;
			}

			return *this;
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \brief Gets sub matrix.
		///
		/// \author Perwass
		/// \date 11.02.2016
		///
		/// \param	nRowStartIdx Zero-based index of the row start.
		/// \param	nColStartIdx Zero-based index of the col start.
		/// \param	nRowCnt		 Number of rows.
		/// \param	nColCnt		 Number of cols.
		///
		/// \return The sub matrix.
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		TMatrix GetSubMatrix(TIdx nRowStartIdx, TIdx nColStartIdx, TIdx nRowCnt, TIdx nColCnt)
		{
			if (nRowStartIdx + nRowCnt - 1 >= GetRowCount()
				|| nColStartIdx + nColCnt - 1 >= GetColCount())
			{
				throw CLU_EXCEPTION("Sub matrix range out of bounds");
			}

			TMatrix matB(nRowCnt, nColCnt);

			TIterator itRowA = BeginRows(nRowStartIdx, nColStartIdx);
			TIterator itRowEndA = itRowA + nRowCnt;
			TIterator itRowB = matB.BeginRows();

			for (; itRowA != itRowEndA; ++itRowA, ++itRowB)
			{
				TIterator itRowColA = BeginCols(itRowA);
				TIterator itRowColEndA = itRowColA + nColCnt;
				TIterator itRowColB = matB.BeginCols(itRowB);

				for (; itRowColA != itRowColEndA; ++itRowColA, ++itRowColB)
				{
					*itRowColB = *itRowColA;
				}
			}

			return matB;
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \brief Sets sub matrix.
		///
		/// \author Perwass
		/// \date 11.02.2016
		///
		/// \param	nRowStartIdx Zero-based index of the row start.
		/// \param	nColStartIdx Zero-based index of the col start.
		/// \param	matB		 The matrix b.
		///
		/// \return A TMatrix&.
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		TMatrix& SetSubMatrix(TIdx nRowStartIdx, TIdx nColStartIdx, const TMatrix& matB)
		{
			if (nRowStartIdx + matB.GetRowCount() - 1 >= GetRowCount()
				|| nColStartIdx + matB.GetColCount() - 1 >= GetColCount())
			{
				throw CLU_EXCEPTION("Sub matrix range out of bounds");
			}

			TIterator itRowA = BeginRows(nRowStartIdx, nColStartIdx);
			TIterator itRowEndA = itRowA + matB.GetRowCount();
			TConstIterator itRowB = matB.ConstBeginRows();

			for (; itRowA != itRowEndA; ++itRowA, ++itRowB)
			{
				TIterator itRowColA = BeginCols(itRowA);
				TIterator itRowColEndA = itRowColA + matB.GetColCount();
				TConstIterator itRowColB = matB.ConstBeginCols(itRowB);

				for (; itRowColA != itRowColEndA; ++itRowColA, ++itRowColB)
				{
					*itRowColA = *itRowColB;
				}
			}

			return *this;
		}


	protected:

		TValue _Abs(TValue tValue)
		{
			return tValue < TValue(0) ? -tValue : tValue;
		}

		bool _IsZero(TValue tValue, TValue tPrec)
		{
			return (_Abs(tValue) < _Abs(tPrec));
		}

		std::vector<TIdx> _GetIndexVector(TIdx nRowIdx, TIdx nColIdx) const
		{
			if (IsTranspose())
			{
				return std::vector<TIdx>({ nColIdx, nRowIdx });
			}
			else
			{
				return std::vector<TIdx>({ nRowIdx, nColIdx });
			}
		}
	};	// class


}	// namespace

#include "Matrix.Operators.h"