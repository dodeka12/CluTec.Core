////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.Math
// file:      Matrix.Operators.h
//
// summary:   Declares the matrix. operators class
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

#include <string>
#include <iostream>

#include "Matrix.h"
#include "CluTec.Base/ValueFormatString.h"

namespace Clu
{
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Addition operator. </summary>
	///
	/// <remarks>	Perwass, 10.02.2016. </remarks>
	///
	/// <typeparam name="TValue">	Type of the value. </typeparam>
	/// <param name="matA">	The matrix a. </param>
	/// <param name="matB">	The matrix b. </param>
	///
	/// <returns>	The result of the operation. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	template<class TValue>
	CMatrix<TValue> operator+(const CMatrix<TValue>& matA, const CMatrix<TValue>& matB)
	{
		CLU_ASSERT(matA.IsEqualSize(matB));
		
		CMatrix<TValue> matC(matA);
		matC += matB;

		return matC;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Subtraction operator. </summary>
	///
	/// <remarks>	Perwass, 10.02.2016. </remarks>
	///
	/// <typeparam name="TValue">	Type of the value. </typeparam>
	/// <param name="matLeftOp"> 	The matrix left operation. </param>
	/// <param name="matRightOp">	The matrix right operation. </param>
	///
	/// <returns>	The result of the operation. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	template<class TValue>
	CMatrix<TValue> operator-(const CMatrix<TValue>& matA, const CMatrix<TValue>& matB)
	{
		CLU_ASSERT(matA.IsEqualSize(matB));

		CMatrix<TValue> matC(matA);
		matC -= matB;

		return matC;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Multiplication operator. </summary>
	///
	/// <remarks>	Perwass, 10.02.2016. </remarks>
	///
	/// <typeparam name="TValue">	Type of the value. </typeparam>
	/// <param name="matA">	The matrix a. </param>
	/// <param name="matB">	The matrix b. </param>
	///
	/// <returns>	The result of the operation. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	template<class TValue>
	CMatrix<TValue> operator*(const CMatrix<TValue>& matA, const CMatrix<TValue>& matB)
	{
		CLU_ASSERT(matA.GetColCount() == matB.GetRowCount());

		CMatrix<TValue> matC(matA.GetRowCount(), matB.GetColCount());

		CMatrix<TValue>::TIterator itRowC = matC.BeginRows();

		matA.ForEachRow([&](CMatrix<TValue>::TConstIterator& itRowA)
		{
			CMatrix<TValue>::TIterator itRowColC = matC.BeginCols(itRowC);
			matB.ForEachCol([&](CMatrix<TValue>::TConstIterator& itColB)
			{
				CMatrix<TValue>::TConstIterator itRowColA = matA.ConstBeginCols(itRowA);
				CMatrix<TValue>::TConstIterator itEndRowColA = itRowColA + matA.GetColCount();
				CMatrix<TValue>::TConstIterator itColRowB = matB.ConstBeginRows(itColB);

				TValue tSum = TValue(0);
				for (; itRowColA != itEndRowColA; ++itRowColA, ++itColRowB)
				{
					//std::cout << "A: " << std::to_string(*itRowColA);
					//std::cout << ", B: " << std::to_string(*itColRowB) << std::endl;
					tSum += *itRowColA * *itColRowB;
				}
				//std::cout << std::endl;
				*itRowColC = tSum;
				++itRowColC;
			});

			++itRowC;
		});

		return matC;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Multiplication operator. </summary>
	///
	/// <remarks>	Perwass, 10.02.2016. </remarks>
	///
	/// <typeparam name="TValue">	Type of the value. </typeparam>
	/// <param name="matA">   	The matrix left operation. </param>
	/// <param name="tScalar">	The scalar. </param>
	///
	/// <returns>	The result of the operation. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	template<class TValue>
	CMatrix<TValue> operator*(const CMatrix<TValue>& matA, const TValue& tScalar)
	{
		CMatrix<TValue> matB(matA);
		matB *= tScalar;
		return matB;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Division operator. </summary>
	///
	/// <remarks>	Perwass, 10.02.2016. </remarks>
	///
	/// <typeparam name="TValue">	Type of the value. </typeparam>
	/// <param name="matA">   	The matrix a. </param>
	/// <param name="tScalar">	The scalar. </param>
	///
	/// <returns>	The result of the operation. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	template<class TValue>
	CMatrix<TValue> operator/(const CMatrix<TValue>& matA, const TValue& tScalar)
	{
		CMatrix<TValue> matB(matA);
		matB /= tScalar;
		return matB;
	}


	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// 	Calculates a block-wise matrix product.
	/// 	Suppose matrix A has dimensions (N*p, q) and matrix B has dimensions (N*q, r), then this function calculates
	/// 	the matrix products of block A[(i*p,0)->(i*p + p-1, q-1)] * B[(i*q, 0)->(i*q + q-1, r-1)].
	/// 	The resultant matrix C has dimensions (N*p, r).
	/// </summary>
	///
	/// <typeparam name="typename TValue">	Type of the typename t value. </typeparam>
	/// <param name="matC">	   	[in,out] The mat c. </param>
	/// <param name="matA">	   	The mat a. </param>
	/// <param name="matB">	   	The mat b. </param>
	/// <param name="uColCntA">	The col count a. </param>
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template<typename TValue>
	void MatrixBlockProduct(CMatrix<TValue>& matC, const CMatrix<TValue>& matA, const CMatrix<TValue>& matB, const size_t uBlockCount)
	{
		typedef CMatrix<TValue> TMatrix;

		try
		{
			const size_t uRowCntA = matA.GetRowCount();
			const size_t uColCntA = matA.GetColCount();
			const size_t uRowCntB = matB.GetRowCount();
			const size_t uColCntB = matB.GetColCount();

			if (uRowCntA % uBlockCount != 0)
			{
				throw CLU_EXCEPTION("Row count of matrix A is incompatible with block count");
			}

			if (uRowCntB % uBlockCount != 0)
			{
				throw CLU_EXCEPTION("Row count of matrix B is incompatible with block count");
			}

			const size_t uBlockRowCntB = uRowCntB / uBlockCount;

			if (uBlockRowCntB != uColCntA)
			{
				throw CLU_EXCEPTION("Block row count of matrix B is incompatible to column count of matrix A");
			}

			const size_t uRowCntC = uRowCntA;
			const size_t uColCntC = uColCntB;
			const size_t uBlockRowCntA = uRowCntA / uBlockCount;
			matC.SetSize(uRowCntC, uColCntC);

			TMatrix::TConstIterator itRowBlockA = matA.ConstBeginRowBlock(uBlockRowCntA);
			TMatrix::TConstIterator itRowBlockB = matB.ConstBeginRowBlock(uBlockRowCntB);
			TMatrix::TIterator itRowBlockC = matC.BeginRowBlock(uBlockRowCntA);
			TMatrix::TConstIterator itRowBlockEndA = itRowBlockA + uBlockCount;

			// Loop over row blocks
			for (; itRowBlockA != itRowBlockEndA; ++itRowBlockA, ++itRowBlockB, ++itRowBlockC)
			{
				TMatrix::TIterator itRowC = matC.BeginRows(itRowBlockC);

				matA.ForEachRow(itRowBlockA, uBlockRowCntA, [&](TMatrix::TConstIterator& itRowA)
				{
					TMatrix::TIterator itRowColC = matC.BeginCols(itRowC);
					matB.ForEachCol(itRowBlockB, matB.GetColCount(), [&](TMatrix::TConstIterator& itColB)
					{
						TMatrix::TConstIterator itRowColA = matA.ConstBeginCols(itRowA);
						TMatrix::TConstIterator itEndRowColA = itRowColA + matA.GetColCount();
						TMatrix::TConstIterator itColRowB = matB.ConstBeginRows(itColB);

						TValue tSum = TValue(0);
						for (; itRowColA != itEndRowColA; ++itRowColA, ++itColRowB)
						{
							//std::cout << "A: " << std::to_string(*itRowColA);
							//std::cout << ", B: " << std::to_string(*itColRowB) << std::endl;
							tSum += *itRowColA * *itColRowB;
						}
						//std::cout << std::endl;
						*itRowColC = tSum;
						++itRowColC;
					});

					++itRowC;
				});
			}
		}
		catch (std::exception& xEx)
		{
			throw CLU_EXCEPTION_NEST("Error calculating matrix block product", std::move(xEx));
		}
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \brief This function calculates A^T * A, where A is the given matrix and A^T denotes the transpose.
	///
	/// \author Perwass
	/// \date 11.02.2016
	///
	/// \tparam	TValue Generic type parameter.
	/// \param	matA The other matrix.
	///
	/// \return A CMatrix<TValue>
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	template<class TValue>
	CMatrix<TValue> Square(const CMatrix<TValue>& matA)
	{
		const size_t nLeftRowCnt = matA.GetColCount();
		const size_t nLeftColCnt = matA.GetRowCount();
		const size_t nRightColCnt = matA.GetColCount();

		CMatrix<TValue> matC(nLeftRowCnt, nRightColCnt);

		CMatrix<TValue>::TIterator itRowC = matC.BeginRows();

		matA.ForEachCol([&](CMatrix<TValue>::TConstIterator& itRowA)
		{
			CMatrix<TValue>::TIterator itRowColC = matC.BeginCols(itRowC);
			matA.ForEachCol([&](CMatrix<TValue>::TConstIterator& itColB)
			{
				CMatrix<TValue>::TConstIterator itRowColA = matA.ConstBeginRows(itRowA);
				CMatrix<TValue>::TConstIterator itEndRowColA = itRowColA + matA.GetRowCount();
				CMatrix<TValue>::TConstIterator itColRowB = matA.ConstBeginRows(itColB);

				TValue tSum = TValue(0);
				for (; itRowColA != itEndRowColA; ++itRowColA, ++itColRowB)
				{
					//std::cout << "A: " << std::to_string(*itRowColA);
					//std::cout << ", B: " << std::to_string(*itColRowB) << std::endl;
					tSum += *itRowColA * *itColRowB;
				}
				//std::cout << std::endl;
				*itRowColC = tSum;
				++itRowColC;
			});

			++itRowC;
		});

		return matC;
	}




	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// 	Convert this object into a string representation.
	/// </summary>
	///
	/// <typeparam name="typename TValue">	Type of the typename t. </typeparam>
	/// <param name="matA">	   	The mat a. </param>
	/// <param name="pcFormat">	The PC format. </param>
	///
	/// <returns>	The given data converted to a std::string. </returns>
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template<typename TValue>
	std::string ToString(const CMatrix<TValue>& matA, const char* pcFormat = nullptr)
	{
		if (matA.IsEmpty())
		{
			return std::string("||");
		}

		std::string sText = "";
		std::string sFormat;
		char pcValue[30];

		if (pcFormat == nullptr)
		{
			sFormat = Clu::ValueFormatString<TValue>();
			pcFormat = sFormat.c_str();
		}

		const unsigned uRowCnt = (unsigned)matA.GetRowCount();
		const unsigned uColCnt = (unsigned)matA.GetColCount();

		sprintf_s(pcValue, "[%u, %u]\n", uRowCnt, uColCnt);
		sText += pcValue;

		matA.ForEachRow([&](CMatrix<TValue>::TConstIterator& itRow)
		{
			CMatrix<TValue>::TConstIterator itRowCol = matA.ConstBeginCols(itRow);
			CMatrix<TValue>::TConstIterator itRowColEnd = itRowCol + matA.GetColCount();

			for (; itRowCol != itRowColEnd; ++itRowCol)
			{
				sprintf_s(pcValue, pcFormat, *itRowCol);
				sText += " | ";
				sText += pcValue;
			}

			sText += " |\n";
		});

		return sText;
	}


} // namespace Clu
