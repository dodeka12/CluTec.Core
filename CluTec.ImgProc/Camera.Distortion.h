////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.ImgProc
// file:      Camera.Distortion.h
//
// summary:   Declares the camera. distortion class
//
//            Copyright (c) 2016 CluTec. All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "CluTec.Math/Static.Vector.h"
#include "Camera.Enums.h"

namespace Clu
{
	namespace Camera
	{
		template<typename TValue> class _CPinhole;

		template<typename _TValue, EDistStyle t_eStyle>
		class _CDistortion
		{
		};

		template<typename _TValue>
		class _CDistortion<_TValue, EDistStyle::OpenCV>
		{
		public:
			static const EDistStyle Style = EDistStyle::OpenCV;

			using TValue = _TValue;
			using TThis = _CDistortion<TValue, Style>;
			using TPinhole = _CPinhole<TValue>;

			using TVec2 = _SVector<TValue, 2>;
			using TVec3 = _SVector<TValue, 3>;
			using TVec6 = _SVector<TValue, 6>;


		protected:
			TVec6 m_vK;
			TVec2 m_vP;

		public:

			void Reset()
			{
				m_vK.SetZero();
				m_vP.SetZero();
			}

			void Create(TValue fP1, TValue fP2, TValue fK1, TValue fK2, TValue fK3, TValue fK4, TValue fK5, TValue fK6)
			{
				m_vP.SetElements(fP1, fP2);
				m_vK.SetElements(fK1, fK2, fK3, fK4, fK5, fK6);
			}

			template<typename TValue2>
			void CastFrom(const _CDistortion<TValue2, Style>& xDistort)
			{
				m_vP.CastFrom(xDistort.ParsP());
				m_vK.CastFrom(xDistort.ParsK());
			}

			const TVec2& ParsP() const
			{
				return m_vP;
			}

			const TVec6& ParsK() const
			{
				return m_vK;
			}

			template<uint32_t t_uDim>
			__CUDA_HDI__ void DistortPX(_SVector<TValue, t_uDim>& vDistPX, const _SVector<TValue, t_uDim>& vPosPX, const TPinhole& camPinhole) const
			{
				static_assert(t_uDim >= 2, "Given vector has to be of dimension 2 at least");

				TVec3 vPos;

				camPinhole.Sensor().Map_PixelIX_to_SensorM(vPos, vPosPX[0], vPosPX[1]);
				vPos -= camPinhole.PinholeM_s();
				vPos /= camPinhole.FocalLength();

				TValue fR2 = vPos[0] * vPos[0] + vPos[1] * vPos[1];
				TValue fR4 = fR2 * fR2;
				TValue fR6 = fR4 * fR2;
				TValue fPoly = (TValue(1) + m_vK[0] * fR2 + m_vK[1] * fR4 + m_vK[2] * fR6)
					/ (TValue(1) + m_vK[3] * fR2 + m_vK[4] * fR4 + m_vK[5] * fR6);

				TVec3 vDist;
				vDist[0] = fPoly * vPos[0]
					+ TValue(2) * m_vP[0] * (vPos[0] * vPos[1]) 
					+ m_vP[1] * (fR2 + TValue(2) * vPos[0] * vPos[0]);

				vDist[1] = fPoly * vPos[1]
					+ TValue(2) * m_vP[1] * (vPos[0] * vPos[1])
					+ m_vP[0] * (fR2 + TValue(2) * vPos[1] * vPos[1]);

				vDist[2] = vPos[2];

				vDist *= camPinhole.FocalLength();
				vDist += camPinhole.PinholeM_s();
				camPinhole.Sensor().Map_SensorM_to_PixelF(vDistPX[0], vDistPX[1], vDist);
			}
		};
	}
}