////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.Types1.rtl
// file:      IImage.cpp
//
// summary:   Declares the IImage interface
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
#include "IImage.h"
#include "IImageImpl.h"
#include "ImageIntern.h"


#include "IException.h"

#define CLU_EXCEPTION(theMsg) \
	Clu::CIException(theMsg, __FILE__, __FUNCTION__, __LINE__)

#define CLU_CATCH_RETHROW_ALL(theMsg) \
	catch (std::exception& xEx) \
		{ \
		throw Clu::CIException(Clu::CIString(theMsg) << " : " << xEx.what(), __FILE__, __FUNCTION__, __LINE__); \
		} \
	catch (Clu::CIException& xEx) \
		{ \
		throw Clu::CIException(Clu::CIString(theMsg), __FILE__, __FUNCTION__, __LINE__, std::move(xEx)); \
		} 

namespace Clu
{

#define REF (*m_pImpl)
#define REF_(theVar) (*theVar.m_pImpl)

#define INTERN (*(m_pImpl->Get()))
#define INTERN_(theVar) (*(theVar.m_pImpl->Get()))

	CIImage::CIImage()
	{
		try
		{
			m_pImpl = new CIImageImpl();
			if (m_pImpl == nullptr)
				return;

			REF.New();
		}
		CLU_CATCH_RETHROW_ALL("Error in constructor")
	}


	CIImage::~CIImage()
	{
		delete m_pImpl;
	}


	CIImage::CIImage(CIImage&& xEx)
	{
		m_pImpl = nullptr;
		*this = std::forward<CIImage>(xEx);
	}

	CIImage& CIImage::operator= (CIImage&& xEx)
	{
		delete m_pImpl;
		m_pImpl = xEx.m_pImpl;
		xEx.m_pImpl = nullptr;
		return *this;
	}

	CIImage::CIImage(const CIImage& xEx)
	{
		m_pImpl = new CIImageImpl(*xEx.m_pImpl);
	}

	CIImage& CIImage::operator= (const CIImage& xImg)
	{
		if (m_pImpl != nullptr && xImg.m_pImpl != nullptr)
		{
			REF = REF_(xImg);
		}

		return *this;
	}

	CIImage::CIImage(const SImageFormat& xStruct)
	{
		try
		{
			m_pImpl = new CIImageImpl();

			if (m_pImpl == nullptr)
				return;

			REF.New();

			Create(xStruct);
		}
		CLU_CATCH_RETHROW_ALL("Error constructing image")
	}

	CIImage::CIImage(const SImageFormat& xStruct, const void *pImageData, bool bCopyData)
	{
		try
		{
			m_pImpl = new CIImageImpl();

			if (m_pImpl == nullptr)
				return;

			REF.New();

			Create(xStruct, pImageData, bCopyData);
		}
		CLU_CATCH_RETHROW_ALL("Error constructing image")
	}

	bool CIImage::IsValidRef() const
	{
		if (m_pImpl == nullptr)
			return false;

		if (!REF.IsValid())
			return false;

		return true;
	}

	bool CIImage::IsValid() const
	{
		if (!IsValidRef())
			return false;

		if (!REF->IsValid())
			return false;

		return true;
	}

	bool CIImage::IsDataOwner() const
	{
		try
		{
			if (!IsValid())
				throw CLU_EXCEPTION("Invalid image instance");

			return REF->IsDataOwner();
		}
		CLU_CATCH_RETHROW_ALL("Error obtaining data owner flag")
	}

	CIImage CIImage::Copy() const
	{
		try
		{
			if (!IsValid())
				throw CLU_EXCEPTION("Invalid image instance");

			CIImage xImg;
			INTERN_(xImg).CopyFrom(INTERN);
			return xImg;
		}
		CLU_CATCH_RETHROW_ALL("Error copying image")
	}


	CIImage CIImage::Crop(int nX, int nY, int nWidth, int nHeight, bool bYOriginAtTop) const
	{
		try
		{
			if (!IsValid())
				throw CLU_EXCEPTION("Invalid image instance");

			CIImage xImg;
			INTERN_(xImg).CropFrom(INTERN, nX, nY, nWidth, nHeight, bYOriginAtTop);
			return xImg;
		}
		CLU_CATCH_RETHROW_ALL("Error cropping image")
	}

	void CIImage::Insert(const CIImage& xImage, int nX, int nY, bool bYOriginAtTop)
	{
		try
		{
			if (!IsValid())
				throw CLU_EXCEPTION("Invalid image instance");

			INTERN.Insert(INTERN_(xImage), nX, nY, bYOriginAtTop);
		}
		CLU_CATCH_RETHROW_ALL("Error inserting image")
	}

	void CIImage::Create(const SImageFormat& xStruct)
	{
		try
		{
			if (!IsValidRef())
				throw CLU_EXCEPTION("Invalid image instance");

			REF->Create(xStruct);
		}
		CLU_CATCH_RETHROW_ALL("Eror creating image")
	}

	void CIImage::Create(const SImageFormat& xStruct, const void *pImageData, bool bCopyData)
	{
		try
		{
			if (!IsValidRef())
				throw CLU_EXCEPTION("Invalid image instance");

			REF->Create(xStruct, pImageData, bCopyData);
		}
		CLU_CATCH_RETHROW_ALL("Error creating image")
	}

	void CIImage::Destroy()
	{
		try
		{
			if (!IsValid())
				throw CLU_EXCEPTION("Invalid image instance");

			REF->Destroy();
		}
		CLU_CATCH_RETHROW_ALL("Error destroying image")
	}

	void CIImage::Release()
	{
		try
		{
			if (!IsValidRef())
				throw CLU_EXCEPTION("Invalid image instance");

			REF.Release();
		}
		CLU_CATCH_RETHROW_ALL("Error releasing image reference")
	}

	const SImageFormat& CIImage::Format() const
	{
		try
		{
			if (!IsValid())
				throw CLU_EXCEPTION("Invalid image instance");

			return REF->Format();
		}
		CLU_CATCH_RETHROW_ALL("Error getting image structure")
	}

	int CIImage::Width() const
	{
		try
		{
			if (!IsValid())
				throw CLU_EXCEPTION("Invalid image instance");

			return REF->Width();
		}
		CLU_CATCH_RETHROW_ALL("Error getting image width")
	}

	int CIImage::Height() const
	{
		try
		{
			if (!IsValid())
				throw CLU_EXCEPTION("Invalid image instance");

			return REF->Height();
		}
		CLU_CATCH_RETHROW_ALL("Error getting image height")
	}

	void CIImage::GetSize(int& nWidth, int& nHeight) const
	{
		try
		{
			if (!IsValid())
				throw CLU_EXCEPTION("Invalid image instance");

			REF->GetSize(nWidth, nHeight);
		}
		CLU_CATCH_RETHROW_ALL("Error getting image size")
	}

	Clu::EDataType CIImage::DataType() const
	{
		try
		{
			if (!IsValid())
				throw CLU_EXCEPTION("Invalid image instance");

			return REF->DataType();
		}
		CLU_CATCH_RETHROW_ALL("Error getting image data type")
	}

	Clu::EPixelType CIImage::PixelType() const
	{
		try
		{
			if (!IsValid())
				throw CLU_EXCEPTION("Invalid image instance");

			return REF->PixelType();
		}
		CLU_CATCH_RETHROW_ALL("Error getting image pixel type")
	}

	const SImageType& CIImage::GetType() const
	{
		try
		{
			if (!IsValid())
				throw CLU_EXCEPTION("Invalid image instance");

			return REF->Type();
		}
		CLU_CATCH_RETHROW_ALL("Error getting image type")
	}

	size_t CIImage::BytesPerPixel() const
	{
		try
		{
			if (!IsValid())
				throw CLU_EXCEPTION("Invalid image instance");

			return REF->BytesPerPixel();
		}
		CLU_CATCH_RETHROW_ALL("Error getting bytes per pixel value")
	}

	size_t CIImage::PixelCount() const
	{
		try
		{
			if (!IsValid())
				throw CLU_EXCEPTION("Invalid image instance");

			return REF->PixelCount();
		}
		CLU_CATCH_RETHROW_ALL("Error getting pixel count")
	}

	size_t CIImage::ByteCount() const
	{
		try
		{
			if (!IsValid())
				throw CLU_EXCEPTION("Invalid image instance");

			return REF->ByteCount();
		}
		CLU_CATCH_RETHROW_ALL("Error getting byte count")
	}


	void* CIImage::DataPointer()
	{
		try
		{
			if (!IsValid())
				throw CLU_EXCEPTION("Invalid image instance");

			return REF->DataPointer();
		}
		CLU_CATCH_RETHROW_ALL("Error getting data pointer")
	}

	const void* CIImage::DataPointer() const
	{
		try
		{
			if (!IsValid())
				throw CLU_EXCEPTION("Invalid image instance");

			return REF->DataPointer();
		}
		CLU_CATCH_RETHROW_ALL("Error getting data pointer")
	}

} // namespace Clu
