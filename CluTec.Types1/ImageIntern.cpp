////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.Types1.rtl
// file:      ImageIntern.cpp
//
// summary:   Implements the image intern class
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
#include "ImageIntern.h"
#include "IException.h"
#include "Defines.h"

#include <utility>


namespace Clu
{


	CImageIntern::CImageIntern()
	{
		_Reset();
	}


	CImageIntern::~CImageIntern()
	{
		Destroy();
	}


	CImageIntern::CImageIntern(CImageIntern&& xImage)
	{
		*this = std::forward<CImageIntern>(xImage);
	}

	CImageIntern& CImageIntern::operator= (CImageIntern&& xImage)
	{
		m_xFormat = xImage.m_xFormat;

		m_pucData = xImage.m_pucData;
		m_bDataOwner = xImage.m_bDataOwner;

		xImage._Reset();
		return *this;
	}

	CImageIntern::CImageIntern(const CImageIntern& xImage)
	{
		*this = xImage;
	}

	CImageIntern& CImageIntern::operator=(const CImageIntern& xImage)
	{
		if (this == &xImage)
			return *this;

		if (!xImage.IsValid())
		{
			Destroy();
		}
		else
		{
			Create(xImage.m_xFormat, xImage.m_pucData, xImage.m_bDataOwner);
		}

		return *this;
	}


	CImageIntern::CImageIntern(const SImageFormat& xStruct)
	{
		_Reset();
		Create(xStruct);
	}

	CImageIntern::CImageIntern(const SImageFormat& xStruct, const void *pImageData, bool bCopyData)
	{
		_Reset();
		Create(xStruct, pImageData, bCopyData);
	}


	void CImageIntern::Create(const SImageFormat& xFormat)
	{
		// If this image already has the correct format then don't create it again
		if (m_xFormat == xFormat && m_bDataOwner)
		{
			return;
		}

		Destroy();

		m_xFormat = xFormat;

		m_pucData = new TData[ByteCount()];
		m_bDataOwner = true;
	}

	void CImageIntern::Create(const SImageFormat& xFormat, const void *pImageData, bool bCopyData)
	{
		if (bCopyData)
		{
			Create(xFormat);
			memcpy(m_pucData, pImageData, ByteCount());
		}
		else
		{
			Destroy();

			m_xFormat = xFormat;
			m_pucData = (TData *)pImageData;
			m_bDataOwner = false;
		}
	}

	void CImageIntern::_Reset()
	{
		m_xFormat.Clear();

		m_pucData = nullptr;
		m_bDataOwner = false;
	}


	void CImageIntern::Destroy()
	{
		if (m_bDataOwner)
		{
			delete[] m_pucData;
		}

		_Reset();
	}


	void CImageIntern::CopyFrom(const CImageIntern& xImage)
	{
		if (!xImage.IsValid())
		{
			throw CLU_EXCEPTION("Invalid image to crop from");
		}

		Create(xImage.m_xFormat, xImage.m_pucData, true);
	}


	void CImageIntern::CropFrom(const CImageIntern& xImage, int iX, int iY, int iWidth, int iHeight, bool bYOriginAtTop)
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
		int nSrcStride = xImage.m_xFormat.iWidth * int(xImage.BytesPerPixel());
		TData* pSrc = xImage.m_pucData + (nAdjY * nSrcStride) + (iX * int(xImage.BytesPerPixel()));

		int nTrgStride = m_xFormat.iWidth * int(BytesPerPixel());
		TData* pTrg = m_pucData;

		for (int nIdx = 0; nIdx < iHeight; ++nIdx, pSrc += nSrcStride, pTrg += nTrgStride)
		{
			memcpy(pTrg, pSrc, nTrgStride);
		}
	}

	void CImageIntern::Insert(const CImageIntern& xImage, int nX, int nY, bool bYOriginAtTop)
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

		int nSrcStride = xImage.m_xFormat.iWidth * int(xImage.BytesPerPixel());
		TData* pSrc = xImage.m_pucData;

		int nAdjY = (bYOriginAtTop ? nY : m_xFormat.iHeight - nY - xImage.m_xFormat.iHeight);
		int nTrgStride = m_xFormat.iWidth * int(BytesPerPixel());
		TData* pTrg = m_pucData + (nAdjY * nTrgStride) + (nX * int(BytesPerPixel()));;

		for (int nIdx = 0; nIdx < xImage.m_xFormat.iHeight; ++nIdx, pSrc += nSrcStride, pTrg += nTrgStride)
		{
			memcpy(pTrg, pSrc, nTrgStride);
		}

	}

} // namespace Clu

