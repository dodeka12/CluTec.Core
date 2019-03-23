////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.ImgProc
// file:      Camera.StereoPinhole.h
//
// summary:   Declares the camera. stereo pinhole class
//
//            Copyright (c) 2016 CluTec. All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include "CluTec.Math\ValuePrecision.h"
#include "CluTec.Math\Debug.h"

#include "Debug.h"
#include "Camera.Pinhole.h"
#include "DisparityConfig.h"

namespace Clu
{
	namespace Camera
	{
		enum class EStereoRectifyOpticalAxis
		{
			Balanced = 0,
			Left,
			Right,
		};

		template<typename _TValue>
		class _CStereoPinhole
		{
		public:
			using TValue = _TValue;
			using TThis = _CStereoPinhole<TValue>;
			using TPinhole = _CPinhole<TValue>;
			using TIdx = uint32_t;

			using TSensor = typename TPinhole::TSensor;
			using TFrame3D = typename TSensor::TFrame3D;
			using TVec2 = typename TPinhole::TVec2;
			using TVec3 = typename TPinhole::TVec3;
			using TUVec2 = typename TPinhole::TUVec2;

			static const TIdx Left = 0;
			static const TIdx Right = 1;

		protected:
			TPinhole m_pCam[2];

		public:
			__CUDA_HDI__ void Create(const TPinhole& camLeft, const TPinhole& camRight)
			{
				m_pCam[Left] = camLeft;
				m_pCam[Right] = camRight;
			}

			template<typename TValue2>
			__CUDA_HDI__ void CastFrom(const _CStereoPinhole<TValue2>& xStereo)
			{
				m_pCam[Left].CastFrom(xStereo[Left]);
				m_pCam[Right].CastFrom(xStereo[Right]);
			}

			__CUDA_HDI__ TPinhole& operator[] (TIdx uIdx)
			{
				CLU_ASSERT(uIdx < 2);
				return m_pCam[uIdx];
			}

			__CUDA_HDI__ const TPinhole& operator[] (TIdx uIdx) const
			{
				CLU_ASSERT(uIdx < 2);
				return m_pCam[uIdx];
			}

			template<typename FuncOp>
			__CUDA_HDI__ void ForEachCameraIdx(FuncOp funcOp)
			{
				for (TIdx iCamIdx = 0; iCamIdx < 2; ++iCamIdx)
				{
					funcOp(m_pCam[iCamIdx], iCamIdx);
				}
			}


			__CUDA_HDI__ int PrincipalPointOffsetX() const
			{
				const TPinhole& camL = m_pCam[Left];
				const TPinhole& camR = m_pCam[Right];
				TValue dXL, dXR, dY;
				TVec3 vPosL = camL.PinholeM_s();
				TVec3 vPosR = camR.PinholeM_s();

				camL.Sensor().Map_SensorM_to_PixelF(dXL, dY, vPosL);
				camR.Sensor().Map_SensorM_to_PixelF(dXR, dY, vPosR);

				int iOffset = int(floor(dXR - dXL + 0.5));

				// ////////////////////////////////////////////////////////////////
				// Debug
				//int iXL = int(floor(dXL + 0.5));
				//int iXR = int(floor(dXR + 0.5));
				//int iY = int(floor(dY + 0.5));
				//TVec3 vPosL2, vPosR2;

				//camL.Sensor().Map_PixelIX_to_SensorM(vPosL2, iXL, iY);
				//camR.Sensor().Map_PixelIX_to_SensorM(vPosR2, iXR, iY);
				// ////////////////////////////////////////////////////////////////

				return iOffset;
			}

			////////////////////////////////////////////////////////////////////////////////////////////////////
			/// <summary>	Get the infinity pixel offset between left and right image. </summary>
			///
			/// <param name="iMipLevelWidth">	Width of the mip level. </param>
			/// <param name="iMipLevel">	 	Zero-based index of the mip level. </param>
			///
			/// <returns>	An int. </returns>
			////////////////////////////////////////////////////////////////////////////////////////////////////

			__CUDA_HDI__ int InfinityOffset(int iMipLevel) const
			{
				return (PrincipalPointOffsetX() >> iMipLevel);
			}



			////////////////////////////////////////////////////////////////////////////////////////////////////
			/// <summary>
			/// Creates maximal disparity configuration. Evaluates maximal disparity offset and range.
			/// </summary>
			///
			/// <param name="iMipLevelWidth">	Width of the mip level. </param>
			/// <param name="iMipLevel">	 	Zero-based index of the mip level. </param>
			///
			/// <returns>	The new disparity configuration. </returns>
			////////////////////////////////////////////////////////////////////////////////////////////////////

			__CUDA_HDI__ Clu::_SDisparityConfig CreateDisparityConfig(int iMipLevelWidth, int iMipLevel) const
			{
				Clu::_SDisparityConfig xDispCfg;

				xDispCfg.Create(0, iMipLevelWidth, InfinityOffset(iMipLevel));

				return xDispCfg;
			}

			////////////////////////////////////////////////////////////////////////////////////////////////////
			/// <summary>	Creates a disparity configuration in a standardized way. </summary>
			///
			/// <param name="iDispRange">		   	The disparity range. If disparity range is smaller than
			/// 									zero, the maximal range is used. </param>
			/// <param name="iDispMin">		   		The minimal disparity. </param>
			/// <param name="iMipLevelWidth">	   	Width of image at the given mip-map level. </param>
			/// <param name="iMipLevel">		   	The zero-based mip-map level. </param>
			/// <param name="bDispDataAtLevelZero">	True if the given disparity data iDispRange and
			/// 									iDispOffset is given for disparity level zero. Otherwise,
			/// 									the disparity data is given for the disparity level
			/// 									iMipLevel. </param>
			///
			/// <returns>	The new disparity configuration. </returns>
			////////////////////////////////////////////////////////////////////////////////////////////////////

			__CUDA_HDI__ Clu::_SDisparityConfig CreateDisparityConfig(int iDispMin, int iDispMax, int iMipLevelWidth, int iMipLevel
				, bool bDispDataAtLevelZero = true) const
			{
				Clu::_SDisparityConfig xDispCfg;

				int iMin, iMax;
				int iInfOff = InfinityOffset(iMipLevel);
				int iEffMin = Clu::Max(0, iInfOff - iMipLevelWidth + 1);
				int iEffMax = Clu::Max(0, iMipLevelWidth - 1 + iInfOff);

				if (iDispMin < 0)
				{
					iMin = 0;
				}
				else
				{
					if (bDispDataAtLevelZero)
					{
						iMin = iDispMin >> iMipLevel;
					}
					else
					{
						iMin = iDispMin;
					}
				}

				
				if (iDispMax < 0)
				{
					iMax = iEffMax;
				}
				else
				{
					if (bDispDataAtLevelZero)
					{
						iMax = iDispMax >> iMipLevel;
					}
					else
					{
						iMax = iDispMax;
					}
				}

				iMin = Clu::Max(iMin, iEffMin);
				iMax = Clu::Min(iMax, iEffMax);

				xDispCfg.Create(iMin, iMax, iInfOff);

				return xDispCfg;
			}


			__CUDA_HDI__ bool TryProjectTo3D(TVec3& vPos, const TVec2& vPosLeftPX, TValue dDisparity
				, const Clu::_SDisparityConfig& xDispCfg, const Clu::_SImageFormat& xF, TValue dPrec) const
			{
				using TLine3D = Clu::SLine3D<TValue>;

				//bool bHasIntersection = false;

				TVec2 vPosRightPX;
				TVec3 vPosL, vPosR;

				vPosRightPX[0] = xDispCfg.MapPixelPosLeftToRight(vPosLeftPX[0], dDisparity);
				vPosRightPX[1] = vPosLeftPX[1];

				// /////////////////////////////////////////////////////////////////////////
				// Debug
				//double dXL, dXR, dXR2, dY;
				//TVec3 vPosR2;
				//m_pCam[Left].Sensor().Map_SensorM_to_PixelF(dXL, dY, m_pCam[Left].PinholeM_s());
				//m_pCam[Right].Sensor().Map_SensorM_to_PixelF(dXR, dY, m_pCam[Right].PinholeM_s());
				//m_pCam[Left].Map_PixelIX_to_WorldM(vPosL, dXL, dY, xF);
				//m_pCam[Right].Map_PixelIX_to_WorldM(vPosR, dXR, dY, xF);

				//dXR2 = xDispCfg.MapPixelPosLeftToRight(dXL, 0.0);
				//m_pCam[Right].Map_PixelIX_to_WorldM(vPosR2, dXR2, dY, xF);

				//TVec3 vXL, vYL, vZL;
				//TVec3 vXR, vYR, vZR;

				//m_pCam[Left].Sensor().FrameM_s_w().GetBasis_l_r(vXL, vYL, vZL);
				//m_pCam[Right].Sensor().FrameM_s_w().GetBasis_l_r(vXR, vYR, vZR);

				// /////////////////////////////////////////////////////////////////////////

				m_pCam[Left].Map_PixelIX_to_WorldM(vPosL, vPosLeftPX[0], vPosLeftPX[1], xF);
				m_pCam[Right].Map_PixelIX_to_WorldM(vPosR, vPosRightPX[0], vPosRightPX[1], xF);

				TLine3D xProjLineLeft, xProjLineRight;

				xProjLineLeft.vOrigin = m_pCam[Left].PinholeM_w();
				xProjLineLeft.vDir = Normalize(vPosL - xProjLineLeft.vOrigin);

				xProjLineRight.vOrigin = m_pCam[Right].PinholeM_w();
				xProjLineRight.vDir = Normalize(vPosR - xProjLineRight.vOrigin);

				return Clu::TryIntersect(vPos, xProjLineLeft, xProjLineRight, dPrec); //Clu::CValuePrecision<TValue>::DefaultPrecision());
			}


			__CUDA_HDI__ void ProjectFrom3D(TVec2& vPosLeftPX, TValue& dDisparity, const TVec3& vPos
				, const Clu::_SDisparityConfig& xDispCfg, const Clu::_SImageFormat& xF) const
			{
				TValue dLeftX, dLeftY, dZ;
				TValue dRightX, dRightY;
				m_pCam[0].Project_WorldM_to_PixelF(dLeftX, dLeftY, dZ, vPos, xF);
				m_pCam[1].Project_WorldM_to_PixelF(dRightX, dRightY, dZ, vPos, xF);

				dDisparity = xDispCfg.EvalDisparity(dLeftX, dRightX);
				vPosLeftPX.SetElements(dLeftX, dLeftY);
			}

			////////////////////////////////////////////////////////////////////////////////////////////////////
			/// <summary>
			/// Convert disparity to depth range. Given a disparity configuration with offset and range,
			/// together with an image format, this function calculates the depth range along the z-axis of
			/// the left camera of the stereo system. This function is mainly useful for a rectified camera
			/// system. The return values dDistNear and dDistFar give the distances from center of the left
			/// image sensor to the depth volume. If the disparity range is larger than is needed to map
			/// infinity, the returned distance is set to infinity.
			/// </summary>
			///
			/// <param name="dDistNear">	[out] The near distance. </param>
			/// <param name="dDistFar"> 	[out] The far distance. </param>
			/// <param name="xDispCfg"> 	The disparity configuration. </param>
			/// <param name="xF">			The image format to use. </param>
			////////////////////////////////////////////////////////////////////////////////////////////////////

			__CUDA_HDI__ void ConvertDisparityToDepthRange(TValue &dDistNear, TValue &dDistFar
				, TValue dDispMin, TValue dDispMax
				, const Clu::_SDisparityConfig& xDispCfg, const Clu::_SImageFormat& xF) const
			{
				using TLine3D = Clu::SLine3D<TValue>;

				TVec3 vPos;
				TVec2 vPosLeftPX;

				// Assume that the disparity config is consistent with the given image format.
				// That is, if the disparity config is calculated for a particular mip-map level
				// xF contains the image format for that mip-map level.

				// Take as left position the optical center at the given image resolution.
				m_pCam[Left].Sensor().Map_SensorM_to_PixelF(vPosLeftPX[0], vPosLeftPX[1], m_pCam[Left].PinholeM_s(), xF);

				if (TryProjectTo3D(vPos, vPosLeftPX, dDispMin, xDispCfg, xF, TValue(1e-3)))
				{
					// world position into sensor coordinate system.
					vPos = m_pCam[Left].Sensor().FrameM_s_w().MapIntoFrame(vPos);
					if (vPos[2] >= TValue(0))
					{
						dDistFar = Clu::NumericLimits<TValue>::Infinity();
					}
					else
					{
						dDistFar = -vPos[2];
					}
				}
				else
				{
					dDistFar = Clu::NumericLimits<TValue>::Infinity();
				}

				if (TryProjectTo3D(vPos, vPosLeftPX, dDispMax, xDispCfg, xF, TValue(1e-3)))
				{
					// world position into sensor coordinate system.
					vPos = m_pCam[Left].Sensor().FrameM_s_w().MapIntoFrame(vPos);
					if (vPos[2] >= TValue(0))
					{
						dDistNear = Clu::NumericLimits<TValue>::Infinity();
					}
					else
					{
						dDistNear = -vPos[2];
					}
				}
				else
				{
					dDistNear = Clu::NumericLimits<TValue>::Infinity();
				}
			}

			////////////////////////////////////////////////////////////////////////////////////////////////////
			/// <summary>	Convert depth to disparity range. </summary>
			///
			/// <param name="xDispCfg">	[in,out] The disp configuration. </param>
			/// <param name="dNearZ">  	The near z coordinate. </param>
			/// <param name="dFarZ">   	The far z coordinate. </param>
			/// <param name="xF">	   	The x coordinate f. </param>
			////////////////////////////////////////////////////////////////////////////////////////////////////

			__CUDA_HDI__ void ConvertDepthToDisparityRange(Clu::_SDisparityConfig& xDispCfg, TValue dDistNear, TValue dDistFar
				, const Clu::_SImageFormat& xF) const
			{
				TVec3 vPos3d_s, vPos3d_w;
				TValue dNearLeftX, dFarLeftX, dLeftY, dZ;
				TValue dNearRightX, dFarRightX, dRightY;

				vPos3d_s = m_pCam[0].PinholeM_s();

				vPos3d_s[2] = -abs(dDistNear);
				vPos3d_w = m_pCam[Left].Sensor().FrameM_s_w().MapOutOfFrame(vPos3d_s);

				m_pCam[0].Project_WorldM_to_PixelF(dNearLeftX, dLeftY, dZ, vPos3d_w, xF);
				m_pCam[1].Project_WorldM_to_PixelF(dNearRightX, dRightY, dZ, vPos3d_w, xF);

				if (dDistFar == Clu::NumericLimits<TValue>::Infinity())
				{
					vPos3d_s[2] = -Clu::NumericLimits<TValue>::Max();
				}
				else
				{
					vPos3d_s[2] = -abs(dDistFar);
				}
				vPos3d_w = m_pCam[Left].Sensor().FrameM_s_w().MapOutOfFrame(vPos3d_s);

				m_pCam[0].Project_WorldM_to_PixelF(dFarLeftX, dLeftY, dZ, vPos3d_w, xF);
				m_pCam[1].Project_WorldM_to_PixelF(dFarRightX, dRightY, dZ, vPos3d_w, xF);

				xDispCfg.Create(dNearLeftX, dNearRightX, dFarLeftX, dFarRightX, InfinityOffset(0));
			}


			////////////////////////////////////////////////////////////////////////////////////////////////////
			/// <summary>
			/// Rectifies this stereo pinhole camera setup and stores the result in xRectStereoCam.
			/// </summary>
			///
			/// <param name="xRectStereoCam">	[out] The rectified stereo camera system. </param>
			////////////////////////////////////////////////////////////////////////////////////////////////////

			__CUDA_HD__ void Rectify(TThis& xRectStereoCam, EStereoRectifyOpticalAxis eOpticalAxis, ERectifyCropStyle eCropStyle)
			{
				using TLine2D = _SLine2D<TValue>;
				using TQuad2D = _SQuad2D<TValue>;
				using TRect2D = _SAlignedRect2D<TValue>;

				// Get the bases of the two pinhole cameras.
				TVec3 pvX[2], pvY[2], pvZ[2];
				TVec3 pvPinhole_w[2], pvCenter_w[2];
				TVec2 vRes;

				ForEachCameraIdx([&](TPinhole& xCam, TIdx i)
				{
					xCam.Sensor().FrameM_s_w().GetBasis_l_r(pvX[i], pvY[i], pvZ[i]);
					pvPinhole_w[i] = xCam.PinholeM_w();

					vRes = xCam.Sensor().ResolutionPX();
					xCam.Map_PixelIX_to_WorldM(pvCenter_w[i], vRes[0] / TValue(2), vRes[1] / TValue(2));
					pvZ[i] = Normalize(pvCenter_w[i] - pvPinhole_w[i]);
				});

				// The new x-axis of the rectifies stereo system in world coordinates has to point from the
				// left optical center to the right optical center.
				TVec3 vDirX_w = Normalize(pvPinhole_w[Right] - pvPinhole_w[Left]);

				// The new z-axis of the rectified frame has to be the part of the mean of the two z-axes of the pinhole cameras
				// that is perpendicular to vDirX_w. So first calculate the mean vector.
				TVec3 vDirZ_w;

				switch (eOpticalAxis)
				{
				case EStereoRectifyOpticalAxis::Balanced:
					vDirZ_w = ((pvZ[Left] + pvZ[Right]) / TValue(2));
					break;
					
				case EStereoRectifyOpticalAxis::Left:
					vDirZ_w = pvZ[Left];
					break;

				case EStereoRectifyOpticalAxis::Right:
					vDirZ_w = pvZ[Right];
					break;

				default:
					throw CLU_EXCEPTION("Stereo rectify optical axis type not supported");
				}

				// We can now calculate the remaining y-axis as the cross product of Z and X.
				TVec3 vDirY_w = Normalize(vDirZ_w ^ vDirX_w);

				// Now make the z-axis perpendicular to vDirX and vDirY.
				vDirZ_w = Normalize(vDirX_w ^ vDirY_w);


				// To find the optimal location of the rectified sensors, we need to project the 
				// sensor corners onto the projection plane of the rectified frame. 
				// The rectified projection plane is at the focal length distance along positive z-axis
				// from the corresponding pinhole. Note, that our z-axis points away from the scene.

				// Calculate the common focal length of the two cameras.
				TValue fMeanFocLen = (m_pCam[Left].FocalLength() + m_pCam[Right].FocalLength()) / TValue(2);

				ForEachCameraIdx([&](TPinhole& xCam, TIdx uCamIdx)
				{
					// Rectify each camera to the new common basis.
					xCam.GetRectified(xRectStereoCam[uCamIdx], vDirX_w, vDirY_w, vDirZ_w, fMeanFocLen, eCropStyle);
				});


				// Adjust the XY-resolutions of the two camera to be equal
				TVec2 vAdjRes;
				switch (eCropStyle)
				{
				case ERectifyCropStyle::InnerRectangle:
					vAdjRes = Min(xRectStereoCam[0].Sensor().ResolutionPX(), xRectStereoCam[1].Sensor().ResolutionPX());
					break;

				case ERectifyCropStyle::OuterRectangle:
					vAdjRes = Max(xRectStereoCam[0].Sensor().ResolutionPX(), xRectStereoCam[1].Sensor().ResolutionPX());
					break;

				default:
					throw CLU_EXCEPTION("Rectify crop style not supported");
				}

				// Adjust resolution to a multiple of 4 so that byte images can fit directly into a surface or texture
				vAdjRes = Floor(vAdjRes / TValue(4)) * TValue(4);

				xRectStereoCam[0].AdjustSensorResolutionPX(vAdjRes);
				xRectStereoCam[1].AdjustSensorResolutionPX(vAdjRes);

				// //////////////////////////////////////////////////////////
				// Debug
				//
				//{
				//	using namespace Clu::Debug::Script;

				//	CText xScript;

				//	xScript.DrawFrameBoxCoord(5.0, 10, 10, 10);

				//	Add(xScript, m_pCam[0], "l", EColor::Red, EColor::Green);
				//	Add(xScript, m_pCam[1], "r", EColor::Magenta, EColor::Green);
				//	Add(xScript, xRectStereoCam[0], "rl", EColor::Blue, EColor::Yellow);
				//	Add(xScript, xRectStereoCam[1], "rl", EColor::Cyan, EColor::Yellow);

				//	std::string sScript = xScript.ToString().ToCString();
				//}
			}
		};
	}
}