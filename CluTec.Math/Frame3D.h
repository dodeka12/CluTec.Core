////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.Math
// file:      Frame3D.h
//
// summary:   Declares the frame 3D class
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

#include "Static.Vector.h"
#include "Static.Matrix.h"
#include "Static.Matrix.Math.h"

// namespace: Clu
namespace Clu
{
	template<class TValue>
	class _CFrame3D
	{
	public:
		using TMat3 = _SMatrix<TValue, 3>;
		using TVec2 = _SVector<TValue, 2>;
		using TVec3 = _SVector<TValue, 3>;
		using TVec4 = _SVector<TValue, 4>;

		using TThis = _CFrame3D<TValue>;

	public:

		/// <summary>	The frame rotation matrix. Given a point in the local frame vX_l, then the same point
		/// 			in reference frame coordinates is given by m_mR_l_r * vX_l + m_vT_l_r.
		/// 			</summary>
		TMat3 m_mR_l_r;


		/// <summary>	The translation vector giving the origin of the frame in the reference frame. 
		/// 			Given a point vX_l in the local frame the same point in the reference frame
		/// 			is given by m_mR_l_r * vX_l + m_vT_l_r.</summary>
		TVec3 m_vT_l_r;

	public:

		__CUDA_HDI__ void Reset()
		{
			m_mR_l_r.SetIdentity();
			m_vT_l_r.SetZero();
		}

		__CUDA_HDI__ void Create(const TThis& xF)
		{
			m_mR_l_r = xF.m_mR_l_r;
			m_vT_l_r = xF.m_vT_l_r;
		}


		template<class TValue2>
		__CUDA_HDI__ void Create(const _CFrame3D<TValue2>& xFrame)
		{
			m_mR_l_r.CastFrom(xFrame.m_mR_l_r);
			m_vT_l_r.CastFrom(xFrame.m_vT_l_r);
		}


		__CUDA_HDI__ void Create(const TVec3& vT_l_r)
		{
			Reset();
			SetTranslation_r_l(vT_l_r);
		}

		__CUDA_HDI__ void Create(const TVec3& vDirZ_r, TValue dRotAboutZInRad, const TVec3& vT_l_r)
		{
			SetBasis_l_r(vDirZ_r, dRotAboutZInRad);
			SetTranslation_r_l(vT_l_r);
		}

		__CUDA_HDI__ void Create(const TVec3& vDirZ_r, const TVec3& vDirX_r, const TVec3& vT_l_r)
		{
			SetBasis_l_r(vDirZ_r, vDirX_r);
			SetTranslation_r_l(vT_l_r);
		}

		__CUDA_HDI__ void Create(const TVec3& vX_r, const TVec3& vY_r, const TVec3& vZ_r, const TVec3& vT_l_r)
		{
			SetBasis_l_r(vX_r, vY_r, vZ_r);
			SetTranslation_r_l(vT_l_r);
		}

		__CUDA_HDI__ void Create(const TMat3& matR_l_r, const TVec3& vT_l_r)
		{
			SetBasis_l_r(matR_l_r);
			SetTranslation_r_l(vT_l_r);
		}

		__CUDA_HDI__ void Create(const TValue dPhiX, const TValue dPhiY, const TValue dPhiZ, const TVec3& vT_l_r)
		{
			SetBasis_l_r(dPhiX, dPhiY, dPhiZ);
			SetTranslation_r_l(vT_l_r);
		}

		template<typename TValue2>
		__CUDA_HDI__ void CastFrom(const _CFrame3D<TValue2>& xFrame)
		{
			m_mR_l_r.CastFrom(xFrame.m_mR_l_r);
			m_vT_l_r.CastFrom(xFrame.m_vT_l_r);
		}

		__CUDA_HDI__ const TVec3& Translation_l_r() const
		{
			return m_vT_l_r;
		}

		__CUDA_HDI__ TVec3& Translation_l_r()
		{
			return m_vT_l_r;
		}

		__CUDA_HDI__ void SetTranslation_r_l(const TVec3& vT)
		{
			m_vT_l_r = vT;
		}

		__CUDA_HDI__ void SetBasis_l_r(const TMat3& matR_l_r)
		{
			m_mR_l_r = matR_l_r;
		}

		__CUDA_HDI__ void SetBasis_l_r(const TValue dPhiX, const TValue dPhiY, const TValue dPhiZ)
		{
			const TValue cx = cos(dPhiX);
			const TValue sx = sin(dPhiX);
			const TValue cy = cos(dPhiY);
			const TValue sy = sin(dPhiY);
			const TValue cz = cos(dPhiZ);
			const TValue sz = sin(dPhiZ);

			m_mR_l_r(0, 0) = cy * cz + sx * sy * sz; /**/ m_mR_l_r(0, 1) = sx * sy * cz - cy * sz; /**/ m_mR_l_r(0, 2) = cx * sy;
			m_mR_l_r(1, 0) =                cx * sz; /**/ m_mR_l_r(1, 1) =                cx * cz; /**/ m_mR_l_r(1, 2) =     -sx;
			m_mR_l_r(2, 0) = sx * cy * sz + sy * cz; /**/ m_mR_l_r(2, 1) = sy * sz + sx * cy * cz; /**/ m_mR_l_r(2, 2) = cx * cy;
		}

		__CUDA_HDI__ void SetBasis_l_r(const TVec3& vDirZ_r, const TVec3& vDirX_r)
		{
			TVec3 vX, vY, vZ;

			vZ = Normalize(vDirZ_r);
			vX = Normalize(vDirZ_r) ^ vZ;
			vY = vZ ^ vX;

			SetBasis_l_r(vX, vY, vZ);
		}

		__CUDA_HDI__ void SetBasis_l_r(const TVec3& vDirZ_r, TValue dRotAboutZInRad)
		{
			typedef TValue F;

			TVec3 vX_r, vY_r, vZ_r, _vX, _vY;
			TVec3 vE1_r;
			TVec3 vE2_r;
			TVec3 vE3_r;

			vE1_r.SetElements(F(1), F(0), F(0));
			vE2_r.SetElements(F(0), F(1), F(0));
			vE3_r.SetElements(F(0), F(0), F(1));

			vZ_r = Normalize(vDirZ_r);

			if (abs(Dot(vZ_r, vE2_r)) < TValue(0.01))
			{
				_vX = Normalize(vE2_r ^ vZ_r);
				if (Dot(_vX, vE1_r) < TValue(0))
				{
					_vX = -_vX;
				}

				_vY = Normalize(vZ_r ^ _vX);
			}
			else
			{
				_vY = Normalize(vZ_r ^ vE1_r);
				_vX = Normalize(_vY ^ vZ_r);
			}

			const TValue dCos = cos(dRotAboutZInRad);
			const TValue dSin = sin(dRotAboutZInRad);
			vX_r.LinearCombination(dCos, _vX, dSin, _vY);
			vY_r.LinearCombination(-dSin, _vX, dCos, _vY);

			SetBasis_l_r(vX_r, vY_r, vZ_r);
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Sets basis of the rotation matrix. The columns of m_mR_l_r give the
		/// 			basis vectors of the frame. </summary>
		///
		/// <typeparam name="TValue2">	Type of the value 2. </typeparam>
		/// <param name="vX">	The v x coordinate. </param>
		/// <param name="vY">	The v y coordinate. </param>
		/// <param name="vZ">	The v z coordinate. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		template<typename TValue2>
		__CUDA_HDI__ void SetBasis_l_r(const _SVector<TValue2, 3>& vX, const _SVector<TValue2, 3>& vY, const _SVector<TValue2, 3>& vZ)
		{
			m_mR_l_r(0, 0) = TValue(vX[0]);
			m_mR_l_r(1, 0) = TValue(vX[1]);
			m_mR_l_r(2, 0) = TValue(vX[2]);

			m_mR_l_r(0, 1) = TValue(vY[0]);
			m_mR_l_r(1, 1) = TValue(vY[1]);
			m_mR_l_r(2, 1) = TValue(vY[2]);

			m_mR_l_r(0, 2) = TValue(vZ[0]);
			m_mR_l_r(1, 2) = TValue(vZ[1]);
			m_mR_l_r(2, 2) = TValue(vZ[2]);
		}


		__CUDA_HDI__ const TMat3& Basis_l_r() const
		{
			return m_mR_l_r;
		}

		template<typename TValue2>
		__CUDA_HDI__ void GetBasis_l_r(_SVector<TValue2, 3>& vX, _SVector<TValue2, 3>& vY, _SVector<TValue2, 3>& vZ) const
		{
			vX[0] = TValue2(m_mR_l_r(0, 0));
			vX[1] = TValue2(m_mR_l_r(1, 0));
			vX[2] = TValue2(m_mR_l_r(2, 0));

			vY[0] = TValue2(m_mR_l_r(0, 1));
			vY[1] = TValue2(m_mR_l_r(1, 1));
			vY[2] = TValue2(m_mR_l_r(2, 1));

			vZ[0] = TValue2(m_mR_l_r(0, 2));
			vZ[1] = TValue2(m_mR_l_r(1, 2));
			vZ[2] = TValue2(m_mR_l_r(2, 2));
		}


		__CUDA_HDI__ TVec3 MapIntoFrame(const TVec3& vReference) const
		{
			// This multiplication interprets vector as row vector multiplied from left with matrix.
			// As m_matR_r_l is an orthonormal matrix, this is equivalent to transposing (inverting)
			// m_matR_r_l and multiplying vector from right.
			return (vReference - m_vT_l_r) * m_mR_l_r;
		}


		__CUDA_HDI__ TVec3 MapOutOfFrame(const TVec3& vLocal) const
		{
			return m_mR_l_r * vLocal + m_vT_l_r;
		}

		__CUDA_HDI__ TVec3 MapOutOfFrame(const TVec2& v2Local) const
		{
			TVec3 v3Local;
			v3Local.SetElements(v2Local[0], v2Local[1]);

			return MapOutOfFrame(v3Local);
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Concatenate frames so that a MapOutOfFrame() of the combined frame maps a point
		/// 			first out of this frame and then out of xFrameB. </summary>
		///
		/// <param name="xResult">	[out] The resultant frame. </param>
		/// <param name="xFrameB">	The frame B. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		__CUDA_HD__ void ConcatFrames_Out_Out(_CFrame3D<TValue>& xResult_l_s, const _CFrame3D<TValue>& xFrameB_r_s) const
		{
			xResult_l_s.m_mR_l_r = xFrameB_r_s.m_mR_l_r * m_mR_l_r;
			xResult_l_s.m_vT_l_r = xFrameB_r_s.m_mR_l_r * m_vT_l_r + xFrameB_r_s.m_vT_l_r;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Concatenate frames so that a MapOutOfFrame() of the combined frame maps a point
		/// 			first out of this frame and then into xFrameB. </summary>
		///
		/// <param name="xResult_l_m">	[out] The resultant frame. </param>
		/// <param name="xFrameB_m_r">	The frame B. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		__CUDA_HD__ void ConcatFrames_Out_In(_CFrame3D<TValue>& xResult_l_m, const _CFrame3D<TValue>& xFrameB_m_r) const
		{
			// Matrix product of transposed R matrix of Frame B with this R matrix.
			MatrixProduct<1, 0>(xResult_l_m.m_mR_l_r, xFrameB_m_r.m_mR_l_r, m_mR_l_r);

			// Vector-Matrix product with transposed R matrix of frame B.
			// Vector multiplied from left interprets vector as row vector and has the same effect
			// as transposing the matrix.
			xResult_l_m.m_vT_l_r = (m_vT_l_r - xFrameB_m_r.m_vT_l_r) * xFrameB_m_r.m_mR_l_r;
		}


		__CUDA_HD__ _CFrame3D<TValue> ConcatFrames_Out_Out(const _CFrame3D<TValue>& xFrameB) const
		{
			_CFrame3D<TValue> xFrame;
			ConcatFrames_Out_Out(xFrame, xFrameB);
			return xFrame;
		}

		__CUDA_HD__ _CFrame3D<TValue> ConcatFrames_Out_In(const _CFrame3D<TValue>& xFrameB) const
		{
			_CFrame3D<TValue> xFrame;
			ConcatFrames_Out_In(xFrame, xFrameB);
			return xFrame;
		}

	public:

		__CUDA_HDI__ bool operator==(const _CFrame3D<TValue>& xFrame) const
		{
			return xFrame.m_mR_l_r == m_mR_l_r && xFrame.m_vT_l_r == m_vT_l_r;
		}

	};



	template<class TValue>
	class CFrame3D : public _CFrame3D<TValue>
	{
	public:
		using TThis = CFrame3D<TValue>;
		using TBase = _CFrame3D<TValue>;

	public:

		__CUDA_HDI__ CFrame3D()
		{
		}

		__CUDA_HDI__ ~CFrame3D()
		{
		}

		__CUDA_HDI__ CFrame3D(const CFrame3D<TValue>& xFrame)
		{
			*this = xFrame;
		}

		template<class TValue2>
		__CUDA_HDI__ explicit CFrame3D(const CFrame3D<TValue2>& xFrame)
		{
			TBase::Create(xFrame);
		}

		__CUDA_HDI__ CFrame3D(const TVec3& vT_l_r)
		{
			Reset();
			m_vT_l_r = vT_l_r;
		}

		__CUDA_HDI__ CFrame3D(const TMat3& matR_l_r, const TVec3& vT_l_r)
		{
			Create(matR_l_r, vT_l_r);
		}

		__CUDA_HDI__ CFrame3D(const TValue dPhiX, const TValue dPhiY, const TValue dPhiZ, const TVec3& vT_l_r)
		{
			Create(dPhiX, dPhiY, dPhiZ, vT_l_r);
		}

		__CUDA_HDI__ CFrame3D& operator=(const CFrame3D<TValue>& xFrame)
		{
			TBase::Create(xFrame);
			return *this;
		}
	};

}
