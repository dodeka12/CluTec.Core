////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.Cuda.MultiView
// file:      DisparityConfig.h
//
// summary:   Declares the disparity configuration class
//
//            Copyright (c) 2016 CluTec. All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include "CluTec.Types1/Pixel.h"
#include "CluTec.Math/StandardMath.h"

namespace Clu
{
	struct _SDisparityConfig
	{
	public:
		using TPixelEx = Clu::TPixel_RGBA_UInt16;
		using TPixel = Clu::TPixel_Lum_UInt16;
		using TPixelF = Clu::TPixel_Lum_Single;

		using TDisp = typename TPixel::TData;
		using TDispF = typename TPixelF::TData;

	protected:
		/// <summary>	The minimal disparity relative to the the infinity offset. </summary>
		int m_iMin;


		/// <summary>	The maximal disparity relative to the infinity offset. </summary>
		int m_iMax;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// The infinity offset. The offset from left to right image in pixel position where the
		/// projection rays are parallel.
		/// </summary>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		int m_iInfOffsetLR;

	public:

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Creates this object. </summary>
		///
		/// <param name="_iMin">			The minimal disparity relative to the infinity offset. </param>
		/// <param name="_iRange">			The disparity range starting at the minimal disparity. </param>
		/// <param name="_iInfOffsetLR">	The infinity offset. </param>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		__CUDA_HDI__ void Create(int _iMin, int _iMax, int _iInfOffsetLR)
		{
			m_iMin = _iMin;
			m_iMax = _iMax;
			m_iInfOffsetLR = _iInfOffsetLR;
		}

		template<typename TValue>
		__CUDA_HDI__ void Create(TValue fNearPosLeft, TValue fNearPosRight, TValue fFarPosLeft, TValue fFarPosRight, int _iInfOffsetLR)
		{
			m_iInfOffsetLR = _iInfOffsetLR;
			m_iMin = Clu::ToIntRound(EvalDisparity(fFarPosLeft, fFarPosRight));
			m_iMax = Clu::ToIntRound(EvalDisparity(fNearPosLeft, fNearPosRight));
		}

		__CUDA_HDI__ int Min() const
		{
			return m_iMin;
		}

		__CUDA_HDI__ int Max() const
		{
			return m_iMax;
		}

		__CUDA_HDI__ int InfOffsetLR() const
		{
			return m_iInfOffsetLR;
		}

		__CUDA_HDI__ int MapPixelPosLeftToRight(int iPixelPosLeft, TDisp uDisparity) const
		{
			return iPixelPosLeft - (int(uDisparity) - m_iInfOffsetLR);
		}

		__CUDA_HDI__ int MapPixelPosRightToLeft(int iPixelPosRight, TDisp uDisparity) const
		{
			return iPixelPosRight + (int(uDisparity) - m_iInfOffsetLR);
		}

		__CUDA_HDI__ int MapPixelPos(int iPixelPos, TDisp uDisparity, int iIsLeftToRight) const
		{
			return iPixelPos + (1 - 2 * iIsLeftToRight) * (int(uDisparity) - m_iInfOffsetLR);
		}

		__CUDA_HDI__ TDisp MaxDisparity(int iPixelPos, int iWidth, int iIsLeftToRight) const
		{
			return TDisp(Clu::Max(0, m_iInfOffsetLR - (1 - 2 * iIsLeftToRight) * iPixelPos + (1 - iIsLeftToRight) * (iWidth - 1)));
		}


		template<typename TValue>
		__CUDA_HDI__ TValue MapPixelPosLeftToRight(TValue fPixelPosLeft, TValue fDisparity) const
		{
			return fPixelPosLeft - (fDisparity - TValue(m_iInfOffsetLR));
		}

		template<typename TValue>
		__CUDA_HDI__ TValue MapPixelPosRightToLeft(TValue fPixelPosRight, TValue fDisparity) const
		{
			return fPixelPosRight + (fDisparity - TValue(m_iInfOffsetLR));
		}

		template<typename TValue>
		__CUDA_HDI__ TValue MapPixelPos(TValue fPixelPos, TValue fDisparity, int iIsLeftToRight) const
		{
			return fPixelPos + TValue(1 - 2 * iIsLeftToRight) * (fDisparity - TValue(m_iInfOffsetLR));
		}


		template<typename TValue>
		__CUDA_HDI__ TValue EvalDisparity(TValue fPixelPosLeft, TValue fPixelPosRight) const
		{
			return fPixelPosLeft - fPixelPosRight + TValue(m_iInfOffsetLR);
		}

	};
}