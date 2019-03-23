////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.Math
// file:      Static.Matrix.Math.h
//
// summary:   Declares the static. matrix. mathematics class
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

#include "Constants.h"
#include "Static.Vector.Math.h"
#include "Static.Matrix.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// namespace: Clu
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace Clu
{
/**
\addtogroup CluToDo
**/
/// @{

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// 	Create a 2x2 counter clockwise rotation matrix for dRad radians.
	/// </summary>
	///
	/// <typeparam name="T"> Generic type parameter. </typeparam>
	/// <param name="dRad"> Rotation angle in radians. </param>
	///
	/// <returns> The rotation matrix. </returns>
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template<class T>
	__CUDA_HDI__ _SMatrix<T, 2> RotMat2(T dRad)
	{
		_SMatrix<T, 2> mA;

		mA(0, 0) = T(cos(dRad));
		mA(0, 1) = T(-sin(dRad));
		mA(1, 0) = -mA(0, 1);
		mA(1, 1) = mA(0, 0);

		return mA;
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// 	3x3 CCW rotation matrix about given 3d-axis.
	/// </summary>
	///
	/// <typeparam name="T"> Generic type parameter. </typeparam>
	/// <param name="dRad">  The radians. </param>
	/// <param name="vAxis"> The axis. </param>
	///
	/// <returns> The rotation matrix. </returns>
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template<class T>
	__CUDA_HDI__ _SMatrix<T, 3> RotMat3(T dRad, const _SVector<T, 3>& vAxis)
	{
		_SMatrix<T, 3> mA;
		_SVector3<T> vN;
		vN = Normalize(vAxis);

		T dS = T(sin(dRad));
		T dC = T(cos(dRad));
		T dD = T(1) - dC;

		T dD11 = vN.x() * vN.x() * dD;
		T dD12 = vN.x() * vN.y() * dD;
		T dD13 = vN.x() * vN.z() * dD;
		T dD22 = vN.y() * vN.y() * dD;
		T dD23 = vN.y() * vN.z() * dD;
		T dD33 = vN.z() * vN.z() * dD;

		T dS1 = vN.x() * dS;
		T dS2 = vN.y() * dS;
		T dS3 = vN.z() * dS;

		mA(0, 0) = dC + dD11;
		mA(0, 1) = dD12 - dS3;
		mA(0, 2) = dD13 + dS2;

		mA(1, 0) = dD12 + dS3;
		mA(1, 1) = dC + dD22;
		mA(1, 2) = dD23 - dS1;

		mA(2, 0) = dD13 - dS2;
		mA(2, 1) = dD23 + dS1;
		mA(2, 2) = dC + dD33;

		return mA;
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// 	Axis and angle from rot matrix 3.
	/// </summary>
	///
	/// <param name="mRotaionMatrix"> The rotaion matrix. </param>
	///
	/// <returns> . </returns>
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template<class T>
	__CUDA_HDI__ _SVector4<T> AxisAndAngleFromRotMat3(_SMatrix<T, 3> mRotationMatrix)
	{
		_SVector4<T> vecAxisAngle;

		// Margin to allow for rounding errors
		double epsilon1 = 0.01;

		// Margin to distinguish between 0 and 180 degrees
		double epsilon2 = 0.1;

		// Optional check that input is pure rotation, is defined at:
		// http://www.euclideanspace.com/maths/algebra/matrix/orthogonal/rotation/

		if ((fabs(mRotationMatrix(0, 1) - mRotationMatrix(1, 0)) < epsilon1)
		    && (fabs(mRotationMatrix(0, 2) - mRotationMatrix(2, 0)) < epsilon1)
		    && (fabs(mRotationMatrix(1, 2) - mRotationMatrix(2, 1)) < epsilon1))
		{
			// Singularity found
			// First check for identity matrix which must have +1 for all terms in leading diagonal and zero in other terms
			if ((fabs(mRotationMatrix(0, 1) + mRotationMatrix(1, 0)) < epsilon2)
			    && (fabs(mRotationMatrix(0, 2) + mRotationMatrix(2, 0)) < epsilon2)
			    && (fabs(mRotationMatrix(1, 2) + mRotationMatrix(2, 1)) < epsilon2)
			    && (fabs(mRotationMatrix(0, 0) + mRotationMatrix(1, 1) + mRotationMatrix(2, 2) - 3) < epsilon2))
			{
				// This singularity is identity matrix so angle = 0

				// Zero angle, arbitrary axis
				vecAxisAngle.x() = 0;
				vecAxisAngle.y() = 1;
				vecAxisAngle.z() = 0;
				vecAxisAngle.w() = 0;
				return vecAxisAngle;
			}

			// Otherwise this singularity is angle = 180
			vecAxisAngle.w() = Clu::Math::Constants<T>::Pi();
			double xx = (mRotationMatrix(0, 0) + 1) / 2;
			double yy = (mRotationMatrix(1, 1) + 1) / 2;
			double zz = (mRotationMatrix(2, 2) + 1) / 2;
			double xy = (mRotationMatrix(0, 1) + mRotationMatrix(1, 0)) / 4;
			double xz = (mRotationMatrix(0, 2) + mRotationMatrix(2, 0)) / 4;
			double yz = (mRotationMatrix(1, 2) + mRotationMatrix(2, 1)) / 4;

			// mRotaionMatrix(0, 0) is the largest diagonal term
			if ((xx > yy) && (xx > zz))
			{
				if (xx < epsilon1)
				{
					vecAxisAngle.x() = 0;
					vecAxisAngle.y() = Clu::Math::Constants<T>::InvSqrt2();
					vecAxisAngle.z() = Clu::Math::Constants<T>::InvSqrt2();
				}
				else
				{
					vecAxisAngle.x() = ::sqrt(xx);
					vecAxisAngle.y() = xy / vecAxisAngle.x;
					vecAxisAngle.z() = xz / vecAxisAngle.x;
				}
			}
			// mRotaionMatrix(1,1) is the largest diagonal term
			else if (yy > zz)
			{
				if (yy < epsilon1)
				{
					vecAxisAngle.x() = Clu::Math::Constants<T>::InvSqrt2();
					vecAxisAngle.y() = 0;
					vecAxisAngle.z() = Clu::Math::Constants<T>::InvSqrt2();
				}
				else
				{
					vecAxisAngle.y() = ::sqrt(yy);
					vecAxisAngle.x() = xy / vecAxisAngle.y();
					vecAxisAngle.z() = yz / vecAxisAngle.y();
				}
			}
			// mRotaionMatrix(2,2) is the largest diagonal term so base result on this
			else
			{
				if (zz < epsilon1)
				{
					vecAxisAngle.x() = Clu::Math::Constants<T>::InvSqrt2();
					vecAxisAngle.y() = Clu::Math::Constants<T>::InvSqrt2();
					vecAxisAngle.z() = 0;
				}
				else
				{
					vecAxisAngle.z() = std::sqrt(zz);
					vecAxisAngle.x() = xz / vecAxisAngle.z();
					vecAxisAngle.y() = yz / vecAxisAngle.z();
				}
			}

			return vecAxisAngle;
		}

		double dDivider = ::sqrt(
				::pow((mRotationMatrix(2, 1) -  mRotationMatrix(1, 2)), 2)
				+ ::pow((mRotationMatrix(0, 2) - mRotationMatrix(2, 0)), 2.0)
				+  ::pow((mRotationMatrix(1, 0) - mRotationMatrix(0, 1)), 2.0));

		vecAxisAngle.x() = (mRotationMatrix(2, 1) - mRotationMatrix(1, 2)) / dDivider;
		vecAxisAngle.y() = (mRotationMatrix(0, 2) - mRotationMatrix(2, 0)) / dDivider;
		vecAxisAngle.z() = (mRotationMatrix(1, 0) - mRotationMatrix(0, 1)) / dDivider;
		vecAxisAngle.w() = acos((mRotationMatrix(0, 0) + mRotationMatrix(1, 1) + mRotationMatrix(2, 2) - 1) / 2);

		return vecAxisAngle;
	}


	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// 	4x4 CCW homogeneous rotation matrix about given 3d-axis.
	/// </summary>
	///
	/// <typeparam name="T"> Generic type parameter. </typeparam>
	/// <param name="dRad">  Rotation angle in radians. </param>
	/// <param name="vAxis"> Rotation axis. Need not be normalized. </param>
	///
	/// <returns> The 4x4 rotation matrix. </returns>
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template<class T>
	__CUDA_HDI__ _SMatrix<T, 4> RotMat4(T dRad, const _SVector<T, 3>& vAxis)
	{
		_SMatrix<T, 4> mA;
		_SVector<T, 3> vN = Normalize(vAxis);

		T dS = T(sin(dRad));
		T dC = T(cos(dRad));
		T dD = T(1) - dC;

		T dD11 = vN[0] * vN[0] * dD;
		T dD12 = vN[0] * vN[1] * dD;
		T dD13 = vN[0] * vN[2] * dD;
		T dD22 = vN[1] * vN[1] * dD;
		T dD23 = vN[1] * vN[2] * dD;
		T dD33 = vN[2] * vN[2] * dD;

		T dS1 = vN[0] * dS;
		T dS2 = vN[1] * dS;
		T dS3 = vN[2] * dS;

		mA(0, 0) = dC + dD11;
		mA(0, 1) = dD12 - dS3;
		mA(0, 2) = dD13 + dS2;
		mA(0, 3) = T(0);

		mA(1, 0) = dD12 + dS3;
		mA(1, 1) = dC + dD22;
		mA(1, 2) = dD23 - dS1;
		mA(1, 3) = T(0);

		mA(2, 0) = dD13 - dS2;
		mA(2, 1) = dD23 + dS1;
		mA(2, 2) = dC + dD33;
		mA(2, 3) = T(0);

		mA(3, 0) = T(0);
		mA(3, 1) = T(0);
		mA(3, 2) = T(0);
		mA(3, 3) = T(1);

		return mA;
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// 	4x4 homogeneous translation matrix by given 3d-vector.
	/// </summary>
	///
	/// <typeparam name="T"> Generic type parameter. </typeparam>
	/// <param name="vT"> Translation vector. </param>
	///
	/// <returns> The matrix. </returns>
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template<class T>
	__CUDA_HDI__ _SMatrix<T, 4> TransMat4(const _SVector<T, 3>& vT)
	{
		_SMatrix<T, 4> mA;

		mA(0, 3) = vT.x;
		mA(1, 3) = vT.y;
		mA(2, 3) = vT.z;
		mA(3, 3) = T(1);

		return mA;
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// 	Matrix transpose.
	/// </summary>
	///
	/// <typeparam name="T">	  The data type of the matrix. </typeparam>
	/// <typeparam name="t_iDim"> The matrix dimension. </typeparam>
	/// <param name="mA"> The matrix to transpose. </param>
	///
	/// <returns> The transpose of mA. </returns>
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template<class T, const int t_nDim>
	__CUDA_HDI__ _SMatrix<T, t_nDim> operator~(const _SMatrix<T, t_nDim>& mA)
	{
		_SMatrix<T, t_nDim> mB;
		for (int iRow = 0; iRow < t_nDim; ++iRow)
		{
			for (int iCol = 0; iCol < t_nDim; ++iCol)
			{
				mB.pMat[iRow][iCol] = mA.pMat[iCol][iRow];
			}
		}

		return mB;
	}

	////////////////////////////////////////////////////
	/**
	        \brief Determinant of 2x2 matrix.

	        \param mA The matrix.

	        \returns The determinant of mA.
	**/
	template<class T>
	__CUDA_HDI__ T Determinant(const _SMatrix<T, 2>& mA)
	{
		return mA(0, 0) * mA(1, 1) - mA(0, 1) * mA(1, 0);
	}

	/**
	        \brief Determinant of 3x3 matrix.

	        \param mA The matrix.

	        \returns The determinant of mA.
	**/
	template<class T>
	__CUDA_HDI__ T Determinant(const _SMatrix<T, 3>& mA)
	{
		return mA(0, 0) * mA(1, 1) * mA(2, 2)
		       +       mA(0, 1) * mA(1, 2) * mA(2, 0)
		       +       mA(0, 2) * mA(1, 0) * mA(2, 1)
		       -       mA(0, 2) * mA(1, 1) * mA(2, 0)
		       -       mA(0, 1) * mA(1, 0) * mA(2, 2)
		       -       mA(0, 0) * mA(1, 2) * mA(2, 1);
	}


	////////////////////////////////////////////////////
	// Inverse

	/**
	        \brief Inverse of 2x2 matrix.

	        \param mA The matrix.

	        \returns The inverse of mA.
	**/
	template<class T>
	__CUDA_HDI__ _SMatrix<T, 2> Inverse(const _SMatrix<T, 2>& mA)
	{
		_SMatrix<T, 2> mB;
		T tDet = Determinant(mA);

		mB.pData[0][0] = mA(1, 1) / tDet;
		mB.pData[0][1] = -mA(0, 1) / tDet;
		mB.pData[1][0] = -mA(1, 0) / tDet;
		mB.pData[1][1] = mA(0, 0) / tDet;

		return mB;
	}

	/**
	        \brief Inverse of 3x3 matrix.

	        \param mA The matrix.

	        \returns The inverse of mA.
	**/
	template<class T>
	__CUDA_HDI__ _SMatrix<T, 3> Inverse(const _SMatrix<T, 3>& mA)
	{
		_SMatrix<T, 3> mB;
		T tDet = Determinant(mA);

		mB.pData[0][0] = (mA(1, 1) * mA(2, 2) - mA(1, 2) * mA(2, 1)) / tDet;
		mB.pData[0][1] = (mA(0, 2) * mA(2, 1) - mA(0, 1) * mA(2, 2)) / tDet;
		mB.pData[0][2] = (mA(0, 1) * mA(1, 2) - mA(0, 2) * mA(1, 1)) / tDet;

		mB.pData[1][0] = (mA(1, 2) * mA(2, 0) - mA(1, 0) * mA(2, 2)) / tDet;
		mB.pData[1][1] = (mA(0, 0) * mA(2, 2) - mA(0, 2) * mA(2, 0)) / tDet;
		mB.pData[1][2] = (mA(0, 2) * mA(1, 0) - mA(0, 0) * mA(1, 2)) / tDet;

		mB.pData[2][0] = (mA(1, 0) * mA(2, 1) - mA(1, 1) * mA(2, 0)) / tDet;
		mB.pData[2][1] = (mA(0, 1) * mA(2, 0) - mA(0, 0) * mA(2, 1)) / tDet;
		mB.pData[2][2] = (mA(0, 0) * mA(1, 1) - mA(0, 1) * mA(1, 0)) / tDet;

		return mB;
	}


	
/// @}
}
