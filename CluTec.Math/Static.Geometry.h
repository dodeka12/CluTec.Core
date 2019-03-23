////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.Math
// file:      Static.Geometry.h
//
// summary:   Declares the static. geometry class
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
#include "Static.Vector.Math.h"

namespace Clu
{
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// A 2D rectangle that is aligned with the canonical coordinate system. That is, it cannot
	/// represent a rectangle rotated in the 2D plane.
	/// </summary>
	///
	/// <typeparam name="TValue">	Type of the value. </typeparam>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	template<typename TValue>
	struct _SAlignedRect2D
	{
	public :
		using TVec2 = _SVector<TValue, 2>;

	protected:
		TVec2 m_vMinPos;
		TVec2 m_vMaxPos;

	public:
		void Create(TValue fMinX, TValue fMinY, TValue fMaxX, TValue fMaxY)
		{
			m_vMinPos[0] = (fMinX < fMaxX ? fMinX : fMaxX);
			m_vMaxPos[0] = (fMinX > fMaxX ? fMinX : fMaxX);

			m_vMinPos[1] = (fMinY < fMaxY ? fMinY : fMaxY);
			m_vMaxPos[1] = (fMinY > fMaxY ? fMinY : fMaxY);
		}

		void Create(const TVec2& vA, const TVec2& vB)
		{
			Create(vA[0], vA[1], vB[0], vB[1]);
		}

		TVec2 Size() const { return m_vMaxPos - m_vMinPos; }
		TVec2 Center() const { return m_vMinPos + Size() / TValue(2); }

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// 	Test whether the given rectangle is inside of this rectangle xRect.
		/// </summary>
		///
		/// <typeparam name="typename T">	Type of the typename t. </typeparam>
		/// <param name="xRect">	The rectangle. </param>
		///
		/// <returns>	True if inside of xRect, false if not. </returns>
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		template<typename T>
		bool IsInside(const _SAlignedRect2D<T>& xRect) const
		{
			return m_vMinPos[0] <= TValue(xRect.vMinPos[0])
			       &&      m_vMinPos[1] <= TValue(xRect.vMinPos[1])
			       &&      m_vMaxPos[0] >= TValue(xRect.vMaxPos[0])
			       &&      m_vMaxPos[1] >= TValue(xRect.vMaxPos[1]);
		}

	
		bool IsInside(const TVec2& vX)
		{
			return (vX[0] >= m_vMinPos[0])
				&& (vX[0] <= m_vMaxPos[0])
				&& (vX[1] >= m_vMinPos[1])
				&& (vX[1] <= m_vMaxPos[1]);
		}

	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Receive circle 2 d. </summary>
	///
	/// <remarks>	Perwass, 05.10.2013. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	template<typename TValue>
	struct SCircle2D
	{
		SCircle2D() { }

		template<typename T2>
		explicit SCircle2D(const SCircle2D<T2>& xCircle)
		{
			vCenter = SVector2<TValue>(xCircle.vCenter);
			tRadius = TValue(xCircle.tRadius);
		}

		SVector2<TValue> vCenter;
		TValue tRadius;
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Represents an ellipse in 2D space.
	/// 			 </summary>
	///
	/// <remarks>	Perwass, 05.10.2013. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	template<class TValue>
	struct SEllipse2D
	{
		SEllipse2D() { }

		template<typename T2>
		explicit SEllipse2D(const SEllipse2D<T2>& xEllipse)
		{
			vCenter = SVector2<TValue>(xEllipse.vCenter);
			vDir1   = SVector2<TValue>(xEllipse.vDir1);
			vDir2   = SVector2<TValue>(xEllipse.vDir2);

			tRadius1 = TValue(xEllipse.tRadius1);
			tRadius2 = TValue(xEllipse.tRadius2);
		}

		void Zero()
		{
			vCenter.zero();
			vDir1.zero();
			vDir2.zero();
			tRadius1 = TValue(0);
			tRadius2 = TValue(0);
		}

		TValue FocusRadius() const { return ::sqrt(::abs(tRadius2 * tRadius2 - tRadius1 * tRadius1)); }
		TValue MinRadius() const { return tRadius1 < tRadius2 ? tRadius1 : tRadius2;  }
		TValue MaxRadius() const { return tRadius1 > tRadius2 ? tRadius1 : tRadius2;  }
		TValue Eccentricity() const { return FocusRadius() / MaxRadius(); }
		SVector2<TValue> Axis1() const { return tRadius1 * vDir1; }
		SVector2<TValue> Axis2() const { return tRadius2 * vDir2; }
		SVector2<TValue> MinDir() const { return tRadius1 < tRadius2 ? vDir1 : vDir2;  }
		SVector2<TValue> MaxDir() const { return tRadius1 > tRadius2 ? vDir1 : vDir2;  }
		SVector2<TValue> FocusPoint() const { return FocusRadius() * MaxDir(); }

		void ScaleBy(TValue dScale)
		{
			vCenter  *= dScale;
			tRadius1 *= dScale;
			tRadius2 *= dScale;
		}

		SVector2<TValue> vCenter;
		SVector2<TValue> vDir1;
		SVector2<TValue> vDir2;

		TValue tRadius1;
		TValue tRadius2;
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Data that described a projective conic. </summary>
	///
	/// <remarks>	Perwass, 05.10.2013. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	template<class TValue>
	struct SConic2D
	{
		SConic2D() { }

		template<typename T2>
		explicit SConic2D(const SConic2D<T2>& xConic)
		{
			vCenter = SVector2<TValue>(xConic.vCenter);
			vDir1   = SVector2<TValue>(xConic.vDir1);
			vDir2   = SVector2<TValue>(xConic.vDir2);

			tLambda1 = TValue(xConic.tLambda1);
			tLambda2 = TValue(xConic.tLambda2);
			tRho     = TValue(xConic.tRho);
		}

		SVector2<TValue> vCenter;
		SVector2<TValue> vDir1;
		SVector2<TValue> vDir2;

		TValue tLambda1;
		TValue tLambda2;
		TValue tRho;
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Receive line 3 d. </summary>
	///
	/// <remarks>	Perwass, 12.02.2014. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	template<class TValue>
	struct SLine3D
	{
		__CUDA_HDI__ SLine3D() { }

		template<typename T2>
		__CUDA_HDI__ explicit SLine3D(const SLine3D<T2>& xLine)
		{
			vOrigin = SVector3<TValue>(xLine.vOrigin);
			vDir = SVector3<TValue>(xLine.vDir);
		}

		/// <summary>	Origin of the line. </summary>
		SVector3<TValue> vOrigin;

		/// <summary>	The direction of the line. </summary>
		SVector3<TValue> vDir;
	};

	template<class TValue> struct SPlaneSegment3D;

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// 	3D Plane
	/// </summary>
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	template<class TValue>
	struct SPlane3D
	{
		__CUDA_HDI__ SPlane3D() { }

		template<typename T2>
		__CUDA_HDI__ explicit SPlane3D(const SPlane3D<T2>& xPlane)
		{
			tDistance = (TValue) (xPlane.tDistance);
			vNormal   = SVector3<TValue>(xPlane.vNormal);
		}

		template<typename T2>
		__CUDA_HDI__ explicit SPlane3D(const SPlaneSegment3D<T2>& xPlaneSeg)
		{
			vNormal   = SVector3<TValue>(xPlaneSeg.Normal());
			tDistance = Dot(vNormal, SVector3<TValue>(xPlaneSeg.vCenter));
		}

		__CUDA_HDI__ void Create(const _SVector<TValue, 3>& vOrig, const _SVector<TValue, 3>& _vNormal)
		{
			vNormal = _vNormal;
			tDistance = Dot(vNormal, vOrig);
		}

		__CUDA_HDI__ void Create(const _SVector<TValue, 3>& vOrig, const _SVector<TValue, 3>& vDirX, const _SVector<TValue, 3>& vDirY)
		{
			vNormal = Normalize(vDirX ^ vDirY);
			tDistance = Dot(vNormal, vOrig);
		}


		__CUDA_HDI__ bool IsValid()
		{
			return IsFiniteNumber(tDistance) && IsFiniteNumber(vNormal) && (Length(vNormal) > TValue(0));
		}

		/// <summary>	The distance from the origin along the normal vector. </summary>
		TValue tDistance;

		/// <summary>	The plane normal. </summary>
		SVector3<TValue> vNormal;
	};

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// 	3D Plane segment
	/// </summary>
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template<class TValue>
	struct SPlaneSegment3D
	{
		SPlaneSegment3D() { }

		template<typename T2>
		explicit SPlaneSegment3D(const SPlaneSegment3D<T2>& xPlaneSeg)
		{
			vCenter = SVector3<TValue>(xPlaneSeg.vCenter);
			vDir1   = SVector3<TValue>(xPlaneSeg.vDir1);
			vDir2   = SVector3<TValue>(xPlaneSeg.vDir2);

			tLen1 = (TValue) (xPlaneSeg.tLen1);
			tLen2 = (TValue) (xPlaneSeg.tLen2);
		}

		template<typename T2>
		explicit SPlaneSegment3D(const SPlane3D<T2>& xPlane, const T2& tSize = T2(1))
		{
			SVector3<TValue> vNormal = SVector3<TValue>(xPlane.vNormal);

			SVector3<TValue> vA1 = vNormal ^ SVector3<TValue>(1, 0, 0);
			SVector3<TValue> vA2 = vNormal ^ SVector3<TValue>(0, 1, 0);
			SVector3<TValue> vA3 = vNormal ^ SVector3<TValue>(0, 0, 1);

			TValue dL1 = Length(vA1);
			TValue dL2 = Length(vA2);
			TValue dL3 = Length(vA3);

			if (dL1 > dL2)
			{
				if (dL1 > dL3) { vDir1 = vA1; }
				else{ vDir1 = vA3; }
			}
			else
			{
				if (dL2 > dL3) { vDir1 = vA2; }
				else{ vDir1 = vA3; }
			}

			vDir1 = Normalize(vDir1);
			vDir2 = vNormal ^ vDir1;

			vCenter = (TValue) (xPlane.tDistance) * vNormal;

			tLen1 = tSize;
			tLen2 = tSize;
		}

		SVector3<TValue> Axis1() const { return tLen1 * vDir1;  }
		SVector3<TValue> Axis2() const { return tLen2 * vDir2;  }

		SVector3<TValue> Normal() const { return Normalize(vDir1 ^ vDir2); }
		TValue Area() const { return tLen1 * tLen2;  }

		void GetCorner(SVector3<TValue>& vC1, SVector3<TValue>& vC2, SVector3<TValue>& vC3, SVector3<TValue>& vC4) const
		{
			SVector3<TValue> vHalfAxis1 = TValue(0.5) * tLen1 * vDir1;
			SVector3<TValue> vHalfAxis2 = TValue(0.5) * tLen2 * vDir2;

			vC1 = vCenter - vHalfAxis1 - vHalfAxis2;
			vC2 = vCenter - vHalfAxis1 + vHalfAxis2;
			vC3 = vCenter + vHalfAxis1 + vHalfAxis2;
			vC4 = vCenter + vHalfAxis1 - vHalfAxis2;
		}

		void GetCorner(SVector3<TValue> pvC[4]) const
		{
			SVector3<TValue> vHalfAxis1 = TValue(0.5) * tLen1 * vDir1;
			SVector3<TValue> vHalfAxis2 = TValue(0.5) * tLen2 * vDir2;

			pvC[0] = vCenter - vHalfAxis1 - vHalfAxis2;
			pvC[1] = vCenter - vHalfAxis1 + vHalfAxis2;
			pvC[2] = vCenter + vHalfAxis1 + vHalfAxis2;
			pvC[3] = vCenter + vHalfAxis1 - vHalfAxis2;
		}

		SVector3<TValue> vCenter;
		SVector3<TValue> vDir1;
		SVector3<TValue> vDir2;

		TValue tLen1;
		TValue tLen2;
	};



	template<class TValue>
	struct _SLine2D
	{
	public:
		using TVec2 = _SVector<TValue, 2>;

	protected:
		TVec2 m_vOrig, m_vDir;

	public:
		template<typename T2>
		__CUDA_HDI__ void CastFrom(const _SLine2D<T2>& xLine)
		{
			m_vOrig.CastFrom(xLine.vOrig);
			m_vDir.CastFrom(xLine.vDir);
		}

		__CUDA_HDI__ void Create(const TVec2& _vOrig, const TVec2& _vDir)
		{
			m_vOrig = _vOrig;
			m_vDir = _vDir;
		}

		__CUDA_HDI__ void Create(const _SLine2D<TValue>& xLine)
		{
			m_vOrig = xLine.m_vOrig;
			m_vDir = xLine.m_vDir;
		}

		__CUDA_HDI__ const TVec2& Origin() const
		{
			return m_vOrig;
		}

		__CUDA_HDI__ const TVec2& Dir() const
		{
			return m_vDir;
		}
	};


	template<class TValue>
	struct _SLineSegment2D : public _SLine2D<TValue>
	{
	public:
		using TThis = _SLineSegment2D<TValue>;
		using TBase = _SLine2D<TValue>;

	protected:
		TValue m_dLength;

	public:
		template<typename T2>
		__CUDA_HDI__ void CastFrom(const _SLineSegment2D<T2>& xLine)
		{
			TBase::CastFrom(xLine);
			m_dLength = TValue(xLine.m_dLength);
		}

		__CUDA_HDI__ void Create(const TVec2& vA, const TVec2& vB)
		{
			m_vOrig = vA;
			m_vDir = vB - vA;
			m_dLength = Clu::Length(m_vDir);
			m_vDir /= m_dLength;
		}

		__CUDA_HDI__ TValue Length() const
		{
			return m_dLength;
		}

		__CUDA_HDI__ TVec2 Start() const
		{
			return m_vOrig;
		}

		__CUDA_HDI__ TVec2 End() const
		{
			return m_vOrig + m_dLength * m_vDir;
		}

		__CUDA_HDI__ bool IsInside(const TVec2& vX, TValue fPrec) const
		{
			TVec2 vRel = vX - m_vOrig;

			// The component along the direction
			TValue dF_par = Dot(vRel, m_vDir);
			// the component perpendicular to the direction
			TValue dF_perp = abs(Determinant(vRel, m_vDir));

			return (dF_perp <= fPrec) && (dF_par >= -TValue(fPrec)) && (dF_par <= m_dLength + fPrec);
		}
	};


	template<class TValue>
	struct _SQuad2D
	{
	public:
		using TThis = _SQuad2D<TValue>;
		using TVec2 = _SVector<TValue, 2>;
		using TLineSeg2D = _SLineSegment2D<TValue>;
		using TIdx = uint32_t;

	protected:
		TLineSeg2D m_pEdges[4];

	public:
		template<typename FuncOp>
		void ForEachEdgeIdx(FuncOp funcOp)
		{
			for (TIdx uIdx = 0; uIdx < 4; ++uIdx)
			{
				funcOp(m_pEdges[uIdx], uIdx);
			}
		}

		template<typename FuncOp>
		void ForEachEdgeIdx(FuncOp funcOp) const
		{
			for (TIdx uIdx = 0; uIdx < 4; ++uIdx)
			{
				funcOp(m_pEdges[uIdx], uIdx);
			}
		}

		__CUDA_HDI__ const TLineSeg2D& Edge(TIdx uIdx) const
		{
			CLU_ASSERT(uIdx < 4);
			return m_pEdges[uIdx];
		}

		template<typename T2>
		__CUDA_HDI__ void CastFrom(const _SQuad2D<T2>& xQuad)
		{
			ForEachEdgeIdx([&xQuad](TLineSeg2D& xLineSeg, TIdx uIdx)
			{
				xLineSeg.CastFrom(xQuad.Edge(uIdx));
			});
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// Creates a quad in 2D from its corners. The corners have to be given in counter clockwise
		/// order.
		/// </summary>
		///
		/// <param name="vTL">	The tl. </param>
		/// <param name="vBL">	The bl. </param>
		/// <param name="vBR">	The line break. </param>
		/// <param name="vTR">	The tr. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		__CUDA_HDI__ void Create(const TVec2& vTL, const TVec2& vBL, const TVec2& vBR, const TVec2& vTR)
		{
			m_pEdges[0].Create(vTL, vBL);
			m_pEdges[1].Create(vBL, vBR);
			m_pEdges[2].Create(vBR, vTR);
			m_pEdges[3].Create(vTR, vTL);
		}

		__CUDA_HDI__ void Create(const TThis& xLine)
		{
			ForEachEdgeIdx([&xLine](TLineSeg2D& xLineSeg, TIdx uIdx)
			{
				xLineSeg.Create(xLine.Edge(uIdx));
			});
		}

	};


}	// Clu
