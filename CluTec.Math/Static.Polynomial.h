////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.Math
// file:      Static.Polynomial.h
//
// summary:   Declares the static. polynomial class
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

#include "CluTec.Base/Defines.h"
#include "Static.Vector.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// namespace: Clu
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace Clu
{
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// 	Polynomial base class of parameter type T and degree t_iDegree. The base class has no constructor or destructor
	/// 	so that it can be used in CUDA constant memory declarations.
	///
	/// 	The value of the polynomial is calculated as SUM_(i=0)^t_iDegree (vtParameter[i] * pow(x, i))
	/// </summary>
	///
	/// <typeparam name="T">		 Datatype. </typeparam>
	/// <typeparam name="t_uDegree"> Polynomial degree. </typeparam>
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template<typename T, const unsigned t_uDegree>
	struct _SPolynomial
	{
		typedef _SVector<T, t_uDegree + 1> _TParListType;
		static const int c_iDegree = t_uDegree;

		/// <summary> Vector of the polynomial parameters. </summary>
		_TParListType vtParameter;

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// 	Assignment operator.
		/// </summary>
		///
		/// <typeparam name="T2"> Datatype of the other polynomial. </typeparam>
		/// <param name="xOtherPolynomial"> The other polynomial. </param>
		///
		/// <returns> The result of the operation. </returns>
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		template<typename T2>
		__CUDA_HDI__ _SPolynomial<T, t_uDegree>& operator=(const _SPolynomial<T2, t_uDegree>& xOtherPolynomial)
		{
			vtParameter = xOtherPolynomial.vtParameter;
			return *this;
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// 	Array indexer operator.
		/// </summary>
		///
		/// <param name="iParamIdx"> The parameter index. </param>
		///
		/// <returns> Reference to the indexed parameter. </returns>
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		__CUDA_HDI__ T& operator[](int iParamIdx)
		{
			return vtParameter[iParamIdx];
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// 	Constant array indexer operator.
		/// </summary>
		///
		/// <param name="iParamIdx"> The parameter index. </param>
		///
		/// <returns> Constant reference to the indexed parameter. </returns>
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		__CUDA_HDI__ const T& operator[](int iParamIdx) const
		{
			return vtParameter[iParamIdx];
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// 	Evaluate polynomial at point tX.
		/// </summary>
		///
		/// <param name="tX"> The t x coordinate. </param>
		///
		/// <returns> The result of the operation. </returns>
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		__CUDA_HDI__ T operator()(const T& tX) const
		{
			// Start with parameter 0
			T tResult = vtParameter[0];

			// Start with x^1
			T tPower = tX;

			// Sum all other parameter multiplied by x^i
			for (int iParamIdx = 1; iParamIdx <= t_uDegree; ++iParamIdx)
			{
				tResult += vtParameter[iParamIdx] * tPower;

				// Now x^i * x = x^(i+1)
				tPower *= tX;
			}

			return tResult;
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// 	Equality operator.
		/// </summary>
		///
		/// <param name="xOtherPolynomial"> The other polynomial. </param>
		///
		/// <returns> True if the polynomial parameters are considered equivalent. </returns>
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		__CUDA_HDI__ bool operator==(const _SPolynomial<T, t_uDegree>& xOtherPolynomial) const
		{
			return vtParameter == xOtherPolynomial.vtParameter;
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// 	Sets all polynomial parameters to zero.
		/// </summary>
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		__CUDA_HDI__ void SetZero()
		{
			vtParameter.SetZero();
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// 	Gets the derivative of the polynomial.
		/// </summary>
		///
		/// <returns> The derivative of the polynomial. </returns>
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		__CUDA_HDI__ _SPolynomial<T, t_uDegree> Derivative() const
		{
			_SPolynomial<T, t_uDegree> xDerivation;
			xDerivation.SetZero();

			for (int iParamIdx = 1; iParamIdx <= t_uDegree; ++iParamIdx)
			{
				xDerivation.vtParameter[iParamIdx - 1] = T(iParamIdx) * vtParameter[iParamIdx];
			}

			return xDerivation;
		}

	};

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// 	Polynomial class of parameter type T and degree t_iDegree.
	///
	/// 	The value of the polynomial is calculated as SUM_(i=0)^t_iDegree (vtParameter[i] * pow(x, i))
	/// </summary>
	///
	/// <typeparam name="T">		 Datatype. </typeparam>
	/// <typeparam name="t_uDegree"> Polynomial degree. </typeparam>
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template<typename T, const unsigned t_uDegree>
	struct SPolynomial : _SPolynomial<T, t_uDegree>
	{
		typedef T TDataType;
		typedef SVector<T, t_uDegree + 1> TParListType;

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// 	Default constructor.
		/// </summary>
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		__CUDA_HDI__ SPolynomial()
		{
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// 	Copy Constructor.
		/// </summary>
		///
		/// <typeparam name="T2"> Datatype of the given polynomial. </typeparam>
		/// <param name="yA"> The polynomial to copy. </param>
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		template<typename T2>
		__CUDA_HDI__ explicit SPolynomial(const SPolynomial<T2, t_uDegree>& yA)
		{
			*this = yA;
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// 	Constructor.
		/// </summary>
		///
		/// <typeparam name="T2"> Datatype of the given parameters. </typeparam>
		/// <param name="vtParams"> The polynomial parameters. </param>
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		template<typename T2>
		__CUDA_HDI__ explicit SPolynomial(const SVector<T2, t_uDegree + 1>& vtParams)
		{
			vtParameter = vtParams;
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// 	Constructor sets polynomial parameter of degree zero to zero. The higher degree parameters are set to _vPars.
		/// </summary>
		///
		/// <typeparam name="T2"> Generic type parameter. </typeparam>
		/// <param name="vtParams"> The polynomial parameters from degree 1 to t_iDegree. </param>
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		template<typename T2>
		__CUDA_HDI__ explicit SPolynomial(const SVector<T2, t_uDegree>& vtParams)
		{
			vtParameter[0] = T(0);
			for (int i = 1; i <= t_uDegree; ++i)
			{
				vtParameter[i] = vtParams[i - 1];
			}
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// 	Cast each element of this polynomial to the desired data type and returns the new polynomial.
		/// </summary>
		///
		/// <typeparam name="T2"> Generic type parameter. </typeparam>
		///
		/// <returns> The casted polynomial. </returns>
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		template<class T2>
		__CUDA_HDI__ SPolynomial<T2, t_uDegree> Cast() const
		{
			SPolynomial<T2, t_uDegree> polyCast(*this);
			return polyCast;
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// 	Assignment operator.
		/// </summary>
		///
		/// <typeparam name="T2"> Datatype of the other polynomial. </typeparam>
		/// <param name="xOtherPolynomial"> The other polynomial. </param>
		///
		/// <returns> The result of the operation. </returns>
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		template<typename T2>
		__CUDA_HDI__ SPolynomial<T, t_uDegree>& operator=(const SPolynomial<T2, t_uDegree>& xOtherPolynomial)
		{
			vtParameter = xOtherPolynomial.vtParameter;
			return *this;
		}
	};
}

