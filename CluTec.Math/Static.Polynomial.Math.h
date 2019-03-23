////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.Math
// file:      Static.Polynomial.Math.h
//
// summary:   Declares the static. polynomial. mathematics class
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
#include "Static.Polynomial.h"

#include "Matrix.h"
#include "Matrix.Algo.SVD.h"

namespace Clu
{
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Polynomal inverse using least-squares method. </summary>
	///
	/// This function evaluates the approximate inverse of a polynomial by fitting a polynomial
	/// of the same degree to a set of points on the inverse graph. The quality of the approximation
	/// can be checked by inspecting the return value of tRMSDev, which is the root mean square deviation.
	/// The function uses uValCnt values between tMin and tMax, whereby tMin and tMax are the first
	/// and the last value with uValCnt-2 values equally spaced between them. Twice as many values are
	/// used to test the approximation.
	/// If the polynomial has no inverse, or if the polynomial has parts with a derivative near zero,
	/// the approximate inverse will experience strong fluctuations.
	///
	/// <remarks>	Perwass, 05.09.2012. </remarks>
	///
	/// <param name="yA">	  	The polynom to calculate the inverse for. </param>
	/// <param name="tMin">   	The minimum value of the range where the fit points lie in. </param>
	/// <param name="tMax">   	The maximum value of the range where the fit points lie in. </param>
	/// <param name="uValCnt">	Number of fit values. </param>
	///
	/// <returns>	The approximate inverse polynomial. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	template<typename T, const uint t_uDegree, const uint t_uInvDegree>
	__CUDA_H__ void PolyInvLS(SPolynomial<T, t_uInvDegree>& yInvA, T& tRMSDev, SPolynomial<T, t_uDegree>& yA, T tMin, T tMax, uint uValCnt)
	{
		try
		{
			if (uValCnt < t_uInvDegree)
			{
				CLU_EXCEPTION("PolyInvLS(): Number of test values has to be greater or equal to the polynomial degree");
			}

			CMatrix<double> mA(uValCnt, t_uInvDegree);
			CMatrix<double> mR(uValCnt, 1), mH;
			T tStep = (tMax - tMin) / T(uValCnt - 1);

			// Create matrix and result vector
			for (uint uRow = 0; uRow < uValCnt; ++uRow)
			{
				T tX       = tMin + T(uRow) * tStep;
				double dS1 = double(yA(tX));
				double dS  = dS1;

				mR(uRow, 0) = double(tX - yA[0]);
				mA(uRow, 0) = dS;

				for (uint uCol = 1; uCol < t_uInvDegree; ++uCol)
				{
					dS            *= dS1;
					mA(uRow, uCol) = dS;
				}
			}

			// Evaluate inverse of matrix using SVD to ensure we get the
			// best fit in a least squares sense. Then multiply inverse with
			// result vector mR to get polynomial parameter vector.
			mH = CMatrixAlgoSVD<T>::Inverse(mA, 1e-10) * mR;

			// Create resultant polynomial
			yInvA[0] = yA[0];

			for (uint i = 0; i < t_uInvDegree; ++i)
			{
				yInvA[i + 1] = T(mH(i, 0));
			}

			// Evaluate Mean Deviation of yInvA from true inverse
			tRMSDev = T(0);

			T tX1 = tMin + tStep / T(3);
			T tX2 = tX1 + tStep / T(3);
			for (unsigned i = 0; i < uValCnt - 1; ++i, tX1 += tStep, tX2 += tStep)
			{
				T tS   = yA(tX1);
				T tDev = (yInvA(tS) - tX1);
				tRMSDev += tDev * tDev;

				tS       = yA(tX2);
				tDev     = yInvA(tS) - tX2;
				tRMSDev += tDev * tDev;
			}

			tRMSDev /= T(2 * (uValCnt - 1));
			tRMSDev  = ::sqrt(tRMSDev);
		}
		catch (CIException& xEx)
		{
			throw CLU_EXCEPTION_NEST("Error calculating polynomial inverse", std::move(xEx));
		}
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// 	Do a least squares fit of a polynomial of degree t_iDegree to the given 2D data points. The x-comp. of the 2D points
	/// 	gives the polynomial parameter and the y-comp. the polynomial result.
	/// </summary>
	///
	/// <typeparam name="T">		 Generic type parameter. </typeparam>
	/// <typeparam name="t_uDegree"> Type of the degree. </typeparam>
	/// <param name="mData"> The data. </param>
	///
	/// <returns> The fit polynomial </returns>
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template<typename T, const unsigned t_uDegree>
	__CUDA_H__ SPolynomial<T, t_uDegree> PolyFitLS(const std::vector < Clu::SVector2 < T >>& vec2DPoints)
	{
		T tRmsDeviation = T(0);
		return PolyFitLS<T, t_uDegree>(vec2DPoints, tRmsDeviation);
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// 	Do a least squares fit of a polynomial of degree t_iDegree to the given 2D data points. The x-comp. of the 2D points
	/// 	gives polynomial parameter and the y-comp. the polynomial result.
	/// </summary>
	///
	/// <typeparam name="typename T">		  	Type of the typename t. </typeparam>
	/// <typeparam name="const int t_iDegree">	Type of the constant int i degree. </typeparam>
	/// <param name="mData">  	The data. </param>
	/// <param name="tRMSDev">	[in,out] The rms development. </param>
	///
	/// <returns>	. </returns>
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template<typename T, const unsigned t_uDegree>
	__CUDA_H__ SPolynomial<T, t_uDegree> PolyFitLS(const std::vector < SVector2 < T >>& mData, T& tRMSDev)
	{
		try
		{
			uint uValCnt = (uint) mData.size();

			if (uValCnt < t_uDegree + 1)
			{
				throw CLU_EXCEPTION("PolyFitLS(): Number of test values has to be greater or equal to the polynomial degree plus one");
			}

			T tMinX, tMaxX;

			tMinX = tMaxX = mData[0].x;

			CMatrix<double> mA(uValCnt, t_uDegree + 1);
			CMatrix<double> mR(uValCnt, 1), mH;

			// Create matrix and result vector
			for (uint uRow = 0; uRow < uValCnt; ++uRow)
			{
				const SVector2<T>& xPnt = mData[uRow];

				double dS1 = double(xPnt.x);
				double dS  = dS1;

				mR(uRow, 0) = double(xPnt.y);
				mA(uRow, 0) = 1.0;

				for (uint uCol = 1; uCol < t_uDegree + 1; ++uCol)
				{
					mA(uRow, uCol) = dS;
					dS            *= dS1;
				}
			}

			//CMatrix<double> mU, mV, mD;
			//CMatrixAlgoSVD<double>::SVD(mA, mU, mD, mV);
			//
			//mH = CMatrixAlgoSVD<double>::Inverse(mA, 1e-10) * mA;

			// Evaluate inverse of matrix using SVD to ensure we get the
			// best fit in a least squares sense. Then multiply inverse with
			// result vector mR to get polynomial parameter vector.
			mH = CMatrixAlgoSVD<double>::Inverse(mA, 1e-10) * mR;

			// Create resultant polynomial
			SPolynomial<T, t_uDegree> yEst;

			for (uint i = 0; i < t_uDegree + 1; ++i)
			{
				yEst[i] = T(mH(i, 0));
			}

			// Evaluate Mean Deviation of yInv from true inverse
			tRMSDev = T(0);

			for (uint uValIdx = 0; uValIdx < uValCnt; ++uValIdx)
			{
				const SVector2<T>& xPnt = mData[uValIdx];

				T tDev = (yEst(xPnt.x) - xPnt.y);
				tRMSDev += tDev * tDev;
			}

			tRMSDev /= T(uValCnt);
			tRMSDev  = ::sqrt(tRMSDev);

			return yEst;
		}
		catch (CIException& xEx)
		{
			throw CLU_EXCEPTION_NEST("Error calculating least squares fit", std::move(xEx));
		}
	}

}
