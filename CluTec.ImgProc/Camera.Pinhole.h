////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.ImgProc
// file:      Camera.Pinhole.h
//
// summary:   Declares the camera. pinhole class
//
//            Copyright (c) 2016 CluTec. All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "CluTec.Math/Static.Vector.h"
#include "CluTec.Math/Static.Matrix.h"
#include "CluTec.Math/Frame3D.h"
#include "CluTec.Math/Static.Geometry.h"
#include "CluTec.Math/Static.Geometry.Math.h"
#include "CluTec.Math/ValuePrecision.h"

#include "Camera.Enums.h"
#include "Camera.Sensor.h"
#include "Camera.Distortion.h"

namespace Clu
{
	namespace Camera
	{
		enum class ERectifyCropStyle
		{
			InnerRectangle = 0,
			OuterRectangle,
		};


		template<typename TValue>
		class _CPinhole
		{
		public:
			using TThis = _CPinhole<TValue>;
			using TSensor = _CSensor<TValue, -1, 1>;
			using TDistort = _CDistortion<TValue, EDistStyle::OpenCV>;

			using TIdx = uint32_t;
			using TFrame3D = _CFrame3D<TValue>;

			using TUVec2 = _SVector<TIdx, 2>;

			using TVec2 = _SVector<TValue, 2>;
			using TVec3 = _SVector<TValue, 3>;
			using TVec5 = _SVector<TValue, 5>;
			using TMat3 = _SMatrix<TValue, 3>;

		protected:
			/// <summary>	The pinhole camera sensor. </summary>
			TSensor m_xSensor;


			/// <summary>	The metric position of the pinhole given in the sensor frame. 
			/// 			The focal length is the negative z-component of this vector, as 
			/// 			the standard z-axis points towards the observer.
			/// 			The x,y-components of this vector give the position of the principal 
			/// 			point wrt. the sensor center in meters.</summary>
			TVec3 m_vPinholeM_s;

			TDistort m_xDistort;
			
		public:

			__CUDA_HDI__ TThis& operator= (const TThis& xPinhole)
			{
				m_xSensor = xPinhole.m_xSensor;
				m_vPinholeM_s = xPinhole.m_vPinholeM_s;
				m_xDistort = xPinhole.m_xDistort;
				return *this;
			}

			__CUDA_HDI__ void Create(const TSensor& xSensor, const TVec3& vPinholeM_s)
			{
				m_xSensor = xSensor;
				m_vPinholeM_s = vPinholeM_s;
				m_xDistort.Reset();
			}
			
			__CUDA_HDI__ void Create(const TSensor& xSensor, const TVec3& vPinholeM_s, const TDistort& xDistort)
			{
				m_xSensor = xSensor;
				m_vPinholeM_s = vPinholeM_s;
				m_xDistort = xDistort;
			}

			template<typename TValue2>
			__CUDA_HDI__ void CastFrom(const _CPinhole<TValue2>& xPinhole)
			{
				m_xSensor.CastFrom(xPinhole.Sensor());
				m_vPinholeM_s.CastFrom(xPinhole.PinholeM_s());
				m_xDistort.CastFrom(xPinhole.Distortion());
			}

			__CUDA_HDI__ TValue FocalLength() const
			{
				return abs(m_vPinholeM_s[2]);
			}

			////////////////////////////////////////////////////////////////////////////////////////////////////
			/// <summary>	Gets the sensor object. </summary>
			///
			/// <returns>	A const. </returns>
			////////////////////////////////////////////////////////////////////////////////////////////////////

			__CUDA_HDI__ const TSensor& Sensor() const
			{
				return m_xSensor;
			}

			__CUDA_HDI__ TVec3 PinholeM_s() const
			{
				return m_vPinholeM_s;
			}

			////////////////////////////////////////////////////////////////////////////////////////////////////
			/// <summary>	Position of the pinhole in the world frame in units of meters. </summary>
			///
			/// <returns>	A TVec3. </returns>
			////////////////////////////////////////////////////////////////////////////////////////////////////

			__CUDA_HDI__ TVec3 PinholeM_w() const
			{
				return m_xSensor.FrameM_s_w().MapOutOfFrame(m_vPinholeM_s);
			}


			__CUDA_HDI__ const TDistort& Distortion() const
			{
				return m_xDistort;
			}

			__CUDA_HDI__ void SetDistortion(const TDistort& xDistort)
			{
				m_xDistort = xDistort;
			}

			template< EStyle t_eStyle>
			__CUDA_HDI__ void CreateFromStyle(const TMat3& mK, const TMat3& mR, const TVec3& vT, const TUVec2& vResolutionPX, TValue dPixelSize);

			////////////////////////////////////////////////////////////////////////////////////////////////////
			/// <summary>
			/// Create a pinhole camera from data in OpenCV style. 
			/// 
			/// EStyle::OpenCV:
			/// - The coordinate system is: x to right, y down, z towards scene.  
			/// - The pixel with index (0,0) lies at the top left corner of the monitor image.
			/// - The origin of the pixel coordinate system lies at the top left corner of the top left pixel.
			/// - Translation vector points to center of projection in world coordinate system. Units are
			/// meters.
			/// - Camera matrix units are pixels.
			/// </summary>
			///
			/// <typeparam name="EStyle::OpenCV">	Type of the style open cv. </typeparam>
			/// <param name="mK">			 	The m k. </param>
			/// <param name="mR">			 	The m r. </param>
			/// <param name="vT">			 	The v t. </param>
			/// <param name="vResolution_px">	The resolution px. </param>
			/// <param name="dPixelSizeX">	 	Horizontal pixel size. </param>
			////////////////////////////////////////////////////////////////////////////////////////////////////

			template<>
			__CUDA_HDI__ void CreateFromStyle<EStyle::OpenCV>(const TMat3& mK, const TMat3& mR, const TVec3& vT, const TUVec2& vResolutionPX, TValue dPixelSizeX)
			{

				TMat3 mRot_l_r;
				TMat3 mNegYZ;
				TVec3 vTrans_l_r;
				TVec2 vPixelSizeM;

				mNegYZ.SetZero();
				mNegYZ(0, 0) = TValue(1);
				mNegYZ(1, 1) = TValue(-1);
				mNegYZ(2, 2) = TValue(-1);

				// In OpenCV style a point in the local camera frame is transformed to the world frame via: mR * vX_l + vT = vX_w.

				//// The columns of mR give the basis vectors of the camera frame in OpenCV style, i.e. right-down-towards scene.
				//// We need to flip y and z axis to convert this to our style right-up-towards observer (like OpenGL).
				//mRot_l_r.ForEachRowPair(mR, 0, [](TValue& xValue, const TValue& xValR)
				//{
				//	xValue = xValR;
				//});

				//mRot_l_r.ForEachRowPair(mR, 1, [](TValue& xValue, const TValue& xValR)
				//{
				//	xValue = -xValR;
				//});

				//mRot_l_r.ForEachRowPair(mR, 2, [](TValue& xValue, const TValue& xValR)
				//{
				//	xValue = -xValR;
				//});

				{
					TMat3 mTemp;
					MatrixProduct<0, 0>(mTemp, mNegYZ, mR);
					MatrixProduct<0, 0>(mRot_l_r, mTemp, mNegYZ);
				}

				// Also flip axes of translation vector
				vTrans_l_r[0] = vT[0];
				vTrans_l_r[1] = -vT[1];
				vTrans_l_r[2] = -vT[2];

				TValue dFocalLength_m = mK(0, 0) * dPixelSizeX;
				TValue dFocalAspect = mK(1, 1) / mK(0, 0);

				vPixelSizeM.SetElements(dPixelSizeX, dFocalAspect * dPixelSizeX);

				TVec2 vRes_px;
				vRes_px.CastFrom(vResolutionPX);

				TFrame3D xFrame;

				// The translation vector is not correct, yet, since it points to the optical center
				// and not the sensor center. We create the sensor nonetheless to easily calculate 
				// the principal point offset in the image plane. Then we re-create the sensor
				// with an updated translation vector.
				xFrame.Create(mRot_l_r, vTrans_l_r);
				m_xSensor.Create(xFrame, vResolutionPX, vPixelSizeM);

				// Map the pixel position of the principal point to a metric position in the sensor frame.
				// Since the origin of the OpenCV pixel coordinate system is the top-left corner of the 
				// top-left pixel and our origin is the pixel's center, we need to subtract one half.
				m_xSensor.Map_PixelIX_to_SensorM(m_vPinholeM_s, mK(0, 2) - TValue(0.5), mK(1, 2) - TValue(0.5));

				// In the sensor coordinate system the focal point lies along the negative z-axis.
				m_vPinholeM_s[2] = -dFocalLength_m;

				// The given translation vector points to the optical center in world frame coordinates.
				// We need to subtract the pinhole position vector transformed into world coordinates
				// from the translation vector, such that vPinhole_m points to the optical center
				// from the sensor center in sensor coordinates.
				vTrans_l_r -= mRot_l_r * m_vPinholeM_s;

				// Create Sensor again with updated translation vector
				xFrame.Create(mRot_l_r, vTrans_l_r);
				m_xSensor.Create(xFrame, vResolutionPX, vPixelSizeM);
			}

			////////////////////////////////////////////////////////////////////////////////////////////////////
			/// <summary>	Middlebury>s. </summary>
			///
			/// <typeparam name="EStyle::Middlebury">	Type of the style middlebury. </typeparam>
			/// <param name="mK">				The m k. </param>
			/// <param name="mR">				The m r. </param>
			/// <param name="vT">				The v t. </param>
			/// <param name="vResolutionPX">	The resolution px. </param>
			/// <param name="dPixelSizeX">  	The pixel size x coordinate. </param>
			////////////////////////////////////////////////////////////////////////////////////////////////////

			template<>
			__CUDA_HDI__ void CreateFromStyle<EStyle::Middlebury>(const TMat3& mK, const TMat3& mR, const TVec3& vT, const TUVec2& vResolutionPX, TValue dPixelSizeX)
			{

				TVec2 vPixelSizeM;
				TMat3 mRot_l_r(mR);
				TVec3 vTrans_l_r(vT);


				TValue dFocalLength_m = mK(0, 0) * dPixelSizeX;
				TValue dFocalAspect = mK(1, 1) / mK(0, 0);

				vPixelSizeM.SetElements(dPixelSizeX, dFocalAspect * dPixelSizeX);

				TVec2 vRes_px;
				vRes_px.CastFrom(vResolutionPX);

				TFrame3D xFrame;

				// The translation vector is not correct, yet, since it points to the optical center
				// and not the sensor center. We create the sensor nonetheless to easily calculate 
				// the principal point offset in the image plane. Then we re-create the sensor
				// with an updated translation vector.
				xFrame.Create(mRot_l_r, vTrans_l_r);
				m_xSensor.Create(xFrame, vResolutionPX, vPixelSizeM);

				// Map the pixel position of the principal point to a metric position in the sensor frame.
				// Since the origin of the OpenCV pixel coordinate system is the top-left corner of the 
				// top-left pixel and our origin is the pixel's center, we need to subtract one half.
				m_xSensor.Map_PixelIX_to_SensorM(m_vPinholeM_s, mK(0, 2) - TValue(0.5), mK(1, 2) - TValue(0.5));

				// In the sensor coordinate system the focal point lies along the negative z-axis.
				m_vPinholeM_s[2] = -dFocalLength_m;

				// The given translation vector points to the optical center in world frame coordinates.
				// We need to subtract the pinhole position vector transformed into world coordinates
				// from the translation vector, such that vPinhole_m points to the optical center
				// from the sensor center in sensor coordinates.
				vTrans_l_r -= mRot_l_r * m_vPinholeM_s;

				// Create Sensor again with updated translation vector
				xFrame.Create(mRot_l_r, vTrans_l_r);
				m_xSensor.Create(xFrame, vResolutionPX, vPixelSizeM);
			}

			////////////////////////////////////////////////////////////////////////////////////////////////////
			/// <summary>	Halcon>s. </summary>
			///
			/// <typeparam name="EStyle::Halcon">	Type of the style halcon. </typeparam>
			/// <param name="mK">				The m k. </param>
			/// <param name="mR">				The m r. </param>
			/// <param name="vT">				The v t. </param>
			/// <param name="vResolutionPX">	The resolution px. </param>
			/// <param name="dPixelSizeX">  	The pixel size x coordinate. </param>
			////////////////////////////////////////////////////////////////////////////////////////////////////

			template<typename T>
			__CUDA_HDI__ void CreateFromStyle_Halcon(T dFocalLength, T dPixSizeX, T dPixSizeY
				, T dCenterPixX, T dCenterPixY, unsigned uPixCountX, unsigned uPixCountY
				, const TMat3& mR, const TVec3& vT)
			{
				TUVec2 vResolutionPX;
				TVec2 vPixelSizeM;
				TMat3 mRot_l_r;
				TMat3 mNegYZ;
				TVec3 vTrans_l_r;

				mNegYZ.SetZero();
				mNegYZ(0, 0) = TValue(1);
				mNegYZ(1, 1) = TValue(-1);
				mNegYZ(2, 2) = TValue(-1);

				{
					TMat3 mTemp;
					MatrixProduct<0, 0>(mTemp, mNegYZ, mR);
					MatrixProduct<0, 0>(mRot_l_r, mTemp, mNegYZ);
				}

				// Also flip axes of translation vector
				vTrans_l_r[0] = vT[0];
				vTrans_l_r[1] = -vT[1];
				vTrans_l_r[2] = -vT[2];


				TValue dFocalLength_m = (TValue)dFocalLength;
				TValue dFocalAspect = TValue(dPixSizeY) / TValue(dPixSizeX);

				vPixelSizeM.SetElements(dPixSizeX, dPixSizeY);
				vResolutionPX.SetElements(uPixCountX, uPixCountY);

				TFrame3D xFrame;

				// The translation vector is not correct, yet, since it points to the optical center
				// and not the sensor center. We create the sensor nonetheless to easily calculate 
				// the principal point offset in the image plane. Then we re-create the sensor
				// with an updated translation vector.
				xFrame.Create(mRot_l_r, vTrans_l_r);
				m_xSensor.Create(xFrame, vResolutionPX, vPixelSizeM);

				// Map the pixel position of the principal point to a metric position in the sensor frame.
				// Since the origin of the OpenCV pixel coordinate system is the top-left corner of the 
				// top-left pixel and our origin is the pixel's center, we need to subtract one half.
				m_xSensor.Map_PixelIX_to_SensorM(m_vPinholeM_s, dCenterPixX - TValue(0.5), dCenterPixY - TValue(0.5));

				// In the sensor coordinate system the focal point lies along the negative z-axis.
				m_vPinholeM_s[2] = -dFocalLength_m;

				// The given translation vector points to the optical center in world frame coordinates.
				// We need to subtract the pinhole position vector transformed into world coordinates
				// from the translation vector, such that vPinhole_m points to the optical center
				// from the sensor center in sensor coordinates.
				vTrans_l_r -= mRot_l_r * m_vPinholeM_s;

				// Create Sensor again with updated translation vector
				xFrame.Create(mRot_l_r, vTrans_l_r);
				m_xSensor.Create(xFrame, vResolutionPX, vPixelSizeM);

				// //////////////////////////////////////////////////////////
				// Debug
				//TVec3 vX, vY, vZ;
				//xFrame.GetBasis_l_r(vX, vY, vZ);

				return;
			}


			////////////////////////////////////////////////////////////////////////////////////////////////////
			/// <summary>
			/// Creates a pinhole camera from a camera matrix (mK), a rotation matrix (mR), a translation vector (vT), a sensor
			/// resolution in pixels (vResolution_px) and the pixel size.
			/// eStyle defines in what overall coordinate system and with which units the data is given.
			/// 
			/// EStyle::OpenCV:
			/// - The coordinate system is: x to right, y down, z towards scene.  
			/// - The pixel with index (0,0) lies at the top left corner of the monitor image.   
			/// - The origin of the pixel coordinate system lies at the top left corner of the top left pixel.
			/// - Translation vector points to center of projection in world coordinate system. Units are meters.
			/// - Camera matrix units are pixels.
			/// </summary>
			///
			/// <param name="mK">			 	The camera matrix. </param>
			/// <param name="mR">			 	The rotation matrix. </param>
			/// <param name="vT">			 	The translation vector. </param>
			/// <param name="vResolution_px">	The resolution in pixels. </param>
			/// <param name="dPixelSize">	  	The pixel size. </param>
			/// <param name="eStyle">		 	The data style. </param>
			////////////////////////////////////////////////////////////////////////////////////////////////////

			__CUDA_HDI__ void Create(const TMat3& mK, const TMat3& mR, const TVec3& vT, const TUVec2& vResolution_px, TValue dPixelSize, EStyle eStyle)
			{
#if defined(__NVCC__)
				if (eStyle == EStyle::OpenCV)
				{
					CreateFromStyle <EStyle::OpenCV>(mK, mR, vT, vResolution_px, dPixelSize);
				}
#else
				switch (eStyle)
				{
				case EStyle::OpenCV:
					CreateFromStyle <EStyle::OpenCV>(mK, mR, vT, vResolution_px, dPixelSize);
					break;

				default:
					throw CLU_EXCEPTION("Given pinhole camera style not implemented");
					break;
				}
#endif
			}

			__CUDA_HDI__ void AdjustSensorResolutionPX(const TVec2& vRes_px)
			{
				m_xSensor.SetResolutionPX(vRes_px);
			}

			////////////////////////////////////////////////////////////////////////////////////////////////////
			/// <summary>	Map a pixel index coordinate to the corresponding world coordinate in meters. </summary>
			///
			/// <typeparam name="TPixIdx">	Type of the pix index. </typeparam>
			/// <param name="vPos">	[in,out] The position. </param>
			/// <param name="iX">  	Zero-based index of the x coordinate. </param>
			/// <param name="iY">  	Zero-based index of the y coordinate. </param>
			////////////////////////////////////////////////////////////////////////////////////////////////////

			template<typename TPixIdx>
			__CUDA_HDI__ void Map_PixelIX_to_WorldM(TVec3& vPos_w, TPixIdx iX, TPixIdx iY) const
			{
				TVec3 vPos_s;
				m_xSensor.Map_PixelIX_to_SensorM(vPos_s, iX, iY);
				vPos_w = m_xSensor.FrameM_s_w().MapOutOfFrame(vPos_s);
			}

			template<typename TPixIdx>
			__CUDA_HDI__ void Map_PixelIX_to_WorldM(TVec3& vPos_w, TPixIdx iX, TPixIdx iY, const Clu::_SImageFormat& xF) const
			{
				TVec3 vPos_s;
				m_xSensor.Map_PixelIX_to_SensorM(vPos_s, iX, iY, xF);
				vPos_w = m_xSensor.FrameM_s_w().MapOutOfFrame(vPos_s);
			}


			////////////////////////////////////////////////////////////////////////////////////////////////////
			/// <summary>	Map world m to pixel index. </summary>
			///
			/// <typeparam name="TPixIdx">	Type of the pix index. </typeparam>
			/// <param name="vPos">	[in,out] The position. </param>
			/// <param name="iX">  	Zero-based index of the x coordinate. </param>
			/// <param name="iY">  	Zero-based index of the y coordinate. </param>
			////////////////////////////////////////////////////////////////////////////////////////////////////

			template<typename TPixIdx>
			__CUDA_HDI__ void Map_WorldM_to_PixelIX(TPixIdx& iX, TPixIdx& iY, const TVec3& vPos_w) const
			{
				TVec3 vPos_s;
				vPos_s = m_xSensor.FrameM_s_w().MapIntoFrame(vPos_w);
				m_xSensor.Map_SensorM_to_PixelIX(iX, iY, vPos_s);
			}

			////////////////////////////////////////////////////////////////////////////////////////////////////
			/// <summary>	Project pixel at given index to world position at given depth. 
			/// 			If the point lies in front of the sensor the depth value has to be negative.</summary>
			///
			/// <typeparam name="TPixIdx">	Type of the pix index. </typeparam>
			/// <param name="vPos_w">   	[in,out] The position w. </param>
			/// <param name="iX">			Zero-based index of the x coordinate. </param>
			/// <param name="iY">			Zero-based index of the y coordinate. </param>
			/// <param name="dDepthM_s">	The depth m s. </param>
			////////////////////////////////////////////////////////////////////////////////////////////////////

			template<typename TPixIdx>
			__CUDA_HDI__ void Project_PixelIX_to_WorldM(TVec3& vPos_w, TPixIdx iX, TPixIdx iY, TValue dDepthM_s) const
			{
				TVec3 vPos_s;
				m_xSensor.Map_PixelIX_to_SensorM(vPos_s, iX, iY);

				// Set the depth of the point in sensor coordinates
				vPos_s[2] = dDepthM_s;

				// If dDepthM_s is negative the point lies in front of the sensor, otherwise behind it.
				// If the pinhole is in front of the sensor plane, its z-component is negative.
				// dScale = (dDepthM_s - m_vPinholeM_s[2]) / m_vPinholeM_s[2];
				TValue dScale = vPos_s[2] / m_vPinholeM_s[2] - TValue(1);

				// Map coordinates relative to pinhole, then scale and then map back to sensor frame
				vPos_s[0] = (vPos_s[0] - m_vPinholeM_s[0]) * -dScale + m_vPinholeM_s[0];
				vPos_s[1] = (vPos_s[1] - m_vPinholeM_s[1]) * -dScale + m_vPinholeM_s[1];

				// Map into world coordinates
				vPos_w = m_xSensor.FrameM_s_w().MapOutOfFrame(vPos_s);
			}

			////////////////////////////////////////////////////////////////////////////////////////////////////
			/// <summary>	Project a world point onto the sensor pixel plane. </summary>
			///
			/// <param name="dX">	   	[in,out] The d x coordinate. </param>
			/// <param name="dY">	   	[in,out] The d y coordinate. </param>
			/// <param name="dDepth_s">	[in,out] The depth s. </param>
			/// <param name="vPos_w">  	[in,out] The position w. </param>
			////////////////////////////////////////////////////////////////////////////////////////////////////

			__CUDA_HDI__ void Project_WorldM_to_PixelF(TValue& dX, TValue& dY, TValue& dDepth_s, const TVec3& vPos_w) const
			{
				TVec3 vPos_s;

				vPos_s = m_xSensor.FrameM_s_w().MapIntoFrame(vPos_w);

				Project_SensorM_to_PixelF(dX, dY, dDepth_s, vPos_s);
			}

			////////////////////////////////////////////////////////////////////////////////////////////////////
			/// <summary>	Project world m to pixel f. </summary>
			///
			/// <param name="dX">	   	[in,out] The d x coordinate. </param>
			/// <param name="dY">	   	[in,out] The d y coordinate. </param>
			/// <param name="dDepth_s">	[in,out] The depth s. </param>
			/// <param name="vPos_w">  	The position w. </param>
			/// <param name="xF">	   	The x coordinate f. </param>
			////////////////////////////////////////////////////////////////////////////////////////////////////

			__CUDA_HDI__ void Project_WorldM_to_PixelF(TValue& dX, TValue& dY, TValue& dDepth_s, const TVec3& vPos_w, const Clu::_SImageFormat& xF) const
			{
				TVec3 vPos_s;

				vPos_s = m_xSensor.FrameM_s_w().MapIntoFrame(vPos_w);

				Project_SensorM_to_PixelF(dX, dY, dDepth_s, vPos_s, xF);
			}


			__CUDA_HDI__ void Project_SensorM_to_PixelF(TValue& dX, TValue& dY, TValue& dDepth_s, const TVec3& vPos_s) const
			{
				// If vPos_s[2] is negative the point lies in front of the sensor, otherwise behind it.
				// If the pinhole is in front of the sensor plane, its z-component is negative.
				TValue dScale = vPos_s[2] / m_vPinholeM_s[2] - TValue(1);

				TVec3 vPos;
				
				// Map coordinates relative to pinhole, then scale and then map back to sensor frame
				vPos[0] = (vPos_s[0] - m_vPinholeM_s[0]) / -dScale + m_vPinholeM_s[0];
				vPos[1] = (vPos_s[1] - m_vPinholeM_s[1]) / -dScale + m_vPinholeM_s[1];

				// Map into sensor pixel coordinate frame
				m_xSensor.Map_SensorM_to_PixelF(dX, dY, vPos);

				dDepth_s = vPos_s[2];
			}

			__CUDA_HDI__ void Project_SensorM_to_PixelF(TValue& dX, TValue& dY, TValue& dDepth_s, const TVec3& vPos_s, const Clu::_SImageFormat& xF) const
			{
				// If vPos_s[2] is negative the point lies in front of the sensor, otherwise behind it.
				// If the pinhole is in front of the sensor plane, its z-component is negative.
				TValue dScale = vPos_s[2] / m_vPinholeM_s[2] - TValue(1);

				TVec3 vPos;

				// Map coordinates relative to pinhole, then scale and then map back to sensor frame
				vPos[0] = (vPos_s[0] - m_vPinholeM_s[0]) / -dScale + m_vPinholeM_s[0];
				vPos[1] = (vPos_s[1] - m_vPinholeM_s[1]) / -dScale + m_vPinholeM_s[1];

				// Map into sensor pixel coordinate frame
				m_xSensor.Map_SensorM_to_PixelF(dX, dY, vPos, xF);

				dDepth_s = vPos_s[2];
			}


			////////////////////////////////////////////////////////////////////////////////////////////////////
			/// <summary>
			/// Create a new pinhole camera with the same optical center but with the given orientation.
			/// </summary>
			///
			/// <param name="vDirX_w">	The dir x coordinate w. </param>
			/// <param name="vDirY_w">	The dir y coordinate w. </param>
			/// <param name="vDirZ_w">	The dir z coordinate w. </param>
			///
			/// <returns>	The TThis. </returns>
			////////////////////////////////////////////////////////////////////////////////////////////////////

			void GetRectified(TThis& xCam_r, const TVec3& vDirX_w, const TVec3& vDirY_w, const TVec3& vDirZ_w, TValue fRectFocalLength, ERectifyCropStyle eCropStyle)
			{
				using TLine2D = _SLine2D<TValue>;
				using TQuad2D = _SQuad2D<TValue>;
				using TRect2D = _SAlignedRect2D<TValue>;

				// The rectified camera frames with origin on the optical centers (pinhole).
				// Maps from rectified frame into world frame.
				TFrame3D xFrameOC_r_w;

				// The combined frame that maps from the original cameras' sensor frame into
				// the rectified frame with origin on pinhole.
				TFrame3D xFrameOC_s_r;

				// Get the pinhole position in world coordinates
				TVec3 vPinhole_w;
				vPinhole_w = PinholeM_w();

				xFrameOC_r_w.Create(vDirX_w, vDirY_w, vDirZ_w, vPinhole_w);
				Sensor().FrameM_s_w().ConcatFrames_Out_In(xFrameOC_s_r, xFrameOC_r_w);

				TVec3 pvCorner[4];
				TVec2 pvCorner_s[4];
				TVec2 pvPixCorner[4];

				// Sensor pixel resolution
				TVec2 vRes = Sensor().ResolutionPX();

				// Top-left (monitor pixel coordinates)
				pvPixCorner[0].SetElements(0, 0);
				// Bottom-left
				pvPixCorner[1].SetElements(0, vRes[1]);
				// Bottom-right
				pvPixCorner[2].SetElements(vRes[0], vRes[1]);
				// Top-right
				pvPixCorner[3].SetElements(vRes[0], 0);

				// Map pixel corners to rectified pinhole frame.
				for (TIdx uIdx = 0; uIdx < 4; ++uIdx)
				{
					// Map from pixel index to metric position on sensor in sensor frame
					Sensor().Map_PixelIX_to_SensorM(pvCorner[uIdx], pvPixCorner[uIdx][0], pvPixCorner[uIdx][1]);
					// Map from sensor frame into rectified pinhole frame.
					pvCorner[uIdx] = xFrameOC_s_r.MapOutOfFrame(pvCorner[uIdx]);
					// Project the corner onto the projection plane at focal length distance along z-axis
					pvCorner[uIdx] *= fRectFocalLength / pvCorner[uIdx][2];


					// Reduce to 2D vector
					pvCorner_s[uIdx].SetElements(pvCorner[uIdx][0], pvCorner[uIdx][1]);
				}

				// Create a quadrilateral out of the four corners.
				TQuad2D xQuad;
				xQuad.Create(pvCorner_s[0], pvCorner_s[1], pvCorner_s[2], pvCorner_s[3]);

				// Now we need to find the largest rectangle with the same aspect ratio as the original sensor
				// that is centered on the line connecting the two optical centers.
				TRect2D xRect;

				if (eCropStyle == ERectifyCropStyle::InnerRectangle)
				{
					TLine2D xCtrLine;
					TVec2 vOrig_r, vDirX_r;
					vOrig_r.SetZero();
					vDirX_r.SetElements(1, 0);
					xCtrLine.Create(vOrig_r, vDirX_r);

					if (!TryFindLargestRectangleInsideQuadOnLine(xRect, xQuad, xCtrLine, vRes[1] / vRes[0], Clu::CValuePrecision<TValue>::DefaultPrecision()))
					{
						throw CLU_EXCEPTION("Cannot find rectified sensor rectangle");
					}
				}
				else if (eCropStyle == ERectifyCropStyle::OuterRectangle)
				{
					TValue dMinX = pvCorner_s[0][0];
					TValue dMaxX = dMinX;
					TValue dMinY = pvCorner_s[0][1];
					TValue dMaxY = dMinY;

					for (int i = 1; i < 4; ++i)
					{
						dMinX = Clu::Min(dMinX, pvCorner_s[i][0]);
						dMaxX = Clu::Max(dMaxX, pvCorner_s[i][0]);

						dMinY = Clu::Min(dMinY, pvCorner_s[i][1]);
						dMaxY = Clu::Max(dMaxY, pvCorner_s[i][1]);
					}

					TValue dMaxAbsY = Clu::Max(Clu::Abs(dMinY), Clu::Abs(dMaxY));

					xRect.Create(dMinX, -dMaxAbsY, dMaxX, dMaxAbsY);
				}
				else
				{
					throw CLU_EXCEPTION("Rectify crop style not supported");
				}


				// The sensor center in the world frame centered on the optical center
				TVec2 vRectCtr2D;
				TVec3 vRectCtr_w, vRectCtrOC_r;

				// Get the rectangle 2D center
				vRectCtr2D = xRect.Center();

				// Get the position of the rectangle center in the rectified frame with origin on the optical center
				vRectCtrOC_r.SetElements(vRectCtr2D[0], TValue(0)/*vRectCtr2D[1]*/, fRectFocalLength);
				// Now map that center out of the frame into the world frame
				vRectCtr_w = xFrameOC_r_w.MapOutOfFrame(vRectCtrOC_r);


				TVec2 vRectSize;
				vRectSize = xRect.Size();

				// Adjust rectangle size to fit an integer number of pixels
				vRectSize = Clu::Floor(vRectSize / Sensor().PixelSizeM());

				// The rectified camera resolution
				TUVec2 vRectRes;
				vRectRes.CastFrom(vRectSize);

				// calculate the metric size
				vRectSize *= Sensor().PixelSizeM();

				// Create the rectified sensor
				TSensor xSensor_r;
				TFrame3D xFrame2D_r;

				// The rectified frame is centered on the rectangle center
				xFrame2D_r.Create(vDirX_w, vDirY_w, vDirZ_w, vRectCtr_w);

				// The pinhole in the rectified frame is the mapping of the world pinhole into the frame.
				TVec3 vPinhole_r = xFrame2D_r.MapIntoFrame(vPinhole_w);

				// Create the rectified sensor
				xSensor_r.Create(xFrame2D_r, vRectRes, Sensor().PixelSizeM());

				// Create the rectified camera
				xCam_r.Create(xSensor_r, vPinhole_r);
			}

		};
	}

}