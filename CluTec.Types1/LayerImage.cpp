////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.Types1.rtl
// file:      LayerImage.cpp
//
// summary:   Implements the layer image class
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

#include "stdafx.h"

#include <utility>

#include "Defines.h"
#include "IException.h"

#include "LayerImage.h"



namespace Clu
{


	CLayerImage::CLayerImage()
	{
		_Reset();
	}


	CLayerImage::~CLayerImage()
	{
		Destroy();
	}


	CLayerImage::CLayerImage(CLayerImage&& xImage)
	{
		*this = std::forward<CLayerImage>(xImage);
	}

	CLayerImage& CLayerImage::operator= (CLayerImage&& xImage)
	{
		m_xFormat = xImage.m_xFormat;

		m_vecLayerPtr = std::move(xImage.m_vecLayerPtr);
		m_bDataOwner = xImage.m_bDataOwner;

		xImage._Reset();
		return *this;
	}

	CLayerImage::CLayerImage(const CLayerImage& xImage)
	{
		*this = xImage;
	}

	CLayerImage& CLayerImage::operator=(const CLayerImage& xImage)
	{
		if (this == &xImage)
			return *this;

		if (!xImage.IsValid())
		{
			Destroy();
		}
		else
		{
			Create(xImage.m_xFormat, xImage.m_vecLayerPtr, xImage.m_bDataOwner);
		}

		return *this;
	}


	CLayerImage::CLayerImage(const SImageFormat& xStruct)
	{
		_Reset();
		Create(xStruct);
	}

	CLayerImage::CLayerImage(const SImageFormat& xStruct, const void **ppImageLayerData, size_t nLayerCount, bool bCopyData)
	{
		_Reset();
		Create(xStruct, ppImageLayerData, nLayerCount, bCopyData);
	}


	void CLayerImage::_Reset()
	{
		m_xFormat.Clear();

		m_vecLayerPtr.clear();
		m_bDataOwner = false;
		m_bIsCompactMemoryBlock = false;
	}


	void CLayerImage::Create(const SImageFormat& xFormat)
	{
		// If this image already has the correct format then don't create it again
		if (m_xFormat == xFormat && m_bDataOwner)
		{
			return;
		}

		Destroy();

		m_xFormat = xFormat;

		size_t nLayerCount = SImageType::DimOf(m_xFormat.ePixelType);
		m_vecLayerPtr.resize(nLayerCount);
		TData *pCurLayer = new TData[TotalByteCount()];
		
		m_bIsCompactMemoryBlock = true;

		for (auto &pLayer : m_vecLayerPtr)
		{
			pLayer = pCurLayer;
			pCurLayer += LayerByteCount();
		}

		m_bDataOwner = true;
	}

	void CLayerImage::Create(const SImageFormat& xFormat, const void **ppImageLayerData, size_t nLayerCount, bool bCopyData)
	{
		if (nLayerCount != SImageType::DimOf(xFormat.ePixelType))
		{
			throw CLU_EXCEPTION("Image pixel type is incompatible with number of image layers given");
		}

		if (bCopyData)
		{
			Create(xFormat);

			size_t nLayerIdx = 0;
			for (auto pLayer : m_vecLayerPtr)
			{
				memcpy(pLayer, ppImageLayerData[nLayerIdx], LayerByteCount());
				++nLayerIdx;
			}
		}
		else
		{
			Destroy();

			m_xFormat = xFormat;
			m_vecLayerPtr.resize(nLayerCount);

			size_t nLayerIdx = 0;
			for (auto &pLayer : m_vecLayerPtr)
			{
				pLayer = (TData *) ppImageLayerData[nLayerIdx];
				++nLayerIdx;
			}

			m_bDataOwner = false;
		}
	}


	void CLayerImage::Destroy()
	{
		if (m_bDataOwner)
		{
			delete[] m_vecLayerPtr[0];
		}

		_Reset();
	}


	void CLayerImage::CopyFrom(const CLayerImage& xImage)
	{
		if (!xImage.IsValid())
		{
			throw CLU_EXCEPTION("Invalid image to crop from");
		}

		Create(xImage.m_xFormat, xImage.m_vecLayerPtr, true);
	}


	void CLayerImage::CropFrom(const CLayerImage& xImage, int iX, int iY, int iWidth, int iHeight, bool bYOriginAtTop)
	{
		if (!xImage.IsValid())
		{
			throw CLU_EXCEPTION("Given image is invalid");
		}

		if (this == &xImage)
		{
			throw CLU_EXCEPTION("Cannot crop into same image");
		}

		if (iX + iWidth > xImage.Width())
		{
			throw CLU_EXCEPTION("Horizontal crop area out of range");
		}

		if (iY + iHeight > xImage.Height())
		{
			throw CLU_EXCEPTION("Vertical crop area out of range");
		}

		Create(SImageFormat(iWidth, iHeight, xImage.m_xFormat.ePixelType, xImage.m_xFormat.eDataType));

		int nAdjY = (bYOriginAtTop ? iY : xImage.m_xFormat.iHeight - iY - iHeight);
		int nSrcStride = xImage.m_xFormat.iWidth * int(xImage.BytesPerLayerPixel());
		int nTrgStride = m_xFormat.iWidth * int(BytesPerLayerPixel());

		for (size_t nLayerIdx = 0; nLayerIdx < LayerCount(); ++nLayerIdx)
		{
			TData* pSrc = xImage.m_vecLayerPtr[nLayerIdx] + (nAdjY * nSrcStride) + (iX * int(xImage.BytesPerLayerPixel()));
			TData* pTrg = m_vecLayerPtr[nLayerIdx];

			for (int nIdx = 0; nIdx < iHeight; ++nIdx, pSrc += nSrcStride, pTrg += nTrgStride)
			{
				memcpy(pTrg, pSrc, nTrgStride);
			}
		}
	}

	void CLayerImage::Insert(const CLayerImage& xImage, int nX, int nY, bool bYOriginAtTop)
	{
		if (!IsValid())
		{
			throw CLU_EXCEPTION("Invalid image");
		}

		if (!xImage.IsValid())
		{
			throw CLU_EXCEPTION("Given image is invalid");
		}

		if (this == &xImage)
		{
			throw CLU_EXCEPTION("Cannot insert into same image");
		}

		if (Type() != xImage.Type())
		{
			throw CLU_EXCEPTION("Inserted image has to be of same type as this image");
		}

		if (nX + xImage.m_xFormat.iWidth > m_xFormat.iWidth)
		{
			throw CLU_EXCEPTION("Horizontal insert area out of range");
		}

		if (nY + xImage.m_xFormat.iHeight > m_xFormat.iHeight)
		{
			throw CLU_EXCEPTION("Vertical insert area out of range");
		}

		int nSrcStride = xImage.m_xFormat.iWidth * int(xImage.BytesPerLayerPixel());
		int nAdjY = (bYOriginAtTop ? nY : m_xFormat.iHeight - nY - xImage.m_xFormat.iHeight);
		int nTrgStride = m_xFormat.iWidth * int(BytesPerLayerPixel());

		for (size_t nLayerIdx = 0; nLayerIdx < LayerCount(); ++nLayerIdx)
		{
			TData* pSrc = xImage.m_vecLayerPtr[nLayerIdx];
			TData* pTrg = m_vecLayerPtr[nLayerIdx] + (nAdjY * nTrgStride) + (nX * int(BytesPerLayerPixel()));

			for (int nIdx = 0; nIdx < xImage.m_xFormat.iHeight; ++nIdx, pSrc += nSrcStride, pTrg += nTrgStride)
			{
				memcpy(pTrg, pSrc, nTrgStride);
			}
		}
	}

} // namespace Clu

