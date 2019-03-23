////////////////////////////////////////////////////////////////////////////////////////////////////
// project:   CluTec.Types1.rtl
// file:      ILayerImage.cpp
//
// summary:   Declares the ILayerImage interface
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
#include "ILayerImage.h"
#include "ILayerImageImpl.h"
#include "LayerImage.h"

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

	CILayerImage::CILayerImage()
	{
		try
		{
			m_pImpl = new CILayerImageImpl();
			if (m_pImpl == nullptr)
				return;

			REF.New();
		}
		CLU_CATCH_RETHROW_ALL("Error in constructor")
	}


	CILayerImage::~CILayerImage()
	{
		delete m_pImpl;
	}


	CILayerImage::CILayerImage(CILayerImage&& xEx)
	{
		m_pImpl = nullptr;
		*this = std::forward<CILayerImage>(xEx);
	}

	CILayerImage& CILayerImage::operator= (CILayerImage&& xEx)
	{
		delete m_pImpl;
		m_pImpl = xEx.m_pImpl;
		xEx.m_pImpl = nullptr;
		return *this;
	}

	CILayerImage::CILayerImage(const CILayerImage& xEx)
	{
		m_pImpl = new CILayerImageImpl(*xEx.m_pImpl);
	}

	CILayerImage& CILayerImage::operator= (const CILayerImage& xImg)
	{
		if (m_pImpl != nullptr && xImg.m_pImpl != nullptr)
		{
			REF = REF_(xImg);
		}

		return *this;
	}

	CILayerImage::CILayerImage(const SImageFormat& xStruct)
	{
		try
		{
			m_pImpl = new CILayerImageImpl();

			if (m_pImpl == nullptr)
				return;

			REF.New();

			Create(xStruct);
		}
		CLU_CATCH_RETHROW_ALL("Error constructing image")
	}

	CILayerImage::CILayerImage(const SImageFormat& xStruct, const void **ppImageLayerData, size_t nLayerCount, bool bCopyData)
	{
		try
		{
			m_pImpl = new CILayerImageImpl();

			if (m_pImpl == nullptr)
				return;

			REF.New();

			Create(xStruct, ppImageLayerData, nLayerCount, bCopyData);
		}
		CLU_CATCH_RETHROW_ALL("Error constructing image")
	}

	bool CILayerImage::IsValidRef() const
	{
		if (m_pImpl == nullptr)
			return false;

		if (!REF.IsValid())
			return false;

		return true;
	}

	bool CILayerImage::IsValid() const
	{
		if (!IsValidRef())
			return false;

		if (!REF->IsValid())
			return false;

		return true;
	}

	bool CILayerImage::IsCompactMemoryBlock() const
	{
		try
		{
			if (!IsValid())
				throw CLU_EXCEPTION("Invalid image instance");

			return REF->IsCompactMemoryBlock();
		}
		CLU_CATCH_RETHROW_ALL("Error copying image")
	}

	bool CILayerImage::IsDataOwner() const
	{
		try
		{
			if (!IsValid())
				throw CLU_EXCEPTION("Invalid image instance");

			return REF->IsDataOwner();
		}
		CLU_CATCH_RETHROW_ALL("Error copying image")
	}

	CILayerImage CILayerImage::Copy() const
	{
		try
		{
			if (!IsValid())
				throw CLU_EXCEPTION("Invalid image instance");

			CILayerImage xImg;
			INTERN_(xImg).CopyFrom(INTERN);
			return xImg;
		}
		CLU_CATCH_RETHROW_ALL("Error copying image")
	}


	CILayerImage CILayerImage::Crop(int nX, int nY, int nWidth, int nHeight, bool bYOriginAtTop) const
	{
		try
		{
			if (!IsValid())
				throw CLU_EXCEPTION("Invalid image instance");

			CILayerImage xImg;
			INTERN_(xImg).CropFrom(INTERN, nX, nY, nWidth, nHeight, bYOriginAtTop);
			return xImg;
		}
		CLU_CATCH_RETHROW_ALL("Error cropping image")
	}

	void CILayerImage::Insert(const CILayerImage& xImage, int nX, int nY, bool bYOriginAtTop)
	{
		try
		{
			if (!IsValid())
				throw CLU_EXCEPTION("Invalid image instance");

			INTERN.Insert(INTERN_(xImage), nX, nY, bYOriginAtTop);
		}
		CLU_CATCH_RETHROW_ALL("Error inserting image")
	}


	void CILayerImage::Create(const SImageFormat& xStruct)
	{
		try
		{
			if (!IsValidRef())
				throw CLU_EXCEPTION("Invalid image instance");

			REF->Create(xStruct);
		}
		CLU_CATCH_RETHROW_ALL("Eror creating image")
	}

	void CILayerImage::Create(const SImageFormat& xStruct, const void **ppImageLayerData, size_t nLayerCount, bool bCopyData)
	{
		try
		{
			if (!IsValidRef())
				throw CLU_EXCEPTION("Invalid image instance");

			REF->Create(xStruct, ppImageLayerData, nLayerCount, bCopyData);
		}
		CLU_CATCH_RETHROW_ALL("Error creating image")
	}

	void CILayerImage::Destroy()
	{
		try
		{
			if (!IsValid())
				throw CLU_EXCEPTION("Invalid image instance");

			REF->Destroy();
		}
		CLU_CATCH_RETHROW_ALL("Error destroying image")
	}

	void CILayerImage::Release()
	{
		try
		{
			if (!IsValidRef())
				throw CLU_EXCEPTION("Invalid image instance");

			REF.Release();
		}
		CLU_CATCH_RETHROW_ALL("Error releasing image reference")
	}

	const SImageFormat& CILayerImage::Format() const
	{
		try
		{
			if (!IsValid())
				throw CLU_EXCEPTION("Invalid image instance");

			return REF->Format();
		}
		CLU_CATCH_RETHROW_ALL("Error getting image structure")
	}

	int CILayerImage::Width() const
	{
		try
		{
			if (!IsValid())
				throw CLU_EXCEPTION("Invalid image instance");

			return REF->Width();
		}
		CLU_CATCH_RETHROW_ALL("Error getting image width")
	}

	int CILayerImage::Height() const
	{
		try
		{
			if (!IsValid())
				throw CLU_EXCEPTION("Invalid image instance");

			return REF->Height();
		}
		CLU_CATCH_RETHROW_ALL("Error getting image height")
	}

	void CILayerImage::GetSize(int& nWidth, int& nHeight) const
	{
		try
		{
			if (!IsValid())
				throw CLU_EXCEPTION("Invalid image instance");

			REF->GetSize(nWidth, nHeight);
		}
		CLU_CATCH_RETHROW_ALL("Error getting image size")
	}

	Clu::EDataType CILayerImage::DataType() const
	{
		try
		{
			if (!IsValid())
				throw CLU_EXCEPTION("Invalid image instance");

			return REF->DataType();
		}
		CLU_CATCH_RETHROW_ALL("Error getting image data type")
	}

	Clu::EPixelType CILayerImage::PixelType() const
	{
		try
		{
			if (!IsValid())
				throw CLU_EXCEPTION("Invalid image instance");

			return REF->PixelType();
		}
		CLU_CATCH_RETHROW_ALL("Error getting image pixel type")
	}

	const SImageType& CILayerImage::GetType() const
	{
		try
		{
			if (!IsValid())
				throw CLU_EXCEPTION("Invalid image instance");

			return REF->Type();
		}
		CLU_CATCH_RETHROW_ALL("Error getting image type")
	}

	size_t CILayerImage::LayerCount() const
	{
		try
		{
			if (!IsValid())
				throw CLU_EXCEPTION("Invalid image instance");

			return REF->LayerCount();
		}
		CLU_CATCH_RETHROW_ALL("Error getting layer count")
	}

	size_t CILayerImage::BytesPerPixel() const
	{
		try
		{
			if (!IsValid())
				throw CLU_EXCEPTION("Invalid image instance");

			return REF->BytesPerPixel();
		}
		CLU_CATCH_RETHROW_ALL("Error getting bytes per pixel value")
	}

	size_t CILayerImage::BytesPerLayerPixel() const
	{
		try
		{
			if (!IsValid())
				throw CLU_EXCEPTION("Invalid image instance");

			return REF->BytesPerLayerPixel();
		}
		CLU_CATCH_RETHROW_ALL("Error getting bytes per layer pixel value")
	}

	size_t CILayerImage::PixelCount() const
	{
		try
		{
			if (!IsValid())
				throw CLU_EXCEPTION("Invalid image instance");

			return REF->PixelCount();
		}
		CLU_CATCH_RETHROW_ALL("Error getting pixel count")
	}

	size_t CILayerImage::LayerByteCount() const
	{
		try
		{
			if (!IsValid())
				throw CLU_EXCEPTION("Invalid image instance");

			return REF->LayerByteCount();
		}
		CLU_CATCH_RETHROW_ALL("Error getting byte count")
	}

	size_t CILayerImage::TotalByteCount() const
	{
		try
		{
			if (!IsValid())
				throw CLU_EXCEPTION("Invalid image instance");

			return REF->TotalByteCount();
		}
		CLU_CATCH_RETHROW_ALL("Error getting byte count")
	}


	void* CILayerImage::DataPointer(size_t nLayerId)
	{
		try
		{
			if (!IsValid())
				throw CLU_EXCEPTION("Invalid image instance");

			return REF->DataPointer(nLayerId);
		}
		CLU_CATCH_RETHROW_ALL("Error getting data pointer")
	}

	const void* CILayerImage::DataPointer(size_t nLayerId) const
	{
		try
		{
			if (!IsValid())
				throw CLU_EXCEPTION("Invalid image instance");

			return REF->DataPointer(nLayerId);
		}
		CLU_CATCH_RETHROW_ALL("Error getting data pointer")
	}

} // namespace Clu
