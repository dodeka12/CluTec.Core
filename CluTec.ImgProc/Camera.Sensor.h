////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.ImgProc
// file:      Camera.Sensor.h
//
// summary:   Declares the camera. sensor class
//
//            Copyright (c) 2016 CluTec. All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include "CluTec.Types1/ImageFormat.h"

#include "CluTec.Math/Static.Vector.h"
#include "CluTec.Math/Static.Matrix.h"
#include "CluTec.Math/Frame3D.h"

namespace Clu
{
	namespace Camera
	{
		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	An image sensor. The frame describes the phyiscal position of the sensor in space.
		/// 			Typically a lens is places in front of the sensor which introduces a point reflection
		/// 			during projection. In that case, the point at the phyiscal bottom right corner of the sensor
		/// 			projects to the top left position of the viewing frustum w.r.t. the sensor frame. 
		/// 			The sensor pixel origin is then at the bottom right corner with the x-axis pointing left 
		/// 			and the y-axis pointing up. On a monitor this point is displayed at the top left corner
		/// 			since it is the first pixel in memory. </summary>
		///
		/// <typeparam name="TValue"> 	Type of the value. </typeparam>
		/// <typeparam name="t_iDirX">	The direction of the horizontal pixel axis. 
		/// 							If +1 x-origin is at left and axis points right. 
		/// 							If -1 x-origin is at right and axis points to left.</typeparam>
		/// <typeparam name="t_iDirY">	The direction of the vertical pixel axis.
		/// 							If +1 y-origin is at bottom and axis points up.
		/// 							If -1 y-origin is at top and axis points down. </typeparam>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		template<typename _TValue, int32_t t_iDirX, int32_t t_iDirY>
		class _CSensor
		{
		public:
			using TThis = _CSensor<_TValue, t_iDirX, t_iDirY>;

			using TValue = _TValue;
			using TDir = int32_t;
			using TIdx = uint32_t;

			using TFrame3D = _CFrame3D<TValue>;
			using TVec2 = _SVector<TValue, 2>;
			using TVec3 = _SVector<TValue, 3>;
			using TUVec2 = _SVector<TIdx, 2>;

			static const TDir DirX = t_iDirX;
			static const TDir DirY = t_iDirY;

		protected:

			////////////////////////////////////////////////////////////////////////////////////////////////////
			/// <summary>
			/// The sensor frame with origin in the center of the sensor. When looking from behind the sensor
			/// towards the scene, the z-axis points towards the observer, i.e. the scene is at negative z-
			/// coordinates. The x-axis points to the right and the y-axis up. The units are meters.
			/// MapIntoFrame() maps world to sensor coordinates.
			/// </summary>
			////////////////////////////////////////////////////////////////////////////////////////////////////

			TFrame3D m_xFrameM_s_w;

			/// <summary>	Horizontal and vertical resolution of the sensor in pixels. </summary>
			TVec2 m_vResolutionPX;

			/// <summary>	The nominal pixel size in meters. </summary>
			TVec2 m_vPixelSizeM;


		public:
			__CUDA_HDI__ TThis& operator= (const TThis& xSensor)
			{
				m_xFrameM_s_w = xSensor.m_xFrameM_s_w;
				m_vResolutionPX = xSensor.m_vResolutionPX;
				m_vPixelSizeM = xSensor.m_vPixelSizeM;
				return *this;
			}

			__CUDA_HDI__ void Create(const TFrame3D& xFrame_m, const TUVec2& vRes_px, const TVec2& vPixSize_m)
			{
				m_xFrameM_s_w = xFrame_m;
				m_vResolutionPX.CastFrom(vRes_px);
				m_vPixelSizeM = vPixSize_m;
			}

			template<typename TValue2>
			__CUDA_HDI__ void CastFrom(const _CSensor<TValue2, t_iDirX, t_iDirY>& xSensor)
			{
				m_xFrameM_s_w.CastFrom(xSensor.FrameM_s_w());
				m_vResolutionPX.CastFrom(xSensor.ResolutionPX());
				m_vPixelSizeM.CastFrom(xSensor.PixelSizeM());
			}

			__CUDA_HDI__ void SetResolutionPX(const TVec2& vRes_px)
			{
				m_vResolutionPX = Floor(vRes_px);
			}

			__CUDA_HDI__ void SetResolutionPX(const TUVec2& vRes_px)
			{
				m_vResolutionPX.CastFrom(vRes_px);
			}

			__CUDA_HDI__ const TFrame3D& FrameM_s_w() const
			{
				return m_xFrameM_s_w;
			}

			__CUDA_HDI__ const TVec2& ResolutionPX() const
			{
				return m_vResolutionPX;
			}

			__CUDA_HDI__ const TVec2& PixelSizeM() const
			{
				return m_vPixelSizeM;
			}


			////////////////////////////////////////////////////////////////////////////////////////////////////
			/// <summary>	Map a pixel index to a metric sensor position. The pixel index has to be given w.r.t.
			/// 			the pixel origin and axis determined by t_iDirX and t_iDirY. For example,
			/// 			the top left pixel on a monitor lies at the bottom right corner of the sensor.
			/// 			The sensor should therefore use t_iDirX = -1 and t_iDirY = 1.
			/// 			A pixel index refers to the center of a pixel. The frame origin lies at the 
			/// 			metric center of the sensor.</summary>
			///
			/// <typeparam name="TPixIdx">	Type of the pix index. </typeparam>
			/// <param name="iX">	Zero-based index of the x coordinate. </param>
			/// <param name="iY">	Zero-based index of the y coordinate. </param>
			///
			/// <returns>	A TVec3. </returns>
			////////////////////////////////////////////////////////////////////////////////////////////////////

			template <typename TPixIdx>
			__CUDA_HDI__ void Map_PixelIX_to_SensorM(TVec3& vPos_m, TPixIdx iX, TPixIdx iY) const
			{
				vPos_m[0] = TValue(DirX) * (TValue(iX) + TValue(0.5) - m_vResolutionPX[0] / TValue(2)) * m_vPixelSizeM[0];
				vPos_m[1] = TValue(DirY) * (TValue(iY) + TValue(0.5) - m_vResolutionPX[1] / TValue(2)) * m_vPixelSizeM[1];
				vPos_m[2] = TValue(0);
			}


			template <typename TPixIdx>
			__CUDA_HDI__ void Map_PixelIX_to_SensorM(TVec3& vPos_m, TPixIdx iX, TPixIdx iY, const Clu::_SImageFormat& xF) const
			{
				TValue fScaleX = TValue(m_vResolutionPX[0]) / TValue(xF.iWidth);
				TValue fScaleY = TValue(m_vResolutionPX[1]) / TValue(xF.iHeight);

				vPos_m[0] = TValue(DirX) * (TValue(iX) + TValue(0.5) - TValue(xF.iWidth) / TValue(2)) * m_vPixelSizeM[0] * fScaleX;
				vPos_m[1] = TValue(DirY) * (TValue(iY) + TValue(0.5) - TValue(xF.iHeight) / TValue(2)) * m_vPixelSizeM[1] * fScaleY;
				vPos_m[2] = TValue(0);
			}


			////////////////////////////////////////////////////////////////////////////////////////////////////
			/// <summary>	Map a metric sensor position to a pixel index. </summary>
			///
			/// <typeparam name="TPixIdx">	Type of the pix index. </typeparam>
			/// <param name="iX">	 	[in,out] Zero-based index of the x coordinate. </param>
			/// <param name="iY">	 	[in,out] Zero-based index of the y coordinate. </param>
			/// <param name="vPos_m">	The position m. </param>
			////////////////////////////////////////////////////////////////////////////////////////////////////

			template <typename TPixIdx>
			__CUDA_HDI__ void Map_SensorM_to_PixelIX(TPixIdx& iX, TPixIdx& iY, const TVec3& vPos_m) const
			{
				iX = TPixIdx(floor(m_vResolutionPX[0] / TValue(2) + TValue(DirX) * TValue(vPos_m[0]) / m_vPixelSizeM[0]));
				iY = TPixIdx(floor(m_vResolutionPX[1] / TValue(2) + TValue(DirY) * TValue(vPos_m[1]) / m_vPixelSizeM[1]));
			}

			////////////////////////////////////////////////////////////////////////////////////////////////////
			/// <summary>	Map a metric sensor position to a floating point pixel coordinate. 
			/// 			The top left corner of the top left pixel (in monitor coordinates) is mapped to 
			/// 			coordinate (-0.5, -0.5).</summary>
			///
			/// <param name="dX">	 	[in,out] The d x coordinate. </param>
			/// <param name="dY">	 	[in,out] The d y coordinate. </param>
			/// <param name="vPos_m">	The position m. </param>
			////////////////////////////////////////////////////////////////////////////////////////////////////

			__CUDA_HDI__ void Map_SensorM_to_PixelF(TValue& dX, TValue& dY, const TVec3& vPos_m) const
			{
				dX = (m_vResolutionPX[0] / TValue(2) - TValue(0.5) + TValue(DirX) * TValue(vPos_m[0]) / m_vPixelSizeM[0]);
				dY = (m_vResolutionPX[1] / TValue(2) - TValue(0.5) + TValue(DirY) * TValue(vPos_m[1]) / m_vPixelSizeM[1]);
			}

			////////////////////////////////////////////////////////////////////////////////////////////////////
			/// <summary>	Map sensor m to pixel f. </summary>
			///
			/// <param name="dX">	 	[in,out] The d x coordinate. </param>
			/// <param name="dY">	 	[in,out] The d y coordinate. </param>
			/// <param name="vPos_m">	The position m. </param>
			/// <param name="xF">	 	The x coordinate f. </param>
			////////////////////////////////////////////////////////////////////////////////////////////////////

			__CUDA_HDI__ void Map_SensorM_to_PixelF(TValue& dX, TValue& dY, const TVec3& vPos_m, const Clu::_SImageFormat& xF) const
			{
				TValue fScaleX = TValue(m_vResolutionPX[0]) / TValue(xF.iWidth);
				TValue fScaleY = TValue(m_vResolutionPX[1]) / TValue(xF.iHeight);

				dX = (TValue(xF.iWidth) / TValue(2) - TValue(0.5) + TValue(DirX) * TValue(vPos_m[0]) / (m_vPixelSizeM[0] * fScaleX));
				dY = (TValue(xF.iHeight) / TValue(2) - TValue(0.5) + TValue(DirY) * TValue(vPos_m[1]) / (m_vPixelSizeM[1] * fScaleY));
			}


		};
	}

}